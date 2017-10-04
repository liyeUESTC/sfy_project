//多进程版本echo server

//#include <sys/types.h>
#include "../writenReadn.h"
#include <unistd.h>
#include <netinet/in.h>
//#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FD_SETSIZE_ 10240
int main(int argc,char *argv[])
{
	int listenfd,connfd,sockfd,maxi,maxfd,i;
	int nready,client[FD_SETSIZE_];
	ssize_t n;
	fd_set rset,allset;
	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;

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
	
	maxfd = listenfd;
	maxi = -1;
	for(i = 0;i < FD_SETSIZE_; ++i)
		client[i] = -1;
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);

	while(1)
	{
		rset = allset;  //防止select函数修改allset 
		if((nready = select(maxfd+1,&rset,NULL,NULL,NULL)) < 0)  //阻塞在这 直到描述符准备好
			perrorAndStop("select error");

		if(FD_ISSET(listenfd,&rset))   //有描述符可读
		{
			clilen = sizeof(cliaddr);
			if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) < 0)
				perrorAndStop("accept error");
			for( i = 0;i <FD_SETSIZE_;++i)
			{
				if(client[i] < 0)
				{
					client[i] = connfd;
					break;
				}
			}

			if( FD_SETSIZE_ == i)
				printfAndStop("too many clients\n");
			FD_SET(connfd,&allset);
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi)
				maxi = i;
			if(--nready <= 0)    //没有可读的已连接描述符
				continue;
		}


		for(i = 0;i <= maxi;++i)
		{
			if((sockfd = client[i]) < 0)
				continue;
			if(FD_ISSET(sockfd,&rset))   //有描述符可读
			{
				if((n =read(sockfd,buf,MAXLINE)) < 0)
					perrorAndStop("read error");
				else if( 0 == n)
				{
					if(close(sockfd) < -1)
						perrorAndStop("close sockfd error");
					FD_CLR(sockfd,&allset);
					client[i] = -1;
				}
				else
				{
					if(write(sockfd,buf,n) < 0)
						printfAndStop("write error");
				}

				if(--nready <= 0)   //没有已连接的描述符
					break;
			}
		}
	}
}

