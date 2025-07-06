#pragma once
#include "Player.h"
#include "Spell.h"
#include "NPC.h"
#include "Room.h"
class World
{
public:
	World();
	Player* GetPlayer();
private:
	Player* player;
};

