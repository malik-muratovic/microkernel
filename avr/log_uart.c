#include <inttypes.h>
#include <avr/io.h>
#include "kernel_log.h"

void port_log_init(void)
{
    #define F_CPU 8000000
    #define BAUD 31250
    #include <util/setbaud.h>
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
    #if USE_2X
        UCSRA |= _BV(U2X);
    #else
        UCSRA &= ~(_BV(U2X));
    #endif
    /* Enable receiver and transmitter. */
    UCSRB = _BV(RXEN) | _BV(TXEN);
    port_log_putchar('\n');
    log_line("OK");
}

void port_log_putchar(char c)
{
    if ('\n' == c) {
        port_log_putchar('\r');
    }
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
}

static char num_to_hex(uint8_t n)
{
    if (n > 9) {
        return n + 'a' - 10;
    } else {
        return n + '0';
    }
}

void port_log_puthex(uint8_t v)
{
    port_log_putchar(num_to_hex(v >> 4));
    port_log_putchar(num_to_hex(v & 0x0f));
}

void port_log_putstring(const char *string)
{
  char c;

  while ((c = *string++)) {
    port_log_putchar(c);
  }
}

char port_log_getchar(void)
{
    loop_until_bit_is_set(UCSRA, RXC);
	return UDR;
}

