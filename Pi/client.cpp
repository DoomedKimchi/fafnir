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

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int connect (char *hostname) {
	printf("Server IP: %s\n", hostname);
	
	int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //char buffer[256];
	char *readbuffer;

    /*if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }*/

    //portno = atoi(argv[2]);
	portno = 8888;
	readbuffer = (char *) malloc(sizeof(char)*2);

	/*
    printf("Please enter the message: ");
    //bzero(buffer,256);
    bzero(readbuffer,sizeof(readbuffer));
    //fgets(buffer,255,stdin);
    fgets(readbuffer,sizeof(readbuffer),stdin);
    //n = write(sockfd,buffer,strlen(buffer));
	printf("%s\n", readbuffer);
	//printf("test\n");
	*/

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    //server = gethostbyname(argv[1]);
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    //bzero(buffer,256);
    bzero(readbuffer,sizeof(readbuffer));
    //fgets(buffer,255,stdin);
    fgets(readbuffer,sizeof(readbuffer),stdin);
    //n = write(sockfd,buffer,strlen(buffer));
	printf("%s\n", readbuffer);
    n = write(sockfd,readbuffer,strlen(readbuffer));
    if (n < 0) 
         error("ERROR writing to socket");
    //bzero(buffer,256);
    bzero(readbuffer,sizeof(readbuffer));
    //n = read(sockfd,buffer,255);
    n = read(sockfd,readbuffer,sizeof(readbuffer));
    if (n < 0) 
         error("ERROR reading from socket");
    //printf("%s\n",buffer);
    printf("%s\n",readbuffer);
    close(sockfd);
    return 0;
}

void send (int status) {
}

void disconnect () {
}
