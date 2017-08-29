/*
    Author : Nithin Devang
    Assignment # :5 
    zid: z1804837
*/

#ifndef _PRG5_CLI__WRAP_GUARD
#define _PRG5_CLI_WRAP_GUARD

#define BOOL int
#define FALSE 0
#define TRUE 1

#define NFLAGS 10

#define SOCKET 1
#define CONNECT 2 
#define READ 3
#define INETPTON 4
#define FPUTS 5
#define CLOSE 6
#define FGETS 7
#define WRITEN 8
#define READLINE 9
#define SHUTDOWN 10


#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"

//BOOL exit_flags[NFLAGS + 1] = {FALSE};

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

    /*
        wrapper for socket function.
        @param int: AF_INET AF_INET6 indication ipv4 or ipv6
        @param: int decides tcp or udp
        @param: int: indicating protocol
        @return: int: file descriptor to Socket 
    */
    int Socket(int, int, int);

    
    /*
        Creates connection to server.
        @param int: filedescriptor of socket
        @param struct sockaddr: pointer to the sock address structure
        @param number: length of sockaddr
        @return int : 0 or success, exit with error code 3 on failure.
    */
    int Connect(int, const struct sockaddr*, socklen_t);

    
    /*
        Read data from file descriptor and add to buffer.
        @param int : file descriptor of socket.
        @param: void* reference to buffer where data should be read to 
        @param int : count of bytes to be read
        @return int: no of count read. Exit on failure.
      
    */
    int Read(int, void*, size_t);

    /*
        converts ipv4 or ipv6 to binary form
        @param int: family
        @param src
        @param dst
        @return returns 1 on success
    */
    int Inet_pton(int, const char*, void*);

    /* 
    puts the content of string to file.
    @param string to put to ofile.
    @param file stream where data should be written.
    @return int . 0 on success, EOF or negative number on error, Exits with error code 7 on failure.
    */
    int Fputs(const char*s, FILE* stream); 

    /*
    Wrapper function to close the open file descriptor.
    @param int: filedescriptor
    @return int: 0 on success Exit with error code 8 on failure
    */ 
    int Close(int);

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
    wrapper forshutdown system call 
    */
    int Shutdown ( int, int );

#endif
