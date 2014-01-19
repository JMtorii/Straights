#include "view.h"

#include <iostream>

using namespace std;

View::View(Controller *c, Model *m) :  panels(false, 10), menu(true, 0), table(true, 100), suits(true, 0), clubs(true, 0), diamonds(true, 0), hearts(true, 0), spades(true, 0), players(true, 10), hand(true, 10){
	// Sets some properties of the window.
	model_ = m;
	controller_ = c;
    set_title( "Jun's Straights" );
	set_border_width( 10 );
	set_size_request(900, 650);
	add(panels);

	//------------------------------ MENU ---------------------------------//
	menu.set_size_request(850, 20);
	panels.add(menu);
	start_game_button.set_label("Start a new game");
	end_game_button.set_label("End current game");
	menu.add(start_game_button);
	menu.add(end_game_button);

	start_game_button.signal_clicked().connect( sigc::mem_fun( *this, &View::startGameButtonClicked ) );
	end_game_button.signal_clicked().connect( sigc::mem_fun( *this, &View::endGameButtonClicked ) );

	//------------------------------ TABLE --------------------------------//
	panels.add(table);
	frame.set_label("Cards on the table");
	table.add(frame);
	frame.add(suits);
	
	suits.add(clubs);
	for(int i = 0; i < NUM_CARDS_IN_EACH_SUIT; i++) {
		card[i].set(deck.null());
		clubs.add(card[i]);
	}

	suits.add(diamonds);
	for(int i = 13; i < NUM_CARDS_IN_EACH_SUIT * 2; i++) {
		card[i].set(deck.null());
		diamonds.add(card[i]);
	}

	suits.add(hearts);
	for(int i = 26; i < NUM_CARDS_IN_EACH_SUIT * 3; i++) {
		card[i].set(deck.null());
		hearts.add(card[i]);
	}

	suits.add(spades);
	for(int i = 39; i < NUM_CARDS_IN_EACH_SUIT * 4; i++) {
		card[i].set(deck.null());
		spades.add(card[i]);
	}

	//------------------------------ PLAYERS --------------------------------//
	panels.add(players);

	for(int i = 0; i < NUM_PLAYERS; i++) {
		stringstream sstm;
		sstm << "Player " << (i+1);
		string result = sstm.str();
		p[i].set_label(result);
		players.add(p[i]);

		p[i].add(pDesc[i]);

		rage[i].set_label("RAGE");
		pDesc[i].add(rage[i]);
		rage[i].signal_clicked().connect( sigc::mem_fun( *this, &View::rageButtonClicked ) );

		points[i].set_text("0 points");
		pDesc[i].add(points[i]);

		discards[i].set_text("0 discards");
		pDesc[i].add(discards[i]);
	}


	//------------------------------ HAND -----------------------------------//
	panels.add(hand);
	hand.add(frameHand);

	frameHand.set_label("Your hand");
	frameHand.add(boxHand);

	for(int i = 0; i < MAX_CARDS_IN_HAND; i++) {
		cardImage[i].set(deck.null());
		hand_card_buttons[i].set_image(cardImage[i]);
		hand_card_buttons[i].set_sensitive(false);
		boxHand.add(hand_card_buttons[i]);
		hand_card_buttons[i].signal_clicked().connect( sigc::bind<int>(sigc::mem_fun( *this, &View::cardInHandClicked ), i) );
	}

	//------------------------------ DISCARD -----------------------------------//
	discardButton.set_sensitive(false);
	discardButton.set_label("Discard");
	panels.add(discardButton);
	discardButton.signal_clicked().connect( sigc::mem_fun( *this, &View::discardButtonClicked ) );

	show_all();


	// Register view as observer of model
	model_->subscribe(this);

	//call the dialog to initialize the game
	startGameButtonClicked();

} // View::View

View::~View() {}


void View::update() {
	//update table
	vector<Card> table = model_->getTable();
	for(int i = 0; i < (int)table.size(); i++) {
		Card c = table[i];
		int index = ((int) c.getRank()) + ((int) c.getSuit()) * 13;
		card[index].set(deck.image(c));
	}
	if((int)table.size() == 0){
		for(int i = 0; i < TOTAL_NUM_CARDS; i++) {
			card[i].set(deck.null());
		}
	}

	//update points
	vector<string> scores = model_->getScores();
	for(int i = 0; i < (int) scores.size(); i++) {
		points[i].set_text(scores[i]);
	}
	if((int)scores.size() == 0){
		for(int i = 0; i < NUM_PLAYERS; i++) {
			points[i].set_text("0 points");
		}
	}

	//update discards
	vector<string> numDiscards = model_->getNumDiscards();
	for(int i = 0; i < (int) numDiscards.size(); i++) {
		discards[i].set_text(numDiscards[i]);
	}
	if((int)numDiscards.size() == 0){
		for(int i = 0; i < NUM_PLAYERS; i++) {
			points[i].set_text("0 discards");
		}
	}

	//enable/disable rage buttons
	for(int i = 1; i <= NUM_PLAYERS; i++) {
		if(i == model_->getCurPlayer() && model_->isCurPlayerHuman())
			rage[i-1].set_sensitive(true);
		else
			rage[i-1].set_sensitive(false);
	}

	//update who is the current human player
	frameHand.set_label(model_->getCurPlayerAsString());

	//update hand
	handCards.clear();
	handCards = model_->getCurPlayerHand();
	vector<Card> legalCards = model_->getLegalCards();

	for (int i = 0; i < MAX_CARDS_IN_HAND; i++){
		if(i >= (int)handCards.size()) {
			cardImage[i].set(deck.null());
			hand_card_buttons[i].set_sensitive(false);
		} else {
			cardImage[i].set(deck.image(handCards[i]));
			for(int j = 0; j < (int)legalCards.size(); j++) {
				if(handCards[i] == legalCards[j]){
					hand_card_buttons[i].set_sensitive(true);
					break;
				} else if (handCards[i] != legalCards[j] && j == (int)legalCards.size() - 1) {
					hand_card_buttons[i].set_sensitive(false);
				}
			}
		}
	}

	//update discard button
	if(model_->getLegalCardsSize() > 0) {
		discardButton.set_sensitive(false);
	} else {
		discardButton.set_sensitive(true);
	}

	//update end of round/game
	if(model_->isRoundFinished()) {
		//set up the discard strings
		vector<string> pDiscards;
		string p1Discards = model_->getP1Discards();
		pDiscards.push_back(p1Discards);
		string p2Discards = model_->getP2Discards();
		pDiscards.push_back(p2Discards);
		string p3Discards = model_->getP3Discards();
		pDiscards.push_back(p3Discards);
		string p4Discards = model_->getP4Discards();
		pDiscards.push_back(p4Discards);

		stringstream ss;
		string strRoundFinished;

		//put the strings together
		for (int i = 1; i <= NUM_PLAYERS; i++) {
			ss << "Player " << i << "'s Discards: " << pDiscards[i-1] << '\n';
			ss << "Player " << i << "'s Points: " << scores[i-1] << '\n' << '\n';
		}

		//if the game is finished, display the winners as well
		if(model_->isGameFinished()) {
			ss << model_->getWinners();
		}

		strRoundFinished = ss.str();

		//display the dialog
		Gtk::MessageDialog dialog(*this, strRoundFinished);

		//display the appropriate title
		if(model_->isGameFinished()) {
			dialog.set_title("The game is finished");
		} else {
			dialog.set_title("The round is finished");
		}

		//this doesn't seem to work but I hope it does
		dialog.set_default_size(800, 100);

		//stop the main thread and run the dialog until there's a response
		dialog.run();

		//reset table -- this may need to be moved to a separate method or handled by the update method more appropriately
		if(!model_->isGameFinished()) {
			for(int i = 0; i < TOTAL_NUM_CARDS; i++) {
				card[i].set(deck.null());
			}

			model_->resetRound();
		}
		
	}
}

void View::startGameButtonClicked() {
	//update should properly clear all of the cards on the table but it doesn't -- due to time constraints, a shortcut is done here
	for(int i = 0; i < TOTAL_NUM_CARDS; i++) {
		card[i].set(deck.null());
	}

	//call the start dialog
	StartDialog dialog( *this, "New Game", controller_);
}

void View::endGameButtonClicked() {
	//the following lines are not necessary but for future implementation, this can clear the entire UI
	for(int i = 0; i < TOTAL_NUM_CARDS; i++) {
		card[i].set(deck.null());
	}

	for(int i = 0; i < NUM_PLAYERS; i++) {
		points[i].set_text("0 points");
		discards[i].set_text("0 discards");
		rage[i].set_sensitive(false);
	}

	for(int i = 0; i < MAX_CARDS_IN_HAND; i++) {
		cardImage[i].set(deck.null());
		hand_card_buttons[i].set_sensitive(false);
	}

	frameHand.set_label("Your Hand");

	discardButton.set_sensitive(false);

	//this quits the game
	hide();
}

void View::cardInHandClicked(int index) {
	//disable all of the hand buttons (this should be done by the update method more appropriately)
	for(int i = 0; i < MAX_CARDS_IN_HAND; i++){
		hand_card_buttons[i].set_sensitive(false);
	}

	if(discardButton.get_sensitive()) {
		//discard
		controller_->discard(handCards[index]);
	} else {
		//play
		controller_->play(handCards[index]);
	}
}

void View::discardButtonClicked() {
	int handSize = (int)handCards.size();

	for(int i = 0; i < MAX_CARDS_IN_HAND; i++){
		if(i >= handSize)
			hand_card_buttons[i].set_sensitive(false);
		else 
			hand_card_buttons[i].set_sensitive(true);
	}
}

void View::rageButtonClicked() {
	controller_->rageButtonClicked();
}