#pragma once
#include <string>
#include <vector>
#include <map>
#include "Object.h"
using namespace std;

class Room : public Object
{
public:
	Room(string _name, string _description, int _type, vector<Object*> _roomObjects, bool _isDark);

	bool IsDark();
	
private:
	
	vector<Object*> roomObjects;
	bool isDark;

};

