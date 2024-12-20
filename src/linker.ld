SECTIONS
{
    . = 0x80000;

    .text.boot ALIGN(0x1000) : {
        *(.text.boot)
    }
    .text ALIGN(0x1000) : {
        *(.text)
    }
    .rodata ALIGN(0x1000) : {
        *(.rodata)
    }
    .data ALIGN(0x1000) : {
        *(.data)
    }
    . = ALIGN(0x1000);
    bss_begin = .;
    .bss : {
        *(.bss)
    }
    bss_end = .;
}