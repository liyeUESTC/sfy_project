//poll版本echo server

#include <sys/types.h>
#include "../writenReadn.h"
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

void sig_chld(int signo);

int main(int argc,char *argv[])
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t chilen;
	struct sockaddr_in cliaddr,servaddr;

	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		perrorAndStop("socket error");
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVER_PORT);

	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
		perrorAndStop("bind error");
	if(listen(listenfd,LISTENQ) < 0)
		perrorAndStop("listen error");
	if(signal(SIGCHLD,sig_chld) < 0)
		perrorAndStop("signal error");
	while(1)
	{
		chilen = sizeof(cliaddr);
		if((connfd = accept(listenfd,(struct sockaddr *)&servaddr,&chilen)) < 0)
			perrorAndStop("accept error");
		if((childpid = fork()) == 0)
		{
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}

void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	while((pid = waitpid(-1,&stat,WNOHANG)) > 0);
		//printf("child %d terminated\n",pid);
	return;
}
