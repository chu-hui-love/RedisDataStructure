#include <sys/types.h>      
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>




#define SERVER_PORT 8001
#define MAXLEN 4096

int main(int argc,char ** argv){

	struct sockaddr_in serveraddr, clientaddr;
    int sockfd, addrlen, confd, len, i;
    char ipstr[128];
    char buf[MAXLINE];

	/*
	 * 
	 * int socket(int domain, int type, int protocol);创建一个socket
	 * domain:指定要在其中创建套接字的通信域,该属性在定义于<bits/socket.h>内.以AF_*开头	 常用的参数为
			  AF_INET : IPv4
	 		  AF_INET6 :IPV6
	 		  AF_UNIT: unix域,通常用来服务端和客户端都在一台机器上
	 		  
	 * type: 确定套接字类型,进一步确定通信特征,
	 			SOCK_DGRAM:     固定长度的,无连接的,不可靠的报文传递.默认协议为UDP
	 			SOCK_RAW:       IP协议的数据报接口
	 			SOCK_SEQPACKET: 固定长度的,有序的,可靠的,面向连接的报文传递
	 			SOCK_STREAM:    有序的,可靠的,双向的,面向连接的字节流.默认协议为TCP
	 			
	 * protocol: 通常是0,表示为给定的域和套接字选择默认协议.
	 * 		 
	 * 
	 *
	*/
	socfd=socket(AF_INET,SOCK_STREAM,0);

    
	



	

	return 0;

}

