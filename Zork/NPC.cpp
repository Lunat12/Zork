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

void Npc::ChangeState(Object* _playerObj)
{
    Player* _player = dynamic_cast<Player*>(_playerObj);

    switch (state) {
    case DEFAULT:
        currentDialog = *dialogs[0];
        state = ACTIVE;
        break;
    case ACTIVE:
        currentDialog = *dialogs[2];
        Object::SaveObject(GetName(), _player->GetCurrentRoom()->GetName(), _player->GetName());
        state = FOLLOWING;
        cout << GetName() << " now follows you!";
        break;
    case FOLLOWING:
        currentDialog = *dialogs[3];
        Object::SaveObject(GetName(), _player->GetName(), _player->GetCurrentRoom()->GetName());
        state = ACTIVE;
        cout << GetName() << " will be waiting here.";
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
    if (state = DEFAULT) return Trigger(_object, _parent);

    Object* _currentObject = _parent->ValidateObject(_object);

    if (_currentObject != nullptr)
    {
        _parent->DropObject(_object);
        inventory.push_back(_currentObject);
        return true;
    }
    return false;
}
