#include "Dispatcher.h"

ProcessManager Dispatcher::processManager;
DriveManager Dispatcher::driveManager;
MemoryManager Dispatcher::memoryManager(&Dispatcher::driveManager);

Scheduler Dispatcher::scheduler;
Registers Dispatcher::registers;

unsigned int Dispatcher::clock = 0;

void Dispatcher::pushProcess(std::string filename)
{
	scheduler.pushProcess(processManager.CreateProcess(filename));
}
void Dispatcher::pushProcess(Process* process)
{
	scheduler.pushProcess(process);
}

void Dispatcher::run()
{
	while (true)
	{
		Process* active = scheduler.readyProcess();
		active->setState(Process::ProcessStates::RUNNING_STATE);
		registers = active->getRegisters();

		while (active->getQuantum() > 0)
		{
			std::cout << "Process " << active->getProcessName() << " running!" << std::endl;

			clock++;
			active->setQuantum(active->getQuantum() - 1);
			scheduler.ageProcesses();
			if (clock % 10 == 0)
				scheduler.scanProcesses();

			if (active->getPriorityClass() > active->getPriorityClass())
				active->setPriorityClass(active->getPriorityClass() - 1);
		}

		if (active->getProcessName() == "file2")
		{
			processManager.TerminateProcess(active->getProcessNumber());
			continue;
		}

		active->setRegisters(registers);
		active->setQuantum(6);
		active->setState(Process::ProcessStates::READY_STATE);
		pushProcess(active);
	}
}