/*
 ============================================================================
 Name        : main.c
 Module Name : APP
 Author      : Ahmed Ali
 Date        : 12 Oct 2023
 Description : The main function
 ============================================================================
 */

#include "HAL/LCD/lcd.h" /* To use LCD functions */
#include "MCAL/GPIO/gpio_private.h"/* To use SREG register definition */
#include "MCAL/UART/uart.h" /* To use UART functions */

#define READY_TO_RECIEVE	0x69

int main(void)
{
	/* Configuration and initialization functions */
	uint16 distance = 0;
	/* select the configuration of UART */
	UART_ConfigType UART_config =
	{ ASYNCHRONOUS, DISABLED_PARITY, STOP_1_BIT, DATA_8_BIT, BAUD_RATE_9600 };

	/* passing the configuration to initialization function of UART */
	UART_init(&UART_config);
	LCD_init();
	LCD_displayString("Distance=    cm");
	UART_sendByte(READY_TO_RECIEVE);
	while (1)
	{
		distance = UART_recieveByte();
		LCD_moveCursor(0, 10);
		/* To ensure that the third digit in numbers less than 100 is not printed */
		LCD_intgerToString(distance);
		if (distance < 100)
		{
			LCD_displayCharacter(' ');
		}
		/* To ensure that the second digit in numbers less than 10 is not printed */
		else if (distance < 10)
		{
			LCD_displayString("  ");
		}
	}
}
