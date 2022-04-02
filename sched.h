/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "stdint.h"
#include "screen.h"
#include "tss.h"
#include <stdbool.h>
#include "game.h"


typedef struct sched_task { //cada tarea
    uint32_t tss_selector;  //Selector de segmento de la tss de la tarea
    uint16_t state; //0-muerto ; 1-sin cosas para hacer ; 2-con cosas para hacer
    uint16_t weight;
    uint16_t readings;
    uint16_t x;
    uint16_t y;

} __attribute__((__packed__)) sched_task;

typedef struct sched_t { //arreglo de tareas + tarea actual
    uint16_t current_taskA;
    uint16_t current_taskB;
    uint32_t points_A;
    uint32_t points_B;
    uint16_t index_last_aliveA;     
    uint16_t index_last_aliveB;
    bool taskA;
    sched_task tasksA[10];
    sched_task tasksB[10];
} __attribute__((__packed__)) sched_t;



void matarTareas(bool current_task_is_A, uint16_t x, uint16_t y);

void meMuevoEnX(uint16_t cantDeCasilleros, uint16_t dir, bool current_task_is_A, uint16_t peso);

void modificarEstadoDelTablero(bool current_task_is_A, uint16_t x, uint16_t y);

void meMuevoEnY(uint16_t cantDeCasilleros, uint16_t dir, bool current_task_is_A, uint16_t peso);

//No le gusta el & delante de celda, pero si no lo pongo no se modifica el valor celda, asi que corroborar esto.
void chequeoDeEstarDentroDelTab(uint32_t celda); 

void terminar_juego();

void recorrerAndModificarTab();

extern void desalojar();

extern sched_t scheduler;
extern int32_t abs(int32_t n);
extern void sched_init();
extern int16_t sched_nextTask();
//extern int16_t read(int32_t x, int32_t y);
//extern int16_t move(e_direction_t dir, uint32_t distance);
//extern int16_t move(uint16_t dir, uint32_t distance);

extern void terminar_turno();                                
extern int16_t primera_viva();

//extern int divider(uint32_t esp0, uint32_t esp1, uint32_t esp2, uint32_t esp3, uint32_t esp4, uint32_t esp5, uint32_t esp6, uint32_t esp7, uint32_t eip);

#endif	/* !__SCHED_H__ */
