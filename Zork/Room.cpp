#include "Room.h"

Room::Room(string _name, string _description, int _type, vector<Object*> _roomObjects, bool _isDark) : Object(_name, _description, _type)
{
	roomObjects = _roomObjects;
	isDark = _isDark;
}

bool Room::IsDark()
{
	return isDark;
}





