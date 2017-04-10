#include "prog4srv.h"

int main ( int argc, char *argv[] ) {
    ssize_t n;
    int i, maxi, maxfd;
    int listenfd, connfd, sockfd;
    int nready, client [ FD_SETSIZE ];
    fd_set rset, allset;
    struct sockaddr_in servaddr;
    char line [ MAXLINE ];

    int servPort = SERV_PORT; //default port

    if(argc > 2 ) {
        fprintf(stderr, "Usage: %s [PORT]\n", argv[0]);
    }

    if(argc == 2) { //if port is passed as command line argument
        servPort = atoi(argv[1]);
    }

    setExitFlags(); //initialize exit flags
    listenfd = Socket ( AF_INET, SOCK_STREAM, 0 );

    bzero ( &servaddr, sizeof ( servaddr ) );
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl ( INADDR_ANY );
    servaddr.sin_port = htons ( servPort );

    Bind ( listenfd, ( SA* ) &servaddr, sizeof ( servaddr ) );
    Listen ( listenfd, QUELEN);

    maxfd = listenfd; maxi = -1;
    for ( i = 0; i < FD_SETSIZE; i++ ) client [ i ] = -1;
    FD_ZERO ( &allset ); FD_SET ( listenfd, &allset );

    double sum = 0; //to store the sum
    double exp = 0; //to store exponent
    int exprcvd = 0; //to check if exponent is received

    while ( TRUE ) {
        rset = allset;
        nready = Select ( maxfd + 1, &rset, 0, 0, 0 );


        if ( FD_ISSET ( listenfd, &rset ) ) {
            connfd = Accept ( listenfd, 0, 0 );

            for ( i = 0; i < FD_SETSIZE && client [ i ] >= 0; i++ );
            if ( i < FD_SETSIZE ) client [ i ] = connfd;
            else {
                fprintf ( stderr, "too many clients\n" ); exit ( 1 );
            }

            FD_SET ( connfd, &allset );
            if ( connfd > maxfd ) maxfd = connfd;
            if ( i > maxi ) maxi = i;
            nready--;
        }
        for ( i = 0; i <= maxi && nready > 0; i++ ) {
            sockfd = client [ i ];
            if ( sockfd >= 0 && FD_ISSET ( sockfd, &rset ) ) {
                if ( ( n = Readline ( sockfd, line, MAXLINE ) ) == 0 )
                {
                    char buffer [50];
                    int bufl = sprintf(buffer, "Sum of all numbers is = %.2f\n", sum);
                    if (sum -(int)sum == 0) bufl = sprintf(buffer, "Sum of all numbers is = %.0f\n", sum); 
                    Writen ( sockfd, buffer, bufl );
                    FD_CLR ( sockfd, &allset ); client [ i ] = -1;
                    Close ( sockfd );
                    sum = 0;
                    exprcvd = 0;
                }
                else {
                   sanitize(line); //remove new line
                   if ( !exprcvd ) {
                       exp = atof(line);
                       exprcvd = 1;
                   } else  {
                       sum = sum + pow(atof(line), exp);
                   }
                }
                nready--;
            }
        }


    }

    Close ( listenfd ); exit ( 0 );
}

/*
sanitizing string to remove new line
*/
void sanitize (char* s) {
        int i =0;
        while (s[i] != '\r' && s[i] != '\n') { //Some windows machine send \r\n as carriage return :(
                i++;
        }
        s[i]= '\0';
        return;
}

/*
method to set exit flags
*/
void setExitFlags() {
    int i;
    for (i = 0; i <= NFLAGS; i++) {
        exit_flags[i] = 1;
    }
}

