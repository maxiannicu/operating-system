#include "idt.h"

void idt_set(int n, uint32_t handler) {
    idt[n].offset_1 = handler & 0xFFFF;
    idt[n].selector = KERNEL_CS;
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_2 = ((handler >> 16 )& 0xFFFF);
}

void idt_init() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}
