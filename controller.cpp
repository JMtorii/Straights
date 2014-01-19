#include "controller.h"

using namespace std;

Controller::Controller(Model *m) : model_(m) {}

void Controller::startGameButtonClicked(std::string sSeed, std::vector<bool> &results) {
	int dSeed;
	stringstream(sSeed) >> dSeed;
	model_->startGame(dSeed, results);
} 

void Controller::play(Card& card) {
	model_->play(card);
}

void Controller::discard(Card& card) {
	model_->discard(card);
}

void Controller::rageButtonClicked() {
	model_->rage();
}