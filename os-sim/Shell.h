#pragma once
#include "UserManager.h"
#include "Split.h"
#include <regex>
#include <string>
#include <iostream>
#include "Dispatcher.h"

class Shell
{
private:
	UserManager userManager;

	enum Rules
	{
		password,
		name,
		command,
		fileName,
		number,
		word,
		folderName
	};
	std::list<std::string> OrdersDesciobsions;

	char translateStrToHex(std::string val);
	std::string translateStrToHex(char val);

	bool CheckIfStringIsValid(std::string command, unsigned int rule);

	bool Parse(std::string command);
public:
	void help();
	Shell();
	void Wait();
};