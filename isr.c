//
// isr.c -- High level interrupt service routines and interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
//

#include "common.h"
#include "isr.h"
#include "fb.h"

isr_t interrupt_handlers[256];

// This gets called from our ASM interrupt handler stub.
int interrupt_handler(registers_t regs)
{
    fb_clear_screen();
    char welcomeMessage[] = "Interupt";

    for(int i = 0; i < 8; i++)
    {
        fb_write_cell(i, welcomeMessage[i], FB_GREEN, FB_BLACK);
    }
    return regs.int_no;
} 

// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
} 