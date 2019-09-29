#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define TAILLE 6144 //32*32*6
#define LONGUEUR 96 //32*3
#define HAUTEUR 64 //32*2

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    int i;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char image[TAILLE];
    char buffer[TAILLE];

    if(argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if(server == NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    bzero(image,TAILLE);
    bzero(buffer,TAILLE);
    while(1)
    {
        system("clear");
        for(i = 0; i < TAILLE; i++)
        {
            image[i]+=64;
            //if(image[i] == 25)
            //    image[i] = 0;
            buffer[i] = image[i];
            //printf("%d ",buffer[i]);
            //if(not((i+1) % LONGUEUR))
            //    printf("\n");
        }

        n = write(sockfd,buffer,TAILLE);
        if(n < 0)
            error("ERROR writing to socket");

        n = read(sockfd,buffer,255);
        if(n < 0)
            error("ERROR reading from socket");
    }

    close(sockfd);
    return 0;
}
