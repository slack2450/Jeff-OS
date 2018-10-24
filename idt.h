#ifndef INCLUDE_IDT_H
#define INCLUDE_IDT_H

#include "io.h"

struct IDT_entry{
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};
 
struct IDT_entry IDT[286];

void idt_init(void) {
    extern int load_idt();

    unsigned long idt_address;
	unsigned long idt_ptr[2]; 
 
	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * 286) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;
 
 
 
	load_idt(idt_ptr);
 
}

#endif /* INCLUDE_IDT_H */