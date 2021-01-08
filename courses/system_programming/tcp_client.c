/*****************************************************************************
 * File name:   tcp_client.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-20 11:21:53
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <netdb.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/********************************* Macros *************************************/ 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr  
 
/************************** Forward Declarations ******************************/
void Chat(int sockfd);
 
/***************************** Global variables *******************************/


/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    /*socket create and varification */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (-1 == sockfd) 
    { 
        printf("socket creation failed...\n"); 
        return (EXIT_FAILURE); 
    } 
    
    bzero(&servaddr, sizeof(servaddr)); 
  
    /*assign IP, PORT*/ 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
  
    /*connect the client socket to server socket*/ 
    if (0 != connect(sockfd, (SA*)&servaddr, sizeof(servaddr))) 
    { 
        printf("connection with the server failed...\n"); 
        return (EXIT_FAILURE); 
    } 
  
    /*function for chat*/ 
    Chat(sockfd); 
  
    /*close the socket*/ 
    close(sockfd); 
 
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
void Chat(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) 
    { 
        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        
        if ((strncmp(buff, "exit", 4)) == 0) 
        { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 

  
