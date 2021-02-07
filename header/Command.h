#ifndef __COMMAND_HEADER_INCLUDED__
#define __COMMAND_HEADER_INCLUDED__
#include "Program.h"
#include<iostream>

using namespace std;

class Command
{
private:
	Program* containers;
public:
	Command(Program& conteiner);
	void showCommands();
	void execute(const string& command);
};



#endif // !__COMMAND_HEADER_INCLUDED
