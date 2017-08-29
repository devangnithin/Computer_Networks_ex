/*
    Author : Nithin Devang
    Assignment # : 5
    zid: z1804837
*/

#include "prog5cli.h"

int main() { 

    char input[MAXLINE]; //to store user commands
    while (TRUE) { //Continuously read user inputs when in FTP command.
        char arg1[MAXLINE] = "", arg2[MAXLINE] = "", arg3[MAXLINE] = ""; //to split user input to commands and arguments
        Fputs("ftp>", stdout);
        Fgets(input, MAXLINE, stdin); //read commands

        int commandId = get_args(input, arg1, arg2, arg3); //process commands

        switch (commandId) { //switching user commands
            case HELP_:
                help(arg2);
                break;

            case OPEN_:
                if(arg2 == 0 || arg2[0] == 0) {
                    Fputs(" (to) ", stdout);
                    Fgets(input, MAXLINE, stdin);
                    sscanf(input, "%s %s", arg2, arg3); //if arg3 is null and atoi will return 0.
                } 
                client(arg2, atoi(arg3), FALSE); 
                break;
            case CLOSE_: //all cases where connections are needed
            case DISCONNECT_:
            case CD_:
            case CDUP_:
            case PWD_:
                Fputs("Not connected.\n", stdout);
                break;

            case LCD_:
                if(arg2 == 0 || arg2[0] == 0 ) { //if optional argument is not present change to home
                     new_dir(getenv("HOME"));
                }
                else {
                    new_dir(arg2);
                }
                if (errno != 0)  fprintf(stderr, "Unable to change directory %s\n", strerror(errno));
                errno = 0;
                break;

            case BYE_:
            case QUIT_:
                Fputs("Goodbye\n", stdout);
                return 0;
            case NEG_:
                Fputs("?Invalid command\n", stdout);
                break;
        } 
    }

    return 0;
}
