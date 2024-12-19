
;# put32(unsigned long x0, unsigned int w1);
.globl put32
put32:
    stp fp, lr, [sp, -16]!
    mov fp, sp
    str w1, [x0]
    ldp fp, lr, [sp], 16
    ret

;# extern unsigned int get32(unsigned long x0);
.globl get32
get32:
    stp fp, lr, [sp, -16]!
    mov fp, sp
    ldr w0, [x0]
    ldp fp, lr, [sp], 16
    ret

;# delay(unsigned long x0);
.globl delay
delay:
    stp fp, lr, [sp, -16]!
    mov fp, sp
delay_loop:
    subs x0, x0, #1
    bne delay_loop
    ldp fp, lr, [sp], 16
    ret
