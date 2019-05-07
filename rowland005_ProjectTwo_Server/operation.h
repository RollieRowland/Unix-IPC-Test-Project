#pragma once

struct operation {
	long message_type;

	int opcode;
	int return_code;
	int user_int1;
	int user_int2;
	char user_string[21];
	char account_number[6];
	char last_name[21];
	char first_name[11];
	long int amount;
};
