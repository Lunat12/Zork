#pragma once
#include <iostream>
#include "Object.h"
#include "Room.h"
using namespace std;

class Room;

enum ExitTypes
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	UP,
	DOWN
};

class Exit : public Object
{
public:
	Exit(string _name, string _description, int _exitType, Object* _trigger, Room* _next);
	Exit(string _name, string _description, int _exitType, Room* _next);


	int GetExitType();
	bool Trigger(string _triggerName, Object* _parent);
	Room* GetNext();
	bool IsActive();
	

private:

	int exitType;
	Object* trigger;
	bool isActive;
	Room* next;

};

