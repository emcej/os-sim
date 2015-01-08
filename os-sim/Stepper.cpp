#include "Stepper.h"

Stepper::Stepper()
{
}

Stepper::~Stepper()
{
}

void Stepper::Step()
{
	std::cin.ignore();
}

void Stepper::Step(std::string message)
{
	std::cout << message << std::endl;
	std::cin.ignore();
}

void Stepper::Step(char *message)
{
	std::cout << message << std::endl;
	std::cin.ignore();
}