#pragma once

#include "SharedMemoryStatus.h"
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>

class SharedMemoryManager {
private:
	int key;
	int shMemId;
	void *sharedMemory;
	SharedMemoryStatus *sharedMessage;

public:
	SharedMemoryManager(int, bool);
	~SharedMemoryManager();

	void setIsInUse(bool);
	bool getIsInUse();

};
