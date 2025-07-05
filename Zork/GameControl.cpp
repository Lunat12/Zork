#include "GameControl.h"
using namespace std;

GameControl::GameControl(World _world)
{
	//TODO: SEARCH FOR PLAYER IN WORLD

	controls["GO"] = [&](vector<string> _command) -> bool {
		_player->GoNextRoom(directions[_command[1]]);
    };
	controls["STORE"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};
	controls["DROP"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};
	controls["SPEAK"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};
	controls["GIVE"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};
	controls["USE"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};
	controls["ASK"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};
	controls["DROP"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};
	controls["CAST"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};
	controls["FILL"] = [&](vector<string> _command) -> bool {
		cout << "test\n";
		return false;
	};

	directions["NORTH"] = 0;
	directions["SOUTH"] = 1;
	directions["EAST"]  = 2;
	directions["WEST"]  = 3;
	directions["UP"]    = 4;
	directions["DOWN"]  = 5;
}

void GameControl::GetCommand()
{
	string _input;
	getline(cin, _input);

	vector<string> _command = ParseInput(_input);

	if (controls.find(_command[0]) != controls.end()) 
	{
		controls[_command[0]](_command);
	}
	else
	{
		cout << "I don't recognize that command.\n";
	}
		
}

vector<string> GameControl::ParseInput(string _input)
{
	vector<string> _command;

	_input = InputToUpper(_input);
	const char* _iterator = _input.c_str();

	do
	{
		const char* _begin = _iterator;

		while (*_iterator != ' ' && *_iterator)
		{
			
			_iterator++;
		}

		_command.push_back(string(_begin, _iterator));

	} while (0 != *_iterator++);

	return _command;
}

string GameControl::InputToUpper(string _input)
{
	for (char& c : _input) 
	{
		c = (char)toupper(c);
	}

	return _input;
}




