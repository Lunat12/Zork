#include "Room.h"

Room::Room(string _name, string _description, Room* _exits[6], vector<Item> _items, vector<Person> _people, vector<Interactable> _interactables, bool _dark)
{
	name = _name;
	description  = _description;
	exits = _exits;
	items = _items;
	people = _people;
	interactables = _interactables;
	dark = _dark;
}

string Room::GetName()
{
	return name;
}

string Room::GetDescription()
{
	return description;
}

bool Room::ValidExit(string _exit)
{	
	if (exitNames.find(_exit) == exitNames.end()) 
	{
		return false;
	}
	else 
	{
		int roomIndex = exitNames[_exit];
		
		if (exits[roomIndex] = nullptr) 
		{
			return false;
		}
		else 
		{
			Move(exits[roomIndex]);
			return true;
		}
	}

	
}

Item* Room::ValidItem(string _item)
{
	for (int i = 0; i < items.size(); i++) {
		if (_item == items[i]->name) {
			return items[i];
		}
	}
	return nullptr;
}

Person* Room::ValidPeople(string _person)
{
	for (int i = 0; i < people.size(); i++) {
		if (_person == people[i]->name) {
			return people[i];
		}
	}
	return nullptr;
}

bool Room::ValidInteraction(string _interactable)
{
	for (int i = 0; i < interactables.size(); i++) {
		if (_interactable == interactables[i]->name) {
			return true;
		}
	}
	return false;
}

void Room::AddToScene(Item* _item)
{
	items.push_back(_item);
}

void Room::AddToScene(Person* _person)
{
	people.push_back(_person);
}

void Room::DropFromScene(Item* _item)
{
	for (int i = 0; i < items.size(); i++) {
		_item = items[i];
	}
}

void Room::DropFromScene(Person* _person)
{
	for (int i = 0; i < items.size(); i++) {
		_person = people[i];
	}
}

void Room::ActivateInteractable(Interactable* _interactable)
{
	//TODO
}

void Room::Move(Room* _room)
{
	//TODO
}



