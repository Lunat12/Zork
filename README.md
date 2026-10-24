# Black Cat's School of Magic

A C++ console-based text adventure inspired by the original *Zork*, developed as an entrance assessment for my Master's in Programming for AAA Video Games.

The assignment was to create a Zork-style game and include an original gameplay mechanic to demonstrate our C++ programming skills. I chose to set my adventure in a magical school and developed a companion system as its original mechanic.

## About the Game

Explore a magical school and its surroundings, interact with characters, collect items and solve puzzles. The main objective is to find a unicorn and complete the adventure. Players can earn up to **80 points** by examining their surroundings and completing interactions along the way.

## Gameplay

The game is played through text commands entered into the console. Alongside exploring rooms, examining objects and managing an inventory, the **companion system** lets players recruit NPCs to follow them, carry items and help overcome obstacles with their abilities.

Players can also learn and cast spells to interact with the environment and solve puzzles.

## How to Play

A downloadable Windows version is available under [GitHub Releases](https://github.com/Lunat12/Zork/releases/tag/Game).

Download `NataliaMuniz_Zork.zip`, extract its contents and run the `.exe` file.

The repository also contains the C++ source code and Visual Studio solution (`Zork/Zork.sln`).

## Commands
- `GO direction` Use it to go through an exit. Directions can either be:
		NORTH
		SOUTH
		EAST
		WEST
		UP
		DOWN
- `STORE item` Use it to store an item in your inventory, you can only carry one. Item corresponds to item name.
- `STORE item IN item` Use it to store an item inside another item. Item corresponds to item name.
- `DROP item` Use it to drop an item from your inventory. Item corresponds to item name.
- `SPEAK TO npc` Use it to talk to an NPC. Npc corresponds to npc name.
- `GIVE item TO npc` Use it to give an item to an NPC. Item corresponds to item name. Npc corresponds to npc name.
- `USE item ON exit` Use it to use an item on an exit. Item corresponds to item name. Exit corresponds to exit name.
- `ASK npc FOR item` Use it to ask an NPC who is following you to give you an item from their inventory. Npc corresponds to npc name. Item corresponds to item name.
- `CAST spell ON something` Use it to cast a spell of your own or of your party on something. Spell corresponds to spell name. Something can mean a room, NPC... depending on the spell.
- `VERBOSE` Use it to enable long descriptions of all rooms.
- `BRIEF` Use it to disable long descriptions of rooms you've already been to, it is active by default.
- `EXAMINE something` Use it to get information about almost anything in the game.
- `INVENTORY` Use it to see your inventory.
- `PARTY` Use it to see your party.
- `LEARN spell` Use it to learn a spell from a spellbook. Spell corresponds to spell name.
- `SPELLS` Use it to see your spells.
- `HELP` Use it to get the list of commands and their uses.



## Walkthrough — 80/80 Points

<details>
<summary>Show full walkthrough (spoilers)</summary>

This is one possible route to finish with 80 points. Try finding your own path before opening the solution.

Pick up Blinds. `store blinds`

Go to the Garden. `go east`

Use the Blinds as rope at the Well. `use blinds on well`

Go to the Greenhouse. `go south`

Learn the Mute spell. `learn mute`

Pick up the Mandrake. `store mandrake`

Go to the Garden. `go north`

Go to the Potions Class. `go north`

Give the Mandrake to Mr. Pots. `give mandrake to pots`

Talk to Mr. Pots. `speak to pots` 

Tell Mr. Pots to follow you. `yes`

Pick up the Cauldron. `store cauldron`

Go to the Garden. `go south`

Deafen yourself against strong noises. `cast mute on me`

Climb down the Well. `go down`

Leave the Cauldron on the floor. `drop cauldron`

Pick up the Coins. `store coins`

Go to the Garden. `go up`

Got to the Hall. `go west`

Give the Coins to Henry. `give coins to henry`

Talk to Henry. `speak to henry` 

Tell Henry to follow you. `yes`

Go to the Garden. `go east`

Pick up the Apple. `store apple`

Give the Apple to Henry. `give apple to henry`

Climb down the Well. `go down`

Pick up Cauldron. `store cauldron`

Go to the Pond. `go east`

Make Mr. Pots cast the spell Hypnodream on the Siren to put her to sleep. `cast hypnodream on siren`

Pick the Sacred Water with the Cauldron. `store water in cauldron`

Go to back trough the hole. `go west`

Go to the Garden. `go up`

Use the Sacred Water to unlock the forest. `use water on vines`

Go to the Magical Forest. `go east`

Give the Cauldron to Henry. `give cauldron to henry`

Ask Henry to give you the Apple. `ask henry for apple`

Give the Apple to the Unicorn.  `give apple to unicorn`

Talk to the Unicorn. `speak to unicorn` 

Tell Unicorn to follow you. `yes`

Go to the Garden. `go west`

Go to the Hall. `go west`

Go to the Dorm. `go north`

End the game. `yes`

</details>

## License

Creative Commons Zero v1.0 Universal (CC0-1.0).
