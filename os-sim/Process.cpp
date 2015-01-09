#include "Process.h"

Process::Process()
{
	this->quantum = 6;
}

Process::Process(std::string name, char priorityBase)
{
	this->processState = NEW_STATE;
	this->name = name;
	this->processNumber = processNumber;
	this->priorityBase = priorityBase;
	this->priorityDynamic = priorityBase;
	this->processState = READY_STATE;
	this->quantum = 6;
}

std::string Process::getProcessName()
{
	return this->name;
}

unsigned int Process::getProcessNumber()
{
	return this->processNumber;
}

char Process::getBasePriorityClass()
{
	return this->priorityBase;
}

void Process::setPriorityClass(char prior)
{
	this->priorityDynamic = prior;
}

char Process::getPriorityClass()
{
	return this->priorityDynamic;
}

void Process::setQuantum(unsigned int quantum)
{
	this->quantum = quantum;
}

unsigned int Process::getQuantum()
{
	return this->quantum;
}

void Process::setState(char state)
{
	this->processState = state;
}

char Process::getState()
{
	return this->processState;
}

void Process::setRegisters(Registers& registers)
{
	this->registers.a = registers.a;
	this->registers.b = registers.b;
	this->registers.c = registers.c;
	this->registers.d = registers.d;
	this->registers.pc = registers.pc;
}
Registers& Process::getRegisters()
{
	return registers;
}

void Process::AddPageToPageTable(unsigned char pageNumber)
{
	for (auto i : pageTable)
	{
		if (i == pageNumber)
			throw std::string("Page Number: " + std::to_string(pageNumber)
			+ " already exists in process with ID: " + std::to_string(this->processNumber));
	}
	pageTable.push_back(pageNumber);
}

unsigned char Process::DeletePageFromPageTable(unsigned char pageNumber)
{
	auto toDelete = std::find(pageTable.begin(), pageTable.end(), pageNumber);

	if (toDelete == pageTable.end())
		throw std::string("Page number: " + std::to_string(pageNumber) + " doesnt exist");
	else
		pageTable.erase(toDelete);
}