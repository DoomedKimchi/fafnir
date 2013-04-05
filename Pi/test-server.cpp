/* test server to receive messages */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFFSIZE 80

int sockfd, newsockfd, portno;
int acc_status, proc_status;
unsigned int c;
int bearing;
bool _fCloseThreads;
socklen_t clilen;
char *readbuffer;
char *msg;
struct sockaddr_in serv_addr, cli_addr;
pthread_t proc_thread;
pthread_t acc_thread;
pthread_attr_t proc_attr;
pthread_attr_t acc_attr;

void error(const char *msg)
{
    perror(msg);
    //printf("%s", msg);
    //exit(1);
}

void * proc(void *arg) {
	proc_status = 1;
	printf("proc started\n");
    while (1) {
    	printf("Start accepting\n");
    	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&c);
    	if (newsockfd < 0) {
    		error("ERROR on accept");
    		//autoController->driveBlindly();
    	}
    	readbuffer = (char *) malloc(sizeof(char)*BUFFSIZE);
    	bzero(readbuffer, BUFFSIZE);
    	printf("Start reading\n");
    	int n = read(newsockfd, readbuffer, (size_t) BUFFSIZE); // n is number of bytes
    	if (readbuffer[0] < 0) {
    		error("ERROR reading from socket");
    		//autoController->driveBlindly();
    	}
    	printf("Readbuffer: %s\n", readbuffer);
    	//sscanf(readbuffer, "%d", bearing);
    	//printf("Recieved bearing: %d\n", bearing);
    	//autoController->update(bearing);

    	if (_fCloseThreads) // exit when requested
    		break;
    }
    printf("closing proc\n");
    return NULL;
}

void * acc(void *arg) {
	acc_status=1;
	//printf("create newsockfd\n");
	//server_update("acc started");
	while(1) {
    	printf("Start accepting\n");
    	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
    	if (newsockfd < 0) {
    		error("ERROR on accept");
    		//autoController->driveBlindly();
    	}
    	if (_fCloseThreads) // exit when requested
    		break;
	}
    printf("closing acc\n");
    //printf("newsockfd created\n");
    return NULL;
}

int main() {
	portno = 8888;
	_fCloseThreads = 0;
	bearing = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
		//printf("negative number of sockfd\n");
    	error("ERROR opening socket");
		return -1;
    }
bzero((char *) &serv_addr, sizeof(serv_addr));
	//printf("bzero\n");
    serv_addr.sin_family = AF_INET;
	//printf("serv_addr.sin_family\n");
    serv_addr.sin_addr.s_addr = INADDR_ANY;
	//printf("serv_addr.sin_addr.s_addr\n");
    serv_addr.sin_port = htons(portno);
	//printf("serv_addr.sin_port\n");
    printf("binding socket\n");
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    	error("ERROR on binding");
    	//autoController->driveBlindly();
		//printf("failed to bind\n");
		return -1;
    }
	printf("listening\n");
   	listen(sockfd, 5);
    c = sizeof(cli_addr);

    	printf("Start accepting\n");
    	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&c);
    	if (newsockfd < 0) {
    		error("ERROR on accept");
    		//autoController->driveBlindly();
    	}
	while (1) {
    	readbuffer = (char *) malloc(BUFFSIZE);
    	bzero(readbuffer, BUFFSIZE);
    	printf("Start reading\n");
    	//int n = read(newsockfd, readbuffer, (size_t) BUFFSIZE); // n is number of bytes
    	//int n = read(newsockfd, readbuffer, strlen(readbuffer)); // n is number of bytes
    	int n = read(newsockfd, readbuffer, BUFFSIZE); // n is number of bytes
    	if (readbuffer[0] < 0) {
    		error("ERROR reading from socket");
    		//autoController->driveBlindly();
    	}
    	printf("Readbuffer: %s\n", readbuffer);
    	sscanf(readbuffer, "%d", &bearing);
    	printf("Recieved bearing: %d\n", bearing);
    	//autoController->update(bearing);
    }

/*
	printf("creating acc_thread\n");
	pthread_create(&acc_thread, &acc_attr, (void *(*)(void *))acc, (void *)acc_status);
	printf("acc_thread created, now detaching\n");
	pthread_detach(acc_thread);
	printf("acc_thread detached\n");

	printf("creating proc_thread\n");
    pthread_create(&proc_thread, &proc_attr, (void *(*)(void *))proc, (void *)proc_status);
    printf("proc_thread created, now detaching\n");
    pthread_detach(proc_thread);
    printf("proc_thread detached\n");

	while(1) {
		//printf("Acc status: %d\n", acc_status);
		//printf("Proc status: %d\n", proc_status);
		if (bearing)
			//printf("Bearing: %d\n", bearing);
		printf("readbuffer: %s\n", readbuffer);
	}
	*/

}
