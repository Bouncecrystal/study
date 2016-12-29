#include "common.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	if(argc != 3)
		err_quit("usage:./tcp_client ip port");
	
	int ret;
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		err_sys("socket error");
	
	//connect
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &addr.sin_addr);
	ret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));	
	if(ret < 0)
		err_sys("connect error");	

	fd_set read_set;
	int flag = 0;
	//send
	for(;;)
	{
		int n;
		char buffer[1024];

		FD_ZERO(&read_set);
		if(flag == 0)
			FD_SET(0, &read_set);
		FD_SET(sockfd, &read_set);
		ret = select(sockfd + 1, &read_set, NULL, NULL, NULL);
		if(ret < 0)
			err_sys("select error");
		else
		{
			if(FD_ISSET(0, &read_set))
			{
				n = read(0, buffer, 1024);
				buffer[n] = '\0';
		
				/*(if(strncmp(buffer, "stop", strlen("stop")) == 0)
				{
					shutdown(sockfd, SHUT_WR);
					flag = 1;
					continue;
				}*/	
				n = send(sockfd, buffer, strlen(buffer), 0);
				if(n < strlen(buffer))
					err_sys("send error");
			}
			if(FD_ISSET(sockfd, &read_set))
			{
				n = read(sockfd, buffer, 1024);
				if(n == 0)
				{
					printf("serve disconnect");
					break;
				}
				buffer[n] = '\0';
				printf("%s\n", buffer);
			}
		}
	}
	
	close(sockfd);
	return 0;
}
