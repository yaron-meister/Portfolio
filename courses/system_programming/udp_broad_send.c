/*****************************************************************************
 * File name:   udp_broad_send.c
 * Developer:   Yaron Meister
 * Date:        2019-03-20 14:11:55
 * Description: UDP broadcasting Sender
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
    char *hello = "\n\nHaCarmel lovesh YAROK\n\n"; 
    struct sockaddr_in servaddr;
    int broadcast = 1; 
      
    /* Creating socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    { 
        perror("socket creation failed"); 
        return (EXIT_FAILURE); 
    } 
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
                                                               sizeof(int)) < 0)
    {
        perror("Setting local interface error\n");
        return (EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr)); 
      
    /* Filling server information */
    servaddr.sin_family      = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 

    if (1 != inet_pton(AF_INET, "10.3.0.255", &servaddr.sin_addr)) 
    {
        perror ("inet_pton");
        return (EXIT_FAILURE);
    }

    int send_ret;

    while (1)
    {
        send_ret = sendto(sockfd, (const char *)hello, strlen(hello),  
            MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
        if (-1 == send_ret)
        {
            perror("sendto");
        }

        sleep(2);
    }
 
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
