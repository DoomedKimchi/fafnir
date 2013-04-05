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

#define HOSTNAME "10.0.8.2"
#define PORT 8888
#define BUFFSIZE 80

	int sockfd; 
	int portno; // port number
	int n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //char buffer[256];
	char *readbuffer;

void error(const char *msg)
{
	perror(msg);
	//exit(0); // exit program on failure to connect
}

bool server_connect () {
	char *hostname = (char *)HOSTNAME;
	printf("Connecting to: %s\n", hostname);
	
    /*if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }*/

    //portno = atoi(argv[2]);
	portno = PORT; // set port number according to #define

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
    if (sockfd < 0) {
        error("ERROR opening socket");
		return 1;
	}
	//printf("connected to socket\n");
	printf("Trying to connect to host...\n");
	while (1) {
    	//server = gethostbyname(argv[1]);
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

bool server_send (int bearing) {
	readbuffer = (char *) malloc(sizeof(char)*BUFFSIZE); // assign memory for readbuffer
	//printf("Please enter the message: ");
    //bzero(buffer,256);
    bzero(readbuffer,sizeof(readbuffer));
	sprintf(readbuffer, "%d", bearing); // use sscanf on server (use & of int)
    //fgets(buffer,255,stdin);
    //fgets(readbuffer,sizeof(readbuffer),stdin);
    //n = write(sockfd,buffer,strlen(buffer));
	printf("Readbuffer: %s\n", readbuffer);
    n = write(sockfd,readbuffer,strlen(readbuffer));
    if (n < 0) 
         error("ERROR writing to socket");
	/*
    //bzero(buffer,256);
    bzero(readbuffer,sizeof(readbuffer));
    //n = read(sockfd,buffer,255);
    n = read(sockfd,readbuffer,sizeof(readbuffer));
    if (n < 0) 
         error("ERROR reading from socket");
    //printf("%s\n",buffer);
    printf("%s\n",readbuffer);
	*/
}

void server_disconnect () {
    close(sockfd);
}
