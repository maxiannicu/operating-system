#include "isr.h"
#include "../drivers/display.h"
#include "idt.h"
#include "../tools/string.h"

interrupt_handler interrupt_handlers[256];

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_init() {
    idt_set(0, (uint32_t)isr0);
    idt_set(1, (uint32_t)isr1);
    idt_set(2, (uint32_t)isr2);
    idt_set(3, (uint32_t)isr3);
    idt_set(4, (uint32_t)isr4);
    idt_set(5, (uint32_t)isr5);
    idt_set(6, (uint32_t)isr6);
    idt_set(7, (uint32_t)isr7);
    idt_set(8, (uint32_t)isr8);
    idt_set(9, (uint32_t)isr9);
    idt_set(10, (uint32_t)isr10);
    idt_set(11, (uint32_t)isr11);
    idt_set(12, (uint32_t)isr12);
    idt_set(13, (uint32_t)isr13);
    idt_set(14, (uint32_t)isr14);
    idt_set(15, (uint32_t)isr15);
    idt_set(16, (uint32_t)isr16);
    idt_set(17, (uint32_t)isr17);
    idt_set(18, (uint32_t)isr18);
    idt_set(19, (uint32_t)isr19);
    idt_set(20, (uint32_t)isr20);
    idt_set(21, (uint32_t)isr21);
    idt_set(22, (uint32_t)isr22);
    idt_set(23, (uint32_t)isr23);
    idt_set(24, (uint32_t)isr24);
    idt_set(25, (uint32_t)isr25);
    idt_set(26, (uint32_t)isr26);
    idt_set(27, (uint32_t)isr27);
    idt_set(28, (uint32_t)isr28);
    idt_set(29, (uint32_t)isr29);
    idt_set(30, (uint32_t)isr30);
    idt_set(31, (uint32_t)isr31);

    // Remap the PIC
	port_byte_out(0x20, 0x11);
	port_byte_out(0xA0, 0x11);
	port_byte_out(0x21, 0x20);
	port_byte_out(0xA1, 0x28);
	port_byte_out(0x21, 0x04);
	port_byte_out(0xA1, 0x02);
	port_byte_out(0x21, 0x01);
	port_byte_out(0xA1, 0x01);
	port_byte_out(0x21, 0x0);
	port_byte_out(0xA1, 0x0);

	// Install the IRQs
	idt_set(32, (uint32_t)irq0);
	idt_set(33, (uint32_t)irq1);
	idt_set(34, (uint32_t)irq2);
	idt_set(35, (uint32_t)irq3);
	idt_set(36, (uint32_t)irq4);
	idt_set(37, (uint32_t)irq5);
	idt_set(38, (uint32_t)irq6);
	idt_set(39, (uint32_t)irq7);
	idt_set(40, (uint32_t)irq8);
	idt_set(41, (uint32_t)irq9);
	idt_set(42, (uint32_t)irq10);
	idt_set(43, (uint32_t)irq11);
	idt_set(44, (uint32_t)irq12);
	idt_set(45, (uint32_t)irq13);
	idt_set(46, (uint32_t)irq14);
	idt_set(47, (uint32_t)irq15);

    idt_init(); // Load with ASM

    asm volatile("sti"); // enable interrupts
}

void isr_handler(registers_t r) {
    print("ISR: ");
    char s[3];
    itoa(r.int_no, s,10);
    print(s);
    print("\n");
    print(exception_messages[r.int_no]);
    print("\n");
}

void irq_handler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40)
    	port_byte_out(0xA0, 0x20); /* slave */
    port_byte_out(0x20, 0x20); /* master */

    interrupt_handler handler = interrupt_handlers[r.int_no];
    if(handler != 0){
    	handler(r);
    }
}


void isr_register_handler(uint8_t n,interrupt_handler handler){
	interrupt_handlers[n] = handler;
}
