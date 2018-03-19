#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>
//global variables
int a,b,c;

void *Thread1Proc()
{	//local variable of thread 1
	int i=50,j=60,k=70;
	printf("\naddress of local variable in thread 1\n");
	printf("\nj = %p\n",&i);
	printf("\nk = %p\n",&j);
	printf("\nl = %p\n",&k);
	printf("\naddress of global variable in thread 1\n");
	printf("\na = %p\n",&a);
	printf("\nb = %p\n",&b);
	printf("\nc = %p\n",&c);
	//reinitialising the global variables
	a = 4,b = 5,c = 6;
	while(1)
	{
		printf("\nvalue of local variable in thread 1\n");
		printf("\ni = %d\n",i);
		printf("\nj = %d\n",j);
		printf("\nk = %d\n",k);
		printf("\nvalue of global variable in thread 1\n");
		printf("\na = %d\n",a);
		printf("\nb = %d\n",b);
		printf("\nc = %d\n",c);
	}
}
void *Thread2Proc()
{   //local variable of thread 2
	int i=80,j=90,k=100;
	printf("\naddress of local variable in thread 2\n");
	printf("\nj = %p\n",&i);
	printf("\nk = %p\n",&j);
	printf("\nl = %p\n",&k);
	printf("\naddress of global variable in thread 2\n");
	printf("\na = %p\n",&a);
	printf("\nb = %p\n",&b);
	printf("\nc = %p\n",&c);
	//reinitialising the global variables
	a = 7,b = 8, c = 9;
	while(1)
	{
		printf("\nvalue of local variable in thread 2\n");
		printf("\ni = %d\n",i);
		printf("\nj = %d\n",j);
		printf("\nk = %d\n",k);
		printf("\nvalue of global variable in thread 2\n");
		printf("\na = %d\n",a);
		printf("\nb = %d\n",b);
		printf("\nc = %d\n",c);
	}
}
void *Thread3Proc()
{   //local variable of thread 3
	int i=110,j=120,k=130;
	printf("\naddress of local variable in thread 3\n");
	printf("\nj = %p\n",&i);
	printf("\nk = %p\n",&j);
	printf("\nl = %p\n",&k);
	printf("\naddress of global variable in thread 3\n");
	printf("\na = %p\n",&a);
	printf("\nb = %p\n",&b);
	printf("\nc = %p\n",&c);
	//reinitialising the global variables
	a = 10, b = 11 , c = 12;
	while(1)
	{
		printf("\nvalue of local variable in thread 2\n");
		printf("\ni = %d\n",i);
		printf("\nj = %d\n",j);
		printf("\nk = %d\n",k);
		printf("\nvalue of global variable in thread 2\n");
		printf("\na = %d\n",a);
		printf("\nb = %d\n",b);
		printf("\nc = %d\n",c);
	}
}
int main()
{	//initialising the global variables
	a = 1, b = 2, c = 3;
	//creating three thread variables
	pthread_t thread1,thread2,thread3;
	//creating the threads
	pthread_create(&thread1,NULL,Thread1Proc,NULL);
	pthread_create(&thread2,NULL,Thread2Proc,NULL);
	pthread_create(&thread3,NULL,Thread3Proc,NULL);
	/*wait until threads are executed. If not used, program terminates as soon as main completes its execution
	 *But here all threads are in infinite loop, they will never terminate unless we kill them.
	 */
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);


}

/* Observations and conclusions
 * There is  no specific order for printing the addresses and values of the global and local variables.
 * The reason is, threads run in a concurrent manner i.e they run in parallel. So the order of execution
 * for threads is not same everytime. Also the output is different everytime because values set for global
 * variable by one thread, may be shown by other thread. All threads have the same copy of global variables
 * that's why the global address is same for all threads. So if one thread modifies the value, it will be
 * reflected in other thread. However they don't share local variables. Each thread has it's own set of
 * local variables which can't be accessed by the other threads, hence the address of local variable is different
 * for each thread. The global variables are stored in heap whereas the local variables are stored in threads'
 * own stack.
 */

/* References
 * https://stackoverflow.com/questions/2483041/what-is-the-difference-between-fork-and-thread
 * https://unix.stackexchange.com/questions/207918/what-does-it-mean-fork-will-copy-address-space-of-original-process
 * https://stackoverflow.com/questions/41632073/do-threads-share-local-variables
 * https://cs.stackexchange.com/questions/48345/what-threads-share-in-general
 * https://stackoverflow.com/questions/7387620/does-local-variable-in-thread-function-have-separe-copy-according-to-thread
 */


