#include "Client.h"

Client::Client(char dbSock, char vaSock) {
	this->dbSock = dbSock;

	smValidate = new SocketManager(vaSock, true);
	uim = UserInputManager();
}

Client::~Client() {
	smValidate->~SocketManager();
	smDB->~SocketManager();
}

void Client::manageClient() {
	while (uim.running()) {
		//Read controls from user
		UserAccountRequest uar = uim.readControl(isCustomer);

		//closes program without error
		if (!uim.running()) {
			break;
		}
		else {
			//creates new message to send request to server
			Message mes = Message();

			mes.uar = uar;

			//sends request to server
			smDB->sendRequest(mes);

			//waits for response from server
			Message recMes = smDB->readResponse();

			std::cout << "Server response: " << recMes.serverResponse << std::endl;

			sleep(1);
		}
	}
}

bool Client::login() {
	//read in 2 char username
	//read in 2 char password
	std::string username;
	std::string password;
	std::string dbId = std::string(1, dbSock);

	std::cout << "Enter username: " << std::endl;
	std::getline(std::cin, username);

	std::cout << "Enter password: " << std::endl;
	std::getline(std::cin, password);

	Message mes;

	std::cout << "Attaching information to message" << std::endl;

	strcpy(mes.userId, username.c_str());
	strcpy(mes.password, password.c_str());
	strcpy(mes.serverResponse, dbId.c_str());

	std::cout << "Information attached to message, validating client." << std::endl;

	smValidate->sendRequest(mes);

	std::cout << "Validation request sent." << std::endl;

	Message smV = smValidate->readResponse();

	if (strcmp(smV.serverResponse, "Validated") == 0) {
		std::cout << "Server validated client successfully." << std::endl;
		isCustomer = smV.isClient;

		sleep(5);

		std::cout << "Connecting to validation servers forked server." << std::endl;
		smDB = new SocketManager(dbSock, true);

		std::cout << "Server connection successful." << std::endl;
		return true;
	}
	else {
		std::cout << "Server denied validation request with response: " << smV.serverResponse << std::endl;
		return false;
	}
}
