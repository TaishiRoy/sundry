#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define PORT 8080 
#define MAX 100 


void ipc(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	bzero(buff, sizeof(buff)); 
	printf("Enter the string : "); 
	n = 0; 
	while ((buff[n++] = getchar()) != '\n') 
		; 
	write(sockfd, buff, sizeof(buff));  //----------------write to server
	bzero(buff, sizeof(buff)); 
	read(sockfd, buff, sizeof(buff));  //-----------------read from server
	printf("From Server : %s", buff); 
		
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 


	 // --------------------------- create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) 
	{ 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 


	// ---------------------------- IP and PORT assignment
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 



	// ----------------------------- client and socket connected
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// ----------------------------- function call for message exchange
	ipc(sockfd); 

	close(sockfd); 
} 
