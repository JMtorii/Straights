#ifndef _TABLE_
#define _TABLE_

#include "Card.h"

#include <vector>

class Table{
public:
	Table();
	void printTableCards(const Suit);					//prints the cards on the table
	void insertCardIntoTable(const Card &); 			//inserts a card into a deck
	int getTableSize() const;							//gets the number of cards on the table
	Card getCardFromTable(const Suit, const int) const;	//given an index, return the card
	int getClubsSize() const; 							//gets the number of clubs on the table
	int getDiamondsSize() const;						//gets the number of diamonds on the table
	int getHeartsSize() const;							//gets the number of hearts on the table
	int getSpadesSize() const;							//gets the number of spades on the table
	std::vector<Card> getClubs() const;					//accessor for clubs
	std::vector<Card> getDiamonds() const;				//accessor for diamonds
	std::vector<Card> getHearts() const;				//accessor for hearts
	std::vector<Card> getSpades() const;				//accessor for spades
	void clear();										//deletes all the vectors

private:
	std::vector<Card> clubs;
	std::vector<Card> diamonds; 
	std::vector<Card> hearts;
	std::vector<Card> spades;
	void sortCards(std::vector<Card> &);
};



#endif