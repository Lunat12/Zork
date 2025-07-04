#include "Exit.h"

Exit::Exit(string _name, string _description, int _exitType, Object* _trigger, Room* _next) : Object(_name, _description)
{
	exitType = _exitType;
	trigger = _trigger;
	type = EXIT;
	isActive = false;
    next = _next;
}

Exit::Exit(string _name, string _description, int _exitType, Room* _next) : Object(_name, _description)
{
    exitType = _exitType;
    type = EXIT;
    isActive = true;
    next = _next;
    trigger = nullptr;
}

int Exit::getExitType()
{
	return exitType;
}

bool Exit::Trigger(string _triggerName)
{
    if (trigger->GetName() == _triggerName)
    {
        isActive = true;
        inventory.push_back(trigger);
        //TODO: print mesage of opening?
        return true;
    }

    return false;
}

Room* Exit::GetNext()
{
    return next;
}
