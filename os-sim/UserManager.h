/*#pragma once
class UserManager
{
private:
	static User *root;
	std::list<User *> userList;

	User *activeUser;

	User* FindUserHandlerByID(unsigned int ID);
	User* FindUserHandlerByName(std::string name);
public:
	UserManager();
	~UserManager();

	void CreateUser(std::string name, std::string password);
	void DeleteUser(unsigned int ID);

	bool DoesUserExist(unsigned int ID);
	bool DoesUserExist(std::string name);

	unsigned int GetCurrentUserID();

	void LogIn(std::string name, std::string password);

	void ChangeUserName(std::string name, std::string newName);

	//DONE
	void ShowUsersList();
	void ChangeUserPassword(
		std::string name,
		std::string currentPassword,
		std::string newPassword); // jak root to nie podawaj starego hasla tylko wyjebane
	void ChangeUserPermissions(
		std::string name,
		char newPermission);
	char GetUserPermissions(std::string name);
	std::string GetUserName(unsigned int ID);
	unsigned int GetUserID(std::string name);
	std::string GetCurrentUserName(); // z active

	double GetSessionStartTime();
	double GetSessionDurationTime();
	char GetAccountCreationTime();
	char GetLastLogTime();

	void ShowFullUsersList();

	// TODO:


};*/