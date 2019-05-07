#pragma once

#include "SocketManager.h"
#include "UserAccountRequest.h"

class ClientConnection {
private:
	SocketManager *sm;

public:
	ClientConnection(char key);
	~ClientConnection();
	void respondToClient(char str[255]);
	UserAccountRequest getUserAccountRequest();

};
