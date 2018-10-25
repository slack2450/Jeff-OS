// we can run things here in C!
#include "fb.h"
#include "isr.h"
#include "descriptor_tables.h"

u32int test_cursor = 20;
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
        fb_write_cell(test_cursor, characters[character], FB_GREEN, FB_BLACK);
        test_cursor++;
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
    characters[0x1E] = 'a';
    characters[0x1F] = 's';
    characters[0x20] = 'd';
    characters[0x21] = 'f';
    characters[0x22] = 'g';
    characters[0x23] = 'h';
    characters[0x24] = 'j';
    characters[0x25] = 'k';
    characters[0x26] = 'l';
    characters[0x2C] = 'z';
    characters[0x2D] = 'x';
    characters[0x2E] = 'c';
    characters[0x2F] = 'v';
    characters[0x30] = 'b';
    characters[0x31] = 'n';
    characters[0x32] = 'm';
    characters[0x33] = 'b';

    register_interrupt_handler(IRQ1, &keyboard_callback);
    return;
}

int main()
{

    fb_clear_screen();

    init_descriptor_tables();

    setup_keyboard();

    fb_put_string("Welcome to Jeff OS!", FB_GREEN, FB_BLACK);

    return 0x69;
}