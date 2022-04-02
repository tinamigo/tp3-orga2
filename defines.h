/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define min(x,y) (x<y)?(x):(y) 

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1
#define GANO_A					1
#define GANO_B					0
/* Atributos paginas */
/* -------------------------------------------------------------------------- */
#define PAG_P                   0x00000001
#define PAG_R                   0x00000000
#define PAG_RW                  0x00000002
#define PAG_S                   0x00000000
#define PAG_US                  0x00000004
#define CONST_USER				1
#define CONST_WRITE				1

/* Misc */
/* -------------------------------------------------------------------------- */
#define NUMBER_MAX_TASK			20
#define SIZE_N                  50
#define SIZE_M                  50
#define PAGE_SIZE 			  	0X1000
#define ATTR 					3   //0000000000000000000000000000011 ; PRESENT SUPER
#define JUGADOR_A				0
#define JUGADOR_B				1
#define DUPLICANDO				1
#define INICIALIZANDO			0


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 50

#define GDT_IDX_NULL_DESC           0

#define GDT_IDX_KERNEL_CODE      	22
#define GDT_IDX_USER_CODE    		23
#define GDT_IDX_KERNEL_DATA     	24
#define GDT_IDX_USER_DATA     		25
#define GDT_IDX_VIDEO		        26
#define GDT_IDX_TSS_INIT			27
#define GDT_IDX_TSS_IDLE			28
#define GDT_IDX_TSS_A0				29
#define GDT_IDX_TSS_A1				30
#define GDT_IDX_TSS_A2				31
#define GDT_IDX_TSS_A3				32
#define GDT_IDX_TSS_A4				33
#define GDT_IDX_TSS_A5				34
#define GDT_IDX_TSS_A6				35
#define GDT_IDX_TSS_A7				36
#define GDT_IDX_TSS_A8				37
#define GDT_IDX_TSS_A9				38
#define GDT_IDX_TSS_B0				39
#define GDT_IDX_TSS_B1				40
#define GDT_IDX_TSS_B2				41
#define GDT_IDX_TSS_B3				42
#define GDT_IDX_TSS_B4				43
#define GDT_IDX_TSS_B5				44
#define GDT_IDX_TSS_B6				45
#define GDT_IDX_TSS_B7				46
#define GDT_IDX_TSS_B8				47
#define GDT_IDX_TSS_B9				48



/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC << 3)
#define OFFSET_GDT_ADDRESS 16

/* Selectores de segmentos */
/* -------------------------------------------------------------------------- */

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define BOOTSECTOR               0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                   0x00001200 /* direccion fisica de comienzo del kernel */
#define VIDEO                    0x000B8000 /* direccion fisica del buffer de video */
#define FIRST_FREE_KERNEL_PAGE   0x100000
#define FIRST_FREE_TASK_PAGE   	 0x400000
/* Direcciones virtuales de código, pila y datos */
/* -------------------------------------------------------------------------- */
#define TASK_CODE             0x08000000 /* direccion virtual del codigo */

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */
#define TASK_IDLE_CODE_SRC_ADDR  0x00014000

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
#define KERNEL_PAGE_DIR          0x00027000
#define KERNEL_PAGE_TABLE_0      0x00028000
#define KERNEL_STACK_BASE        0x00027000




/* Estados de una tarea*/
/* -------------------------------------------------------------------------- */
#define MUERTA 0
#define FETO 1
#define VIVA_POR_EJECUTAR 2
#define VIVA_EJECUTADA 3
#define MORIBUNDA 4



#endif  /* !__DEFINES_H__ */
