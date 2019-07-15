#include <sys/epoll.h>


/*
 * Linux epoll(2) 三个函数
 * int epoll_create(int size);
 * 		epoll_create 创建一个epoll(7)实例.自从Linux 2.6.8开始,size参数就被忽略了,但是必须给定一个大于0的值.
 * 		epoll_create() 返回一个引用新epoll实例的文件描述符,此文件描述符用于对epoll接口的所有后续调用.
 * 
 * int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
 * 
 *
 *
 * 
 * int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <errno.h>
#include "serverlog.h"

#define MAXLINE 80       /*读取的长度*/
#define SERV_PORT 8000  /*端口号*/
#define OPEN_MAX 1024   /*打开的最大文件描述符*/


int main(int argc,char** argv){

int i,j,maxi,listenfd,connfd,sockfd;

int nready,etd,res;

ssize_t n;

char buf[MAXLINE],str[INET_ADDRSTRLEN];
socklen_t clilen;
int client[OPEN_MAX];
struct sockaddr_in cliaddr, servaddr;
struct epoll_event tep, ep[OPEN_MAX];
listenfd = Socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);
/**/
bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
/*启动监听*/
Listen(listenfd, 20);


for(i=0;i<OPEN_MAX;i++){
	client[i]=-1;
}





}





