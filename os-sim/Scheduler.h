#pragma once
#include <list>
#include <bitset>
#include "Process.h"

class Scheduler
{
private:
	std::list<std::pair<Process*, unsigned>> queueProcess[9];
	std::bitset<9> queueIndicator;

public:
	Scheduler();
	~Scheduler();

	Process* readyProcess();
	void scanProcesses();

	void ageProcesses();

	void pushProcess(Process*);
};