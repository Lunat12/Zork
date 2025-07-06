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

int Exit::GetExitType()
{
	return exitType;
}

bool Exit::Trigger(string _triggerName, Object* _parent)
{
    if (trigger->GetName() == _triggerName)
    {
        isActive = true;
        SaveObject(_triggerName, _parent);
        cout << "You can now go trough " << GetName();
        return true;
    }

    return false;
}

Room* Exit::GetNext()
{
    return next;
}

bool Exit::IsActive()
{
    return isActive;
}
