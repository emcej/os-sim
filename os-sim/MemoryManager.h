#pragma once
#include <utility>
#include <vector>
#include <bitset>
#include <iostream>
#include "DriveManager.h"

struct PageTable
{
	std::vector<std::pair<char, char>> _content;
	char getFrameNumber(char pageNumber);
	char getPageNumber(char frameNumber);
	void setPageLocation(char pageNumber, char location);
};

class MemoryManager
{
private:
	DriveManager* driveManager;

	char RAM[16][16];
	void RAMzero();

	PageTable _pageTable;
 	std::vector<char> _fifoList;

	std::bitset<127> memoryIndicator;
	char findFreeMemory();

	std::bitset<127> pageIndicator;
	char findFreePage();

	//-----------------------------------------------------------------------------------------------------------------------------------------//
	void saveOnDisc(char pageNumber);
	char getFromDisc(char pageNumber);
	char takeVictim();
	
public://///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MemoryManager(DriveManager* driveManager);
	~MemoryManager();

	char readData(short address);
	void saveData(char data, short address);

	short allocateMemory();
	void freeMemory(char pageNumber);

	void printRAM();
	void printPageTable();
	void printFifoList();	
};