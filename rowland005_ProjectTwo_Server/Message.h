#pragma once

#include "UserAccountRequest.h"

typedef struct Message {
	bool isClient;
	char userId[2];
	char password[2];
	UserAccountRequest uar;
	char serverResponse[255];
} Message;
