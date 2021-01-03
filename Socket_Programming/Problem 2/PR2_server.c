			
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include<errno.h> 
#define PORT 8080 
#define MAX 100 
#define LINEBYTES 256
#define INP "input.txt"

char *read_file_kth(int k)
{
	FILE *fp;										
	size_t line_size;								
	char *line;										
	int i, sock;							

	fp=fopen(INP,"r");
	line_size=(size_t)LINEBYTES;

	if(fp==NULL)
	{
		perror("FOPEN ERROR");
		exit(1);
	}

	line=(char *)malloc(LINEBYTES * sizeof(char));	
	if(line==NULL)
	{
		perror("MALLOC ERROR");
		exit(1);
	}
	
	for(i=1;i<=k;i++)
	{
		int ret=getline(&line,&line_size,fp); 		
		if(ret==-1)
		{
			perror("GETLINE ERROR");
			exit(1);
		}
	}
	return line;									
}



int append_file_msg(char *msg)
{
	FILE *fp;										

	
	fp=fopen(INP,"a");


	if(fp==NULL)
	{
		perror("FOPEN ERROR");
		exit(1);
	}

	fprintf(fp,"\n%s",msg);							
	fflush(NULL);

	return 1;										

}


int main()
{
	int sock;										
	struct sockaddr_in address;						
	int addrlen;								
	int x;	
	int y;			
	struct sockaddr_in addr_client;
	socklen_t length_client; 						
	int client_sock;								
	int check;							
	char *buffer,*buffer2;
	int opt;				
	socklen_t optlen;							


	// ---------------------------- create socket
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


	// --------------------------- IP and PORT assignment
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);	
    address.sin_port = htons(PORT);
    addrlen = sizeof(address);


	// -------------------------- socket bind
    x=bind(sock,(struct sockaddr *)&address,sizeof(address));
	if(x==-1)
    {
        perror("socket bind failed...\n");
        exit(1);
    }
    printf("Socket successfully binded..\n");



	// ------------------------- Listen to client 
    y=listen(sock,5);								
    if(y==-1)
    {
	   perror("Listen failed...\n");
	   exit(1);
    }
    printf("Server listening..\n");
	


	length_client = sizeof(addr_client);

	// ------------------------- Accept
	client_sock = accept(sock, (struct sockaddr *) &addr_client,&length_client);
	printf("server acccept the client...\n");
	
	buffer=(char *)malloc((LINEBYTES+1)*sizeof(char));
	buffer2=(char *)malloc((LINEBYTES+1)*sizeof(char));
	memset(buffer,0,LINEBYTES);
	memset(buffer2,0,LINEBYTES);
	check = read(client_sock,buffer,LINEBYTES);//-----------------read from client
	if(check==-1)
	{
		perror("error while reading");
		exit(1);
	}
	printf("\nNew Command = %s\n",buffer);
	if(buffer[0]=='R')
	{
		//for READX k command
		int k;
		sscanf(buffer,"READX %d",&k);
		buffer2=read_file_kth(k);
		check = write(client_sock,buffer2,LINEBYTES);//----------------write to client
		if(check==-1)
		{
			perror("error while reading");
			exit(1);
		}
	}
	if(buffer[0]=='W')
	{
		//for WRITEX msg command
		sscanf(buffer,"WRITEX %s",buffer2);
		x=append_file_msg(buffer2);
		if(x==1)
		{
			buffer2="SUCCESS";
			write(client_sock,buffer2,8);//----------------write to client
		}
		else
		{
			buffer2="FAILURE";
			write(client_sock,buffer2,8);//----------------write to client
		}
		
	}
	close(client_sock);
	close(sock);

}

