#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>
//global variables
int a,b,c;

void *Thread1Proc()
{
    int i=50,j=60,k=70;
    printf("address of local variable in thread 1\n");
    printf("%p\n",&i);
    printf("%p\n",&j);
    printf("%p\n",&k);
    printf("address of global variable in thread 1\n");
    printf("%p\n",&a);
    printf("%p\n",&b);
    printf("%p\n",&c);
    while(1)
    {
        printf("value of local variable in thread 1\n");
        printf("%d\n",i);
        printf("%d\n",j);
        printf("%d\n",k);
        printf("value of global variable in thread 1\n");
        printf("%d\n",a);
        printf("%d\n",b);
        printf("%d\n",c);
       // a = 4,b = 5,c = 6;
    }
        a = 4,b = 5,c = 6;
}
void *Thread2Proc()
{   
    int i=80,j=90,k=100;
    printf("address of local variable in thread 2\n");
    printf("\n%p\n",&i);
    printf("%p\n",&j);
    printf("%p\n",&k);
    printf("address of global variable in thread 2\n");
    printf("%p\n",&a);
    printf("%p\n",&b);
    printf("%p\n",&c);
    while(1)
    {
        printf("value of local variable in thread 2\n");
        printf("%d\n",i);
        printf("%d\n",j);
        printf("%d\n",k);
        printf("value of global variable in thread 2\n");
        printf("%d\n",a);
        printf("%d\n",b);
        printf("%d\n",c);
       // a = 7,b = 8, c = 9;
    }
        a = 7,b = 8, c = 9;
}
void *Thread3Proc()
{   
    int i=110,j=120,k=130;
    printf("address of local variable in thread 3\n");
    printf("\n%p\n",&i);
    printf("%p\n",&j);
    printf("%p\n",&k);
    printf("address of global variable in thread 3\n");
    printf("%p\n",&a);
    printf("%p\n",&b);
    printf("%p\n",&c);
    while(1)
    {
        printf("value of local variable in thread 3\n");
        printf("%d\n",i);
        printf("%d\n",j);
        printf("%d\n",k);
        printf("value of global variable in thread 3\n");
        printf("%d\n",a);
        printf("%d\n",b);
        printf("%d\n",c);
        //a = 10, b = 11 , c = 12;
    }
        a = 10, b = 11 , c = 12;
}
int main()
{
    a = 1, b = 2, c = 3;
    pthread_t thread1,thread2,thread3;
    pthread_create(&thread1,NULL,Thread1Proc,NULL);
    pthread_create(&thread2,NULL,Thread2Proc,NULL);
    pthread_create(&thread3,NULL,Thread3Proc,NULL);
    sleep(1);
    //pthread_join(thread1,NULL);
    //pthread_join(thread2,NULL);
    //pthread_join(thread3,NULL);


}
