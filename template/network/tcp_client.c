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

	//send
	for(;;)
	{
		int n;
		char buffer[1024];
		fgets(buffer, 1024, stdin);
		
		if(strncmp(buffer, "stop", strlen("stop")) == 0)
			break;
		
		n = send(sockfd, buffer, strlen(buffer), 0);
		if(n < strlen(buffer))
			err_sys("send error");
	}
	
	close(sockfd);
	return 0;
}
