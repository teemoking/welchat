/*
#***********************************************
#
#      Filename: client.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-04-21 00:57:47
# Last Modified: 2018-04-21 00:57:47
#***********************************************
*/

#include "client.h"

int create_socket()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in sa;
	memset(&sa,0,sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(HOST_PORT); 
	sa.sin_addr.s_addr = inet_addr(HOST_IP);

	int res = connect(sockfd,(struct sockaddr*)&sa,sizeof(sa));
	if(res == -1)
	{
		return -1;
	}
	return sockfd;
}
/*
int main()
{
	int sockfd = create_sockfd();
	assert(sockfd != -1);
	
	while(1)
	{
		char buff[512] = {0};
		send(sockfd,"hello",5,0);
		
		recv(sockfd,buff,511,0);
		printf("buff = %s\n",buff);
	}

	exit(0);
}
*/
