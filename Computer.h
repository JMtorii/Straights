#ifndef _COMPUTER_
#define _COMPUTER_

#include "Player.h"

class Computer: public Player{
public:
	Computer(int, char);
	Computer(int, char, int/*, int*/, std::vector<Card>, std::vector<Card>);
	void play(std::vector<Card>&, Table&, Card &, bool&);
	void discard(int, Card&, bool&);
};

#endif