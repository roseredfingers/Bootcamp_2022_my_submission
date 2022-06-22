/* run using ./server <port> */
#include "http_server.hh"
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>

#include <pthread.h>

#define BUFFER_SIZE 2048
using namespace std;

void error(char *msg) {
  perror(msg);
  exit(1);
}

class threadPara{
  public:
  char* buffer;
  int newsockfd;

  threadPara(char* passedBuffer, int PassedNewSockfd){
    buffer = passedBuffer;
    newsockfd = PassedNewSockfd;
  }
};

void* ClientHandling(void* parameters){
  //Reads messages from client
  threadPara parameter = *(threadPara*) parameters;
  char* buffer = parameter.buffer;
  int newsockfd = parameter.newsockfd;

  bzero(buffer, BUFFER_SIZE);
  int n;
  n = read(newsockfd, buffer, BUFFER_SIZE-1);
  if(n < 0){
    error("Error reading from socket");
  }
  string req (buffer, buffer + n);

  HTTP_Response *response = handle_request(req);
  string res = response->get_string();

  n = write(newsockfd, res.c_str(), res.length()-1);
  if( n < 0){
    error("Error writing to socket");
  }

  delete response;
  return 0;
}

int main(int argc, char *argv[]) {
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in serv_addr, cli_addr;

  if (argc < 2) {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }

  /* create socket */

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");

  /* fill in port number to listen on. IP address can be anything (INADDR_ANY)
   */
  memset((char*)&serv_addr, 0, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  /* bind socket to this port number on this machine */

  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  /* listen for incoming connection requests */

  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  cout<<"Server running...\n";
  /* accept a new request, create a newsockfd */



  while(1){
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    error("ERROR on accept");

    pthread_t thread_id;

    threadPara parameters = threadPara(buffer, newsockfd);
    //Creating separate thread for client
    pthread_create(&thread_id, NULL, ClientHandling, &parameters);
  }

  /* read message from client */

  /*bzero(buffer, 256);
  n = read(newsockfd, buffer, 255);
  if (n < 0)
    error("ERROR reading from socket");
  printf("Here is the message: %s", buffer);

  /* send reply to client */

  /*n = write(newsockfd, "I got your message", 18);
  if (n < 0)
    error("ERROR writing to socket");*/

  return 0;
}
