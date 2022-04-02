/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"
#include "tss.h"
#include "screen.h"
#include "colors.h"

uint16_t debug_mode;


void int_keyboard(uint32_t input ){
    if (input == 0x15){
        if (debug_mode == 0){
            debug_mode = 1;
            print((const char*)"M0D0 D38U6", 65, 5, C_FG_WHITE | C_BG_CYAN);
            //y print modo debug
        } else if (debug_mode == 1) {
            debug_mode = 0;

            print((const char*)"          ", 65, 5, C_FG_WHITE | C_BG_CYAN);
        } else if (debug_mode == 2){
            debug_mode = 1;
            //el juego va a retomar y la pantallita desaparece, por el funcionamiento de las int del reloj 
        }
    }
}


idt_entry idt[255] = { };

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:
*/


#define IDT_ENTRY(numero)                                                                          \
    idt[numero].offset_0_15 = (uint16_t) ((uint32_t)(&_isr ## numero) & (uint32_t) 0xFFFF);        \
    idt[numero].segsel = (uint16_t) GDT_IDX_KERNEL_CODE<<3;                                        \
    idt[numero].attr = (uint16_t) 0x8E00;                                                          \
    idt[numero].offset_16_31 = (uint16_t) ((uint32_t)(&_isr ## numero) >> 16 & (uint32_t) 0xFFFF); 


#define IDT_ENTRY3(numero)                                                                         \
    idt[numero].offset_0_15 = (uint16_t) ((uint32_t)(&_isr ## numero) & (uint32_t) 0xFFFF);        \
    idt[numero].segsel = (uint16_t) GDT_IDX_KERNEL_CODE<<3;                                          \
    idt[numero].attr = (uint16_t) 0xEE00;                                                          \
    idt[numero].offset_16_31 = (uint16_t) ((uint32_t)(&_isr ## numero) >> 16 & (uint32_t) 0xFFFF); 

    /*  
    1               ;P
    00              ;DPL(corroborar)
    0               ;S
    1               ;D
    110             ;TYPE (interrupción)
    000             ;CERO
    00000           ;RESERVED
    */
  
   /* void idt_inicializar() {

    }*/


void idt_init() {
    // Excepciones
    IDT_ENTRY(0);
    IDT_ENTRY(1);
    IDT_ENTRY(2);
    IDT_ENTRY(3);
    IDT_ENTRY(4);
    IDT_ENTRY(5);
    IDT_ENTRY(6);
    IDT_ENTRY(7);
    IDT_ENTRY(8);
    IDT_ENTRY(9);
    IDT_ENTRY(10);
    IDT_ENTRY(11);
    IDT_ENTRY(12);
    IDT_ENTRY(13);
    IDT_ENTRY(14);
    IDT_ENTRY(15);
    IDT_ENTRY(16);
    IDT_ENTRY(17);
    IDT_ENTRY(18);
    IDT_ENTRY(19);
    
    IDT_ENTRY(32);              //Clock.
    IDT_ENTRY(33);              //Teclado.
    IDT_ENTRY3(71);             //0x47 read  
    IDT_ENTRY3(73);             //0x49 move
    IDT_ENTRY3(76);             //0x4C divide

}

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (uint32_t) &idt
};
