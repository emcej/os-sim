#pragma once
#include <string>
#include <iostream>
#include "ProcessManager.h"

#include "Scheduler.h"
#include "Registers.h"

class Dispatcher
{
private:
	static ProcessManager processManager;

	static Scheduler scheduler;
	static Registers registers;

	static unsigned int clock;
public:
	static void pushProcess(std::string);
	static void pushProcess(Process*);

	static void run();
};
