/*
#***********************************************
#
#      Filename: chat_client.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-04-21 00:05:05
# Last Modified: 2018-04-21 00:05:05
#***********************************************
*/
#include "client.h"
#include "login.h"

int main()
{	
	//用户界面，选择登录，注册
	int sockfd = create_socket();
	assert(sockfd != -1);
	//连接服务器
	init(sockfd);
	//聊天，发送文件或者发送离线消息，
	
	//用户退出

	exit(0);
}
