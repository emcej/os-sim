#pragma once
#include <string>
#include <iostream>

class DriveManager
{
private:
	unsigned char memory[64][128];

	std::string currentPath;
	unsigned char currentSector;

	//ZAMIANA DATY, CZASU I WIELKOŒCI
public:
	DriveManager();
	~DriveManager();

	void enterDir(std::string);
	void showDir(std::string);
};