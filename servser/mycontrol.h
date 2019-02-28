/*
#***********************************************
#
#      Filename: control.h
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-05-02 00:38:58
# Last Modified: 2018-05-02 00:38:58
#***********************************************
*/
#ifndef _CONTROL_H_
#define _CONTROL_H_
#include <iostream>
#include <json/json.h>
#include <map>
#include <mysql/mysql.h>
#include "myview.h"
using namespace std;

#define MYSQL_IP "127.0.0.1"
#define MYSQL_NAME "teemo"
#define MYSQL_PASSWD "123456"
#define MYSQL_DATABASE "chat"

class control
{
public:
	control();
	void process(int fd,Json::Value json);
private:
	map<int,view*> _map;
	MYSQL mysql;
};

#endif
