#include "wrap4srv.h"

BOOL exit_flags[NFLAGS + 1] = {FALSE}; //exit flags to decide if function should exit or continue

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
            Close( sockfd);
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
            Close(sockfd);
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
            Close ( sockfd );
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
            Close( fd );
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

    errno =0;
	if ((n = close(fild)) < 0) {
        fprintf(stderr, "Unable to close:: %s\n", strerror(errno));
        if(exit_flags[CLOSE]) {
            exit(CLOSE);
        }
    }

    return n;
}

 /*
    wrapper for fork function
    @return process id of child, 0 for foked process
*/
pid_t Fork() {
    pid_t n; //return value of close
    errno = 0;

    if ((n = fork()) < 0) {
        fprintf(stderr, "Unable to fork:: %s\n", strerror(errno));
        if(exit_flags[FORK]) {
            exit(FORK);
        }
    }

    return n;
}

/*
wrapper for file open function
@path of file
*mode for reading or writing
@return file pointer
*/
FILE *Fopen(const char *path, const char *mode) {
    errno = 0;

    FILE* fp;
    if((fp =  fopen(path, mode)) == NULL) {
        fprintf(stderr, "Unable to open file %s:: %s\n", path, strerror(errno));
        if(exit_flags[FOPEN]) {
            exit(FOPEN);
        } 
    }
    return fp;
}

/*
wrapper for fgets function
@param s : string to store data
size to be read
file to get from
returns string
*/
char* Fgets(char *s, int size, FILE *stream) {
    errno = 0;
    char* ret;
    //int n;
    if ((ret = fgets(s, size, stream)) == NULL) {
        if(errno != 0) {
            fprintf(stderr, "fgets failes:: %s\n", strerror(errno));
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
            Close (fd);
            exit(READLINE);
        }
    }
    return n;
}

/*
wrapper for rewind function
@param : filepointer
*/
void Rewind(FILE *stream) {
    errno = 0;
    rewind(stream);
    if(errno != 0) {
        fprintf(stderr, "rewind failes:: %s\n", strerror(errno));
        if(exit_flags[REWIND]) {
            exit(REWIND);
        }
    }
}

/*
wrapper for fclose function
@param file pointer to be close
@return int indicating status
*/
int Fclose(FILE *stream) {
    errno = 0;
    int n;
    if((n=fclose(stream)) != 0) {
        fprintf(stderr, "writen failes:: %s\n", strerror(errno));
        if(exit_flags[FCLOSE]) {
            exit(FCLOSE);
         }
    }
    return n;
}

/*wrapper fos ignal function
@param int: signal number to be handled
@param callback function
@return sighandler_t number
*/

sighandler_t Signal(int signum, sighandler_t handler) {
    errno = 0;
 
    sighandler_t r;

    if((r = signal(signum, handler))== SIG_ERR) {
        fprintf(stderr, "writen failed : %s\n", strerror(errno));
        if(exit_flags[SIGNAL]) {
            exit(SIGNAL);
         }
    }
    return r;
} 

int Select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout) {
    int n;
    if (( n = select(nfds, readfds, writefds, exceptfds, timeout)) <0 ) {
       fprintf(stderr, "select failed:: %s\n", strerror(errno));
        if(exit_flags[SELECT]) {
            exit(SELECT);
         } 
    }
    return n;
}
