/*
#***********************************************
#
#      Filename: talk.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-04-24 07:07:40
# Last Modified: 2018-04-24 07:07:40
#***********************************************
*/
#include "talk.h"
#include "login.h"
#include "client.h"

void recvmesge(int sockfd)
{
	char buff[BUFF_SIZE] = {0};
	recv(sockfd,buff,BUFF_SIZE-1,0);

	Json::Value root;
	Json::Reader read;
	
	if(-1 ==  read.parse(buff,root))
	{
		cout <<" 网络错误" << endl;
		return ;
	}
	//if(root["flag"] == 4)
	if(root["flag"] == 4)
	{
		cout <<"\r" <<root["friend"].asString() ;
		cout << YELLOW << root["fname"].asString() << " ";//有回车的符号
		cout << root["message"].asString();
	}
	else
	{
		cout<< RED << "\r" << "系统消息"<< buff ;
		//cout<< RED << "系统消息"<< buff ;
	}
	cout << BLACK <<endl;
	
	//int len = strlen(root.toStyledString().c_str());
	//buff+=len;
}
void sendmesge(int sockfd)
{
	struct data lg;
	char buff[BUFF_SIZE] = {0};
/*
	fgets(buff,BUFF_SIZE,stdin);
	printf("fname: ");
	fflush(stdout);
	
	lg.flag = 4;
	fgets(lg.fname,NAME_SIZE-1,stdin);
	lg.name[strlen(lg.name)] = '\0';
	printf("messge: ");
	fflush(stdout);
	fgets(lg.message,BUFF_SIZE-1,stdin);
	lg.me[strlen(lg.name)] = '\0';
*/
	lg.flag = 4;
	cout << "fname: ";
	cin >> lg.name;
	if(	strcmp(lg.name,"flist") == 0)
	{
		getfriendlist();
		return ;
	}

	cout << "message: ";
	cin >> lg.message;

	Json::Value val;
	
	val["flag"] = lg.flag;
	val["fname"] = lg.fname;
	val["message"] = lg.message;

	if(-1 == send(sockfd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))
	{
		cout << "发送错误"<< endl;
	}
	//cout << val.toStyledString().c_str() <<endl;
}

void getfriendlist()
{
	cout << "friend list" <<endl;
	cout << "\tteemo" <<endl;
}

