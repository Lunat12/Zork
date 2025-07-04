#include "Object.h"

Object::Object(string _name, string _description)
{
	name = _name;
	description = _description;
	type = ITEM;

}

string Object::GetName()
{
	return name;
}

string Object::GetDescription()
{
	return description;
}

int Object::GetType()
{
	return type;
}

void Object::SaveObject(Object* _object)
{
	inventory.push_back(_object);
}

bool Object::DropObject(string _object)
{
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (inventory[i]->name == _object) 
		{
			inventory.erase(inventory.begin() + i);
			return true;
		}
	}
	return false;
}
