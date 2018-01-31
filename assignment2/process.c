#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<assert.h>
/* Declaration of the global variables */
int g_first, g_second, g_third;
/* function which is being called by the child processes */
void printVariable() {
	int j, k, l;
	/* printing address of local variable */
	printf("\nj = %p\n", &j);
	printf("\nk = %p\n", &k);
	printf("\nl = %p\n", &l);
	/* printing address of global variables */
	printf("\ng_first = %p\n", &g_first);
	printf("\ng_second = %p\n", &g_second);
	printf("\ng_third = %p\n", &g_third);
}
void main() {
	/* Declaration of the local variables */
	int a, b, c;
	/* printing address of local variable */
	printf("\nPrinting addresses from main process\n");
	printf("\na = %p\n",&a);
	printf("\nb = %p\n", &b);
	printf("\nc = %p\n", &c);
	/* printing address of global variables */
	printf("\ng_first = %p\n", &g_first);
	printf("\ng_second = %p\n", &g_second);
	printf("\ng_third = %p\n", &g_third);
	/* creating a file pointer to write into scr.sh */
	FILE *fp = fopen("scr.sh","w+");
	fprintf(fp,"%s\n","#/bin/bash");
	/* creating three child process */
	pid_t childOne, childTwo, childThree;
	childOne = fork();
	if (childOne >= 0) //fork successful
	{
		//childOne
		if (childOne == 0) {
			printf("\nprinting addresses from childOne\n");
			printVariable();
			while (1) {}
		} else {

			childTwo = fork();
			if (childTwo >= 0) //fork successful
			{
				if (childTwo == 0) {
					printf("\nprinting addresses from childTwo");
					printVariable();
					while (1) {}
				} else {

					childThree = fork();
					if (childThree >= 0) //fork successful
					{
						if (childThree == 0) {
							printf("\nprinting addresses from childThree");
							printVariable();
							while (1) {}

						} else {
							/* getting pid of third child and writing into the file */
							fprintf(fp,"kill -9 %d\n",childThree);

						}

					}else{
						printf("\nFork was unsuccessful\n");
					}
					/* getting pid of second child and writing into the file */
					fprintf(fp,"kill -9 %d\n",childTwo);
				}
				/* getting pid of first child and writing into the file */
				fprintf(fp,"kill -9 %d\n",childOne);
				/* writing the pid of the parent into the file */
				fprintf(fp,"kill -9 %d\n",getpid());
				fclose(fp);
				/* copying the content of scr.sh into kill.sh to avoid text file busy error */
				FILE *fd = fopen("scr.sh","r");
				FILE *fw = fopen("kill.sh","w+");
				char ch[100];
				while(!(feof(fd))){
					fgets(ch,100,fd);
					fprintf(fw,"%s",ch);
				}
				/* this command removes the kill.sh after it is being executed */
				fputs("rm kill.sh",fw);
				fclose(fd);
				fclose(fw);
				/* removing scr.sh as it is no longer needed */
				system("rm scr.sh");
				/*giving execution permission */
				system("chmod +x kill.sh");
				while (1) {}

			}else{
				printf("\nFork was unsuccessful\n");
			}

		}
	}else{
		printf("\nFork was unsuccessful\n");
	}

}
/* Observations and Conclusions */

/*  All of the child process were printing the same local and global address.This happens due to virtual addresses.
 *  The child and parent have the same virtual address but different physical address. This address translation from
 *  virtual to physical is done by Memory Management unit. When we execute ./a.out, each child process is assigned the
 *  same virtual address. Each process thinks that it has the entire machine to itself. So parent process’ pages are
 *  shared among them and not copied. Linux uses a copy on write (COW) mechanism. With this technique, when a fork
 *  occurs, parent process’ pages are not copied for the child process, instead they are shared between child and
 *  parent process. Whenever a process wants to modify a page, a separate copy of that page alone is made for that
 *  process. The process will then use newly copied page for future references rather than the shared one. This is
 *  called copy on write since the page is copied when one process writes to it.
 *  Global address is same everywhere because they are not shared in any way which is visible to the programmer.
 *  The process can modify their own copy of global variable independently and they can change without any noticeable
 *  effect on the other process.
 */


/* References
 * https://stackoverflow.com/questions/4298678/after-forking-are-global-variables-shared
 * https://stackoverflow.com/questions/13185917/address-space-after-fork-call
 * https://stackoverflow.com/questions/27486873/fork-system-call-and-memory-space-of-the-process
 * https://stackoverflow.com/questions/4594329/difference-between-the-address-space-of-parent-process-and-its-child-process-in
 *
 */


