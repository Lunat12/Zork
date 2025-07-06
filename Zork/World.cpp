#include "World.h"

World::World()
{
	Spell* mute = new Spell("Mute", "Spell that mutes inconvinient noises.", MUTE);
	Spell* hypnodream = new Spell("Hypnodream", "Spell that puts beasts to sleep.", HYPNODREAM);
	Spell* lumos = new Spell("Lumos", "Spell that creates light.", LUMOS);

	Object* blinds = new Object("Blinds", "Great Hall's iconic red blinds.");
	Object* apple = new Object("Apple", "Golden apple from the school's garden.");
	Object* cauldron = new Object("Cauldron", "Rusty cauldron for potion brewing.");
	Object* mandrake = new Object("Mandrake", "Really noisy plant, commonly used for potion making.");
	Object* coins = new Object("Coins", "This coins were ment to be student's wishes.");
}

Player* World::GetPlayer()
{
	return player;
}
