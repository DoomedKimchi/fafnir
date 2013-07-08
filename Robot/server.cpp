#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "Robot.h"

int sockfd, newsockfd, portno;
socklen_t clilen;
char *readbuffer;
struct sockaddr_in serv_addr, cli_addr;
pthread_t proc_thread;
pthread_attr_t attr;
Robot *robot;

void * proc(void *arg) {
	while (1) {
		bzero(readbuffer, 2);
		int n = read(newsockfd, readbuffer, (size_t) 2);
		if (readbuffer[0] < 0) {
			break;
		}
		robot->aim((float)readbuffer[0], (float)readbuffer[1]);
	}
}

void server_init(Robot *r) {
	robot = r;
	portno = 8888;
	readbuffer = (char *) malloc(sizeof(char)*2);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		return;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		return;
	}
	listen(sockfd, 5);
	int c = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
}

void server_begin_listening() {
	pthread_create(&proc_thread, &attr, (void *(*)(void *))proc, (void *)robot);
	pthread_detach(proc_thread);
	return;
}
