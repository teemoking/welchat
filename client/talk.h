/*
#***********************************************
#
#      Filename: talk.h
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-04-24 06:23:27
# Last Modified: 2018-04-24 06:23:27
#***********************************************
*/

#ifndef _TALK_H_
#define _TALK_H_

#include <stdio.h>
#include <string.h>

#define YELLOW  "\033[33m"     
#define RED     "\033[31m"  
#define BLACK   "\033[30m"

void getfriendlist();
void recvmesge(int sockfd);
void sendmesge(int sockfd);

#endif
