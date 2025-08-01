#include "GameControl.h"

GameControl::GameControl(Player* _player)
{
	player = _player;
	isFirstCommand = true;

	controls["GO"] = [&](vector<string> _command) -> bool {

		if (_command.size() == 2) 
		{
			if (directions.find(_command[1]) != directions.end())
			{
				if (player->GetCurrentRoom()->GetName() == "HALL" && directions[_command[1]] == NORTH) 
				{

					cout << "Are you sure you want to go to your room and end your adventure?" << "\n";
					if (player->ValidateObject("UNICORN") == nullptr)
					{
						cout << "You don't have a unicorn yet...\n";
					}
					cout << "<<Type YES or NO.>>\n";
					string _input;
					getline(cin, _input);
					_input = Globals_ToUpper(_input);

					if (_input == "YES")
					{
						global_end = true;
						if (player->ValidateObject("UNICORN")) global_gotUnicorn = true;
							
						return true;
					}
					else if (_input == "NO")
					{
						cout << "You decided to stay in the hall.\n";
						return false;
					}
					cout << "Not even you could make sense of what you said.\n";
					return false;
				}

				if (player->GoNextRoom(directions[_command[1]]))
				{
					Room* _currentRoom = player->GetCurrentRoom();

					if (_currentRoom->GetName() == "UNDERWELL") 
					{
						if (player->IsHearing()) 
						{
							global_dead = true;
							cout << "You hear an eeire melody. It lures you in its direction. You seem to walk for a while until you reach the source of the song. Then you can feel something pulling you from below.\n";
							cout << "YOU DROWNED.\n";
							global_end = true;
							return true;
						}
						
						global_climbedWell = true;
					}

					if (_currentRoom->GetName() == "FOREST")
					{
						global_visitedMagicalForest = true;
					}
					
					if (!global_isVerbose && _currentRoom->IsVisited()) 
					{
						cout << _currentRoom->GetName() + "\n";
						return true;
					}

					PrintExamine(_currentRoom);

					return true;
				}
				cout << "You can't go there.\n";
				return false;
			}
			cout << "You can't go there.\n";
			return false;
		}
		cout << "You cannot do that.\n";
		return false;
    };
	controls["STORE"] = [&](vector<string> _command) -> bool {

		bool _isInInventory;
		if (_command.size() >= 2)
		{

			if (player->GetCurrentRoom()->ValidateObject(_command[1]) != nullptr)
			{
				_isInInventory = false;
			}
			else if (player->ValidateObject(_command[1]) != nullptr)
			{
				_isInInventory = true;
			}
			else
			{
				cout << "You can't find that object.\n";
				return false;
			}

			if (!player->hasItemAllready() && _command.size() == 2)
			{
				if (!_isInInventory)
				{
					Object* _item = player->GetCurrentRoom()->ValidateObject(_command[1]);

					if (_item->GetType() != ITEM || _item->GetName() == "WATER")
					{
						cout << "It might not be a good idea to get that inside your robe.\n";
						return false;
					}
					if (player->SaveObject(_command[1]))
					{
						cout << "You stored " << Globals_ToNormalized(_command[1]) << " in your robe.\n";
						return true;
					}
				}
				else
				{
					cout << "You already got that.\n";
					return false;
				}
			}
			else if (player->hasItemAllready() && _command.size() == 2)
			{
				cout << "You can only fit one item in your robe.\n";
				return false;
			}
			if (_command.size() == 4)
			{
				Object* _container = player->ValidateObject(_command[3]);
				if (_container == nullptr)
				{
					cout << "You can't store an item in an object you don't possess.\n";
					return false;
				}

				if (_container->GetType() == ITEM && _container->IsContainer())
				{
					if (_isInInventory)
					{
						Object* _item = player->ValidateObject(_command[1]);
						if (_item->GetType() != ITEM)
						{
							cout << "It might not be a good idea to get that inside a " << Globals_ToNormalized(_command[3]) << ".\n";
							return false;
						}
						if (player->SaveObject(_command[1], player->GetName(), _command[3]))
						{
							cout << "You stored " << Globals_ToNormalized(_command[1]) << " inside the " << Globals_ToNormalized(_command[3]) << ".\n";
							return true;
						}
					}

					Object* _item = player->GetCurrentRoom()->ValidateObject(_command[1]);
					if (_item->GetType() != ITEM)
					{
						cout << "It might not be a good idea to get that inside a " << Globals_ToNormalized(_command[3]) << ".\n";
						return false;
					}

					if (player->GetCurrentRoom()->GetName() == "POND" && _item->GetName() == "WATER")
					{
						Object* _sirenObj = player->GetCurrentRoom()->ValidateObject("SIREN");
						Enemy* _siren;
						_siren = dynamic_cast<Enemy*>(_sirenObj);

						if (!_siren->IsAsleep())
						{
							cout << "It might not be a good idea to get near the water now.\n";
							return false;
						}
					}

					if (_container->ValidateItem(_item->GetName()) == nullptr) 
					{
						cout << Globals_ToNormalized(_item->GetName()) << " don't seem to fit well inside of " << Globals_ToNormalized(_container->GetName()) << ".\n";
						return false;
					}

					if (player->SaveObject(_command[1], player->GetCurrentRoom()->GetName(), _command[3]))
					{
						cout << "You stored " << Globals_ToNormalized(_command[1]) << " inside the " << Globals_ToNormalized(_command[3]) << ".\n";
						return true;
					}
				}
				cout << "You cannot store items in that.\n";
				return false;
			}
			cout << "You cannot store that.\n";
			return false;
		}
		cout << "You cannot do that.\n";
		return false;
	};
	controls["DROP"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 2) 
		{
			cout << "You cannot do that.\n";
			return false;
		}
		Object* _item = player->ValidateObject(_command[1]);
		if (_item == nullptr) 
		{
			cout << "You don't even have that item.\n";
			return false;
		}
		if (_item->GetType() == ITEM && player->GetCurrentRoom()->SaveObject(_command[1], player))
		{
			cout << "You dropped " << Globals_ToNormalized(_command[1]) << ".\n";
			return true;
		}
		cout << "You cannot drop that.\n";
		return false;
	};
	controls["SPEAK"] = [&](vector<string> _command) -> bool {

		if (_command.size() == 3) 
		{
			Object* _object = player->GetCurrentRoom()->ValidateObject(_command[2]);

			if (_object == nullptr) 
			{
				_object = player->ValidateObject(_command[2]);
			}

			if (_object != nullptr && _object->GetType() == NPC)
			{
				Npc* _npc = dynamic_cast<Npc*>(_object);

				cout << _npc->GetDialog() << "\n";
				if (_npc->GetState() != DEFAULT) 
				{
					cout << "<<Type YES or NO.>>\n";
					string _input;
					getline(cin, _input);
					_input = Globals_ToUpper(_input);

					if (_input == "YES") 
					{
						_npc->ChangeState(player);
						return true;
						
					}
					else if (_input == "NO") 
					{
						cout << Globals_ToNormalized(_npc->GetName()) << " says: Ok!\n";
						return true;
					}
					cout << Globals_ToNormalized(_npc->GetName()) << " could not make sense of what you said.\n";
					return false;
				}
				return true;
			}
			cout << "You cannot talk to" << Globals_ToNormalized(_command[2]) <<".\n";
			return false;
		}
		cout << "Sorry nobody understood you.\n";
		return false;
	};
	controls["GIVE"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 4) 
		{
			cout << "You cannot do that.\n";
			return false;
		}

		Object* _container = player->ValidateObject(_command[3]);
		if (_container == nullptr)
		{
			_container = player->GetCurrentRoom()->ValidateObject(_command[3]);

			if (_container == nullptr)
			{
				cout << "You can't give anything to someone who's not here.\n";
				return false;
			}
		}

		if (_container->GetType() == NPC)
		{
			Npc* _npc;
			_npc = dynamic_cast<Npc*>(_container);
			if (_npc->GetName() == "POTS" && _npc->GetState() != DEFAULT)
			{
				cout << "Pots is not carrying any bag at the moment.\n";
				return false;
			}

			Object* _item = player->ValidateObject(_command[1]);
			if (_item != nullptr) 
			{
				if (_item->GetType() != ITEM)
				{
					cout << "It might not be a good idea to give that to " << Globals_ToNormalized(_command[3]) << ".\n";
					return false;
				}
				if (player->SaveObject(_command[1], player->GetName(), _command[3]))
				{
					cout << "You gave " << Globals_ToNormalized(_command[1]) << " to " << Globals_ToNormalized(_command[3]) << ".\n";

					if (Globals_ToNormalized(_command[1]) == "Mandrake" && Globals_ToNormalized(_command[3]) == "Pots") global_mandrakeGiven = true;
					if (Globals_ToNormalized(_command[1]) == "Coins" && Globals_ToNormalized(_command[3]) == "Henry") global_coinsGiven = true;

					return true;
				}
			}
			cout << "You can't give something you don't have.\n";
			return false;
		}
		cout << "You can't go around giving stuff to things that are not human.\n";
		return false;
	};
	controls["USE"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 4)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		Object* _container = player->GetCurrentRoom()->ValidateObject(_command[3]);
		if (_container == nullptr)
		{
			cout << "You can't use that here.\n";
			return false;
		}

		if (_container->GetType() == EXIT)
		{
			Exit* _exit;
			_exit = dynamic_cast<Exit*>(_container);

			Object* _item = player->ValidateObject(_command[1]);
			if (_item == nullptr)
			{
				if(player->GetInventory()[ITEM].size() > 0) _item = player->GetInventory()[ITEM][0]->ValidateObject(_command[1]);
				
				if (_item == nullptr)
				{
					cout << "You can't use something you don't have.\n";
					return false;
				}
			}

			if (_item->GetType() != ITEM)
			{
				cout << "It might not be a good idea to use that here.\n";
				return false;
			}
			if (_exit->Trigger(_item->GetName(), player))
			{
				cout << "You used " << Globals_ToNormalized(_command[1]) << " at the " << Globals_ToNormalized(_command[3]) << ".\n";
				return true;
			}
			cout << "You can't use that.\n";
			return false;
			
		}
		cout << "You can't use that.\n";
		return false;
	};
	controls["ASK"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 4)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		Object* _parent = player->ValidateObject(_command[1]);
		if (_parent == nullptr)
		{
			_parent = player->GetCurrentRoom()->ValidateObject(_command[1]);

			if (_parent == nullptr)
			{
				cout << "You can't ask someone who's not here to give you anything.\n";
				return false;
			}
		}

		if (_parent->GetType() == NPC)
		{
			Npc* _npc;
			_npc = dynamic_cast<Npc*>(_parent);
			if (_npc->GetTrigger() == _command[3])
			{
				cout << Globals_ToNormalized(_npc->GetName()) << " says: Sorry I need that.\n";
				return false;
			}

			Object* _item = _parent->ValidateObject(_command[3]);
			if (_item != nullptr)
			{
				if (_item->GetType() != ITEM || player->hasItemAllready())
				{
					cout << _parent->GetName() << " says: You cannot carry that.\n";
					return false;
				}
				if (player->Object::SaveObject(_item->GetName(), _parent->GetName()))
				{
					cout << Globals_ToNormalized(_command[1]) << " gave you " << Globals_ToNormalized(_command[3]) << ".\n";
					return true;
				}
				cout << Globals_ToNormalized(_parent->GetName()) << " says: I cannot give you that.\n";
				return false;
			}
			cout << Globals_ToNormalized(_parent->GetName()) << " says: I don't have that.\n";
			return false;
		}
		cout << "You can't ask someone who's not human to give you anything.\n";
		return false;
	};
	controls["CAST"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 4)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		Object* _spellObj = player->ValidateObject(_command[1]);
		if (_spellObj == nullptr)
		{
			for (size_t i = 0; i < player->GetInventory()[NPC].size(); i++)
			{
				_spellObj = player->GetInventory()[NPC][i]->ValidateObject(_command[1]);
				if (_spellObj != nullptr)
				{
					break;
				}
			}

			if (_spellObj == nullptr)
			{
				cout << "Neither you nor your party has that spell.\n";
				return false;
			}	
		}

		if (_spellObj->GetType() == SPELL) 
		{
			Spell* _spell;
			_spell = dynamic_cast<Spell*>(_spellObj);

			Object* _item = player->GetCurrentRoom()->ValidateObject(_command[3]);

			if (_item == nullptr && _command[3] == player->GetCurrentRoom()->GetName()) _item = player->GetCurrentRoom();

			if (_item != nullptr)
			{
				if (_spell->Cast(_item)) 
				{
					if (_item->GetName() == "SIREN") global_sirenDefeated = true;
		
					return true;
				}
			}

			if (_command[3] == "ME" || _command[3] == "PARTY" || _command[3] == "PLAYER" || _command[3] == "NOISE")
			{
				if (_spell->Cast(player))
				{
					return true;
				}
			}

			cout << "The spell didn't work.\n";
			return false;
			
		}
		cout << "That's not any spell you've ever heard of.\n";
		return false;
	};
	controls["VERBOSE"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 1)
		{
			cout << "You cannot do that.\n";
			return false;
		}
		global_isVerbose = true;
		cout << "Verbose mode activated. I will now read full descriptions of rooms.\n";
		return false;
	};
	controls["BRIEF"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 1)
		{
			cout << "You cannot do that.\n";
			return false;
		}
		global_isVerbose = false;
		cout << "Verbose mode deactivated. I will now only give full descriptions of rooms you've never been to.\n";
		return false;
	};
	controls["EXAMINE"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 2)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		Object* _object = player->GetCurrentRoom()->ValidateObject(_command[1]);
		if (_object != nullptr)
		{
			PrintExamine(_object);
			return true;
		}

		_object = player->ValidateObject(_command[1]);
		if (_object != nullptr)
		{
			PrintExamine(_object);
			return true;
		}

		if (directions.find(_command[1]) != directions.end())
		{
			_object = player->GetCurrentRoom()->ValidateExit(directions[_command[1]]);
			if (_object != nullptr)
			{
				PrintExamine(_object);
				return true;
			}
		}

		if (player->GetCurrentRoom()->GetName() == _command[1])
		{
			PrintExamine(player->GetCurrentRoom());
			return true;
		}

		if (player->GetName() == _command[1] || _command[1] == "PLAYER")
		{
			PrintExamine(player);
			return true;
		}

		cout << "You cannot examine that.\n";
		return false;
	};
	controls["INVENTORY"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 1)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		if (player->GetInventory()[ITEM].size() < 1) 
		{
			cout << "Your robe pocket is empty.\n";
			return true;
		}

		cout << "Your robe pocket contains:\n";
		cout << Globals_ToNormalized(player->GetInventory()[ITEM][0]->GetName()) << "\n";
		return true;
	};
	controls["PARTY"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 1)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		if (player->GetInventory()[NPC].size() < 1)
		{
			cout << "Nobody is tagging along.\n";
			return true;
		}

		cout << "Your party:\n";
		for (size_t i = 0; i < player->GetInventory()[NPC].size(); i++)
		{
			cout << Globals_ToNormalized(player->GetInventory()[NPC][i]->GetName()) << "\n";
		}
		return true;
	};
	controls["LEARN"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 2)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		Object* _container = player->GetCurrentRoom()->ValidateObject(_command[1]);

		if (_container != nullptr)
		{
			if (_container->GetType() == SPELL) 
			{
				if (player->SaveObject(_command[1]))
				{
					cout << "You learned " << Globals_ToNormalized(_command[1]) << ".\n";
					global_spellLearned = true;
					return true;
				}
				cout << "You were not able to learn this spell.\n";
				return false;
			}
			cout << "This is not a spell.\n";
			return false;
		}
		cout << "There's no such spell here.\n";
		return false;
	};
	controls["SPELLS"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 1)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		if (player->GetInventory()[SPELL].size() < 1)
		{
			cout << "You're still learning your way around magical stuff, no spells here.\n";
			return true;
		}

		cout << "Your spells:\n";
		for (size_t i = 0; i < player->GetInventory()[SPELL].size(); i++)
		{
			cout << Globals_ToNormalized(player->GetInventory()[SPELL][i]->GetName()) << "\n";
		}
		return true;
	};
	controls["HELP"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 1)
		{
			cout << "You cannot do that.\n";
			return false;
		}

		cout << "COMMANDS:\n";
		cout << "-'GO direction' Use it to go through an exit. Directions can either be:\n";
		cout << "	'NORTH\n";
		cout << "	'SOUTH\n";
		cout << "	'EAST\n";
		cout << "	'WEST\n";
		cout << "	'UP\n";
		cout << "	'DOWN\n";
		cout << "-'STORE item' Use it to store an item in your inventory, you can only carry one. Item corresponds to item name.\n";
		cout << "-'STORE item IN item' Use it to store an item inside another item. Item corresponds to item name.\n";
		cout << "-'DROP item' Use it to drop an item from your inventory. Item corresponds to item name.\n";
		cout << "-'SPEAK TO npc' Use it to talk to an NPC. Npc corresponds to npc name.\n";
		cout << "-'GIVE item TO npc' Use it to give an item to an NPC. Item corresponds to item name. Npc corresponds to npc name.\n";
		cout << "-'USE item ON exit' Use it to use an item on an exit. Item corresponds to item name. Exit corresponds to exit name.\n";
		cout << "-'ASK npc FOR item' Use it to ask an NPC who is following you to give you an item from their inventory. Npc corresponds to npc name. Item corresponds to item name.\n";
		cout << "-'CAST spell ON something' Use it to cast a spell of your own or of your party on something. Spell corresponds to spell name. Something can mean a room, NPC... depending on the spell.\n";
		cout << "-'VERBOSE' Use it to enable long descriptions of all rooms.\n";
		cout << "-'BRIEF' Use it to disable long descriptions of rooms you've already been to, it is active by default.\n";
		cout << "-'EXAMINE something' Use it to get information about almost anything in the game.\n";
		cout << "-'INVENTORY' Use it to see your inventory.\n";
		cout << "-'PARTY' Use it to see your party.\n";
		cout << "-'LEARN spell' Use it to learn a spell from a spellbook. Spell corresponds to spell name.\n";
		cout << "-'SPELLS' Use it to see your spells.\n";
		cout << "-'HELP' Use it to get the list of commands and their uses.\n";
		return true;
	};

	directions["NORTH"] = 0;
	directions["SOUTH"] = 1;
	directions["EAST"]  = 2;
	directions["WEST"]  = 3;
	directions["UP"]    = 4;
	directions["DOWN"]  = 5;
}

void GameControl::GetCommand()
{
	if (isFirstCommand)
	{
		vector<string> _command = {
			"EXAMINE",
			"HALL"
		};
		controls[_command[0]](_command);

		isFirstCommand = false;
		return;
	}

	string _input;
	getline(cin, _input);

	vector<string> _command = ParseInput(_input);

	if (controls.find(_command[0]) != controls.end()) 
	{
		controls[_command[0]](_command);
	}
	else
	{
		cout << "I don't recognize that command.\n";
	}
		
}

vector<string> GameControl::ParseInput(string _input)
{
	vector<string> _command;

	_input = Globals_ToUpper(_input);
	const char* _iterator = _input.c_str();

	do
	{
		const char* _begin = _iterator;

		while (*_iterator != ' ' && *_iterator)
		{
			
			_iterator++;
		}

		_command.push_back(string(_begin, _iterator));

	} while (0 != *_iterator++);

	return _command;
}

void GameControl::PrintExamine(Object* _object)
{
	cout << Globals_ToNormalized(_object->GetName()) + "\n";
	
	

	if (_object->GetType() == ROOM) 
	{
		Room* _currentRoom;
		_currentRoom = dynamic_cast<Room*>(_object);

		if (_currentRoom->IsDark()) 
		{
			cout << "It's too dark to see anything in here.\n";
			return;
		} 

		cout << _object->GetDescription() + "\n";

		for (size_t i = 0; i < _object->GetInventory()[ITEM].size(); i++)
		{
			cout << "There's an item here: " << Globals_ToNormalized(_object->GetInventory()[ITEM][i]->GetName()) << "\n";
		}
		for (size_t i = 0; i < _object->GetInventory()[NPC].size(); i++)
		{
			cout << "There's a person here: " << Globals_ToNormalized(_object->GetInventory()[NPC][i]->GetName()) << "\n";
		}
		for (size_t i = 0; i < _object->GetInventory()[ENEMY].size(); i++)
		{
			cout << "There's a " << Globals_ToNormalized(_object->GetInventory()[ENEMY][i]->GetName()) << " here.\n";
		}
		for (size_t i = 0; i < _object->GetInventory()[SPELL].size(); i++)
		{
			cout << "There's a spellbook titled: " << Globals_ToNormalized(_object->GetInventory()[SPELL][i]->GetName()) << " here.\n";
		}

		cout << "Exits:\n";
		for (size_t i = 0; i < _object->GetInventory()[EXIT].size(); i++)
		{
			Exit* _currentExit;
			_currentExit = dynamic_cast<Exit*>(_object->GetInventory()[EXIT][i]);

			string _currentExitType;

			for (auto i = directions.begin(); i != directions.end(); i++)
			{
				if (_currentExit->GetExitType() == i->second) 
				{
					_currentExitType = i->first;
					break;
				} 
			}

			cout << "- " << Globals_ToNormalized(_currentExitType) << ": " << Globals_ToNormalized(_currentExit->GetName()) << "\n";
		}

		return;
	}
	
	cout << _object->GetDescription() + "\n";
	
	if(_object->GetType() == ITEM && _object->IsContainer() && _object->GetInventory()[ITEM].size() > 0)
	{
		cout << "Contains:\n";
		for (size_t i = 0; i < _object->GetInventory()[ITEM].size(); i++)
		{
			cout << Globals_ToNormalized(_object->GetInventory()[ITEM][i]->GetName()) << "\n";
		}
	
	}
	else if (_object->GetType() == NPC)
	{
		for (size_t i = 0; i < _object->GetInventory()[ITEM].size(); i++)
		{
			cout << "Carries " << Globals_ToNormalized(_object->GetInventory()[ITEM][i]->GetName()) << " with them.\n";
		}
		for (size_t i = 0; i < _object->GetInventory()[SPELL].size(); i++)
		{
			{
				cout << "Can cast " << Globals_ToNormalized(_object->GetInventory()[SPELL][i]->GetName()) << ".\n";
			}
		}
	}
}




