#define SCAN_CODE_BACKSPACE         0x0E
#define SCAN_CODE_ENTER             0x1C
#define SCAN_CODE_L_SHIFT_DOWN      0x2A
#define SCAN_CODE_L_SHIFT_UP        0xAA

#define KEYBOARD_INPUT_BUFFER_SIZE  0xFF

#include "common.h"
#include "descriptor_tables.h"
#include "fb.h"
#include "isr.h"

unsigned char read_scan_code(void);

void keyboard_input_buffer_push(char c);

int keyboard_input_buffer_space();

void keyboard_input_buffer_clear();

void keyboard_input_buffer_pop();

void keyboard_callback(registers_t regs);

void setup_keyboard(void);