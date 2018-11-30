#include "function.h"

int sd,sd2;


void exitfunc(){
  printf("exit func\n");
  close(sd);
  close(sd2);
}


int main(int argc,char* argv[])
{
  char buf[1024];
  pid_t pid;
  atexit(exitfunc);

  if(createConnection(&sd,"192.168.74.10",2000)){
    exit(1);
  }

  if(createConnection(&sd2,"192.168.74.10",3002)){
    exit(1);
  }
  putCommands(sd2,"commands");
  //putCommand(sd2,"LOG ICOM1 GPGGA ONTIME 1");


  FILE* fp;
  openFile(&fp,"../testlog","w");

  // switch (pid = fork()) {
  //   case -1 :
  //     perror("fork error\n");
  //     exit(1);
  //     break;
  //   case 0 : //child
  //
  //
  //   break;
  // }

  int rlen=0;
  while((rlen = recv(sd,buf,BUF_SIZE,0)) > -1){
    //printf("receved\n");
		fputs(buf,fp);
    fflush(fp);
	}


  return 1;
}
