/*
    Author : Nithin Devang
    Assignment # :4 
    zid: z1804837
*/

#ifndef _PRG4_WRAP_GUARD
#define _PRG4_WRAP_GUARD

#define BOOL int
#define FALSE 0
#define TRUE 1

#define NFLAGS 15  

#define SOCKET 1
#define LISTEN 2 
#define BIND 3
#define ACCEPT 4
#define WRITE 5
#define CLOSE 6
#define FORK 7
#define FGETS 8
#define FOPEN 9
#define READLINE 10
#define WRITEN 11
#define REWIND 12
#define FCLOSE 13
#define SIGNAL 14
#define SELECT 15

#define SA struct sockaddr
typedef void (*sighandler_t)(int);


#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>

    /*
        wrapper for socket function.
        @param int: AF_INET AF_INET6 indication ipv4 or ipv6
        @param: int decides tcp or udp
        @param: int: indicating protocol
        @return: int: file descriptor to Socket 
    */
    int Socket(int, int, int);

    /*
        wrapper for listen function.
        @param int:file descriptor where it should listen from 
        @param: int size of queue
        @return: int:  
    */
    int Listen(int, int);

    /*
        wrapper for bind function.
        @param int: file` descr where it should bind to
        @param: struct sockaddr 
        @param: number : address length
        @return: int:
    */ 
    int Bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen);

    /*
        wrapper for accept function.
        @param int: file descr where it should listen from
        @param: struct sock address
        @param: number lenght
        @return: int:
    */
    int Accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);

   /*
        wrapper for write function.
        @param int: file descr where it should listen from
        @param: reference to buffer
        @param: count : number of bytes 
        @return: size of byte read:
    */ 
    ssize_t Write(int fd, const void* buf, size_t count);

    /*
        Wrapper function to close the open file descriptor.
        @param int: filedescriptor
        @return int: 0 on success Exit with error code 8 on failure
    */ 
    int Close(int);

    /*
    wrapper for fork function
    @return process id of child, 0 for foked process
    */	
    pid_t Fork();

    /*
    wrapper for file open function
    @path of file
    *mode for reading or writing
    @return file pointer
*/
    FILE *Fopen(const char *path, const char *mode);

    /*
    Wrapper function to Fgets.
    @param char* string to be written
    @param int length of content
    @param File* file pointer where it should be written
    @return int: 
    */
    char* Fgets(char *s, int size, FILE *stream);

    /*
    wrapper for writen function
    @param int : file descriptor
    @s refernce where data should be written
    len length of data
    */
    ssize_t Writen (int, const void*, size_t);

    /*
    wrapper for readline function
    @param int filedescriptor
    @param void* referecnce to buffer where the data should be read
    @param len: size to be read
    */
    ssize_t Readline ( int, void*, size_t );

    /*
    wrapper for rewind function
    @param : filepointer 
    */
    void Rewind(FILE *stream);

    /*
    wrapper for fclose function
    @param file pointer to be close
    @return int indicating status
    */
    int Fclose(FILE *stream);

    /*
    wrapper fos ignal function
    @param int: signal number to be handled
    @param callback function
    @return sighandler_t number
    */
    sighandler_t Signal(int signum, sighandler_t handler);

/*
    wrapper fos ignal function
    @param int: signal number to be handled
    @param callback function
    @return sighandler_t number
    */
    int Select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);


#endif
