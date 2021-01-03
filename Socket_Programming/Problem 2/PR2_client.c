
#include<stdio.h> 			
#include<errno.h> 			
#include<stdlib.h> 	
#include<string.h>			
#include<sys/socket.h>		
#include<sys/types.h>		
#include<netinet/in.h>		
#include<unistd.h>			
#define PORT 8080 
#define MAX 100
#define INP "input.txt"
#define LineBytes 256



int main()
{
	int sock;										
	struct sockaddr_in address;						
	int check;										

	int addrlen;									
	int x;		
	int y;				
	struct sockaddr_in addr_client;
	socklen_t length_client; 						
	int client_sock;								
	
	char *buffer,*buffer2;							
	int opt;										
	socklen_t optlen;												


	printf("ENTER COMMAND :\n");
	buffer=(char *)malloc(LineBytes*sizeof(char));
	buffer2=(char *)malloc(LineBytes*sizeof(char));
	gets(buffer);

	// --------------------------- create socket
	sock=socket(AF_INET,SOCK_STREAM,0);						
	if(sock==-1)									
    {
        perror("socket creation failed...\n");
        exit(1);
    }
    printf("Socket successfully created..\n");

    opt=1;
	optlen=sizeof(opt);
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,optlen);


    memset((void *)&address,0,sizeof(address));


	// ---------------------------- IP and PORT assignment
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    address.sin_port = htons(PORT);
   

	// ----------------------------- client and socket connected
   	check=connect(sock, (struct sockaddr *)&address, sizeof(address));
    if(check< 0)
    {
        perror("connection with the server failed...");
        return -1;
    }
    printf("connected to the server..\n");
    
    write(sock,buffer,strlen(buffer));//-----------------read from server
    if(buffer[0]=='R')
    {
    	read(sock,buffer2,LineBytes);//----------------write to server
    	printf("\nRequired Line = \t\n");
    	puts(buffer2);
    }
    if(buffer[0]=='W')
    {
    	read(sock,buffer2,8);//----------------write to server
    	if(buffer2[0]=='S')
    	{
    		printf("“SUCCESS!!”\n");
    	}
    	else if(buffer[1]=='F')
    	{
    		printf("FAILED!!\n");
    	}
    }	
	close(client_sock);
	close(sock);

}