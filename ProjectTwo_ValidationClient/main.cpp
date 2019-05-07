#include <cstdio>
#include <iostream>
#include <signal.h>
#include "Validator.h"

using namespace std;

Validator *validator;

//catches the interupt
void sighandler(int signal) {
	std::cout << "Caught signal: " << signal << std::endl;
	validator->~Validator();

	exit(1);
}

int main(int argc, char *argv[]) {
	signal(SIGINT, &sighandler);

	char validatorSock = argv[1][0];
	int dbKeyStart = atoi(argv[2]);
	int smKey = atoi(argv[3]);

	//creates new validator
	validator = new Validator(validatorSock, smKey);

	cout << "Validator created with client start key: socket_" << validatorSock << ", db start key: " << dbKeyStart << ", and shared memory key: " << smKey << endl;

	validator->Validate(dbKeyStart, smKey);

	validator->~Validator();

    return 0;
}
