//多进程版本echo server

#include <sys/types.h>
#include "../writenReadn.h"
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <malloc.h>

void *doit(void *arg);

int main(int argc,char *argv[])
{
	int listenfd,*iptr;
	pthread_t tid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;

	if((listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
		perrorAndStop("socket error");

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVER_PORT);

	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(sockaddr)))
		perrorAndStop("bind error");

	if(listen(listenfd,LISTENQ) < 0)
		perrorAndStop("listen error");
	
	while(1)
	{
		clilen = sizeof(cliaddr);
		if((iptr = (int *)malloc(sizeof(int))) == NULL)
			perrorAndStop("malloc error");
		if((*iptr = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) < 0)
		{
			if(EINTR == errno)
				continue;
			perrorAndStop("accept error");
		}

		if(pthread_create(&tid,NULL,doit,(void *)iptr) > 0)
			perrorAndStop("pthread_create error");
	}	
}

void *doit(void *arg)
{
	int connfd;

	connfd = *((int *)arg);
	free(arg);

	pthread_detach(pthread_self());
	str_echo(connfd);
	return NULL;
}
