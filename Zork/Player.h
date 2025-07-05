#pragma once
#include "Object.h"
#include "Room.h"

class Player : public Object
{
public:
	Player(Room* _currentRoom);

	bool SaveObject(string _object) override;
	bool SaveObject(string _object, string _parent, string _recipient) override;
	bool GoNextRoom(int _dir);


private:

	Room* currentRoom;
	
};

