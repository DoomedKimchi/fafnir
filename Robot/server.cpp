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
//Robot *robot;
AutonomousController *autoController;
int bearing;

void error(const char *msg)
{
    perror(msg);
    //printf("%s", msg);
    //exit(1);
}

void * proc(void *arg) {
	printf("proc started\n");
    while (1) {
    	printf("Start accepting\n");
    	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
    	if (newsockfd < 0) {
    		error("ERROR on accept");
    		autoController->driveBlindly();
    	}
    	readbuffer = (char *) malloc(sizeof(char)*BUFFSIZE);
    	bzero(readbuffer, BUFFSIZE);
    	printf("Start reading\n");
    	int n = read(newsockfd, readbuffer, (size_t) BUFFSIZE); // n is number of bytes
    	if (readbuffer[0] < 0) {
    		error("ERROR reading from socket");
    		autoController->driveBlindly();
    	}
    	printf("Readbuffer: %s\n", readbuffer);
    	sscanf(readbuffer, "%d", bearing);
    	printf("Recieved bearing: %d\n", bearing);
    	autoController->update(bearing);

    	if (_fCloseThreads) // exit when requested
    		break;
    }
    printf("closing proc\n");
    return NULL;
}

void * acc(void *arg) {
	//printf("create newsockfd\n");
	//server_update("acc started");
	while(1) {
    	printf("Start accepting\n");
    	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
    	if (newsockfd < 0) {
    		error("ERROR on accept");
    		autoController->driveBlindly();
    	}
    	if (_fCloseThreads) // exit when requested
    		break;
	}
    printf("closing acc\n");
    //printf("newsockfd created\n");
    return NULL;
}

void server_init(AutonomousController *ac) {
    //robot = r;
	autoController = ac;
    portno = 8888;
    _fCloseThreads = 0;
    bearing = 1;

    	//robot->setVision(5);

	//printf("before readbuffer\n");
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
    	//autoController->driveBlindly();
		//printf("failed to bind\n");
		return;
    }
	printf("listening\n");
   	listen(sockfd, 5);
    c = sizeof(cli_addr);

   	printf("Start accepting\n");
   	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
   	if (newsockfd < 0) {
   		error("ERROR on accept");
   		//autoController->driveBlindly();
   	}

    // infinite loop to accept requests
    while (1) {
    	readbuffer = (char *) malloc(BUFFSIZE);
    	bzero(readbuffer, BUFFSIZE);
    	printf("reading\n");
    	//int n = read(newsockfd, readbuffer, (size_t) BUFFSIZE); // n is number of bytes
    	int n = read(newsockfd, readbuffer, BUFFSIZE); // n is number of bytes
    	if (readbuffer[0] < 0) {
    		error("ERROR reading from socket");
    		//autoController->driveBlindly();
    	}
    		printf("Readbuffer: %s\n", readbuffer);
    	sscanf(readbuffer, "%d", bearing);
    		printf("Recieved bearing: %d\n", bearing);
    	autoController->update(bearing);
    	free(readbuffer);
    }
	//printf("c\n");
	// fails here
    //newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &c);
	//printf("newsockfd\n");
/*
	printf("creating acc_thread\n");
	pthread_create(&acc_thread, &acc_attr, (void *(*)(void *))acc, (void *)robot);
	printf("acc_thread created, now detaching\n");
	pthread_detach(acc_thread);
	printf("acc_thread detached\n");
*/
}

void server_begin_listening() {
	/*
	printf("creating proc_thread\n");
    pthread_create(&proc_thread, &proc_attr, (void *(*)(void *))proc, (void *)robot);
    printf("proc_thread created, now detaching\n");
    pthread_detach(proc_thread);
    printf("proc_thread detached\n");
    return;
    */
}

void server_update() {
	// don't put this here
	//int bearing;
	//printf("Message: %s\n", message);
	//robot->setVision(5);

    //free(readbuffer);
}

void server_close() {
	_fCloseThreads = 1; // request all pthreads to close
	close(newsockfd);
	close(sockfd);
	printf("server closed\n");
}
