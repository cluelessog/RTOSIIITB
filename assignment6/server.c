#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
#define PORT 32771
int newsd = 0,n=0;
char msg[1024];
void *snd()
{
  while(1)
  {
  fgets(msg,1024, stdin);
  write(newsd, msg, strlen(msg)+1);
  }
}
char buffer[1024];
void *rcv()
{
  while(1)
  {
  while((n = read(newsd, buffer, sizeof(buffer)-1)) > 0)
    {
      buffer[n] = 0;
      printf("Client:");
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
    struct sockaddr_in server,client;
    //server socket descriptor
    int sd = socket(AF_UNIX,SOCK_STREAM,0);
    //address family
    server.sin_family = AF_UNIX;
    //port in network
    server.sin_port = htons(PORT);
    //internet address in network
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sd,(struct sockaddr *)(&server),sizeof(server));
    //listening
    listen(sd,1);
    int size = sizeof(client);
    newsd = accept(sd,(struct sockaddr *)&client,(socklen_t*)&size);
    pthread_t th1, th2;
    pthread_create(&th1, NULL, snd, NULL);
    pthread_create(&th2, NULL, rcv, NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    close(newsd);
    close(sd);
    return 0;

}
