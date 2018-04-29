//server code
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#define BUFSIZE 18000
#define PORT 6542  
#define RATE 6800 

//socket variables
int sd;
struct sockaddr_in server;
int addrlen = sizeof(server);
//record variables
pa_simple *s = NULL;
//playback varibale
pa_simple *s1 = NULL;
uint8_t rcvBuffer[BUFSIZE];
uint8_t sendBuffer[BUFSIZE];
/* A simple routine calling UNIX write() in a loop */
static ssize_t loop_write(int fd, const void*data, size_t size) {
    ssize_t ret = 0;
    while (size > 0) {
        ssize_t r;
        if ((r = sendto(fd, data, size, 0, (struct sockaddr *)&server, addrlen)) < 0)
            return r;
        if (r == 0)
            break;
        ret += r;
        data = (const uint8_t*) data + r;
        size -= (size_t) r;
    }
    return ret;
}
void pulseaudiorecord_end()
{
    if (s!=NULL){
        pa_simple_free(s);
        s= NULL;
    }
}
void pulseaudiorecord_init()
{
    int error;
    /* The sample type to use */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = RATE,
        .channels = 2
    };
    /* Create the recording stream */
    if (!(s = pa_simple_new(NULL, "FooApp", PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        pulseaudiorecord_end();
    }
    
}
void pulseaudiorecord_begin()
{
    int error;
    while(1)
    {
        printf("\n Recording the audio");
        if (pa_simple_read(s, sendBuffer, BUFSIZE, &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
            pulseaudiorecord_end();
        }
        printf("\n Writing to socket");
        /* And write it to STDOUT */
        if ((loop_write(sd, sendBuffer, BUFSIZE)) != BUFSIZE) {
            fprintf(stderr, __FILE__": write() failed: %s\n", strerror(errno));
            pulseaudiorecord_end();
        }
    }
    
    
}

void pulseaudioplayback_end()
{
    if (s1!=NULL){
        pa_simple_free(s1);
        s1= NULL;
    }
}
void pulseaudioplayback_init()
{   int error;
    /* The Sample format to use */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = RATE,
        .channels = 2
    };
    
    
    
    /* Create a new playback stream */
    if (!(s1 = pa_simple_new(NULL, "FooApp", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        pulseaudioplayback_end();
    }
}

void pulseaudioplayback_begin()
{   
    int error;
    while(1)
    {   
        ssize_t r;
        /* Read some data ... */
        printf("\n reading audio");
        if ((r = recvfrom(sd, rcvBuffer, BUFSIZE,0,(struct sockaddr *)&server, &addrlen)) <= 0) {
            if (r == 0) /* EOF */
                break;
            fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
            pulseaudioplayback_end();
        }
        printf("\n playing the audio");
        /* ... and play it */
        if (pa_simple_write(s1, rcvBuffer,BUFSIZE, &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
            pulseaudioplayback_end();
        }
    }
    /* Make sure that every single sample was played */
    if (pa_simple_drain(s1, &error) < 0) {
        fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));
        pulseaudioplayback_end();
    }
    
    
    
}
void *snd()
{
    pulseaudiorecord_init();
    pulseaudiorecord_begin();
    pulseaudiorecord_end();
    
}
void *rcve()
{
    pulseaudioplayback_init();
    pulseaudioplayback_begin();
    pulseaudioplayback_end();    
}
int main()
{   
    pthread_t SendT, RecvT;
    //server socket descriptor
    if ((sd=socket(AF_INET, SOCK_DGRAM,0)) == -1)
    {
        printf("\n socket fail");
        perror("error :");
    }
    printf("\n socket created");
    //address family
    server.sin_family = AF_INET;
    //port in network
    server.sin_port = htons(PORT);
    //internet address in network
    server.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(sd,(struct sockaddr *)(&server),sizeof(server)) < 0)
    {
        printf("\n bind fail");
        perror(":");
    }
    printf("\n bind done");
   
    recvfrom(sd, rcvBuffer, BUFSIZE,0,(struct sockaddr *)&server, &addrlen);
    pthread_create(&RecvT,NULL,rcve,NULL);
    pthread_create(&SendT,NULL,snd,NULL);
    pthread_join(RecvT,NULL);
    pthread_join(SendT,NULL);  
    pulseaudiorecord_end();
    pulseaudioplayback_end();
    close(sd);
}
