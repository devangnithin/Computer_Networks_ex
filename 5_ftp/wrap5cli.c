/*
    Author : Nithin Devang
    Assignment # : 4
    zid: z1804837
*/

#include "wrap5cli.h"

BOOL exit_flags[NFLAGS + 1] = {FALSE};

/*
    wrapper for socket function.
    @param int: AF_INET AF_INET6 indication ipv4 or ipv6
    @param: int decides tcp or udp
    @param: int: indicating protocol
    @return: int: file descriptor to Socket 
*/
int Socket(int domain, int type, int protocol) {
    int sockfd; //file descriptor for socket

    errno = 0;
    if((sockfd = socket(domain, type, protocol)) < 0) {
        fprintf(stderr, "Socket failed %s\n", strerror(errno));
        if(exit_flags[SOCKET]) {
            exit(SOCKET);
        }
    }

    return sockfd;
}


/*
    Creates connection to server.
    @param int: filedescriptor of socket
    @param struct sockaddr: pointer to the sock address structure
    @param number: length of sockaddr
    @return int : 0 or success, exit with error code 3 on failure.
*/
int Connect(int sockfd, const struct sockaddr* servaddr, socklen_t addrlen) {
    int n; //return value for connect
    errno = 0;
    if((n = connect(sockfd, servaddr, addrlen)) < 0) {
        fprintf(stderr, "Connect failed :( %s\n", strerror(errno));
        if(exit_flags[CONNECT]) {
            Close ( sockfd );
            exit(CONNECT);
        }
    }

    return n;
}


/*
    converts ipv4 or ipv6 to binary form
    @param int: family
    @param src
    @param dst
    @return returns 1 on success
*/
int Inet_pton(int af, const char* src, void * dst) {
    errno = 0;

    int res = inet_pton(af, src, dst);

    if (res == 0) {
        fprintf(stderr, "inet_pton failed, Not valid address\n");
        if(exit_flags[INETPTON]) {
            exit(INETPTON);
        }
    }

    if(res < 0) {
        fprintf(stderr, "inet_pton failed :: %s\n", strerror(errno));
        if(exit_flags[INETPTON]) {
            exit(INETPTON);
        }
    }

    return res; 
} 

/*
    Read data from file descriptor and add to buffer.
    @param int : file descriptor of socket.
    @param: void* reference to buffer where data should be read to 
    @param int : count of bytes to be read
    @return int: no of count read. Exit on failure.
*/
int Read(int sockfd, void* buf, size_t count) {
    errno = 0;

    int n = read(sockfd, buf, count);

    if(n < 0) {
        fprintf(stderr, "Read failed %s\n", strerror(errno));
        if(exit_flags[READ]) {
            Close ( sockfd );
            exit(READ);
        }
    }

    return n;
}

/* 
    wrapper puts the content of string to file.
    @param string to put to ofile.
    @param file stream where data should be written.
    @return int . 0 on success, EOF or negative number on error, Exits with error code 7 on failure.
*/
int Fputs(const char* s, FILE* stream){
    int n; //return value fputs

    errno = 0;
    if((n = fputs(s, stream)) == EOF || errno != 0) {
        fprintf(stderr, "Fputs failed %s\n", strerror(errno));
        if(exit_flags[FPUTS]) { 
            exit(FPUTS);
        }
    }
    return n;
}

/*
    Wrapper function to close the open file descriptor.
    @param int: filedescriptor
    @return int: 0 on success Exit with error code 8 on failure
*/
int Close(int filed) {
    int n; //return value of close

    if ((n = close(filed)) < 0) {
        fprintf(stderr, "Unable to close:: %s\n", strerror(errno));
        if(exit_flags[CLOSE]) {
            exit(CLOSE);
        } 
    }

    return n;
}

/*
    Wrapper function to Fgets.
    @param char* string to be written
    @param int length of content
    @param File* file pointer where it should be written
    @return int: 
*/
char* Fgets(char *s, int size, FILE *stream) {
    errno = 0;
    char* ret;
    //int n;
    if ((ret = fgets(s, size, stream)) == NULL) {
        if(errno != 0) {
            fprintf(stderr, "Unable to close:: %s\n", strerror(errno));
            if(exit_flags[FGETS]) {
                exit(FGETS);
            }
        }
    }
    return ret;
}


/*
wrapper for writen function
@param int : file descriptor
@s refernce where data should be written
len length of data
*/
ssize_t Writen (int fd, const void* s, size_t len) {
    errno = 0;
    ssize_t n;
    if((n= writen (fd, s, len)) < 0 ) {
        fprintf(stderr, "writen failes:: %s\n", strerror(errno));
        if(exit_flags[WRITEN]) {
            Close ( fd );
            exit(WRITEN);
        }
    }
    return n;
}

/*
wrapper for readline function
@param int filedescriptor
@param void* referecnce to buffer where the data should be read
@param len: size to be read
*/
ssize_t Readline ( int fd, void* s, size_t len) {
    errno = 0;
    ssize_t n;
    if((n= readline ( fd, s, len )) < 0 ) {
        fprintf(stderr, "writen failes:: %s\n", strerror(errno));
        if(exit_flags[READLINE]) {
            Close ( fd );
            exit(READLINE);
        }
    }
    return n;
}

/*
wrapper for  shutdown
@param len: size to be read
*/
int Shutdown ( int sockfd, int how) {
    errno = 0;
    ssize_t n;
    if((n= shutdown ( sockfd, how )) < 0 ) {
        fprintf(stderr, "shutdown failed:: %s\n", strerror(errno));
        if(exit_flags[SHUTDOWN]) {
            Close ( sockfd );
            exit(SHUTDOWN);
        }
    }
    return n;
}

