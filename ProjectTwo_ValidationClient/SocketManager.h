#pragma once

#include "Message.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sstream>

class SocketManager {
private:
	std::string strkey;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;

public:
	SocketManager(char, bool);
	~SocketManager();

	void sendRequest(Message);
	Message readResponse();
	int acceptClient();

};
