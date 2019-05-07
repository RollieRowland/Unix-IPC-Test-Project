#pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>

#include "UserAccountRequest.h"

class UserInterface {
private:
	bool shutdown;
	std::vector<std::string> splitString(std::string);
	UserAccountRequest uarFromVector(AccountRequest, std::vector<std::string>);
public:
	UserInterface();
	UserAccountRequest readTellerControl();
	UserAccountRequest readCustomerControl();
	bool didUserRequestShutdown();
};
