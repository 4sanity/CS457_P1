//Sam Bruns
//Project 1
//Date: 9/3/2014
//chat.cpp

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	string welcome = "Welcome to Chat!";
	
	if(argc==1){
		//server side
		
		
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