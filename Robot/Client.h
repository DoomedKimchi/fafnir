#ifndef CLIENT_H
#define CLIENT_H

#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

/* VxWorks includes because the cRIO ain't running linux */
#include <vxWorks.h>
#include <sockLib.h>
#include <inetLib.h>
#include <hostLib.h>
/* For VxWorks socket programming:
 * http://www.vxdev.com/docs/vx55man/vxworks/netguide/c-sockets.html
 */

#define BUFFSIZE 80 // this needs to go in Constants.h

class Client {
	private:
		struct sockaddr_in serv_addr; // server's socket address

		int sock_addr_size;
		int sockfd; // socket file descriptor
		unsigned int portno;
		struct hostent *server;

		char *readbuffer;
		char *hostname;


	public:
		Client();

		int server_connect();
		int server_get();
		void server_disconnect();
};

#endif /* CLIENT_H */
