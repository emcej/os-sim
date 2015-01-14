#pragma once
#include <utility>
#include <vector>
#include <bitset>
#include <iostream>
#include "DriveManager.h"

#define FRAME_NUMBER 16	//Pewien nie jestem ale 16 bêdzie chyba górn¹ granic¹
#define FRAME_SIZE 16	// Pewien nie jestem ale 16 bêdzie chyba górn¹ granic¹
#define MAX_ADDRESS 127       // MAX_ADDRESS belongs to reach 0..127 included

struct PageTable
{
	std::vector<std::pair<char, char>> _content;
	char getFrameNumber(char pageNumber);
	char getPageNumber(char frameNumber);
	void setPageLocation(char pageNumber, char location);
	void printPageTable();
};

class MemoryManager
{
private:
	DriveManager* driveManager;

	char RAM[FRAME_NUMBER][FRAME_SIZE];
	void RAMzero();

	PageTable _pageTable;
 	std::vector<char> _fifoList;

	std::bitset<MAX_ADDRESS> memoryIndicator;
	char findFreeMemory();

	std::bitset<MAX_ADDRESS> pageIndicator;
	char findFreePage();

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