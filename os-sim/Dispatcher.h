#pragma once
#include <string>
#include "ProcessManager.h"

#include "Scheduler.h"
#include "Registers.h"

class Dispatcher
{
private:
	static ProcessManager processManager;

	static Scheduler scheduler;
	static Registers registers;
public:
	static void pushProcess(std::string filename);

	static void run();
};
