#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SHMSZ 4*sizeof(char)
#define MAX 128

int main(){
    char *str;
    int shmid;
    key_t key;

  
  switch(fork()){
  
    case -1:
        printf("fork unsuccessful");
        break;
    case 0:
        key  = ftok(".",'a');
        if ((shmid = shmget(key, SHMSZ, 0666 | IPC_CREAT)) < 0) {
            perror("shmget");
            exit(1);
        }
        if ((str = shmat(shmid, NULL, 0)) == (char *) -1) {
            perror("shmat");
            exit(1);
        }
        printf("Write data : \n");
        fgets(str,MAX,stdin);
        printf("Data written, sending\n");
        //detach the shared memory
        shmdt(str);
        break;
    default:
        key = ftok(".",'a');
        if ((shmid = shmget(key, SHMSZ, 0666 | IPC_CREAT)) < 0) {
            perror("shmget");
            exit(1);
        }
        if ((str = shmat(shmid, NULL, 0)) == (char *) -1) {
            perror("shmat");
            exit(1);
        }
        wait(NULL);
        printf("Data received : %s\n",str);
        //detach the shared memory
        shmdt(str);
        //destroy the shared memory
        shmctl(shmid,IPC_RMID,NULL);
        break;
         
  
  }
    
}
