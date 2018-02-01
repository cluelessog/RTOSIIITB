#include <errno.h>
#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
static volatile int globalCounter = 0;
//to trigger interrupt
#define	INTR	0  //physical PIN 11
// for async mode
#define GPIO_1  5 //physical pin 18
#define	GPIO_2	1  //physical PIN 12
#define	GPIO_3	2  //physical PIN 13
#define	GPIO_4	3  //physical PIN 15

//for push mode 
#define	GPIO_5	24  //physical PIN 35
#define	GPIO_6	27  //physical PIN 36
#define	GPIO_7	25  //physical PIN 37
#define	GPIO_8	28  //physical PIN 38
//called everytime there is an event
void my_ISR(void)
{
  ++globalCounter;
  printf("gpi0_5 : %d\n",digitalRead(GPIO_5));
  printf("gpi0_6 : %d\n",digitalRead(GPIO_6));
  printf("gpi0_7 : %d\n",digitalRead(GPIO_7));
  printf("gpi0_8 : %d\n",digitalRead(GPIO_8));
}

int main (void)
{
  int myCounter = 0;
  wiringPiSetup () ;
  //configuring pins in input mode(async mode)
  pinMode (GPIO_1, INPUT) ;
  pinMode (GPIO_2, INPUT) ;
  pinMode (GPIO_3, INPUT) ;
  pinMode (GPIO_4, INPUT) ;
  //configuring pins in input mode(pull mode)
  pinMode (GPIO_5, INPUT) ;
  pinMode (GPIO_6, INPUT) ;
  pinMode (GPIO_7, INPUT) ;
  pinMode (GPIO_8, INPUT) ;
  //configuring the INTR pin
  pinMode (INTR,INPUT);
  //printing the status for async mode
  printf("gpi0_1 : %d\n",digitalRead(GPIO_1));
  printf("gpi0_2 : %d\n",digitalRead(GPIO_2));
  printf("gpi0_3 : %d\n",digitalRead(GPIO_3));
  printf("gpi0_4 : %d\n",digitalRead(GPIO_4));	
 
  //condition to trigger interrupt service routine
  if(wiringPiISR(digitalRead(INTR),INT_EDGE_FALLING,&my_ISR)<0)
  {
	  fprintf(stderr,"Unable to setup ISR: %s\n",strerror(errno));
	  return 1;
  }
  
  while(1)
  {
	while(myCounter == globalCounter)
	{
	delay(100);
	}
	printf("\nglobalCounter =  %d \n",globalCounter);
	myCounter = globalCounter;
  }

  return 0 ;
}
/* References
 * http://www.science.smith.edu/dftwiki/index.php/Tutorial:_Interrupt-Driven_Event-Counter_on_the_Raspberry_Pi
 * https://github.com/ngs/wiringPi/blob/master/examples/isr.c
 */
