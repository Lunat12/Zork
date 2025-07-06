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
	void SetLight();
	bool IsVisited();
	Exit* ValidateExit(int _exitType);
	void LoadExit(Exit* _exit);
	
private:
	
	bool isDark;
	bool isVisited;

};

