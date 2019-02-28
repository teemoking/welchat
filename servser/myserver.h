/*
#***********************************************
#
#      Filename: myserver.h
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-05-08 02:51:47
# Last Modified: 2018-05-08 02:51:47
#***********************************************
*/
#ifndef _MYSERVER_H_
#define _MYSERVER_H_
#include <iostream>
#include <json/json.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <event.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <assert.h>
#include <string.h>
#include "mypthread.h"
using namespace std;

#define PTH_NUM 3
#define LISTEN_MAX 5
#define BUFF_SIZE 512

class server
{
	friend void To_write(int fd,short event,void* arg);
	friend void To_read(int fd,short event,void* arg);
public:
	server(const char* ip,int port);
	~server();
	void server_run();
	
private:
	int sockfd;
	int sockpair[PTH_NUM][2];
	Pthread* pth[PTH_NUM];
	struct event_base* event_list;
	map<int,int> _map;
};

int create_sockfd(const char* ip ,int port);
void To_write(int fd,short event,void* arg);
void To_read(int fd,short event,void* arg);
#endif
