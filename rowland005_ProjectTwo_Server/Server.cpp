#include "Server.h"

//creates a new server object with a client start key and database start key
Server::Server(char clientSocket, int dbStartKey, int smStartKey) {
	clientConn = new ClientConnection(clientSocket);
	smm = new SharedMemoryManager(smStartKey, false);

	dbm = new DatabaseManager(dbStartKey, dbStartKey + 1);
	loop = true;
}

//destructor for server to remove client and database connections
Server::~Server() {
	loop = false;

	std::cout << "Disposing of client connection." << std::endl;

	clientConn->~ClientConnection();

	std::cout << "Disposing of database manager." << std::endl;
	dbm->~DatabaseManager();
}

//client handler loop, runs through each client checking for messages and sends to database if necessary
void Server::handleClient() {
	do {
		std::string str;

		//check SHM if false, set to true then perform operation
		//if true, loop
		while (smm->getIsInUse()) { sleep(1); }

		smm->setIsInUse(true);

		bool val = dbm->performOperation(clientConn->getUserAccountRequest(), str);

		smm->setIsInUse(false);

		//set SHM to false

		if (val) {
			std::string tempStr = "Database operation successful: " + std::string(str.c_str());
			char tempC[255];

			strcpy(tempC, tempStr.c_str());
			clientConn->respondToClient(tempC);
		}
		else {
			std::string tempStr = "Database operation failed: " + std::string(str.c_str());
			char tempC[255];

			strcpy(tempC, tempStr.c_str());
			clientConn->respondToClient(tempC);
		}

		std::cout << "Sleep for 5 seconds." << std::endl;

		sleep(5);
	} while (loop);
}
