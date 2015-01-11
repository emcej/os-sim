/*#include "UserManager.h"
#include "User.h"
#include <string>
#include <iostream>
#include <list>

User* UserManager::root = new User("root");

UserManager::UserManager()
{
	userList.push_back(root);
	activeUser = nullptr;
}

UserManager::~UserManager()
{
}

void UserManager::CreateUser(std::string name, std::string password = "")
{
	if (DoesUserExist(name))
			throw std::string("There already is user named: " + name);

	this->userList.push_back(new User(name, password));
}

bool UserManager::DoesUserExist(unsigned int ID)
{
	for (auto i : userList)
	{
		if (i->GetID() == ID)
		{
			return true;
		}
		return false;
	}
}

bool UserManager::DoesUserExist(std::string name)
{
	for (auto i : userList)
	{
		if (i->GetName() == name)
		{
			return true;
		}
		return false;
	}
}

void UserManager::DeleteUser(unsigned int ID)
{
	if (!DoesUserExist(ID))
		throw std::string("There is no user with ID: " + std::to_string(ID));

	std::list<User*>::iterator i = userList.begin();
	while (i != userList.end())
	{
		if ((*i)->GetID() == ID)
			i = userList.erase(i);
		else
			i++;
	}
}

unsigned int UserManager::GetCurrentUserID()
{
	return this->activeUser->GetID();
}

std::string UserManager::GetCurrentUserName()
{
	return this->activeUser->GetName();
}

void UserManager::LogIn(std::string name, std::string password)
{
	if(!this->DoesUserExist(name))
		throw std::string("User with name " + name + " doesnt exist");

	for (auto i : userList)
	{
		if (i->GetName() == name)
		{
			char permissions = FindUserHandlerByName(name)->GetPermission();
			if (permissions == User::PermissionTypes::Admin || permissions == User::PermissionTypes::Root)
			{
				this->activeUser->SetSessionDurationTime(activeUser->GetSessionStartTime());
				this->activeUser = i;
				this->activeUser->SetSessionStartTime();
				this->activeUser->SetLastLogTime();
				break;
			}
			else
			{
				if (i->GetPassword() == password)
				{
					this->activeUser->SetSessionDurationTime(activeUser->GetSessionStartTime());
					this->activeUser = i;
					this->activeUser->SetSessionStartTime();
					this->activeUser->SetLastLogTime();
					break;
				}
				else
					throw std::string("Password incorrect");
			}
		}
	}
}

User* UserManager::FindUserHandlerByID(unsigned int ID)
{
	for (auto i : userList)
	{
		if (i->GetID() == ID)
		{
			return i;
		}
	}
	throw std::string("There in no user with ID: " + std::to_string(ID));
}

User* UserManager::FindUserHandlerByName(std::string name)
{
	for (auto i : userList)
	{
		if (i->GetName() == name)
		{
			return i;
		}
	}
	throw std::string("There in no user with name: " + name);
}

void UserManager::ChangeUserName(std::string currentName, std::string newName)
{
	if (currentName == "root")
		throw std::string("You cant change name of root");

	if (!DoesUserExist(currentName))
		throw std::string("There is no user with name: " + currentName);

	if (DoesUserExist(newName))
		throw std::string("There already is user with name: " + newName);

	User* toChange = FindUserHandlerByName(currentName);
	if (toChange->GetName() == activeUser->GetName())
		toChange->SetName(newName);
	else
	{
		char permissions = activeUser->GetPermission();
		if (permissions == User::PermissionTypes::Admin || permissions == User::PermissionTypes::Root)
			toChange->SetName(newName);
		else
			throw std::string("Active user has no permission to change name of user named: " + currentName);
	}
}

void UserManager::ShowUsersList()
{
	for (auto i : userList)
		std::cout << "  User : " << i->GetName() << std::endl;
}

void UserManager::ShowFullUsersList()
{
		std::cout << "Number of users : " << /*User::GetCounter() << std::endl;
		std::cout << "  User ID : | name : | permission : | Account Creation : | Last log time: | Session duration time : |" << std::endl;
	for (auto i : userList)
	{
		std::cout  << 
			i->GetID, 
			i->GetName, 
			i->GetPermission,
			i->GetAccountCreationTime, 
			i->GetLastLogTime,
			i->GetSessionDurationTime << std::endl;
	}
}
void UserManager::ChangeUserPassword(std::string name, std::string currentPassword, std::string newPassword)
{
	if (!DoesUserExist(name))
		throw std::string("There is no user with name: " + name);

	User* toChange = FindUserHandlerByName(name);
	char permissions = toChange->GetPermission();

	if (permissions != User::PermissionTypes::Admin && permissions != User::PermissionTypes::Root)
		if (toChange->GetName() == activeUser->GetName())
			if (toChange->GetPassword() == currentPassword)
				toChange->SetPassword(newPassword);
			else
				throw std::string("Wrong password!");
		else
			throw std::string("Active user has no permission to change password of user named: " + name);
	else
		toChange->SetPassword(newPassword);
}

void UserManager::ChangeUserPermissions(std::string name, char newPermission)
{
	if (!DoesUserExist(name))
		throw std::string("There is no user with name: " + name);

	if (name == "root")
		throw std::string("The permission of root is unchangeable");

	User* toChange = FindUserHandlerByName(name);

	char permissions = activeUser->GetPermission();

	if (permissions == User::PermissionTypes::Admin || permissions == User::PermissionTypes::Root)
			toChange->SetPermission(newPermission);
	else
		throw std::string("Active user is not allowed to change permission of user named: " + name);
}

char UserManager::GetUserPermissions(std::string name)
{
	if (!DoesUserExist(name))
		throw std::string("There is no user with name: " + name);

	User* toGet = FindUserHandlerByName(name);

	return toGet->GetPermission();
}

std::string UserManager::GetUserName(unsigned int ID)
{
	if (!DoesUserExist(ID))
		throw std::string("There is no user with ID: " + ID);

	User* toGet = FindUserHandlerByID(ID);

	return toGet->GetName();
}

unsigned int UserManager::GetUserID(std::string name)
{
	if (!DoesUserExist(name))
		throw std::string("There is no user with name: " + name);

	User* toGet = FindUserHandlerByName(name);

	return toGet->GetID();
}

double UserManager::GetSessionStartTime()
{
	return activeUser->GetSessionStartTime();
}

double UserManager::GetSessionDurationTime()
{
	return activeUser->GetSessionDurationTime();
}

char UserManager::GetAccountCreationTime()
{
	return activeUser->GetAccountCreationTime();
}

char UserManager::GetLastLogTime()
{
	return activeUser->GetLastLogTime();
}
*/