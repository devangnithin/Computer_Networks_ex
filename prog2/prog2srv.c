/*
    Author : Nithin Devang
    Assignment # : 3
    zid: z1804837
*/

#include "prog2srv.h"


extern BOOL exit_flags[]; //exit flags to decide if any wrapper calls to system calls should exit or continue


int main (int argc, char **argv) {
    int listenfd, confd; //file descriptor to listen and write
    struct sockaddr_in servaddr;
	//struct sockaddr_in6 servaddr; // for ipv6
    char buff[MAXLINE];
    time_t ticks;

    setExitFlags(); //initialize exit flags

    int servPort = SERV_PORT; //default port
    if(argc>1) { //if port is passed as command line argument
        servPort = atoi(argv[1]);
    }

    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	//listenfd = Socket(AF_INET6, SOCK_STREAM, 0); for ipv6

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
	//servaddr.sin6_family = AF_INET6; //ipv6
	servaddr.sin_port = htons(servPort);
	//servaddr.sin6_port = htons(servPort);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, QUELEN); 

    while(TRUE) { //Continuously process request inside loop 
        confd = Accept(listenfd, 0, 0);
        ticks = time(NOSTORE);
        snprintf(buff, sizeof(buff), "%.24s\n\r", ctime(&ticks)); // adds to string
        Write(confd, buff, strlen(buff)); //invoking wrapper to write response
        
        Close(confd);
    }

    return 0;
}

/*
Method to set wrapper flags for various wrapper calls.
*/
void setExitFlags() {
    int i;
    for (i = 0; i <=NFLAGS; i++) {
        exit_flags[i] = TRUE;
    }
}
