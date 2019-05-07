#pragma once

#include "DatabaseManager.h"
#include "ClientConnection.h"
#include "SharedMemoryManager.h"

class Server {
private:
	ClientConnection* clientConn;
	DatabaseManager *dbm;
	SharedMemoryManager *smm;

	bool loop;

public:
	Server(char clientSocket, int dbStartKey, int smKey);
	~Server();
	void handleClient();

};
