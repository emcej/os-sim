#include "DriveManager.h"

DriveManager::DriveManager()
{
	for (int i = 0; i < 16; ++i)
		memory[0][i] = 0;
	currentPath = "";
	currentSector = 1;
}
DriveManager::~DriveManager() {}

void DriveManager::enterDir(std::string folder)
{
	currentPath += folder;
	for (int i = 0; i < 111; i += 16)
	{
		char temp[5];
		for (int j = 0; j < 5; ++j)
			temp[j] = memory[currentSector][i + j];
		if (temp == folder)
		{
			currentSector = memory[currentSector][i + 16];
			return;
		}
	}

	throw (std::string)"No such file/directory!";
}
void DriveManager::showDir(std::string path)
{
	for (int i = 0; i < 111; i += 16)
	{
		for (int j = 0; j < 5; ++j)
			std::cout << memory[currentSector][i + j];
		//ZAMIANA DATY, CZASU, WIELKOŒCI
	}
}