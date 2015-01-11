/*#include "Shell.h"
#include "User.h"
#include <regex>
#include <string>
#include <iostream>
#include "Dispatcher.h"

using namespace std;


void Shell::CreateFile(std::string filename)
{
	//tworzenie pliku...
}
void Shell::DeleteFile(std::string filename)
{
	//usuwanie pliku
}
void Shell::EnterDir(std::string directory)
{
	//??
}
void Shell::PushProcess(std::string filename)
{
	Dispatcher::pushProcess(filename);
}

void Shell::Parse(std::string cmd)
{
		// TUTAJ ROZBIJASZ NA PARTY STRING I SPRAWDASZ KTORA TO KOMENDA
		// (POSZUKAC I NAPISAC METODE SPLIT DLA STRINGA)
		// SPLIT WZGLEDEM BIALYCH ZNAKOW I PRZECINKA

		// 1 part sprawdzamy dla RULE::Word (command) czy ki chuj
		// if(part1 == "new")
		// {
		// if(parts.size > ilosc wymaganych partow)
		// wypierdol blad SYNTAX ERROR
		// }
		// dla kzdego parta: 
		// part.......(checkif....(..));
		// bo wiesz jaka jest struktura tej komendy

		if (std::regex_match(cmd, regex("run")))
			Dispatcher::run();

		else if (regex_match(cmd, regex("new")))
			NewFile(params);

		else if (regex_match(cmd, regex("add")))
			PushProcess(params);

		else if (regex_match(cmd, regex("del")))
			PushProcess(params);

		else if (regex_match(cmd, regex("cd ")))
			PushProcess(params);
	/*
	std::string cmd = command.substr(0, command.find_first_of(' '));
	*/
	/*if (std::regex_match(command, std::regex("^run&")))
		Dispatcher::run();

	else if (std::regex_match(command, std::regex("^new .*")))
		newFile(std::regex_replace(command, std::regex("^new "), "$2"));

	else if (std::regex_match(command, std::regex("^add .*")))
		pushProcess(command.substr(4, command.length()));

	else if (std::regex_match(command, std::regex("^del .*")))
		deleteFile(command.substr(4, command.length()));

	else if (std::regex_match(command, std::regex("^cd .*")))
		enterDir(command.substr(3, command.length));

}

void Shell::Wait()
{
	std::cout << "Booting up..." << std::endl;
	std::string command;

	while (true)
	{
		std::cout << " > ";
		std::cin >> command;

		Parse(command);
	}
}

bool Shell::CheckIfStringIsValid(std::string command, unsigned int rule)
{
	switch (rule)
	{
	case Shell::Rules::password:
		/*if (REGEX)
			return true;
		else
			return false;
		break;
	case Shell::Rules::name:

		break;
	case Shell::Rules::command:
		break;

	default:
		break;
	}
}*/