//Client
#include <iostream>
#include "Client.h"
#include <signal.h>

using namespace std;

Client *client;

//catches the interupt
void sighandler(int signal) {
	std::cout << "Caught signal: " << signal << std::endl;
	client->~Client();

	exit(1);
}

int main(int argc, char *argv[]){
	signal(SIGINT, &sighandler);

	char sockDB = argv[1][0];
	char sockVal = argv[2][0];

	std::cout << "DB:" << sockDB << " Val:" << sockVal << std::endl;

	//creates a new client from the specified key
	client = new Client(sockDB, sockVal);

	cout << "Client created with sock db key: socket_" << sockDB << " sock validation key: socket_" << sockVal << endl;

	if (client->login()) {
		//runs a loop for the client 
		client->manageClient();
	}
	else {
		cout << "Client not validated, username or password incorrect." << endl;
	}
	
    return 0;
}
