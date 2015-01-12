#include "MemoryManager.h"
#include "DriveManager.h"
#include <iostream>

int main(void)
{
	DriveManager drv;
	MemoryManager mem(&drv);
	
	short* table = new short[30];

	for (int i = 0; i < 20; ++i)
		table[i] = mem.allocateMemory();

	for (int i = 0; i < 20; ++i)
		for (int j = 0; j < 16; ++j)
			mem.saveData(i, table[j]);

	mem.printFifoList();
	mem.printPageTable();
	mem.printRAM();

	drv.showSwap();

	std::cin.sync();
	std::cin.ignore();
	return 0;
}