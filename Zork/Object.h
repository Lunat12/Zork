#pragma once
#include <string>
#include <vector>
#include <map>
#include "Globals.h"
using namespace std;

enum ObjectTypes
{
	ROOM,
	PC,
	NPC,
	ITEM,
	ENEMY,
	EXIT,
	SPELL
};

class Object
{
public:
	Object(string _name, string _description);
	Object(string _name, string _description, bool _isContainer);
	Object(string _name, string _description, bool _isContainer, vector<Object*> _positbleItems);

	string GetName();
	string GetDescription();
	int GetType();
	bool SaveObject(string _object, string _parent);
	virtual bool SaveObject(string _object, Object* _parent);
	virtual bool SaveObject(string _object, string _parent, string _recipient);
	virtual bool SaveObject(string _object);
	bool DropObject(string _object);
	Object* ValidateObject(string _object);
	Object* ValidateItem(string _object);
	map<int, vector<Object*>> GetInventory();
	bool IsContainer();
	void SetDescription(string _description);

protected:
	vector<Object*> inventory;
	int type;

private:
	bool isContainer;
	string name;
	string description;
	vector<Object*> positbleItems;
};

