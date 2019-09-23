#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>

#define LISTENQ 5
#define MAXLINE 512

int main(){

    int listenfd,connfd;
    socklen_t len;
    struct sockaddr_in servaddr,cliaddr;
    char buff[MAXLINE];
    time_t ticks;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0){
        perror("listen");
        exit(-1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_
    return 0;
}

