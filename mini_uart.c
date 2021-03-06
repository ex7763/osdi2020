#include "gpio.h"
#include "common.h"
#include "string.h"

/* Auxilary mini UART registers */
#define AUX_ENABLE ((volatile unsigned int *)(MMIO_BASE + 0x00215004))
#define AUX_MU_IO ((volatile unsigned int *)(MMIO_BASE + 0x00215040))
#define AUX_MU_IER ((volatile unsigned int *)(MMIO_BASE + 0x00215044))
#define AUX_MU_IIR ((volatile unsigned int *)(MMIO_BASE + 0x00215048))
#define AUX_MU_LCR ((volatile unsigned int *)(MMIO_BASE + 0x0021504C))
#define AUX_MU_MCR ((volatile unsigned int *)(MMIO_BASE + 0x00215050))
#define AUX_MU_LSR ((volatile unsigned int *)(MMIO_BASE + 0x00215054))
#define AUX_MU_MSR ((volatile unsigned int *)(MMIO_BASE + 0x00215058))
#define AUX_MU_SCRATCH ((volatile unsigned int *)(MMIO_BASE + 0x0021505C))
#define AUX_MU_CNTL ((volatile unsigned int *)(MMIO_BASE + 0x00215060))
#define AUX_MU_STAT ((volatile unsigned int *)(MMIO_BASE + 0x00215064))
#define AUX_MU_BAUD ((volatile unsigned int *)(MMIO_BASE + 0x00215068))

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void mini_uart_init()
{
    register unsigned int r;

    /* initialize UART */
    *AUX_ENABLE |= 1; // enable UART1, AUX mini uart
    *AUX_MU_CNTL = 0;
    *AUX_MU_LCR = 3; // 8 bits
    *AUX_MU_MCR = 0;
    *AUX_MU_IER = 0;
    *AUX_MU_IIR = 0xc6; // disable interrupts
    *AUX_MU_BAUD = 270; // 115200 baud
    /* map UART1 to GPIO pins */
    r = *GPFSEL1;
    r &= ~((7 << 12) | (7 << 15)); // gpio14, gpio15
    r |= (2 << 12) | (2 << 15);    // alt5
    *GPFSEL1 = r;
    *GPPUD = 0; // enable pins 14 and 15
    r = 150;
    while (r--)
    {
        asm volatile("nop");
    }
    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    r = 150;
    while (r--)
    {
        asm volatile("nop");
    }
    *GPPUDCLK0 = 0;   // flush GPIO setup
    *AUX_MU_CNTL = 3; // enable Tx, Rx
}

void mini_uart_send(unsigned int c)
{
    // Check AUX_MU_LSR_REG’s Transmitter empty field.
    while (!(*AUX_MU_LSR & 0x20))
    {
        asm volatile("nop");
    };

    // If set, write to AUX_MU_IO_REG
    *AUX_MU_IO = c;
}

char mini_uart_getc()
{
    char c;

    // Check AUX_MU_LSR_REG’s data ready field.
    while (!(*AUX_MU_LSR & 0x01))
    {
        asm volatile("nop");
    };

    // If set, read from AUX_MU_IO_REG
    c = (char)(*AUX_MU_IO);

    // '\r' => '\n'
    c = (c == '\r') ? '\n' : c;

    return c;
}

void mini_uart_puts(char *s)
{
    while (*s != '\0')
    {
        /* convert newline to carrige return + newline */
        if (*s == '\n')
            mini_uart_send('\r');
        mini_uart_send(*s++);
    }
}

void mini_uart_send_int(int n)
{
    char s[1024];
    itoa(n, s, 10);

    mini_uart_puts(s);
}

void mini_uart_send_hex(int n)
{
    char s[1024];
    itoa(n, s, 16);

    mini_uart_puts("0x");
    mini_uart_puts(s);
}

void mini_uart_send_float(float f, int n)
{
    char s[1024];
    ftoa(f, s, n);
    mini_uart_puts(s);
}

int mini_uart_print(char *s)
{
    mini_uart_puts(s);
}

int mini_uart_gets(char *buf, int buf_size)
{
    int i = 0;
    char c;

    do
    {
        c = mini_uart_getc();

        c = c == '\r' ? '\n' : c;

        if (c == 8 || c == 127)
        {
            if (i > 0)
            {
                buf[i--] = '\0';
                mini_uart_send(8);
                mini_uart_send(' ');
                mini_uart_send(8);
            }
        }
        else
        {
            buf[i++] = c;
            // ensure users can see what they type
            mini_uart_send(c);
        }
    } while (c != '\n' && i < buf_size - 1);

    // replace '\n' with NULL
    buf[--i] == '\0';

    if (i == buf_size)
        return -1;

    return i;
}
