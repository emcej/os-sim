#include "Dispatcher.h"

Scheduler Dispatcher::scheduler;
Registers Dispatcher::registers;

void Dispatcher::pushProcess(Process* process)
{
	scheduler.pushProcess(process);
}

void Dispatcher::run()
{
	//pushProcess(new Process(ERYK));

	while (true)
	{

	}
}