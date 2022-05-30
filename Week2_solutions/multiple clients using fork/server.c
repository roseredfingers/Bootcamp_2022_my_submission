#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define PORT 4444

int main(){

    int sockfd, ret;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    int newSocket;
    struct sockaddr_in newAddr;

    char buffer[1024];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        printf("[-]Connection error.\n");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
    printf("[-]Binding error.\n");
    exit(1);
    }
    printf("[+]Bind to port %d\n", PORT);
    if(listen(sockfd, 3) == 0){
        printf("[+]Listening...\n");
    }
    else{
    printf("[-]Binding error.\n");
    exit(1);       
    }

    while(1){
        newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
        if(newSocket < 0){
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
        bzero(buffer, sizeof(buffer));
        if((childpid = fork()) == 0){
            close(sockfd);

            while(1){
                recv(newSocket, buffer, 1024, 0);
                if(strcmp(buffer, ":exit") == 0){
                    printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break;
                }
                else{
                    printf("Client: %s\n", buffer);
                    send(newSocket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }
    close(newSocket);

    return 0;
}