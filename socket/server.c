#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#define PORT 32771
int main(){
    struct sockaddr_in server,client;
    //server socket descriptor
    int sd = socket(AF_UNIX,SOCK_STREAM,0);
    //accept socket descriptor
    int newsd; //for accept
    char buffer[1024]; //to store server msg
    char msg[1024];
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
    while(1)
    {   
        //receiving from client
        read(newsd,buffer,sizeof(buffer));
        printf("Client: %s",buffer);
        //sending back to client
        fgets(msg,1024,stdin);
        write(newsd,msg,strlen(msg)+1);
    }


}
