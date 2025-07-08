# Zork
Conversational game based on the game Zork.

The objective of this game is to get all the quest points by the end of the game. How to get the perfect score is hidden until completion and won't show up if the player ends up dead, but it should be easy to get by examining everything and completing the main objective: getting a unicorn.

The game allows for some extra features like having NPCs follow you around, speaking to them, and using their inventory and skills. 

<br/>

## Author:
Natalia Isabel Muñiz Muñoz

<br/>

## Github Repository:
https://github.com/Lunat12/Zork

<br/>

## License:
Creative Commons Zero v1.0 Universal - CC0-1.0

<br/>

## Commands:
- `GO direction` Use it to go through an exit. Directions can either be:
		NORTH
		SOUTH
		EAST;
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

<br/>

## Step By step - How to get 80/80 points:
This is a step by step guide on how to end the game with 80 points the fastest, it is not the only way possible, so feel free to try your own path first.

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
