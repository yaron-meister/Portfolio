/*****************************************************************************
 * File name:   udp_client.cpp
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
#include <sstream>

/********************************* Macros *************************************/ 
#define PORT    8080 
#define MAXLINE 4*1024 
 
/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	int sockfd;
    size_t struct_size = sizeof(struct sockaddr_in); 
    struct sockaddr_in servaddr;
    struct sockaddr_in client; 
    char buffer[MAXLINE];
    char storage[MAXLINE]; 
    char* hello[3] = {"221;1114;124;1;\0", "1245;11;25;1;\0", "11;111;26;0;\0"};
    // size_t offset = 221;
    // size_t length = 1114;
    // unsigned int id = 124;
    // unsigned int type = 0;
    // std::stringstream stream;

    // stream << offset << ';' << length << ';' << id << ';' << 0 << ';' << '\0';
  
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    { 
        perror("socket creation failed"); 
        return (EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&client, 0, sizeof(client));
 
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    /* Bind the socket with the server address */
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        perror("bind failed"); 
        throw std::runtime_error("bind");
    }


    int n, len, i = 0; 
     
    while (i < 3)  
    {

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                    0, (struct sockaddr *) &client, reinterpret_cast<socklen_t *>(&struct_size)); 
        
        printf("udp_client: received %ld bytes\n", n);

        sleep(1);
        
    	ssize_t sentlen = sendto(sockfd, (const char *)(hello[i]), strlen(hello[i]), 
            MSG_CONFIRM, (const struct sockaddr *) &client, sizeof(client)); 

        printf("udp_client: send %ld bytes\n", sentlen);
        
        printf("%s\n", buffer);

        buffer[n] = '\0'; 
        
        ++i; 
    }
  
    close(sockfd); 
 
    return (EXIT_SUCCESS);
} 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
