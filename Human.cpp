#include "Human.h"

#include <iostream>
#include <vector>

using namespace std;

Human::Human(int num, char type): Player(num, type) {
	//nothing to do here
}

Human::Human(int num, char type, int score/*, int addedScore*/, vector<Card> hand2, vector<Card> discards2): Player(num, type, score/*, addedScore*/, hand2, discards2){
	//nothing to do here
}

void Human::play(vector<Card>& legalCards, Table& table, Card &card, bool& turnFinished) {
	if(isLegal(legalCards, card)) {
		cout << "Player " << getNumber() << " plays " << card << "." << endl;
		table.insertCardIntoTable(card);
		removeCardFromHand(card);
		turnFinished = true;

	} else {
		cout << "This is not a legal play." << endl;
	}
}

void Human::discard(int legalCardsSize, Card& card, bool& turnFinished) {
	if(legalCardsSize == 0) {
		cout << "Player " << getNumber() << " discards " << card << "." << endl;
		addCardToDiscards(card);
		removeCardFromHand(card);
		setScore(card.getRank() + 1);
		turnFinished = true;

	} else {
		cout << "You have a legal play. You may not discard." << endl;
	}
}