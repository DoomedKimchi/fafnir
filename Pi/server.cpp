#include "server.hpp"

#define HOSTNAME localhost
#define PORT 8888
#define BUFFSIZE 80

int sockfd, newsockfd, portno;
socklen_t clilen;
pid_t childpid;
char *readbuffer;
struct sockaddr_in serv_addr, cli_addr;

int server_init(int portno) {
	printf("Starting server\n");
	/* Open a socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("ERROR opening socket\n");
		return 1;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* Bind the socket */
	printf("Binding socket\n");
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("ERROR on binding\n");
		return 1;
	}
	printf("Listening\n");
	listen(sockfd, 5);

	return 0;
}

int server_accept() {
	printf("Start accepting\n");
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		printf("ERROR on accept\n");
		printf("newsockfd: %d\n", newsockfd);
		return 1;
	}
	readbuffer = (char *) malloc(BUFFSIZE);

	if ((childpid = fork()) == 0) {
		while (1) {
			bzero(readbuffer, BUFFSIZE);
			printf("reading\n");
			int n = read(newsockfd, readbuffer, BUFFSIZE);
			if (readbuffer[0] < 0) {
				printf("ERROR reading from socket\n");
				continue;
			}
			if ( (readbuffer == NULL) || (*readbuffer == '\0') ) {
				printf("Readbuffer is empty or null");
				break;
			}
			printf("Readbuffer: %s\n", readbuffer);
		}
	}

	return 0;
}

int server_close() {
	printf("Shutting down server\n");
	return 0;
}
