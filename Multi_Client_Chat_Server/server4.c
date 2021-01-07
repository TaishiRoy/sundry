#include <stdio.h> 
#include<stdbool.h>
#include<math.h>
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include <string.h> //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> //close 
#include <arpa/inet.h> //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <signal.h> 
#include <ctype.h>
#include <errno.h>
#include<sys/sem.h>
#include<sys/stat.h>
#include<fcntl.h>	
#define MAX 255 
#define PORT 5001
#define OFFSET 43562
#define MAXLINE 1024 
  
 
int main()
{
	int opt = 1, currGroups = 0; 
    int group[5][10];	
	int socket_fd, connection_fd, length,count,n,read_check,temp;
	char line[256];
    char message_table[60][100];
	int i = 0;
	char c; 
    int client_list[5];
    int loop = 0;
    for(loop = 0; loop < 5; loop++)
    {
        client_list[loop] = 0;
    }
	char buff[MAX];
	char *buffer2;
	buffer2=(char *)malloc((MAX+1)*sizeof(char));
	memset(buffer2,0,MAX);
	struct sockaddr_in server_addr, client; 
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);  // for creating socket and  verification of socket 
	if (socket_fd == -1) 
	{ 
		printf("socket creation failed\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created\n"); 
	bzero(&server_addr, sizeof(server_addr)); 
	server_addr.sin_family = AF_INET;  ///assign ipv4 family
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //assign ip address
	server_addr.sin_port = htons(PORT); ///assign port
	if ((bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) != 0) //// to Bind  created socket to given IP 
	{ 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n");  
	
	if ((listen(socket_fd, 5)) != 0) // lsiten and verification of server 
	{ 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n");
	int client_count=0;
	for(;;)
    {
	    length = sizeof(client); 	
	    connection_fd = accept(socket_fd, (struct sockaddr*)&client, &length); // to accept data from client 
	    client_count++;
	    if (connection_fd < 0) 
        { 
	    	printf("server acccept failed...\n"); 
	    	exit(0); 
	    } 
	    else
        {
	    	printf("server acccept the client socket no %d...\n",client_count); 
            bzero(buff, MAX);
            for(loop = 0; loop < 5; loop++)
            {
                if(client_list[loop] == 0)
                {
                    client_list[loop] = connection_fd;
                    break;
                }
            }
            sprintf(buff, "WELCOME Your Unique ID is %d and at socket %d", OFFSET + loop, connection_fd);
            send(connection_fd,buff,sizeof(buff),0);
        }
    
	    if(fork()==0)
        {
	        close(socket_fd);
            for(;;)
            { 	
	            bzero(buff, MAX);
	            read_check = recv(connection_fd, buff, sizeof(buff), 0); 
	            strcpy(buffer2,buff);
	            printf("\nClient socket %d sent message: = %s",client_count,buff);
                if(strncmp(buff,"/quit",5)==0)
	            {
	            	printf("client pressed exit\n");
                    for(loop = 0; loop < 5; loop++)
                    {
                        if(client_list[loop] == connection_fd)
                        {
                            client_list[loop] = 0;
                            break;
                        }
                    }
                    sprintf(buff, "exit");
                    send(connection_fd,buff,sizeof(buff),0);
	            	close(connection_fd);	
                    close(socket_fd);
	            	break;
	            }

                // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                  TO GET ACTIVE GROUPS                   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                    else if(strncmp(buff,"/activegroups",13) == 0)
                    {
					    char output[1024];
					    int l = 0;
                        loop = 0;
                        for(loop = 0; loop < 10; loop++)
                        {
                            if(group[0][loop] != 0)
                            {
                                int trac = 0;
                                for(trac = 0; trac < 5; trac++)
                                {
                                    if(client_list[group[trac][loop] - OFFSET] == connection_fd )
                                    {
                                        l += snprintf(output + l,1024,"Your group with unique_key %d is currently active.\n",OFFSET + loop + 6 );
                                        break;
                                    }
                                }
                                
                            }
                        }
						write(connection_fd,output,1024);
					}

                // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                  TO GET ACTIVE CLIENTS                   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
				else if(strncmp(buff,"/active",7) == 0)
                {
				    char output[1024];
				    int l = 0;
                    loop = 0;
                    for(loop = 0; loop < 5; loop++)
                    {
                        if(client_list[loop] != 0)
                        {
                            l += snprintf(output + l,1024,"Client with unique_key %d and socket %d is currently active.\n",OFFSET + loop ,client_list[loop]);
                        }
                    }
					send(connection_fd,output,1024,0);
				}

                // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                  TO SEND MESSAGE IN A GROUP                   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                    else  if(strncmp(buff,"/sendgroup",10) == 0 )
                    {
                        char *ptr = strtok(buff," ");
						ptr = strtok(NULL, " ");
						int ar =atoi(ptr),j=0;
                        int thisGroup = 0;
                        loop = 0;
                        thisGroup = ar - OFFSET - 6; // ----------- group position
						
						ptr = strtok(NULL, " ");

                        
						while(1)
                        {
                            if(group[loop][thisGroup] == 0)
                            {
                                break;
                            }
                            char msg2[100];
                            sprintf(msg2, "-- New Message from group %d :", OFFSET + thisGroup + 6);
                            send(client_list[group[loop++][thisGroup] - OFFSET],msg2,1024,0);
                            send(client_list[group[loop-1][thisGroup] - OFFSET],ptr,1024,0);
                        }		
					}
			



                    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                  TO SEND MESSAGE TO  CLIENT                   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
					else  if(strncmp(buff,"/send",5) == 0 )
                    {
                        char *ptr = strtok(buff," ");
						ptr = strtok(NULL, " ");
						int ar =atoi(ptr),j=0;
                        int new = 0;
                        loop = 0;
                        for(loop = 0; loop < 5; loop++)
                        {
                            if(ar == OFFSET+loop)
                            {
                                new = loop;
                                break;
                            }
                        }
						j=0;	
						ptr = strtok(NULL, " ");
						send(client_list[new],ptr,1024,0);	
                        char msg2[100];
                        sprintf(msg2, "-- Message sent successfully ");
                        send(connection_fd,msg2,1024,0);	
					}



                // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                  TO CREATE NEW GROUP                   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                    else  if(strncmp(buff,"/makegroup",10) == 0 )
                    {
                        
                        loop = 0;
                        char buffer2[1025]; 
                        while(1)
                        {
                            if(buff[loop] == '\n')
                            {
                                break;
                            }
                            buffer2[loop++] = buff[loop];
                        }

                        char msg[100];
                        sprintf(msg, "-- Added to group with ID %d", OFFSET + currGroups + 6);

                        for(loop = 0; loop < 5; loop++)
                        {
                            if(client_list[loop] == connection_fd)
                            {
                                group[0][currGroups] = OFFSET + loop;
                                send(client_list[group[0][currGroups] - OFFSET],msg,1024,0);
                                break;
                            }
                        }

                        loop = 1;
                        char *ptr = strtok(buffer2," ");
						ptr = strtok(NULL, " ");
                        while(1)
                        {
                            // group[loop++][currGroups] = atoi(ptr);
                            if( ptr == NULL)
                            {
                                break;
                            }
                            group[loop++][currGroups] = atoi(ptr);
                            
                            send(client_list[group[loop-1][currGroups] - OFFSET],msg,1024,0);	
                            ptr = strtok(NULL," ");
                        }
						

                        ++currGroups; // Unique ID of group would be OFFSET +  currGroups + 6
        
                    }

                else if(strncmp(buff,"/broadcast",10) == 0)
                    {
						char output[1024];
						int l = 0;
						char *bb;
					    bb=(char*)malloc(1024*sizeof(char));
                        bzero(buff, MAX);
                        sprintf(buff, "broad");
                        send(connection_fd, buff, sizeof(buff), 0);		
						sscanf(buff,"/broadcast %10[0-9a-zA-Z ] ",bb);
				    		int k=0;									
						for(k=0;k<5;k++)
						{       
							if(client_list[k]!=0 && client_list[k]!=connection_fd)
								send(client_list[k],bb,sizeof(bb), 0);
						}
						char dat[1024];	
						snprintf(dat,1024,"Broadcast completed !!");
						send(connection_fd,dat,sizeof(dat), 0);
					}

	            send(connection_fd,buff,sizeof(buff),0);

	        }
	    }
	    //close(socket_fd);

    }
}
