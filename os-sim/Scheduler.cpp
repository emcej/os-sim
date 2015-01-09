#include "Scheduler.h"

Scheduler::Scheduler()
{
	queueProcess[0].push_front(std::pair<Process*, unsigned>(new Process("idle", 0), 0));
}
Scheduler::~Scheduler() {}

Process* Scheduler::readyProcess()
{
	int x = 0;
	for (int i = 8; i > 0; i--)
		if (!queueProcess[i].empty())
		{
			x = i;
			break;
		}

	Process* temp = queueProcess[x].front().first;
	queueProcess[x].pop_front();
	return temp;
}
void Scheduler::scanProcesses()
{
	for (int i = 8; i > 0; i--)
		for (auto iter = queueProcess[i].begin(); iter != queueProcess[i].end();)
			if (iter->second > 30)
			{
				auto temp = *iter;
				temp.first->setPriorityClass(Process::PriorityClasses::MAX_PRIORITY_CLASS);
				temp.first->setQuantum(temp.first->getQuantum() * 2);
				queueProcess[temp.first->getPriorityClass()].push_back(temp);
				iter = queueProcess[i].erase(iter);
			}
			else
				iter++;
}

void Scheduler::ageProcesses()
{
	for (int i = 8; i > 0; i--)
		for (auto& j : queueProcess[i])
				j.second++;
}

void Scheduler::pushProcess(Process* process)
{
	queueProcess[process->getPriorityClass()].push_back(std::pair<Process*, unsigned>(process, 0));
}