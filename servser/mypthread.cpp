/*
#***********************************************
#
#      Filename: mypthread.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-05-07 00:55:17
# Last Modified: 2018-05-07 00:55:17
#***********************************************
*/
#include "mypthread.h"

Pthread:: Pthread(int fd)
{

	socketpair = fd;//socketpair

	cont;//contorl

	event_list = event_base_new();
	struct event* pthread_event = event_new(event_list,socketpair,EV_READ|EV_PERSIST,Pthread_accept,this);
	if(NULL == pthread_event)
	{
		cout << "注册线程套接子失败" << endl;
	}
	else
	{
		//event_map.insert(make_pair(socketpair,pthread_event));
		event_add(pthread_event,NULL);
	}
	pthread_t pt;
	pthread_create(&pt,NULL,Pthread_run,this);
}
/*
void* Pthread:: Pthread_run(void* arg)
{
	Pthread* pth = (Pthread*)arg;

	event_base_dispatch(pth->event_list);

	//socketpair 中读取主线程传输的SOCKFD
	int fd;
	read(socketpair[0],&fd,sizeof(int));
	//注册事件
	struct event* = event_new(pth->event_list,fd,EV_READ|EV_PERSIST,);

	//发送给主线程监听的套接字数目
	write();
	
}
*/
void* Pthread_run(void* arg)
{
	Pthread* pth = (Pthread*)arg;
	event_base_dispatch(pth->event_list);
}

Pthread::~Pthread()
{
	event_base_free(event_list);
}

void Pthread_accept(int sockfd,short event,void* arg)
{
	//cout<<"pthread_accept" << sockfd <<endl;
	Pthread* pth = (Pthread*)arg;
	//map_event  的大小
	//write();
	//char buff[BUFF_SIZE] = {0};
	int c = 0;
	read(pth->socketpair,&c,sizeof(int));
	if(c <= 0)
	{
		cout << "连接套接子分配失败" << endl;
	}
	else
	{
		struct event* connect_event = event_new(pth->event_list,c,EV_READ|EV_PERSIST,Pthread_work,pth);
		if(NULL == connect_event)
		{
			cout << " 注册套连接接字失败" << endl;
		}
		else
		{
			pth->event_map.insert(make_pair(c,connect_event));
			event_add(connect_event,NULL);
			int size = pth->event_map.size();
			write(pth->socketpair,&size,sizeof(int));
		}
	}
	//cout<<"pthread_accept is over" <<endl;
}
void Pthread_work(int c,short event,void* arg)
{
	//cout<<"pthread_work" << c << endl;
	Pthread* pth = (Pthread*)arg;
	
	char buff[BUFF_SIZE] = {0};
	int res = recv(c,buff,BUFF_SIZE-1,0);
	if(res == 0)
	{
		cout << "客户端断开"<< endl;
		event_del(pth->event_map[c]);//删除libevent中的事件
		pth->event_map.erase(c);//删除map中的事件
		int size = pth->event_map.size();
		write(pth->socketpair,&size,sizeof(int));
		
		close(c);//关闭套接字
		Json::Value eval;
		eval["flag"] = 0;
		pth->cont.process(c,eval);
	}
	else
	{
		Json::Value root;
		Json::Reader read;
		if(-1 == read.parse(buff,root))
		{
			cout << "网络错误" << endl;
		}
		else
		{
			pth->cont.process(c,root);
		}

	}

	//cout<<"pthread_work is over" << c << endl;
}
