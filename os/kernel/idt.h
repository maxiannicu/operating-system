#ifndef IDT_H
#define IDT_H
#include <stdint.h>
#define IDT_ENTRIES 256
#define KERNEL_CS 0x08

typedef struct {
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t zero;      // unused, set to 0
   uint8_t type_attr; // type and attributes, see below
   uint16_t offset_2; // offset bits 16..31
} __attribute__((packed)) idt_gate_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

/* Functions implemented in idt.c */
void idt_set(int n, uint32_t handler);
void idt_init();

#endif
