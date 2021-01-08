/*****************************************************************************
 * File name:   udp_client.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-20 13:17:51
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
    char *hello = "Pong"; 
    struct sockaddr_in servaddr; 
  
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    { 
        perror("socket creation failed"); 
        return (EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n, len; 
     
    while (1)  
    {
    	sendto(sockfd, (const char *)hello, strlen(hello), 
            MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
              
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
        buffer[n] = '\0'; 
        sleep(1);
        printf("%s\n", buffer); 
    }
  
    close(sockfd); 
 
    return (EXIT_SUCCESS);
} 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 

