#include "prog4srv.h"


int main(int argc, char *argv[]) {
    int i, maxi, maxfd;
    int listenfd, connfd, sockfd; //listening and connection file descriptor
    ssize_t n;

    int nready, client [FD_SETSIZE];
    fd_set rset, allset;
    char line[MAXLINE];

    struct sockaddr_in servaddr;

    int servPort = SERV_PORT; //default port

    if(argc > 2 ) {
        fprintf(stderr, "Usage: %s [PORT]\n", argv[0]);
    }
        
    if(argc == 2) { //if port is passed as command line argument
        servPort = atoi(argv[1]);
    }

    setExitFlags(); //initialize exit flags

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof( servaddr ));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
    servaddr.sin_port = htons( servPort );

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    Listen(listenfd, QUELEN); 

    /* initialize mux variable starts*/

    maxfd = listenfd;
    maxi = -1;

    for(i = 0; i<FD_SETSIZE; i++) {
        client[i] = -1;
    }

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    /* Initialize mux variable ends*/

    while(TRUE) { //Continuously process request inside loop 
        rset = allset;
        nready = select(maxfd + 1, &rset, 0, 0, 0); //TODO wrap 
printf("nready now = %d \n", nready);

        if(FD_ISSET(listenfd, &rset)) {
printf("listening set\n");
            connfd = Accept(listenfd, 0, 0);
printf("accepted\n");
            for ( i = 0; i < FD_SETSIZE && client[i] >=0; i++ ); 
            if ( i < FD_SETSIZE) { 
                client [ i ] = connfd;
printf("confd assigned for processing\n");
}
            else {
                fprintf( stderr, "too many clients \n ");
                exit (1);
            }
            FD_SET(connfd, &allset);
printf("fd set\n");
            if( i > maxi) maxi = i;
            nready-- ;
        }
printf("nready now %d\n", nready);
        int sum = 0;

        for ( i = 0; i<= maxi && nready > 0; i++) {
            sockfd = client [i];
printf("in ;loop\n");
            if( sockfd >= 0 && FD_ISSET(sockfd, &rset)) {
printf("sockfd set\n");
                if(( n = Readline ( sockfd, line, MAXLINE)) == 0)
                {
                    sum = sum + (atoi(line), 2);
printf("new sum %d\n", sum);
                    FD_CLR(sockfd, &allset);
                    client [i] = -1;
                    Close (sockfd);
                 }
                 else Writen ( sockfd, line , n );
                 nready --;
             }
        }
printf("returning to main loop\n");    
    }
    Close(listenfd);
    return 0;
}

/*
method to process the request received from client*/
/*void process (int confd) {
    FILE * fp;
    fp = Fopen("/home/cs631/common/books.d","r");
    char recvline[MAXLINE], fileline[MAXLINE]; //string to store received line and sending line
    //char key[MAXLINE], value[MAXLINE];
    while(Readline(confd, recvline, MAXLINE) != 0) { //readling client request
        int found = 0;
        while((Fgets(fileline, MAXLINE, fp)) != NULL) { //read line by line from file
            char key[MAXLINE], value[MAXLINE];
            split(fileline, key, value); //split line based on tokens
            sanitize(recvline); //sanitize input to remove new line character
            if(!strcasecmp(key, recvline)) {
                 Writen(confd, value, strlen(value)); //invoking wrapper to write response 
                 found = 1;
                 break;
            }
        }
        if(!found) {
            char notFound[20] = "Not found\n";
            writen(confd, notFound, strlen(notFound)); //invoking wrapper to write response i//TODO wrap
        }
        Rewind(fp); //rewind file pointer to starting position for new key
    }
    Fclose(fp);
    return;
} */

/*
method to set exit flags
*/
void setExitFlags() {
    int i;
    for (i = 0; i <= NFLAGS; i++) {
        exit_flags[i] = 1;
    }
}
