/*
#***********************************************
#
#      Filename: mypthread.h
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-05-07 00:27:54
# Last Modified: 2018-05-07 00:27:54
#***********************************************
*/
#ifndef _PTHREAD_H_
#define _PTHREAD_H_
#include <iostream>
#include <pthread.h>
#include <event.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <json/json.h>
#include <map>
#include <string>
#include "mycontrol.h"
using namespace std;

#define BUFF_SIZE 512

class Pthread
{
public:
	friend void Pthread_accept(int sockfd,short event, void *arg);
	friend void Pthread_work(int c,short event,void *arg);
	friend	void* Pthread_run(void*);
	Pthread(int fd);
	~Pthread();
private:
	int socket;
	int socketpair;
	control cont;
	struct event_base* event_list;
	map<int,struct event*> event_map;
};

void* Pthread_run(void*);
void Pthread_accept(int sockfd,short event, void *arg);
void Pthread_work(int c,short event,void *arg);

#endif
