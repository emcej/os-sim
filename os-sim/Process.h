#pragma once
#include "ProcessDeclarations.h"
#include <string>

class Process
{
public:
	std::string name;

	char processState;

	unsigned int processNumber;
	static unsigned int processNumberStatic;

	char priorityBase;
	char priorityDynamic;

	Registers registers;

	Process();
	Process(std::string name, char priorityBase = NORMAL_PRIORITY_CLASS);
};