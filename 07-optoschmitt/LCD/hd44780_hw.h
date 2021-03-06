/*************************************************************************
 Title	:   C include file for the HW defs of for the HD44780U LCD library
            modified for multilines LCD
 Author:    Markus Ermert, Fandi Gunawan
***************************************************************************/
#ifndef HD47880_HW_H
#define HD44780_HW_H

/* change these definitions to adapt setting */

/*Change this to what you need this is an example of 16x2 lcd display */
#define LCD_LINES           2     /* visible lines */
#define LCD_CHARS           8     /* number of char in a row */

/* Change IO setting */

#define LCD_DATA_PIN_D7  PC3	/* arbitrary pin for LCD data line D7 */
#define LCD_DATA_PIN_D6  PC2	/* arbitrary pin for LCD data line D6 */
#define LCD_DATA_PIN_D5  PC1	/* arbitrary pin for LCD data line D5 */
#define LCD_DATA_PIN_D4  PC0	/* arbitrary pin for LCD data line D4 */

#define LCD_DATA_PINR_D7 PINC	/* input pin register for LCD data line D7 */
#define LCD_DATA_PINR_D6 PINC	/* input pin register for LCD data line D6 */
#define LCD_DATA_PINR_D5 PINC	/* input pin register for LCD data line D5 */
#define LCD_DATA_PINR_D4 PINC	/* input pin register for LCD data line D4 */

#define LCD_DATA_DDR_D7 DDRC	/* ddr for LCD data line D7 */
#define LCD_DATA_DDR_D6 DDRC	/* ddr for LCD data line D6 */
#define LCD_DATA_DDR_D5 DDRC	/* ddr for LCD data line D5 */
#define LCD_DATA_DDR_D4 DDRC	/* ddr for LCD data line D4 */

#define LCD_DATA_PORT_D7 PORTC	/* port for LCD data line D7 */
#define LCD_DATA_PORT_D6 PORTC	/* port for LCD data line D6 */
#define LCD_DATA_PORT_D5 PORTC	/* port for LCD data line D5 */
#define LCD_DATA_PORT_D4 PORTC	/* port for LCD data line D4 */

#define LCD_RS_DDR       DDRC   /* ddr for RS line */
#define LCD_RS_PORT      PORTC  /* port for RS line */
#define LCD_RS_PIN       PC6
#define LCD_RW_DDR       DDRC  /* ddr for RW line */
#define LCD_RW_PORT      PORTC  /* port for RW line */
#define LCD_RW_PIN       PC5
#define LCD_E_DDR        DDRC  /* ddr for Enable line */
#define LCD_E_PORT       PORTC  /* port for Enable line */
#define LCD_E_PIN        PC4


/* normally you do not change the following */
#define LCD_LINE_LENGTH  0x40     /* internal line length */
#define LCD_START_LINE1  0x00     /* DDRAM address of first char of line 1 */
#define LCD_START_LINE2  0x40     /* DDRAM address of first char of line 2 */
#define LCD_START_LINE3  0x14     /* DDRAM address of first char of line 3 */
#define LCD_START_LINE4  0x54     /* DDRAM address of first char of line 4 */

#endif //HD44780_HW_H

