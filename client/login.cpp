/*
#***********************************************
# g++ -o login login.h client.h client.cpp login.cpp -lcrypt -ljson -g
#      Filename: login.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-04-23 03:14:36
# Last Modified: 2018-04-23 03:14:36
#***********************************************
*/

#include "login.h"
#include "client.h"

void init_show()
{
	printf("-------------------\n");
    printf("\t1.sign in\n");
    printf("\t2.sign up\n");
    printf("\t3.forgot you password\n");
    printf("-------------------\n");
	
}

void init(int sockfd)
{
	char datebuff[BUFF_SIZE] = {0};
	//char datebuff[512] = {0};
    time_t t = time(0);
    strftime(datebuff,BUFF_SIZE,"   :) %Y年%m月%d日 见到你真好",localtime(&t));
    printf("-------------------\n");
    printf("%s\n",datebuff);
	
	while(1)
	{
		init_show();
		printf("please choose : ");
		fflush(stdout);
		
		char command[10] = {0};
		fgets(command,9,stdin);
		
		char buff[BUFF_SIZE] = {0};
		if(strncmp(command,"1",1) == 0)
		{
			if(getinfo(1,sockfd) == 0)
			{
				recv(sockfd,buff,18,0);
				//cout << buff <<endl;
				if(strncmp(buff,"login successfully",18) == 0)
				{
					//cout << buff << endl;
					cout << "登录成功" << endl;
					break;
				}
			}
			else if(strcmp(buff,"already online") == 0)
			{
				cout <<"已在其他地方登录，不能重复登录" << endl;
			}
			else
			{
				cout << "登录失败" << endl;
			}
		}
		else if(strncmp(command,"2",1) == 0)
		{
			if(getinfo(2,sockfd) == 0)
			{
				recv(sockfd,buff,21,0);
				//cout << buff <<endl;
				if(strcmp(buff,"register successfully") == 0)
				{
				//	cout << buff << endl;
					cout << "注册成功" << endl;
					break;
				}
			}
			else
			{
				cout << "注册失败" << endl;
			}
		}
		else 
		{
			//cout << "continue" <<endl;
			continue;	
		}
	}
}

int getinfo(int flag,int sockfd)
{
	struct data  lg;
	memset(&lg,0,sizeof(lg));

	lg.flag = flag;
	printf("\tname : ");
	fflush(stdout);
	fgets(lg.name,NAME_SIZE-1,stdin);
	strtok(lg.name,"\n");	

	if(flag == 1 || flag == 2)
	{
		getpasswd(lg.name,lg.passwd);
	}
	if(flag == 2)
	{
		char passwd[PASSWD_SIZE] = {0};
		getpasswd(lg.name,passwd);
		if(strcmp(passwd,lg.passwd) != 0)
		{
			cout << endl;
			cout << "两次密码不一致" << endl;
			return -1;
		}
		/*
		printf("\ttel num ");
		fflush(stdout);
		fgets(lg.telnum,TEL_SIZE-1,stdin);
		*/
	}


	//printf("struct login \n%d\n%s\n%s\n%s\n",lg.flag,lg.name,lg.passwd,lg.telnum);
	if(-1 == send_json(lg,sockfd))
	{
		return -1;
	}
	//send(sockfd,(char*)&lg,sizeof(lg),0);
	return 0;
}

int send_json(struct data lg,int sockfd)
{	//json 进行数据打包
	
	Json::Value val;
	val["flag"] = lg.flag;
	val["name"] = lg.name;
	val["passwd"] = lg.passwd;
	//val["telnum"] = lg.telnum;
	
	if(-1 == send(sockfd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0))
	{
		cout << "发送错误" << endl;
		return -1;
	}
	//cout <<val.toStyledString().c_str() << endl;
	return 0;
}

void getpasswd(char* name,char* passwd)
{
	printf("\tpasswd : ");
    fflush(stdout);

    struct termios oldt,newt;
    tcgetattr(0,&oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO|ICANON);
    tcsetattr(0,TCSANOW,&newt);

    char backup[BUFF_SIZE] =  {0};
    int i = 0;
    while(1)
    {
        char ch = getchar();
        if(ch == '\n')  break;
      	backup[i++] = ch;
        printf("*");
        fflush(stdout);
    }
    tcsetattr(0,TCSANOW,&oldt);

    char salt[2] ;
    int m = strlen(name);
    salt[0] = name[0];
    if(m>0)
    {
        salt[1] = name[m-1];
    }
    else
    {
        salt[1] = salt[0];
    }
    char* encryption = crypt(backup,salt);
	strcpy(passwd,encryption);
	cout << endl;
}
/*
int main()
{
	int fd = create_socket();	
	init(fd);
}
*/
