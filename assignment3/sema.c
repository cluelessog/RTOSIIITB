#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

sem_t sem;
int global_var = 0;
int main(){
    
    sem_init(&sem,0,0);
    
    switch(fork()){
  
    case -1:
        printf("fork unsuccessful");
        break;
    case 0:
        sem_wait(&sem);
        printf("\nglobal var : %d\n",global_var);
        sem_post(&sem);
        break;
    default:
        
        global_var = 1;
        
        wait(NULL);
        break;
         
  
  }
    
}
