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
	if (command == "run")
		Dispatcher::run();
	else if (command == "new")
	{
		//CODE HERE
	}
	else if (command == "add")
	{
		std::string process;
		std::cout << "  > ";
		std::cin >> process;
		Dispatcher::pushProcess(process);
	}
	else if (command == "dir")
	{

	}
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