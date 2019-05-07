#include "SocketManager.h"

//creates new socket manager
SocketManager::SocketManager(char key, bool isClient) {
	std::stringstream ss;
	ss << "socket_";
	ss << key;

	ss >> strkey;

	if (isClient) {
		std::cout << "Creating client socket" << std::endl;

		server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

		server_address.sun_family = AF_UNIX;
		strcpy(server_address.sun_path, strkey.c_str());
		server_len = sizeof(server_address);

		int result = connect(server_sockfd, (struct sockaddr *)&server_address, server_len);

		if (result == -1)
		{
			std::cout << "Problem with client socket connection" << std::endl;
		}
	}
	else {
		std::cout << "Creating server socket" << std::endl;

		unlink(strkey.c_str());

		server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

		server_address.sun_family = AF_UNIX;
		strcpy(server_address.sun_path, strkey.c_str());
		server_len = sizeof(server_address);

		bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

		listen(server_sockfd, 5);

		std::cout << "Server Waiting " << std::endl;
	}
}

//unlinks and closes sockets
SocketManager::~SocketManager() {
	close(client_sockfd);
	close(server_sockfd);

	unlink(strkey.c_str());

	std::cout << "Socket(s) removed." << std::endl;
}

//sends message
void SocketManager::sendRequest(Message mes) {
	std::cout << "   SM sending message request." << std::endl;

	write(client_sockfd, &mes, sizeof(Message));

	std::cout << "   SM message request sent." << std::endl;
}

//waits for a message and then reads
Message SocketManager::readResponse() {
	std::cout << "   SM receiving message request." << std::endl;

	Message tempMessage;
	read(client_sockfd, &tempMessage, sizeof(Message));

	std::cout << "   SM message received." << std::endl;

	return tempMessage;
}

int SocketManager::acceptClient() {
	client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

	return client_sockfd;
}
