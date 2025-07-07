#include <iostream>
#include <string>
#include "GameControl.h"
#include "World.h"
using namespace std;

int CalculatePoints()
{
	int _score = 0;

	if (global_mandrakeGiven)
	{
		cout << "You gave the mandrake to Mr.Pots. +5 points\n";
		_score += 5;
	}
	if (global_spellLearned)
	{
		cout << "You learned a spell. + 5 points\n";
		_score += 5;
	}
	if (global_coinsGiven)
	{
		cout << "You gave Henry the coins. + 10 points\n";
		_score += 10;
	}
	if (global_climbedWell)
	{
		cout << "You climbed down the well. + 5 points\n";
		_score += 5;
	}
	if (global_syrenDefeated)
	{
		cout << "You defeated the syren. + 20 points\n";
		_score += 20;
	}
	if (global_visitedMagicalForest)
	{
		cout << "You visited the Magical Forest. + 10 points\n";
		_score += 10;
	}
	if (global_gotUnicorn)
	{
		cout << "You got the unicorn into your room and it's now yours. + 25 points\n";
		_score += 25;
	}

	return _score;
}

int main()
{
	World world;
	GameControl gameControl(world.GetPlayer());

	cout << "WELCOME TO BLACK CAT'S SCHOOL OF MAGIC!\n";
	cout << "You are a student of first year at BLACK CAT'S SCHOOL OF MAGIC!\n";
	cout << "It's holliday seasson and almost all students have returned home for the festivites.\n";
	cout << "You could't get back home due to your family's flying car failure last week, so you're stuck at school with little to nothig to do.\n";
	cout << "You have decided that to pass the time today is the day you get a UNICORN!.\n";

	while(!global_end) 
	{
		gameControl.GetCommand();

		cout << "\n\n";
	}

	if (!global_dead) 
	{
		int score = CalculatePoints();
		cout << "You made " << score << "/80 points.";
	}
	cout << "Thanks for playing!\n";
}


