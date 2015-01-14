#include "User.h"

unsigned int User::_counter = 0;
unsigned int User::_IDcounter = 0;

User::User(std::string name, std::string password)
{
	this->SetName(name);
	this->SetPassword(password);
	this->SetAccountCreationTime();
	this->_ID = _IDcounter;
	this->_permission = User::PermissionTypes::ReadWriteUser;
	User::_IDcounter++;
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

std::string User::GetPermissionString()
{
	switch (this->_permission)
	{
	case PermissionTypes::Admin:
		return std::string("Admin");
	case PermissionTypes::ReadUser:
		return std::string("ReadUser");
	case PermissionTypes::ReadWriteUser:
		return std::string("ReadWriteUser");
	case PermissionTypes::Root:
		return std::string("Root");
	default:
		throw std::string("Could not get permission string");
	}
}

unsigned int User::GetID()
{
	return this->_ID;
}

int User::GetCounter()
{
	return User::_counter;
}

void User::SetAccountCreationTime()
{
	time_t ltime;
	char buf[100];
	errno_t err;

	time(&ltime);

	err = ctime_s(buf, 100, &ltime);

	this->_accountCreationTime = buf;
}
std::string User::GetAccountCreationTime()
{
	return this->_accountCreationTime;
}
void User::SetLastLogTime()
{
	time_t ltime;
	char buf[100];
	errno_t err;

	time(&ltime);

	err = ctime_s(buf, 100, &ltime);

	this->_lastLogTime = buf;
}
std::string User::GetLastLogTime()
{
	return this->_lastLogTime;
}

std::string User::ToString()
{
	return std::string("UserID: " + std::to_string(this->_ID) + "\n{\n\tName: " + this->_name + "\n\tPermission: " +
		this->GetPermissionString() + "\n\tCreationTime: " + this->GetAccountCreationTime() + "\tLastLogTime: " +
		this->GetLastLogTime() + "\n}\n");
}