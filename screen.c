/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "game.h"



void print_exception(uint32_t cr0, uint32_t cr2, uint32_t cr3, uint32_t cr4, uint16_t cs, uint16_t ds, uint16_t es, uint16_t fs, uint16_t gs,  uint32_t edi, uint32_t esi, uint32_t ebp, uint32_t esp0, uint32_t ebx, uint32_t edx, uint32_t ecx, uint32_t eax, uint32_t eip, uint32_t cs3, uint32_t eflags, uint32_t esp, uint32_t ss3) {


    


    print("                               ", 9, 3, 0x00);
    print("                              ", 9, 4,  0x70);
    print(" eax                          ", 9, 5,  0x70);
    print("               cr0            ", 9, 6,  0x70);
    print(" ebx                          ", 9, 7,  0x70);
    print("               cr2            ", 9, 8,  0x70);
    print(" ecx                          ", 9, 9,  0x70);
    print("               cr3            ", 9, 10,  0x70);
    print(" edx                          ", 9, 11,  0x70);
    print("               cr4            ", 9, 12,  0x70);
    print(" esi                          ", 9, 13,  0x70);
    print("                              ", 9, 14,  0x70);
    print(" edi                          ", 9, 15,  0x70);
    print("                              ", 9, 16,  0x70);
    print(" ebp                          ", 9, 17,  0x70);
    print("                              ", 9, 18,  0x70);
    print(" esp                          ", 9, 19,  0x70);
    print("                              ", 9, 20,  0x70);
    print(" eip                          ", 9, 21,  0x70);
    print("                              ", 9, 22,  0x70);
    print("  cs           pila           ", 9, 23,  0x70);
    print("                              ", 9, 24,  0x70);
    print("  ds                          ", 9, 25,  0x70);
    print("                              ", 9, 26,  0x70);
    print("  es                          ", 9, 27,  0x70);
    print("                              ", 9, 28,  0x70);
    print("  fs                          ", 9, 29,  0x70);
    print("                              ", 9, 30,  0x70);
    print("  gs                          ", 9, 31,  0x70);
    print("                              ", 9, 32,  0x70);
    print("                              ", 9, 33,  0x70);
    print("                              ", 9, 34,  0x70);
    print("                              ", 9, 35,  0x70);
    print("  eflags                      ", 9, 36,  0x70);
    print("                              ", 9, 37,  0x70);
    print("                              ", 9, 38, 0x0f);
   

    for (int i = 3; i < 39; ++i) {
        print(" ", 8, i, 0x00);
        print(" ", 39, i, 0x00); 
    }
    
    uint32_t *stack = (uint32_t*) esp0;

    // imprimir registros y pila
    print_hex(eax, 8, 14, 5,  0x7f); 
    print_hex(ebx, 8, 14, 7,  0x7f);                             
    print_hex(ecx, 8, 14, 9,  0x7f);        
    print_hex(edx, 8, 14, 11,  0x7f);       
    print_hex(esi, 8, 14, 13,  0x7f);
    print_hex(edi, 8, 14, 15,  0x7f);
    print_hex(ebp, 8, 14, 17,  0x7f);
    print_hex(esp0, 8, 14, 19,  0x7f);
    print_hex(eip, 8, 14, 21,  0x7f);
    print_hex(cs3, 4, 14, 23,  0x7f);        
    print_hex(ds, 4, 14, 25,  0x7f);       
    print_hex(es, 4, 14, 27,  0x7f);     
    print_hex(fs, 4, 14, 29,  0x7f);     
    print_hex(gs, 4, 14, 31,  0x7f);    

    print_hex(eflags, 8, 18, 36, 0x7f);

    print_hex(cr0, 8, 28,  6,  0x71);
    print_hex(cr2, 8, 28,  8,  0x71); 
    print_hex(cr3, 8,  28, 10,  0x71);
    print_hex(cr4, 8,  28, 12,  0x71);
    
    
    print_hex((uint32_t)(*stack), 8, 24, 26,  0x7f);   
    print_hex((uint32_t)(*(stack+1)), 8, 24, 27,  0x7f);
    print_hex((uint32_t)(*(stack+2)), 8, 24, 28,  0x7f);
    print_hex((uint32_t)(*(stack+3)), 8, 24, 29,  0x7f);   
    print_hex((uint32_t)(*(stack+4)), 8, 24, 30,  0x7f);   

}



void print(const char* text, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int32_t i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (uint8_t) text[i];
        p[y][x].a = (uint8_t) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_board(){
    //print((const char *)(tablero[1][1].valor), 1, 1, 0xDF);
    for (int i = 0; i < 50; ++i){
        for (int j = 0; j < 50; ++j){
            if (tablero[i][j].valor == '0'){
                screen_drawBox(j, i, 1, 1, ' ', C_FG_WHITE | C_BG_MAGENTA);
            }else{
                print( &(tablero[i][j].valor), i, j, C_FG_WHITE | C_BG_MAGENTA);
            }
        }
    }
    print_dec( scheduler.points_A, 10, 60, 15, C_FG_WHITE | C_BG_MAGENTA);
    print_dec( scheduler.points_B, 10, 60, 35, C_FG_WHITE | C_BG_MAGENTA);

    for (int i = 0; i < 10;  i++){ 
        if(scheduler.tasksA[i].state == MUERTA){
            print( "X" , 51+3*i , 17, C_FG_WHITE | C_BG_CYAN);
            print( "--" , 51+3*i , 19, C_FG_WHITE | C_BG_CYAN);
        
        } else {
            print( "O" , 51+3*i , 17, C_FG_WHITE | C_BG_CYAN);
            print_dec( scheduler.tasksA[i].weight, 2, 51+3*i, 19, C_FG_WHITE | C_BG_CYAN);
        }

    } 

    for (int i = 0; i < 10;  i++){ 
        if(scheduler.tasksB[i].state == MUERTA){
            print( "X" , 51+3*i , 37, C_FG_WHITE | C_BG_CYAN);
            print( "--" , 51+3*i , 39, C_FG_WHITE | C_BG_CYAN);
        
        } else {
            print( "O" , 51+3*i , 37, C_FG_WHITE | C_BG_CYAN);
            print_dec( scheduler.tasksB[i].weight, 2, 51+3*i, 39, C_FG_WHITE | C_BG_CYAN);
        }

    } 



    //return tablero[0][1].valor;
}

void print_dec(uint32_t numero, uint32_t size, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    uint32_t i;
    uint8_t letras[16] = "0123456789";

    for(i = 0; i < size; i++) {
        uint32_t resto  = numero % 10;
        numero = numero / 10;
        p[y][x + size - i - 1].c = letras[resto];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_hex(uint32_t numero, int32_t size, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int32_t i;
    uint8_t hexa[8];
    uint8_t letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void screen_drawBox(uint32_t fInit,
                    uint32_t cInit,
                    uint32_t fSize,
                    uint32_t cSize,
                    uint8_t character,
                    uint8_t attr ) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    uint32_t f;
    uint32_t c;
    for (f = fInit; f < fInit+fSize; f++) {
    for (c = cInit; c < cInit+cSize; c++) {
          p[f][c].c = character;
          p[f][c].a = attr;
    }}
}




