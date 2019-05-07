#include "SharedMemoryManager.h"

//Creates new instance of shared memory
SharedMemoryManager::SharedMemoryManager(int key, bool isClient) {
	this->key = key;

	sharedMemory = (void *)0;

	shMemId = shmget((key_t)key, sizeof(SharedMemoryStatus), 0666 | IPC_CREAT);

	if (shMemId == -1) {
		std::cout << "shmget failed" << std::endl;
	}

	sharedMemory = shmat(shMemId, (void *)0, 0);

	if (sharedMemory == (void *)-1) {
		std::cout << "shmat failed" << std::endl;
	}
	else {
		std::cout << "Memory attached at: " << (uint)sharedMemory << std::endl;
		std::cout << "  with shmid: " << shMemId << std::endl;
	}

	sharedMessage = (SharedMemoryStatus *)sharedMemory;

	if (!isClient) {
		sharedMessage->isInUse = false;//always gives client initial control
	}
}

//detaches from shared memory
SharedMemoryManager::~SharedMemoryManager() {
	if (shmdt(sharedMemory) == -1)
	{
		std::cerr << "shmdt failed" << std::endl;
	}

	if (shmctl(shMemId, IPC_RMID, 0) == -1)
	{
		std::cerr << "shmctl(IPC_RMID) failed" << std::endl;
	}
}

//sends the request to the server
void SharedMemoryManager::setIsInUse(bool value) {
	sharedMessage->isInUse = value;
}

//checks if the server has responded to the client
bool SharedMemoryManager::getIsInUse() {
	return sharedMessage->isInUse;
}
