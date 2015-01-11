#include "File.h"

File::File() {}

File::File(char filename[8], char extension[3], bool flagReadOnly, bool flagHidden, bool flagSystem, bool flagDirectory, Time time, Date date, short size)
	: flagReadOnly(flagReadOnly), flagHidden(flagHidden), flagSystem(flagSystem), flagDirectory(flagDirectory), time(time), date(date), size(size)
{
	strcpy_s(this->filename, filename);
	strcpy_s(this->extension, extension);
}

std::string File::toString()
{
	std::string temp = filename;
	if (flagDirectory)
		temp += "    ";
	else
	{
		temp += ".";
		temp.append(extension);
	}

	temp += "  ";
	temp += (flagReadOnly ? "R" : " ");
	temp += (flagHidden ? "H" : " ");
	temp += (flagSystem ? "S" : " ");
	temp += (flagDirectory ? "D" : " ");

	temp += "  " + std::to_string(date.Day) + "/" + std::to_string(date.Month) + "/" + std::to_string(date.Year);
	temp += "  " + std::to_string(time.Hour) + ":" + std::to_string(time.Minute) + ":" + std::to_string(time.Second);
	
	return temp;
}