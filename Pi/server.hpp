#ifndef __server_hpp__
#define __server_hpp__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int server_init(int portno);
int server_accept();
int server_close();

#endif
