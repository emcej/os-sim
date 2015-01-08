#include "ProcessManager.h"

Process* ProcessManager::CreateProcess(std::string name, char priorityBase)
{
		Process *tmp = new Process(name, priorityBase);
		processes.push_back(tmp);
		return tmp;
}

void ProcessManager::TerminateProcess(unsigned int processNumber)
{
	if (!DoesExist(processNumber))
	{
		throw std::string("Process doesnt exist");
	}
	else
	{
		std::list<Process*>::iterator i = processes.begin();
		while (i != processes.end())
		{
			if (processNumber == (*i)->processNumber)
			{
				(*i)->processState = TERMINATED_STATE;
				delete (*i);
				i = processes.erase(i);
			}
			else
			{
				i++;
			}
		}
	}
}

Process *ProcessManager::GetProcessHandler(unsigned int processNumber)
{
	for (auto i : processes)
	{
		if (i->processNumber == processNumber) return i;
	}
	return NULL; //jebnac throwy zamiast tej pierdoly
}

Process *ProcessManager::GetCurrentProcessHandler()
{
	for (auto i : processes)
	{
		if (i->processState == RUNNING_STATE) return i;
	}
	return NULL;
}

unsigned int ProcessManager::GetCurrentProcessNumber()
{
	for (auto i : processes)
	{
		if (i->processState == RUNNING_STATE) return i->processNumber;
	}
	return NULL;
}


std::string ProcessManager::GetCurrentProcessName()
{
	for (auto i : processes)
	{
		if (i->processState == RUNNING_STATE) return i->name;
	}
	return NULL;
}

bool ProcessManager::DoesExist(unsigned int processNumber)
{
	for (auto i : processes)
	{
		if (i->processNumber == processNumber) return true;
	}
	return false;
}

void ProcessManager::SetPriorityClass(unsigned int processNumber, char priority)
{
	this->GetProcessHandler(processNumber)->priorityDynamic = priority;
}

void ProcessManager::SetPriorityClass(Process *process, char priority)
{
	process->priorityDynamic = priority;
}