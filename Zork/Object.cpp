#include "Object.h"

Object::Object(string _name, string _description, int _type)
{
	name = _name;
	description = _description;
	type = _type;

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
