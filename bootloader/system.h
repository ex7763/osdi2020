#ifndef _SYSTEM_H_
#define _SYSTEM_H_


#define PM_PASSWORD 0x5a000000

#define PM_RSTC      ((volatile unsigned int*)(0x3F10001c))
#define PM_RSTS      ((volatile unsigned int*)(0x3F100020))
#define PM_WDOG      ((volatile unsigned int*)(0x3F100024))


/*****
time = timer counter / timer frequency

register 64bits
*****/
float gettime(){
    register unsigned long frq, ct;
    // mrs: 狀態暫存器到通用暫存器的傳送指令
    asm volatile("mrs %0, cntfrq_el0" : "=r"(frq));
    asm volatile("mrs %0, cntpct_el0" : "=r"(ct));

    return (float)ct/frq;
}


/*****
This snippet of code only works on real rpi3, not on QEMU.
*****/
void reset(int tick){ // reboot after watchdog timer expire
  unsigned int r;
  r = *PM_RSTS;
  r &= ~0xfffffaaa;
  *PM_RSTC = PM_PASSWORD | 0x00000020; // full reset
  *PM_RSTS = PM_PASSWORD | r;
  *PM_WDOG = PM_PASSWORD | 10; // number of watchdog tick
}

void cancel_reset() {
  unsigned int r;
  r = *PM_RSTS;
  r &= ~0xfffffaaa;
  *PM_RSTC = PM_PASSWORD | 0; // full reset
  *PM_RSTS = PM_PASSWORD | r;
  *PM_WDOG = PM_PASSWORD | 0; // number of watchdog tick
}
#endif
