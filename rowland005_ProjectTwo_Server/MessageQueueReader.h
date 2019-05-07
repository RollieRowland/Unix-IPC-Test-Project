#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "operation.h"

class MessageQueueReader {
private:
	int key;
	int msgId;
	struct operation op;

public:
	MessageQueueReader(int key);
	~MessageQueueReader();
	struct operation readOperation();
};
