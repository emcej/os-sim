/*#pragma once

class User
{
private:
	static unsigned int _counter;
	unsigned _ID;
	double _sessionStartTime, _sessionDurationTime;
	char _accountCreationTime, _lastLogTime;
	std::string _name;
	std::string _password;
	char _permission;

public:
	static enum PermissionTypes
	{
		Root,
		Admin,
		ReadWriteUser,
		ReadUser
	};

	User();
	User(std::string name, std::string password = "");
	~User();

	std::string GetPassword();
	void SetPassword(std::string password);

	std::string GetName();
	void SetName(std::string name);

	char GetPermission(); 
	void SetPermission(char permission);

	unsigned int GetID();
	int GetCounter();

	void SetSessionStartTime();
	void SetSessionDurationTime(double sessionStartTime);
	void SetAccountCreationTime();
	void SetLastLogTime();

	double GetSessionStartTime();
	double GetSessionDurationTime();
	char GetAccountCreationTime();
	char GetLastLogTime();
};*/	