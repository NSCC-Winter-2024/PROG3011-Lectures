
	.cpu cortex-m0plus      @ same as -mcpu value
	.syntax unified         @ use new combined Thumb and ARM syntax
	.thumb                  @ use 16-bit thumb instructions

loop:
	movs R0, #0x01          @ R0 = 1
	movs R1, #0x02          @ R1 = 2
	adds R1, R0             @ R1 = R1 + R0
	b loop                  @ goto the "loop" label

	.end
