#include "server.h"

int sockfd, newsockfd, portno;
int c;
bool _fCloseThreads;
socklen_t clilen;
char *readbuffer;
struct sockaddr_in serv_addr, cli_addr;
pthread_t proc_thread;
pthread_t acc_thread;
pthread_attr_t proc_attr;
pthread_attr_t acc_attr;
Robot *robot;

void error(const char *msg)
{
    perror(msg);
    //printf("%s", msg);
    exit(1);
}

void * proc(void *arg) {
	printf("proc started\n");
    while (1) {
    	bzero(readbuffer, 2);
    	int n = read(newsockfd, readbuffer, (size_t) 2);
    	//char *message = read(newsockfd, readbuffer, (size_t) 2);
    	if (readbuffer[0] < 0) {
    		error("ERROR reading from socket");
    		break;
    	}
    	printf("n: %d\n", n);
    	//robot->aim((float)readbuffer[0], (float)readbuffer[1]);

    	if (_fCloseThreads) // exit when requested
    		break;
    }
    printf("closing proc\n");
    return NULL;
}

void * acc(void *arg) {
	//printf("create newsockfd\n");
	server_update("acc started");
    while (1) {
    	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
    	if (newsockfd < 0)
    		error("ERROR on accept");

    	if (_fCloseThreads) // exit when requested
    		break;
    }
    printf("closing acc\n");
    //printf("newsockfd created\n");
    return NULL;
}

void server_init(Robot *r) {
    robot = r;
    portno = 8888;
    _fCloseThreads = 0;
	//printf("before readbuffer\n");
    readbuffer = (char *) malloc(sizeof(char)*2);
	//printf("readbuffer\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//printf("sockfd\n");
    if (sockfd < 0) {
		//printf("negative number of sockfd\n");
    	error("ERROR opening socket");
		return;
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
		//printf("failed to bind\n");
		return;
    }
	printf("listening\n");
   	listen(sockfd, 5);
    c = sizeof(cli_addr);
	//printf("c\n");
	// fails here
    //newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
	//printf("newsockfd\n");

	printf("creating acc_thread\n");
	pthread_create(&acc_thread, &acc_attr, (void *(*)(void *))acc, (void *)robot);
	printf("acc_thread created, now detaching\n");
	pthread_detach(acc_thread);
	printf("acc_thread detached\n");

}

void server_begin_listening() {
	printf("creating proc_thread\n");
    pthread_create(&proc_thread, &proc_attr, (void *(*)(void *))proc, (void *)robot);
    printf("proc_thread created, now detaching\n");
    pthread_detach(proc_thread);
    printf("proc_thread detached\n");
    return;
}

void server_update(char *message) {
	printf("Message: %s\n", message);
}

void server_close() {
	_fCloseThreads = 1; // request all pthreads to close
	close(newsockfd);
	close(sockfd);
	printf("server closed\n");
}
