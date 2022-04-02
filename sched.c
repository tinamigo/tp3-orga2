/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "screen.h"
#include "game.h"

bool primera_tarea;
sched_t scheduler;

void sched_init() {
	primera_tarea =  false;
	scheduler.current_taskA = 0;
	scheduler.current_taskB = 0;
	scheduler.taskA = false;  //(la "ultima que corrimos" NO fue A, entonces arranco con A)
    scheduler.points_A = 0; 
    scheduler.points_B = 0; 

	scheduler.tasksA[0].tss_selector = (29<<3);
	scheduler.tasksA[0].state = VIVA_POR_EJECUTAR;
	for (int i = 1; i < 10; ++i){
		scheduler.tasksA[i].state = MUERTA;
		scheduler.tasksB[i].state = MUERTA;
		scheduler.tasksA[i].tss_selector = ((29 + i)<<3);
		scheduler.tasksB[i].tss_selector = ((39 + i)<<3);
 		scheduler.tasksA[i].readings = 0;
    	scheduler.tasksB[i].readings = 0;
    	scheduler.tasksA[i].weight = 0;
    	scheduler.tasksB[i].weight = 0;
 
	}

    scheduler.tasksA[0].weight = 64;
    scheduler.tasksA[0].readings = 0;
    scheduler.tasksA[0].x = 0;
    scheduler.tasksA[0].y = 0;
    tss_inicializar_tasks(0,29,JUGADOR_A,INICIALIZANDO,0);

	scheduler.tasksB[0].tss_selector = (39<<3);
	scheduler.tasksB[0].state = VIVA_POR_EJECUTAR;
    scheduler.tasksB[0].weight = 64;
    scheduler.tasksB[0].readings = 0;
    scheduler.tasksB[0].x = 0;
    scheduler.tasksB[0].y = 49;
    tss_inicializar_tasks(10,39,JUGADOR_B,INICIALIZANDO,0);
}

int16_t sched_nextTask() {

	if(primera_tarea){
		scheduler.taskA = true;
		int16_t first = primera_viva();
		scheduler.tasksA[first].state = VIVA_EJECUTADA;
		primera_tarea = false;  
		return scheduler.tasksA[first].tss_selector;
	}

	if(scheduler.taskA){    // La ultima tarea corrida fue de A.
		while(scheduler.tasksB[scheduler.current_taskB].state != VIVA_POR_EJECUTAR && scheduler.current_taskB < 10 ){
			scheduler.current_taskB++;	
		}
		if (scheduler.current_taskB != 10){  //si no encontre ninguna viva por ejecutar de B
			scheduler.taskA = false;
			scheduler.tasksB[scheduler.current_taskB].state = VIVA_EJECUTADA;
			return scheduler.tasksB[scheduler.current_taskB].tss_selector; 
		}	
	//swapear a y b en los comentarios de abajo	
	} 
	while(scheduler.tasksA[scheduler.current_taskA].state != VIVA_POR_EJECUTAR && scheduler.current_taskA < 10 ){
		scheduler.current_taskA++;	
	}
	if (scheduler.current_taskA != 10){  //si no encontre ninguna viva por ejecutar de B
		scheduler.taskA = true;
		scheduler.tasksA[scheduler.current_taskA].state = VIVA_EJECUTADA;
		return scheduler.tasksA[scheduler.current_taskA].tss_selector; 
	}
	while(scheduler.tasksB[scheduler.current_taskB].state != VIVA_POR_EJECUTAR && scheduler.current_taskB < 10){  //busco viva por ejecutar de A
		scheduler.current_taskB++;	
	}
	if(scheduler.current_taskB != 10){  //si tampoco habia vivas por ejecutar de A
		scheduler.taskA = false;
		scheduler.tasksB[scheduler.current_taskB].state = VIVA_EJECUTADA;
		return scheduler.tasksB[scheduler.current_taskB].tss_selector; 
	}
	terminar_turno();
/*	
	scheduler.taskA = true;
	int16_t first = primera_viva();
	scheduler.tasksA[first].state = VIVA_EJECUTADA;  
	return scheduler.tasksA[first].tss_selector;
*/
	return GDT_IDX_TSS_IDLE<<3 ;
	 // idle 11100000b

}

void terminar_turno(){
	// Actualizamos los estados de todas las tareas.
	for (int i = 0; i < 10; ++i){
		if( (scheduler.tasksA[i].state == FETO) || (scheduler.tasksA[i].state == VIVA_EJECUTADA)){
			scheduler.tasksA[i].state = VIVA_POR_EJECUTAR;
		}else if(scheduler.tasksA[i].state == MORIBUNDA){
			scheduler.tasksA[i].state = MUERTA;
			scheduler.tasksA[i].weight = 0;
		}
	}
	for (int i = 0; i < 10; ++i){
		if( (scheduler.tasksB[i].state == FETO) || (scheduler.tasksB[i].state == VIVA_EJECUTADA)){
			scheduler.tasksB[i].state = VIVA_POR_EJECUTAR;
		}else if(scheduler.tasksB[i].state == MORIBUNDA){
			scheduler.tasksB[i].state = MUERTA;
			scheduler.tasksB[i].weight = 0;
		}
	}
	// Actualizamos la tarea actual de A, que va a ser la primera viva literalmente.
	scheduler.current_taskA = primera_viva();
	int i = 0;
 
	// Es igual a lo que nos arroja  primera_viva() pero en este caso es de B.
	while(i<10){
		if(scheduler.tasksB[i].state == VIVA_POR_EJECUTAR){
			scheduler.current_taskB = i;                     //pongo la actual de B en la primera viva de B y salgo del while
			i = 50;
		}else{
			i++;
		}
	}

	if (i == 10 || scheduler.current_taskA == 10) {
		terminar_juego();
		primera_tarea = false;
	} else {
		primera_tarea = true;
		recorrerAndModificarTab();
		print_board();
	}
	for (int i = 0; i < 10; ++i){
		scheduler.tasksA[i].readings = 0;
		scheduler.tasksB[i].readings = 0;
	}
	

}     
// Devuelvo el indice mas chico de la tarea viva de A a ejecutar.
int16_t primera_viva(){
	int i = 0;
	while(i<10){
		if(scheduler.tasksA[i].state == VIVA_POR_EJECUTAR){
			return i;
		}else{
			 i++;
		}
	}
	if (i == 10){
		terminar_juego();
		primera_tarea = false;
	}
	return i;
}

void recorrerAndModificarTab(){
	// Esta funcion lo que hace es sumar los puntos a cada tarea, si habia frutas y muchos o un jugador de una misma tarea
	// la suma una sola vez y en el casod e que haya tareas del A y del B deside quien muere y quien vive y quien se queda con 
	// la fruta.  :O
	bool hay_frula = false;
	for (uint16_t i = 0; i < 50; i++){
		for (uint16_t j = 0; j < 50; j++){
			int peso_A = tablero[i][j].pesoA;
			int peso_B = tablero[i][j].pesoB;
			hay_frula = hay_frula || (tablero[i][j].valor) == 'F'; 
			hay_frula = hay_frula || (tablero[i][j].valor) == 'P';
			hay_frula = hay_frula || (tablero[i][j].valor) == 'U';
			if(peso_A != 0 && peso_B  != 0){  //entonces hay un conflicto (hay A y B)
				if(peso_A > peso_B){
					// Estamos en el caso en el que A gano.
					scheduler.points_A += peso_B;
					modificarEstadoDelTablero(GANO_A, i, j);
					// Para la proxima pasada ya no pueden correr las de B.
					matarTareas(GANO_A, i ,j);
					tablero[i][j].pesoB = 0;


				}else{
					// Estamos en el caso en el que B gano.
					scheduler.points_B = scheduler.points_B + tablero[i][j].pesoA;
					modificarEstadoDelTablero(GANO_B, i, j);
					// Para la proxima pasada ya no pueden correr las de A.
					matarTareas(GANO_B, i, j);
					tablero[i][j].pesoA = 0;

				}
			}else{
				// En este caso puede que haya una o mas tareas de B en la misma casilla.
				if(peso_B != 0 ){
					modificarEstadoDelTablero(GANO_B, i, j);
				} else if (peso_A != 0 ){
					modificarEstadoDelTablero(GANO_A, i, j);
				} else if ((tablero[i][j].valor) == 'A' || (tablero[i][j].valor) == 'B'){
					(tablero[i][j].valor) = '0';
				}
			}
		}
	}
	if (!hay_frula){
		terminar_juego();
		primera_tarea = false;
	}
}




//Recorda que si hay mas de una tarea vas a tener que restar, eso es horrible. Ver como solucionarlo.
void modificarEstadoDelTablero(bool winner_task_is_A, uint16_t x, uint16_t y){
	char estadoDeLaCelda;
	estadoDeLaCelda = (tablero[x][y].valor);
	
	switch(estadoDeLaCelda){
	case '0':
		break;
	case 'F':
		if(winner_task_is_A){
			scheduler.points_A = scheduler.points_A + 64;
		}else{
			scheduler.points_B = scheduler.points_B + 64;
		}
		
		break;
	case 'P':
		if(winner_task_is_A){
			scheduler.points_A = scheduler.points_A + 32;
		}else{
			scheduler.points_B = scheduler.points_B + 32;
		}
		
		break;
	case 'U':
		if(winner_task_is_A){
			scheduler.points_A = scheduler.points_A + 16;
		}else{
			scheduler.points_B = scheduler.points_B + 16;
		}
				
		break;
	}
	if (winner_task_is_A){
		(tablero[x][y].valor) = 'A';
	} else {
		(tablero[x][y].valor) = 'B';
	}
}

void chequeoDeEstarDentroDelTab(uint32_t celda){
	// Mis valores de celdas van siempre entre 0 y 50, lo que puede pasar es que de la vuelta al tablero, entonces tengo
	// que  modificar el valor de la celda por uno valido. 
	while(0 > celda || celda > 50){
		if(celda < 0){
			celda = celda + 50;
		}else {
			celda = celda - 50;

		}
	}
}

void matarTareas(bool winner_task_is_A, uint16_t x, uint16_t y){
	// Esta funcion va a matar las tareas de A o de B segudn lo indique winner_task_is_A, de la celda tablero[x][y].
	if(winner_task_is_A){
		for (int i = 0; i < 10; ++i){
			if(scheduler.tasksB[i].x == x && scheduler.tasksB[i].y == y){
				scheduler.tasksB[i].state = MUERTA;
				scheduler.tasksB[i].weight = 0;

				//gdt[scheduler.tasksB[i].tss_selector>>12].p = 0;
			}
		}
	}else {
		for (int i = 0; i < 10; ++i){
			if(scheduler.tasksA[i].x == x && scheduler.tasksA[i].y == y){
				scheduler.tasksA[i].state = MUERTA;
				scheduler.tasksA[i].weight = 0;

				//gdt[scheduler.tasksA[i].tss_selector>>12].p = 0;
			}
		}
	}
}

void desalojar(){
	if(scheduler.taskA){
		scheduler.tasksA[scheduler.current_taskA].state = MORIBUNDA;
		tablero[scheduler.tasksA[scheduler.current_taskA].x][scheduler.tasksA[scheduler.current_taskA].y].pesoA -= scheduler.tasksA[scheduler.current_taskA].weight;
	}else{
		scheduler.tasksB[scheduler.current_taskB].state = MORIBUNDA;
		tablero[scheduler.tasksB[scheduler.current_taskB].x][scheduler.tasksB[scheduler.current_taskB].y].pesoB -= scheduler.tasksB[scheduler.current_taskB].weight;		
	}
}

void terminar_juego(){
	for (int i = 0; i < 10; ++i)	{
		//gdt[i].p = 0;
		scheduler.tasksA[i].state = MUERTA;	
		scheduler.tasksB[i].state = MUERTA;

	}
	bool gano_a = scheduler.points_A>scheduler.points_B;
	screen_drawBox(0, 0, 50, 80, ' ', C_FG_WHITE | C_BG_RED); 
	if(gano_a){
		print((const char*) "FELICITACIONES A. B SOS UNX GILX", 20, 25, C_FG_LIGHT_BROWN | C_BG_RED);
	} else {
		print((const char*) "FELICITACIONES B. A SOS UNX GILX", 20, 25, C_FG_LIGHT_BROWN  | C_BG_RED);
	}
}

int32_t abs(int32_t n){
	if (n < 0){
		return -n;
	}
	return n;
}
