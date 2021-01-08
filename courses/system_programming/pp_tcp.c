/*****************************************************************************
 * File name:   pp_tcp.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-20 16:59:00
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <netinet/in.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/********************************* Macros *************************************/ 
#define PORT 9877 
#define MAXLINE 1024 
 
/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void) 
{ 
    int sockfd; 
    char buffer[MAXLINE] = {0}; 
    char* message = "Ping\n\n"; 
    struct sockaddr_in servaddr; 
  
    int n, len; 

    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        perror("socket"); 
        return (EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.2"); 
  
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) 
    { 
        perror("connect");
        return (EXIT_FAILURE); 
    } 
  
    int counter = 0;

    while (1)
	{
        if (2 == counter)
        {
            message = "Quit";
        }
	    if (-1 == sendto(sockfd, (const char*)message, strlen(message), 
           0, (const struct sockaddr*)&servaddr, sizeof(servaddr)))
        {
        	perror("sendto");
        	return (EXIT_FAILURE);
        } 
	    
	    printf("Message from server: "); 
	    
	    if (recvfrom(sockfd, (char*)buffer, sizeof(buffer), 0, 
                                         (struct sockaddr*)&servaddr, &len) > 0)
	    {
	    	puts(buffer); 
	    }
   
    	sleep(1);
        ++counter;
    } 

    close(sockfd);

    return (EXIT_SUCCESS); 
} 

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
