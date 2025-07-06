#pragma once
#include <string>
#include <vector>
#include <map>
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

	string GetName();
	string GetDescription();
	int GetType();
	bool SaveObject(string _object, string _parent);
	virtual bool SaveObject(string _object, Object* _parent);
	virtual bool SaveObject(string _object, string _parent, string _recipient);
	virtual bool SaveObject(string _object);
	bool DropObject(string _object);
	Object* ValidateObject(string _object);
	map<int, vector<Object*>> GetInventory();

protected:
	vector<Object*> inventory;
	int type;

private:

	string name;
	string description;
};

