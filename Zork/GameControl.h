#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
using namespace std;

class GameControl
{
public:
	GameControl();

	void GetCommand();
	vector<string> ParseInput(string _input);
	string InputToUpper(string _input);

private:

	map<string, function<bool(vector<string>)>> controls;

};

