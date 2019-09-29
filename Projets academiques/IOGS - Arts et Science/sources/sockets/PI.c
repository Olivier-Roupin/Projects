/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TAILLE 6144 //32*32*6
#define LONGUEUR 96 //32*3
#define HAUTEUR 64 //32*2

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    char buffer[TAILLE];
    struct sockaddr_in serv_addr, cli_addr;
    int i;

    if(argc < 2)
    {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
    if(newsockfd < 0)
        error("ERROR on accept");

    while(1)
    {
        bzero(buffer,TAILLE);
        n = read(newsockfd,buffer,TAILLE);
        if(n < 0)
            error("ERROR reading from socket");

        system("clear");
        for(i = 0; i < TAILLE; i++)
        {
            printf("%d ",buffer[i]);
            if(not((i+1) % LONGUEUR))
                printf("\n");
        }

        n = write(newsockfd,"ACK",3);
        if(n < 0)
            error("ERROR writing to socket");
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
