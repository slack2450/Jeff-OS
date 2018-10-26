// we can run things here in C!
#include "fb.h"
#include "isr.h"
#include "descriptor_tables.h"
#include "keyboard.h"

int main()
{

    fb_clear_screen();

    init_descriptor_tables();

    setup_keyboard();

    fb_put_string("Welcome to Jeff OS!", FB_GREEN, FB_BLACK);
    fb_new_line();
    fb_put_string("User@Jeff:~$ ", FB_LIGHT_BLUE, FB_BLACK);

    //char welcomeMessage[] = "Welcome to Jeff OS!";

    //for(int i = 0; i < 19; i++)
    //{
    //    fb_put_char(welcomeMessage[i], FB_GREEN, FB_BLACK);
    //}

    return 0x69;
}