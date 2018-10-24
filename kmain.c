// we can run things here in C!
#include "fb.h"
#include "idt.h"

void clear_screen()
{
    for(int i = 0; i < 80 * 25; i++)
    {
        fb_write_cell(i, 0, 0, 0);
    }
}

int main()
{
    clear_screen();

    idt_init();

    char welcomeMessage[] = "Welcome to Jeff OS!";

    for(int i = 0; i < 19; i++)
    {
        fb_write_cell(i, welcomeMessage[i], FB_GREEN, FB_BLACK);
    }

    int bit;
    while(1 == 1)
    {
        if(bit == 1)
        {
            bit = 0;
            fb_write_cell(20, ' ', FB_GREEN, FB_GREEN);
        }
        else
        {
            bit = 1;
            fb_write_cell(20, ' ', FB_BLACK, FB_BLACK);
        }
    }

    return 0x69;
}