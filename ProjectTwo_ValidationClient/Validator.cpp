#include "Validator.h"

Validator::Validator(char valSock, int shmKey) {
	smm = new SharedMemoryManager(shmKey, false);
	sm = new SocketManager(valSock, false);
}

Validator::~Validator() {
	smm->~SharedMemoryManager();
	sm->~SocketManager();
}

//char clientSocket, int dbStartKey, int smStartKey
void Validator::Validate(int dbStartKey, int smStartKey) {
	loop = true;
	//read connections
	while (loop) {
		std::cout << "Validator waiting for client." << std::endl;
		int clientFD = sm->acceptClient();

		std::cout << "Client validated, waiting for message." << std::endl;
		Message recM = sm->readResponse();
		Message sendM;

		std::cout << "Validating client." << std::endl;

		if (strcmp(recM.userId, "U1") && strcmp(recM.password, "U1")) {
			sendM.isClient = true;//customer
			std::stringstream response("Validated");

			response >> sendM.serverResponse;
		}
		else if (strcmp(recM.userId, "T1") && strcmp(recM.password, "T1")) {
			sendM.isClient = false;//teller
			std::stringstream response("Validated");

			response >> sendM.serverResponse;
		}
		else {
			std::stringstream response("Invalid");
			response >> sendM.serverResponse;

			sm->sendRequest(sendM);

			break;
		}

		std::cout << "Client validated, starting child server process." << std::endl;

		pid_t forkResult = fork();

		if (forkResult == -1) {
			std::cout << "Fork error, breaking." << std::endl;
			break;
		}

		//child process
		if (forkResult == 0) {
			std::stringstream db;
			std::stringstream sm;

			std::string test;
			std::string dbs;
			std::string sms;

			db << dbStartKey;
			sm << smStartKey;

			db >> dbs;
			sm >> sms;

			test += recM.serverResponse;
			test += " ";
			test += dbs;
			test += " ";
			test += sms;

			std::cout << "Started child server with parameters: " << test.c_str() << std::endl;

			execl("server.out", "server.out", test.c_str(), (char *)0);

			std::cout << "Server execution failed." << std::endl;
		}

		sm->sendRequest(sendM);
	}
}
