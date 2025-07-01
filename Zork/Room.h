#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

class Room
{
public:
	Room(string _name, string _description, Room* _exits[6], vector<Item*> _items, vector<Person*> _people, vector<Interactable*> _interactables, bool _dark);

	
	string GetName();
	string GetDescription();
	bool ValidExit(string _exit);
	Item* ValidItem(string _item);
	Person* ValidPeople(string _person);
	bool ValidInteraction(string _interactable);
	void AddToScene(Item* _item);
	void AddToScene(Person* _person);
	void DropFromScene(Item* _item);
	void DropFromScene(Person* _person);

private:
	
	string name;
	string description;
	Room* exits[6];
	vector<Item*> items;
	vector<Person*> people;
	vector<Interactable*> interactables;
	void ActivateInteractable(Interactable* _interactable);
	void Move(Room* _room);
	bool dark;

	map<string, int> exitNames
	{
		{"NORTH", 1},
		{"SOUTH", 2},
		{"EAST", 3},
		{"WEST", 4},
		{"DOWN", 5},
		{"UP", 6}   

	};
};

