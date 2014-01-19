#include "Player.h"

#include <iostream>
#include <vector>

using namespace std;

Player::Player(int num, char type) {
	number_ = num;
	type_ = type;
	score_ = 0;
}

Player::Player(int num, char type, int score, vector<Card> hand2, vector<Card> discards2) {
	number_ = num;
	type_ = type;
	score_ = score;
	hand = hand2;
	discards = discards2;
}

void Player::play(vector<Card>& legalCards, Table& table, Card& card, bool & turnFinished){
	//nothing to do here
}

void Player::discard(int legalCardsSize, Card& card, bool& turnFinished){
	//nothing to do here
}

void Player::setNumber(const int number) {
	number_ = number;
}

void Player::setType(const char type) {
	type_ = type;
}

void Player::setScore(const int score) {
	score_ += score;
}

void Player::addCardToHand(const Card& card) {
	hand.push_back(card);
}

void Player::addCardToDiscards(const Card& card) {
	discards.push_back(card);
}

int Player::getNumber() const {
	return number_;
}

char Player::getType() const {
	return type_;
}

int Player::getScore() const {
	return score_;
}

vector<Card> Player::getHand() const {
	return hand;
}

Card Player::getCardFromHand(int index) const{
	return hand[index];
}

int Player::getHandSize() const {
	return hand.size();
}

vector<Card> Player::getDiscards() const {
	return discards;
}

void Player::removeCardFromHand(const Card& card){
	int i = 0;
	while(hand[i] != card) {
		i++;
	}
	hand.erase(hand.begin() + i);
}

bool Player::isLegal(const vector<Card> &legalCards, const Card& card){
	for(int i = 0; i < (int)legalCards.size(); i++) {
		if(card == legalCards[i]) 
			return true;
	}
	return false;
}

void Player::clear() {
	hand.clear();
	discards.clear();
}