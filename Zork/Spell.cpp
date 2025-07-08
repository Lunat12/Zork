#include "Spell.h"

Spell::Spell(string _name, string _description, int _spell) : Object(_name, _description)
{
    spell = _spell;
    type = SPELL;
}

bool Spell::Cast(Object* _objective)
{
    switch (spell) {
    case LUMOS:
        return CreateLight(_objective);
        break;
    case HYPNODREAM:
        return HypnosDream(_objective);
        break;
    case MUTE:
        return Mute(_objective);
        break;
    }

    return false;
}

bool Spell::CreateLight(Object* _objective)
{
    Room* _room = dynamic_cast<Room*>(_objective);

    if (_room != nullptr)
    {
        _room->SetLight();
        cout << "You created light in the " << Globals_ToNormalized(_room->GetName()) << ".\n";
        return true;
    }
    return false;
}

bool Spell::HypnosDream(Object* _objective)
{
    Enemy* _enemy = dynamic_cast<Enemy*>(_objective);

    if (_enemy != nullptr)
    {
        _enemy->MakeSleep();
        cout << "The " << Globals_ToNormalized(_enemy->GetName()) << " fell asleep.\n";
        _enemy->SetDescription(_enemy->GetDescription() + " Is sleeping.");
        return true;
    }
    return false;
}

bool Spell::Mute(Object* _objective)
{
    Player* _player = dynamic_cast<Player*>(_objective);

    if (_player != nullptr)
    {
        _player->SetMute();
        cout << "You cannot hear any loud noises anymore.\n";
        return true;
    }
    return false;
}




