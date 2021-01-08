/*****************************************************************************
 * File name:   udp_server.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-20 13:17:58
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

/********************************* Macros *************************************/ 
#define PORT    8080 
#define MAXLINE 1024   
 

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Ping"; 
    struct sockaddr_in servaddr, cliaddr; 
      
    /* Creating socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    { 
        perror("socket creation failed"); 
        return (EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    /* Filling server information */
    servaddr.sin_family      = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    /*Bind the socket with the server address */
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        perror("bind failed"); 
        return (EXIT_FAILURE); 
    } 
      
    int len, n; 
    while (1)
    {
    	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, 
        	(struct sockaddr *) &cliaddr, &len); 
    
        buffer[n] = '\0'; 
        sleep(1);
        printf("%s\n", buffer); 
        sendto(sockfd, (const char *)hello, strlen(hello),  
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
    }
 
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
