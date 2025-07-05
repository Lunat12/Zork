#pragma once
#include <vector>
#include "Object.h"

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

	int getState();
	string getDialog();
	bool Trigger(string _triggerName, Object* _player);
	bool SaveObject(string _object, Object* _parent) override;
	

private:

	string currentDialog;
	Object* trigger;
	int state;
	vector<string*> dialogs;
	void changeState();
};

