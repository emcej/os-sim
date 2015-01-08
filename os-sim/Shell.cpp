#include "Shell.h"

void Shell::newFile(std::string filename)
{

}
void Shell::deleteFile(std::string filename)
{

}

void Shell::enterDir(std::string directory)
{

}

void Shell::pushProcess(std::string filename)
{
	Dispatcher::pushProcess(filename);
}

void Shell::parse(std::string command)
{
	std::string cmd = command.substr(0, command.find_first_of(' '));

	if (cmd == "run")
		Dispatcher::run();
	else if (cmd == "new")
	{
		//CODE HERE
	}
	else if (cmd == "add")
		pushProcess(command.substr(4, command.length()));
	//CODE HERE
}

void Shell::wait()
{
	std::cout << "Booting up..." << std::endl;
	std::string command;

	while (true)
	{
		std::cout << " > ";
		std::cin >> command;

		parse(command);
	}
}