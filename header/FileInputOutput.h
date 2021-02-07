#ifndef __FILEINPUTOUTPUT_HEADER_INCLUDED__
#define __FILEINPUTOUTPUT_HEADER_INCLUDED__
#include <fstream>
#include <string>
#include <iostream>
#include "Program.h"
using namespace std;

class FileInputOutput
{
private:
	ifstream reading_file;
	ofstream writing_file;
public:
	bool input(Program& Container);
	bool output(Program& Container);
};
#endif // !__INPUTOUTPUT_HEADER_INCLUDED__

