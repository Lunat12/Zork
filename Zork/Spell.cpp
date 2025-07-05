#include "Spell.h"

Spell::Spell(string _name, string _description, int _spell, int _objectiveType) : Object(_name, _description)
{
    spell = _spell;
    objectiveType = _objectiveType;
}



bool Spell::Cast(Object* _objective)
{
    if (_objective->GetType() == objectiveType) 
    {
        switch (spell) {
        case CREATE_LIGHT:
            CreateLight(_objective);
            break;
        case HYPNOS_DREAM:
            HypnosDream(_objective);
            break;
        case MUTE:
            Mute(_objective);
            break;
        }

        return true;
    }
    return false;
}

void Spell::CreateLight(Object* _objective)
{
    Room* _room = dynamic_cast<Room*>(_objective);

    _room->SetLight();
}

void Spell::HypnosDream(Object* _objective)
{
    //TODO: Come back after creating anemy class.
}

void Spell::Mute(Object* _objective)
{
    Player* _player = dynamic_cast<Player*>(_objective);

    _player->SetMute();
}




