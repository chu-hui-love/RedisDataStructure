#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>


/*
 * select ����ԭ�� 
 *int select(int nfds, fd_set *readfds, fd_set *writefds,
 *				 fd_set *exceptfds, struct timeval *timeout);
 * ��������:
 * ndfds:����ļ�����������+1,��Ϊ�˲���������ں˼��ǰ������ļ���������״̬
 * readdfs: ��ض������ļ�������
 * writefds:���д�����ļ�������
 * exceptfds:����쳣�����ļ�������
 * timeout: ��ʱ�������ʱ��
 *           NULL ��Զ����ȥ
 *           ����timeval,�ȴ��̶�ʱ��
 *           ����timeval��Ϊ0,��������Ӻ���������,��ѯ
 *
 * select �ܼ������ļ�����������ΪFD_SETSIZE,һ��Ϊ1024
 * ����ֵΪ��������ļ��������ĸ���
 /





