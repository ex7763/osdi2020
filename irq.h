#ifndef _IRQ_H
#define _IRQ_H

extern void enable_irq();
extern void disable_irq();

extern void irq_router();

#define IRQ_BASIC_PENDING (volatile unsigned int *)(MMIO_BASE + 0xb200)
#define ENABLE_IRQ2 (volatile unsigned int *)(MMIO_BASE + 0xb214)

// Timers interrupt control registers
#define CORE0_TIMER_IRQCNTL (volatile unsigned int *)0x40000040
#define CORE1_TIMER_IRQCNTL (volatile unsigned int *)0x40000044
#define CORE2_TIMER_IRQCNTL (volatile unsigned int *)0x40000048
#define CORE3_TIMER_IRQCNTL (volatile unsigned int *)0x4000004C
// Where to route timer interrupt to, IRQ/FIQ
// Setting both the IRQ and FIQ bit gives an FIQ
#define TIMER0_IRQ (volatile unsigned int *)0x01
#define TIMER1_IRQ (volatile unsigned int *)0x02
#define TIMER2_IRQ (volatile unsigned int *)0x04
#define TIMER3_IRQ (volatile unsigned int *)0x08
#define TIMER0_FIQ (volatile unsigned int *)0x10
#define TIMER1_FIQ (volatile unsigned int *)0x20
#define TIMER2_FIQ (volatile unsigned int *)0x40
#define TIMER3_FIQ (volatile unsigned int *)0x80
// Mailbox interrupt control registers
#define CORE0_MBOX_IRQCNTL (volatile unsigned int *)0x40000050
#define CORE1_MBOX_IRQCNTL (volatile unsigned int *)0x40000054
#define CORE2_MBOX_IRQCNTL (volatile unsigned int *)0x40000058
#define CORE3_MBOX_IRQCNTL (volatile unsigned int *)0x4000005C
// Where to route mailbox interrupt to, IRQ/FIQ
// Setting both the IRQ and FIQ bit gives an FIQ
#define MBOX0_IRQ (volatile unsigned int *)0x01
#define MBOX1_IRQ (volatile unsigned int *)0x02
#define MBOX2_IRQ (volatile unsigned int *)0x04
#define MBOX3_IRQ (volatile unsigned int *)0x08
#define MBOX0_FIQ (volatile unsigned int *)0x10
#define MBOX1_FIQ (volatile unsigned int *)0x20
#define MBOX2_FIQ (volatile unsigned int *)0x40
#define MBOX3_FIQ (volatile unsigned int *)0x80
// IRQ & FIQ source registers
#define CORE0_IRQ_SOURCE (volatile unsigned int *)0x40000060
#define CORE1_IRQ_SOURCE (volatile unsigned int *)0x40000064
#define CORE2_IRQ_SOURCE (volatile unsigned int *)0x40000068
#define CORE3_IRQ_SOURCE (volatile unsigned int *)0x4000006C
#define CORE0_FIQ_SOURCE (volatile unsigned int *)0x40000070
#define CORE1_FIQ_SOURCE (volatile unsigned int *)0x40000074
#define CORE2_FIQ_SOURCE (volatile unsigned int *)0x40000078
#define CORE3_FIQ_SOURCE (volatile unsigned int *)0x4000007C
// Interrupt source bits
// IRQ and FIQ are the same
// GPU bits can be set for one core only
#define INT_SRC_TIMER0 (volatile unsigned int *)0x00000001
#define INT_SRC_TIMER1 (volatile unsigned int *)0x00000002
#define INT_SRC_TIMER2 (volatile unsigned int *)0x00000004
#define INT_SRC_TIMER3 (volatile unsigned int *)0x00000008
#define INT_SRC_MBOX0 (volatile unsigned int *)0x00000010
#define INT_SRC_MBOX1 (volatile unsigned int *)0x00000020
#define INT_SRC_MBOX2 (volatile unsigned int *)0x00000040
#define INT_SRC_MBOX3 (volatile unsigned int *)0x00000080
#define INT_SRC_GPU (volatile unsigned int *)0x00000100
#define INT_SRC_PMU (volatile unsigned int *)0x00000200
// Mailbox write-set registers (Write only)
#define CORE0_MBOX0_SET (volatile unsigned int *)0x40000080
#define CORE0_MBOX1_SET (volatile unsigned int *)0x40000084
#define CORE0_MBOX2_SET (volatile unsigned int *)0x40000088
#define CORE0_MBOX3_SET (volatile unsigned int *)0x4000008C
#define CORE1_MBOX0_SET (volatile unsigned int *)0x40000090
#define CORE1_MBOX1_SET (volatile unsigned int *)0x40000094
#define CORE1_MBOX2_SET (volatile unsigned int *)0x40000098
#define CORE1_MBOX3_SET (volatile unsigned int *)0x4000009C
#define CORE2_MBOX0_SET (volatile unsigned int *)0x400000A0
#define CORE2_MBOX1_SET (volatile unsigned int *)0x400000A4
#define CORE2_MBOX2_SET (volatile unsigned int *)0x400000A8
#define CORE2_MBOX3_SET (volatile unsigned int *)0x400000AC
#define CORE3_MBOX0_SET (volatile unsigned int *)0x400000B0
#define CORE3_MBOX1_SET (volatile unsigned int *)0x400000B4
#define CORE3_MBOX2_SET (volatile unsigned int *)0x400000B8
#define CORE3_MBOX3_SET (volatile unsigned int *)0x400000BC
// Mailbox write-clear registers (Read & Write)
#define CORE0_MBOX0_RDCLR (volatile unsigned int *)0x400000C0
#define CORE0_MBOX1_RDCLR (volatile unsigned int *)0x400000C4
#define CORE0_MBOX2_RDCLR (volatile unsigned int *)0x400000C8
#define CORE0_MBOX3_RDCLR (volatile unsigned int *)0x400000CC
#define CORE1_MBOX0_RDCLR (volatile unsigned int *)0x400000D0
#define CORE1_MBOX1_RDCLR (volatile unsigned int *)0x400000D4
#define CORE1_MBOX2_RDCLR (volatile unsigned int *)0x400000D8
#define CORE1_MBOX3_RDCLR (volatile unsigned int *)0x400000DC
#define CORE2_MBOX0_RDCLR (volatile unsigned int *)0x400000E0
#define CORE2_MBOX1_RDCLR (volatile unsigned int *)0x400000E4
#define CORE2_MBOX2_RDCLR (volatile unsigned int *)0x400000E8
#define CORE2_MBOX3_RDCLR (volatile unsigned int *)0x400000EC
#define CORE3_MBOX0_RDCLR (volatile unsigned int *)0x400000F0
#define CORE3_MBOX1_RDCLR (volatile unsigned int *)0x400000F4
#define CORE3_MBOX2_RDCLR (volatile unsigned int *)0x400000F8
#define CORE3_MBOX3_RDCLR (volatile unsigned int *)0x400000FC

#endif
