#include "NPC.h"

Npc::Npc(string _name, string _description, Object* _trigger, vector<string*> _dialogs) : Object(_name, _description)
{
    trigger = _trigger;
    dialogs = _dialogs;
    type = NPC;
    state = DEFAULT;
    currentDialog = *dialogs[0];
}

Npc::Npc(string _name, string _description, Object* _trigger, vector<string*> _dialogs, vector<Object*> _inventory) : Object(_name, _description)
{
    trigger = _trigger;
    dialogs = _dialogs;
    type = NPC;
    state = DEFAULT;
    currentDialog = *dialogs[0];
    inventory = _inventory;
}

int Npc::GetState()
{
    return state;
}

string Npc::GetTrigger()
{
    return trigger->GetName();
}

string Npc::GetDialog()
{
    return currentDialog;
}

void Npc::ChangeState(Object* _playerObj)
{
    Player* _player = dynamic_cast<Player*>(_playerObj);

    switch (state) {
    case DEFAULT:
        currentDialog = *dialogs[2];
        state = ACTIVE;
        break;
    case ACTIVE:
        currentDialog = *dialogs[3];
        _player->SaveObject(GetName());
        state = FOLLOWING;
        cout << Globals_ToNormalized(GetName()) << " now follows you!\n";
        break;
    case FOLLOWING:
        currentDialog = *dialogs[2];
        _player->SaveObject(GetName(), _player->GetName(), _player->GetCurrentRoom()->GetName());
        state = ACTIVE;
        cout << Globals_ToNormalized(GetName()) << " will be waiting here.\n";
        break;
    }
}

bool Npc::Trigger(string _triggerName, Object* _player)
{
    if (trigger->GetName() == _triggerName)
    {
        ChangeState(_player);
        SaveObject(_triggerName, _player);
        cout << *dialogs[1] << "\n";
        return true;
    }

    return false; 
}

bool Npc::SaveObject(string _object, Object* _parent)
{
    if (state == DEFAULT) return Trigger(_object, _parent);

    Object* _currentObject = _parent->ValidateObject(_object);

    if (_currentObject != nullptr)
    {
        _parent->DropObject(_object);
        inventory.push_back(_currentObject);
        return true;
    }
    return false;
}
