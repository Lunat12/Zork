#include "Object.h"

Object::Object(string _name, string _description)
{
	name = _name;
	description = _description;
	type = ITEM;
	isContainer = true;
}

Object::Object(string _name, string _description, bool _isContainer)
{
	name = _name;
	description = _description;
	type = ITEM;
	isContainer = _isContainer;
}

Object::Object(string _name, string _description, bool _isContainer, vector<Object*> _positbleItems)
{
	name = _name;
	description = _description;
	type = ITEM;
	isContainer = _isContainer;
	positbleItems = _positbleItems;
}

string Object::GetName()
{
	return Globals_ToUpper(name);
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
	Object* _currentObject = nullptr;

	if (_currentParent != nullptr) 
	{
		_currentObject = _currentParent->ValidateObject(_object);
	}

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

		string _name = inventory[i]->name;
		_name = Globals_ToUpper(_name);

		if (_name == _object) 
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
		string _name = inventory[i]->name;
		_name = Globals_ToUpper(_name);

		if (_name == _object)
		{
			return inventory[i];
		}
	}
	return nullptr;
}

Object* Object::ValidateItem(string _object)
{
	for (size_t i = 0; i < positbleItems.size(); i++)
	{
		string _name = positbleItems[i]->name;
		_name = Globals_ToUpper(_name);

		if (_name == _object)
		{
			return positbleItems[i];
		}
	}
	return nullptr;
}

map<int, vector<Object*>> Object::GetInventory()
{
	map<int, vector<Object*>> _sortedInventory;

	for (size_t i = 0; i < 7; i++)
	{
		vector<Object*> _newVector;
		_sortedInventory[i] = _newVector;
	}

	for (size_t i = 0; i < inventory.size(); i++)
	{
		_sortedInventory[inventory[i]->GetType()].push_back(inventory[i]);
	}
	return _sortedInventory;
}

bool Object::IsContainer()
{
	return isContainer;
}

void Object::SetDescription(string _description)
{
	description = _description;
}

