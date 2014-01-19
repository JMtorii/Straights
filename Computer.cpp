#include "Computer.h"

#include <iostream>
#include <vector>

using namespace std;

Computer::Computer(int num, char type): Player(num, type) {
	//nothing to do here
}

Computer::Computer(int num, char type, int score/*, int addedScore*/, vector<Card> hand2, vector<Card> discards2) : Player(num, type, score/*, addedScore*/, hand2, discards2){
	//nothing to do here
}

void Computer::play(vector<Card>& legalCards, Table& table, Card &card, bool& turnFinished) {
	cout << "Player " << getNumber() << " plays " << card << "." << endl;
	table.insertCardIntoTable(card);
	removeCardFromHand(card);
}

void Computer::discard(int legalCardsSize, Card& card, bool& turnFinished) {
	addCardToDiscards(card);
	removeCardFromHand(card);
	setScore(card.getRank() + 1);
}