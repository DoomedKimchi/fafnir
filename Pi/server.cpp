#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define HOSTNAME localhost
#define PORT 8888

int sockfd, newsockfd, portno;
int c;
socklen_t clilen;
pid_t childpid;
char *readbuffer;
struct sockaddr_in serv_addr, cli_addr;

void server_init(int portno) {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("ERROR opening socket\n");
		exit(1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	printf("Binding socket\n");
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    	printf("ERROR on binding\n");
    	//autoController->driveBlindly();
		//printf("failed to bind\n");
		exit(1);
    }
	printf("Listening\n");
	listen(sockfd, 5);
	c = sizeof(cli_addr);

	}

void server_accept() {
   	printf("Start accepting\n");
   	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
   	if (newsockfd < 0) {
   		error("ERROR on accept");
   		//autoController->driveBlindly();
   	}
    readbuffer = (char *) malloc(BUFFSIZE);

	if ((childpid = fork()) == 0) {
		while (1) {
			bzero(readbuffer, BUFFSIZE);
			printf("reading\n");
			int n = read(newsockfd, readbuffer, BUFFSIZE);
			if (readbuffer[0] < 0) {
    			error("ERROR reading from socket");
    		}
    		if ( (readbuffer == NULL) || (*readbuffer == '\0') ) {
    			printf("Readbuffer is empty or null");
    			break;
    		}
		printf("Readbuffer: %s\n", readbuffer);
		}
	}

}
