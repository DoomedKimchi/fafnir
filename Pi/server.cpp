#include "server.hpp"

int sockfd; // listen socket
int newsockfd; // accept socket
int portno;
socklen_t clilen;
pid_t childpid;
char *writebuffer;
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

	/* Reuse the socket if needed */
	int tr = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &tr, sizeof(int)) == -1) {
		perror("setsockopt");
		return 1;
	}

	/* Bind the socket */
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("ERROR on binding\n");
		server_close();
		return 1;
	}

	printf("Listening on port %d\n", portno);
	listen(sockfd, 5);

	printf("Start accepting\n");
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		printf("ERROR on accept\n");
		server_close();
		return 1;
	}

	return 0;
}

int server_send(char *writebuffer) {
	//printf("Writebuffer: %s\n", writebuffer);

	if (write(newsockfd, writebuffer, sizeof(writebuffer)) < 0) {
		printf("ERROR writing\n");
		server_close();
		return 1;
	}

	return 0;
}

int server_close() {
	printf("Shutting down server\n");

	if (kill(childpid, SIGKILL) < 0) { // kill the forked process
		printf("Failed to kill child process\n");
	}
	else
		printf("Killed child proccess\n");

	if (close(sockfd) < 0)
		printf("Failed to close listening socket\n\n");
	else
		printf("Closed sockfd\n");
	if (close(newsockfd) < 0)
		printf("Failed to close accepting socket\n\n");
	else
		printf("Closed newsockfd\n");

	return 0;
}
