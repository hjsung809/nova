#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 1024

int createConnection(int* sd,const char* addr,const int port);
int putCommands(const int sd,const char*path);
int openFile(FILE** fp,const char* path,const char* mode);
