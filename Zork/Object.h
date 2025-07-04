#pragma once
class Object
{
public:
	Object(string _name, string _description, int type);

	string GetName();
	string GetDescription();
	int GetType();

private:

	string name;
	string description;
	int type;

};

