#include "DriveManager.h"

std::pair<char, short> DriveManager::findFileAddress(File& file)
{
	char workingSector = currentSector;
	while (workingSector != 0x7F)
	{
		for (short address = 0; address < 0x200; address += 0x14)
		{
			if (sectors[workingSector][address] == 0x00)
				throw (std::string)"File not found!";

			char tempFilename[8];
			for (int i = 0; i < 8; ++i)
				file.filename[i] = sectors[workingSector][i];
			if (strcmp(file.filename, tempFilename) == 0)
				return std::pair<char, short>(workingSector, sectors[workingSector][address]);
		}
	}
	throw (std::string)"File not found!";
}
std::pair<char, short> DriveManager::findFileAddress(char filename[8])
{
	char workingSector = currentSector;
	while (workingSector != 0x7F)
	{
		for (short address = 0; address < 0x200; address += 0x14)
		{
			if (sectors[workingSector][address] == 0x00)
				throw (std::string)"File not found!";

			std::string tempFilename1(filename);
			std::string tempFilename2;
			for (int i = 0; i < 8; ++i)
			{
				if (sectors[workingSector][address + i] == 0x00)
					break;
				tempFilename2 += sectors[workingSector][address + i];
			}
			if (tempFilename1 == tempFilename2)
			{
				std::pair<char, short> x;
				x.first = workingSector;
				x.second = address;
				return x;
			}
		}
	}
	throw (std::string)"File not found!";
}

char DriveManager::findEmptySector()
{
	for (int i = 0; i < 64; ++i)
		if (!freeSectors[i])
		{
			freeSectors[i] = true;
			for (int address = 0x00; address < 0x200; ++address)
				sectors[i][address] = 0x00;
			return i;
		}
	throw (std::string)"Drive full!";
}
void DriveManager::moveUp(char sector, short removalAddress)
{
	char tempChar = sectors[sector][removalAddress + 0x14];
	while (tempChar != 0x00)
	{
		for (short i = 0x00; i < 0x14; ++i)
			sectors[sector][removalAddress + i] = sectors[sector][removalAddress + i + 0x14];
		removalAddress += 0x14;

		if (removalAddress == 0x1EC)
		{
			if (sectors[0][sector] != 0x7F)
			{
				for (short i = 0x00; i < 0x14; ++i)
					sectors[sector][removalAddress + i] = sectors[ sectors[0][sector] ][i];
				sector = sectors[0][sector];
				removalAddress = 0x00;
				tempChar = sectors[sector][removalAddress + 0x14];
			}
			else
			{
				for (short i = 0x00; i < 0x14; ++i)
					sectors[sector][removalAddress + i] = 0x00;
				tempChar = 0x00;
			}
		}
		else
			tempChar = sectors[sector][removalAddress + 0x14];
	}
}

time_t DriveManager::getCurrentDateAndTime()
{
	std::chrono::time_point<std::chrono::system_clock> time;
	time = std::chrono::system_clock::now();
	return std::chrono::system_clock::to_time_t(time);
}

short DriveManager::stringToInt(std::string str)
{
	int tmp = 0, i = 0;
	bool m = false;
	if (str[0] == '-') {
		m = true;
		i++;
	}
	for (; i < (int)str.size(); i++)
		tmp = 10 * tmp + str[i] - 48;
	return m ? -tmp : tmp;
}
char DriveManager::monthToInt(std::string month)
{
	if (month == "Jan")
		return 1;
	if (month == "Feb")
		return 2;
	if (month == "Mar")
		return 3;
	if (month == "Apr")
		return 4;
	if (month == "May")
		return 5;
	if (month == "Jun")
		return 6;
	if (month == "Jul")
		return 7;
	if (month == "Aug")
		return 8;
	if (month == "Sep")
		return 9;
	if (month == "Oct")
		return 10;
	if (month == "Nov")
		return 11;
	if (month == "Dec")
		return 12;

	throw (std::string)"Invalid month!";
}

DriveManager::DriveManager()
{ 
	for (int i = 0; i < 64; ++i)
		for (int j = 0; j < 512; ++j)
			sectors[i][j] = 0x00;		//Formatting entire drive
	sectors[0][0] = 0x7F;				//Creating FAT entry for root directory
	sectors[0][1] = 0x7F;

	freeSectors.reset();
	freeSectors[0] = 1;
	freeSectors[1] = 1;					//Setting bitset to initial (all zeroes but FAT table and root directory)

	currentSector = 0x01;
	currentPath = "";

	createFile("swap", "", false, true, true, false);
}
DriveManager::~DriveManager() {}

/****************************************
**           Wpis katalogowy           **
*****************************************
** Bajt       Dane                     **
** --------   ------------------------ **
** 01234567 - nazwa                    **
** 89A      - rozszerzenie             **
** B        - flagi                    **
** CD       - czas                     **
** EF       - data                     **
** 0        - numer pierwszego sektora **
** 1234     - rozmiar                  **
****************************************/

void DriveManager::createFile(char filename[8], char extension[3], bool flagReadOnly, bool flagHidden, bool flagSystem, bool flagDirectory)
{
	char workingSector = currentSector;
	short address = 0x00;
	do
	{
		bool sectorFull = true;
		while (address < 0x200 && sectorFull)
		{
			if (sectors[workingSector][address] == 0x00)
				sectorFull = false;
			else
				address += 0x15;
		}
				

		if (sectorFull)
		{
			if (sectors[0][workingSector] == 0x7F)
			{
				try {
					address = 0x00;
					workingSector = findEmptySector();
					sectors[0][currentSector] = workingSector;
					sectors[0][workingSector] = 0x7F;
				}
				catch (std::string error) {
					throw error;
				}
			}
			else
				workingSector = sectors[0][workingSector];
		}
	} while (sectors[0][workingSector] != 0x7F);

	// FILENAME ASSIGNMENT
	int k = 0;
	for (int j = address; j < address + 0x08; ++j)
		sectors[workingSector][j] = filename[k++];
	
	// EXTENSION ASSIGNMENT
	k = 0;
	if (flagDirectory)
		for (int j = address + 8; j < address + 0x0B; ++j)
			sectors[workingSector][j] = 0x00;
	else
		for (int j = address + 8; j < address + 0x0B; ++j)
			sectors[workingSector][j] = extension[k++];

	// FLAGS
	sectors[workingSector][address + 0x0B] = 0x00;
	if (flagReadOnly)
		sectors[workingSector][address + 0x0B] |= FileAttributes::READ_ONLY;
	if (flagHidden)
		sectors[workingSector][address + 0x0B] |= FileAttributes::HIDDEN;
	if (flagSystem)
		sectors[workingSector][address + 0x0B] |= FileAttributes::SYSTEM;
	if (flagDirectory)
		sectors[workingSector][address + 0x0B] |= FileAttributes::DIRECTORY;

	time_t time = getCurrentDateAndTime();
	std::string timeAndDateString(std::ctime(&time));

	//TIME
	std::string timeString = timeAndDateString.substr(11, 8);
	char hour = (char)stringToInt(timeString.substr(0, 2));
	char minute = (char)stringToInt(timeString.substr(3, 2));
	char second = (char)stringToInt(timeString.substr(6, 2)) / 2;

	char timeA, timeB;
	timeA = hour << 3;
	timeA |= minute >> 3;
	timeB = minute << 5;
	second = second << 3;
	second = second >> 3;
	timeB |= second;

	sectors[workingSector][address + 0x0C] = timeB;
	sectors[workingSector][address + 0x0D] = timeA;

	//DATE
	std::string dateString = timeAndDateString.substr(8, 2) + timeAndDateString.substr(4, 3) + timeAndDateString.substr(20, 4);
	char day = (char)stringToInt(timeAndDateString.substr(8, 2));
	char month = monthToInt(timeAndDateString.substr(4, 3));
	char year = stringToInt(timeAndDateString.substr(20, 4)) - 1980;
	
	char dateA, dateB;
	dateA = year << 1;
	dateA |= month >> 3;
	dateB = month << 5;
	day = day << 3;
	day = day >> 3;
	dateB |= day;

	sectors[workingSector][address + 0x0E] = dateB;
	sectors[workingSector][address + 0x0F] = dateA;

	// FIRST SECTOR NUMBER
	try {
		char startingSector = findEmptySector();
		sectors[workingSector][address + 0x10] = startingSector;
	}
	catch (std::string error) {
		throw error;
	}

	//SIZE
	sectors[workingSector][address + 0x11] = 0x00;
	sectors[workingSector][address + 0x12] = 0x00;
	sectors[workingSector][address + 0x13] = 0x00;
	sectors[workingSector][address + 0x14] = 0x00;
}
void DriveManager::removeFile(File& file)
{
	// Finding a file in a directory
	std::pair<char, short> tempPair;
	try {
		tempPair = findFileAddress(file);
	}
	catch (std::string error) {
		throw error;
	}
	char workingSector = tempPair.first;
	short tempAddress = tempPair.second;

	// Clearing FAT Table
	short tempFATsector = sectors[0][ sectors[workingSector][tempAddress] ];
	do
	{
		char temp = sectors[0][tempFATsector];
		sectors[0][tempFATsector] = 0x00;
		tempFATsector = temp;
	} while (sectors[0][tempAddress] != 0x7F);
	sectors[0][tempFATsector] = 0x00;

	// Moving all files below, up!
	moveUp(workingSector, tempAddress);
}
void DriveManager::renameFile(File& file, char newFilename[8], char newExtension[3])
{
	// Finding a file in a directory
	std::pair<char, short> tempPair;
	try {
		tempPair = findFileAddress(file);
	}
	catch (std::string error) {
		throw error;
	}
	char workingSector = tempPair.first;
	short tempAddress = tempPair.second;

	for (int i = 0x00; i < 0x08; ++i)
		sectors[workingSector][tempAddress + i] = newFilename[i];
	for (int i = 0x08; i < 0x0B; ++i)
		sectors[workingSector][tempAddress + i] = newExtension[i];
}

void DriveManager::editFile(File& file)
{
	// Finding a file in a directory
	std::pair<char, short> tempPair;
	try {
		tempPair = findFileAddress(file);
	}
	catch (std::string error) {
		throw error;
	}
	char workingSector = sectors[tempPair.first][tempPair.second + 0x10];
	
	short i = 0x00;
	int currentData = sectors[workingSector][i];
	int newData = 0x00;
	while (newData != 0x7F)
	{
		std::cout << "[" << std::hex << i << "] : " << std::hex << currentData << "  ";
		std::cin >> std::hex >> newData;
		std::cout << std::endl;

		sectors[workingSector][i] = (char)newData;
		currentData = (int)sectors[workingSector][i++];
	}
}
void DriveManager::saveToSwap(char sign, short offset)
{
	// Finding a file in a directory
	std::pair<char, short> tempPair;
	try {
		tempPair = findFileAddress("swap");
	}
	catch (std::string error) {
		throw error;
	}
	char workingSector = sectors[tempPair.first][tempPair.second + 0x10];

	while (offset > 0x200)
	{
		if (sectors[0][workingSector] == 0x7F)
			workingSector = findEmptySector();
		else
			workingSector = sectors[0][workingSector];
	}

	sectors[workingSector][offset] = sign;
}
char DriveManager::readFromSwap(short offset)
{
	// Finding a file in a directory
	std::pair<char, short> tempPair;
	try {
		tempPair = findFileAddress("swap");
	}
	catch (std::string error) {
		throw error;
	}
	char workingSector = sectors[tempPair.first][tempPair.second + 0x10];

	while (offset > 0x200)
	{
		if (sectors[0][workingSector] == 0x7F)
			throw (std::string)"Error! Offset to big! EOF!";
		else
			workingSector = sectors[0][workingSector];
	}

	return sectors[workingSector][offset];
}

std::vector<File> DriveManager::getDirContent()
{
	std::vector<File> dirContent;
	for (int i = 0; i < 512; i += 0x15)
		if (sectors[currentSector][i] != 0x00)
		{
		File currentFile;
		int k = 0;
		for (int j = i; j < i + 0x08; ++j)
			currentFile.filename[k++] = sectors[currentSector][j];
		
		k = 0;
		for (int j = i + 0x08; j < i + 0x0B; ++j)
			currentFile.extension[k++] = sectors[currentSector][j];

		//FLAGS
		char flags = sectors[currentSector][i + 0x0B];
		if ((flags & FileAttributes::READ_ONLY) == FileAttributes::READ_ONLY)
			currentFile.flagReadOnly = true;
		if ((flags & FileAttributes::HIDDEN) == FileAttributes::HIDDEN)
			currentFile.flagHidden = true;
		if ((flags & FileAttributes::SYSTEM) == FileAttributes::SYSTEM)
			currentFile.flagSystem = true;
		if ((flags & FileAttributes::DIRECTORY) == FileAttributes::DIRECTORY)
			currentFile.flagDirectory = true;

		// CZAS TUTAJ
		short time = sectors[currentSector][i + 0x0C];
		time |= sectors[currentSector][i + 0x0D] << 8;
		currentFile.time.Hour = time >> 11;
		currentFile.time.Minute = time << 5 >> 11;
		currentFile.time.Second = time << 11 >> 11;
		currentFile.time.Second *= 2;

		// DATA TUTAJ
		short date = sectors[currentSector][i + 0x0E];
		date |= sectors[currentSector][i + 0x0F] << 8;
		currentFile.date.Year = date >> 9;
		currentFile.date.Year += 1980;
		currentFile.date.Month = date << 7 >> 13;
		currentFile.date.Day = date << 11 >> 11;

		//SIZE
		int size = sectors[currentSector][i + 0x14] << 24;
		size |= sectors[currentSector][i + 0x13] << 16;
		size |= sectors[currentSector][i + 0x12] << 8;
		size |= sectors[currentSector][i + 0x11];

		dirContent.push_back(currentFile);
		}
	return dirContent;
}

void DriveManager::showSwap()
{
	// Finding a file in a directory
	std::pair<char, short> tempPair;
	try {
		tempPair = findFileAddress("swap");
	}
	catch (std::string error) {
		throw error;
	}
	char workingSector = sectors[tempPair.first][tempPair.second + 0x10];
	
	std::cout << std::endl << " -- SWAP FILE" << std::endl;
	std::cout << " --   0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F" << std::endl;
	std::cout << " --------------------------------------------------------------------" << std::endl;
	for (int i = 0x00; i < 0x200; i += 0x10)
	{
		std::cout.width(3);
		std::cout << std::hex << i << " ";
		for (int j = 0; j < 16; ++j)
		{
			std::cout.width(3);
			std::cout << std::hex << (int)sectors[workingSector][j] << " ";
		}
		std::cout << std::endl;
	}
}