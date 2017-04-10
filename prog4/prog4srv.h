/*
    Auuthor : Nithin Devang
    Assignment # :4 
    zid: z1804837
*/

#include "wrap4srv.h"

#ifndef _PRG4_SRV_GUARD
#define _PRG4_SRV_GUARD

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

//#define MAXLINE 1001 

#define SERV_PORT 9880

#define QUELEN 5

extern BOOL exit_flags[]; //exit flags to decide if any wrapper calls to system calls should exit or continue

void setExitFlags(); // to initalise exit flags

/* method to split tokens*/
void split(const char* input, char* key, char* value); 

/* Sanitize string to remove newline*/
void sanitize (char* s);

/* method to process data */
void process (int confd);

/*handler method for signal*/
void sig_child(int signo); 


#endif
