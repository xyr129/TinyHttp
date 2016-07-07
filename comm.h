#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>

#define _MSGSIZE_ 1024
#define _FILEPATH_ "."
#define _ID_ 0

static int server_type = 1;
static int client_type = 2;

struct msgbuf
{
   long mtype;
   char mtext[_MSGSIZE_];
};

int creat_msg();
int send_msg(int msg_id,const char* msg,int send_type);
int recv_msg(int msg_id,char* msg_out,int recv_type);
int destory_msg(int msg_id);
