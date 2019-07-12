#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>


/*
 * select 函数原型 
 *int select(int nfds, fd_set *readfds, fd_set *writefds,
 *				 fd_set *exceptfds, struct timeval *timeout);
 * 参数描述:
 * ndfds:最大文件描述符个数+1,因为此参数会告诉内核检测前多个个文件描述符的状态
 * readdfs: 监控读属性文件描述符
 * writefds:监控写属性文件描述符
 * exceptfds:监控异常属性文件描述符
 * timeout: 定时阻塞监控时间
 *           NULL 永远等下去
 *           设置timeval,等待固定时间
 *           设置timeval均为0,检查描述子后立即返回,轮询
 *
 * select 能监听的文件描述符受限为FD_SETSIZE,一般为1024
 * 返回值为被激活的文件描述符的个数
 /





