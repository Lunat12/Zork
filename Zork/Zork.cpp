#include <iostream>
#include "Globals.h"
#include "GameControl.h"
using namespace std;

int main()
{
	GameControl gameControl;

	while(!global_end) 
	{
		gameControl.GetCommand();
	}

	//TODO: CALCULATE POINTS

	cout << "Thanks for playing!";
}
