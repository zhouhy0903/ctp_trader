#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#define MAXLINE 4096
#define PORT 6666
 
int main(int argc, char** argv)
{
    int    listenfd, connfd;
    struct sockaddr_in     servaddr;
    char    buff[MAXLINE];
    int     n;
 
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  //创建套接字
    printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
 
    memset(&servaddr, 0, sizeof(servaddr));//结构体清零
    servaddr.sin_family = AF_INET;  //sa_family是通信类型，最常用的值是 "AF_INET"
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //指定接受任何连接
    servaddr.sin_port = htons(PORT); //监听端口
 
    //给套接口绑定地址
    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
 
    if( listen(listenfd, 10) == -1){   //开始监听，最大请求数为10，可以自己设置
    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
 
    printf("======waiting for client's request======\n");
     
    while(1){
      //建立通信，等待客户端connect()函数的连接
      if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1)
      {
         printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
         continue;
      }
      n = recv(connfd, buff, MAXLINE, 0);  //n可以判断错误，此处可直接用recv()函数
                                           //接收到的信息存放在buff中
      buff[n] = '\0';  //添加结束符
      printf("recv msg from client: %s\n", buff);
     close(connfd);
    }
 
    close(listenfd);
}