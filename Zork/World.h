#pragma once
#include "Player.h"
#include "Spell.h"

class World
{
public:
	World();
	Player* GetPlayer();
private:
	Player* player;
};

