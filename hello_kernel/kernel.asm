;; kernel.asm
bits 32						;; directive to NASM 32 bits
section .text
	;; multiboot specifications
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00) ;; checksum

global start
extern kmain				;; C function

start:
	cli						;; block interrupts
	mov esp, stack_space	;; set stack pointer
	call kmain
	hlt						;; halt CPU
	
section .bss
resb 8192					;; 8KB for stack
stack_space:
