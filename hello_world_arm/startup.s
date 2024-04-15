
	.cpu cortex-m0plus      @ same as -mcpu value
	.syntax unified         @ use new combined Thumb and ARM syntax
	.thumb                  @ use 16-bit thumb instructions

	.global _vectors, _start, _print_ch

	.section .vectors

	@ from 0x00000000 to 0x000000C0
	@ each vector is 32-bits (4 bytes) long

	.type _vectors, %object
_vectors:
	.long _stack_top        @ 0
	.long _start            @ 1

	.rept 13
	.long 0
	.endr

	.long systick_handler   @ 15

	.rept 7
	.long 0
	.endr

	.long exti4_15_handler	@ 23

	.rept 24
	.long 0
	.endr

	.size _vectors, . - _vectors

	.text
	.type _start, %function
_start:
	@ setup stuff goes here
	ldr r0, =_stack_top
	mov sp, r0

	b main  @ jump to main routine

	.size _start, . - _start

	.type _print_ch, %function
_print_ch:
	push { r0, r1 }         @ save old r0 and r1
	mov r1, r0              @ copy r0 (parameter) to r1
	ldr r0, =#3             @ set r0 to semihosting operation (e.g. SYS_WRITEC)
	bkpt 0xab               @ call semihosting service
	pop { r0, r1 }          @ restore r0 and r1
	bx lr                   @ return to the caller
	.size _print_ch, . - _print_ch

	.end
