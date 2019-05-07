//Server
#include <iostream>
#include "Server.h"
#include <signal.h>

using namespace std;

Server *server;

//catches the interupt to detach queues and memory
void sighandler(int signal) {
	std::cout << "Caught signal: " << signal << std::endl;
	server->~Server();

	exit(1);
}

int main(int argc, char *argv[]) {
	std::cout << "Server child process of validator started." << std::endl;

	std::string arr[3];
	std::stringstream ss(argv[1]);
	
	int i = 0;
	while (ss.good() && i < 3) {
		ss >> arr[i];
		++i;
	}

	signal(SIGINT, &sighandler);

	char clientSocket = argv[1][0];
	int dbKeyStart = atoi(arr[1].c_str());
	int smKey = atoi(arr[2].c_str());

	std::cout << "Server client:" << clientSocket << " db:" << dbKeyStart << " shm:" << smKey << std::endl;

	//creates new server from client and database start keys
	server = new Server(clientSocket, dbKeyStart, smKey);

	cout << "Server created with client start key: socket_" << clientSocket << ", db start key: " << dbKeyStart << ", and shared memory key: " << smKey << endl;

	//handles single client instance
	server->handleClient();

    return 0;
}
