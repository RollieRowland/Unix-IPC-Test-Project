#include "ClientConnection.h"

//creates an instance of the client manager
ClientConnection::ClientConnection(char key) {
	this->sm = new SocketManager(key, false);
}

//calls shared memory destructor 
ClientConnection::~ClientConnection() {
	this->sm->~SocketManager();
}

//returns current shared memory user account request
UserAccountRequest ClientConnection::getUserAccountRequest() {
	return sm->readResponse().uar;
}

//responds to the client with a string message
void ClientConnection::respondToClient(char str[255]) {
	Message mes = Message();

	strcpy(mes.serverResponse, str);

	std::cout << mes.serverResponse << std::endl;

	this->sm->sendRequest(mes);
}
