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
        //TODO: print mesage of opening?
        return true;
    }

    return false;
}

Room* Exit::GetNext()
{
    return next;
}

bool Exit::SaveObject(string _object, Object* _parent)
{
    if (!isActive) return Trigger(_object, _parent);

    Object* _currentObject = _parent->ValidateObject(_object);

    if (_currentObject != nullptr)
    {
        _parent->DropObject(_object);
        inventory.push_back(_currentObject);
        return true;
    }
    return false;
}

bool Exit::IsActive()
{
    return isActive;
}
