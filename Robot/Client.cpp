#include "Client.h"

Client::Client() :
	portno(SERVER_PORT)
{
}

int Client::server_connect() {
	hostname = (char *)"localhost";
	printf("Connecting to: %s\n", hostname);

	/* Create a socket */
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
	if ( (serv_addr.sin_addr.s_addr = inet_addr(hostname)) == ERROR &&
			(serv_addr.sin_addr.s_addr = hostGetByName(hostname)) == ERROR ) {
		printf("ERROR, no such host\n");
		close(sockfd);
		return 1;
	}

	/* Connect to server */
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sock_addr_size) == ERROR) {
		printf("ERROR connecting\n");
		close(sockfd);
		return 1;
	}

	return 0;
}

int Client::server_get() {
	readbuffer = (char *) malloc(BUFFSIZE); // assign memory for readbuffer
	bzero(readbuffer,sizeof(readbuffer));
	//sprintf(readbuffer, "%d", bearing); // use sscanf on server (use & of int)
	readbuffer = (char *)"hi";
	printf("Readbuffer: %s\n", readbuffer);
	int n = write(sockfd,readbuffer,BUFFSIZE);
	if (n < 0)
		printf("ERROR writing to socket");
}

void Client::server_disconnect() {
	close(sockfd);
}
