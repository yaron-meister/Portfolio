/*****************************************************************************
 * File name:   pp_udp.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-20 16:59:03
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/********************************* Macros *************************************/ 
#define PORT 9877 
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
  
    int n, len; 
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    { 
        perror("socket");
        return (EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.2"); 
    
    int i = 0;
    int counter = 0;

    while (1)
    {
        if (2 == counter)
        {
            message = "Quit";
        }
    	// send hello message to server 
    	sendto(sockfd, (const char*)message, strlen(message), 
           0, (const struct sockaddr*)&servaddr, sizeof(servaddr)); 

	    // receive server's response 
	    printf("Message from server: "); 
	    n = recvfrom(sockfd, (char*)buffer, MAXLINE, 0, 
                                             (struct sockaddr*)&servaddr, &len); 
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
