#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Player.h"
#include "NPC.h"
#include "Spell.h"
#include "Globals.h"
using namespace std;

class GameControl
{
public:
	GameControl(Player* _player);

	void GetCommand();
	vector<string> ParseInput(string _input);
	string InputToNormalized(string _input);
	void PrintExamine(Object* _object);


private:

	map<string, function<bool(vector<string>)>> controls;
	map<string, int> directions;
	Player* player;
	bool isFirstCommand;
};

