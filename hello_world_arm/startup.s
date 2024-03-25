
	.cpu cortex-m0plus      @ same as -mcpu value
	.syntax unified         @ use new combined Thumb and ARM syntax
	.thumb                  @ use 16-bit thumb instructions

	.global _vectors, _start

	.section .vectors

	@ from 0x00000000 to 0x000000C0
	@ each vector is 32-bits (4 bytes) long

	.type _vectors, %object
_vectors:
	.long _stack_top
	.long _start

	.rept 46
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
	.end
