/*********************************************************************************************************************************
NAME                            : Satyanarayana
ASSIGNMENT NUMBER       : 5
DUE DATE                        : 4/28/2017.
*********************************************************************************************************************************/

#include "prog5cli.h"
#include "wrap5cli.h"


// This function is used to handle the client by connecting to the remote server by giving the ip adress and port number.Then it calls the subroutine str_cli to continue communication with the server.

int client(char* ag1,char* ag2)
{
    char ags[MAXLINE];
  int  portno;
 char* c=NULL;char* cc=NULL;
        if(ag1==NULL)
        {
 printf("(to)");

           fgets(ags,MAXLINE,stdin);
           ags[strlen(ags)-1] = '\0';

           char* eve = strtok(ags," ");
          if(eve!=NULL)
          {
                  //allocating memory to c.
           c = (char*) malloc(strlen(eve)*sizeof(char));

          strcpy(c,eve);
          }
        // store the splitted string.
          eve =strtok(NULL," ");
          if(eve!=NULL)
            {

              cc = (char*) malloc(strlen(eve)*sizeof(char));
        strcpy(cc,eve);
 }
                //assigning the port number.
           if(cc==NULL) portno = SERV_PORT;
           else
           {
                   //converting the port number to integer.
                   portno = atoi(cc);
           }
        }
     if(ag1!=NULL)
        {
                        //copying the string
                        strcpy(ags,ag1);
                        //assigning the default port number.
        portno = SERV_PORT;
            }
        else if(ag2!=NULL)
        {
                portno = atoi(ag2);
        }
   // sockfd stores the socket information.
 int sockfd,in;

   struct sockaddr_in servaddr;
                 //calling the socket wrapper function to create a socket.
       sockfd = Socket(AF_INET, SOCK_STREAM, 0);

       bzero(&servaddr, sizeof(servaddr));

       servaddr.sin_family = AF_INET;
    // htons converts the host byte order to network byte order
       servaddr.sin_port = htons(portno);
    // calling the inet_pton wrapper function inorder to convert the ip adress  
      in = Inet_pton(AF_INET, ags, &servaddr.sin_addr);
	  if (in <1) {
		fputs("Inet_pton error", stdout);
	  }
        // calling the connect wrapper function inorder to connect to the server.
               Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

                        b=1;
                        printf(" \n connected to %s \n",ags);
 printf("ftp> ");
                        char buf[MAXLINE];
  while( fgets(buf,MAXLINE,stdin))
 {

   char buff[MAXLINE];
   strcpy(buff,buf);
   char* cmd = NULL;
   char* arg1=NULL; char* arg2 = NULL;
   //checking for the command length.
   if(strlen(buff) > 1)
   {

        buff[strlen(buff) -1]='\0';
        buf[strlen(buf)-1] = '\0';

        char* event;
        event = strtok(buff," ");
        if(event!=NULL)
        {
 cmd = (char*) malloc(strlen(event) * sizeof(char));

     strcpy(cmd,event);
        }

        event = strtok(NULL," ");
        if(event!=NULL)
        {

                arg1=(char*) malloc(strlen(event)*sizeof(char));

                strcpy(arg1,event);
        }
        event = strtok(NULL," ");
        if(event!=NULL)
        {
                //allocating memory.
                arg2 = (char*) malloc(strlen(event)*sizeof(char));
                strcpy(arg2,event);
        }
        //getting the vaalue of cmd_id SOCK_STREAM value to give input to the switch case.
cmd_id j = find_id(cmd);
   switch(j)
    {
     case NEG_:
                                //not a vlaid command.
                                printf("not a valid command \n"); break;
     case ZERO_:
                                //if not a valid command.
                                printf("\n"); break;
     case QM_:
                                //calling the QMARK function.
                                QMARK(arg1,arg2); break;
     case HELP_:
                                        //calling the HELP function.
                                HELP(arg1,arg2);
                                break;
     case BYE_:
                                //closing the socket and terminating the program.
                                Close(sockfd);
                                exit(0);
 break;
    case QUIT_:
                                //closing the socket and terminating the program.
                                Close(sockfd);
                                 exit(0);
                                 break;
    case CLOSE_:
                                //closing the socket.
                                Close(sockfd);
                                puts("\n Goodbye");
                                //changing the connection related variable.
                                      b=0;
                                  return 1;
                                break;
    case DISCONNECT_:
                                //closing the socket.
                                Close(sockfd);
                                puts("\n Goodbye");
                                //changing the connection related variable.
                                 b=0;
return 1;
                                 break;
    case OPEN_:
                                //checking for the double open.
                                if(b==1)
                                 {
                                        printf("already in connection. first close the connection\n");
                                 } break;
    case LCD_:
                                //calling the LCD function.
                                LCD(arg1,arg2);
                                break;

    case CD_: if(arg1==NULL)
                                {

                    char ar[MAXLINE];
                                        printf("(remote directory)");

                                        fgets(ar,MAXLINE,stdin);
ar[strlen(ar)-1] = '\0';
                                        unsigned j=0;

                                        buf[strlen(buf)] = ' ';
                                        for(unsigned i=strlen(buf);i<(strlen(buf))+strlen(ar);i++)
                                                buf[i] = ar[j++];
                                }

                                 str_cli(sockfd,buf,strlen(buf));               
                                  break;
   case CDUP_:

                                str_cli(sockfd,buf,strlen(buf)); break;
   case PWD_:

                                str_cli(sockfd,buf,strlen(buf)); break;
   default:
                                printf("no commands \n");
     }
 }
   printf("ftp> ");
 }
                //closing the socket.
        Close(sockfd);
//}
return 0;
}
void str_cli(int sockfd,char param[],size_t size)
{
                //store the message.
    char recvline[MAXLINE];
                     param[size] = '\n';
       size_t len = strlen(param);
                                //writing the data to the socket inorder to get the response fro the server.
               Writen(sockfd, param, len);

        bzero(recvline,MAXLINE);
if( Readline(sockfd, recvline, MAXLINE) == 0)
                      {
                        fprintf(stderr, "server terminated prematurely\n");
                      }
                          //printing the response
            if(recvline[0]=='0')
                                puts("Sucessfully changed remote diretory");
               else if(recvline[0]=='1')
                                   puts("unsucess while changing remote diretory");
              else Fputs(recvline, stdout);

           bzero(recvline,MAXLINE);
             }

