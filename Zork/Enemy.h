#pragma once
#include "Object.h"
class Enemy : public Object
{
public:
	Enemy(string _name, string _description);

	void makeSleep();
	bool IsAsleep();

private:

	bool isAsleep;
};

