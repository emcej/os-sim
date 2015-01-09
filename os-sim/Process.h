#pragma once
#include "Registers.h"
#include <vector>
#include <string>

class Process
{
private:
	std::string name;
	unsigned int processNumber;

	char priorityBase;
	char priorityDynamic;

	unsigned int quantum;

	char processState;

	Registers registers;

	std::vector<unsigned char> pageTable;
public:
	static enum ProcessStates
	{
		NEW_STATE,
		RUNNING_STATE,
		WAITING_STATE,
		READY_STATE,
		TERMINATED_STATE
	};

	static enum PriorityClasses
	{
		IDLE_PRIORITY_CLASS = 1,
		LOW_PRIORITY_CLASS = 2,
		BELOW_NORMAL_PRIORITY_CLASS = 3,
		NORMAL_PRIORITY_CLASS = 4,
		ABOVE_NORMAL_PRIORITY_CLASS = 5,
		HIGH_PRIORITY_CLASS = 6,
		ULTRA_HIGH_PRIORITY_CLASS = 7,
		MAX_PRIORITY_CLASS = 8
	};

	Process();
	Process(std::string name, char priorityBase = NORMAL_PRIORITY_CLASS);

	std::string getProcessName();
	unsigned int getProcessNumber();

	char getBasePriorityClass();

	void setPriorityClass(char prior);
	char getPriorityClass();

	void setQuantum(unsigned int quantum);
	unsigned int getQuantum();

	void setState(char state);
	char getState();

	void setRegisters(Registers& registers);
	Registers& getRegisters();

	void AddPageToPageTable(unsigned char pageNumber);
	unsigned char DeletePageFromPageTable(unsigned char pageNumber);
};