#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "operation.h"

class MessageQueueWriter {
private:
	int key;
	int msgId;

public:
	MessageQueueWriter(int key);
	~MessageQueueWriter();
	bool writeOperation(struct operation);
};
