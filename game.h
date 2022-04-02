/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "stdint.h"
#include "defines.h"
#include "screen.h"
#include "mmu.h"
#include "sched.h"
//#include <vector>

//using namespace std; 
//#include "cmath"
//#include "cstdlib"


typedef enum e_direction {
    Right = 1,
    Left = 2,
    Up = 3,
    Down = 4,
} e_direction_t;

typedef enum e_datatype {
    Null = 0, // no llega a ver que hay
    None = 10,
    Player = 20,
    Opponent = 30,
    Food = 40,
    Excess = 50,
} e_datatype_t;

typedef struct celda_t {
	char valor;
	int pesoA;
	int pesoB;
    //int total_task_A[10];
    //int total_task_B[10];
    //std::vector<int> total_task_A;
    //std::vector<int> total_task_B;
} __attribute__((__packed__)) celda;



extern celda tablero[50][50];

int16_t read(int32_t y, int32_t x);

int16_t move(uint32_t dir, uint32_t distance);

int divider(uint32_t eip, uint32_t esp, uint32_t esp0, uint32_t esp1, uint32_t esp2, uint32_t esp3, uint32_t esp4, uint32_t esp5, uint32_t esp6, uint32_t esp7, uint16_t ss, uint32_t xxx, uint32_t flags, uint16_t cs);

//void duplicar (uint16_t indice_tss_array, uint32_t indice_tss_vieja, uint32_t jugador);

void game_init();

void game_nextStep();


uint16_t dame_max_dist(uint16_t peso);

#endif  /* !__GAME_H__ */
