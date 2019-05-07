#include "MessageQueueWriter.h"

//creates a new message queue writer
MessageQueueWriter::MessageQueueWriter(int key) {
	this->msgId = msgget((key_t)key, 0666 | IPC_CREAT);

	if (msgId == -1) {
		std::cerr << "msgget failed" << std::endl;
	}
	else {
		std::cout << "Message queue writer at key " << key << " created." << std::endl;
	}
}

//destructor for removing message queue from system
MessageQueueWriter::~MessageQueueWriter() {
	if (msgctl(msgId, IPC_RMID, 0) == -1) {
		std::cerr << "msgctl (IPC_RMID) failed" << std::endl;
	}
}

//writes operation to message queue/database
bool MessageQueueWriter::writeOperation(struct operation op) {
	std::cout << "MQR OP: " << op.opcode << " " << op.account_number << " " << op.first_name << " " << op.last_name << " " << op.amount << std::endl;

	if (msgsnd(msgId, (void *)&op, sizeof(op) - 4, 0) == -1) {
		std::cerr << "msgsnd failed" << std::endl;

		return false;
	}
	else {
		return true;
	}
}
