#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "usart.h"
/*
 * INSTRUCTIONS
 */
#define INSTR_WRITE 	0x03


/*
 * ID
 */
#define ID 0xFE

/*
 * Reserved
 */
#define RESERVED 0x00

/*
 * HEADER
 */
#define HEADER0 0xFF
#define HEADER1 0xFF
#define HEADER2 0xFD

/*
 * LED COLORS
 */
#define OFF 0x00
#define RED 0x01
#define GREEN 0x02
#define YELLOW 0x03
#define BLUE 0x04
#define PURPLE 0x05
#define CYAN 0x06
#define WHITE 0x07



void servo();
void clignote();
void close();
void open();
void speed();
