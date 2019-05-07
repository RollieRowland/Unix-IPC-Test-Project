#pragma once

#include "UserInterface.h"

class UserInputManager {
private:
	UserInterface ui;

public:
	UserInputManager();
	UserAccountRequest readControl(bool isCustomer);
	void writeMessage(std::string);
	bool running();

};
