#pragma once

#include "AccountRequest.h"

typedef struct UserAccountRequest {
	AccountRequest ar;
	char accountNumber[6];
	char lastName[50];
	char firstName[20];
	long int balance;
	long int requestAmount;
} UserAccountRequest;
