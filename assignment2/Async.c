#include <errno.h>
#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
// defining GPIO pins

#define GPIO_1  0  //physical pin 11
#define	GPIO_2	1  //physical PIN 12
#define	GPIO_3	2  //physical PIN 13
#define	GPIO_4	3  //physical PIN 15



int main (void)
{
	wiringPiSetup () ;
	//configuring pins in input mode
	pinMode (GPIO_1, INPUT) ;
	pinMode (GPIO_2, INPUT) ;
	pinMode (GPIO_3, INPUT) ;
	pinMode (GPIO_4, INPUT) ;
	//declaring variable to store pin status
	int gpio_1,gpio_2,gpio_3,gpio_4;
	//assigning status
	while(1)
	{
		gpio_1 = digitalRead(GPIO_1);
		gpio_2 = digitalRead(GPIO_2);
		gpio_3 = digitalRead(GPIO_3);
		gpio_4 = digitalRead(GPIO_4);
		printf("Received Value is : %d\n",(8*gpio_4 + 4*gpio_3 + 2*gpio_2 + gpio_1));
		delay(500);
	}
	return 0 ;
}
/* References
 * http://www.science.smith.edu/dftwiki/index.php/Tutorial:_Interrupt-Driven_Event-Counter_on_the_Raspberry_Pi
 * https://github.com/ngs/wiringPi/blob/master/examples/isr.c
 * GPIO_1 is the LSB and GPIO_4 is the MSB on raspberry pi.
 * On arduino PIN 8 to 11 are used out of which 8 is the LSB, connected to
 * GPIO_1 and 11 is MSB, connected to GPIO_4. PIN 9 is connected to GPIO_2 and
 * PIN 10 is connected to GPIO_3.
 */

