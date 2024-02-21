#pragma once
#ifndef PLAYHER_H
#define PLAYER_H
#include "Twine.h"
#include "Spool.h"
#include "Item.h"
#include "Room.h"
#include "Spell.h"
#include "Stats.h"

class Player {
public:
	int xCord = 0;
	int yCord = 0;
	Room* currentRoom = nullptr;
	Twine inputTwine;
	Twine name;
	int health;
	Stats s;
	Item** playerInventory;
	Spool spellBook;
	Spell** spells;
	int spellCount;
	Twine validItemCommands[3]{
		"use",
		"look",
		"examine",
	};

	Twine validRoomCommands[5]{
		"search",
		"inspect",
		"open",
		"investigate",
		"turn on",
	};

	Twine validMoveCommands[5]{
		"move",
		"go to",
		"head",
		"go",
		"move to",
	};

	Twine validSpellCommands[5]{
		"cast",
		"summon",
		"look up",
		"check",
		"spell",
	};

	Twine Directions[4]{
		"north",
		"east",
		"south",
		"west",
	};

	

	int numberOfItems = 0;

	Player();
	~Player();

	void CheckForValidCommand(Twine& searchT);
	void AddItem(Item& c);
	void SearchItem(Twine& searchT);
	void MovePlayer(int i);
	void SpellLookUp(Twine searchT);
	void LearnSpell(Spell* sp);
	void CastSpell(Twine searchT);
	void InitPlayer();


};





#endif // !PLAYHER_H
