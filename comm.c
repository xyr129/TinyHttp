#include "comm.h"

int creat_msg()
{
   key_t _key = ftok(_FILEPATH_,_ID_);
   if(_key < 0)
   {
      printf("%d:%s\n",errno,strerror(errno));
      return -1;
   }
   int msg_id = msgget(_key,IPC_CREAT);
   if(msg_id < 0)
   {
      printf("%d:%s\n",errno,strerror(errno));
      return -1;
   }
   return msg_id;
}

int send_msg(int msg_id,const char* msg,int send_type)
{
   struct msgbuf _buf;
   _buf.mtype = send_type;
   strncpy(_buf.mtext,msg,strlen(msg)+1);
   if(msgsnd(msg_id,&_buf,sizeof(_buf.mtext),0) < 0)
   {
      printf("send_msg:%d:%s\n",errno,strerror(errno));
      return -1;
   }
   return 0; 
}

int recv_msg(int msg_id,char* msg_out,int recv_type)
{
   struct msgbuf _buf;
   memset(_buf.mtext,'\0',sizeof(_buf.mtext));
   if(msgrcv(msg_id,&_buf,sizeof(_buf.mtext),recv_type,0) < 0)
   {
      printf("recv_msg:%d:%s\n",errno,strerror(errno));
      return -1;
   }
   else
   {
      strcpy(msg_out,_buf.mtext);
   }
   return 0;
}

int destroy_msg(int msg_id)
{
	if(msg_id != -1)
	{
		if(msgctl(msg_id,IPC_RMID,NULL)==-1)
		{
			printf("destroy_msg:%d:%s\n",errno,strerror(errno));
			return -1;  
		}
    }
    return 0;
}   
