#include "NPC.h"

NPC::NPC(string _name, string _description, int _type, Object* _trigger, vector<string*> _dialogs) : Object(_name, _description, _type)
{
    trigger = _trigger;
    dialogs = _dialogs;
}

int NPC::getState()
{
    return state;
}

string NPC::getDialog()
{
    return currentDialog;
}

void NPC::changeState()
{
    switch (state) {
    case DEFAULT:
        currentDialog = *dialogs[0];
        state = ACTIVE;
        break;
    case ACTIVE:
        currentDialog = *dialogs[2];
        state = FOLLOWING;
        break;
    case FOLLOWING:
        currentDialog = *dialogs[3];
        state = ACTIVE;
        break;
 
    }

}

bool NPC::Trigger(string _triggerName)
{
    if (trigger->GetName() == _triggerName)
    {
        changeState();
        inventory.push_back(trigger);
        //TODO: print dialog 1 directly
        return true;
    }

    return false; 
}
