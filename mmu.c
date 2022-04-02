/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
extern int code_copy(uint32_t src, uint32_t dst);
extern int getCR3();

unsigned int next_free_kernel_page;
unsigned int next_free_task_page;

void mmu_init() {
    next_free_kernel_page =  FIRST_FREE_KERNEL_PAGE;
    next_free_task_page =  FIRST_FREE_TASK_PAGE;
}


uint32_t mmu_nextFreeKernelPage() {             //Nueva página en memoria fisica en el area libre Kernel, osea en los 
                                                //segundos 3 MBytes de memoria. 
    unsigned int free_page = next_free_kernel_page;
    next_free_kernel_page += PAGE_SIZE;
    return free_page;
}

uint32_t mmu_nextFreeTaskPage() {               //Nueva página en memoria fisica en el area libre tareas, osea en los 
                                                //terceros 4 MBytes de memoria. 
    unsigned int free_page = next_free_task_page;
    next_free_task_page += PAGE_SIZE;
    return free_page;
}

uint32_t  mmu_initTaskDir(uint32_t jugador, uint16_t duplicando){     //Si el jugador es A, entonces jugador == 0 

    pdentry *pde = (pdentry* ) mmu_nextFreeKernelPage() ;          // Dirección de inicializacion del directorio de páginas. Ocupa 4KBytes.
    pde[0].p = 1;                   // Tabla de descriptores de páginas (apuntará a la unica dirección valairda del directorio), 
                                    // puede almacenar hasta 1024 descriptores de páginas validors de 4 KBity c/u.
                                    // Estas 1024 contendran codigo y datos de la tarea.
                                    // De este modo inicializamos un proceso con solo dos tablas de 4KBytes para administrar hasta 
                                    // 1024 páginas de 4KBytes, es decir 4MBytes para acomodar su cogigo y datos. 
    pde[0].rw = 1;                  // Establecemos que la página puede ser escrita.
    pde[0].us = 0;
    pde[0].pwt = 0;
    pde[0].pcd = 0;
    pde[0].a = 0;
    pde[0].ign = 0;
    pde[0].ps = 0;
    pde[0].g = 0;
    pde[0].avl = 0;
    uint32_t new_task_page_table = mmu_nextFreeKernelPage();
    pde[0].base = (new_task_page_table  >> 12);  // Dirección de la pila donde esta la tabla de páginas del kernel
                                    //xxxxxxxx | xxxxxxxxxx | xxxxxxxxxxxx los 12 bites enos singinficativos no nos importa, solo 
                                    //tomamos los primeros 20. 

for(int i = 1; i < 1024; i++){
    pde[i].p = 0;
}

    ptentry *pte = (ptentry* )new_task_page_table;   // Creamos el arreglo de page table entry y lo posicionamos en la direccion de memoria 
                                       

for(int i = 0; i < 1024; i++){
    pte[i].p = 1;                    
    pte[i].rw = 1;                      // Establecemos que la página puede ser escrita.
    pte[i].us = 0;
    pte[i].pwt = 0;
    pte[i].pcd = 0;
    pte[i].a = 0;
    pte[i].d = 0;
    pte[i].pat= 0;
    pte[i].g = 0;
    pte[i].avl = 0;
    pte[i].base = i;  
}

//1. pedir pagina libre tarea P1
//2. pedir pagina libre tarea P2
    uint32_t physical1 = mmu_nextFreeTaskPage();
    uint32_t physical2 = mmu_nextFreeTaskPage();


//3. mapear P1 con idd a cr3 actual
//4. mapear P2 con idd a cr3 actual
      
    uint32_t actual_cr3 = rcr3();

    mmu_mapPage(physical1, physical1, actual_cr3, ATTR);  //mapeamos la dirección virtual 0x8000000 a una fisica cualquiera que me dio la linea anterior
    mmu_mapPage(physical2, physical2, actual_cr3, ATTR);  //mapeamos la dirección virtual 0x8001000 a otra fisica cualquiera que me dio la linea anterior

//5. copiar codigo desde el kernel o desde la tarea a P1
//6. copiar codigo desde el kernel o desde la tarea a P2

    if(duplicando){
        memcpy(0x8000000, physical1, 4096);
        memcpy(0x8001000, physical2, 4096);
    } else {
        if (jugador == JUGADOR_A){
            memcpy(0x10000, physical1, 4096);
            memcpy(0x11000, physical2, 4096);
        } else{
            memcpy(0x12000, physical1, 4096);
            memcpy(0x13000, physical2, 4096);
        }
    }
    

//7. map P1 al cr3 nuevo en 0x8000000
//8. map P2 al cr3 nuevo en 0x8001000

    uint32_t new_cr3 = (uint32_t) pde;          //CASTEAR: PONEMOS ENTRE () EL QUE QUEREMOS QUE SEA.


    mmu_mapPage(0x8000000, physical1, new_cr3, 7);  //mapeamos la dirección virtual 0x800000 a una fisica cualquiera que me dio la linea anterior
    mmu_mapPage(0x8001000, physical2, new_cr3, 7);  //mapeamos la dirección virtual 0x800100 a otra fisica cualquiera que me dio la linea anterior


//9. desmapear P1 idd en mi cr3 actual
//10. desmapear P2 idd en mi cr3 actual

    mmu_unmapPage(physical1, actual_cr3);
    mmu_unmapPage(physical2, actual_cr3);
 
    
    return new_cr3;
 }

void mmu_mapPage(uint32_t virtual, uint32_t fisica, uint32_t cr3, uint32_t atributos) { 

//La dirección virtual es la direccion lineal de la diapositiva 15 de la clase de Ezequiel.(Es la que desarmamos)
//void mmu_mappear_pagina(unsigned int virtual, unsigned int dir_pdt, unsigned int fisica, unsigned int atributos) {

    int32_t pdeidx = virtual >> 22;             // Nos quedamos solo con los 10 bits más sirnificativos, que es 
                                                // donde se encuentra el indice del page directory. 
    int32_t pteidx = (virtual << 10) >> 22;     // Primero shifteamos 10 hacia <-- para sacarnos de encima los 
                                                // bits del indice del page directory y después shifteamos 22
                                                // para quedarme solo con el indice del page table.

    //int cr3 = getCR3();                         // MOV RAX, CR3 

    pdentry* pdbase = (pdentry*) ((cr3 >> 12) << 12); //Para sacarnos los ultimos 3 bytes porque en los 20 primeros
                                                     // esta la direccion de nuestro page directory.
//    pdentry* pdtEnt = &(pdbase[pdeidx]);                //Estamos en el page directory y nos estamos metiendo en la page table.
    if (pdbase[pdeidx].p == 0) {
        ptentry* ptable = (ptentry*)mmu_nextFreeKernelPage(); //Pedimos una nueva pagina para crear una nueva page table.
        
        for(int i=0;i<1024;i++) ptable[i].p = 0;
                                                       // Devuelve una PDT Entry con todos los valores en 0
        pdbase[pdeidx].p = 0x1;
        pdbase[pdeidx].us = CONST_USER;
        pdbase[pdeidx].rw = CONST_WRITE;
        pdbase[pdeidx].base = ((uint32_t) ptable) >> 12;
    }

    ptentry* ptable = (ptentry*)(pdbase[pdeidx].base << 12);

    int getS = (atributos & 4) && 1;
    int getRW = (atributos << 30) >> 31;

    ptable[pteidx].base = fisica >> 12;                                //Ahora ponemos la direccion que queremos. 
    ptable[pteidx].us = getS;
    ptable[pteidx].rw = getRW;
    ptable[pteidx].p = 1;

    tlbflush();
}
 
uint32_t mmu_unmapPage(uint32_t virtual, uint32_t cr3) {
    
    int32_t pdedir = virtual >> 22;             // Nos quedamos solo con los 10 bits más sirnificativos, que es 
                                                // donde se encuentra el indice del page directory. 
    int32_t ptedir = (virtual << 10) >> 22;     // Primero shifteamos 10 hacia <-- para sacarnos de encima los 
                                                // bits del indice del page directory y después shifteamos 22
                                                // para quedarme solo con el indice del page table.

    pdentry* pdbase = (pdentry*) ((cr3 >> 12) << 12); //Para sacarnos los ultimos 3 bytes porque en los 20 primeros
                                                     // esta la direccion de nuestro page directory.

    //pdentry pdtEnt = pdbase[pdedir];                //Estamos en el page directory y nos estamos metiendo en la page table.

    (( (ptentry*)( (pdbase[pdedir].base) << 12 ) )[ptedir]).p = 0; //Obtenemos le page table entry correspondiente

    //pte.p = 0x0;             //Ponemos el bit presente en 0
   
    tlbflush();

    return 0;
}



uint32_t mmu_initKernelDir() {
    
    pdentry *pde = (pdentry* )KERNEL_PAGE_DIR ;         // Dirección de inicializacion del directorio de páginas. Ocupa 4KBytes.
    pde[0].p = 1;                   // Tabla de descriptores de páginas (apuntará a la unica dirección valairda del directorio), 
                                    // puede almacenar hasta 1024 descriptores de páginas validors de 4 KBity c/u.
                                    // Estas 1024 contendran codigo y datos de la tarea.
                                    // De este modo inicializamos un proceso con solo dos tablas de 4KBytes para administrar hasta 
                                    // 1024 páginas de 4KBytes, es decir 4MBytes para acomodar su cogigo y datos. 
    pde[0].rw = 1;                  // Establecemos que la página puede ser escrita.
    pde[0].us = 0;
    pde[0].pwt = 0;
    pde[0].pcd = 0;
    pde[0].a = 0;
    pde[0].ign = 0;
    pde[0].ps = 0;
    pde[0].g = 0;
    pde[0].avl = 0;
    pde[0].base = (KERNEL_PAGE_TABLE_0  >> 12);  // Dirección de la pila donde esta la tabla de páginas del kernel
                                    //xxxxxxxx | xxxxxxxxxx | xxxxxxxxxxxx los 12 bites enos singinficativos no nos importa, solo 
                                    //tomamos los primeros 20. 


for(int i = 1; i < 1024; i++){
	pde[i].p = 0;
}

    ptentry *pte = (ptentry* )KERNEL_PAGE_TABLE_0 ;   // Creamos el arreglo de page table entry y lo posicionamos en la direccion de memoria 
                                         // física 0x28000.

    
for(int i = 0; i < 1024; i++){
    pte[i].p = 1;                    
    pte[i].rw = 1;                      // Establecemos que la página puede ser escrita.
    pte[i].us = 0;
    pte[i].pwt = 0;
    pte[i].pcd = 0;
    pte[i].a = 0;
    pte[i].d = 0;
    pte[i].pat= 0;
    pte[i].g = 0;
    pte[i].avl = 0;
    pte[i].base = i;  
}
    return 0;
}


//continuará... O NO?


void memcpy(unsigned int src, unsigned int dest, unsigned int len) {
  
    char* srcp = (char*)src;
    char* destp = (char*)dest;
    unsigned int i;
    for (i = 0; i < len; ++i) {
        destp[i] = srcp[i];
    }

}
