#include "Room.h"

Room::Room(string _name, string _description, vector<Object*> _roomObjects, bool _isDark) : Object(_name, _description)
{
	roomObjects = _roomObjects;
	isDark = _isDark;
	type = ROOM;
}

bool Room::IsDark()
{
	return isDark;
}





