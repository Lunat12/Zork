#include "World.h"

World::World()
{
	Spell* mute       = new Spell("Mute", "Spell that mutes inconvenient noises.", MUTE);
	Spell* hypnodream = new Spell("Hypnodream", "Spell that puts beasts to sleep.", HYPNODREAM);
	Spell* lumos      = new Spell("Lumos", "Spell that creates light.", LUMOS);

	Object* blinds   = new Object("Blinds", "Great Hall's iconic red blinds. They're huge and seem pretty sturdy.");
	Object* apple    = new Object("Apple", "Golden apple from the school's garden.");
	Object* mandrake = new Object("Mandrake", "Really noisy plant, commonly used for potion making.");
	Object* coins    = new Object("Coins", "These coins were meant to be students's wishes.");
	Object* water    = new Object("Water", "This water seems to be sacred.");

	vector<Object*> cauldronPosibles = {
		water
	};

	Object* cauldron = new Object("Cauldron", "Rusty cauldron for potion brewing.", true, cauldronPosibles);

	vector<string*> henryDialogs = {
		new string("Henry says: Sight... I cannot believe those dudes from fourth grade took my wallet before leaving... What am I supposed to do now?"),
		new string("Henry says: Thank you so much. Where did you get this? Right! Don't ask... Anyway, if you need me for anything, just say it and I'll help you."),
		new string("Henry says: Do you want me to follow you now?"),
		new string("Henry says: Do you want me to wait here?")
	};

	vector<string*> teacherDialogs = {
		new string("Pots says: So you're looking for unicorns today? Mmm... That's a tricky subject, you should be able to attract one whith an apple, but you'll need to bring Sacred Water to be allowed into the Magical Forest. The apple should be easy enough to get from the garden, but I don't know about the Sacred Water. Anyway, have fun on your quest, and if you get across a mandrake, would you be so kind as to bring it to me?"),
		new string("Pots says: Thank you so much. You took this from Mrs.Green's Greenhouse? Nicely done, it probably would have starved anyway waiting for Mrs.Green to get back. If you need help on your quest now, I'll be happy to help."),
		new string("Pots says: Do you want me to follow you now?"),
		new string("Pots says: Do you want me to wait here?")
	};

	vector<string*> unicornDialogs = {
		new string("Unicorn says: *Horse noises*"),
		new string("Unicorn says: *Happy horse noises*"),
		new string("Unicorn says: Do you want me to follow you now? *brrr*"),
		new string("Unicorn says: Do you want me to wait here? *brrr*")
	};

	vector<Object*> potsInventory = {
		hypnodream
	};

	Npc* pots    = new Npc("Pots", "Mr.Pots is your potions teacher, but he also knows his way around magic.", mandrake, teacherDialogs, potsInventory);
	Npc* henry   = new Npc("Henry", "Your classmate, he's stuck here with you during the holiday. Always goes around with a huge bag.", coins, henryDialogs);
	Npc* unicorn = new Npc("Unicorn", "Beautiful unicorn with hair the colors of the rainbow.", apple, unicornDialogs);

	Enemy* siren = new Enemy("Siren", "A woman with a bird body awaits, seated on the rock in the middle of the pond, sings a strange song.");

	vector<Object*> hallObjects = {
		henry,
		blinds
	};

	vector<Object*> gardenObjects = {
		apple
	};

	vector<Object*> classObjects = {
		cauldron,
		pots
	};

	vector<Object*> forestObjects = {
		unicorn
	};

	vector<Object*> greenhouseObjects = {
		mute,
		mandrake
	};

	vector<Object*> wellObjects = {
		coins
	};

	vector<Object*> pondObjects = {
		siren,
		water
	};

	Room* hall        = new Room("Hall", "Great Hall of Black Cat's School, here you have conferences and dine.", hallObjects, false);
	Room* garden      = new Room("Garden", "The school's garden is a peaceful place.", gardenObjects, false);
	Room* potionClass = new Room("Class", "This is your potions class, here you learn all about brewing magical concoctions.", classObjects, false);
	Room* forest      = new Room("Forest", "This is your first time in the magical forest, and it is indeed magical.", forestObjects, false);
	Room* greenhouse  = new Room("Greenhouse", "This is the greenhouse, you will be taking gardening class with Mrs.Green here starting next year.", greenhouseObjects, false);
	Room* underwell   = new Room("Underwell", "Small cavity below the well.", wellObjects, true);
	Room* pond        = new Room("Pond", "Cavern with a huge pond in the middle.", pondObjects, true);

	//HALL
	Exit* room = new Exit("Door", "Door to the dorms.", NORTH, NULL);
	Exit* hallToGarden = new Exit("Terrace", "You can see the garden past it.", EAST, garden);

	hall->LoadExit(room);
	hall->LoadExit(hallToGarden);

	//GARDEN
	Exit* gardenToHall = new Exit("Terrace", "You can see the Great Hall past it.", WEST, hall);
	Exit* gardenToClass = new Exit("Building", "Northern building.", NORTH , potionClass);
	Exit* gardenToForest = new Exit("Vines", "Huge vines that guard the entrance to the magical forest.", EAST, water, forest);
	Exit* gardenToGreenhouse = new Exit("Shaft", "Small glass cabin.", SOUTH, greenhouse);
	Exit* gardenToUnderWell = new Exit("Well", "Classical water well not featuring any bucket or pulley system, you could tie something to get down there. You believe you can hear faint eeire sounds coming from below.", DOWN, blinds, underwell);

	garden->LoadExit(gardenToHall);
	garden->LoadExit(gardenToClass);
	garden->LoadExit(gardenToForest);
	garden->LoadExit(gardenToGreenhouse);
	garden->LoadExit(gardenToUnderWell);


	//POTION CLASS
	Exit* classToGarden = new Exit("Door", "Standard wooden door.", SOUTH, garden);

	potionClass->LoadExit(classToGarden);

	//FOREST
	Exit* forestToGarden = new Exit("Vines", "Huge vines that guard the entrance to the magical forest.", WEST, garden);

	forest->LoadExit(forestToGarden);

	//GREENHOUSE
	Exit* greenhouseToGarden = new Exit("Door", "Regular door but featuring flower designs.", NORTH, garden);

	greenhouse->LoadExit(greenhouseToGarden);

	//UNDERWELL
	Exit* underwellToGarden = new Exit("Well", "You can see dim light above you.", UP, garden);
	Exit* underwellToPond = new Exit("Hole", "There's a small opening on the cavern wall.", EAST, pond);

	underwell->LoadExit(underwellToGarden);
	underwell->LoadExit(underwellToPond);

	//POND
	Exit* pondToUnderwell = new Exit("Hole", "There's a small opening on the cavern wall.", WEST, underwell);
	
	pond->LoadExit(pondToUnderwell);


	vector<Object*> playerInventory = {
		lumos
	};
	player = new Player(hall, playerInventory);
}

Player* World::GetPlayer()
{
	return player;
}
