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

					cout << _currentRoom->GetName() + "\n";
					if (!isVerbose && _currentRoom->IsVisited()) return true;

					cout << _currentRoom->GetDescription() + "\n";

					for (size_t i = 0; i < _currentRoom->GetInventory()[ITEM].size(); i++)
					{
						cout << "There's an item here: " << _currentRoom->GetInventory()[ITEM][i]->GetName() << "\n";
					}
					for (size_t i = 0; i < _currentRoom->GetInventory()[NPC].size(); i++)
					{
						cout << "There's a person here: " << _currentRoom->GetInventory()[NPC][i]->GetName() << "\n";
					}
					for (size_t i = 0; i < _currentRoom->GetInventory()[ENEMY].size(); i++)
					{
						cout << "There's a " << _currentRoom->GetInventory()[ENEMY][i]->GetName() << " here.\n";
					}

					cout << "Exits:\n";
					for (size_t i = 0; i < _currentRoom->GetInventory()[EXIT].size(); i++)
					{
						Exit* _currentExit;
						_currentExit = dynamic_cast<Exit*>(_currentRoom->GetInventory()[EXIT][i]);
						cout << "-" << _currentExit->GetExitType() << ": " << _currentExit->GetName() << "\n";
					}

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
		cout << "test\n";
		return false;
	};
	controls["VERBOSE"] = [&](vector<string> _command) -> bool {
		isVerbose = true;
		cout << "Verbose mode activated. I will now read full descriptions of rooms.\n";
		return false;
	};
	controls["BRIEF"] = [&](vector<string> _command) -> bool {
		cout << "Verbose mode deactivated. I will now only full descriptions of rooms you've never been to.\n";
		return false;
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




