/*
    Author : Nithin Devang
    Assignment # : 4
    zid: z1804837
*/
#include "prog4cli.h"


/* Method to process user inputs and send request to server.
This prints server response
*/
void str_cli(int sockfd) {
    char recvline[MAXLINE + 1], sendline[MAXLINE]; //variable to store receiving and sending string
    int n; // to store readline result

    while(Fgets(sendline, MAXLINE, stdin) != NULL ) {
        Fputs("sending: ", stdout);
        Fputs(sendline, stdout);
        Writen(sockfd, sendline, strlen(sendline));  //Writing to server socket
    }

    Shutdown(sockfd, SHUT_WR); //shutdown writing in sockfd

    while((n = Readline(sockfd, recvline, MAXLINE)) != 0 ) { 
        Fputs(recvline, stdout); //Put what ever is received to stdout
    }
}

int main(int argc, char**argv) { 
    int sockfd; //sockfd is filedescriptor for socket created 
    struct sockaddr_in servaddr; //struct to store server address and info
    char* ipaddress;

    setExitFlags(); //initialize exit flags

    int servPort = SERV_PORT;  //default port set

    if (argc < 2 || argc > 3) { //ipaddress part not available
        fprintf(stderr, "Usage: %s <IPaddress> [PORT]\n", argv[0]); 
        exit(USAGE_ERROR);
    }
    ipaddress = argv[1];

    if(argc == 3) { //if port is passed through command, use that
        servPort = atoi(argv[2]);
    }


    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero (&servaddr, sizeof(servaddr) );
    servaddr.sin_family = AF_INET; //ipv4
    servaddr.sin_port = htons(servPort); //set port

    Inet_pton(AF_INET, ipaddress, &servaddr.sin_addr); //set ipaddress etc

    Connect(sockfd, (SA*) &servaddr, sizeof(servaddr));

    str_cli(sockfd);

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
