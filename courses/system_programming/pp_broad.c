/*****************************************************************************
 * File name:   pp_broad.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-21 10:29:03
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
#define PORT    9877 
#define MAXLINE 1024   
 

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	int sockfd; 
    char buffer[MAXLINE]; 
    char* message = "Ping\n\n"; 
    struct sockaddr_in servaddr;
    int broadcast = 1; 
      
    // Creating socket file descriptor
    int n, len; 
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
    { 
        perror("socket");
        return (EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr));

    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
                                                               sizeof(int)) < 0)
    {
        perror("Setting local interface error\n");
        return (EXIT_FAILURE);
    }

    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY;  
      
    if (1 != inet_pton(AF_INET, "10.3.0.255", &servaddr.sin_addr)) 
    {
        perror ("inet_pton");
        return (EXIT_FAILURE);
    }

    int counter = 0;

    while (1)
    {
        if (2 == counter)
        {
            message = "Quit";
        }

    	// send hello message to server 
    	if (-1 == sendto(sockfd, (const char*)message, strlen(message), 
           	MSG_CONFIRM, (const struct sockaddr*)&servaddr, sizeof(servaddr)))
        {
        	perror("sendto");
        	return (EXIT_FAILURE);
        } 

	    // receive server's response 
	    if (recvfrom(sockfd, (char*)buffer, MAXLINE, 0, 
                                         (struct sockaddr*)&servaddr, &len) < 0)
        {
            perror("recvfrom");
            return (EXIT_FAILURE);
    	} 
        
        printf("Message from server: "); 
        puts(buffer);

    	sleep(1);
        ++counter;
    }

    close(sockfd); 

    return (EXIT_SUCCESS); 
} 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
