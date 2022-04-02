/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_initial;
tss tss_idle;

tss tss_tasks[NUMBER_MAX_TASK];


void tss_init() {
	tss_inicializar_gdt_entry(27, (unsigned int)&tss_initial);
}

void tss_inicializar_idle() {
//tss_idle.ptl = ;						//Previous Task Link
tss_idle.unused0 = 0x0000;				//Reserved
tss_idle.esp0 = KERNEL_STACK_BASE;		//Stack Pointer Level 0
tss_idle.ss0 = GDT_IDX_KERNEL_DATA<<3;	//SS0 Selector de segmento de datos nivel 0
tss_idle.unused1 = 0x0000;				//Reserved
tss_idle.esp1 = 0x00000000;				//Stack Pointer Level 1
tss_idle.ss1 = 0x0000;					//SS1
tss_idle.unused2 = 0x0000;				//Reserved
tss_idle.esp2 = 0x00000000;				//Stack Pointer Level 2
tss_idle.ss2 = 0x0000;					//SS2
tss_idle.unused3 = 0x0000;				//Reserved
tss_idle.cr3 = KERNEL_PAGE_DIR;			//Pila del kernel.
tss_idle.eip = 0x00014000; 				//Instruction Pointer Donde comeinza el area libre de tareas. O 0x14000 ???????????
tss_idle.eflags = 0x00000202;			//eFlags
tss_idle.eax=0;							
tss_idle.ecx=0;
tss_idle.edx=0;
tss_idle.ebx=0;
tss_idle.esp = KERNEL_STACK_BASE;
tss_idle.ebp = KERNEL_STACK_BASE;
tss_idle.esi=0;        
tss_idle.edi=0;
tss_idle.es = GDT_IDX_KERNEL_DATA<<3;
tss_idle.unused4 = 0x0000;				//Reserved
tss_idle.cs = GDT_IDX_KERNEL_CODE<<3 ;
tss_idle.unused5 = 0x0000;				//Reserved
tss_idle.ss = GDT_IDX_KERNEL_DATA<<3;
tss_idle.unused6 = 0x0000;				//Reserved
tss_idle.ds = GDT_IDX_KERNEL_DATA<<3;
tss_idle.unused7 = 0x0000;
tss_idle.fs = GDT_IDX_KERNEL_DATA<<3;
tss_idle.unused8 = 0x0000;				//Reserved
tss_idle.gs = GDT_IDX_KERNEL_DATA<<3;
tss_idle.unused9 = 0x0000;				//Reserved
tss_idle.ldt=0;							
tss_idle.unused10 = 0x0000;				//Reserved
tss_idle.dtrap = 0x0000;
tss_idle.iomap = 0xFFFF;

	//tss_tasks[1] = tss_idle;
	tss_inicializar_gdt_entry(28, (unsigned int)&tss_idle);

}



void tss_inicializar_tasks(uint16_t index, uint32_t gdt_entry, uint32_t jugador, uint16_t duplicando, uint32_t esp) {  //jugador es 0 si juega A, 1 si juega B ;)
/*
	unsigned int base;
	uint32_t cr3
	uint32_t jugador = JUGADOR_A;

	for (int index = GDT_TSS_A0 ; index < GDT_TSS_B0; index++){
*/
   // unsigned int base = (unsigned int) &tss_tasks[index];			//Direccion de la tarea indicada por el index.

    uint32_t free_page = mmu_nextFreeKernelPage(); // OJO!   

  //  tss_inicializar_gdt_entry(gdt_entry, base);

    uint32_t cr3 = mmu_initTaskDir(jugador, duplicando);

    
//	tss_tasks[index].ptl = ;					//Previous Task Link
	tss_tasks[index].unused0 = 0x0000;		//Reserved
	tss_tasks[index].esp0 = free_page + 0x1000;		//Stack Pointer Level 0
	tss_tasks[index].ss0 = GDT_IDX_KERNEL_DATA<<3;	//SS0
	tss_tasks[index].unused1 = 0x0000;				//Reserved
	tss_tasks[index].esp1 = 0x00000000;				//Stack Pointer Level 1
	tss_tasks[index].ss1 = 0x0000;					//SS1
	tss_tasks[index].unused2 = 0x0000;				//Reserved
	tss_tasks[index].esp2 = 0x00000000;				//Stack Pointer Level 2
	tss_tasks[index].ss2 = 0x0000;					//SS2
	tss_tasks[index].unused3 = 0x0000;				//Reserved
	
   	tss_tasks[index].cr3 = cr3;			//Dirección del directorio que pedí recién
	tss_tasks[index].eip = 0x8000000;// jugador == JUGADOR_A? 0x000010000 : 0x000012000;  //0x8000000
//Instruction Pointer Donde comeinza el codigo de  la tarea. O 0x10000 ???????????
	
    
	tss_tasks[index].eflags = 0x00000202;			//eFlags
/*
	tss_idle.eax;							
	tss_tasks[index].ecx;
	tss_tasks[index].edx;
	tss_tasks[index].ebx;
*/
	tss_tasks[index].esp = 0x8002000;
	tss_tasks[index].ebp = 0x8002000;
   

/*	tss_tasks[index].esi;        
	tss_tasks[index].edi;*/
	tss_tasks[index].es = GDT_IDX_USER_DATA<<3 | 3;							//
	tss_tasks[index].unused4 = 0x0000;				//Reserved
	tss_tasks[index].cs = GDT_IDX_USER_CODE<<3 | 3;
	tss_tasks[index].unused5 = 0x0000;				//Reserved
	tss_tasks[index].ss = GDT_IDX_USER_DATA<<3 | 3;
	tss_tasks[index].unused6 = 0x0000;				//Reserved
	tss_tasks[index].ds = GDT_IDX_USER_DATA<<3 | 3;
	tss_tasks[index].unused7 = 0x0000;
	tss_tasks[index].fs = GDT_IDX_USER_DATA<<3 | 3;
	tss_tasks[index].unused8 = 0x0000;				//Reserved
	tss_tasks[index].gs = GDT_IDX_USER_DATA<<3 | 3;
	tss_tasks[index].unused9 = 0x0000;				//Reserved
//	tss_tasks[index].ldt;							
	tss_tasks[index].unused10 = 0x0000;				//Reserved
	tss_tasks[index].dtrap = 0x0000;
	tss_tasks[index].iomap = 0xFFFF;

	if(duplicando){

		uint32_t* src = (uint32_t*) ((esp>>12)<<12);			// limpio el offset del ebp para obtener la pagina de la pila del kernel ant
		uint32_t* dst = (uint32_t*) free_page;				// el destino es la pagina q me pedi para la pila del kernel

		for (uint32_t i = 0; i < PAGE_SIZE/4; ++i){			// copio de una pila a otra
			*(dst+i)=*(src+i);
		}

		tss_tasks[index].esp0 = ((esp<<20)>>20) + free_page;
		tss_tasks[index].esp = ((esp<<20)>>20) + free_page;

	}


	tss_inicializar_gdt_entry(gdt_entry, (unsigned int)&tss_tasks[index]);


}


void tss_inicializar_gdt_entry(unsigned int index, unsigned int base) {
// Inicializamos el descriptor de la GDT de la tarea solicitada.
		gdt[index].limit_0_15 = 0x0067;
	    gdt[index].base_0_15 = base;// & 0xFFFF;
	    gdt[index].base_23_16 = (base >> 16);// & 0xFF;
	    gdt[index].type = 0x9; //1001
	    gdt[index].s = 0x0;
	    gdt[index].dpl = 0x0;
	    gdt[index].p = 0x1;
	    gdt[index].limit_16_19 = 0x0;
	    gdt[index].avl = 0x0;
	    gdt[index].l = 0x0;
	    gdt[index].db = 0x1;
	    gdt[index].g = 0x0;
	    gdt[index].base_31_24 = (base >> 24);


}