#pragma once
#include <string>
#include <bitset>
#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include "File.h"

class DriveManager
{
private:
	char sectors[64][32];
	std::bitset<64> freeSectors;

	std::string currentPath;
	char currentSector;

	std::pair<char, short> findFileAddress(File& file);
	std::pair<char, short> findFileAddress(char filename[8]);
	char findEmptySector();
	void moveUp(char sector, short removalAddress);

	time_t getCurrentDateAndTime();

	short stringToInt(std::string str);
	char monthToInt(std::string month);
public:
	static enum FileAttributes
	{
		READ_ONLY = 0x01,
		HIDDEN = 0x02,
		SYSTEM = 0x04,
		DIRECTORY = 0x08
	};

	DriveManager();
	~DriveManager();

	void createFile(char filename[8], char extension[3], bool flagReadOnly = false, bool flagHidden = false, bool flagSystem = false, bool flagDirectory = false);
	void removeFile(File& file);
	void renameFile(File& file, char newFilename[8], char newExtension[3]);

	void editFile(File& file);
	void saveToSwap(char sign, short location);
	char readFromSwap(short offset);

	std::vector<File> getDirContent();

	void showSwap();
};