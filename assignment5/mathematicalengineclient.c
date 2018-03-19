#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 128
typedef struct compute
{
    long type;
    char mtext[MAX];
}compute;

int main(){
    int msqid;
    int msgflg = IPC_CREAT | 0644;
    key_t key;
    size_t buflen;
    struct compute mengn;
    key = 1234;
    //getting msg queue id for given key
    if((msqid = msgget(key,msgflg)) == -1){
        perror("msgget");
        exit(1);
    }
    mengn.type = 1;
    while(1){
    printf("\nEnter the Mathematical expression \n");
    fgets(mengn.mtext,MAX,stdin);
    buflen = strlen(mengn.mtext) + 1 ;
    if(msgsnd(msqid,&mengn,buflen,msgflg) == -1){
        perror("msgsnd");
    }
    
    //get result back from server
    if(msgrcv(msqid,&mengn,MAX,mengn.type,msgflg) == -1){
        perror("msgsnd");
    }
    printf("\nThe result of computation is %s\n",mengn.mtext);
    }
    return 0;
}
