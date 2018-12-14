#include "function.h"

int createConnection(int* sd,const char* addr,const int port){
        int _sd;
        struct sockaddr_in sin; //_sd adress struct

        if((_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                perror("socket failed. Error");
                return -1;
        }
        memset((char*)&sin, '\0', sizeof(sin));
        sin.sin_family = AF_INET;
        //sin.sin_port = htons(2000);
        //sin.sin_addr.s_addr = inet_addr("192.168.74.10");
        sin.sin_port = htons(port);
        sin.sin_addr.s_addr = inet_addr(addr);
        memset(&(sin.sin_zero), 0,8);


        if(bind(_sd, (struct sockaddr *)&sin, sizeof(struct sockaddr))) {
                perror("bind failed. Error");
        }

        if(connect(_sd, (struct sockaddr *)&sin, sizeof(struct sockaddr))) {
                perror("connect failed. Error");
                return -1;
        }

        (*sd) = _sd;

        // char buf[BUF_SIZE];
        // memset(buf, 0, BUF_SIZE * (sizeof buf[0]) );
        // if(recv(_sd,buf,BUF_SIZE,0) == -1) {
        //         perror("command reseive error\n");
        //         return -1;
        // }
        // printf("Port opened.\n");
        // printf("Port Name : %s\n",buf);

        return 0;
}


int putCommands(const int sd,const char*path)
{
        FILE *fp;
        int len,rlen;
        char buf[BUF_SIZE];
        struct timespec tim,tim2;
        tim.tv_sec = 0;
        tim.tv_nsec = 100000000; // 0.1s
        //char buf2[BUF_SIZE];
        if((fp = fopen(path,"r")) ==0 )
        {
                perror("open error\n");
                return -1;
        }

        memset(buf, 0, BUF_SIZE * (sizeof buf[0]) );
        //memset(buf2, 0, BUF_SIZE * (sizeof buf[0]) );

        while((fgets(buf,BUF_SIZE,fp))!=NULL)
        {
                printf("To Server : %s",buf);

                len = strlen(buf) + 1;
                if(send(sd,buf,len,0) == -1) {
                        perror("command send error\n");
                        return -1;
                }

                if(nanosleep(&tim, &tim2) < 0)
            		{
            			printf("sleep error");
            			exit(0);
            		}
        }

        fclose(fp);
        return 0;
}

int putCommand(const int sd,const char* command)
{
        int len;
        len = strlen(command) + 1;
        if(send(sd,command,len,0) == -1) {
                perror("command send error\n");
                return -1;
        }

        printf("To server: %s\n", command);
      return 0;
}


int openFile(FILE** fp,const char* path,const char* mode){
  FILE* _fp;
  if((_fp = fopen(path,mode)) ==0 )
  {
    perror("open error\n");
    return -1;
  }

  (*fp)=_fp;
  return 0;
}
