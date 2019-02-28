/*
#***********************************************
#
#      Filename: main.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-04-24 07:59:43
# Last Modified: 2018-04-24 07:59:43
#***********************************************
g++ -o main main.cpp login.h login.cpp  talk.h talk.cpp  client.h client.cpp  -ljson -lcrypt -g

*/
#include <pthread.h>
#include "login.h"
#include "talk.h"
#include "client.h"

void* fun(void* arg)
{
	int c = (int)arg;
	
	while(1)
	{
		recvmesge(c);
		//char buff[512] = {0};
		//recv(c,buff,511,0);
		//cout << buff <<endl;
	}
}
int main()
{
	int fd = create_socket();
	assert(fd != -1);
	
	init(fd);
	
	pthread_t pt;
	pthread_create(&pt,NULL,fun,(void*)fd);	
	
	while(1)
	{
		//进入shell

		//frend list
		
		//talk
		sendmesge(fd);
	}
	return 0;
}
