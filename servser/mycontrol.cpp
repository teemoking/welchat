/*
#***********************************************
#
#      Filename: control.cpp
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-05-02 03:27:05
# Last Modified: 2018-05-02 03:27:05
#***********************************************
*/
#include "mycontrol.h"

control:: control()
{
    mysql_init(&mysql);
    if(&mysql == NULL)
    {
        cout << "init error" <<endl;
    }
    if(!mysql_real_connect(&mysql,MYSQL_IP,MYSQL_NAME,MYSQL_PASSWD,MYSQL_DATABASE,3306,NULL,0))
    {
        cout << "connect error" <<endl;
    }

	_map.insert(make_pair(1,new view_login));
	_map.insert(make_pair(2,new view_register));
	_map.insert(make_pair(4,new view_talk));
	_map.insert(make_pair(0,new view_exit));
	//_map.insert(make_pair(MSG_TYPE_TALK,new view_talk()));
	//_map.insert(make_pair(MSG_TYPE_LOGIN,new view_login()));
	//_map.insert(make_pair(MSG_TYPE_TALK,new view_talk()));
	//_map.insert(make_pair(MSG_TYPE_REGISTER,new view_register()));
	
}
void control:: process(int fd,Json::Value json)
{
	//json
	map<int,view*>::iterator it =  _map.find(json["flag"].asInt());
	if(it != _map.end())
	{
		it->second->process(fd,json,&mysql);
	}
		
	/*
	map<int,view*>::iterator it = _map.begin();
	for(; it!=_map.end() ;++it)
	{
		cout << "view" << endl;
		it->second->process();	
	}	
	*/
	//it->second->process();
}
