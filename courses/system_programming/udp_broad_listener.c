/*****************************************************************************
 * File name:   udp_broad_listener.c
 * Developer:   Yaron Meister
 * Date:        2019-03-20 14:39:52
 * Description: UDP broadcasting Listener
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
#define PORT    9876 
#define MAXLINE 1024 
 
/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	int sockfd; 
    char buffer[MAXLINE]; 
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
    
    if (1 != inet_pton(AF_INET, "10.3.0.255", &servaddr.sin_addr)) 
    {
        perror ("inet_pton");
        return (EXIT_FAILURE);
    }

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        perror("bind failed"); 
        return (EXIT_FAILURE); 
    }

    int n, len; 
     
    while (1)  
    {
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
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
