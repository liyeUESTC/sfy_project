#ifndef WRITENREADN_H
#define WRITENREADN_H

#include <sys/types.h>
#include <stdio.h>

#define SERVER_PORT 9000
#define LISTENQ 3000
#define MAXLINE 1000
#define OPEN_MAX 30000
#define INFTIM -1

void perrorAndStop(const char *msg);
void printfAndStop(const char *msg);
ssize_t writen(int fd,const void *vptr,size_t n);
ssize_t readn(int fd,void *vptr,size_t n);
ssize_t readline(int fd,void *vptr,size_t maxlen);
void str_cli(FILE *fp,int sockfd);
void str_echo(int sockfd);
#endif

