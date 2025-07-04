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
	Object(string _name, string _description);

	string GetName();
	string GetDescription();
	int GetType();
	void SaveObject(Object* _object);
	bool DropObject(string _object);

protected:
	vector<Object*> inventory;
	int type;

private:

	string name;
	string description;
	

};

