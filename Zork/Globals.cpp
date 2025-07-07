#include "Globals.h"

string Globals_ToUpper(string _input)
{
	for (char& c : _input)
	{
		c = (char)toupper(c);
	}

	return _input;
}