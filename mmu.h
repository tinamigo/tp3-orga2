/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "stdint.h"
#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"


void mmu_init();

void memcpy(unsigned int src, unsigned int dest, unsigned int len);

//uint32_t getCR3();

uint32_t mmu_nextFreeKernelPage(); 

uint32_t  mmu_initTaskDir(uint32_t jugador, uint16_t duplicando);     //Si el jugador es A, entonces jugador == 0 

uint32_t mmu_nextFreeTaskPage();

void mmu_mapPage(uint32_t virtual, uint32_t phy, uint32_t cr3, uint32_t attrs);

uint32_t mmu_unmapPage(uint32_t virtual, uint32_t cr3);

uint32_t mmu_initKernelDir();


typedef struct str_pdentry {
    uint8_t   p:1;
    uint8_t   rw:1;
    uint8_t   us:1;
    uint8_t   pwt:1;
    uint8_t   pcd:1;
    uint8_t   a:1;
    uint8_t   ign:1;
    uint8_t   ps:1;
    uint8_t   g:1;
    uint8_t   avl:3;
    uint32_t  base:20;     
} __attribute__((__packed__)) pdentry;

typedef struct str_ptentry {
    uint8_t   p:1;
    uint8_t   rw:1;
    uint8_t   us:1;
    uint8_t   pwt:1;
    uint8_t   pcd:1;
    uint8_t   a:1;
    uint8_t   d:1;
    uint8_t   pat:1;
    uint8_t   g:1;
    uint8_t   avl:3;
    uint32_t  base:20;     
} __attribute__((__packed__)) ptentry;

pdentry getNewPdtEntry();  
ptentry getNewPtEntry();  


extern uint32_t mmu_initKernelDir();

//extern uint32_t getCR3();



#endif	/* !__MMU_H__ */




