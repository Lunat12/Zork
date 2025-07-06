#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Player.h"
#include "Globals.h"
using namespace std;

class GameControl
{
public:
	GameControl(World* _world);

	void GetCommand();
	vector<string> ParseInput(string _input);
	string InputToUpper(string _input);
	string InputToNormalized(string _input);


private:

	map<string, function<bool(vector<string>)>> controls;
	map<string, int> directions;
	Player* player;
	World* world;
};

