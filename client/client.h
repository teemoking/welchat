/*
#***********************************************
#
#      Filename: client.h
#        Author:teemo_king
#         Email: Mp - AK1028430241@gmail.com
#   Description: ---
#        Create: 2018-04-21 00:08:36
# Last Modified: 2018-04-21 00:08:36
#***********************************************
*/
#ifndef _CHAT_CLIENT_H
#define _CHAT_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <string.h>

#define HOST_IP "127.0.0.1"
#define HOST_PORT 6000

int create_socket();

#endif
