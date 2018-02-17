#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#define PORT 32771
int main(){
    struct sockaddr_in client;
    //client socket descriptor
    int sd = socket(AF_UNIX,SOCK_STREAM,0);
    char buffer[1024]; //to store server msg
    char msg[1024];
    //address family
    client.sin_family = AF_UNIX;
    //port in network
    client.sin_port = htons(PORT);
    //internet address in network
    client.sin_addr.s_addr = INADDR_ANY;
    connect(sd,(struct sockaddr *)(&client),sizeof(client));

    //setting up connection
    while(1)
    {   //sending to client
        fgets(msg,1024,stdin);
        write(sd,msg,strlen(msg)+1);
        //receiving from server
        read(sd,buffer,sizeof(buffer));
        printf("Server: %s",buffer);
    }


}
