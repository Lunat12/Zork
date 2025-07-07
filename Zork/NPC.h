#pragma once
#include <vector>
#include <iostream>
#include "Object.h"
#include "Player.h"
using namespace std;

enum NPCStates 
{
	DEFAULT,
	ACTIVE,
	FOLLOWING
};

class Npc : public Object
{
public:
	Npc(string _name, string _description, Object* _trigger, vector<string*> _dialogs);
	Npc(string _name, string _description, Object* _trigger, vector<string*> _dialogs, vector<Object*> _inventory);

	int GetState();
	string GetTrigger();
	string GetDialog();
	bool Trigger(string _triggerName, Object* _player);
	bool SaveObject(string _object, Object* _parent) override;
	void ChangeState(Object* _player);

private:

	string currentDialog;
	Object* trigger;
	int state;
	vector<string*> dialogs;
};

