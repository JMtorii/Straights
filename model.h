#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include "subject.h"
#include "Game.h"

#include <vector>

class Model : public Subject {
public:
	Model();

    //methods called from controller
    void startGame(int, std::vector<bool> &);               //initializes the entire game
    void play(Card &);                                      //plays a card
    void discard(Card &);                                   //discards a card
    void rage();                                            //converts a player to a computer
    void resetRound();                                      //resets all fields for a new round

    //accessors
    int getCurPlayer() const;                               //gets the current player as an integer
    std::string getCurPlayerAsString() const;               //gets the current player as a string
    std::vector<Card> getCurPlayerHand() const;             //gets all of the cards in the hand of the current player
    std::vector<Card> getLegalCards() const;                //gets all legal cards that the current player can play
    int getLegalCardsSize() const;                          //gets the size of all legal cards that the current player can play
    std::vector<Card> getTable() const;                     //gets all cards on the table
    std::vector<std::string> getScores() const;             //gets the scores of all of the players
    std::vector<std::string> getNumDiscards() const;        //gets the number of the discards of each player
    std::string getP1Discards() const;                      //gets the discards of player 1 as a string
    std::string getP2Discards() const;                      //gets the discards of player 2 as a string
    std::string getP3Discards() const;                      //gets the discards of player 3 as a string
    std::string getP4Discards() const;                      //gets the discards of player 4 as a string
    std::string getWinners() const;                         //gets all of the winners as a string for the view to display
    bool isCurPlayerHuman() const;                          //determines if the current player is human
    bool isGameFinished() const;                            //determines if the game is finished
    bool isRoundFinished() const;                           //determines if the round is finished

private:
	Game game;
}; // Model


#endif
