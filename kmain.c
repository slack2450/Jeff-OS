// we can run things here in C!
#include "fb.h"
#include "isr.h"
#include "descriptor_tables.h"

u32int cursor = 20;
u32int text = 0;
unsigned char character;

char characters[0xFF] = {};

unsigned char read_scan_code(void)
{
    return inb(0x60);
}

static void keyboard_callback(registers_t regs)
{
    character = read_scan_code();
    if(characters[character] != 0x00)
    {
        fb_write_cell(cursor, characters[character], FB_GREEN, FB_BLACK);
        cursor++;
    }
    text = regs.int_no;
    return;
}

static void setup_keyboard(void)
{
    characters[0x10] = 'q';
    characters[0x11] = 'w';
    characters[0x12] = 'e';
    characters[0x13] = 'r';
    characters[0x14] = 't';
    characters[0x15] = 'y';
    characters[0x16] = 'u';
    characters[0x17] = 'i';
    characters[0x18] = 'o';
    characters[0x19] = 'p';

    register_interrupt_handler(IRQ1, &keyboard_callback);
    return;
}

int main()
{

    fb_clear_screen();

    init_descriptor_tables();

    setup_keyboard();

    char welcomeMessage[] = "Welcome to Jeff OS!";

    for(int i = 0; i < 19; i++)
    {
        fb_write_cell(i, welcomeMessage[i], FB_GREEN, FB_BLACK);
    }

    return 0x69;
}