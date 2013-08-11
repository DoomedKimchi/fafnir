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

//char buffer[256];
int portno;
char *hostname;
char *readbuffer;

void error(const char *msg)
{
	perror(msg);
	//exit(0); // exit program on failure to connect
}

int main (int argc, char **argv) {
	int i;
	int host = 0;
	int port = 0;

	for (i = 1; i < argc; i++) {
		if ( (strcmp(argv[i], "-h") == 0) ||
				(strcmp(argv[i], "--host") == 0) ) {
			host = 1;
			if (i + 1 <= argc -1) {
				i++;
				hostname = argv[i];
			}
			else {
				printf("Usage: -h <host IP>\n");
				return -1;
			}
		}
		else if ( (strcmp(argv[i], "-p") == 0) ||
				(strcmp(argv[i], "--port") == 0) ) {
			port = 1;
			if (i + 1 <= argc -1) {
				i++;
				sscanf(argv[i], "%d", &portno);
			}
			else {
				printf("Usage: -p <port number>\n");
				return -1;
			}
		}
	}

	if (argc < 2) {
		//usage instructions
		printf ("Usage: %s <options>\n", argv[0] );
		// need more usage instructions
		return(-1);
	}
	if (port == 1 && host == 0) {
		printf("Please specify a hostname\n");
		return -1;
	}
	else if (port == 0 && host == 1) {
		printf("Please specify a port number\n");
		return -1;
	}

	printf("Connecting to: %s\n", hostname);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		error("ERROR opening socket");
		return 1;
	}
	//printf("connected to socket\n");
	printf("Trying to connect to host...\n");
	while (1) {
		//server = gethostbyname(argv[1]);
		if (hostname == "NULL") {
			printf("Not connecting to a server\n");
			break;
		}
		server = gethostbyname(hostname);
		if (server == NULL) {
			fprintf(stderr,"ERROR, no such host\n");
			printf("Reconnecting...\n");
			//return 1;
		}

		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr,
				(char *)&serv_addr.sin_addr.s_addr,
				server->h_length);
		serv_addr.sin_port = htons(portno);
		if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
			error("ERROR connecting");
			printf("Reconnecting...\n");
			//return 1;
		}
		else
			break;
	}
	return 0;
}

bool server_send () {
	readbuffer = (char *) malloc(BUFFSIZE); // assign memory for readbuffer
	//printf("Please enter the message: ");
	//bzero(buffer,256);
	bzero(readbuffer,sizeof(readbuffer));
	//sprintf(readbuffer, "%d", bearing); // use sscanf on server (use & of int)
	//fgets(buffer,255,stdin);
	//fgets(readbuffer,sizeof(readbuffer),stdin);
	//n = write(sockfd,buffer,strlen(buffer));
	readbuffer = "hi";
	printf("Readbuffer: %s\n", readbuffer);
	n = write(sockfd,readbuffer,BUFFSIZE);
	if (n < 0)
		error("ERROR writing to socket");
}

void server_disconnect () {
	close(sockfd);
}
