#include "UserInputManager.h"

//Creates manager for user interface
UserInputManager::UserInputManager() {
	this->ui = UserInterface();
}

//reads controls from user interface
UserAccountRequest UserInputManager::readControl(bool isCustomer) {
	if (!isCustomer) {
		return ui.readCustomerControl();
	}
	else {
		return ui.readTellerControl();
	}
}

//writes message to user interface
void UserInputManager::writeMessage(std::string str) {
	std::cout << str << std::endl;
}

//will return true unless the user requested shutdown
bool UserInputManager::running() {
	return !ui.didUserRequestShutdown();
}
