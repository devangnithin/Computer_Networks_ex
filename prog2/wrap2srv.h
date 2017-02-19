/*
    Author : Nithin Devang
    Assignment # : 1
    zid: z1804837
*/

#ifndef _PRG2_WRAP_GUARD
#define _PRG2_WRAP_GUARD

#define BOOL int
#define FALSE 0
#define TRUE 1

#define NFLAGS 6  

#define SOCKET 1
#define LISTEN 2 
#define BIND 3
#define ACCEPT 4
#define WRITE 5
#define CLOSE 6

#define SA struct sockaddr


#include "/home/cs631/common/config.h"
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


#endif
