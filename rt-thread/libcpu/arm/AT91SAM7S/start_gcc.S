/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first version
 */

    /* Internal Memory Base Addresses */
    .equ    FLASH_BASE,     0x00100000
    .equ    RAM_BASE,       0x00200000

    /* Stack Configuration */
    .equ    TOP_STACK,      0x00204000
    .equ    UND_STACK_SIZE, 0x00000100
    .equ    SVC_STACK_SIZE, 0x00000400
    .equ    ABT_STACK_SIZE, 0x00000100
    .equ    FIQ_STACK_SIZE, 0x00000100
    .equ    IRQ_STACK_SIZE, 0x00000100
    .equ    USR_STACK_SIZE, 0x00000004

    /* ARM architecture definitions */
    .equ    MODE_USR, 0x10
    .equ    MODE_FIQ, 0x11
    .equ    MODE_IRQ, 0x12
    .equ    MODE_SVC, 0x13
    .equ    MODE_ABT, 0x17
    .equ    MODE_UND, 0x1B
    .equ    MODE_SYS, 0x1F

    .equ    I_BIT, 0x80    /* when this bit is set, IRQ is disabled */
    .equ    F_BIT, 0x40    /* when this bit is set, FIQ is disabled */

.section .init, "ax"
.code 32
.align 0
.globl _start
_start:
    b   reset
    ldr pc, _vector_undef
    ldr pc, _vector_swi
    ldr pc, _vector_pabt
    ldr pc, _vector_dabt
    nop                         /* reserved vector */
    ldr pc, _vector_irq
    ldr pc, _vector_fiq

_vector_undef:  .word vector_undef
_vector_swi:    .word vector_swi
_vector_pabt:   .word vector_pabt
_vector_dabt:   .word vector_dabt
_vector_resv:   .word vector_resv
_vector_irq:    .word vector_irq
_vector_fiq:    .word vector_fiq

/*
 * rtthread bss start and end
 * which are defined in linker script
 */
.globl _bss_start
_bss_start: .word __bss_start
.globl _bss_end
_bss_end:   .word __bss_end

/* the system entry */
reset:
    /* disable watchdog */
    ldr r0, =0xFFFFFD40
    ldr r1, =0x00008000
    str r1, [r0, #0x04]

    /* enable the main oscillator */
    ldr r0, =0xFFFFFC00
    ldr r1, =0x00000601
    str r1, [r0, #0x20]

    /* wait for main oscillator to stabilize */
moscs_loop:
    ldr r2, [r0, #0x68]
    ands r2, r2, #1
    beq moscs_loop

    /* set up the PLL */
    ldr r1, =0x00191C05
    str r1, [r0, #0x2C]

    /* wait for PLL to lock */
pll_loop:
    ldr r2, [r0, #0x68]
    ands r2, r2, #0x04
    beq pll_loop

    /* select clock */
    ldr r1, =0x00000007
    str r1, [r0, #0x30]

    /* setup stack for each mode */
    ldr r0, =TOP_STACK

    /* set stack */
    /* undefined instruction mode */
    msr cpsr_c, #MODE_UND|I_BIT|F_BIT
    mov sp, r0
    sub r0, r0, #UND_STACK_SIZE

    /* abort mode */
    msr cpsr_c, #MODE_ABT|I_BIT|F_BIT
    mov sp, r0
    sub r0, r0, #ABT_STACK_SIZE

    /* FIQ mode */
    msr cpsr_c, #MODE_FIQ|I_BIT|F_BIT
    mov sp, r0
    sub r0, r0, #FIQ_STACK_SIZE

    /* IRQ mode */
    msr cpsr_c, #MODE_IRQ|I_BIT|F_BIT
    mov sp, r0
    sub r0, r0, #IRQ_STACK_SIZE

    /* supervisor mode */
    msr cpsr_c, #MODE_SVC
    mov sp, r0

#ifdef __FLASH_BUILD__
    /* Relocate .data section (Copy from ROM to RAM) */
    ldr     r1, =_etext
    ldr     r2, =_data
    ldr     r3, =_edata
data_loop:
    cmp     r2, r3
    ldrlo   r0, [r1], #4
    strlo   r0, [r2], #4
    blo     data_loop
#else
    /* remap SRAM to 0x0000 */
    ldr r0, =0xFFFFFF00
    mov r1, #0x01
    str r1, [r0]
#endif

    /* mask all IRQs */
    ldr r1, =0xFFFFF124
    ldr r0, =0XFFFFFFFF
    str r0, [r1]

    /* start RT-Thread Kernel */
    ldr pc, _rtthread_startup

_rtthread_startup: .word rtthread_startup

/* exception handlers */
vector_undef: b vector_undef
vector_swi  : b vector_swi
vector_pabt : b vector_pabt
vector_dabt : b vector_dabt
vector_resv : b vector_resv

.globl rt_interrupt_enter
.globl rt_interrupt_leave
.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
vector_irq:
    stmfd   sp!, {r0-r12,lr}
    bl  rt_interrupt_enter
    bl  rt_hw_trap_irq
    bl  rt_interrupt_leave

    /*
     * if rt_thread_switch_interrupt_flag set, jump to
     * rt_hw_context_switch_interrupt_do and don't return
     */
    ldr r0, =rt_thread_switch_interrupt_flag
    ldr r1, [r0]
    cmp r1, #1
    beq rt_hw_context_switch_interrupt_do

    ldmfd   sp!, {r0-r12,lr}
    subs    pc, lr, #4

vector_fiq:
    stmfd   sp!,{r0-r7,lr}
    bl  rt_hw_trap_fiq
    ldmfd   sp!,{r0-r7,lr}
    subs    pc,lr,#4

/*
 * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
 */
rt_hw_context_switch_interrupt_do:
    mov     r1,  #0             /* clear flag */
    str     r1,  [r0]

    ldmfd   sp!, {r0-r12,lr}    /* reload saved registers */
    stmfd   sp!, {r0-r3}        /* save r0-r3 */
    mov     r1,  sp
    add     sp,  sp, #16        /* restore sp */
    sub     r2,  lr, #4         /* save old task's pc to r2 */

    mrs     r3,  spsr           /* disable interrupt */
    orr     r0,  r3, #I_BIT|F_BIT
    msr     spsr_c, r0

    ldr     r0,  =.+8           /* switch to interrupted task's stack */
    movs    pc,  r0

    stmfd   sp!, {r2}           /* push old task's pc */
    stmfd   sp!, {r4-r12,lr}    /* push old task's lr,r12-r4 */
    mov     r4,  r1             /* Special optimised code below */
    mov     r5,  r3
    ldmfd   r4!, {r0-r3}
    stmfd   sp!, {r0-r3}        /* push old task's r3-r0 */
    stmfd   sp!, {r5}           /* push old task's psr */
    mrs     r4,  spsr
    stmfd   sp!, {r4}           /* push old task's spsr */

    ldr     r4,  =rt_interrupt_from_thread
    ldr     r5,  [r4]
    str     sp,  [r5]           /* store sp in preempted tasks's TCB */

    ldr     r6,  =rt_interrupt_to_thread
    ldr     r6,  [r6]
    ldr     sp,  [r6]           /* get new task's stack pointer */

    ldmfd   sp!, {r4}           /* pop new task's spsr */
    msr     SPSR_cxsf, r4
    ldmfd   sp!, {r4}           /* pop new task's psr */
    msr     CPSR_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc} /* pop new task's r0-r12,lr & pc */
