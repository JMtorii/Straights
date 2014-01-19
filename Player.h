#ifndef _PLAYER_
#define _PLAYER_

#include "Table.h"

#include <vector>

const int MAX_PLAYERS = 4;
const int MAX_CARDS_PER_PLAYER = 13;
const int MAX_TURNS = 13;
const int POINTS_TO_WIN = 80;

class Player{
public:
	Player(int, char);
	Player(int, char, int/*, int*/, std::vector<Card>, std::vector<Card>); //special constructor for ragequit
	virtual void play(std::vector<Card>&, Table&, Card&, bool&);	//plays a card from the hand
	virtual void discard(int, Card&, bool&);	//discards a card from the hand
	void setNumber(const int);					//sets the player id/number
	void setType(const char);					//sets the player type
	void setScore(const int);					//sets the player's score
	//void setAddedScore(const int);				//sets the player's score for the round
	void addCardToHand(const Card &);			//adds a card to the player's hand
	void addCardToDiscards(const Card &);		//adds a card to the player's discard collection
	int getNumber() const;						//accessor for player's number
	char getType() const;						//accessor for player's type
	int getScore() const;						//accessor for player's score
	//int getAddedScore() const;					//accessor for player's score for the round
	std::vector<Card> getHand() const;			//returns the collection of cards in the player's hand
	Card getCardFromHand(int) const;			//gets a card from the hand based on the index
	int getHandSize() const;					//gets the number of cards in the hand
	std::vector<Card> getDiscards() const;		//gets the collection of discarded cards 
	void removeCardFromHand(const Card &);		//removes a card from the hand
	bool isLegal(const std::vector<Card> &, const Card &);	//determines if a card is legal
	void clear();								//clears the player's hand and discards

private:
	int number_;
	char type_;
	int score_;
	//int addedScore_;
	std::vector<Card> hand;
	std::vector<Card> discards;
	
};


#endif