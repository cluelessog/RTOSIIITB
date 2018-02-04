#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>
#include<semaphore.h>
sem_t lock;
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
		sem_post(&lock);
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
	//sem_wait(&lock);
	//reinitialising the global variables
	//a = 7,b = 8, c = 9;
	while(1)
	{
	    sem_wait(&lock);
	    a = 7,b = 8, c = 9;
		printf("\nvalue of local variable in thread 2\n");
		printf("\ni = %d\n",i);
		printf("\nj = %d\n",j);
		printf("\nk = %d\n",k);
		printf("\nvalue of global variable in thread 2\n");
		printf("\na = %d\n",a);
		printf("\nb = %d\n",b);
		printf("\nc = %d\n",c);
		sem_post(&lock);
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
	//sem_wait(&lock);
	//reinitialising the global variables
	//a = 10, b = 11 , c = 12;
	while(1)
	{
	    sem_wait(&lock);
	    a = 10, b = 11 , c = 12;
		printf("\nvalue of local variable in thread 3\n");
		printf("\ni = %d\n",i);
		printf("\nj = %d\n",j);
		printf("\nk = %d\n",k);
		printf("\nvalue of global variable in thread 3\n");
		printf("\na = %d\n",a);
		printf("\nb = %d\n",b);
		printf("\nc = %d\n",c);
		sem_post(&lock);
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
 * Here semaphores are used which are signalling and synchronisation mechanisms.
 * sem_wait() makes the caller wait untill the value is greater than 1 and once the condition evaluates to true
 * it allows the thread to access critical section and decrement the value by 1.
 * sem_post() increments the value again by one thereby allowing other threads to access the critical section.
 * In this case we don't see random printing instead the output is synchronised. Only one thread at a time
 * can access the critical section. Other threads are in wait state.
 * It's like talking on a phone booth. When a person enters in a phone booth(thread),he holds the door(lock),then he
* talk to the other person with privacy. Once he is done talking
 * he releases the door (unlocks) thereby allowing other people to use phone booth(other threads).
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
 * http://pages.cs.wisc.edu/~remzi/Classes/537/Fall2008/Notes/threads-semaphores.txt
 */
