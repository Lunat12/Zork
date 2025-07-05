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
	Spell(string _name, string _description, int _spell, int _objectiveType);

	bool Cast(Object* _objective);

	void CreateLight(Object* _objective);
	void HypnosDream(Object* _objective);
	void Mute(Object* _objective);

private:
	int spell;
	int objectiveType;
};

