#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    //pipe file descriptors
    int fd[2];
    //create pipe
    if(pipe(fd) == -1){
        printf("pipe unsuccessful");
    }
    
    switch(fork()){
    
        case -1:
            printf("fork unsuccessful");
        case 0:
            close(fd[0]);//closing the read end
            //take control of the stdout (use fd[1], close(1))
            dup2(fd[1],1);
            execlp("ls","ls","-l",(char *)NULL);//writes to pipe
            close(fd[1]);//closing the write end
            break;
        default:
            close(fd[1]);//closing the write end
            //takes control of the stdin(use fd[0],close(0))
            dup2(fd[0],0);
            execlp("wc","wc","-l",(char *)NULL);//reads from pipe
            close(fd[0]);//closing the read end
            break;
    }
    exit(EXIT_SUCCESS);
}
