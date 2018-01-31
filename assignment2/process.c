#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <sys/wait.h> 
#include <stdlib.h>
#include<assert.h>
//global variable declaration
int g_first, g_second, g_third;
void printVariable() {
	int j, k, l;
	//print address of local variable
	printf("\n%p\n", &j);
	printf("%p\n", &k);
	printf("%p\n", &l);
	//print address of global variables
	printf("%p\n", &g_first);
	printf("%p\n", &g_second);
	printf("%p\n", &g_third);
}
void main() {
	//local variable declaration
	int a, b, c;
	//print address of local variable
	printf("Printing addresses from main process\n");
	printf("%p\n",&a);
	printf("%p\n", &b);
	printf("%p\n", &c);
	//print address of global variables
	printf("%p\n", &g_first);
	printf("%p\n", &g_second);
	printf("%p\n", &g_third);
    FILE *fp = fopen("scr.sh","w+");
    fprintf(fp,"%s\n","#/bin/bash");
	//creating three child processes
	pid_t childOne, childTwo, childThree;
	childOne = fork();
	if (childOne >= 0) //fork successful
	{
		//childOne
		if (childOne == 0) {
			printf("printing addresses from childOne\n");
			printVariable();
			while (1) {}
		} else {
			//parent one

			childTwo = fork();
			if (childTwo >= 0) //fork successful
			{
				if (childTwo == 0) {
					printf("printing addresses from childTwo");
					printVariable();
					while (1) {}
				} else {

					childThree = fork();
					if (childThree >= 0) //fork successful
					{
						if (childThree == 0) {
							printf("printing addresses from childThree");
							printVariable();
							while (1) {}

						} else {
                            fprintf(fp,"kill -9 %d\n",childThree);
							//parent three
								//	while(1)
								//	{
							// printf("p3");
								//	}
						}

					}
                    fprintf(fp,"kill -9 %d\n",childTwo);
					//parent two
				//	while(1)
				//	{
					// printf("p2");
				//	}
				}
                 fprintf(fp,"kill -9 %d\n",childOne);
                 fprintf(fp,"kill -9 %d\n",getpid());
                 fclose(fp);
                 FILE *fd = fopen("scr.sh","r");
                 FILE *fw = fopen("kill.sh","w+");
                 char ch[100];
                 while(!(feof(fd))){
                 fgets(ch,100,fd);
                 fprintf(fw,"%s",ch);
                 }
                 fputs("rm kill.sh",fw);
                 fclose(fd);
                 fclose(fw);
                 system("rm scr.sh");
                 system("chmod +x kill.sh");
				//parent one
				while (1) {}

			}

		}
	}

}


