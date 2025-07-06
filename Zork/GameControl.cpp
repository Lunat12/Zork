#include "GameControl.h"

GameControl::GameControl()
{
	//TODO: SEARCH FOR PLAYER IN WORLD

	controls["GO"] = [&](vector<string> _command) -> bool {

		if (_command.size() == 2) 
		{
			if (directions.find(_command[1]) != directions.end())
			{
				if (player->GoNextRoom(directions[_command[1]]))
				{
					Room* _currentRoom = player->GetCurrentRoom();
					
					if (!isVerbose && _currentRoom->IsVisited()) 
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

		bool isInInventory;
		if (_command.size() >= 2)
		{
			if (player->GetCurrentRoom()->ValidateObject(_command[1]) != nullptr)
			{
				isInInventory = false;
			}
			else if (player->ValidateObject(_command[1]) != nullptr)
			{
				isInInventory = true;
			}
			else
			{
				cout << "You can't find that object.\n";
				return false;
			}
		}

		if (!player->hasItemAllready() && _command.size() == 2)
		{
			if (!isInInventory)
			{
				if (player->GetCurrentRoom()->ValidateObject(_command[1])->GetType() != ITEM)
				{
					cout << "It might not be a good idea to get that inside your robe.\n";
					return false;
				}
				if (player->SaveObject(_command[1]))
				{
					cout << "You stored " << InputToNormalized(_command[1]) << " in your robe.\n";
					return true;
				}
			}
			else
			{
				cout << "You allready got that.\n";
				return false;
			}
		}
		else if (player->hasItemAllready() && _command.size() == 2) 
		{
			cout << "You can only fit one item in your robe.\n";
			return false;
		}
		if(_command.size() == 4)
		{
			Object* _container = player->ValidateObject(_command[3]);
			if (_container == nullptr) 
			{
				cout << "You can't store an item in an object you don't posses.\n";
				return false;
			}

			if (_container->GetType() == ITEM && _container->IsContainer()) 
			{
				if (isInInventory)
				{
					if (player->ValidateObject(_command[1])->GetType() != ITEM)
					{
						cout << "It might not be a good idea to get that inside a " << InputToNormalized(_command[3]) << ".\n";
						return false;
					}
					if (player->SaveObject(_command[1], player->GetName(), _command[3]))
					{
						cout << "You stored " << InputToNormalized(_command[1]) << " inside the " << InputToNormalized(_command[3]) << ".\n";
						return true;
					}
				}
				if (player->GetCurrentRoom()->ValidateObject(_command[1])->GetType() != ITEM)
				{
					cout << "It might not be a good idea to get that inside a " << InputToNormalized(_command[3]) << ".\n";
					return false;
				}
				if (player->SaveObject(_command[1], player->GetCurrentRoom()->GetName(), _command[3]))
				{
					cout << "You stored " << InputToNormalized(_command[1]) << " inside the " << InputToNormalized(_command[3]) << ".\n";
					return true;
				}
			}
			cout << "You cannot store items in that.\n";
			return false;
		}
		cout << "You cannot store that.\n";
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
			cout << "You dropped " << InputToNormalized(_command[1]) << ".\n";
			return true;
		}
		cout << "You cannot drop that.\n";
		return false;
	};
	controls["SPEAK"] = [&](vector<string> _command) -> bool {

		if (_command.size() == 3) 
		{
			Object* _object = player->GetCurrentRoom()->ValidateObject(_command[2]);
			if (_object != nullptr && _object->GetType() == NPC)
			{
				Npc* _npc = dynamic_cast<Npc*>(_object);

				cout << _npc->getDialog() << "\n";
				if (_npc->getState() != DEFAULT) 
				{
					cout << "<<Type YES or NO.>>\n";
					string _input;
					getline(cin, _input);
					_input = InputToUpper(_input);

					if (_input == "YES") 
					{
						_npc->ChangeState(player);
						return true;
						
					}
					else if (_input == "NO") 
					{
						cout << _npc->GetName() << " says: Ok!";
						return true;
					}
					cout << _npc->GetName() << " could not make sense of what you said.\n";
					return false;
				}
				return true;
			}
			cout << "You cannot talk to" << InputToNormalized(_command[2]) <<"\n";
			return false;
		}
		cout << "Sorry nobody understood you";
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
			Object* _item = player->ValidateObject(_command[1]);
			if (_item != nullptr) 
			{
				if (_item->GetType() != ITEM)
				{
					cout << "It might not be a good idea to give that to " << InputToNormalized(_command[3]) << ".\n";
					return false;
				}
				if (player->SaveObject(_command[1], player->GetName(), _command[3]))
				{
					cout << "You gave " << InputToNormalized(_command[1]) << " to " << InputToNormalized(_command[3]) << ".\n";
					return true;
				}
			}
			cout << "You can't give something you don't have.\n";
			return false;
		}
		cout << "You can't go arround giving stuff to things that are not human.\n";
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
			if (_item != nullptr)
			{
				if (_item->GetType() != ITEM)
				{
					cout << "It might not be a good idea to use that here.\n";
					return false;
				}
				if (_exit->Trigger(_item->GetName(), player))
				{
					cout << "You used " << InputToNormalized(_command[1]) << " at the " << InputToNormalized(_command[3]) << ".\n";
					return true;
				}
			}
			cout << "You can't use something you don't have.\n";
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
			Object* _item = _parent->ValidateObject(_command[3]);
			if (_item != nullptr)
			{
				if (_item->GetType() != ITEM || player->hasItemAllready())
				{
					cout << _parent->GetName() << " says: You can not carry that.\n";
					return false;
				}
				if (player->Object::SaveObject(_item->GetName(), _parent->GetName()))
				{
					cout << InputToNormalized(_command[1]) << " gave you " << InputToNormalized(_command[3]) << ".\n";
					return true;
				}
				cout << _parent->GetName() << " says: I cannot give you that.\n";
				return false;
			}
			cout << _parent->GetName() << " says: I don't have that.\n";
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
				cout << "Neither you or your party have that spell.\n";
				return false;
			}	
		}

		if (_spellObj->GetType() == SPELL) 
		{
			Spell* _spell;
			_spell = dynamic_cast<Spell*>(_spellObj);

			Object* _item = player->GetCurrentRoom()->ValidateObject(_command[3]);
			if (_item != nullptr)
			{
				if (_spell->Cast(_item)) 
				{
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
		cout << "That's not any spell you ever heard of.\n";
		return false;
	};
	controls["VERBOSE"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 1)
		{
			cout << "You cannot do that.\n";
			return false;
		}
		isVerbose = true;
		cout << "Verbose mode activated. I will now read full descriptions of rooms.\n";
		return false;
	};
	controls["BRIEF"] = [&](vector<string> _command) -> bool {
		if (_command.size() != 1)
		{
			cout << "You cannot do that.\n";
			return false;
		}
		cout << "Verbose mode deactivated. I will now only full descriptions of rooms you've never been to.\n";
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

		if (player->GetCurrentRoom()->GetName() == InputToNormalized(_command[1]))
		{
			PrintExamine(player->GetCurrentRoom());
			return true;
		}

		if (player->GetName() == InputToNormalized(_command[1]) || _command[1] == "PLAYER")
		{
			PrintExamine(player);
			return true;
		}

		cout << "You cannot examine that.\n";
		return false;
	};
	controls["IVENTORY"] = [&](vector<string> _command) -> bool {
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
		cout << player->GetInventory()[ITEM][0]->GetName();
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
			cout << "Nobody is tagging allong.\n";
			return true;
		}

		cout << "Your party:\n";
		for (size_t i = 0; i < player->GetInventory()[NPC].size(); i++)
		{
			cout << player->GetInventory()[NPC][i]->GetName() << "\n";
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
		cout << "-'GO directtion' Use it to go trough an exit. Directions can ither be:\n";
		cout << "	'NORTH\n";
		cout << "	'SOUTH\n";
		cout << "	'EAST\n";
		cout << "	'WEST\n";
		cout << "	'UP\n";
		cout << "	'DOWN\n";
		cout << "-'STORE item' Use it to store an item in your inventory, you can only carry one. Item corresponds to item name.\n";
		cout << "-'STORE item IN item' Use it to store an item inside another item. Item corresponds to item name.\n";
		cout << "-'DROP item' Use it drop an item of your inventory. Item corresponds to item name.\n";
		cout << "-'SPEAK TO npc' Use it to talk to an npc. Npc corresponds to npc name.\n";
		cout << "-'GIVE item TO npc' Use it to give an item to an npc. Item corresponds to item name. Npc corresponds to npc name.\n";
		cout << "-'USE item ON exit' Use it to use an item on an exit. Item corresponds to item name. Exit corresponds to exit name.\n";
		cout << "-'ASK npc FOR item' Use it to ask an npc to give you an item of their inventory. Npc corresponds to npc name. Item corresponds to item name.\n";
		cout << "-'CAST spell ON something' Use it to cast an spell of your own or of your party on something. Spell corresponds to spell name. Something can mean a room, npc... depending on the spell.\n";
		cout << "-'VERBOSE' Use it to enables long descriptions of all rooms, is active by default.\n";
		cout << "-'BRIEF' Use it to disables long descriptions of rooms you've allready been to.\n";
		cout << "-'EXAMINE something' Use it to get information of almost anything in the game.\n";
		cout << "-'INVENTORY' Use it to see your inventory.\n";
		cout << "-'PARTY' Use it to see your party.\n";
		cout << "-'HELP' Use it to get the list of commands and its uses.\n";
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

	_input = InputToUpper(_input);
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

string GameControl::InputToUpper(string _input)
{
	for (char& c : _input) 
	{
		c = (char)toupper(c);
	}

	return _input;
}

string GameControl::InputToNormalized(string _input)
{
	bool _isFirst = true;

	for (char& c : _input)
	{
		c = _isFirst ? (char)toupper(c) : (char)tolower(c);
		_isFirst = false;
	}

	return _input;
}

void GameControl::PrintExamine(Object* _object)
{
	cout << _object->GetName() + "\n";
	cout << _object->GetDescription() + "\n";

	if (_object->GetType() == ROOM) 
	{
		for (size_t i = 0; i < _object->GetInventory()[ITEM].size(); i++)
		{
			cout << "There's an item here: " << _object->GetInventory()[ITEM][i]->GetName() << "\n";
		}
		for (size_t i = 0; i < _object->GetInventory()[NPC].size(); i++)
		{
			cout << "There's a person here: " << _object->GetInventory()[NPC][i]->GetName() << "\n";
		}
		for (size_t i = 0; i < _object->GetInventory()[ENEMY].size(); i++)
		{
			cout << "There's a " << _object->GetInventory()[ENEMY][i]->GetName() << " here.\n";
		}

		cout << "Exits:\n";
		for (size_t i = 0; i < _object->GetInventory()[EXIT].size(); i++)
		{
			Exit* _currentExit;
			_currentExit = dynamic_cast<Exit*>(_object->GetInventory()[EXIT][i]);
			cout << "-" << _currentExit->GetExitType() << ": " << _currentExit->GetName() << "\n";
		}
	}
	else if(_object->GetType() == ITEM && _object->IsContainer())
	{
		cout << "Contains:\n";
		for (size_t i = 0; i < _object->GetInventory()[ITEM].size(); i++)
		{
			cout << _object->GetInventory()[ITEM][i]->GetName() << "\n";
		}
	
	}
	else if(_object->GetType() == NPC)
	{
		for (size_t i = 0; i < _object->GetInventory()[ITEM].size(); i++)
		{
			cout << "Carries " << _object->GetInventory()[ITEM][i]->GetName() << " with them.\n";
		}
		for (size_t i = 0; i < _object->GetInventory()[SPELL].size(); i++)
		{
			cout << "Can cast " << _object->GetInventory()[SPELL][i]->GetName() << "\n";
		}
	}
}




