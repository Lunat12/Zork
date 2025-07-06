#include "Room.h"

Room::Room(string _name, string _description, vector<Object*> _roomObjects, bool _isDark) : Object(_name, _description)
{
	for (size_t i = 0; i < _roomObjects.size(); i++)
	{
		inventory.push_back(_roomObjects[i]);
	}

	isDark = _isDark;
	type = ROOM;
	isVisited = false;
}

bool Room::IsDark()
{
	return isDark;
}

void Room::SetLight()
{
	isDark = false;
}

bool Room::IsVisited()
{
	if (isVisited)
	{
		return true;
	}
	else 
	{
		isVisited = true;
		return false;
	}
	
}

Exit* Room::ValidateExit(int _exitType)
{
	Exit* _currentExit;

	for (size_t i = 0; i < inventory.size(); i++)
	{
		_currentExit = dynamic_cast<Exit*>(inventory[i]);

		if (_currentExit != nullptr) 
		{
			if (_currentExit->GetExitType() == _exitType) 
			{
				return _currentExit;
			}
		}
	}

	return nullptr;
}

void Room::LoadExit(Exit* _exit)
{
	inventory.push_back(_exit);
}





