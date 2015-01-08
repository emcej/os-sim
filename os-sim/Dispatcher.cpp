#include "Dispatcher.h"

ProcessManager Dispatcher::processManager;

Scheduler Dispatcher::scheduler;
Registers Dispatcher::registers;

void Dispatcher::pushProcess(std::string filename)
{
	scheduler.pushProcess(processManager.CreateProcess(filename));
}

void Dispatcher::run()
{
	
	while (true)
	{

	}
}