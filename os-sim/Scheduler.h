#pragma once
#include <queue>
#include <bitset>

struct Process
{

};

class Scheduler
{
private:
	std::queue<Process*> queueProcess[9];
	std::bitset<9> queueIndicator;

public:
	Process* readyProcess();
	void scanProcesses();

	void pushProcess(Process*);
};