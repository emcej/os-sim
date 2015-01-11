#pragma once
#include <utility>
#include <vector>
#include <bitset>

struct PageTable
{
	std::vector<std::pair<unsigned char, unsigned char>> _content;
	unsigned char getFrameNumber(unsigned char pageNumber);
	unsigned char getPageNumber(unsigned char frameNumber);
	void setPageLocation(unsigned char pageNumber, char location);
};

class MemoryManager
{
private:
	unsigned char RAM[16][16];
	
	PageTable _pageTable;
 	std::vector<unsigned char> _fifoList;

	std::bitset<16> memoryIndicator;
	unsigned char findFreeMemory();

	std::bitset<256> pageIndicator;
	unsigned char findFreePage();

	//-----------------------------------------------------------------------------------------------------------------------------------------//
	void saveOnDisc(unsigned char pageNumber);
	void getFromDisc(unsigned char pageNumber);
	unsigned char takeVictim();
	
public://///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MemoryManager();
	~MemoryManager();

	unsigned char readData(short address);
	void saveData(unsigned char data, short address);

	unsigned char allocateMemory();
	void freeMemory(unsigned char pageNumber);
	//void terminateProcess();
};