#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Player.h"
#include "Globals.h"
#include "NPC.h"
#include "Spell.h"
using namespace std;

class GameControl
{
public:
	GameControl();

	void GetCommand();
	vector<string> ParseInput(string _input);
	string InputToUpper(string _input);
	string InputToNormalized(string _input);
	void PrintExamine(Object* _object);


private:

	map<string, function<bool(vector<string>)>> controls;
	map<string, int> directions;
	Player* player;
	//World* world;
};

