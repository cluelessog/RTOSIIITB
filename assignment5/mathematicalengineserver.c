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
}compute ;

int getRes(char *str) {
    int result;
    int first,second;
    char op;
    sscanf(str,"%d %c %d",&first,&op,&second);
    if(op == '+')
    {
    result = first + second;
    }else if(op == '-'){
    result = first - second;
    }else if(op == '/'){
    result = first / second;
    }else{
    result = first * second;
    }
    return result;
 }

int main(){
    int msqid;
    int msgflg = IPC_CREAT | 0644;
    key_t key;
    size_t buflen;
    struct compute mengnrcv;
    key = 1234;
    //getting msg queue id for given key
    if((msqid = msgget(key,msgflg)) == -1){
        perror("msgget");
        exit(1);
    }
    while(1){
    if(msgrcv(msqid,&mengnrcv,MAX,mengnrcv.type,msgflg) == -1){
        perror("msgsnd");
    }
    int res = getRes(mengnrcv.mtext);
    
    //return this result back to client
    printf("\nComputation done, return result back to client\n");
    char result[MAX];
    mengnrcv.type = 1;
    sprintf(result,"%d",res);
    strcpy(mengnrcv.mtext,result);
    buflen = strlen(mengnrcv.mtext) + 1 ;
    if(msgsnd(msqid,&mengnrcv,buflen,msgflg) == -1){
        perror("msgsnd");
    }
 }   
    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(1);
    }
    return 0;
}
