#pragma once
#include <string>
#include <vector>
using namespace std;

class Room
{
public:
	Room(int id, string name, string description, vector<int> exits, vector<Item> items, vector<Person> people, vector<Interactable> interactables);

	int GetId();
	string GetName();
	string GetDescription();
	bool ValidExit(string _exit);
	bool ValidItem(string _item);
	bool ValidPeople(string _person);
	bool ValidInteraction(string _interactable);
	void AddToScene(Item _item);
	void DropFromScene(string _item);
	void AddToScene(Person _person);
	void DropFromScene(string _person);

private:
	int id;
	string name;
	string description;
	vector<int> exits;
	vector<Item> items;
	vector<Person> people;
	vector<Interactable> interactables;
	void ActivateInteractable(Interactable _interactable);
};

