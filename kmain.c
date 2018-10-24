// we can run things here in C!
#include "fb.h"

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

    char welcomeMessage[] = "Welcome to Jeff OS!";

    for(int i = 0; i < 19; i++)
    {
        fb_write_cell(i, welcomeMessage[i], FB_GREEN, FB_BLACK);
    }

    return 0x69;
}