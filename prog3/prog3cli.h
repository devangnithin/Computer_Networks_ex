/*
    Author : Nithin Devang
    Assignment # : 1
    zid: z1804837
*/

#include "wrap3cli.h"

#ifndef _PRG3_CLI_GUARD
#define _PRG3_CLI_GUARD

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int exit_flags[]; //exit flags to decide if any wrapper calls to system calls should exit or continue

//#define MAXLINE 20

#define SERV_PORT 9880

#define SA struct sockaddr

#define USAGE_ERROR 10

/* utility methid to set exit flags*/
void setExitFlags();
#endif
