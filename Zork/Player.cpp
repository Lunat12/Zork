#include "Player.h"

Player::Player(Room* _currentRoom) : Object("Me", "You look exactly as you did this morning.")
{
	currentRoom = _currentRoom;
	type = PC;
	isHearing = true;
}

bool Player::SaveObject(string _object)
{

	Object* _currentObject = currentRoom->ValidateObject(_object);

	if (_currentObject != nullptr)
	{
		currentRoom->DropObject(_object);
		inventory.push_back(_currentObject);
		return true;
	}
	return false;
}

bool Player::SaveObject(string _object, string _parent, string _recipient)
{
	Object* _currentParent;

	if (_parent == "Me") 
	{
		_currentParent = this;
	}
	else 
	{
		_currentParent = ValidateObject(_parent);
	}

	Object* _currentRecipient = currentRoom->ValidateObject(_recipient);

	if (_currentParent != nullptr && _currentRecipient != nullptr)
	{
		return _currentRecipient->SaveObject(_object, _currentParent);
	}
	return false;
}

bool Player::GoNextRoom(int _dir)
{
	Exit* _nextRoom = currentRoom->ValidateExit(_dir);
	if (_nextRoom == nullptr) return false;

	if (_nextRoom->IsActive()) 
	{
		currentRoom = _nextRoom->GetNext();
		return true;
	}
	cout << "This path is inaccessible at the moment.";
	return false;

	
}

void Player::SetMute()
{
	isHearing = false;
}

bool Player::IsHearing()
{
	return isHearing;
}

bool Player::hasItemAllready()
{
	for (size_t i = 0; i < inventory.size(); i++)
	{
		if (inventory[i]->GetType() == ITEM) return true;
	}

	return false;
}

Room* Player::GetCurrentRoom()
{
	return currentRoom;
}
