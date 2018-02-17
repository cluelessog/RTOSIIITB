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
    if(msgrcv(msqid,&mengnrcv,MAX,mengnrcv.type,msgflg) == -1){
        perror("msgsnd");
    }
    printf("Expression received is : %s\n",mengnrcv.mtext);
    FILE *fp = fopen("result.txt","w");
    int res = getRes(mengnrcv.mtext);
    fprintf(fp,"%d\n",res);
    fclose(fp);
    return 0;
}
