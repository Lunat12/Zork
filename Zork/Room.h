#pragma once
#include <vector>
#include "Object.h"

class Room : public Object
{
public:
	Room(string _name, string _description, int _type, vector<Object*> _roomObjects, bool _isDark);

	bool IsDark();
	
private:
	
	vector<Object*> roomObjects;
	bool isDark;

};

