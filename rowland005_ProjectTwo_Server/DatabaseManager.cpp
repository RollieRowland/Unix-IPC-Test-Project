#include "DatabaseManager.h"

//creates a new database manager from reader and writer message queue keys
DatabaseManager::DatabaseManager(int writeKey, int readKey) {
	mqw = new MessageQueueWriter(writeKey);
	mqr = new MessageQueueReader(readKey);
}

//destructor for taking down message queues
DatabaseManager::~DatabaseManager() {
	std::cout << "Disposing of message queue writer." << std::endl;
	mqw->~MessageQueueWriter();

	std::cout << "Disposing of message queue reader." << std::endl;
	mqr->~MessageQueueReader();
}

//creates and sends an operation to the database with a out reference error/message string
bool DatabaseManager::performOperation(UserAccountRequest uar, std::string &str) {
	//writes, reads response, then responds if the database took the message
	struct operation op = DatabaseManager::createOperation(uar);

	int tempOpCode = op.opcode;

	if (mqw->writeOperation(op)) {
		std::cout << "Message added to the queue successfully." << std::endl;
	}
	else {
		perror("Message queue add to database failed");
	}

	struct operation tempOp = mqr->readOperation();

	if (tempOp.return_code == 0) {
		std::cout << "Operation read successfully." << std::endl;

		//generates response for client
		if (tempOpCode == 6) {
			std::string amount;
			std::stringstream ss;
			ss << tempOp.amount;
			ss >> amount;

			str.append("Account Number: ");
			str.append(tempOp.account_number);
			str.append(" First Name: ");
			str.append(tempOp.first_name);
			str.append(" Last Name: ");
			str.append(tempOp.last_name);
			str.append(" Amount: ");
			str.append(amount);
		}
		else if (tempOpCode == 3 || tempOpCode == 4){
			std::string amount;
			std::stringstream ss;
			ss << tempOp.amount;
			ss >> amount;

			str.append("Account Number: ");
			str.append(tempOp.account_number);
			str.append(" Balance: ");
			str.append(amount);
		}
		else if (tempOpCode == 1) {
			str.append("Account added successfully.");
		}
		else if (tempOpCode == 2) {
			str.append("Account deleted successfully.");
		}
		else if (tempOpCode == 5) {
			str.append("Account modified successfully.");
		}


		return true;
	}
	else {
		std::cout << "Operation read failed, opcode: " << tempOp.return_code << std::endl;

		//error handling for database
		switch (tempOp.return_code) {
		case 0:
			str.append("No database error - Requested operation was performed");
			break;
		case 1:
			str.append("Invalid op code");
			break;
		case 2:
			str.append("Invalid account number was given – account number must contain exactly five(5) digits");
			break;
		case 11:
			str.append("Add requested, but database is full.  Cannot add a new customer at this time.");
			break;
		case 12:
			str.append("Add requested, but a customer with this account number already exists, so this customer cannot be added.");
			break;
		case 21:
			str.append("Delete requested, but there is no record in the database with the specified account number, so the customer cannot be deleted.");
			break;
		case 31:
			str.append("Deposit requested, but there is no record in the database with the specified account number, so the deposit cannot be made.");
			break;
		case 41:
			str.append("Withdrawal requested, but there is no record in the database with the specified account number, so the withdrawal cannot be made.");
			break;
		case 42:
			str.append("Withdrawal requested, but account has insufficient funds.  The withdrawal is denied and the balance is unchanged.");
			break;
		case 51:
			str.append("Modify requested, but there is no record in the database with the specified account number, so cannot modify.");
			break;
		case 61:
			str.append("Read requested, but there is no record in the database with the specified account number, so cannot read.");
			break;
		default:
			str.append("Unknown error has occurred.");
			break;
		}

		return false;
	}
}

//creates a new operation struct from a user account request object
struct operation DatabaseManager::createOperation(UserAccountRequest uar) {
	struct operation op;

	memset(op.account_number, '\0', 6);
	memset(op.first_name, '\0', 11);
	memset(op.last_name, '\0', 21);
	memset(op.user_string, '\0', 21);


	if (uar.ar == Add || uar.ar == Change) {
		op.amount = uar.balance;
	}
	else {
		op.amount = uar.requestAmount;
	}

	strcpy(op.account_number, uar.accountNumber);
	strcpy(op.user_string, "null\0");

	if (uar.ar == Add) op.opcode = 1;
	if (uar.ar == Delete) op.opcode = 2;
	if (uar.ar == Deposit) op.opcode = 3;
	if (uar.ar == Withdrawal) op.opcode = 4;
	if (uar.ar == Change) op.opcode = 5;
	if (uar.ar == View) op.opcode = 6;

	if (op.opcode == 1 || op.opcode == 5) {
		strcpy(op.first_name, uar.firstName);
		strcpy(op.last_name, uar.lastName);
	}

	op.message_type = 1;
	op.return_code = -1;
	op.user_int1 = -1;
	op.user_int2 = -1;

	return op;
}

//shutsdown the database
void DatabaseManager::shutdown() {
	struct operation op;

	op.message_type = 1;
	op.opcode = 15;

	mqw->writeOperation(op);
}
