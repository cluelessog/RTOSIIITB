#include <errno.h>
#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
//to trigger interrupt
#define	INTR	0  //physical PIN 11
//defining GPIO pins 
#define	GPIO_5	24  //physical PIN 35
#define	GPIO_6	27  //physical PIN 36
#define	GPIO_7	25  //physical PIN 37
#define	GPIO_8	28  //physical PIN 38

//called everytime there is an event
void my_ISR(void)
{
	printf("Received Value is : %d\n",(8*digitalRead(GPIO_8) + 4*digitalRead(GPIO_7) + 2*digitalRead(GPIO_6) + digitalRead(GPIO_5)));

}

int main (void)
{
	int myCounter = 0;
	wiringPiSetup () ;
	//configuring pins in input mode
	pinMode (GPIO_5, INPUT) ;
	pinMode (GPIO_6, INPUT) ;
	pinMode (GPIO_7, INPUT) ;
	pinMode (GPIO_8, INPUT) ;
	//configuring the INTR pin
	pinMode (INTR,INPUT);

	//condition to trigger interrupt service routine on Falling Edge
	if(wiringPiISR(digitalRead(INTR),INT_EDGE_FALLING,&my_ISR)<0)
	{
		fprintf(stderr,"Unable to setup ISR: %s\n",strerror(errno));
		return 1;
	}

	while(1){}

	return 0 ;
}
/* References
 * http://www.science.smith.edu/dftwiki/index.php/Tutorial:_Interrupt-Driven_Event-Counter_on_the_Raspberry_Pi
 * https://github.com/ngs/wiringPi/blob/master/examples/isr.c
 * GPIO_5 is the LSB and GPIO_8 is the MSB on raspberry pi.
 * On arduino PIN 8 to 11 are used out of which 8 is the LSB, connected to
 * GPIO_5 and 11 is MSB, connected to GPIO_8. PIN 9 is connected to GPIO_6 and
 * PIN 10 is connected to GPIO_7 
 * Interrupt was applied at INTR which is the interrupt pin, using PIN 12 on arduino.
 * Whenever state change from logic 1 to logic 0, the interrupt my_ISR was serviced.
 * /
