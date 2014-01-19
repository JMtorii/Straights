#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include "DeckGUI.h"
#include "observer.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "DeckGUI.h"
#include "StartDialog.h"
#include "Card.h"

#include <vector>
#include <gtkmm.h>

class Controller;
class Model;

const int NUM_CARDS_IN_EACH_SUIT = 13;
const int MAX_CARDS_IN_HAND = 13;
const int TOTAL_NUM_CARDS = 52;
const int NUM_PLAYERS = 4;


class View : public Gtk::Window, public Observer {
public:
    View( Controller*, Model* );
	virtual ~View();
	virtual void update();					// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Card Images
	DeckGUI deck;

	//GUI members
	Gtk::VBox panels;

	Gtk::HBox menu;
	Gtk::Button start_game_button;			//button to start a new game
	Gtk::Button end_game_button;			//button to end the game

	Gtk::HBox table;
	Gtk::Frame frame;
	Gtk::VBox suits;
	Gtk::HBox clubs;						//holds all of the clubs on the table
	Gtk::HBox diamonds;						//holds all of the diamonds on the table
	Gtk::HBox hearts;						//holds all of the hearts on the table
	Gtk::HBox spades;						//holds all of the spades on the table
	Gtk::Image card[52];					//images for the cards

	Gtk::HBox players;
	Gtk::Frame p[4];
	Gtk::VBox pDesc[4];
	Gtk::Button rage[4];					//rage button
	Gtk::Label points[4];					//displays the points
	Gtk::Label discards[4];					//displays the number of discards

	Gtk::HBox hand;
	Gtk::Frame frameHand;
	Gtk::HBox boxHand;
	Gtk::Image cardImage[13];				//displays the cards in the hand as images
	Gtk::Button hand_card_buttons[13];		//buttons for the cards in the hand

	Gtk::Button discardButton;

	std::vector<Card> handCards;			//holds the cards in the current player's hand

	//methods for the buttons
	void startGameButtonClicked();			//starts a new game with a new seed and options for players
	void endGameButtonClicked();			//ends the game and terminates
	void cardInHandClicked(int);			//handles play and discards based on the card clicked in the hand
	void discardButtonClicked();			//discard button to allow discards
	void rageButtonClicked();				//player rages and becomes a computer

}; // View

#endif
