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

bool Object::SaveObject(string _object, string _parent)
{
	Object* _currentParent = ValidateObject(_parent);
	Object* _currentObject = _currentParent->ValidateObject(_object);

	if (_currentObject != nullptr)
	{
		_currentParent->DropObject(_object);
		inventory.push_back(_currentObject);
		return true;
	}
	return false;
}

bool Object::SaveObject(string _object, Object* _parent)
{
	Object* _currentObject = _parent->ValidateObject(_object);

	if (_currentObject != nullptr) 
	{
		_parent->DropObject(_object);
		inventory.push_back(_currentObject);
		return true;
	} 
	return false;
}

bool Object::SaveObject(string _object, string _parent, string _recipient)
{
	Object* _currentRecipient = ValidateObject(_recipient);
	Object* _currentParent = ValidateObject(_parent);

	if (_currentParent != nullptr && _currentRecipient != nullptr)
	{
		return _currentRecipient->SaveObject(_object, _currentParent);
	}
	return false;
}

bool Object::SaveObject(string _object)
{
	return false;
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

Object* Object::ValidateObject(string _object)
{
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (inventory[i]->name == _object)
		{
			return inventory[i];
		}
	}
	return nullptr;
}
