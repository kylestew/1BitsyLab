.syntax unified
.thumb_func
.global main
main:
    # Turn on on GPIOA by enabling its clock
    # load base RCC register address into r0
    movw r0, #0x3800  @ Copy 0x3800 to the bottom half of r0
    movt r0, #0x4002  @ Copy 0x4002 to the top half of r0 (t stands for top)

    # set bit 0 in register r1 (GPIOAEN bit)
    movw r1, #0x01

    # store value in r1 at RCC base + AHB1ENR offset (0x30)
    str r1, [r0, #0x30]

    # Enable GPIOA8 as an output in the GPIOA_MODER register
    # load base GPIOA register into r0
    movw r0, #0x0000
    movt r0, #0x4002
    # reset value of 0xA800 0000 needs to be added to MODER8[1:0] bits
    # (0xA800 0000 + 0x0001 0000)
    movw r1, #0x0000
    movt r1, #0xA801
    # store value on GPIOA_MODER register
    str r1, [r0]

.loop:
    # set BPIOA_BSRR bit for BR8 (turn on LED)
    movw r1, #0x0000
    movt r1, #0x0100
    # GPIOA base address is still in r0
    # BSRR register is offset by 0x18
    str r1, [r0, #0x18]

    # Delay - count down from 0x3500 000c
    movw r2, #0x3500
    movt r2, #0x000c
.L1:
    # sub(s) will set a flag in Program Status Register if result is zero
    subs r2, #0x0001
    bne .L1

    # Set BS8 field in GPIOA_BSRR (turn off LED)
    movw r1, #0x0100
    str r1, [r0, #0x18]

    # Delay
    movw r2, #0x3500
    movt r2, #0x000c
.L2:
    subs r2, #0x0001
    bne .L2

    # bkpt
    b .loop

.section .vector_table.reset_vector
.word main
