global loader                                   ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002                     ; define the magic number constant
FLAGS        equ 0x0                            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER                  ; calculate the checksum
                                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096                      ; size of stack in bytes
extern main


section .bss
align 4                                         ; align at 4 byes
kernel_stack:                                   ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                      ; reserve stack for the kernel
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ;point esp to the start of the
                                                ; stack (end of memory aread)

section .text                                   ; start of the text (code) section
align 4                                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER                             ; write the magic number to the machine code,
    dd FLAGS                                    ; the flags,
    dd CHECKSUM                                 ; and the checksum

gdt:
    
    gdt_null:
        dq 0
    gdt_code:
        dw 0FFFFh
        dw 0
        db 0
        db 10011010b
        db 11001111b
        db 0
    gdt_data:
        dw 0FFFFh
        dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0
gdt_end:
    
gdt_desc:
    dw gdt_end - gdt - 1
    dd gdt


loader:                                         ; the loader label (defined as entry point in linker script)

    
    lgdt [gdt_desc]
    jmp 0x0008:fix_cs
    fix_cs:
    mov ax, 0x0010
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, kernel_stack   ;set stack pointer

    mov eax, 0xCAFEBABE                         ; place the number 0xCAFEBABE in the register eax
    call main

.loop:
    jmp .loop                                   ; loop forever