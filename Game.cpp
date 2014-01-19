#include "Game.h"

#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;


Game::Game() :numTurns(MAX_TURNS * MAX_PLAYERS), shuffleCount(1), minScore(POINTS_TO_WIN), roundFinished(false), gameFinished(false){
	//nothing to do here
}

Game::~Game() {
	//nothing to do here
}

//-------------------------------------------- ACCESSORS -----------------------------------------------------//

int Game::getCurPlayer() const {
	return curPlayer;
}

string Game::getCurPlayerAsString() const {
	stringstream ss;
	ss << getCurPlayer();
	return ss.str();
}

vector<Card> Game::getCurPlayerHand() const {
	return player[curPlayer-1]->getHand();
}

vector<Card> Game::getLegalPlays(Player *&player, Table& table) {
	vector<Card> legalCards;  //legal cards which will be returned
	vector<Card> bottom;    //cards at the bottom of the table for each suit
	vector<Card> top;     //cards at the top of the table for each suit
	vector<Card> h = player->getHand(); //get the hand
	bool check = false;     //a switch to prevent too many checks

	//put the bottom and top cards in the appropriate vector
	if(table.getClubsSize() > 0) {
		bottom.push_back(table.getCardFromTable(CLUB, 0));
		top.push_back(table.getCardFromTable(CLUB, table.getClubsSize() - 1));
	} 
	if(table.getDiamondsSize() > 0) {
		bottom.push_back(table.getCardFromTable(DIAMOND, 0));
		top.push_back(table.getCardFromTable(DIAMOND, table.getDiamondsSize() - 1));
  	}
  	if(table.getHeartsSize() > 0) {
		bottom.push_back(table.getCardFromTable(HEART, 0));
		top.push_back(table.getCardFromTable(HEART, table.getHeartsSize() - 1));
  	}
  	if(table.getSpadesSize() > 0) {
		bottom.push_back(table.getCardFromTable(SPADE, 0));
		top.push_back(table.getCardFromTable(SPADE, table.getSpadesSize() - 1));
  	}

	//iterate through the hand and compare it to the bottom and top cards of each suit
	for(int i = 0; i < player->getHandSize(); i++) {
		if(h[i].getRank() == SEVEN) {
			legalCards.push_back(h[i]);
		} else {
			check = false;
			//check bottom cards
			for(int j = 0; j < (int)bottom.size(); j++) {
				if(bottom[j].getSuit() == h[i].getSuit() && bottom[j].getRank() - 1 == h[i].getRank() ) {
				  	legalCards.push_back(h[i]);
				  	check = true; //since this card is a legal card, there is no need to do the second check
				  	break;
				}
			}
			if(!check) {
				//check top cards
				for(int j = 0; j < (int)top.size(); j++) {
					if(top[j].getSuit() == h[i].getSuit() && top[j].getRank() + 1 == h[i].getRank()) {
						legalCards.push_back(h[i]);
						break;
				 	}
				}
			}
		}
	}

	return legalCards;
}

vector<Card> Game::getLegalCards() const{
	return legalCards;
}

vector<Card> Game::getTable() const{
	vector<Card>tableVector;
	vector<Card>clubs = table.getClubs();
	vector<Card>diamonds = table.getDiamonds();
	vector<Card>hearts = table.getHearts();
	vector<Card>spades = table.getSpades();

	for(int i = 0; i < (int)table.getClubsSize(); i++)
		tableVector.push_back(clubs[i]);
	for(int i = 0; i < (int)table.getDiamondsSize(); i++)
		tableVector.push_back(diamonds[i]);
	for(int i = 0; i < (int)table.getHeartsSize(); i++)
		tableVector.push_back(hearts[i]);
	for(int i = 0; i < (int)table.getSpadesSize(); i++)
		tableVector.push_back(spades[i]);

	return tableVector;
}

vector<int> Game::getScores() const {
	vector<int> tempScores;
	for(int i = 0; i < MAX_PLAYERS; i++){
		tempScores.push_back(player[i]->getScore());
	}

	return tempScores;
}

vector<int> Game::getNumDiscards() const {
	vector<int> numDiscards;
	for(int i = 0; i < MAX_PLAYERS; i++) {
		numDiscards.push_back((int)player[i]->getDiscards().size());
	}

	return numDiscards;
}

vector<Card> Game::getP1Discards() const {
	return player[0]->getDiscards();
}

vector<Card> Game::getP2Discards() const {
	return player[1]->getDiscards();
}

vector<Card> Game::getP3Discards() const {
	return player[2]->getDiscards();
}

vector<Card> Game::getP4Discards() const {
	return player[3]->getDiscards();
}

int Game::getNumTurns() const {
	return numTurns;
}

vector<int> Game::getWinners() const{
	return winners;
}

bool Game::isCurPlayerHuman() const{
	char type = player[curPlayer-1]->getType();
	if(type == 'h')
		return true;
	else 
		return false;
}

bool Game::isRoundFinished() const {
	return roundFinished;
}

bool Game::isGameFinished() const {
	return gameFinished;
}

//-------------------------------------------- METHODS FROM VIEW/CONTROLLER ----------------------------------------------------//

void Game::startGame(int seed, vector<bool> &results) {
	deck.clear();
	legalCards.clear();
	player.clear();
	winners.clear();
	table.clear();
	numTurns = MAX_TURNS * MAX_PLAYERS;
	shuffleCount = 1;
	minScore = POINTS_TO_WIN;
	roundFinished = false;
	gameFinished = false;


	setSeed(seed);
	
	//assign the players the appropriate values
	for(int i = 0; i < MAX_PLAYERS; i++) {
		Player *p;
		if(results[i])
			p = new Computer(i + 1, 'c');
		else 
			p = new Human(i + 1, 'h');

		player.push_back(p);
	}

	//initialize the deck in proper order 
	for (int i = CLUB; i != SUIT_COUNT; i++) {
		for (int j = ACE; j != RANK_COUNT; j++){
			Card *card = new Card(static_cast<Suit>(i), static_cast<Rank>(j));
			insertCardIntoDeck(deck, *card);

		}
	}

	newRound();
}

void Game::resetGame() {
	deck.clear();
	legalCards.clear();
	player.clear();
	winners.clear();
	table.clear();
	numTurns = MAX_TURNS * MAX_PLAYERS;
	shuffleCount = 1;
	minScore = POINTS_TO_WIN;
	roundFinished = false;
	gameFinished = false;
}

void Game::play(Card &card) {
	player[curPlayer-1]->play(legalCards, table, card, turnFinished);
	clearAndContinue();
}

void Game::discard(Card &card) {
	player[curPlayer-1]->discard(legalCards.size(), card, turnFinished);
	clearAndContinue();
}

void Game::rage() {
	cout << "Player " << curPlayer << " ragequits. A computer will now take over." << endl;
	newComp = new Computer(curPlayer, 'c', player[curPlayer-1]->getScore()/*, player[curPlayer-1]->getAddedScore()*/, player[curPlayer-1]->getHand(), player[curPlayer-1]->getDiscards());

	player[curPlayer - 1] = newComp;
}

//------------------------------------ METHODS RELATED TO LOGIC OF GAME OR COMMON CODE

void Game::setSeed(int seed) {
	srand48(seed);
}

void Game::insertCardIntoDeck(vector<Card> &deck, Card& card) {
	deck.push_back(card);
}

void Game::shuffle(vector<Card> &deck) {
	int n = MAX_NUM_CARDS;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card c = deck[n]; // modified 
		deck[n] = deck[k];
		deck[k] = c;
	}
}

void Game::printCards(const vector<Card> &cards) {
	//general way of printing the cards
	for (int i = 0; i < (int) cards.size(); i++) {
		cout << " " << cards[i];
	}
}

void Game::showDeck(const vector<Card> &deck) {
  	int i = 0;
  	while(i < MAX_NUM_CARDS) {
		if(i == 0)
	  		cout << deck[0];
		else if (i % 13 == 0)
	  		cout << endl << deck[i];
		else 
	  		cout << " " << deck[i];
		
		++i;
  	}
  	cout << endl;
}

void Game::assignCards() {
	for(int i = 0; i < MAX_PLAYERS; i++) {
		for(int j = 0; j < MAX_CARDS_PER_PLAYER; j++) {
			Card c = deck[i * 13 + j];
			if(c.getSuit() == SPADE && c.getRank() == SEVEN) {
				curPlayer = i + 1;
			}

			player[i]->addCardToHand( c );
		}
	}
}

void Game::setUpLegalPlays() {
	if(table.getTableSize() == 0) {
		Card *c = new Card(SPADE, SEVEN);
		legalCards.push_back(*c);
	} else {
		legalCards = getLegalPlays(player[curPlayer-1], table);
		//Commented out for now -- due to time constraints, command line output was not considered
		/*cout << "Legal plays:";
		printCards(legalCards);
		cout << endl;*/
	}
}

void Game::clearAndContinue() {
	legalCards.clear();
	numTurns--;
	if(curPlayer == 4) 
		curPlayer = 1;
	else 
		curPlayer++;
	if(numTurns > 0) { 
		if(player[curPlayer-1]->getType() == 'h') {
			//when it's a player's turn, they are allowed to use 5 possible commands; the hand, and table is shown
			cout << "Cards on the table:" << endl;
			table.printTableCards(CLUB);
			table.printTableCards(DIAMOND);
			table.printTableCards(HEART);
			table.printTableCards(SPADE);

			cout << "Your hand:";
			printCards(player[curPlayer-1]->getHand());
			cout << endl;
			setUpLegalPlays();
			turnFinished = false;

		} else {
			computerMoves();
		}

	} 

	if(numTurns < 1) {
		//when all cards have been played, the round ends 
		roundFinished = true;		

		for (int i = 1; i <= MAX_PLAYERS; i++){
			if(player[i-1]->getScore() >= POINTS_TO_WIN) 
				gameFinished = true;
		}

		if(gameFinished){
			gameDone();
		}
	}
}

void Game::computerMoves() {
	while(numTurns > 0 && player[curPlayer-1]->getType() != 'h') {
		//if it's a computer, he plays the first legal move; if no legal move, then he discards the first card
		setUpLegalPlays();

		//if there are some legal cards, then play the first one; otherwise, discard the first card
		if((int) legalCards.size() > 0) {
			player[curPlayer-1]->play(legalCards, table, legalCards[0], turnFinished);
		} else {
			Card c = player[curPlayer-1]->getCardFromHand(0);
			player[curPlayer-1]->discard(0, c, turnFinished);
		}

		legalCards.clear();
		numTurns--;
		if(curPlayer == 4) 
			curPlayer = 1;
		else 
			curPlayer++;
	}

	if(numTurns > 0) {
		setUpLegalPlays();
		turnFinished = false;
	}
}



void Game::resetRound() {
	legalCards.clear();
	table.clear();
	player[0]->clear();
	player[1]->clear();
	player[2]->clear();
	player[3]->clear();
	shuffleCount++;
	numTurns = MAX_TURNS * MAX_PLAYERS;
	roundFinished = false;
	gameFinished = false;
	
	newRound();
}

void Game::newRound() {
	shuffle(deck);
	assignCards();

	//print "A new round begins. It's player <x>'s turn to play." Player x is whoever has 7 of spades.
	cout << "A new round begins. It's player " << curPlayer << "'s turn to play." << endl;

	if(player[curPlayer-1]->getType() != 'h') {
		computerMoves();
		if(numTurns == 0)
			clearAndContinue();
	} else {
		//when it's a player's turn, they are allowed to use 5 possible commands; the hand, and table is shown
		cout << "Cards on the table:" << endl;
		table.printTableCards(CLUB);
		table.printTableCards(DIAMOND);
		table.printTableCards(HEART);
		table.printTableCards(SPADE);

		cout << "Your hand:";
		printCards(player[curPlayer-1]->getHand());
		cout << endl;
		setUpLegalPlays();
		turnFinished = false;
	}
}

void Game::gameDone() {
	for (int i = 0; i < MAX_PLAYERS; i++ ){
		if(player[i]->getScore() < POINTS_TO_WIN && player[i]->getScore() < minScore){
			minScore = player[i]->getScore();
			winners.clear();
			winners.push_back(i+1);
		} else if (player[i]->getScore() < POINTS_TO_WIN && player[i]->getScore() == minScore){
			winners.push_back(i+1);
		}
	}

	//display who the winners are
	for(int i = 0; i < (int)winners.size(); i++ ){
		cout << "Player " << winners[i] << " wins!" << endl;
	}
}