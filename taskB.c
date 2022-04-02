/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "syscall.h" 

//extern int16_t _isr71(int32_t y, int32_t x);

void task() {


 while(1){}
  while(1){
  int32_t move_res = 8;
    int32_t divide_res = syscall_divide();
    if (divide_res == 0 && move_res != 0xFAFAFA){
      move_res = syscall_move(3, Right);
    } else if (divide_res == 1) {
      move_res = syscall_move(3, Down);
    } if (divide_res == -1) {
      while(1){
        move_res = syscall_move(1, Up);      }
    }
    
  }
  
/*
   int32_t move_res = 8; 

  int32_t divide_res = syscall_divide();
  if (divide_res != 0 && move_res != 8000){
    move_res = syscall_move(3, Right);
  }
  move_res = syscall_move(1, Up);
  divide_res = syscall_divide();
  if (divide_res != 0 && move_res != 8000){
    move_res = syscall_move(3, Right);
  }

  while(1){
    move_res = syscall_move(1, Up); 
    move_res = syscall_move(5, Left); 
    move_res = syscall_move(6, Down); 
    move_res = syscall_move(3, Right); 
  }

*/
/*
   bool primera_vez = true; 
   int32_t aux = 8;
   while(1) {
    int32_t divide_res;
    if (primera_vez){      
      divide_res = syscall_divide();
      primera_vez = false;
      if (divide_res != 0 && aux != 8000){
        aux = syscall_move(3, Right);

        //primera_vez = true;
      }
      
    }
    while(1){}
  }

*/


/* while (1){
    int32_t read_res = syscall_read(3,3);
    int32_t aux = syscall_move(1, Left);
    aux = syscall_move(1, Up);
    aux = syscall_move(1, Up);
    aux = syscall_move(1, Up);
    int32_t divide_res = syscall_divide();
    if(divide_res == 0 || aux == 8000 || read_res == 8000){
      aux = syscall_move(5, Left);
     } else {
      while(1){
        aux = syscall_move(5, Up);
      }
    }    
  }
*/



  /*while(1) { 
    int32_t aux = syscall_move(1, Down);
    aux = syscall_move(1, Left);
    aux = syscall_move(1, Left);
    if(aux !=0){
    }
  }
*/
/*
  while(1){
    int32_t aux = syscall_move(1, Right);
    //aux = syscall_move(1, Up);
    //aux = syscall_move(1, Left);
    //aux = syscall_move(1, Up);


    if (aux != 0){
      aux = 0; 
    }
  }
*/
       /*
        int32_t aux =  syscall_divide();


          if (aux != 0){
            aux = 0; 
        }
   }*/
/*
    int a = syscall_read(1,1);
    if(a == 40) {
        syscall_move(1, Down);
        syscall_move(1, Right);
    }
*/

    while(1) { __asm __volatile("mov $2, %%eax":::"eax"); }
}
