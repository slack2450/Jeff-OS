#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* Colours */
#define FB_BLACK            0x0
#define FB_BLUE             0x1
#define FB_GREEN            0x2
#define FB_CYAN             0x3
#define FB_RED              0x4
#define FB_MAGENTA          0x5
#define FB_BROWN            0x6
#define FB_LIGHT_GREY       0x7
#define FB_DARK_GREY        0x8
#define FB_LIGHT_BLUE       0x9
#define FB_LIGHT_GREEN      0xA
#define FB_LIGHT_CYAN       0xB
#define FB_LIGHT_RED        0xC
#define FB_LIGHT_MAGENTA    0xD
#define FB_LIGHT_BROWN      0xE
#define FB_WHITE            0xF

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    0xE
#define FB_LOW_BYTE_COMMAND     0xF

/** fb_move_cursor
 *  Moves the cursor of the framebuffer to the current position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_write_cell
 *  Writes a character with the given foreground and background to position i
 *  in the frame buffer
 *  
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground colour
 *  @param bg The background colour
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

void fb_clear_screen();
void fb_put_char(char c, unsigned char fg, unsigned char bg);
void fb_put_string(char* c, unsigned char fg, unsigned char bg);
void fb_new_line();
void fb_backspace(unsigned char fg, unsigned char bg);

int fb_cursor;
int fb_row;