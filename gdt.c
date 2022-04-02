/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"
extern tss tss_initial;
extern tss tss_idle ;

//uint16_t tss_idle0 = (uint16_t) &tss_idle:16;

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (uint16_t)    0x0000,         /* limit[0:15]  */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x00,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x00,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x00,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },
/* Descriptores de codigo*/
    [GDT_IDX_KERNEL_CODE] = (gdt_entry) {
        (uint16_t)    0x8A63,         /* limit[0:15] X */ //1000 1010 0110 0011
        (uint16_t)    0x0000,         /* base[0:15]  X */
        (uint8_t)     0x00,           /* base[23:16] X */
        (uint8_t)     0x0A,           /* type X        */ 
        (uint8_t)     0x01,           /* s    X        */
        (uint8_t)     0x00,           /* dpl  X        */
        (uint8_t)     0x01,           /* p    X        */
        (uint8_t)     0x02,           /* limit[16:19] X*/  //0010
        (uint8_t)     0x00,           /* avl  X        */
        (uint8_t)     0x00,           /* l    X        */
        (uint8_t)     0x01,           /* db   X        */ 
        (uint8_t)     0x01,           /* g    x        */
        (uint8_t)     0x00,           /* base[31:24] X */
    },
    [GDT_IDX_USER_CODE] = (gdt_entry) {
        (uint16_t)    0x8A63,         /* limit[0:15] X */ //1000 1010 0110 0011
        (uint16_t)    0x0000,         /* base[0:15]  X */
        (uint8_t)     0x00,           /* base[23:16] X */
        (uint8_t)     0x0A,           /* type X        */ 
        (uint8_t)     0x01,           /* s    X        */
        (uint8_t)     0x03,           /* dpl  X        */
        (uint8_t)     0x01,           /* p    X        */
        (uint8_t)     0x02,           /* limit[16:19] X*/  //0010
        (uint8_t)     0x00,           /* avl  X        */
        (uint8_t)     0x00,           /* l    X        */
        (uint8_t)     0x01,           /* db   X        */
        (uint8_t)     0x01,           /* g    X        */
        (uint8_t)     0x00,           /* base[31:24] X */
    },
/* Descriptores de dato*/
     [GDT_IDX_KERNEL_DATA] = (gdt_entry) {
        (uint16_t)    0x8A63,         /* limit[0:15] X */ //1000 1010 0110 0011
        (uint16_t)    0x0000,         /* base[0:15]  X */
        (uint8_t)     0x00,           /* base[23:16] X */
        (uint8_t)     0x02,           /* type X        */
        (uint8_t)     0x01,           /* s    X        */
        (uint8_t)     0x00,           /* dpl  X        */
        (uint8_t)     0x01,           /* p    X        */
        (uint8_t)     0x02,           /* limit[16:19] X*/  //0010
        (uint8_t)     0x00,           /* avl  X        */
        (uint8_t)     0x00,           /* l    X        */
        (uint8_t)     0x01,           /* db   X        */
        (uint8_t)     0x01,           /* g    X        */
        (uint8_t)     0x00,           /* base[31:24] X */
    },
    [GDT_IDX_USER_DATA] = (gdt_entry) {
        (uint16_t)    0x8A63,         /* limit[0:15] X */ //1000 1010 0110 0011
        (uint16_t)    0x0000,         /* base[0:15]  X */
        (uint8_t)     0x00,           /* base[23:16] X */
        (uint8_t)     0x02,           /* type X        */
        (uint8_t)     0x01,           /* s    X        */
        (uint8_t)     0x03,           /* dpl  X        */
        (uint8_t)     0x01,           /* p    X        */
        (uint8_t)     0x02,           /* limit[16:19] X*/  //0010
        (uint8_t)     0x00,           /* avl  X        */
        (uint8_t)     0x00,           /* l    X        */
        (uint8_t)     0x01,           /* db   X        */
        (uint8_t)     0x01,           /* g    X        */
        (uint8_t)     0x00,           /* base[31:24] X */
    },

    [GDT_IDX_VIDEO] = (gdt_entry) {
        (uint16_t)    0x1F3F,         /* limit[0:15] X */
        (uint16_t)    0x0000,         /* base[0:15]  X */
        (uint8_t)     0x00,           /* base[23:16] X */
        (uint8_t)     0x02,           /* type        X */
        (uint8_t)     0x01,           /* s           X */
        (uint8_t)     0x00,           /* dpl         X */
        (uint8_t)     0x01,           /* p           X */
        (uint8_t)     0x00,           /* limit[16:19]X */
        (uint8_t)     0x00,           /* avl         X */
        (uint8_t)     0x00,           /* l           X */
        (uint8_t)     0x01,           /* db          X */
        (uint8_t)     0x00,           /* g           X */
        (uint8_t)     0xB8,           /* base[31:24] X */
    }, 

   
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (uint32_t) &gdt
};
