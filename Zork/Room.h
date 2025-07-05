#pragma once
#include <vector>
#include "Object.h"
#include "Exit.h"

class Exit;

class Room : public Object
{
public:
	Room(string _name, string _description, vector<Object*> _roomObjects, bool _isDark);

	bool IsDark();
	bool IsVisited();
	Exit* ValidateExit(int _exitType);
	
private:
	
	bool isDark;
	bool isVisited;

};

