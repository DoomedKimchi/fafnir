#ifndef SERVER_H
#define SERVER_H

//#include <WPILib.h>
//#include <NetworkTables/NetworkTable.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "Robot.h"

void error (const char *msg);

void *proc (void *arg);

void server_init(Robot *r);

void server_begin_listening();

void server_update(char *message);

void server_close();

#endif /* SERVER_H */
