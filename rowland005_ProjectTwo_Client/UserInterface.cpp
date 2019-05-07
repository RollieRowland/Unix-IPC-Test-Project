#include "UserInterface.h"

UserInterface::UserInterface() {
	shutdown = false;
}

UserAccountRequest UserInterface::readTellerControl() {
	bool loop = true;
	UserAccountRequest uar;

	std::cout << "Hello teller client." << std::endl;

	while (loop) {
		std::cout << "Which action would you like to perform? Enter the number for the action item." << std::endl;
		std::cout << " 1: Add a new account." << std::endl;
		std::cout << " 2: Delete an account." << std::endl;
		std::cout << " 3: Modify account information." << std::endl;
		std::cout << " 4: Make a deposit." << std::endl;
		std::cout << " 5: Make a withdrawal." << std::endl;
		std::cout << " 6: Display client information." << std::endl;
		std::cout << " 7: Shutdown client." << std::endl;

		std::string actionItem;
		std::string str;

		std::getline(std::cin, actionItem);

		switch (atoi(actionItem.c_str())) {
		case 1:
			std::cout << "You have selected to create a new account. To cancel, enter 'cancel'." << std::endl;
			std::cout << "To continue, enter account number, last name, first name, and initial balance as follows: 'accountNumber lastName firstName initialBalance'." << std::endl;

			std::getline(std::cin, str);

			if (!strcmp(str.c_str(), "cancel")) {
				std::cout << "    Action cancelled." << std::endl;
			}
			else {
				loop = false;
				uar = UserInterface::uarFromVector(Add, UserInterface::splitString(str));

				std::cout << "1: User account request created." << std::endl << std::endl;
			}

			break;
		case 2:
			std::cout << "You have selected to delete an account. To cancel, enter 'cancel'." << std::endl;
			std::cout << "To continue, enter the account number." << std::endl;

			std::getline(std::cin, str);

			if (!strcmp(str.c_str(), "cancel")) {
				std::cout << "    Action cancelled." << std::endl;
			}
			else {
				loop = false;
				uar = UserInterface::uarFromVector(Delete, UserInterface::splitString(str));

				std::cout << "2: User account request created." << std::endl;
			}

			break;
		case 3:
			std::cout << "You have selected to modify an account. To cancel, enter 'cancel'." << std::endl;
			std::cout << "To continue, enter account number, last name, first name, and balance as follows: 'accountNumber lastName firstName balance'." << std::endl;

			std::getline(std::cin, str);

			if (!strcmp(str.c_str(), "cancel")) {
				std::cout << "    Action cancelled." << std::endl;
			}
			else {
				loop = false;
				uar = UserInterface::uarFromVector(Change, UserInterface::splitString(str));

				std::cout << "3: User account request created." << std::endl;
			}

			break;
		case 4:
			std::cout << "You have selected to make a deposit. To cancel, enter 'cancel'." << std::endl;
			std::cout << "To continue, enter the account number and amount to deposit as follows: 'accountNumber amount'" << std::endl;

			std::getline(std::cin, str);

			if (!strcmp(str.c_str(), "cancel")) {
				std::cout << "    Action cancelled." << std::endl;
			}
			else {
				loop = false;
				uar = UserInterface::uarFromVector(Deposit, UserInterface::splitString(str));

				std::cout << "4: User account request created." << std::endl;
			}

			break;
		case 5:
			std::cout << "You have selected to make a withdrawal. To cancel, enter 'cancel'." << std::endl;
			std::cout << "To continue, enter the account number and amount to withdrawal as follows: 'accountNumber amount'" << std::endl;

			std::getline(std::cin, str);

			if (!strcmp(str.c_str(), "cancel")) {
				std::cout << "    Action cancelled." << std::endl;
			}
			else {
				loop = false;
				uar = UserInterface::uarFromVector(Withdrawal, UserInterface::splitString(str));

				std::cout << "5: User account request created." << std::endl;
			}

			break;
		case 6:
			std::cout << "You have selected to view client information. To cancel, enter 'cancel'." << std::endl;
			std::cout << "To continue, enter the account number and amount to view as follows: 'accountNumber'" << std::endl;

			std::getline(std::cin, str);

			if (!strcmp(str.c_str(), "cancel")) {
				std::cout << "    Action cancelled." << std::endl;
			}
			else {
				loop = false;
				uar = UserInterface::uarFromVector(View, UserInterface::splitString(str));

				std::cout << "6: User account request created." << std::endl;
			}

			break;
		case 7:
			std::cout << "Shutting down client." << std::endl;

			shutdown = true;
			loop = false;

			break;
		default:
			std::cout << "You have selected an invalid option." << std::endl << std::endl;
			break;
		}

		if (!loop) {
			break;
		}
	}

	return uar;
}

UserAccountRequest UserInterface::readCustomerControl() {
	bool loop = true;
	UserAccountRequest uar;

	std::cout << "Hello customer client." << std::endl;

	while (loop) {
		std::cout << "Which action would you like to perform? Enter the number for the action item." << std::endl;
		std::cout << " 1: Make a withdrawal." << std::endl;
		std::cout << " 2: Display account information." << std::endl;
		std::cout << " 3: Shutdown client." << std::endl;

		std::string actionItem;
		std::string str;

		std::getline(std::cin, actionItem);

		switch (atoi(actionItem.c_str())) {
		case 1:
			std::cout << "You have selected to make a withdrawal. To cancel, enter 'cancel'." << std::endl;
			std::cout << "To continue, enter the account number and amount to withdrawal as follows: 'accountNumber amount'" << std::endl;

			std::getline(std::cin, str);

			if (!strcmp(str.c_str(), "cancel")) {
				std::cout << "    Action cancelled." << std::endl;
			}
			else {
				loop = false;
				uar = UserInterface::uarFromVector(Withdrawal, UserInterface::splitString(str));

				std::cout << "5: User account request created." << std::endl;
			}

			break;
		case 2:
			std::cout << "You have selected to view client information. To cancel, enter 'cancel'." << std::endl;
			std::cout << "To continue, enter the account number and amount to view as follows: 'accountNumber'" << std::endl;

			std::getline(std::cin, str);

			if (!strcmp(str.c_str(), "cancel")) {
				std::cout << "    Action cancelled." << std::endl;
			}
			else {
				loop = false;
				uar = UserInterface::uarFromVector(View, UserInterface::splitString(str));

				std::cout << "6: User account request created." << std::endl;
			}

			break;
		case 3:
			std::cout << "Shutting down client." << std::endl;

			shutdown = true;
			loop = false;

			break;
		default:
			std::cout << "You have selected an invalid option." << std::endl << std::endl;
			break;
		}

		if (!loop) {
			break;
		}
	}

	return uar;
}

UserAccountRequest UserInterface::uarFromVector(AccountRequest ar, std::vector<std::string> str) {
	UserAccountRequest uar;

	//Creates new user account requests through parsing vector
	if (ar == Add || ar == Change) {
		std::stringstream acNum(str[0]);
		std::stringstream lastN(str[1]);
		std::stringstream firsN(str[2]);
		std::stringstream balan(str[3]);

		acNum >> uar.accountNumber;
		balan >> uar.balance;
		lastN >> uar.lastName;
		firsN >> uar.firstName;
		uar.ar = ar;
		uar.requestAmount = 0;
	}
	else if (ar == Delete || ar == View) {
		std::stringstream acNum(str[0]);

		acNum >> uar.accountNumber;
		uar.ar = ar;
	}
	else {
		std::stringstream acNum(str[0]);
		std::stringstream amoun(str[1]);

		acNum >> uar.accountNumber;
		amoun >> uar.requestAmount;
		uar.ar = ar;
	}

	return uar;
}

std::vector<std::string> UserInterface::splitString(std::string str) {
	std::vector<std::string> result;
	std::istringstream iss(str);

	//splits string based on space as delimiter
	for (std::string temp; iss >> temp;) {
		result.push_back(temp);
	}

	return result;
}

bool UserInterface::didUserRequestShutdown() {
	return shutdown;
}
