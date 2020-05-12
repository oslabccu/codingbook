#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <signal.h>
#include <arpa/inet.h>

//start continer
const char* docker_run = "docker run -d --net=bridge ";
const char* docker_name = " --name=";
const char* docker_password = " -e PASSWORD=";
const char* docker_PUID = " -e PUID=";
const char* docker_PGID = " -e PGID=";
const char* docker_system_limit = " --cpus=1 --cpuset-cpus=\"1-23\" ";
const char* docker_ip = " -P ";
const char* docker_external_folder = " -v /home/ccugrp/";
const char* docker_internal_folder = ":/config ";
const char* docker_image_version = " sp:0.4 ";

//remove_container
const char* docker_remove = "docker rm -f ";

//restart container
const char* docker_restart = "docker restart ";

//stop contianer
const char* docker_stop = "docker stop ";

//Start container
const char* docker_start = "docker start ";

//get contianer IP
const char* docker_get_container_IP = "docker ps --filter \"name=\" --format \"{{.Ports}}\" | awk -F ':' '{print $2}' | awk -F '-' '{print $1}'";


const char* host_ip = "140.123.97.31";
char* PGID;
const char* Successed = "10";
const char* Failed = "11";



//main function
char* Open_container(char* account, char* password);
bool Remove_container(char* account);
char* Restart_container(char* account);
bool Stop_container(char* account);
char* Start_container(char* account);

//sub function
int get_PGID();
char* get_PUID(char* account);
char* get_container_IP(char* account);


int main(int argc, char *argv[])
{   
    get_PGID();

    char* sperate = "~";
    //set up server socket
    char inputBuffer[256] = {};
    char message[] = {"HI,I'm server\n"};
    int socket_fd = 0, client_socket_fd = 0;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    printf("code server start\n");

    if(socket_fd == -1){
        printf("FAIL to create a socket\n");
    }

    //socket connect
    struct sockaddr_in server_info;
    struct sockaddr_in clinent_info;
    int addrlen = sizeof(clinent_info);
    bzero(&server_info, sizeof(server_info));

    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(10010);
    bind(socket_fd, (struct sockaddr *) &server_info, sizeof(server_info));
    listen(socket_fd, 5);
    printf("%d\n",socket_fd);

    pid_t pid;

    while(1)
    {
        client_socket_fd = accept(socket_fd, (struct sockaddr*) &clinent_info, &addrlen);

        pid = fork();

        if(pid == -1)
        {
            printf("fork failed\n");
        }
        if(pid == 0)
        {
        
            
        }
        
/*
        recv(client_socket_fd, inputBuffer, sizeof(inputBuffer), 0);
        printf("Get:%s\n", inputBuffer);
        //printf("%d\n", socket_fd);
        
        char* mode = strtok(inputBuffer, sperate);
        //char* account = strtok(NULL, sperate);
        //char* password = strtok(NULL, sperate);
        //printf("%s %s %s\n", mode, account, password);
        
        //01 open_container
        if(strcmp(mode, "01") == 0)
        {
            char* account = strtok(NULL, sperate);
            char* password = strtok(NULL, sperate);
            //printf("%s %s\n", account) password);
            char* address = Open_container(account, password);
            if(strcmp(address, Failed) == 0)
            {
                printf("Failed to open container %s\n", account);
                send(client_socket_fd, Failed, strlen(Failed), 0); 
            }
            else
            {    
                send(client_socket_fd, address, strlen(address), 0);
                printf("Open container %s on port %s\n", account, address);
            }
        }
        //02 remove_container 
        else if(strcmp(mode, "02") == 0)
        {
            char* account = strtok(NULL, sperate);
            printf("Start remove container %s\n", account);
            bool check = Remove_container(account);
            if(check)
            {
                printf("Successed to remove container %s\n", account);
                send(client_socket_fd, Successed, strlen(Successed), 0);
            }
            else
            {
                printf("Failed to remove container %s\n", account);
                send(client_socket_fd, Failed, strlen(Failed), 0);
            }
            
        }
        //restart continer
        else if(strcmp(mode, "03") == 0)
        {
            char* account = strtok(NULL, sperate);
            printf("Start restart container %s\n", account);
            char* check = Restart_container(account);
            if(strcmp(check, Failed) == 0)
            {
                printf("Failed to restart continer %s\n", account);
                send(client_socket_fd, Failed, strlen(Failed), 0);
            }
            else
            {
                printf("Successed to restart continer %s\n", account);
                send(client_socket_fd, check, strlen(check), 0);
            }
        }
        //stop continer
        else if(strcmp(mode, "04") == 0)
        {
            char* account = strtok(NULL,sperate);
            printf("Start stop container %s\n", account);
            bool check = Stop_container(account);
            if(check)
            {
                printf("Successed to stop container %s\n", account);
                send(client_socket_fd, Successed, strlen(Successed), 0);
            }
            else
            {
                printf("Failed to stop container %s\n", account);
                send(client_socket_fd, Failed, strlen(Failed), 0);
            } 
        }
        //start container
        else if(strcmp(mode, "05") == 0)
        {
            char* account = strtok(NULL, sperate);
            printf("Start start container %s\n", account);
            char* check = Start_container(account);
            if(strcmp(check, Failed) == 0)
            {
                printf("Failed to Start container %s\n", account);
                send(client_socket_fd, Failed, strlen(Failed), 0);
            }
            else
            {
                printf("Successed to start container %s\n", account);
                send(client_socket_fd, check, strlen(check), 0);
            }
        }    
        else   
        {
            printf("Doesn't exist mode %s\n", mode);
            send(client_socket_fd, Failed, strlen(Failed), 0);
        }

        
    }

*/

    return 0;
}

//call docker run
char* Open_container(char* account, char* password)
{
    //store return ip address
    char* container_ip = "qwer";
    char* PUID = get_PUID(account);   
    //printf("%s\n", PUID); 

    char* cammand = malloc(strlen(docker_run) + strlen(docker_name) + strlen(account) + strlen(docker_password) + strlen(password) + strlen(docker_PGID) + strlen(PGID) + strlen(docker_PUID) + strlen(PUID) + strlen(docker_ip) + strlen(docker_external_folder) + strlen(account) + strlen(docker_internal_folder) + strlen(docker_image_version) + 1);
    strcpy(cammand, docker_run);
    strcat(cammand, docker_name);
    strcat(cammand, account);
    strcat(cammand, docker_password);
    strcat(cammand, password);
    strcat(cammand, docker_PGID);
    strcat(cammand, PGID);
    strcat(cammand, docker_PUID);
    strcat(cammand, PUID);
    strcat(cammand, docker_ip);
    strcat(cammand, docker_external_folder);
    strcat(cammand, account);
    strcat(cammand, docker_internal_folder);
    strcat(cammand, docker_image_version);   


   
    int check = system(cammand);
    
    if(check != 0)
    {
        //printf("Failed to open container %s\n", account);
        return (char*) Failed;
    }
    else
    {
        char* container_IP = get_container_IP(account);
        printf("%d\n", check);
        return container_IP;
    }
}

bool Remove_container(char* account)
{
    char* cammand = malloc(strlen(docker_remove) + strlen(account) + 1);
    strcpy(cammand, docker_remove);
    strcat(cammand, account);
    FILE *p;
    int a = system(cammand);
    if(a != 0)
    {
        //printf("Failed to remove container %s\n", account);
        return false;
    }
    
    return true;
}

char* Restart_container(char* account)
{
    char* cammand = malloc(strlen(docker_restart) + strlen(account) + 1);
    strcpy(cammand, docker_restart);
    strcat(cammand, account);
    FILE *p;
    int check = system(cammand);
    if(check != 0)
    { 
        return (char*) Failed;
    }
    char* result =  get_container_IP(account);
    return result;
}

bool Stop_container(char* account)
{
    char* cammand = malloc(strlen(docker_stop) + strlen(account) + 1);
    strcpy(cammand, docker_stop);
    strcat(cammand, account);
    FILE *p;
    int check = system(cammand);
    if(check != 0)
    {
        return false;
    }
    return true;
}

char* Start_container(char* account)
{
    char* cammand = malloc(strlen(docker_start) + strlen(account) + 1);
    strcpy(cammand, docker_start);
    strcat(cammand, account);
    FILE *p;
    int check = system(cammand);
    if(check !=0)
    {
        return (char*) Failed;
    }
    char* result = get_container_IP(account);
    return result;
}


int get_PGID()
{
    printf("Get PGID\n");
    char* c = "id -g ccugrp ";
    char buffer[10] = {};
    FILE *p;
    if((p = popen(c, "r")) == NULL)
    {
        printf("Failed to get PGID\n");
        exit(1);
    } 
    
    fgets(buffer, sizeof(buffer), p);
    PGID = malloc(sizeof(buffer));
    strcpy(PGID, buffer);
    PGID[strcspn(PGID, "\n")] = '\0';
    printf("PGID is %s\n", PGID);
    return 0;
}

char* get_PUID(char* account)
{
    printf("Get PUID\n");
    char* c = "id -u ";
    char buffer[10] = {};
    char* PUID;
    char* cammand = malloc(strlen(c) + strlen(account) + 1);
    strcpy(cammand, c);
    strcat(cammand, account);
    //printf("%s\n", cammand); 

    FILE *p;
    if((p = popen(cammand, "r")) == NULL)
    {
        printf("Failed to get PUID with %s\n", account);
        
    }

    fgets(buffer, sizeof(buffer), p);
    //printf("%s\n", buffer);
    PUID =  malloc(sizeof(buffer+1));
    strcpy(PUID, buffer);
    PUID[strcspn(PUID, "\n")] = '\0';
    //PUID[strlen(PUID-1)] = '\0';
    //printf("!!!%s %ld", PUID, strlen(PUID));
    return PUID;
}

char* get_container_IP(char* account)
{
    //printf("%c\n", docker_get_container_IP[24]);
    char* cammand = malloc(strlen(docker_get_container_IP) + strlen(account) + 1);
    strncpy(cammand, docker_get_container_IP, 25);
    strcat(cammand, account);
    strcat(cammand, docker_get_container_IP+25);
    //printf("%s\n", cammand);
    
    FILE *p;
    char buffer[30] = {};
    char* result;
    if((p = popen(cammand, "r")) == NULL)
    {
        printf("Failed to get container_ip with %s\n", account);
    }

    fgets(buffer, sizeof(buffer), p);
    result = malloc(sizeof(buffer+1));
    strcpy(result,buffer);

    return result;

}




