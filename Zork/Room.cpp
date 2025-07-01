#include "Room.h"

Room::Room(int id, string name, string description, vector<int> exits, vector<Item> items, vector<Person> people, vector<Interactable> interactables)
{
}

int Room::GetId()
{
	return 0;
}

string Room::GetName()
{
	return string();
}

string Room::GetDescription()
{
	return string();
}

bool Room::ValidExit(string _exit)
{
	return false;
}

bool Room::ValidItem(string _item)
{
	return false;
}

bool Room::ValidPeople(string _person)
{
	return false;
}

bool Room::ValidInteraction(string _interactable)
{
	return false;
}

void Room::AddToScene(Item _item)
{
}

void Room::DropFromScene(string _item)
{
}

void Room::ActivateInteractable(Interactable _interactable)
{
}

void Room::AddToScene(Person _person)
{
}
