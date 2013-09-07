#include "Client.h"

Client::Client() :
	portno(SERVER_PORT)
{
}

int Client::server_connect() {
	hostname = (char *) SERVER_ADDR;
	printf("Connecting to: %s\n", hostname);

	/* Create a socket */
	printf("Creating socket\n");
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
		printf("ERROR opening socket\n");
		return 1;
	}

	sock_addr_size = sizeof(struct sockaddr_in);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_len = (u_char) sock_addr_size;
	serv_addr.sin_port = htons(portno);

	/* Get the host name */
	printf("Resolving host\n");
	if ( (serv_addr.sin_addr.s_addr = inet_addr(hostname)) == ERROR &&
			(serv_addr.sin_addr.s_addr = hostGetByName(hostname)) == ERROR ) {
		printf("ERROR, no such host\n");
		close(sockfd);
		return 1;
	}

	/* Connect to server */
	printf("Connecting to server\n");
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sock_addr_size) == ERROR) {
		printf("ERROR connecting\n");
		close(sockfd);
		return 1;
	}

	printf("Successfully connected\n");
	return 0;
}

int Client::server_get() {
	/* Send a request to the server */
	if (write(sockfd, (char *) &myRequest, sizeof(myRequest)) == ERROR) {
		printf("ERROR writing\n");
		close(sockfd);
		return 1;
	}

	return 0;
}

void Client::server_disconnect() {
	close(sockfd);
}
