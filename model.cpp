#include "model.h"

#include <vector>
#include <sstream>
#include <string>
using namespace std;

Model::Model() {
	//nothing to do here
}

//------------------- METHODS THAT NOTIFY THE VIEW -------------------------//

void Model::startGame(int seed, vector<bool> &results) {
	game.startGame(seed, results);
	notify();
}

void Model::play(Card &card) {
	game.play(card);
	notify();
}

void Model::discard(Card &card) {
	game.discard(card);
	notify();
}

void Model::rage() {
	game.rage();
	game.computerMoves();
	if(game.getNumTurns() < 1)
		game.clearAndContinue();
	notify();
}

void Model::resetRound() {
	game.resetRound();
	notify();
}

//------------------------- ACCESSORS ----------------------------------//


int Model::getCurPlayer() const {
	return game.getCurPlayer();
}

string Model::getCurPlayerAsString() const {
	stringstream ss;
	ss << "Player " << game.getCurPlayerAsString() << "'s Hand";
	return ss.str();
}

vector<Card> Model::getCurPlayerHand() const {
	return game.getCurPlayerHand();
}

vector<Card> Model::getLegalCards() const {
	return game.getLegalCards();
}

int Model::getLegalCardsSize() const {
	return getLegalCards().size();
}

vector<Card> Model::getTable() const {
	return game.getTable();
}

vector<string> Model::getScores() const {
	vector<int> scores = game.getScores();
	vector<string> tempScores;
	for(int i = 0; i < (int)scores.size(); i++){
		stringstream ss;
		ss << scores[i] << " points";
		tempScores.push_back(ss.str());
	}

	return tempScores;
}

vector<string> Model::getNumDiscards() const {
	vector<int> numDiscards = game.getNumDiscards();
	vector<string> strDiscards;
	for(int i = 0; i < (int)numDiscards.size(); i++) {
		stringstream ss;
		ss << numDiscards[i] << " discards";
		strDiscards.push_back(ss.str());
	}

	return strDiscards;
}

string Model::getP1Discards() const {
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	string strP1Discards;
	stringstream ss;

	for(int i = 0; i < (int)game.getP1Discards().size(); i++) {
		ss << ranks[game.getP1Discards().at(i).getRank()] << suits[game.getP1Discards().at(i).getSuit()];
		if(i < (int)game.getP1Discards().size() - 1)
			ss << " ";
		
	}

	strP1Discards = ss.str();
	return strP1Discards;
}

string Model::getP2Discards() const {
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	string strP2Discards;
	stringstream ss;

	for(int i = 0; i < (int)game.getP2Discards().size(); i++) {
		ss << ranks[game.getP2Discards().at(i).getRank()] << suits[game.getP2Discards().at(i).getSuit()];
		if(i < (int)game.getP2Discards().size() - 1)
			ss << " ";
	}

	strP2Discards = ss.str();
	return strP2Discards;
}

string Model::getP3Discards() const {
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	string strP3Discards;
	stringstream ss;

	for(int i = 0; i < (int)game.getP3Discards().size(); i++) {
		ss << ranks[game.getP3Discards().at(i).getRank()] << suits[game.getP3Discards().at(i).getSuit()];
		if(i < (int)game.getP3Discards().size() - 1)
			ss << " ";
	}

	strP3Discards = ss.str();
	return strP3Discards;
}

string Model::getP4Discards() const {
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	string strP4Discards;
	stringstream ss;

	for(int i = 0; i < (int)game.getP4Discards().size(); i++) {
		ss << ranks[game.getP4Discards().at(i).getRank()] << suits[game.getP4Discards().at(i).getSuit()];
		if(i < (int)game.getP4Discards().size() - 1)
			ss << " ";
	}

	strP4Discards = ss.str();
	return strP4Discards;
}

string Model::getWinners() const {
	vector<int> dWinners = game.getWinners();
	stringstream ss;
	ss << "Player(s) ";
	for(int i = 0; i < (int)dWinners.size(); i++) {
		if(i < (int)dWinners.size() - 1)
			ss << dWinners[i] << ", ";
		else
			ss << dWinners[i];
	}
	ss << " wins!";
	return ss.str();
}

bool Model::isCurPlayerHuman() const {
	return game.isCurPlayerHuman();
}

bool Model::isGameFinished() const {
	return game.isGameFinished();
}

bool Model::isRoundFinished() const {
	return game.isRoundFinished();
}