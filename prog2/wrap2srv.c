#include "wrap2srv.h"

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
    wrapper for listen function.
    @param int: file descr where it should listen from
    @param: int queue size 
    @return: int:  
*/
int Listen (int sockfd, int backlog) {
    int res; //result of listen
    
    errno = 0;
    if((res = listen(sockfd, backlog) != 0)) {
        fprintf(stderr, "Listen failed %s\n", strerror(errno));
        if(exit_flags[LISTEN]) {
            exit(LISTEN);
        }
   }
   return res;
}

/*
    wrapper for bind function.
    @param int: file` descr where it should bind to
    @param: struct sockaddr 
    @param: number : address length
    @return: int:
*/
int Bind (int sockfd, const SA* addr, socklen_t addrlen) {
    int res; //result of bind

    errno = 0;
    if((res = bind(sockfd, addr, addrlen) != 0)) {
        fprintf(stderr, "Bind failed %s\n", strerror(errno));
        if(exit_flags[BIND]) {
            exit(BIND);
        }
   }
   return res;
}

/*
    wrapper for accept function.
    @param int: file descr where it should listen from
    @param: struct sock address
    @param: number lenght
    @return: int:
*/
int Accept(int sockfd, SA* addr, socklen_t* addrlen) {
    int res; //result of accept

    errno = 0;
    if((res = accept(sockfd, addr, addrlen)) == -1) {
        fprintf(stderr, "Accept failed %s\n", strerror(errno));
        if(exit_flags[ACCEPT]) {
            exit(ACCEPT);
        }
   }
   return res;
}


/*
    wrapper for write function.
    @param int: file descr where it should listen from
    @param: reference to buffer
    @param: count : number of bytes 
    @return: size of byte read:
*/

ssize_t Write(int fd, const void* buf, size_t count) {
    int res; //result of write

    errno = 0;
    if((res = write(fd, buf, count) == -1)) {
        fprintf(stderr, "Write failed %s\n", strerror(errno));
        if(exit_flags[WRITE]) {
            exit(WRITE);
        }
   }
   return res;
}

/*
    Wrapper function to close the open file descriptor.
    @param int: filedescriptor
    @return int: 0 on success Exit with error code 8 on failure
*/
int Close(int fild) {
    int n; //return value of close

    if ((n = close(fild)) < 0) {
        fprintf(stderr, "Unable to close:: %s\n", strerror(errno));
        if(exit_flags[CLOSE]) {
            exit(CLOSE);
        }
    }

    return n;
}
 
