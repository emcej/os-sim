#include "Process.h"

unsigned int Process::processNumberStatic = 0;

Process::Process()
{
}

Process::Process(std::string name, char priorityBase)
{
	this->processState = NEW_STATE;
	this->name = name;
	this->processNumber = processNumberStatic++;
	this->priorityBase = priorityBase;
	this->processState = READY_STATE;
}