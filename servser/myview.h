/*
#***********************************************
#
#      Filename: myview.h
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-05-02 00:56:47
# Last Modified: 2018-05-02 00:56:47
#***********************************************
*/

#ifndef _MYVIEW_H_
#define _MYVIEW_H_
#include <iostream>
#include <mysql/mysql.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <json/json.h>
#include <string.h>
using namespace std;

#define QUERY_SIZE  512

class view
{
public:
	//view(){}
	virtual void process(int fd,Json::Value json,MYSQL* mysql)= 0;
};

class view_login:public view
{
public:
	//获取离线表中的留言信息
	void get_offline(int fd, Json::Value json,MYSQL* mysql)
	{
		MYSQL_RES* res;
		MYSQL_ROW row;
		char query[QUERY_SIZE] = {0};
		sprintf(query,"select * from offline where name = %s",json["name"].toStyledString().c_str());
		int reg = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{	
			cout << "查询离线消息失败" << endl;
		}
		else
		{
			res = mysql_store_result(mysql);
			while(row = mysql_fetch_row(res))
			{
				Json::Value val;
				val["flag"] = 4;
				val["friend"] = row[0];
				//val["fname"] = row[1];
				val["message"] = row[2];
				//发送离线消息
				send(fd,val.toStyledString().c_str(),strlen(val.toStyledString().c_str()),0);
			}
		}

		memset(query,0,QUERY_SIZE);
		sprintf(query,"delete from offline where name=%s",json["name"].toStyledString().c_str());
		reg = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{
			cout << "update offline error " << endl;
		}
		else
		{
			//cout << "update offline successful " << endl;
		}
	}	
	bool insert_online(int fd, Json::Value json,MYSQL* mysql)
	{
		MYSQL_RES* res;
		MYSQL_ROW row;
		char query[QUERY_SIZE] = {0};
		sprintf(query,"select count(*) from online where name = %s",json["name"].toStyledString().c_str());
		int reg = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{
			cout << "检查在线表错误" << endl;
			return false;
		}
		else
		{
			res = mysql_store_result(mysql);
			row = mysql_fetch_row(res);
			if(strcmp("1",row[0])==0)
			{
				//send(fd,"alread online",13,0);
				return false;
			}
		}
		
		memset(query,0,QUERY_SIZE);
		sprintf(query,"insert into online(socket,name) values(%d,%s)",fd,json["name"].toStyledString().c_str());
		reg = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{
			cout << "update online error " << endl;
			return false;
		}
		else
		{
			//cout << "update online successful " << endl;
		}
		return true;
	}
	bool identity( Json::Value json,MYSQL* mysql)
	{
		MYSQL_RES* res;
		MYSQL_ROW row;
		//cout <<"login"<< endl;
		char query[QUERY_SIZE] = {0};
		sprintf(query,"select count(*) from user where name = %s and passwd=%s",json["name"].toStyledString().c_str(),json["passwd"].toStyledString().c_str());
		//cout << json.toStyledString().c_str() <<endl;
		//cout << query << endl;
		int reg  = mysql_real_query(mysql,query,strlen(query));
	//	if(reg != 0)
	//	{
	//		cout << "query error" << endl;
	//		return ;
	//	}
		//cout << reg << endl;
		res = mysql_store_result(mysql);
		row = mysql_fetch_row(res);
		if(strcmp("0",row[0]) == 0)
		{
			//send(fd,"login successfully",18,0);
			return false;
		}
		//cout << fd << endl;
		else
		{
			//send(fd,"login error",11,0);	
			return true;
		}
	}
	void process(int fd, Json::Value json,MYSQL* mysql)
	{
		if(identity(json,mysql) == false)	
		{
			send(fd,"login error",11,0);
		}
		else if(insert_online(fd,json,mysql) == false)
		{
			send(fd,"already online",14,0);
		}
		else
		{
			send(fd,"login successfully",18,0);
			//离线消息
			get_offline(fd,json,mysql);
			//加入在线表
			//insert_online(fd,json,mysql);
			
		}
	}
};

class view_register:public view
{
public:
	void process(int fd, Json::Value json,MYSQL* mysql)
	{
		//cout <<"register"<< endl;
		char query[QUERY_SIZE] = {0};
		
		sprintf(query,"insert into user(name,passwd) values(%s,%s)",json["name"].toStyledString().c_str(),json["passwd"].toStyledString().c_str());
		//cout << json.toStyledString().c_str() <<endl;
		//cout << query << endl;
		int reg  = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{
			//cout << "query error" << endl;
			send(fd,"register error",14,0);
			return ;
		}
		//cout << fd << endl;
		send(fd,"register successfully",21,0);
	}
};

class view_talk:public view
{
public:
	void process(int fd,Json::Value json,MYSQL* mysql)
	{
		MYSQL_RES* res;
		MYSQL_ROW row;
		//cout <<"talk"<< endl;
		char query[QUERY_SIZE] = {0};
        sprintf(query,"select name from online where socket = %d ",fd);
		int reg = mysql_real_query(mysql,query,strlen(query));
        res = mysql_store_result(mysql);
        if(row = mysql_fetch_row(res))
        {
            json["friend"] = row[0];
        }

		memset(query,0,QUERY_SIZE);
		sprintf(query,"select socket from online where name =%s",json["fname"].toStyledString().c_str());
		reg = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{
			cout <<"在线消息查询状态失败" << endl;
		}
		res = mysql_store_result(mysql);
		
		if(row = mysql_fetch_row(res))
		{
			//转发消息
			json["fname"] = " ";
			send(atoi(row[0]),json.toStyledString().c_str(),strlen(json.toStyledString().c_str()),0);	
		}
		else
		{
			memset(query,0,QUERY_SIZE);
			sprintf(query,"insert into offline(friend,name,message) values(%s,%s ,%s)",json["friend"].toStyledString().c_str(),json["fname"].toStyledString().c_str(),json["message"].toStyledString().c_str());
			reg = mysql_real_query(mysql,query,strlen(query));
			if(reg != 0)
			{
				cout <<"离线消息发送成功" << endl;
			}
		}
		send(fd,"message successfully",20,0);
	}
};
class view_exit:public view
{
public:
	/*
	void insert_offline(int fd, Json::Value json,MYSQL* mysql)
	{
		MYSQL_RES* res;
		MYSQL_ROW row;
		char query[QUERY_SIZE] = {0};
		sprintf(query,"select id from user where name = %s",json["name"].toStyledString().c_str());
		int reg = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{
			cout << " 查询id 失败"<<endl;
		}
		else
		{
			res = mysql_store_result(mysql);
			row = mysql_fetch_row(res);
		}
		int id = atoi(row[0]);
		sprintf(query,"insert into offline(id,name) values(%d,%s)",id,json["name"].toStyledString().c_str());
		
		memset(query,0,QUERY_SIZE);
		reg = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{
			cout << "update offlien error " << endl;
		}
		else
		{
			cout << "update offlien successful " << endl;
		}

	}
	*/
	void delete_online(int fd,MYSQL* mysql)
	{
		char query[QUERY_SIZE] = {0};
		sprintf(query,"delete from online where socket = %d",fd);
		int reg = mysql_real_query(mysql,query,strlen(query));
		if(reg != 0)
		{
			cout << "update onlien error " << endl;
		}
		else
		{
			//cout << "update onlien successful " << endl;
		}
	}
	void process(int fd,Json::Value json,MYSQL* mysql)
	{
		//加入离线表
		delete_online(fd,mysql);
		//insert_offline(fd,json,mysql);
	}
};
#endif
