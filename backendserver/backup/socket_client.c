#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, int **argv)
{
    int cmd_opt = 0;
    char* mode;
    char* account; 
    char* password;
    char* seprate = "~";
    while(1)
    {
    
        cmd_opt = getopt(argc, argv, "m:a:p:");
        
        if(cmd_opt == -1)
        {
            break;
        }
    
        switch(cmd_opt)
        {
            //get mode
            case 'm':            
                //printf("mode: %s\n", optarg);
                mode = optarg;
                break;

            case 'a':
                //printf("account: %s\n", optarg);
                account = optarg;
                break;

            //get mode
            case 'p':
                //printf("password: %s\n", optarg);
                password = optarg;
                break;
        }
    }
    

    char *message = malloc(strlen(mode) + strlen(account) + strlen(password) + 3);
    strcpy(message, mode);
    strcat(message, seprate);
    strcat(message, account);
    strcat(message, seprate);
    strcat(message, password);

    printf("%s\n", message);
    //printf("%d\n", strlen(message));
    
    
    int socket_fd = 0;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_fd == -1)
    {
        printf("FAIL to create socket");
        return 0;
    }
    
   
    //socket connect
    struct sockaddr_in info;
    bzero(&info, sizeof(info));
    info.sin_family = PF_INET;
    
    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(10010);

    int err = connect(socket_fd, (struct sockaddr *)&info, sizeof(info));
    if(err == -1)
    {
        printf("Connection error");
    }

    char receiveMessage[100] = {};
    send(socket_fd, message, strlen(message), 0);
    recv(socket_fd, receiveMessage, sizeof(receiveMessage),0);

    printf("%s\n", receiveMessage);
    printf("close socket\n");
    close(socket_fd);




    
    
    return 0;
}
