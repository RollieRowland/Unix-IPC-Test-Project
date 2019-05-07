#pragma once

#include "SharedMemoryManager.h"
#include "SocketManager.h"
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <sstream>
#include <string>

class Validator {
public:
	Validator(char, int);
	~Validator();

	void Validate(int dbStartKey, int smStartKey);

private:
	SharedMemoryManager * smm;
	SocketManager *sm;
	bool loop;

};
