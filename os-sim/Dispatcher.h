#pragma once

#include "Scheduler.h"
#include "Registers.h"

class Dispatcher
{
private:
	static Scheduler scheduler;
	static Registers registers;
public:
	static void pushProcess(Process*);

	static void run();
};
