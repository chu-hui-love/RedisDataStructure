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
	 * int socket(int domain, int type, int protocol);����һ��socket
	 * domain:ָ��Ҫ�����д����׽��ֵ�ͨ����,�������ڶ�����<bits/socket.h>��.��AF_*��ͷ	 ���õĲ���Ϊ
			  AF_INET : IPv4
	 		  AF_INET6 :IPV6
	 		  AF_UNIT: unix��,ͨ����������˺Ϳͻ��˶���һ̨������
	 		  
	 * type: ȷ���׽�������,��һ��ȷ��ͨ������,
	 			SOCK_DGRAM:     �̶����ȵ�,�����ӵ�,���ɿ��ı��Ĵ���.Ĭ��Э��ΪUDP
	 			SOCK_RAW:       IPЭ������ݱ��ӿ�
	 			SOCK_SEQPACKET: �̶����ȵ�,�����,�ɿ���,�������ӵı��Ĵ���
	 			SOCK_STREAM:    �����,�ɿ���,˫���,�������ӵ��ֽ���.Ĭ��Э��ΪTCP
	 			
	 * protocol: ͨ����0,��ʾΪ����������׽���ѡ��Ĭ��Э��.
	 * 		 
	 * 
	 *
	*/
	socfd=socket(AF_INET,SOCK_STREAM,0);

    
	



	

	return 0;

}

