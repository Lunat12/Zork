#pragma once
#include <string>
#include <vector>
using namespace std;

enum ObjectTypes
{
	ROOM,
	PC,
	NPC,
	ITEM,
	ENEMY,
	EXIT
};

class Object
{
public:
	Object(string _name, string _description, int _type);

	string GetName();
	string GetDescription();
	int GetType();
	void SaveObject(Object* _object);
	void DropObject(Object* _object);

protected:
	vector<Object*> inventory;

private:

	string name;
	string description;
	int type;

};

