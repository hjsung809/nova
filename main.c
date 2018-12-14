#include "function.h"

int sd,sd2;

void exitfunc(){
  printf("exit func\n");
  close(sd);
  close(sd2);
}


int main(int argc,char* argv[])
{
  pid_t pid1;
  atexit(exitfunc);


  if(createConnection(&sd,"192.168.74.10",2000)){   //로그 기록용
    exit(1);
  }

  if(createConnection(&sd2,"192.168.74.10",3002)){  //명령 전송용
    exit(1);
  }

  FILE* fp;
  openFile(&fp,"../testlog","w"); //로그 기록용 파일
  fputs("sxx records start.\n",fp);


  if((pid1=fork()) < 0){  //  로그 기록 프로세스
    perror("fork error \n");
    exit(0);
  }else if(pid1 == 0 ){
    int rlen=0;
    char buf[1024];
    memset(buf, 0, 1024 * (sizeof buf[0]));

    while((rlen = recv(sd,buf,BUF_SIZE,0)) > -1){
      //printf("receved\n");
  		fputs(buf,fp);
      fflush(fp);
      memset(buf, 0, 1024 * (sizeof buf[0]));
  	}

    printf("log exited. \n");
    exit(0);
  }


  putCommands(sd,"commands");  //initialize commands


  if((pid1=fork()) < 0){    //로그에 대한 피드백 받는 프로세스
    perror("fork error \n");
    exit(0);
  }else if(pid1 == 0 ){
    int rlen=0;
    char buf[1024];
    memset(buf, 0, 1024 * (sizeof buf[0]));

    while((rlen = recv(sd2,buf,BUF_SIZE,0)) > -1){
      //printf("receved\n");
  		fputs(buf,stdout);
      fflush(stdout);
      memset(buf, 0, 1024 * (sizeof buf[0]));
  	}

    printf("log response exited. \n");
    exit(0);
  }

  char cbuf[1024];         //로그 명령 입력및 전송. (메인 프로세스)
  while(1){
    memset(cbuf, 0, 1024 * (sizeof cbuf[0]));
    fgets(cbuf,1024,stdin);
    putCommand(sd2,cbuf);
  }
  pause();

  return 1;
}
