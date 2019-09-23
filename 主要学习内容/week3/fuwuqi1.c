#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;

#define SERVER_PORT  5050               //端口号
#define SERVER_IP    "192.168.3.105"    //服务器ip
#define QUEUE_SIZE   5                  //所监听端口队列大小

int main(int argc, char *argv[])
{
    //创建一个套接字，并检测是否创建成功
    int sockSer;                        
    sockSer = socket(AF_INET, SOCK_STREAM, 0);
    if(sockSer == -1){
        perror("socket");
    }

    //设置端口可以重用，可以多个客户端连接同一个端口，并检测是否设置成功
    int yes = 1;
    if(setsockopt(sockSer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
        perror("setsockopt");
    }

    struct sockaddr_in addrSer,addrCli;        //创建一个记录地址信息的结构体
    addrSer.sin_family = AF_INET;              //所使用AF_INET协议族
    addrSer.sin_port = htons(SERVER_PORT);     //设置地址结构体中的端口号
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);   //设置其中的服务器ip

    //将套接字地址与所创建的套接字号联系起来。并检测是否绑定成功
    socklen_t addrlen = sizeof(struct sockaddr);
    int res = bind(sockSer,(struct sockaddr*)&addrSer, addrlen);
    if(res == -1)
        perror("bind");

    listen(sockSer, QUEUE_SIZE);       //监听端口队列是否由连接请求，如果有就将该端口设置位可连接状态，等待服务器接收连接

    printf("Server Wait Client Accept......\n");
    //如果监听到有连接请求接受连接请求。并检测是否连接成功，成功返回0，否则返回-1
    int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
    if(sockConn == -1)
        perror("accept");
    else
    {
        printf("Server Accept Client OK.\n");
        printf("Client IP:> %s\n", inet_ntoa(addrCli.sin_addr));
        printf("Client Port:> %d\n",ntohs(addrCli.sin_port));
    }

    char sendbuf[256];         //申请一个发送缓存区
    char recvbuf[256];         //申请一个接收缓存区
    while(1)
    {
        printf("Ser:>");
        scanf("%s",sendbuf);
        if(strncmp(sendbuf,"quit",4) == 0)    //如果所要发送的数据为"quit"，则直接退出。
            break;
        send(sockConn, sendbuf, strlen(sendbuf)+1, 0);   //发送数据
        recv(sockConn, recvbuf, 256, 0);    //接收客户端发送的数据
        printf("Cli:> %s\n",recvbuf);
    }

    close(sockSer);         //关闭套接字
    return 0;
}

