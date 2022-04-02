/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80

#include "stdint.h"
#include "colors.h"
#include "defines.h"


/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    uint8_t c;
    uint8_t a;
} ca;

void print(const char* text, uint32_t x, uint32_t y, uint16_t attr);
void print_dec(uint32_t numero, uint32_t size, uint32_t x, uint32_t y, uint16_t attr);
void print_hex(uint32_t numero, int size, uint32_t x, uint32_t y, uint16_t attr);

void screen_drawBox(uint32_t fInit, uint32_t cInit,
                    uint32_t fSize, uint32_t cSize,
                    uint8_t character, uint8_t attr );
void print_board();

extern void print_exception(uint32_t cr0, uint32_t cr2, uint32_t cr3, uint32_t cr4, uint16_t cs, uint16_t ds, uint16_t es, uint16_t fs, uint16_t gs, uint32_t edi, uint32_t esi, uint32_t ebp, uint32_t esp0, uint32_t ebx, uint32_t edx, uint32_t ecx, uint32_t eax, uint32_t eip, uint32_t cs3, uint32_t eflags, uint32_t esp, uint32_t ss3);

#endif  /* !__SCREEN_H__ */
