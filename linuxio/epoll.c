#include <sys/epoll.h>


/*
 * Linux epoll(2) ��������
 *
 *
 * int epoll_create(int size);
 * 		epoll_create ����һ��epoll(7)ʵ��.�Դ�Linux 2.6.8��ʼ,size�����ͱ�������,���Ǳ������һ������0��ֵ.
 * 		epoll_create() ����һ��������epollʵ�����ļ�������,���ļ����������ڶ�epoll�ӿڵ����к�������.
 *      size :�����ں˼������ļ�������������
 *      ���ص���epoll�ľ��,�þ��������Ҫ���ӵ�������,����һ�ú����.����java1.8�е�hashmap֮��,��������֪���ĵڶ���ʹ�ú�����ĵط���
 * 
 *
 * int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
 *  epfd: epoll_create�ľ��,������epoll_create�ķ���ֵ
 *  op: ��ʾ����
 *		EPOLL_CTL_ADD ע���µ�fd��epfd
 * 		EPOLL_CTL_MOD �޸��Ѿ�ע���fd�ļ����¼�
 * 		EPOLL_CTL_DEL ��epfd��ɾ��һ���Ѿ�������fd
 * fd: ��Ҫ������fd
 * event:
 *  struct epoll_event{
 *   __unit32_t events; //epoll ��Ϣ
 *   epoll_data_t data; // �û����ݱ���
 *
 *	}
 *   ��������õ�����
 *   EPOLLIN:��ʾ��Ӧ���ļ����������Զ�
 *   EPOLLOUT: ��ʾ��Ӧ���ļ�����������д
 *   EPOLLERR����ʾ��Ӧ���ļ���������������
 *  
 *   EPOLLPRI����ʾ��Ӧ���ļ��������н��������ݿɶ�������Ӧ�ñ�ʾ�д������ݵ�����
 *   EPOLLHUP����ʾ��Ӧ���ļ����������Ҷϣ�
 *   EPOLLET�� ��EPOLL��Ϊ��Ե����(Edge Triggered)ģʽ�����������ˮƽ����(Level Triggered)��˵��
 *   EPOLLONESHOT��ֻ����һ���¼���������������¼�֮���������Ҫ�����������socket�Ļ�����Ҫ�ٴΰ����socket���뵽EPOLL������
 *
 *
 *
 * int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
 *
 * epfd: epoll_create�ľ��,������epoll_create�ķ���ֵ
 * events: ��һ������,�������ں˵õ��¼��ļ���
 * maxevents����֮�ں����events�ж��,���maxevents��ֵ���ܴ��ڴ���epoll_create()ʱ��size��
 * timeout���ǳ�ʱʱ��
 *      -1������
 *       0���������أ�������
 *       >0��ָ��΢��
 *		����ֵ���ɹ������ж����ļ�������������ʱ�䵽ʱ����0��������-1
 * �����ش���0������res,Ӧ��������������Ϣ:
 * for(int i=0;i<res;i++){
 *     struct epoll_event event=events[i]; //�õ���Ҫ������¼�
 *	}
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
#include <unistd.h>

#include <errno.h>


#define MAXLINE 80       /*��ȡ�ĳ���*/
#define SERV_PORT 8000  /*�˿ں�*/
#define OPEN_MAX 1024   /*�򿪵�����ļ�������*/


int main(int argc,char** argv){

int i,j,maxi,listenfd,connfd,sockfd;

int nready,efd,res;

ssize_t n;

char buf[MAXLINE],str[INET_ADDRSTRLEN];
socklen_t clilen;
int client[OPEN_MAX];
struct sockaddr_in cliaddr, servaddr;
struct epoll_event tep, ep[OPEN_MAX];
listenfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);

bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
/*��������*/
listen(listenfd, 20);


for(i=0;i<OPEN_MAX;i++){
	client[i]=-1;
}

maxi=-1;
// ����epoll,�����1024���ļ�������
efd=epoll_create(OPEN_MAX);

if(efd==-1){
	exit(efd);
}

tep.events=EPOLLIN;tep.data.fd=listenfd;

// ��listenfdע�ᵽepoll��,epoll��������¼�
res=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);

if(res==-1){
	exit(res);
}


for(;;){
    
	nready=epoll_wait(efd,ep,OPEN_MAX,-1); /*�����ȴ�,�������¼����ļ�������,��д��ep��*/
	if(nready==-1){
		exit(nready);
	}
	

	for(i=0;i<nready;i++){
		// ��Ϊһ��ʼע����Ƕ��¼�,������Ƕ��¼�,�������һ��ѭ��
		if(!ep[i].events & EPOLLIN)
			continue;
		// �������Ϣ���ļ�������,����listenfd
		if(ep[i].data.fd==listenfd){
			clilen=sizeof(cliaddr);
			// �򿪿ͻ�������
			connfd=accept(listenfd,(struct sockaddr *)&cliaddr, &clilen);
			printf("received from %s at PORT %d", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));

			for(j=0;j<OPEN_MAX;j++){
				if(client[j]<0){
					client[j]=connfd; /*�����ļ�������,��,���ͻ��˱�������*/
					break;
				}
			}
			if(j>maxi){
				maxi=j;  /**/
			}

			/*���µõ���connfd,ע�ᵽepoll��*/
			tep.events=EPOLLIN;tep.data.fd=connfd;
			res=epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep);
			if(res==-1){
				exit(res);
			}
		}else{
		   /*�������Ϣ���ڿͻ���*/
		   
		   sockfd = ep[i].data.fd;
		   // �ӿͻ��˶�ȡ80���ֽ�
		   n = read(sockfd, buf, MAXLINE);

		   if(n==0){
			  //����0���ֽ�,����ͻ����Ѿ��ر�
			  for(j=0;j<maxi;j++){
			  	// ���ÿͻ��˵�λ��λ��-1,û������
				if(client[j]==sockfd){
					client[j]=-1;
					break;
				}
			  }
			 // ���ÿͻ���(�ļ�������)��epoll��ɾ��
			  res=epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
			  if (res == -1){
				exit(res);
			  }
			 close(sockfd);
			 printf("client[%d] closed connection",j);
		   }else{
				for (j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
				//д�ؿͻ���
				write(sockfd, buf, n);
		   }
		   
		}
	}

}


close(listenfd);
close(efd);
return 0;

}





