/*
#***********************************************
#
#      Filename: login.h
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-04-23 03:06:42
# Last Modified: 2018-04-23 03:06:42
#***********************************************
*/
#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <crypt.h>
#include <termios.h>
#include <json/json.h>
#include <string>
using namespace std;

//#define _XOPEN_SOURCE
#define BUFF_SIZE  512
#define NAME_SIZE  50
#define PASSWD_SIZE 100
#define TEL_SIZE 20

/*
enum flag
{
	FLAG_SIGNIN,
	FLAG_SIGNUP,
	FLAG_FORGET,
	FLAG_SIGNOUT
};
*/
struct data
{
	int flag;
	union
	{
		char name[NAME_SIZE];
		char fname[NAME_SIZE];
	};
	union
	{
		char passwd[PASSWD_SIZE];
		char message[BUFF_SIZE];
	};
	//char telnum[TEL_SIZE];
};


void init_show();
void init(int sockfd);
void getpasswd(char *name,char* passwd);
int  getinfo(int flag,int sockfd);
int send_json(struct data lg,int sockfd);

#endif
