#include "Spell.h"

Spell::Spell(string _name, string _description, int _spell) : Object(_name, _description)
{
    spell = _spell;
    type = SPELL;
}

bool Spell::Cast(Object* _objective)
{
    switch (spell) {
    case CREATE_LIGHT:
        return CreateLight(_objective);
        break;
    case HYPNOS_DREAM:
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
        return true;
    }
    return false;
}

bool Spell::HypnosDream(Object* _objective)
{
    Enemy* _enemy = dynamic_cast<Enemy*>(_objective);

    if (_enemy != nullptr)
    {
        _enemy->makeSleep();
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
        return true;
    }
    return false;
}




