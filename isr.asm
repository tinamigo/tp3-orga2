; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "print.mac"
extern pic_finish1
extern read
extern move
extern divider
extern print_board
extern desalojar
extern int_keyboard
extern print_exception
extern GDT_IDX_TSS_IDLE

extern debug_mode


%define key_y        0x15 ; 

%define temp         0 



; Teclado numerico horizontal.
%define key_0_a        0x8B ; 
%define key_1_a        0x82 ; 
%define key_2_a        0x83 ; 
%define key_3_a        0x84 ; 
%define key_4_a        0x85 ; 
%define key_5_a        0x86 ; 
%define key_6_a        0x87 ; 
%define key_7_a        0x88 ; 
%define key_8_a        0x89 ; 
%define key_9_a        0x8A ; 



; Pad numerico.
%define key_0_b        0xD2 ; 
%define key_1_b        0xCF ; 
%define key_2_b        0xD0 ; 
%define key_3_b        0xD1 ; 
%define key_4_b        0xCB ; 
%define key_5_b        0xCC ; 
%define key_6_b        0xCD ; 
%define key_7_b        0xC7 ; 
%define key_8_b        0xC8 ; 
%define key_9_b        0xC9 ; 



BITS 32

sched_task_offset:     dd 0x00
sched_task_selector:   dw 0x00

;; PIC
extern pic_finish1

;; Sched
extern sched_nextTask

isrmensaje:          db 'Exception! Su excepcion es:'
isrmensaje_len:      equ $ - isrmensaje

isrmensaje_0:        db 'Divide-by-zero (0)'
len_isrmensaje_0:    equ $ - isrmensaje_0

isrmensaje_1:        db 'reserved (1)'
len_isrmensaje_1:    equ $ - isrmensaje_1

isrmensaje_2:        db 'NMI Interrupt (2)'
len_isrmensaje_2:    equ $ - isrmensaje_2

isrmensaje_3:        db 'Breakpoint (3)'
len_isrmensaje_3:    equ $ - isrmensaje_3

isrmensaje_4:        db 'Overflow (4)'
len_isrmensaje_4:    equ $ - isrmensaje_4

isrmensaje_5:        db 'BOUND Range Exceeded (5)'
len_isrmensaje_5:    equ $ - isrmensaje_5

isrmensaje_6:        db 'Invalid Opcode (6)'
len_isrmensaje_6:    equ $ - isrmensaje_6

isrmensaje_7:        db 'Device Not Available (7)'
len_isrmensaje_7:    equ $ - isrmensaje_7

isrmensaje_8:        db 'Double Fault (8)'
len_isrmensaje_8:    equ $ - isrmensaje_8

isrmensaje_9:        db 'Coprocessor Segment Overrun (9)'
len_isrmensaje_9:    equ $ - isrmensaje_9

isrmensaje_10:       db 'Invalid TSS (10)'
len_isrmensaje_10:   equ $ - isrmensaje_10

isrmensaje_11:       db 'Segment not present (11)'
len_isrmensaje_11:   equ $ - isrmensaje_11

isrmensaje_12:       db 'Stack-Segment Fault (12)'
len_isrmensaje_12:   equ $ - isrmensaje_12

isrmensaje_13:       db 'General Protection Fault (13)'
len_isrmensaje_13:   equ $ - isrmensaje_13

isrmensaje_14:       db 'Page Fault (14)'
len_isrmensaje_14:   equ $ - isrmensaje_14

isrmensaje_15:       db 'reserved (15)'
len_isrmensaje_15:   equ $ - isrmensaje_15

isrmensaje_16:       db 'x87 FPU Foating-Point Error (16)'
len_isrmensaje_16:   equ $ - isrmensaje_16

isrmensaje_17:       db 'Alignment Check (17)'
len_isrmensaje_17:   equ $ - isrmensaje_17

isrmensaje_18:       db 'Machine Check (18)'
len_isrmensaje_18:   equ $ - isrmensaje_18

isrmensaje_19:       db 'SIMD Floating-Point Exception (19)'
len_isrmensaje_19:   equ $ - isrmensaje_19


cero_msg db       '0'
cero_msg_len equ  $ - cero_msg

one_msg db        '1'
one_msg_len equ  $ - one_msg

two_msg db        '2'
two_msg_len equ  $ - two_msg

three_msg db      '3'
three_msg_len equ  $ - three_msg

four_msg db       '4'
four_msg_len equ  $ - four_msg

five_msg db       '5'
five_msg_len equ  $ - five_msg

six_msg db        '6'
six_msg_len equ  $ - six_msg

seven_msg db      '7'
seven_msg_len equ  $ - seven_msg

eight_msg db       '8'
eight_msg_len equ  $ - eight_msg

nine_msg db       '9'
nine_msg_len equ  $ - nine_msg



;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;
%macro ISR 1        ;Cuantos parametros toma.
global _isr%1       ;Que parametro es, si es el primero o el segundo.

_isr%1:
    pushad

    xor eax, eax
    cmp [debug_mode], eax
    jne .debug
    jmp .fin
    
.debug:
    mov eax, 2
    mov [debug_mode], eax
    push gs
    push fs 
    push es 
    push ds 
    push cs 
    mov eax, cr4
    push eax
    mov eax, cr3
    push eax
    mov eax, cr2
    push eax
    mov eax, cr0
    push eax

    call print_exception
    
    ; cr
    pop eax
    pop eax
    pop eax
    pop eax
    ; segmentos
    pop eax
    pop eax
    pop eax
    pop eax
    pop eax
    

.fin

    call desalojar

    jmp (28<<3):0

    popad


    iret
%endmacro


;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR  0              ; '#DE Divide Error'
ISR  1              ; '#DB RESERVED'
ISR  2              ; 'NMI Interrupt'
ISR  3              ; '#BP Breakpoint'
ISR  4              ; '#OF Overflow'
ISR  5              ; '#BR BOUND Range Exceeded'
ISR  6              ; '#UD Invalid Opcode (Undefined Opcode)'
ISR  7              ; '#NM Device Not Available (No Math Coprocessor)'
ISR  8              ; '#DF Double Fault'
ISR  9              ; 'Coprocessor Segment Overrun (reserved)'
ISR 10              ; '#TS Invalid TSS'
ISR 11              ; '#NP Segment Not Present'
ISR 12              ; '#SS Stack-Segment Fault'
ISR 13              ; '#GP General Protection'
ISR 14              ; '#PF Page Fault'
ISR 15              ; '(Intel reserved. Do not use.)'
ISR 16              ; '#MF x87 FPU Floating-Point Error (Math Fault)'
ISR 17              ; '#AC Alignment Check'
ISR 18              ; '#MC Machine Check'
ISR 19              ; '#XM SIMD Floating-Point Exception'


;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;
global _isr32

_isr32:

    pushad           ; Push all con 32 bits. 

    call pic_finish1 ; Comunicamos al pic que se atendio la interrupcion.



    call nextClock   ; Tarea correspondiente.

    mov eax, 2
    cmp [debug_mode], eax
    je .fin

    call sched_nextTask
    str cx 
    cmp cx, ax
    je .fin 

    mov [selector], ax
    jmp far [offset]

.fin:
    popad

    iret 


;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global _isr33

_isr33:
    pushfd          ; Guarda del valor de los flags.

    pushad          ; Push all con 32 bits. 
    
    call pic_finish1
    
    xor eax, eax
    in al, 0x60     ; Leemos del teclado.

    push eax

    call int_keyboard
    
    pop ecx


    jmp .fin 
    
    cmp al, key_0_a
    je .print0
    cmp al, key_0_b
    je .print0
    cmp al, key_1_a
    je .print1
    cmp al, key_1_b
    je .print1
    cmp al, key_2_a
    je .print2
    cmp al, key_2_b
    je .print2
    cmp al, key_3_a
    je .print3
    cmp al, key_3_b
    je .print3
    cmp al, key_4_a
    je .print4
    cmp al, key_4_b
    je .print4
    cmp al, key_5_a
    je .print5
    cmp al, key_5_b
    je .print5
    cmp al, key_6_a
    je .print6
    cmp al, key_6_b
    je .print6
    cmp al, key_7_a
    je .print7
    cmp al, key_7_b
    je .print7
    cmp al, key_8_a
    je .print8
    cmp al, key_8_b
    je .print8
    cmp al, key_9_a
    je .print9
    cmp al, key_9_b
    je .print9
    jmp .fin

.print0:
    print_text_pm cero_msg, cero_msg_len, 0xCE, 0, 79
    jmp .fin

.print1:
    print_text_pm one_msg, one_msg_len, 0x5E, 0, 79
    jmp .fin

.print2:
    print_text_pm two_msg, two_msg_len, 0x4E, 0, 79
    jmp .fin

.print3:
    print_text_pm three_msg, three_msg_len, 0x6E, 0, 79
    jmp .fin

.print4:
    print_text_pm four_msg, four_msg_len, 0x0E, 0, 79
    jmp .fin

.print5:
    print_text_pm five_msg, five_msg_len, 0x05, 0, 79
    jmp .fin

.print6:
    print_text_pm six_msg, six_msg_len, 0xDE, 0, 79
    jmp .fin

.print7:
    print_text_pm seven_msg, seven_msg_len, 0xDE, 0, 79
    jmp .fin

.print8:
    print_text_pm eight_msg, eight_msg_len, 0xDE, 0, 79
    jmp .fin

.print9:
    print_text_pm nine_msg, nine_msg_len, 0xDE, 0, 79
    jmp .fin

.fin:
    popad

    popfd

    iret 






;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
global _isr71
global _isr73
global _isr76

_isr71:
    pushad    ; Push all con 32 bits. 
       
    push eax
    push ebx
    call read   
    
    mov [temp], eax
    pop ebx          
    pop ecx               ; Pues es lo mismo popear en cualquiera de los registros. Lo que importa
                          ; es que lo sacamos de la pila.
    cmp eax, 50
    je .excess


    jmp .fin

.excess:

    jmp 11100000b:0     ;salto a idle

.fin:
    popad
    mov eax, [temp]
    iret 


_isr73:
    pushad    ; Push all con 32 bits. 
    
    push ecx
    push edx

    call move   

    mov [temp], eax
    pop edx
    pop ecx

    jmp 11100000b:0     ;salto a idle

    popad
    mov eax, [temp]

    iret




_isr76:
    pushad    ;push all con 32 bits 
    ; <- esp
    push esp
    push dummy

    call divider

    mov [temp], eax

    jmp 11100000b:0     ;salto a idle  
    pop ecx
    pop ecx

    popad
    mov eax, [temp]
    iret 
    
    dummy:
    ;pop ecx
    ;pop ecx

    popad
    mov eax, 1
    iret  

;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
isrNumber:           dd 0x00000000
isrClock:            db '|/-\'
offset: dd 0
selector: dw 0
nextClock:
    
        pushad
        inc DWORD [isrNumber]
        mov ebx, [isrNumber]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrNumber], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                print_text_pm ebx, 1, 0x0f, 49, 79

     
        popad        
        ret

global getCR3


getCR3:
    push ebp
    mov ebp, esp
    mov eax, cr3
    pop ebp
    ret
;extern getCR3 

; EDI = SRC
; ESI = DST
global code_copy

code_copy:

    ;jmp .fin
    pop ecx ;direccion de la tarea
    pop edx ;direccion fisica

    mov eax, 4096  ;1 pagina de 4KB
    ;mov eax, 8192 ;2 paginas de 4KB
.ciclo:
    mov ebx, [ecx]
    mov [edx], ebx
    add edx,4  
    add ecx,4 
    sub eax, 4  
    cmp eax, 0
    je .fin 
    jmp .ciclo  

.fin:
   ret

