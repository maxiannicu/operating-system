#include "timer.h"
#include "display.h"
#include "../kernel/isr.h"
#include "../runtime/string.h"
#include "../runtime/ports.h"

uint32_t tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    display_print_str("Tick: ");

    char tick_ascii[256];
    itoa(tick, tick_ascii,10);
    display_print_str(tick_ascii);
    display_print_str("\n");
}

void timer_init(uint32_t freq) {
    /* Install the function we just wrote */
    isr_register_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);

    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
