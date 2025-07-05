#pragma once
#include "Object.h"
#include "Room.h"
#include "Player.h"
#include "Enemy.h"

enum Spells
{
	CREATE_LIGHT,
	HYPNOS_DREAM,
	MUTE
};

class Spell : public Object
{
public:
	Spell(string _name, string _description, int _spell);

	bool Cast(Object* _objective);

	bool CreateLight(Object* _objective);
	bool HypnosDream(Object* _objective);
	bool Mute(Object* _objective);

private:
	int spell;
};

