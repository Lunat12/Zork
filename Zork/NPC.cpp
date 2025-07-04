#include "NPC.h"

Npc::Npc(string _name, string _description, Object* _trigger, vector<string*> _dialogs) : Object(_name, _description)
{
    trigger = _trigger;
    dialogs = _dialogs;
    type = NPC;
    state = DEFAULT;
}

int Npc::getState()
{
    return state;
}

string Npc::getDialog()
{
    return currentDialog;
}

void Npc::changeState()
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

bool Npc::Trigger(string _triggerName)
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
