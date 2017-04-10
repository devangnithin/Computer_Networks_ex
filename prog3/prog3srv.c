#include "prog3srv.h"


int main(int argc, char *argv[]) {
    
    int listenfd, confd; //listening and connection file descriptor
  
    pid_t childpid; //variable to store child pid after fork

    struct sockaddr_in servaddr;

    int servPort = SERV_PORT; //default port

    if(argc > 2 ) {
        fprintf(stderr, "Usage: %s [PORT]\n", argv[0]);
    }
        
    if(argc == 2) { //if port is passed as command line argument
        servPort = atoi(argv[1]);
    }

    Signal(SIGCHLD, sig_child);
    setExitFlags(); //initialize exit flags

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(servPort);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, QUELEN); 

    while(TRUE) { //Continuously process request inside loop 
        confd = Accept(listenfd, 0, 0);
        if((childpid = Fork()) == 0) {  // This will execute only for child process
            Close(listenfd); //Child do not need to listen
            process(confd); // process request
            Close(confd); //close connection after completion
            exit(0);
       } 
        Close(confd); //parent do not need confd
    }
    Close(listenfd);
    return 0;
}

/*
method to process the request received from client*/
void process (int confd) {
    FILE * fp;
    fp = Fopen("/home/cs631/common/books.d","r");
    char recvline[MAXLINE], fileline[MAXLINE]; //string to store received line and sending line
    //char key[MAXLINE], value[MAXLINE];
    while(Readline(confd, recvline, MAXLINE) != 0) { //readling client request
        int found = 0;
        while((Fgets(fileline, MAXLINE, fp)) != NULL) { //read line by line from file
            char key[MAXLINE], value[MAXLINE];
            split(fileline, key, value); //split line based on tokens
            sanitize(recvline); //sanitize input to remove new line character
            if(!strcasecmp(key, recvline)) {
                 Writen(confd, value, strlen(value)); //invoking wrapper to write response 
                 found = 1;
                 break;
            }
        }
        if(!found) {
            char notFound[20] = "Not found\n";
            writen(confd, notFound, strlen(notFound)); //invoking wrapper to write response i//TODO wrap
        }
        Rewind(fp); //rewind file pointer to starting position for new key
    }
    Fclose(fp);
    return;
}

/* 
signal handler method to be called when child exits
*/
void sig_child(int signo) {
    wait(0); //wait for child process to return
    fprintf(stdout, "%d, signal received\n", signo);
    signal(SIGCHLD, sig_child); //calling signal again because some system unregister signal handler once called.
}

/*
method to split the file line based on token to key and value
*/
void split(const char* input, char* key, char* value) {
    int i = 0;
    while (input[i] != ':' && input[i] != '\0') {
       key[i] = input[i];
       i++;
    }
    key[i] = '\0';
    i++;
    int j = 0;
    while (input[i] != ':' && input[i] != '\0' && input [i] != '\n') {
        value[j++] = input[i++];
    }
    value[j] = '\n';
    value[j+1] = '\0';
    return;

}

/*
sanitizing string to remove new line
*/
void sanitize (char* s) {
        int i =0;
        while (s[i] != '\r' && s[i] != '\n') { //Some windows machine send \r\n as carriage return :(
                i++;
        }
        s[i]= '\0';
        return;
}

/*
method to set exit flags
*/
void setExitFlags() {
    int i;
    for (i = 0; i <= NFLAGS; i++) {
        exit_flags[i] = 1;
    }
}
