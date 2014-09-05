//Sam Bruns
//Project 1
//Date: 9/3/2014
//chat.cpp 

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXPENDING 5

using namespace std;

int main(int argc, char *argv[]){
	
	int serverSocket;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	int newSocket;
	
	if(argc==1){
		//server side
		if((serverSocket=socket(PF_INET,SOCK_STREAM,0))<0){
			cout << "Error: Server socket could not be created." << endl;
			exit(1);
		}
		
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); //LOOPBACK binds to localhost
		serverAddress.sin_port = htons(5894);
		
		if(bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
			cout << "Error: Server failed to bind." << endl;
			exit(1);
		}
		
		if(listen(serverSocket, MAXPENDING)<0){
			cout << "Error: Server failed to start listen." << endl;
			exit(1);
		}
		
		// printf("%d\n",ntohl(serverAddress.sin_addr.s_addr));
		// char *some_addr;
		// some_addr = inet_ntoa(serverAddress.sin_addr);
		// printf("%s\n", some_addr);
		// printf("Port Number: %d\n", ntohs(serverAddress.sin_port));
		
		//not sure why socklen_t works
		socklen_t clientLength = sizeof(clientAddress);
		if((newSocket=accept(serverSocket,(struct sockaddr*)&clientAddress,&clientLength))<0){
			cout << "Error: Server failed to accept connection." << endl;
			exit(1);
		}
		
		
		
	}else if(argc==2){
		string arg1 = argv[1];
		if(arg1=="-h"){
			//help message
			cout << "got to help" << endl;
		}else{
			cout << "Error: Argument invalid. Use ./chat -h for help message." << endl;
		}
		
		
	}else if(argc==5){
		//client side
		string arg1 = argv[1];
		string arg2 = argv[2];
		string arg3 = argv[3];
		string arg4 = argv[4];
		int PORT;
		string SADDRESS;
		
		//make sure both arguments are not the same
		if( (arg1=="-p"&&arg3=="-p") || (arg1=="-s"&&arg3=="-s") ){
			cout << "Error: Arguments incorrect. Use ./chat -h for help message." << endl;
			exit(1);
		}
		if(arg1!="-p" && arg1!="-s" ){
			cout << "Error: Arguments incorrect. Use ./chat -h for help message." << endl;
			exit(1);
		}
		if(arg3!="-s" && arg3!="-p" ){
			cout << "Error: Arguments incorrect. Use ./chat -h for help message." << endl;
			exit(1);
		}
		if(arg1=="-p" && !atoi(argv[2])){
			cout << "Error: Could not convert port argument to number." << endl;
			exit(1);
		}		
		if(arg3=="-p" && !atoi(argv[4])){
			cout << "Error: Could not convert port argument to number." << endl;
			exit(1);
		}
		if(arg1=="-s"){
			for(unsigned i=0; i<arg2.length(); i++){
				if( !isdigit(arg2[i]) && arg2[i]!='.' ){
					cout << "Error: Server address is not in the correct format." << endl;
					exit(1);
				}
			}
			//if the server address comes first this is where i initialize
			SADDRESS = arg2;
			PORT = atoi(argv[4]);
		}
		if(arg3=="-s"){
			for(unsigned i=0; i<arg4.length(); i++){
				if( !isdigit(arg4[i]) && arg4[i]!='.'){
					cout << "Error: Server address is not in the correct format." << endl;
					exit(1);
				}
			}
			//if the server address comes second this is where i initialize
			SADDRESS = arg4;
			PORT = atoi(argv[2]);
		}
		
		//sanitization done
		int clientSocket;
		struct sockaddr_in serverAddress;

		if((clientSocket=socket(PF_INET,SOCK_STREAM,0))<0){
			cout << "Error: Client socket could not be created." << endl;
			exit(1);
		}
		
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = htonl(inet_network(SADDRESS.c_str()));  //inet_addr(SADDRESS)
		serverAddress.sin_port = htons(PORT);

   		if((connect(clientSocket,(struct sockaddr *)&serverAddress,sizeof(sockaddr_in))< 0)){
			cout << "Error: Failed to connect with server." << endl;
			exit(1);
		}
		cout << "Connecting to server... Connected!" << endl;
		cout << "Connected to a friend! You send first." << endl;
		cout << "You: ";
		
		string message;
		cin >> message;
		if(message.length()>140){
			cout << "Error: Input too long." << endl;
			//ask for input?
		}
		
	}else{
		cout << "Error: Number of arguments incorrect. Use ./chat -h for help message." << endl;
	}

return 0;
}
















