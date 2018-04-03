#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
#define PORT 32771
int sd = 0,n = 0;
char msg[1024];
void *snd()
{
  while(1)
  {
  fgets(msg,1024, stdin);
  write(sd, msg, strlen(msg)+1);
  }
}
char buffer[1024];
void *rcv()
{
  while(1)
  {
  while((n = read(sd, buffer, sizeof(buffer)-1)) > 0)
    {
      buffer[n] = 0;
      printf("Server:");
      if(fputs(buffer, stdout) == EOF)
    {
      printf("\n Error : Fputs error");
    }
   }

  if( n < 0)
    {
      printf("\n Read Error \n");
    }
  }
}
int main(){
    struct sockaddr_in client;
    //client socket descriptor
    sd = socket(AF_UNIX,SOCK_STREAM,0);
    //address family
    client.sin_family = AF_UNIX;
    //port in network
    client.sin_port = htons(PORT);
    //internet address in network
    client.sin_addr.s_addr = INADDR_ANY;
    connect(sd,(struct sockaddr *)(&client),sizeof(client));

    //setting up connection
    pthread_t th1, th2;
    pthread_create(&th1, NULL, snd, NULL);
    pthread_create(&th2, NULL, rcv, NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    close(sd);
  return 0;
}
