#include <iostream>
#include "NPC.h"

int main()
{
	Object gafas = Object("Gafas", "Gafas de miopia.");
	vector<string*> dialogos = {new string("aaaaaaaaaaaaaa"), new string("bbbbbbbbbbbbbbb"), new string("ccccccccccccccccccc"), new string("bbbbbbbbbbbbbbb") };
	Npc pepe = Npc("Pepe", "Se�oro Miope.", &gafas, dialogos);


	cout << pepe.GetType();   
	cout << gafas.GetType();

}
