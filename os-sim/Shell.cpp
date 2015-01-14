#include "Shell.h"

bool Shell::Parse(std::string cmd)
{
	std::vector<std::string> lines = split(cmd, ' ');

	if (CheckIfStringIsValid(lines[0], Shell::Rules::command))
	{
		if (lines[0] == "run")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				Dispatcher::run();
		}
		else if (lines[0] == "help")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				help();
		}
		else if (lines[0] == "exit")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				return true;
		}
		else if (lines[0] == "add")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[0], Shell::Rules::fileName))
					Dispatcher::pushProcess(lines[1]);
				else
					throw std::string("SYNTAX ERROR");
		}

		else if (lines[0] == "del")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[0], Shell::Rules::name))
			Dispatcher::getDriveManager().removeFile(lines[1].c_str());
				else
					throw std::string("SYNTAX ERROR!");
		}
		else if (lines[0] == "cd")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				Dispatcher::getDriveManager().enterFolder(lines[1]);
		}
		else if (lines[0] == "dir")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				Dispatcher::getDriveManager().showFolder();
		}
		else if (lines[0] == "mdir")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				Dispatcher::getDriveManager().createFile(lines[1].c_str());
		}
		else if (lines[0] == "adu")
		{
			if (lines.size() > 3)
				throw std::string("Wrong number of parameters");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::name) && CheckIfStringIsValid(lines[2], Shell::Rules::password))
					userManager.CreateUser(lines[1], lines[2]);
				else
					throw std::string("Wrong name or password syntax!");
		}
		else if (lines[0] == "dlu")
		{
			if (lines.size() > 2)
				throw std::string("Wrong number of parameters");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::number))
					userManager.DeleteUser(stoi(lines[1]));
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "due")
		{
			if (lines.size() > 2)
				throw std::string("Wrong number of parameters");
			else
			{
				if (CheckIfStringIsValid(lines[1], Shell::Rules::number))
					userManager.DoesUserExist(stoi(lines[1]));
				else if (CheckIfStringIsValid(lines[1], Shell::Rules::name))
					userManager.DoesUserExist(lines[1]);
				else
					throw std::string("SYNTAX ERROR");
			}
		}
		else if (lines[0] == "gcui")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.GetCurrentUserID();
		}
		else if (lines[0] == "log")
		{
			if (lines.size() > 3)
				throw std::string("Wrong number of parameters");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::name) && CheckIfStringIsValid(lines[2], Shell::Rules::password))
					userManager.LogIn(lines[1], lines[2]);
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "cun")
		{
			if (lines.size() > 3)
				throw std::string("Wrong number of parameters");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::name) && CheckIfStringIsValid(lines[2], Shell::Rules::name))
					userManager.ChangeUserName(lines[1], lines[2]);
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "sul")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.ShowUsersList();
		}
		else if (lines[0] == "cup")
		{
			if (lines.size() > 4)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::name) && CheckIfStringIsValid(lines[2], Shell::Rules::password) && CheckIfStringIsValid(lines[3], Shell::Rules::password))
					userManager.ChangeUserPassword(lines[1], lines[2], lines[3]);
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "cupr")
		{
			if (lines.size() > 3)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[2], Shell::Rules::name) && CheckIfStringIsValid(lines[3], Shell::Rules::word))
					userManager.ChangeUserPermissions(lines[1], std::stoi(lines[2]));
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "gup")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::name))
					userManager.GetUserPermissions(lines[1]);
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "gun")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::number))
					userManager.GetUserName(std::stoi(lines[1]));
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "guid")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::name))
					userManager.GetUserID(lines[1]);
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "gcun")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.GetCurrentUserName();
		}
		else if (lines[0] == "gsst")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.GetSessionStartTime();
		}
		else if (lines[0] == "gsdt")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.GetSessionDurationTime();
		}
		else if (lines[0] == "gact")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.GetAccountCreationTime();
		}
		else if (lines[0] == "gllt")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.GetLastLogTime();
		}
		else if (lines[0] == "sful")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.ShowFullUsersList();
		}
		else if (lines[0] == "gcun")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				userManager.GetCurrentUserName();
		}

		else if (lines[0] == "ppl")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
					Dispatcher::getProcessManager().PrintCurrentProcess();
		}
		else if (lines[0] == "pcp")
		{
			if (lines.size() > 1)
				throw std::string("SYNTAX ERROR");
			else
				Dispatcher::getProcessManager().PrintCurrentProcess();
		}
		else if (lines[0] == "ppwnu")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::number))
				{
					Dispatcher::getProcessManager().PrintProcessWithNumber(stoi(lines[1]));
				}
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "ppwna")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
				if (CheckIfStringIsValid(lines[1], Shell::Rules::word))
				{
					Dispatcher::getProcessManager().PrintProcessesWithName(lines[1]);
				}
				else
					throw std::string("SYNTAX ERROR");
		}
		else if (lines[0] == "ppws")
		{
			if (lines.size() > 2)
				throw std::string("SYNTAX ERROR");
			else
			{
				if (CheckIfStringIsValid(lines[1], Shell::Rules::number) || CheckIfStringIsValid(lines[1], Shell::Rules::word))
				{
					unsigned char param;
					if (lines[1] == "new" || lines[1] == "NEW" || lines[1] == "0")
					{
						param = (char)0;
					}
					else if (lines[1] == "running" || lines[1] == "RUNNING" || lines[1] == "1")
					{
						param = (char)1;
					}
					else if (lines[1] == "waiting" || lines[1] == "WAITING" || lines[1] == "2")
					{
						param = (char)2;
					}
					else if (lines[1] == "ready" || lines[1] == "READY" || lines[1] == "3")
					{
						param = (char)3;
					}
					else if (lines[1] == "terminated" || lines[1] == "TERMINATED" || lines[1] == "4")
					{
						param = (char)4;
					}
					Dispatcher::getProcessManager().PrintProcessesWithState(param);
				}
			}
		}
		else
			throw std::string("SYNTAX ERROR");
	}
	else if (lines[0] == "ppwp")
	{
		if (lines.size() > 2)
			throw std::string("SYNTAX ERROR");
		else
		{
			if (CheckIfStringIsValid(lines[1], Shell::Rules::number) || CheckIfStringIsValid(lines[1], Shell::Rules::word))
			{
				unsigned char param;
				if (lines[1] == "idle" || lines[1] == "IDLE" || lines[1] == "1")
				{
					param = (char)1;
				}
				else if (lines[1] == "low" || lines[1] == "LOW" || lines[1] == "2")
				{
					param = (char)2;
				}
				else if (lines[1] == "below" || lines[1] == "BELOW" || lines[1] == "3")
				{
					param = (char)3;
				}
				else if (lines[1] == "normal" || lines[1] == "NORMAL" || lines[1] == "4")
				{
					param = (char)4;
				}
				else if (lines[1] == "above" || lines[1] == "ABOVE" || lines[1] == "5")
				{
					param = (char)5;
				}
				else if (lines[1] == "high" || lines[1] == "HIGH" || lines[1] == "6")
				{
					param = (char)6;
				}
				else if (lines[1] == "ultra" || lines[1] == "ULTRA" || lines[1] == "7")
				{
					param = (char)7;
				}
				else if (lines[1] == "max" || lines[1] == "MAX" || lines[1] == "8")
				{
					param = (char)8;
				}
				Dispatcher::getProcessManager().PrintProcessesWithPriority(param);
			}
			else
				throw std::string("SYNTAX ERROR");
		}
	}
	else
		throw std::string("SYNTAX ERROR!");
}

void Shell::Wait()
{
	std::cout << "Booting up..." << std::endl;
	std::string command;

	while (true)
	{
		std::cout << " > ";
		std::cin >> command;
		if (Parse(command) == true)
			return;
	}
}

bool Shell::CheckIfStringIsValid(std::string command, unsigned int rule)
{
	std::vector<std::string> splitedFileName;

	switch (rule)
	{
	case Shell::Rules::password:
		if (command.length() < 8) return false;
		if (std::regex_match(command, std::regex("[a-zA-Z0-9]+")))
			return true;
		else
			return false;
		break;
	case Shell::Rules::name:
		if (command.length() < 4) return false;
		if (std::regex_match(command, std::regex("[a-zA-Z0-9]+")))
			return true;
		else
			return false;
		break;
	case Shell::Rules::command:
		if (command.length() < 1 && command.length() > 4) return false;
		if (std::regex_match(command, std::regex("[a-zA-Z]+")))
			return true;
		else
			return false;
		break;
	case Shell::Rules::fileName:

		if (command.find('.') == -1) throw std::string("Wrong file name syntax");
		splitedFileName = split(command, '.');

		if (splitedFileName[0].length() < 8 &&
			splitedFileName[0].length() > 20 &&
			splitedFileName[1].length() < 1 &&
			splitedFileName[1].length() > 3) return false;

		if (std::regex_match(splitedFileName[0], std::regex("[a-zA-Z0-9]+")) && std::regex_match(splitedFileName[1], std::regex("[a-zA-Z]+")))
			return true;
		else
			return false;

	case Shell::Rules::number:
		if (command.length() < 1) return false;
		if (std::regex_match(command, std::regex("[0-9]+")))
			return true;
		else
			return false;
	case Shell::Rules::word:
		if (command.length() < 1) return false;
		if (std::regex_match(command, std::regex("[a-zA-Z]+")))
			return true;
		else
			return false;
	case Shell::Rules::folderName:
		if (command.length() < 4 && command.length() > 20) return false;
		if (std::regex_match(command, std::regex("[a-zA-Z]+")))
			return true;
		else
			return false;
	default:
		break;
	}
}
Shell::Shell()
{
	/*
	"run",
	"add",
	"del",
	"cd",
	"dir",
	"mdir",
	"adu",
	"dlu",
	"due",
	"gcui",
	"log",
	"cum",
	"sul",
	"cup",
	"cupr",
	"gup",
	"gun",
	"guid",
	"gcum",
	"gsst",
	"gsdt",
	"gact",
	"gllt",
	"sful",
	"gcun",
	"ppl",
	"pcp",
	"ppwnu",
	"ppwna",
	"ppws",
	"exit",
	"help"
	*/

	OrdersDesciobsions.push_back("run	(run the added processes)");
	OrdersDesciobsions.push_back("add  [filename]		(creates a process in current directory)");
	OrdersDesciobsions.push_back("del  [filename]		(delete file)");
	OrdersDesciobsions.push_back("cd   [foldername]		(enters to the folder)");
	OrdersDesciobsions.push_back("dir  [filename]		(shows folder)");
			OrdersDesciobsions.push_back("mdir [filename]        (creates a file)");
			OrdersDesciobsions.push_back("adu  [name] [pasworrd] (create user)");
			OrdersDesciobsions.push_back("dlu  [ID]              (delete user)");
			OrdersDesciobsions.push_back("due  [name or ID]      (returns true if user exists)");
			OrdersDesciobsions.push_back("gcui (prints current user ID)");
			OrdersDesciobsions.push_back("log  [name] [pasworrd]	(log in user)");
			OrdersDesciobsions.push_back("cum  [current name] [new name] (change user name)");
			OrdersDesciobsions.push_back("sul  (prints user list)");
			OrdersDesciobsions.push_back("cup  [name] [current masworrd][pasworrd] (change user password)");
			OrdersDesciobsions.push_back("cupr [name] [permission] (sets user permissions)");
			OrdersDesciobsions.push_back("gup  [name](prints user permissions by name)");
			OrdersDesciobsions.push_back("gun  [id] (get user name by id)");
			OrdersDesciobsions.push_back("guid [name] (prints user ID by name)");
			OrdersDesciobsions.push_back("gcum (prints current user name)");
			OrdersDesciobsions.push_back("gsst (prints session start time)");
			OrdersDesciobsions.push_back("gsdt (prints session duration time)");
			OrdersDesciobsions.push_back("gact (prints accounts creation time)");
			OrdersDesciobsions.push_back("gllt (get last log time)");
			OrdersDesciobsions.push_back("sful (prints ful user list)");
			OrdersDesciobsions.push_back("gcun (prints current user name)");
			OrdersDesciobsions.push_back("ppl  (prints process list)");
			OrdersDesciobsions.push_back("pcp  (prints current process)");
			OrdersDesciobsions.push_back("ppwnu [Number] (prints process by number)");
			OrdersDesciobsions.push_back("ppwna [Name] (prints process by name)");
			OrdersDesciobsions.push_back("ppws [State] (prints list of proceses by state )");
			OrdersDesciobsions.push_back("ppwp [Priority] (prints list of procesess by priority)");
			OrdersDesciobsions.push_back("exit (ends program)");
			OrdersDesciobsions.push_back("help (prints all methods)");

}

void Shell::help()
{
	for (auto i : OrdersDesciobsions)
	{
		std::cout << i << std::endl;
	}
}
