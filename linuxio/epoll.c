#include <sys/epoll.h>


/*
 * Linux epoll(2) 三个函数
 *
 *
 * int epoll_create(int size);
 * 		epoll_create 创建一个epoll(7)实例.自从Linux 2.6.8开始,size参数就被忽略了,但是必须给定一个大于0的值.
 * 		epoll_create() 返回一个引用新epoll实例的文件描述符,此文件描述符用于对epoll接口的所有后续调用.
 *      size :告诉内核监听的文件描述符的数量
 *      返回的是epoll的句柄,该句柄和其所要监视的描述符,构成一棵红黑树.除了java1.8中的hashmap之外,这是我所知道的第二个使用红黑树的地方了
 * 
 *
 * int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
 *  epfd: epoll_create的句柄,即调用epoll_create的返回值
 *  op: 表示动作
 *		EPOLL_CTL_ADD 注册新的fd到epfd
 * 		EPOLL_CTL_MOD 修改已经注册的fd的监听事件
 * 		EPOLL_CTL_DEL 从epfd中删除一个已经监听的fd
 * fd: 需要操作的fd
 * event:
 *  struct epoll_event{
 *   __unit32_t events; //epoll 消息
 *   epoll_data_t data; // 用户数据变量
 *
 *	}
 *   以下是最常用的三个
 *   EPOLLIN:表示对应的文件描述符可以读
 *   EPOLLOUT: 表示对应的文件描述符可以写
 *   EPOLLERR：表示对应的文件描述符发生错误
 *  
 *   EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）
 *   EPOLLHUP：表示对应的文件描述符被挂断；
 *   EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的
 *   EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
 *
 *
 *
 * int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
 *
 * epfd: epoll_create的句柄,即调用epoll_create的返回值
 * events: 是一个出参,用来从内核得到事件的集合
 * maxevents：告之内核这个events有多大,这个maxevents的值不能大于创建epoll_create()时的size，
 * timeout：是超时时间
 *      -1：阻塞
 *       0：立即返回，非阻塞
 *       >0：指定微秒
 *		返回值：成功返回有多少文件描述符就绪，时间到时返回0，出错返回-1
 * 若返回大于0的数字res,应该这样来处理消息:
 * for(int i=0;i<res;i++){
 *     struct epoll_event event=events[i]; //得到需要处理的事件
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


#define MAXLINE 80       /*读取的长度*/
#define SERV_PORT 8000  /*端口号*/
#define OPEN_MAX 1024   /*打开的最大文件描述符*/


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
/*启动监听*/
listen(listenfd, 20);


for(i=0;i<OPEN_MAX;i++){
	client[i]=-1;
}

maxi=-1;
// 创建epoll,其监听1024个文件描述符
efd=epoll_create(OPEN_MAX);

if(efd==-1){
	exit(efd);
}

tep.events=EPOLLIN;tep.data.fd=listenfd;

// 将listenfd注册到epoll中,epoll监听其读事件
res=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);

if(res==-1){
	exit(res);
}


for(;;){
    
	nready=epoll_wait(efd,ep,OPEN_MAX,-1); /*阻塞等待,所有有事件的文件描述符,被写到ep中*/
	if(nready==-1){
		exit(nready);
	}
	

	for(i=0;i<nready;i++){
		// 因为一开始注册的是读事件,如果不是读事件,则继续下一个循环
		if(!ep[i].events & EPOLLIN)
			continue;
		// 如果该消息的文件描述符,属于listenfd
		if(ep[i].data.fd==listenfd){
			clilen=sizeof(cliaddr);
			// 打开客户端连接
			connfd=accept(listenfd,(struct sockaddr *)&cliaddr, &clilen);
			printf("received from %s at PORT %d", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));

			for(j=0;j<OPEN_MAX;j++){
				if(client[j]<0){
					client[j]=connfd; /*保存文件描述符,即,将客户端保存起来*/
					break;
				}
			}
			if(j>maxi){
				maxi=j;  /**/
			}

			/*将新得到的connfd,注册到epoll中*/
			tep.events=EPOLLIN;tep.data.fd=connfd;
			res=epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep);
			if(res==-1){
				exit(res);
			}
		}else{
		   /*如果该消息属于客户端*/
		   
		   sockfd = ep[i].data.fd;
		   // 从客户端读取80个字节
		   n = read(sockfd, buf, MAXLINE);

		   if(n==0){
			  //读到0个字节,代表客户端已经关闭
			  for(j=0;j<maxi;j++){
			  	// 将该客户端的位置位置-1,没有启用
				if(client[j]==sockfd){
					client[j]=-1;
					break;
				}
			  }
			 // 将该客户端(文件描述符)从epoll中删除
			  res=epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
			  if (res == -1){
				exit(res);
			  }
			 close(sockfd);
			 printf("client[%d] closed connection",j);
		   }else{
				for (j = 0; j < n; j++)
						buf[j] = toupper(buf[j]);
				//写回客户端
				write(sockfd, buf, n);
		   }
		   
		}
	}

}


close(listenfd);
close(efd);
return 0;

}





