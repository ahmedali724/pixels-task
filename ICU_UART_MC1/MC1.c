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
#include "HAL/ULTRASONIC_SENSOR/ultrasonic_sensor.h" /* To use ULTRASONIC SENSOR functions */
#include "MCAL/GPIO/gpio_private.h"/* To use SREG register definition */
#include "MCAL/UART/uart.h" /* To use UART functions */

#define READY_TO_SEND	0x69

int main(void)
{
	/* Configuration and initialization functions */
	uint16 distance = 0;
	/* Enable global interrupt */
	SREG_REG.Bits.I_Bit = 1;
	/* select the configuration of UART */
	UART_ConfigType UART_config =
	{ ASYNCHRONOUS, DISABLED_PARITY, STOP_1_BIT, DATA_8_BIT, BAUD_RATE_9600 };

	/* passing the configuration to initialization function of UART */
	UART_init(&UART_config);
	Ultrasonic_init();
	while (UART_recieveByte() != READY_TO_SEND)
		;
	while (1)
	{
		/* Get the distance value from the sensor */
		distance = Ultrasonic_readDistance();
		/* Send the distance value to MC2 to display it on LCD */
		UART_sendByte(distance);
	}
}
