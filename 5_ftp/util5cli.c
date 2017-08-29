#include "prog5cli.h"

//list of user accepted commands
const char* cmds [ ] = { "", "?", "bye", "cd", "cdup", "close", "disconnect", "help", "lcd", "open", "pwd", "quit" };


/*
method to change directory localy
@param : directory path
@return bool: true on success and false on failure
*/
BOOL new_dir(char* dir) {
    char message[MAXLINE] = "";
    if(!strcmp(dir, "~")) snprintf(dir, MAXLINE, "%s", getenv("HOME"));
    errno =0;
    chdir(dir);
    if (errno != 0) {
        return FALSE;
    } else {
        getcwd(message, MAXLINE);
        fprintf(stdout, "directory now %s\n", message);
        return TRUE;
    }
}


/*
function to take user input and split into string and return the enum representing the command
@param: buf, string to be parsed
@param command where command should be split
@arg1 and arg2 are respective arguments
@return: enum representing the command
*/
cmd_id get_args(char* buf, char* cmd, char* arg1, char* arg2){
    sscanf( buf, "%s %s %s", cmd, arg1, arg2);
    return find_id(cmd);
}

/* function returns corresponding enums based on command passed*/
int find_id(char* cmd ) {
    if(!strcmp(cmd, "help") || !strcmp(cmd, "?")) {
       return HELP_;
    }
    if(!strcmp(cmd, "open")) {
        return OPEN_;
    }
    if(!strcmp(cmd, "cd")) {
        return CD_;
    }
    if(!strcmp(cmd, "bye")) {
        return BYE_;
    }
    if(!strcmp(cmd, "cdup")) {
       return CDUP_;
    }
    if(!strcmp(cmd, "close")) {
       return CLOSE_;
    }
    if(!strcmp(cmd, "disconnect")) {
       return DISCONNECT_;
    }
    if(!strcmp(cmd, "lcd")) {
       return LCD_;
    }
    if(!strcmp(cmd, "pwd")) {
       return PWD_;
    }
    if(!strcmp(cmd, "quit")) {
       return QUIT_;
    }
    return NEG_;
}

/*a
takes payload command and prints the help text for the command
*/
void help(char* payload) {
    if (strlen(payload) == 0 ) {
        fprintf(stdout, "Commands may be abbreviated.  Commands are:\n");
        for (int i = 1; i < 12; i++) {
            fprintf (stdout, "%-16s", cmds[i]);
            if (!(i % 5)) fprintf(stdout, "\n");
        }
        fprintf (stdout, "\n");
        return;
    }

    if(!strcmp(payload, cmds[2]) || !strcmp(payload, cmds[11])) { //bye
        fprintf(stdout, "%s\t Terminate the FTP session with the remote server and exit FTP. An EOF will also terminate the session and exit.\n", payload);
        return;
    }

    if(!strcmp(payload, cmds[1]) || !strcmp(payload, cmds[7])) { //?
        fprintf(stdout, "%s\t Print an informative message about the meaning of command. If no argument is given, FTP prints a list of the known commands.\n", payload);
        return;
    }

     if(!strcmp(payload, cmds[3])) { // cd
        fprintf(stdout, "%s\tChange the working directory on the remote machine to remote-directory\n", payload);
        return;
    }

    if(!strcmp(payload, cmds[4])) { //cdu
        fprintf(stdout, "%s\t Change the remote machine working directory to the parent of the current remote machine working directory.\n", payload);
        return;
    }

    if(!strcmp(payload, cmds[5])) { //close
        fprintf(stdout, "%s\t Terminate the FTP session with the remote server, and return to the command interpreter.\n", payload);
        return;
    }

    if(!strcmp(payload, cmds[6])) { //disconnect
        fprintf(stdout, "%s\t Terminate the FTP session with the remote server, and return to the command interpreter.\n", payload);
        return;
    }
    if(!strcmp(payload, cmds[8])) { //lcd
        fprintf(stdout, "%s\t change local working directory\n", payload);
        return;
    }
    if(!strcmp(payload, cmds[9])) {//open
        fprintf(stdout, "%s\t Establish a connection to the specified host FTP server. An optional port number may be supplied, in which case, FTP will attempt to contact an FTP server at that port.\n", payload);
        return;
    }

    if(!strcmp(payload, cmds[10])) {//pwd
        fprintf(stdout, "%s\t Print the name of the current working directory on the remote machine.\n", payload);
        return;
    }
}
