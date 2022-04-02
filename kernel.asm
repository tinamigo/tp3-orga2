; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "print.mac"
extern GDT_DESC
extern IDT_DESC
extern idt_init
extern pic_reset
extern pic_enable
extern pic_disable
extern screen_drawBox
extern print 
extern mmu_initKernelDir
global start
extern tss_inicializar_idle
extern tss_init
extern sched_init
extern print_board
extern game_init
extern mmu_init
extern debug_mode

extern mmu_mapPage

space equ ' '
starting_score db ' 0000000000 '  

;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
start_rm_msg db     'Iniciando kernel en Modo Real'
start_rm_len equ    $ - start_rm_msg

start_pm_msg db     'Iniciando kernel en Modo Protegido'
start_pm_len equ    $ - start_pm_msg

text_tareaA db 'TAREA A', 0
text_tareaB db 'TAREA B', 0

;msje_vacio_rosa db '                                                  ' ;50 espacios
;len_vacio_rosa equ $ - msje_vacio_rosa

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    
    ; Deshabilitar interrupciones
    cli
    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h 					  ; Set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h 					  ; Load 8x8 font

    ; Imprimir mensaje de bienvenida
    print_text_rm start_rm_msg, start_rm_len, 0x07, 0, 0

	mov al,0xdf                   ; Comando de habilitación de A20.
    call    A20_enable            ; Habilitar Gate A20.
GateA20_enabled:
    mov word [0x7DFE],0xAA55      ; Firmamos.

    ; Cargar la GDT.
     lgdt [GDT_DESC]              
   
    ; Setear el bit PE del registro CR0
	;ツ
	; 				  ; Magic Breakpoint.
    mov eax, cr0
    or eax, 1 
    mov cr0, eax          		  ; Estamos en MP.

    jmp 22<<3:mp                  ; Primer descriptor de codigo (8x22).

    ;*******************  Aquí está en modo protegido  ***************************
BITS 32
mp:
    
    ; Establecer selectores de segmentos
    mov ax, 192        			  ; Primer descriptor de datos (8x24).  
    mov ss, ax         			  ; Los ponemos en el de datos en 0 
    mov ds, ax
    mov es, ax
    mov gs, ax
    
; Establecer la base de la pila.
    mov esp, 0x27000             ; Pila del kernel.
    

    print_text_pm start_pm_msg, start_pm_len, 0xD0, 0, 0

    mov ax, 208   				 ; Segmento que describe el area de la pantalla en memoria (8x26).
    mov fs, ax     				 ; Lo ponemos en el selector de video.

     push 0xD0
     push space
     push 50
     push 50
     push 0
     push 0

    call screen_drawBox

    push 0xB0
    push space
    push 30
    push 50
    push 50
    push 0

    call screen_drawBox

    push 0X3F
    push 12  ;el otro 30
    push 61
    push text_tareaA
    call print 

    push 0X3F
    push 32
    push 61
    push text_tareaB
    call print 


    call game_init


    call print_board
    

    ;push 0xD0 
    ;push 50
    ;push 12
    ;push 59
    ;push starting_score

    ;call print

	;ツ
    ;					  ; Magic Breakpoint.
    ; Inicializar el manejador de memoria
    call mmu_init 


    ; Inicializar el directorio de paginas
    call mmu_initKernelDir

    ; Cargar directorio de paginas
    mov eax, 0x27000
    mov cr3, eax
    ; Habilitar paginacion
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ;ツ



;void mmu_mapPage(uint32_t virtual, uint32_t fisica, uint32_t cr3, uint32_t atributos) { 

;push 3
;push 0x27000
;push 0x500000
;push 0xFF00F000
;call mmu_mapPage
;add esp, 4*4

;



    ; Inicializar tss
    call tss_init
    ; Inicializar tss de la tarea Idle
    call tss_inicializar_idle

    ; Inicializar el scheduler
    ;
    call sched_init
    ;
    ; Inicializar la IDT    
    call idt_init

    ; Cargar IDT
    lidt [IDT_DESC]

    ; Configurar controlador de interrupciones
    call pic_reset
    call pic_enable
 
    ; Cargar tarea inicial
    mov ax, 27<<3
    ltr ax
    
    ;ツ
;  
    ;Inicializo el modo debug en 0
    xor ax, ax
    mov [debug_mode], ax    

    ; Habilitar interrupciones
    sti 
 ;    
    ; Saltar a la primera tarea: Idle
    jmp 11100000b:0
    
    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"

