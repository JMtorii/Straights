#ifndef GAME_H
#define GAME_H

#include "Command.h"
#include "Table.h"
#include "Card.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"

#include <vector>

class Game {
public:
	Game();
	~Game();

	//accessors
	int getCurPlayer() const;									//gets the current player
	std::string getCurPlayerAsString() const;					//gets the current player as a string
	std::vector<Card> getCurPlayerHand() const;					//gets the current player's hand
	std::vector<Card> getLegalPlays(Player *&, Table &);		//return a vector of legal cards
	std::vector<Card> getLegalCards() const;					//gets the legal cards that the current player can play
	std::vector<Card> getTable() const;							//gets the cards on the table
	std::vector<int> getScores() const;							//gets the scores of all of the players
	std::vector<int> getNumDiscards() const;					//gets the number of discarded cards
	std::vector<Card> getP1Discards() const;					//gets player 1's discarded cards
    std::vector<Card> getP2Discards() const;					//gets player 2's discarded cards
    std::vector<Card> getP3Discards() const;					//gets player 3's discarded cards
    std::vector<Card> getP4Discards() const;					//gets player 4's discarded cards
    int getNumTurns() const;									//gets the number of turns left in the round
    std::vector<int> getWinners() const;						//gets the list of winners
    bool isCurPlayerHuman() const;								//determines if the current player is human
    bool isRoundFinished() const;								//determines if the round is finished
   	bool isGameFinished() const;								//determines if the game is finished

    //methods called by the view and the controller
	void startGame(int, std::vector<bool> &);					//starts the entire game
	void resetGame();											//resets the entire game
	void play(Card &);											//plays a card
	void discard(Card &);										//discards a card
	void rage();												//player rages

	//common code and/or methods that work the logic of the game
	void setSeed(int);
	void insertCardIntoDeck(std::vector<Card> &, Card&);		//inserts a card into the deck
	void shuffle(std::vector<Card> &deck);						//shuffles the cards
	void printCards(const std::vector<Card> &);					//prints a vector of cards
	void showDeck(const std::vector<Card> &);					//prints out the deck
	void assignCards();											//assigns the cards in the beginnning of the game to the appropriate players
	void setUpLegalPlays();										//set up the legal cards
	void clearAndContinue();									//in the beginning of each turn, clear necessary variables and continue to the next player
	void computerMoves();										//perform computer moves
    void resetRound();											//reset variables for a new round
    void newRound();											//start a new round
    void gameDone();											//perform necessary logic when game is finished
    
private:
	std::vector<Card> deck;
	std::vector<Card> legalCards;
	std::vector<Player*> player;
	std::vector<int> winners;
	Table table;
	Command cmd;
	Player *newComp;
	int dInput;
	int curPlayer;
	int numTurns;
	int shuffleCount;
	int minScore;
	bool turnFinished;
	bool roundFinished;
	bool gameFinished;
}; 


#endif
