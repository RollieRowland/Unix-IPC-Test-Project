#pragma once

#include "MessageQueueReader.h"
#include "MessageQueueWriter.h"
#include "UserAccountRequest.h"
#include "operation.h"
#include <stdio.h>
#include <sstream>

class DatabaseManager {
private:
	MessageQueueWriter *mqw;
	MessageQueueReader *mqr;

	struct operation createOperation(UserAccountRequest);

public:
	DatabaseManager(int, int);
	~DatabaseManager();
	bool performOperation(UserAccountRequest, std::string&);
	void shutdown();

};
