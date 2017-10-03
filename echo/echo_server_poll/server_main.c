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
#include <poll.h>

int main(int argc,char *argv[])
{
	int listenfd,connfd,sockfd,i,maxi;
	int nready;
	ssize_t n;
	char buf[MAXLINE];
	socklen_t clilen;
	struct pollfd client[OPEN_MAX];
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

	client[0].fd = listenfd;
	client[0].events = 	POLLRDNORM;
	for(i = 1;i < OPEN_MAX;++i)
		client[i].fd = -1;
	
	maxi = 0;
	
	while(1)
	{

		if((nready = poll(client,maxi+1,INFTIM)) < 0)
			perrorAndStop("poll error");

		if(client[0].revents & POLLRDNORM)
		{	
			clilen = sizeof(cliaddr);
		
			if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) < 0)
			{
				if(EINTR == errno)
					continue;
				perrorAndStop("accept error");
			}
			
		//	printf("connect client\n");

			for(i = 1;i < OPEN_MAX;++i)
			{
				if(client[i].fd < 0)
				{
					client[i].fd = connfd;
					client[i].events = POLLRDNORM;
					break;
				}
			}

			if(OPEN_MAX == i)
				printfAndStop("too many clients\n");
			if(i > maxi)
				maxi = i;
			if(--nready <= 0)
				continue;
		}

		for(i = 1;i <= maxi;++i)
		{
			if((sockfd = client[i].fd) < 0)
				continue;
			if(client[i].revents & (POLLRDNORM | POLLERR))
			{
				if((n=read(sockfd,buf,MAXLINE)) < 0)
				{
					if(ECONNRESET == errno)
					{
						if(close(sockfd) < 0)
							perrorAndStop("close error");
						client[i].fd = -1;
					}
					else
						perrorAndStop("read error");
				}
				else if(0 == n)
				{
					if(close(sockfd) < 0)
						perrorAndStop("close error");
					client[i].fd = -1;
				}
				else
				{
					if(write(sockfd,buf,n) < 0)
						perrorAndStop("write error");
					//printf("success writen data\n");
				}
					
			}

			if(--nready <=0)
				break;
		}
	}
}

