#include "comm.h"

int main()
{
    int msg_id = creat_msg();
    char buf[_MSGSIZE_];
    while(1)
    {
        ssize_t _s=read(0,buf,sizeof(buf)-1);
        if(_s > 0)
        {
            buf[_s-1]='\0';
        }
        send_msg(msg_id,buf,client_type);
        if(strcasecmp(buf,"quit") == 0)
        {
            break;
        }

        memset(buf,'\0',sizeof(buf));
        recv_msg(msg_id,buf,server_type);
        if(strcasecmp(buf,"quit") == 0)
        {
            break;
        }
        printf("server > %s\n",buf);
        printf("server say done,please enter > ");
        fflush(stdout);
        
    }
    destroy_msg(msg_id);
    return 0;
}
        
