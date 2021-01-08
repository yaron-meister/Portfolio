/*****************************************************************************
 * File name:   pp_server.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-03-20 16:56:33
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /*    printf    */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <string.h>

#include "utils.h" 

/********************************* Macros *************************************/ 
#define PORT 9877 
#define MAXLINE 1024 
 
/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{ 
    int listenfd, connfd, udpfd, nready, maxfdp; 
    char buffer[MAXLINE]; 
    pid_t childpid; 
    fd_set rset; 
    ssize_t n; 
    socklen_t len; 
    const int on = 1; 
    struct sockaddr_in cliaddr, servaddr;
    char* message = "Pong\n"; 
    void sig_chld(int); 
 	int broadcast = 1;

    // create listening TCP socket 
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd)
    {
    	perror("TCP socket");
    	return (EXIT_FAILURE);
    } 

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // binding server addr structure to listenfd 
    if (-1 == bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
    {
    	perror("TCP bind");
    	return (EXIT_FAILURE);
    }

    if(-1 == listen(listenfd, 10))
    {
    	perror("listen");
    	return (EXIT_FAILURE);
    } 
  
    // create UDP socket 
    udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
    if (-1 == udpfd)
    {
    	perror("UDP socket");
    	return (EXIT_FAILURE);
    }

    if (setsockopt(udpfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
                                                               sizeof(int)) < 0)
    {
        perror("Setting local interface error\n");
        return (EXIT_FAILURE);
    }

    // binding server addr structure to udp sockfd 
    if (-1 == bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
    {
    	perror("UDP bind");
    	return (EXIT_FAILURE);
    } 

    // clear the descriptor set 
    FD_ZERO(&rset); 

    maxfdp = MAX(listenfd, udpfd) + 1; 
    while (1) 
    { 
        // set listenfd and udpfd in readset 
        FD_SET(listenfd, &rset); 
        FD_SET(udpfd, &rset);
  
        // select the ready descriptor 
        nready = select(maxfdp, &rset, NULL, NULL, NULL); 
  		if (-1 == nready)
  		{
  			perror("select");
  			return (EXIT_FAILURE);
  		}

        // if tcp socket is readable then handle 
        // it by accepting the connection 
        if (FD_ISSET(listenfd, &rset)) 
        { 
            len = sizeof(cliaddr); 
            connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len); 
            
            childpid = fork();
            if (0 == childpid) 
            { 
                close(listenfd);

                while (1)
                {	
	                bzero(buffer, sizeof(buffer)); 
	                if (read(connfd, buffer, sizeof(buffer)) < 0)
	                {
	                	perror("read");
	                	return (EXIT_FAILURE);
	                }
	                
	                if (0 == strcmp("Quit", buffer))
                	{
                        kill(getppid(), SIGKILL);
                		close(connfd);
                        return (EXIT_SUCCESS);
	                }  

                    if (0 == strcmp("Ping\n\n", buffer))
                    {
                        printf("Message From TCP client: "); 
    	                puts(buffer); 
    	                write(connfd, (const char*)message, strlen(message)); 
                    }
                }
            } 
           
            close(connfd); 
        } 

        // if udp socket is readable receive the message. 
        if (FD_ISSET(udpfd, &rset)) 
        { 
	            len = sizeof(cliaddr); 
	            bzero(buffer, sizeof(buffer)); 
	            n = recvfrom(udpfd, buffer, sizeof(buffer), 0, 
	                         (struct sockaddr*)&cliaddr, &len);
                if (0 == strcmp("Quit", buffer))
                {
                    close(udpfd);
                    kill(getpid(), SIGKILL);
                } 

                if (0 == strcmp("Ping\n\n", buffer))
                {
    	            printf("Message from UDP client: "); 
    	            puts(buffer); 
    	            sendto(udpfd, (const char*)message, strlen(message), 0, 
    	                   (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
                }
        } 
    } 

    return (EXIT_SUCCESS);
} 


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 


