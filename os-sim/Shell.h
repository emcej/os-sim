#pragma once
#include <string>
#include <iostream>
#include "Dispatcher.h"

class Shell
{
private:
	void newFile(std::string filename);
	void deleteFile(std::string filename);

	void enterDir(std::string directory);

	void pushProcess(std::string filename);

	void parse(std::string command);
public:
	void wait();
};