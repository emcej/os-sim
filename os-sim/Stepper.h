#pragma once
#include <iostream>
#include <string>

class Stepper
{
public:
	Stepper();
	~Stepper();

	void Step();
	void Step(std::string message);
	void Step(char *message);
};