#pragma once
#include "Process.h"
#include <list>

class ProcessManager
{
public:
	std::list<Process *> processes;

	Process* CreateProcess(std::string processName, char priorityBase = NORMAL_PRIORITY_CLASS);
	void TerminateProcess(unsigned int processNumber);

	Process *GetProcessHandler(unsigned int processNumber);
	
	Process *GetCurrentProcessHandler();
	unsigned int GetCurrentProcessNumber();
	std::string GetCurrentProcessName();

	bool DoesExist(unsigned int processNumber);

	void SetPriorityClass(unsigned int processNumber, char priority);
	void SetPriorityClass(Process *process, char priority);
};