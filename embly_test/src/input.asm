SYS_EXIT equ 1
SYS_READ equ 3
SYS_WRITE equ 4
STDIN equ 0
STDOUT equ 1

section .text
	global _start

;; Main program action
_start:
	mov eax, SYS_WRITE
	mov ebx, STDOUT
	mov ecx, welcome_msg
	mov edx, welcome_len
	int 0x80
	
	;; Read numbers an assign it to memory
	mov eax, SYS_WRITE
	mov ebx, STDOUT
	mov ecx, num1_msg
	mov edx, num1_len
	int 0x80
	
	mov eax, SYS_READ
	mov ebx, STDIN
	mov ecx, num1
	mov edx, 5
	int 0x80
	
	
	
	;; Sum and show results
	mov eax, SYS_WRITE
	mov ebx, STDOUT
	mov ecx, num1
	mov edx, 5
	int 0x80
	
	;; Always exit code
	;; Not exiting code wil cause a
	;; core dumped segment error
	mov eax, SYS_EXIT
	mov ebx, 0			;; This is the exit status!!!!
	int 0x80

;; Constant messages	
section .data
	welcome_msg db "Basic assembly sumator", 0xA, 0xD
	welcome_len equ $ - welcome_msg

	num1_msg db "Number 1: "
	
	
	num1_len equ $ - num1_msg
	
	num2_msg db "Number 2: "
	num2_len equ $ - num2_msg

;; Input number variables
section .bss
	num1 resb 5
	num2 resb 5
	
