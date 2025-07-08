#include "Globals.h"

bool global_end;
bool global_dead;
bool global_isVerbose;

bool global_mandrakeGiven;
bool global_spellLearned;
bool global_coinsGiven;
bool global_climbedWell;
bool global_sirenDefeated;
bool global_visitedMagicalForest;
bool global_gotUnicorn;

string Globals_ToUpper(string _input)
{
	for (char& c : _input)
	{
		c = (char)toupper(c);
	}

	return _input;
}

string Globals_ToNormalized(string _input)
{
	bool _isFirst = true;

	for (char& c : _input)
	{
		c = _isFirst ? (char)toupper(c) : (char)tolower(c);
		_isFirst = false;
	}

	return _input;
}