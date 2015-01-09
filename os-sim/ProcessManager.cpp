#include "ProcessManager.h"

Process* ProcessManager::CreateProcess(std::string name, char priorityBase)
{
	try
	{
		Process *tmp = new Process(name, priorityBase);
		processes.push_back(tmp);
		return tmp;
	}
	catch (...)
	{
		throw std::string("Process creating went wrong");
	}
}

void ProcessManager::TerminateProcess(unsigned int processNumber)
{
	if (!DoesExist(processNumber))
	{
		throw std::string("Process with ID: " + std::to_string(processNumber) + " doesnt exist");
	}
	else
	{
		std::list<Process*>::iterator i = processes.begin();
		while (i != processes.end())
		{
			if (processNumber == (*i)->getProcessNumber())
			{
				(*i)->setState(Process::ProcessStates::TERMINATED_STATE);
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
		if (i->getProcessNumber() == processNumber) return i;
	}
	throw std::string("There is no process with ID: " + std::to_string(processNumber));
}

Process *ProcessManager::GetCurrentProcessHandler()
{
	for (auto i : processes)
	{
		if (i->getState() == Process::ProcessStates::RUNNING_STATE) return i;
	}
	throw std::string("There is no current process");
}

unsigned int ProcessManager::GetCurrentProcessNumber()
{
	for (auto i : processes)
	{
		if (i->getState() == Process::ProcessStates::RUNNING_STATE) return i->getProcessNumber();
	}
	throw std::string("There is no current process");
}


std::string ProcessManager::GetCurrentProcessName()
{
	for (auto i : processes)
	{
		if (i->getState() == Process::ProcessStates::RUNNING_STATE) return i->getProcessName();
	}
	throw std::string("There is no current process");
}

bool ProcessManager::DoesExist(unsigned int processNumber)
{
	for (auto i : processes)
	{
		if (i->getProcessNumber() == processNumber) return true;
	}
	return false;
}