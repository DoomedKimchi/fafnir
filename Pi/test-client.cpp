#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define BUFFSIZE 80
#define PORT 8888
#define HOSTNAME "localhost"

int sockfd;
int n;
struct sockaddr_in serv_addr;
struct hostent *server;

int portno;
char *hostname;
char *readbuffer;
char *writebuffer;

int server_connect() {
	hostname = (char *) HOSTNAME;
	portno = PORT;

	printf("Connecting to: %s\n", hostname);

	// Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("ERROR opening socket\n");
		return 1;
	}

	printf("Resolving host...\n");
	server = gethostbyname(hostname);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		return 1;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);

	// Connect to server
	if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("ERROR connecting\n");
		return 1;
	}

	printf("Successfully connected\n");
	return 0;

}

int server_get() {
	while (1) {
		bzero(readbuffer, BUFFSIZE);

		int n;
		if ((n = read(sockfd, readbuffer, sizeof(readbuffer))) < 0) {
			printf("ERROR reading\n");
			close(sockfd);
			return 1;
		}

		if ( (readbuffer == NULL) || (*readbuffer == '\0') ) {
			printf("Readbuffer is empty or null\n");
			break;
		}
		else
			printf("Got a message: %s\n", readbuffer);
	}

	return 0;
}

int server_send () {
	bzero(writebuffer, sizeof(writebuffer));
	writebuffer = (char *) "hi";
	printf("Readbuffer: %s\n", writebuffer);
	n = write(sockfd, writebuffer, BUFFSIZE);
	if (n < 0) {
		printf("ERROR writing to socket\n");
		close(sockfd);
		return 1;
	}

	return 0;
}

void server_disconnect () {
	printf("Disconnecting\n");
	close(sockfd);
}

int main (int argc, char **argv) {
	readbuffer = (char *) malloc(BUFFSIZE); // assign memory for readbuffer
	writebuffer = (char *) malloc(BUFFSIZE); // assign memory for writebuffer

	server_connect();
	server_get();

	return 0;
}
