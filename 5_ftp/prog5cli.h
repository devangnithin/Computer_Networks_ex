/*
    Author : Nithin Devang
    Assignment # : 5
    zid: z1804837
*/

#include "wrap5cli.h"

#ifndef _PRG5_CLI_GUARD
#define _PRG5_CLI_GUARD

#include "/home/cs631/common/config.h"
#include "/home/cs631/common/in-out.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

extern int exit_flags[]; //exit flags to decide if any wrapper calls to system calls should exit or continue

//#define MAXLINE 20

#define SERV_PORT 9880

#define SA struct sockaddr

#define USAGE_ERROR 10

typedef enum { NEG_ = -1, ZERO_, QM_, BYE_, CD_, CDUP_, CLOSE_, DISCONNECT_, HELP_, LCD_, OPEN_, PWD_, QUIT_ } cmd_id; 

//extern const char* cmds [ ] = { "", "?", "bye", "cd", "cdup", "close", "disconnect", "help", "lcd", "open", "pwd", "quit" };

/* utility methid to set exit flags*/
void setExitFlags();

/* function returns corresponding enums based on command passed*/
int find_id(char* cmd ); 

/*
function to take user input and split into string and return the enum representing the command
@param: buf, string to be parsed
@param command where command should be split
@arg1 and arg2 are respective arguments
@return: enum representing the command
*/
cmd_id get_args(char* buf, char* cmd, char* arg1, char* arg2);

/*a
takes payload command and prints the help text for the command
*/
void help(char* payload);

/*
method to change directory localy
@param : directory path
@return bool: true on success and false on failure
*/
BOOL new_dir(char* dir);

/*
helps open method to initiate connection to ftp server
@param: ipaddress
@param port
@param prompt to show disconenction
*/
void client(char* ipaddress, int port, BOOL prompt);
#endif
