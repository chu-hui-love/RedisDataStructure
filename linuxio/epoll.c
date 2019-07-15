#include <sys/epoll.h>


/*
 * Linux epoll(2) ��������
 * int epoll_create(int size);
 * 		epoll_create ����һ��epoll(7)ʵ��.�Դ�Linux 2.6.8��ʼ,size�����ͱ�������,���Ǳ������һ������0��ֵ.
 * 		epoll_create() ����һ��������epollʵ�����ļ�������,���ļ����������ڶ�epoll�ӿڵ����к�������.
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

#define MAXLINE 80       /*��ȡ�ĳ���*/
#define SERV_PORT 8000  /*�˿ں�*/
#define OPEN_MAX 1024   /*�򿪵�����ļ�������*/


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
/*��������*/
Listen(listenfd, 20);


for(i=0;i<OPEN_MAX;i++){
	client[i]=-1;
}





}





