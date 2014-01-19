#include "Table.h"

#include <iostream>
#include <vector>
using namespace std;

Table::Table () {
	//clear the table vectors
	clubs.clear();
	diamonds.clear();
	hearts.clear();
	spades.clear();
}

void Table::printTableCards(const Suit suit) {
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	int suitTableSize = 0;
	vector<Card> suitTable;

	//depending on the suit, print the respectful suit in the table
	if(suit == 0) {
		cout << "Clubs:";
		suitTableSize = (int) clubs.size();
		suitTable = clubs;
	} else if(suit == 1) {
		cout << "Diamonds:";
		suitTableSize = (int) diamonds.size();
		suitTable = diamonds;
	} else if(suit == 2) {
		cout << "Hearts:";
		suitTableSize = (int) hearts.size();
		suitTable = hearts;
	} else if(suit == 3) {
		cout << "Spades:";
		suitTableSize = (int) spades.size();
		suitTable = spades;
	}

	for(int i = 0; i < suitTableSize; i++){
		cout << " " << ranks[suitTable[i].getRank()];
	}
	
	cout << endl;
}

void Table::insertCardIntoTable(const Card &card) {
	Suit suit = card.getSuit();
	switch (suit) {
		case CLUB:
			clubs.push_back(card);
			sortCards(clubs);
			break;
		case DIAMOND:
			diamonds.push_back(card);
			sortCards(diamonds);
			break;
		case HEART:
			hearts.push_back(card);
			sortCards(hearts);
			break;
		case SPADE:
			spades.push_back(card);
			sortCards(spades);
			break;
		default:
			break;
	}
}

int Table::getTableSize() const{
	//add all vector sizes
	return clubs.size() + diamonds.size() + hearts.size() + spades.size();
}

Card Table::getCardFromTable(const Suit suit, const int index) const {
	//depending on the index and the suit, return to the card
	switch (suit) {
		case CLUB:
			return clubs[index];
			break;
		case DIAMOND:
			return diamonds[index];
			break;
		case HEART:
			return hearts[index];
			break;
		case SPADE:
			return spades[index];
			break;
		default:
			return clubs[index];
			break;
	}
}

int Table::getClubsSize() const {
	return clubs.size();
}

int Table::getDiamondsSize() const {
	return diamonds.size();
}

int Table::getHeartsSize() const {
	return hearts.size();
}

int Table::getSpadesSize() const {
	return spades.size();
}

vector<Card> Table::getClubs() const {
	return clubs;
}

vector<Card> Table::getDiamonds() const {
	return diamonds;
}

vector<Card> Table::getHearts() const {
	return hearts;
}

vector<Card> Table::getSpades() const {
	return spades;
}


void Table::sortCards(vector<Card> &cards) {
	//sort the cards based on the rank from Ace to King
	vector<Card> sorted;
	for(int i = 0; i < RANK_COUNT; i++){
		for(int j = 0; j < (int)cards.size(); j++) {
			if(cards[j].getRank() == i) 
				sorted.push_back(cards[j]);
		}
	}

	cards = sorted;
}

void Table::clear() {
	//clear all of the cards on table
	clubs.clear();
	diamonds.clear();
	hearts.clear();
	spades.clear();
}
