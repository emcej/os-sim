#pragma once
#include <cstring>
#include <string>

class File
{
public:
	char filename[8];
	char extension[3];
	bool flagReadOnly, flagHidden, flagSystem, flagDirectory;

	struct Time
	{
		char Hour;
		char Minute;
		char Second;
	} time;
	struct Date
	{
		char Day;
		char Month;
		short Year;
	} date;

	short size;

	File();
	File(char filename[8], char extension[3], bool flagReadOnly, bool flagHidden, bool flagSystem, bool flagDirectory, Time time, Date date, short size);

	std::string toString();
};