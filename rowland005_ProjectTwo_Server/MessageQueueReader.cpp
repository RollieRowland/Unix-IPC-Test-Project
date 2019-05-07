#include "MessageQueueReader.h"

//creates a new message queue from a specified key
MessageQueueReader::MessageQueueReader(int key) {
	this->msgId = msgget((key_t)key, 0666 | IPC_CREAT);

	if (msgId == -1)
	{
		std::cerr << "msgget failed" << std::endl;
	}
	else {
		std::cout << "Message queue reader at key " << key << " created." << std::endl;
	}
}

//destructor for removing message queue from system
MessageQueueReader::~MessageQueueReader() {
	if (msgctl(msgId, IPC_RMID, 0) == -1)
	{
		std::cerr << "msgctl (IPC_RMID) failed" << std::endl;
	}
}

//reads from the message queue 
struct operation MessageQueueReader::readOperation() {
	if (msgrcv(msgId, (void *)&op, sizeof(struct operation) - 4, 1, 0) == -1)
	{
		std::cerr << "msgrcv failed" << std::endl;
	}

	struct operation tempOp = op;

	return tempOp;
}
