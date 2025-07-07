#include "Enemy.h"

Enemy::Enemy(string _name, string _description) : Object(_name, _description)
{
	type = ENEMY;
	isAsleep = false;
}

void Enemy::MakeSleep()
{
	isAsleep = true;
}

bool Enemy::IsAsleep()
{
	return isAsleep;
}
