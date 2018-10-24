global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
 global load_idt
 
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret