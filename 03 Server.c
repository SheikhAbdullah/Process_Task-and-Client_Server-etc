#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
// Make a given string NULL
void makeNULL(char ch[],int size){
	for (int i=0;i<size;i++){
		ch[i]='\0';
	}
}
int main() { 
//	Creating socket file descriptor
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
//	Set Address at Socket
	struct sockaddr_in socket_address; 
	socket_address.sin_family = AF_INET; 
    	socket_address.sin_addr.s_addr = INADDR_ANY; 
    	socket_address.sin_port = htons( PORT );
//	Get name and Show on other end communicator
	char p_name[50];
	char s_name[50];
	makeNULL(p_name,50);
	makeNULL(s_name,50);
	printf("Enter Your Name  : ");
	fgets(p_name,50,stdin);
//	Get size of socket address in addrlen
	int addrlen = sizeof(socket_address);
//	Bind Server for forcelly of socket Address
	bind(server_socket, (struct sockaddr *)&socket_address,addrlen);
//	Looking for Requests from requested communicator
	listen(server_socket,3);
//	If listen then make a new socket for other communicator
	int new_socket = accept(server_socket, (struct sockaddr *)&socket_address, (socklen_t*)&addrlen);
//	Receive name of other communicator
	recv( new_socket , s_name, 50,0);
//	Send name to other communicator
	send(new_socket , p_name , strlen(p_name) , 0 );
//	Make a new Process, ready for receive Messages
	int cpid=fork();	
	if (cpid==0){			// Child Process
		char buffer[1024];
		int j=1;
		while (j==1){
			makeNULL(buffer,1024);
			recv( new_socket , buffer, 1024,0); 	// receive string from other communicator
    			printf("%s %s",s_name,buffer );
		}
	}
//	Take Input and send to other communicator
	char msg[50];
	int i=1;
	while (i==1){
		makeNULL(msg,50);
		fgets(msg,50,stdin);
		send(new_socket , msg , strlen(msg) , 0 );
	} 
    	return 0; 
}
