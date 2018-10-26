#include "keyboard.h"

u32int text = 0;
unsigned char scan_code;

int keyboard_shift_state;

char lowercase_characters[0xFF] = {};
char uppercase_characters[0xFF] = {};

char keyboard_input_buffer[KEYBOARD_INPUT_BUFFER_SIZE];
int  keyboard_input_buffer_index;

unsigned char read_scan_code(void)
{
    return inb(0x60);
}

void keyboard_input_buffer_push(char c)
{
    
    keyboard_input_buffer[keyboard_input_buffer_index] = c;
    keyboard_input_buffer_index++;
}

int keyboard_input_buffer_space()
{
    return KEYBOARD_INPUT_BUFFER_SIZE - keyboard_input_buffer_index;
}

void keyboard_input_buffer_clear()
{
    for(int i = 0; i < keyboard_input_buffer_index; i++)
    {
        keyboard_input_buffer[i] = 0x00;
    }
    keyboard_input_buffer_index = 0;
}

void keyboard_input_buffer_pop()
{
    keyboard_input_buffer_index--;
    keyboard_input_buffer[keyboard_input_buffer_index] = 0x00;
}

void keyboard_callback(registers_t regs)
{
    scan_code = read_scan_code();
    
    if(keyboard_input_buffer_space() > 0 && (lowercase_characters[scan_code] != 0x00 || uppercase_characters[scan_code] != 0x00))
    {
        if(keyboard_shift_state <= 0)
        {
            fb_put_char(lowercase_characters[scan_code], FB_WHITE, FB_BLACK);
            keyboard_input_buffer_push(lowercase_characters[scan_code]);
        }
        if(keyboard_shift_state > 0)
        {
            fb_put_char(uppercase_characters[scan_code], FB_WHITE, FB_BLACK);
            keyboard_input_buffer_push(uppercase_characters[scan_code]);
        }
    }
    else
    {
        switch(scan_code)
        {
            case SCAN_CODE_BACKSPACE:
                if(keyboard_input_buffer_index > 0)
                {
                    keyboard_input_buffer_pop();
                    fb_backspace(FB_WHITE, FB_BLACK);
                }
                break;
            case SCAN_CODE_ENTER:
                if(strcmp("help", keyboard_input_buffer) == TRUE)
                {
                    fb_new_line();
                    fb_put_string("HELP MENU:", FB_CYAN, FB_BLACK);
                    fb_new_line();
                    fb_new_line();
                    fb_put_string("Work in progress...", FB_CYAN, FB_BLACK);
                    fb_new_line();
                }
                keyboard_input_buffer_clear();
                fb_new_line();
                fb_put_string("User@Jeff:~$ ", FB_LIGHT_BLUE, FB_BLACK);
                break;
            case SCAN_CODE_L_SHIFT_DOWN:
                keyboard_shift_state++;
                break;
            case SCAN_CODE_L_SHIFT_UP:
                keyboard_shift_state--;
                break;
        }
    }

    text = regs.int_no;
    return;
}

void setup_keyboard(void)
{
    lowercase_characters[0x10] = 'q';
    lowercase_characters[0x11] = 'w';
    lowercase_characters[0x12] = 'e';
    lowercase_characters[0x13] = 'r';
    lowercase_characters[0x14] = 't';
    lowercase_characters[0x15] = 'y';
    lowercase_characters[0x16] = 'u';
    lowercase_characters[0x17] = 'i';
    lowercase_characters[0x18] = 'o';
    lowercase_characters[0x19] = 'p';
    lowercase_characters[0x1E] = 'a';
    lowercase_characters[0x1F] = 's';
    lowercase_characters[0x20] = 'd';
    lowercase_characters[0x21] = 'f';
    lowercase_characters[0x22] = 'g';
    lowercase_characters[0x23] = 'h';
    lowercase_characters[0x24] = 'j';
    lowercase_characters[0x25] = 'k';
    lowercase_characters[0x26] = 'l';
    lowercase_characters[0x2C] = 'z';
    lowercase_characters[0x2D] = 'x';
    lowercase_characters[0x2E] = 'c';
    lowercase_characters[0x2F] = 'v';
    lowercase_characters[0x30] = 'b';
    lowercase_characters[0x31] = 'n';
    lowercase_characters[0x32] = 'm';
    lowercase_characters[0x39] = ' ';

    uppercase_characters[0x10] = 'Q';
    uppercase_characters[0x11] = 'W';
    uppercase_characters[0x12] = 'E';
    uppercase_characters[0x13] = 'R';
    uppercase_characters[0x14] = 'T';
    uppercase_characters[0x15] = 'Y';
    uppercase_characters[0x16] = 'U';
    uppercase_characters[0x17] = 'I';
    uppercase_characters[0x18] = 'O';
    uppercase_characters[0x19] = 'P';
    uppercase_characters[0x1E] = 'A';
    uppercase_characters[0x1F] = 'S';
    uppercase_characters[0x20] = 'D';
    uppercase_characters[0x21] = 'F';
    uppercase_characters[0x22] = 'G';
    uppercase_characters[0x23] = 'H';
    uppercase_characters[0x24] = 'J';
    uppercase_characters[0x25] = 'K';
    uppercase_characters[0x26] = 'L';
    uppercase_characters[0x2C] = 'Z';
    uppercase_characters[0x2D] = 'X';
    uppercase_characters[0x2E] = 'C';
    uppercase_characters[0x2F] = 'V';
    uppercase_characters[0x30] = 'B';
    uppercase_characters[0x31] = 'N';
    uppercase_characters[0x32] = 'M';
    uppercase_characters[0x39] = ' ';

    keyboard_input_buffer_index = 0;
    keyboard_shift_state = 0;

    register_interrupt_handler(IRQ1, &keyboard_callback);
    return;
}
