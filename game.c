/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include <stdlib.h>
#include "screen.h"
#include "sched.h"

		
celda tablero[50][50];

void game_init() {
	//*(tablero[0][0].valor) = '0';
	//*(tablero[20][20].valor) = '0';

	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			tablero[i][j].valor = '0';
			//print((const char *)(tablero[i][j].valor), i, j, 0xDF);
			tablero[i][j].pesoA = 0;
			tablero[i][j].pesoB = 0;
			//tablero[i][j].total_task_A;
			//tablero[i][j].total_task_B;	
		}
	}

	tablero[5][4].valor = 'F';
	tablero[1][25].valor = 'F';
	tablero[46][3].valor = 'F';
	tablero[20][3].valor = 'U';
	tablero[19][34].valor = 'U';
	tablero[2][11].valor = 'U';
	tablero[13][18].valor = 'U';
	tablero[22][48].valor = 'P';
	tablero[7][26].valor = 'P';
	tablero[24][37].valor = 'P';
	tablero[19][19].valor = 'P';
	tablero[6][39].valor = 'P';
	tablero[39][2].valor = 'P';
	tablero[43][38].valor = 'P';
	tablero[35][42].valor = 'U';

	tablero[0][0].valor = 'A';
	tablero[0][0].pesoA = 64;
	tablero[0][0].pesoB =  0;
	
	tablero[0][49].valor = 'B';
	tablero[0][49].pesoA =  0;
	tablero[0][49].pesoB = 64;

	/*
	for (int i = 0; i < 5; ++i){
		int x = 10;//random() % 50;
		int y = 1;//random() % 50;

		*(tablero[x][y].valor) = 'F';
		tablero[x][y].pesoA = 0;
		tablero[x][y].pesoB = 0;
	}*/
	/*for (int i = 0; i < 5; ++i){
		int x = 41;//random() % 50;
		int y = 2;//random() % 50;

		*(tablero[x][y].valor) = 'P';
		tablero[x][y].pesoA = 0;
		tablero[x][y].pesoB = 0;
	}	
	for (int i = 0; i < 5; ++i){
		int x = 2;//random() % 50;
		int y = 23;//random() % 50;

		*(tablero[x][y].valor) = 'U';
		tablero[x][y].pesoA = 0;
		tablero[x][y].pesoB = 0;
	}

*/

}

void game_nextStep() {
}



int16_t read(int32_t y, int32_t x){

	int32_t distanciaRelativa = abs(x) + abs(y); 

	uint16_t i = 0;
	uint16_t j = 0;

	
if(scheduler.taskA){
		i = scheduler.tasksA[scheduler.current_taskA].x;
		j = scheduler.tasksA[scheduler.current_taskA].y;
	} else {
		i = scheduler.tasksB[scheduler.current_taskB].x;
		j = scheduler.tasksB[scheduler.current_taskB].y;
	}
//return tablero[25][25].valor;
	uint16_t peso = 0;
	if(scheduler.taskA){
		peso = scheduler.tasksA[scheduler.current_taskA].weight;

	}else{
		peso = scheduler.tasksB[scheduler.current_taskB].weight;
	}

	if(distanciaRelativa > peso){
		return Null;    //Asumimos que las lecturas que no se pueden realizar no suman cantidad de lecturas  
	}
	uint32_t pos_x = i+x;
	uint32_t pos_y = j+y;

	if(scheduler.taskA){
		scheduler.tasksA[scheduler.current_taskA].readings ++;
		if (scheduler.tasksA[scheduler.current_taskA].readings > peso) return Excess;
	} else {
		scheduler.tasksB[scheduler.current_taskB].readings ++;
		if (scheduler.tasksB[scheduler.current_taskB].readings > peso) return Excess;
	}

	if(tablero[pos_x][pos_y].valor == '0'){
		return None;
	} else if (tablero[pos_x][pos_y].valor == 'F' || tablero[pos_x][pos_y].valor == 'P' || tablero[pos_x][pos_y].valor == 'U') {
		return Food;
	} else if (tablero[pos_x][pos_y].valor == 'A') {
		if(scheduler.taskA){
			return Player;
		}else{
			return Opponent;
		}
	}else if (tablero[pos_x][pos_y].valor == 'B') {
		if(!scheduler.taskA){
			return Player;
		}else{
			return Opponent;
		}
	}
	return 0xCACA;
	
}

//----------------------------------------MOVE----------------------------------------------
int16_t move(uint32_t dir, uint32_t distance){
	dir &= 0xF;
	//breakpoint();
	uint16_t peso = scheduler.taskA? scheduler.tasksA[scheduler.current_taskA].weight
					: scheduler.tasksB[scheduler.current_taskB].weight;

	distance = min(distance, dame_max_dist(peso));
	uint16_t tarea_actual = scheduler.taskA? scheduler.current_taskA : scheduler.current_taskB;
	sched_task* tareas = scheduler.taskA? scheduler.tasksA : scheduler.tasksB;
	sched_task *ta = &(tareas[tarea_actual]);

	if(scheduler.taskA){

		if(dir == Right ){
			tablero[ta->x][ta->y].pesoA -= peso;
			ta->x = (ta->x + distance) % 50;
			tablero[ta->x][ta->y].pesoA += peso;
		} else if(dir == Left ){
			tablero[ta->x][ta->y].pesoA -= peso;
			ta->x = (ta->x - distance) % 50;
			tablero[ta->x][ta->y].pesoA += peso;
		} else if(dir == Up){
			tablero[ta->x][ta->y].pesoA -= peso;
			ta->y = (ta->y - distance) % 50;
			tablero[ta->x][ta->y].pesoA += peso;
		} else if(dir == Down ){
			tablero[ta->x][ta->y].pesoA -= peso;
			ta->y = (ta->y + distance) % 50;
			tablero[ta->x][ta->y].pesoA += peso;
		}
	} else {
		if(dir == Right ){
			tablero[ta->x][ta->y].pesoB -= peso;
			ta->x = (ta->x + distance) % 50;
			tablero[ta->x][ta->y].pesoB += peso;
		} else if(dir == Left ){
			tablero[ta->x][ta->y].pesoB -= peso;
			ta->x = (ta->x - distance) % 50;
			tablero[ta->x][ta->y].pesoB += peso;
		} else if(dir == Up){
			tablero[ta->x][ta->y].pesoB -= peso;
			ta->y = (ta->y - distance) % 50;
			tablero[ta->x][ta->y].pesoB += peso;
		} else if(dir == Down ){
			tablero[ta->x][ta->y].pesoB -= peso;
			ta->y = (ta->y + distance) % 50;
			tablero[ta->x][ta->y].pesoB += peso;
		}
	//	breakpoint();
	}

return distance;
}

                                                                                                                                                        //xxx es el esp de nivel 3 que no nos sirve                             
int divider(uint32_t eip, uint32_t esp, uint32_t esp0, uint32_t esp1, uint32_t esp2, uint32_t esp3, uint32_t esp4, uint32_t esp5, uint32_t esp6, uint32_t esp7, uint16_t ss, uint32_t xxx, uint32_t flags, uint16_t cs){
	uint32_t indiceGDT = 0;                                                                                                                                                                                        
//	uint32_t tss_deLaTareaADividir;

	if(scheduler.taskA){
		uint16_t i = 0;
		while( i<10 && scheduler.tasksA[i].state != MUERTA){
			i++;
		}
		if (i==10){
			return  -1;
		}else{ //Encontramos una menor a 10 y que esta muerta.
			indiceGDT = scheduler.tasksA[i].tss_selector>>3;
		}

		if (scheduler.tasksA[scheduler.current_taskA].weight == 1 ){
			return  -1;
		}

		scheduler.tasksA[scheduler.current_taskA].weight = scheduler.tasksA[scheduler.current_taskA].weight/2; 
		// Pedimos el tss_selector de la tarea a dividir.
		//tss_deLaTareaADividir = scheduler.tasksA[scheduler.current_taskA].tss_selector;
		// Duplico la tss.
		tss_inicializar_tasks(indiceGDT - 29, indiceGDT, JUGADOR_A, DUPLICANDO, esp);
//		duplicar(indiceGDT - 29, (tss_deLaTareaADividir>>3) -29, JUGADOR_A);

		tss_tasks[indiceGDT - 29].edi = esp0;
		tss_tasks[indiceGDT - 29].esi = esp1;
		tss_tasks[indiceGDT - 29].ebp = esp2;
		tss_tasks[indiceGDT - 29].ebx = esp4;
		tss_tasks[indiceGDT - 29].edx = esp5;
		tss_tasks[indiceGDT - 29].ecx = esp6;
		tss_tasks[indiceGDT - 29].eax = 1;
		tss_tasks[indiceGDT - 29].eip = eip;
		tss_tasks[indiceGDT - 29].cs = 0xb0;//cs;
		tss_tasks[indiceGDT - 29].eflags = 0x2;
		//tss_tasks[indiceGDT - 29].esp = esp;
		tss_tasks[indiceGDT - 29].ss = 0xc0;



		scheduler.tasksA[i].tss_selector = (indiceGDT)<<3;
		scheduler.tasksA[i].state = FETO;
		scheduler.tasksA[i].weight = scheduler.tasksA[scheduler.current_taskA].weight; 
		scheduler.tasksA[i].readings = 0;
		scheduler.tasksA[i].x = scheduler.tasksA[scheduler.current_taskA].x;
		scheduler.tasksA[i].y = scheduler.tasksA[scheduler.current_taskA].y;

	}else{
		uint16_t i = 0;
		while( i<10 && scheduler.tasksB[i].state != MUERTA){
			i++;
		}
		if (i==10){
			return  -1;
		}else{
			indiceGDT = scheduler.tasksB[i].tss_selector>>3;
		}

		if (scheduler.tasksB[scheduler.current_taskB].weight == 1 ){
			return  -1;
		}

		scheduler.tasksB[scheduler.current_taskB].weight = scheduler.tasksB[scheduler.current_taskB].weight/2; 

		// Pedimos el tss_selector de la tarea a dividir.
		//tss_deLaTareaADividir = scheduler.tasksB[scheduler.current_taskB].tss_selector;
		// Duplico la tss.
		tss_inicializar_tasks(indiceGDT - 29, indiceGDT, JUGADOR_B, DUPLICANDO, esp);
		//duplicar(indiceGDT - 29, (tss_deLaTareaADividir>>3) -29, JUGADOR_B);

		tss_tasks[indiceGDT - 29].edi = esp0;
		tss_tasks[indiceGDT - 29].esi = esp1;
		tss_tasks[indiceGDT - 29].ebp = esp2;
		tss_tasks[indiceGDT - 29].ebx = esp4;
		tss_tasks[indiceGDT - 29].edx = esp5;
		tss_tasks[indiceGDT - 29].ecx = esp6;
		tss_tasks[indiceGDT - 29].eax = 1;
		tss_tasks[indiceGDT - 29].eip = eip;
		tss_tasks[indiceGDT - 29].cs = 0xb0;//cs;
		tss_tasks[indiceGDT - 29].eflags = 0x2;
		//tss_tasks[indiceGDT - 29].esp = esp;
		tss_tasks[indiceGDT - 29].ss = 0xc0;;

		scheduler.tasksB[i].tss_selector = (indiceGDT)<<3;
		scheduler.tasksB[i].state = FETO;
		scheduler.tasksB[i].weight = scheduler.tasksB[scheduler.current_taskB].weight; 
		scheduler.tasksB[i].readings = 0;
		scheduler.tasksB[i].x = scheduler.tasksB[scheduler.current_taskB].x;
		scheduler.tasksB[i].y = scheduler.tasksB[scheduler.current_taskB].y;

	
	}
	return 0;
}


uint16_t dame_max_dist(uint16_t peso){
	uint16_t max_dist;
	switch(peso){
	case 64:
		max_dist = 1;
		break;
	case 32:
		max_dist = 2;
		break;
	case 16:
		max_dist = 4;
		break;
	case 8:
		max_dist = 8;
		break;
	case 4:
		max_dist = 16;
		break;
	case 2:
		max_dist = 32;
		break;	
	case 1:
		max_dist = 64;
		break;	

	default:
		return 0xCACA;
		break;
	}
	return max_dist;
}