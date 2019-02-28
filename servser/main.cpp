/*
#***********************************************
#
#      Filename: main.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-05-02 01:02:30
# Last Modified: 2018-05-02 01:02:30
#***********************************************
g++ -o main mypthread.h mypthread.cpp  myserver.h myserver.cpp    myview.h mycontrol.h mycontrol.cpp main.cpp -ljson `mysql_config --cflags --libs` -lpthread -levent -g
*/
#include <iostream>
#include "myserver.h"
using namespace std;

#define HOST_IP "127.0.0.1"
#define HOST_PORT 6000

int main()
{
	server ser(HOST_IP,HOST_PORT);
	ser.server_run();
}
