/*----------------------------------------------------------------------------
*         ATMEL Microcontroller Software Support  -  ROUSSET  -
*----------------------------------------------------------------------------
* The software is delivered "AS IS" without warranty or condition of any
* kind, either express, implied or statutory. This includes without
* limitation any warranty or condition with respect to merchantability or
* fitness for any particular purpose, or against the infringements of
* intellectual property rights of others.
*----------------------------------------------------------------------------
* File Name           : h64_board.h
* Object              : AT91SAM7S Evaluation Board Features Definition File.
*
* Creation            : JPP   16/Jun/2004
*----------------------------------------------------------------------------
*/
#ifndef h64_board_h_included
#define h64_board_h_included

#include "AT91SAM7S64.h"
#include "libsam7.h"

#define true	1
#define false	0

/*-------------------------------*/
/* SAM7Board Memories Definition */
/*-------------------------------*/
// The AT91SAM7S64 embeds a 16-Kbyte SRAM bank, and 64 K-Byte Flash
// The AT91SAM7S256 embeds a 64-Kbyte SRAM bank, and 256 K-Byte Flash

#define  INT_SRAM           0x00200000
#define  INT_SRAM_REMAP	    0x00000000

#define  INT_FLASH          0x00000000
#define  INT_FLASH_REMAP    0x01000000

#define  FLASH_PAGE_NB		1024
#define  FLASH_PAGE_SIZE	256

#define USB_DP_PUP   (1<<16)
#define USB_DM_PUP   (1<<8)

/*-----------------*/
/* Led Definition  */
/*-----------------*/
#define LED1            AT91C_PIO_PA8
#define LED2            0  /* no second LED */
#define LED_MASK        (LED1|LED2)

/*------------------*/
/* USART Definition */
/*------------------*/
/* SUB-D 9 points J3 DBGU*/
#define DBGU_RXD		AT91C_PA9_DRXD
#define DBGU_TXD		AT91C_PA10_DTXD
#define AT91C_DBGU_BAUD	        115200

#define US_RXD_PIN		AT91C_PA5_RXD0
#define US_TXD_PIN		AT91C_PA6_TXD0
#define US_RTS_PIN		AT91C_PA7_RTS0
#define US_CTS_PIN		AT91C_PA8_CTS0

/*--------------*/
/* Master Clock */
/*--------------*/

#define EXT_OSC         18432000   // External oscillator MAINCK, not actually used
#define MCK             48054841
#define MCKKHz          (MCK/1000)

#endif /* h64_board_h_included */
