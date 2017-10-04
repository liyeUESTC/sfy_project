//epoll版本echo server

#include <sys/types.h>
#include "../writenReadn.h"
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>

int main(int argc,char *argv[])
{
	int listenfd,connfd,sockfd,epfd,i;
	int nready;
	ssize_t n;
	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	struct epoll_event event,events[OPEN_MAX];

	if((listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
		perrorAndStop("socket error");

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVER_PORT);

	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(sockaddr)) < 0)
		perrorAndStop("bind error");

	if(listen(listenfd,LISTENQ) < 0)
		perrorAndStop("listen error");

	if((epfd = epoll_create(OPEN_MAX)) < 0)
		perrorAndStop("epoll_create error");

	event.data.fd = listenfd;
	event.events = EPOLLIN;
	
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&event) < 0)
	{
		close(epfd);
		perrorAndStop("epoll_ctl error");
	}

	while(1)
	{
		if((nready = epoll_wait(epfd,events,OPEN_MAX,-1)) < 0)
		{
			close(epfd);
			perrorAndStop("epoll_wait error");
		}

		for(i = 0;i < nready;++i)
		{
			if((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || !(events[i].events & EPOLLIN))
			{
				close(events[i].data.fd);
				continue;
			}
			else if(listenfd == events[i].data.fd)
			{
				clilen = sizeof(cliaddr);				
				if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) < 0)
				{
					close(epfd);
					perrorAndStop("accept error");
				}

				event.data.fd = connfd;
				event.events = EPOLLIN;
				if(epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&event) < 0)
				{
					close(epfd);
					perrorAndStop("epoll_ctl error");
				}
			}

			else if(events[i].events & EPOLLIN)
			{
				sockfd = events[i].data.fd;
				if((n = read(sockfd,buf,MAXLINE)) < 0)
				{
					
					if(ECONNRESET == errno)   //reset by client
					{
						if(close(sockfd) < 0)
						{
							close(epfd);
							perrorAndStop("close error");
						}
					}
					else
					{
						close(epfd);
						perrorAndStop("read error");
					}
				}
				else if(0 == n)
				{
					if(close(sockfd) < 0)
					{
						close(epfd);
						perrorAndStop("close error");
					}
				}
				else
				{
					if(write(sockfd,buf,n) < 0)
					{
						close(epfd);
						perrorAndStop("write error");
					}
				}
			}
		}
	}
}

