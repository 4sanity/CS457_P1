//Sam Bruns
//Project 1
//Date: 9/3/2014
//chat.cpp 

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAXPENDING 5

using namespace std;

struct In_addr {
    unsigned long s_addr;
};

struct socketAddress{
	unsigned short family;
	unsigned short port;
	struct In_addr addr;
	char zero[8];
};

int main(int argc, char *argv[]){
	string welcome = "Welcome to Chat!";
	
	int serverSocket;
	struct socketAddress serverAddress;
	struct socketAddress clientAddress;
	int newSocket;
	
	if(argc==1){
		//server side
		if((serverSocket=socket(PF_INET,SOCK_STREAM,0))<0){
			cout << "Error: Server socket could not be created." << endl;
			exit(1);
		}
		
		serverAddress.family=AF_INET;
		serverAddress.addr.s_addr=htonl(INADDR_ANY);
		serverAddress.port=htons(3400);
		cout << serverAddress.addr.s_addr << "   " << serverAddress.port << endl;
		if(bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
			cout << "Error: Server failed to bind." << endl;
			exit(1);
		}
		
		if(listen(serverSocket, MAXPENDING)<0){
			cout << "Error: Server failed to start listen." << endl;
			exit(1);
		}
		
		//not sure why socklen_t works
		socklen_t clientLength = sizeof(clientAddress);
		if((newSocket=accept(serverSocket,(struct sockaddr*)&clientAddress,&clientLength))<0){
			cout << "Error: Server failed to accept connection." << endl;
			exit(1);
		}
		
		cout << welcome << "Waiting for a connection on " << serverAddress.addr.s_addr
			<< " port " << serverAddress.port << endl;
		
		
	}else if(argc==2){
		string arg2 = argv[1];
		if(arg2=="-h"){
			//help message
			cout << "got to help" << endl;
		}else{
			cout << "Error: Argument invalid. Use ./chat -h for help message." << endl;
		}
		
		
	}else if(argc==5){
		//client side
		
		
	}else{
		cout << "Error: Number of arguments incorrect. Use ./chat -h for help message." << endl;
	}

return 0;
}