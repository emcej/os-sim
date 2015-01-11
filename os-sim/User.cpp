/*#include "User.h"
#include <time.h>
#include <string>


User::User(std::string name, std::string password)
{
	this->SetName(name);
	this->SetPassword(password);
	this->SetAccountCreationTime();
	//this->_ID = _counter;
	User::_counter++;
}

User::~User()
{
	User::_counter--;
}

std::string User::GetPassword()
{
	return this->_password;
}

void User::SetPassword(std::string password)
{
	this->_password = password;
}

std::string User::GetName()
{
	return this->_name;
}

void User::SetName(std::string name)
{
	this->_name = name;
}

char User::GetPermission()
{
	return this->_permission;
}

void User::SetPermission(char permission)
{
	this->_permission = permission;
}

unsigned int User::GetID()
{
	return this->_ID;
}

void User::SetSessionStartTime()
{
	time_t seconds;
	seconds = time(NULL);

	this->_sessionStartTime = seconds;
}
double User::GetSessionStartTime()
{	
	return this->_sessionStartTime;
}

int User::GetCounter() //??
{
	return this->_counter;
}

void User::SetSessionDurationTime(double sessionStartTime)
{
	time_t seconds;
	seconds = time(NULL);
	seconds -= sessionStartTime;

	this->_sessionDurationTime = seconds;
}
double User::GetSessionDurationTime()
{
	return this->_sessionDurationTime;
}

void User::SetAccountCreationTime()
{
	time_t timer;
	time(&timer);
	char * date = ctime(&timer);

	this->_accountCreationTime = *date;
}
char User::GetAccountCreationTime()
{
	return this->_accountCreationTime;
}
void User::SetLastLogTime()
{
	time_t timer;
	time(&timer);
	char * date = ctime(&timer);

	this->_lastLogTime = *date;
}
char User::GetLastLogTime()
{
	return this->_lastLogTime;
}*/