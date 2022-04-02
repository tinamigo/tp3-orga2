/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "syscall.h" 
#include "game.h"
#include "screen.h"

//extern int32_t syscall_read(uint32_t x, uint32_t y);

void task() {
/*
  int32_t read_res = 8;
  int32_t move_res = 8;


  read_res = syscall_read(5,5);

  if (read_res == Food || move_res == 800000){
    while(1){
      move_res = syscall_move(1, Right);
    }
  } else {
    while(1){
      move_res = syscall_move(1, Down);
    }
  }

*/

/*
  int32_t move_res = 8;
  int32_t divide_res = syscall_divide();
  if (divide_res == 0 && move_res != 0xFAFAFA ){
      move_res = syscall_move(3, Right);
    } 

  while(1){
      move_res = syscall_move(1, Down);
  }
*/
/*
  int32_t move_res = 8;
    int32_t divide_res = syscall_divide();
    if (divide_res == 0 && move_res != 0xFAFAFA ){
      move_res = syscall_move(3, Right);
    } else if (divide_res == 1) {
      move_res = syscall_move(3, Down);
    } else if (divide_res == -1) {

      while(1){
        move_res = syscall_move(1, Up);      }
    }
    
  }
  */




/*
// UNA A QUIETA Y LA OTRA POR LA LINEA 
  int32_t move_res = 8;

  int32_t read_res = syscall_read(3,3);
  read_res = syscall_read(3,3);
  read_res = syscall_read(3,3);
  read_res = syscall_read(3,3);
  move_res = syscall_move(3, Right);
  int32_t divide_res = syscall_divide();
  if (divide_res != 0 && move_res != 0xFAFAFA && read_res != 0xFAFAFA){
    move_res = syscall_move(3, Right);
    divide_res = syscall_divide();
    while(1){
    move_res = syscall_move(2, Right); 
  }
  //}
}
  while(1){
    //move_res = syscall_move(1, Up); 
  }
*/

/*
int32_t aux = 8;
int32_t divide_res = syscall_divide();


  if(divide_res == 1 || aux == 8000 ){
    aux = syscall_move(5, Right);
    while(1){
      aux = syscall_move(5, Right);
    }
  }else {
    
  }    

  while(1){

  }

*/



/*
int32_t divide_res = syscall_divide();
  while (1){
    int32_t read_res = syscall_read(3,3);
    int32_t aux = syscall_move(1, Right);
    aux = syscall_move(1, Down);
    aux = syscall_move(1, Down);
    
    if(divide_res == 0 || aux == 8000 || read_res == 8000){
      aux = syscall_move(5, Right);
    } else if (divide_res == -1){

    } else {
      while(1){
        aux = syscall_move(5, Down);
      }
    }    
  }

 */ 








  
   bool primera_vez = true; 
   int32_t aux;
   for (int i = 0; i < 80; ++i){
      aux = syscall_move(1, Up);
    }
   while(1) {
    int32_t divide_res = 0;
    if (primera_vez){      
      divide_res = syscall_divide();
      primera_vez = false;
      if (divide_res != 0 && aux != 8000){
        aux = syscall_move(2, Right);
       int cero = 0;
       aux = aux / cero;
       primera_vez = true;

      }
      
    }

    for (int i = 0; i < 80; ++i){
      aux = syscall_move(1, Up);
    }

  }

    //while(1) { __asm __volatile("mov $2, %%eax":::"eax"); }
}
