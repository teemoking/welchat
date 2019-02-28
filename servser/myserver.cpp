/*
#***********************************************
#
#      Filename: myserver.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-05-08 03:00:36
# Last Modified: 2018-05-08 03:00:36
#***********************************************
*/
#include "myserver.h"

server:: server(const char* ip,int port)
{
	int sockfd = create_sockfd(ip,port);
	assert(sockfd != -1);

	event_list = event_base_new();
	struct event* listen_event = event_new(event_list,sockfd,EV_READ|EV_PERSIST,To_write,this);
	if(NULL ==  listen_event)
	{
		cout << "监听套接字注册失败" << endl;
	}
	else
	{
		event_add(listen_event,NULL);
		//_map.insert(make_pair(sockfd,listen_event));
	}
	
	for(int i=0; i< PTH_NUM; i++)
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,sockpair[i]);
		pth[i] = new Pthread(sockpair[i][1]);
		struct event* pair_event = event_new(event_list,sockpair[i][0],EV_READ|EV_PERSIST,To_read,this);
		if(NULL == pair_event)
		{
			cout <<"注册socketpair事件失败" << endl;
		}
		else
		{
			event_add(pair_event,NULL);
			_map.insert(make_pair(sockpair[i][0],0));
		}
	}
	
}
void server:: server_run()
{
	event_base_dispatch(event_list);
	return;
}

server::~server()
{
	event_base_free(event_list);
}

int create_sockfd(const char* ip,int port)
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd != -1);

    struct sockaddr_in sa;
    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip);
    sa.sin_port = htons(port);

    int res = bind(sockfd,(struct sockaddr*)&sa,sizeof(sa));
    if(res == -1)
    {
        cout << "绑定失败" << endl;
        return -1;
    }
    listen(sockfd,LISTEN_MAX);
    return sockfd;
}
void To_write(int fd,short event,void* arg)
{	
	server* ser = (server*)arg;
	//cout<<"To_write" << fd <<endl;
	struct sockaddr_in sa;
	int len = sizeof(sa);
	int c = accept(fd,(struct sockaddr*)&sa,(socklen_t*)&len);
	if(c <= 0)
	{	
		return ;
	}
	
	map<int,int>:: iterator it = ser->_map.begin();
	int flag = it->first;
	int tem = it->second;
	for(; it != ser->_map.end();++it )
	{
		if(it->second <= tem)
		{
			tem = it->second;
			flag = it->first;
		}
		//cout<<"event_map" << flag << ": " << tem << endl; 
	}
	write(flag,&c,sizeof(int));
	//cout << "write" << flag <<endl;
}
void To_read(int sockpair,short event,void* arg)
{
	server* ser = (server*)arg;
	//cout <<"To_read" <<sockpair <<endl;
	int num  = 0;
	read(sockpair,&num,sizeof(int));
	//cout << ser->_map[sockpair] <<endl;
	ser->_map[sockpair] = num;
	//cout << ser->_map[sockpair] <<endl;
	
	map<int,int>:: iterator it = ser->_map.find(sockpair);
	for(it = ser->_map.begin() ; it != ser->_map.end();++it )
	{
		cout << it->first << ": " << it->second << endl;
		
	}

	//cout << "map" << sockpair<< "<- " << num << endl;

}
