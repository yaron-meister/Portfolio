/*****************************************************************************
 * File name:   tcp_server.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-20 11:21:58
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

/********************************* Macros *************************************/ 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr  
 
/************************** Forward Declarations ******************************/
void Chat(int sockfd);

/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    /*socket create and verification*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if (-1 == sockfd) 
    { 
        perror("sockfd"); 
        return (EXIT_FAILURE); 
    } 
    
	bzero(&servaddr, sizeof(servaddr)); 
  
    /*assign IP, PORT */
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    /*Binding newly created socket to given IP and verification */
    if (0 != (bind(sockfd, (SA*)&servaddr, sizeof(servaddr)))) 
    { 
        perror("bind"); 
        return (EXIT_FAILURE); 
    } 
  
    /*Now server is ready to listen and verification */
    if (0 != (listen(sockfd, 5))) 
    { 
        perror("listen"); 
        return (EXIT_FAILURE); 
    } 
    
    len = sizeof(cli); 
  
    /*Accept the data packet from client and verification */
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) 
    { 
        perror("connfd"); 
        return (EXIT_FAILURE); 
    } 
  
    /*Function for chatting between client and server */
    Chat(connfd); 
  
    /*After chatting close the socket */
    close(sockfd); 
 
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/   
/*Function designed for chat between client and server. */
void Chat(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    /*infinite loop for chat */
    for (;;) 
    { 
        bzero(buff, MAX); 
  
        /*read the message from client and copy it in buffer */
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        /*copy server message in the buffer */
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        /*and send that buffer to client */
        write(sockfd, buff, sizeof(buff)); 
  
        /*if msg contains "Exit" then server exit and chat ended. */
        if (strncmp("exit", buff, 4) == 0) 
        { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
  

