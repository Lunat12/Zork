#pragma once
#include "Object.h"
#include "Room.h"

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


	int getExitType();
	bool Trigger(string _triggerName);
	Room* GetNext();
	

private:

	int exitType;
	Object* trigger;
	bool isActive;
	Room* next;

};

