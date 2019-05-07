#pragma once

#include "UserInputManager.h"
#include "SocketManager.h"
#include "UserAccountRequest.h"
#include <unistd.h>
#include <string>
#include <iostream>

class Client {
private:
	UserInputManager uim;
	SocketManager *smDB;
	SocketManager *smValidate;
	bool isCustomer;
	char dbSock;

public:
	Client(char, char);
	~Client();
	void manageClient();
	bool login();

};
