#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <unistd.h>
#include "../writenReadn.h"
#include <sys/wait.h>


void sig_chld(int signo);

int main(int argc,char *argv[])
{
	int sockfd,epfd,nready,connfd,rec_number,number,err_number,serve_port;
	struct sockaddr_in serveraddr;
	struct epoll_event *events,event;
	char buf[100] = "Hello Serve";
	struct timeval start,end;
	double time_use;
	int i,j,k,*fd_array,per_sec_num,t_pid;


	if(argc != 4)
		printfAndStop("usage:client.a<IPadress> <端口号> <连接数>\n");
	
	memset(&serveraddr,0,sizeof(serveraddr));

	sscanf(argv[2],"%d",&serve_port);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(serve_port);
	if(inet_pton(AF_INET,argv[1],&serveraddr.sin_addr) <= 0)
		perrorAndStop("inet_pton error");

	sscanf(argv[3],"%d",&number);

	if((epfd = epoll_create(number+1)) < 0)
		perrorAndStop("epoll_create error");
	

	events = (struct epoll_event *)malloc(number *sizeof(struct epoll_event));

	fd_array = (int *)malloc(number*sizeof(int));
	
	//if(signal(SIGCHLD,sig_chld) < 0)
	//	perrorAndStop("signal error");	

	gettimeofday(&start,NULL);

	j = 0;
	rec_number = 0;
	err_number = 0;

	for(i = 0;i < number;++i)
	{
		
		if((sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
			perrorAndStop("socket error");
		if(connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
			perrorAndStop("connet error");
		*(fd_array+j) = sockfd;
		j++;
		event.data.fd = sockfd;
		event.events = EPOLLOUT;
		if(epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event) < 0)
			perrorAndStop("epoll_ctl error1");
	}
	

	gettimeofday(&end,NULL);
	time_use = 1000*(end.tv_sec-start.tv_sec) +((double) (end.tv_usec-start.tv_usec))/1000.0;		
	printf("时间:%fms\n",time_use);
	start.tv_sec = end.tv_sec;
	start.tv_usec = end.tv_usec;


	while(1)
	{
		if((nready = epoll_wait(epfd,events,number,-1)) < 0)
			perrorAndStop("epoll_wait error");
		for(i = 0;i < nready;++i)
		{
			if(((events+i)->events & EPOLLERR) || ((events+i)->events & EPOLLHUP))
			{
				++err_number;
					//close((events+i)->data.fd);
				shutdown((events+i)->data.fd,SHUT_WR);
				for(j = 0;j < number;++j)
				{
					if((*(fd_array+j)) == ((events+i)->data.fd))
					{
						*(fd_array+j) = -1;
						break;
					}
				}
				continue;
			}
			else if((events+i)->events & EPOLLOUT)
			{
				connfd = (events+i)->data.fd;
				if(write(connfd,buf,strlen(buf)+1) < 0)
					perrorAndStop("write error");
				event.data.fd = connfd;
				event.events = EPOLLIN;
				if(epoll_ctl(epfd[k],EPOLL_CTL_MOD,connfd,&event) < 0)
					perrorAndStop("epoll_ctl error2");
			}
			else if((events+i)->events & EPOLLIN)
			{
				++rec_number;
				connfd = (events+i)->data.fd;
				if( read(connfd,buf,100) < 0)
					perrorAndStop("read error");
				event.data.fd = connfd;
				event.events = EPOLLOUT;							
				if(epoll_ctl(epfd[k],EPOLL_CTL_MOD,connfd,&event) < 0)
					perrorAndStop("epoll_ctl error3");
			}	
		}
		
		gettimeofday(&end,NULL);
		if((end.tv_sec - start.tv_sec) > 60)
			break;
	}
		
		//gettimeofday(&end,NULL);
	time_use = 1000*(end.tv_sec-start.tv_sec) +((double) (end.tv_usec-start.tv_usec))/1000.0;		
	per_sec_num = rec_number/60;	
	printf("每秒负载:%d 错误量:%d 时间:%fms %s\n",per_sec_num,err_number,time_use,buf);
	
	while(wait(NULL) >0);

	for(j = 0;j < number*;++j)
	{
		if(*(fd_array+j) != -1)
		{
			shutdown(*(fd_array+j),SHUT_WR);
			while(read(*(fd_array+j),buf,100) > 0);
		}
	}
	free(fd_array);
	free(events);
	exit(0);
}

void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	while((pid = waitpid(-1,&stat,WNOHANG)) > 0);
	return;
}
