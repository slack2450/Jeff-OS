#include "fb.h"

char *fb = (char *) 0x000B8000;
int row = 0;
int cursor = 0;

void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

short fb_get_index()
{
    return row * 80 + cursor;
}

void fb_increment_index()
{
    cursor++;
    if(row % 80 == 0)
    {
        row++;
        cursor=0;
    }
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    i*=2;
    fb[i] = c;
    fb[i+1] = (fg & 0x0F) | ((bg & 0x0F) << 4);
}

void fb_clear_screen()
{
    row = 0;
    cursor = 0;
    for(int i = 0; i < 80 * 25; i++)
    {
        fb_write_cell(i, ' ', FB_BLACK, FB_BLACK);
    }
}

void fb_put_char(char c, unsigned char fg, unsigned char bg)
{
    fb_write_cell(fb_get_index(), c, fg, bg);
    fb_increment_index();
}

void fb_put_string(char* c, unsigned char fg, unsigned char bg)
{
    int i = 0;
    while(c[i])
    {
        fb_put_char(c[i], fg, bg);
        i++;
    }
}