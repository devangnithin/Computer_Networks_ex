/*
    Author : Nithin Devang
    Assignment # : 2
    zid: z1804837
*/
#include "prog2cli.h"

extern int exit_flags[]; //exit flags to decide if any wrapper calls to system calls should exit or continue

int main(int argc, char**argv) { 
    int sockfd, n; //sockfd is filedescriptor for socket created, n is no of 
                   //lines read by Read function 
    char recvline[MAXLINE+1]; //Buffer to read data from n/w Read
    struct sockaddr_in servaddr; //struct to store server address and info
    char* ipaddress;

    setExitFlags(); //initialize exit flags

    int servPort = SERV_PORT;  //default port set

    if (argc < 2) { //ipaddress part not available
        fprintf(stderr, "Usage: %s <IPaddress> [PORT]\n",argv[0]); 
        exit(10);
    }
    ipaddress = argv[1];

    if(argc >= 3) { //if port is passed through command, use that
        servPort = atoi(argv[2]);
    }


    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; //ipv4
    servaddr.sin_port = htons(servPort); //set port

    Inet_pton(AF_INET, ipaddress, &servaddr.sin_addr); //set ipaddress etc

    Connect(sockfd, (SA*) &servaddr, sizeof(servaddr));

    while((n = Read(sockfd, recvline, MAXLINE)) > 0) { 
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }

    Close(sockfd);

    return 0;
}

/* Method to set and initialize exit flags */
void setExitFlags() {
    int i;
    for (i = 0; i <= NFLAGS; i++) {
        exit_flags[i] = 1;
    }
}
