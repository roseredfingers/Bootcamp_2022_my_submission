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

    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0){
        printf("[-]Connection error.\n");
        exit(1);
    }
    printf("[+]Client socket created successfully.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
        printf("[-]Connection error.\n");
        exit(1);
    }
    printf("[+]Connected to server.\n");

    while(1){
        bzero(buffer, sizeof(buffer));
        printf("Client: \t");
        scanf("%s", &buffer[0]);
        send(clientSocket, buffer, strlen(buffer), 0);

        if(strcmp(buffer, ":exit") == 0){
            close(clientSocket);
            printf("Disconnected from server.\n");
            exit(1);
        }

        if(recv(clientSocket, buffer, strlen(buffer), 0) < 0){
            printf("Error in receiving the message.\n");
        }
        else{
            printf("Server: \t%s\n", buffer);
        }
    }

    return 0;
}