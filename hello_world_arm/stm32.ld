MEMORY
{
    rom (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    ram (!rx) : ORIGIN = 0x20000000, LENGTH = 36K
}

_stack_top = ORIGIN(ram) + LENGTH(ram);

ENTRY(_start)

SECTIONS
{
    .text : {
        *(.vectors)
        *(.text)
    } > rom

    .data : {
        *(.data)
    } > ram AT > rom

    .bss : {
        *(.bss)
    } > ram
}
