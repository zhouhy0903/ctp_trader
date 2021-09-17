#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAXLINE 4096 //发送接受信息长度
#define PORT 6666   //端口 
 
int main(int argc, char** argv)
{
    int    sockfd, n;
    char    recvline[MAXLINE], sendline[MAXLINE];
    struct sockaddr_in    servaddr;
 
    if( argc != 2){
    printf("usage: ./client <ipaddress>\n");  //使用方法
    exit(0);
    }
 
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){   //创建套接字，并未连接
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
    }
     
    
    //memset(结构体地址，清零，要清零的长度);清零结构体servaddr，将结构体数据全部设置为0
    //同bzero(结构体地址，要清理的长度);默认清零
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;   //sa_family是通信类型，最常用的值是 "AF_INET"
    servaddr.sin_port = htons(PORT); //端口号
     
    //servaddr.sin_addr.s_addr=inet_addr(argv[1]); //服务器IP,如下功能相同
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
    printf("inet_pton error for %s\n",argv[1]);
    exit(0);
    }
 
    //连接服务器
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
 
    printf("send msg to server: \n");
    fgets(sendline, MAXLINE, stdin);  //输入向服务器发送的信息
     
    if( send(sockfd, sendline, strlen(sendline), 0) < 0)  //向服务器发送信息
    {
    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
    exit(0);
    }
 
    close(sockfd); //关闭套接字
    exit(0);
}