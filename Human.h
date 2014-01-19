#ifndef _HUMAN_
#define _HUMAN_

#include "Player.h"
#include "Game.h"

class Human: public Player{
public:
	Human(int, char);
	Human(int, char, int/*, int*/, std::vector<Card>, std::vector<Card>);
	void play(std::vector<Card>&, Table&, Card&, bool&);
	void discard(int, Card&, bool&);
};

#endif