#include "fb.h"

char *fb = (char *) 0x000B8000;

void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    i*=2;
    fb[i] = c;
    fb[i+1] = (fg & 0x0F) | ((bg & 0x0F) << 4);
}

void fb_clear_screen()
{
    fb_move_cursor(0);
    fb_cursor = 0;
    fb_row = 0;
    for(int i = 0; i < 80 * 25; i++)
    {
        fb_write_cell(i, ' ', FB_WHITE, FB_BLACK);
    }
}

void fb_increment_cursor()
{
    fb_cursor++;
    if(fb_cursor == 80)
    {
        fb_row++;
        fb_cursor = 0;
    }
}

void fb_decrement_cursor()
{
    if(fb_cursor == 0)
    {
        fb_row--;
        fb_cursor = 80;
    }
    fb_cursor--;
}

int fb_get_pointer()
{
    return 80 * fb_row + fb_cursor;
}

void fb_new_line()
{
    fb_row++;
    fb_cursor = 0;
}

void fb_backspace(unsigned char fg, unsigned char bg)
{
    fb_decrement_cursor();
    fb_write_cell(fb_get_pointer(), ' ', fg, bg);
    fb_move_cursor(fb_get_pointer());
}

void fb_put_char(char c, unsigned char fg, unsigned char bg)
{
    fb_scroll();
    fb_write_cell(fb_get_pointer(), c, fg, bg);
    fb_increment_cursor();
    fb_move_cursor(fb_get_pointer());
}

void fb_put_string(char* c, unsigned char fg, unsigned char bg)
{
    for(int i = 0; c[i] != 0x00; i++)
    {
        fb_put_char(c[i], fg, bg);
    }
}

void fb_scroll()
{
    if(fb_row >= 25)
    {
        int i;
        for(i = 0*80; i < 24 * 2 * 80; i++)
        {
            fb[i] = fb[i+80*2];
        }

        for(i = 24 * 80; i < 25 * 80; i++)
        {
            fb_write_cell(i, ' ', FB_WHITE, FB_BLACK);
        }
        fb_row = 24;
    }
}