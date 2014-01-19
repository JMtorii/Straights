#include <iostream>
#include "StartDialog.h"

using namespace std;

// Specifies the parent window of the dialog box and the title of the dialog box.
StartDialog::StartDialog( Gtk::Window & parentWindow, string title, Controller *c) : Dialog( title, parentWindow, true, true ), players(true, 0), instr("Enter a seed and identify the humans and players:"), seedBox(false, 10), seedLabel("Seed:"){
	controller_ = c;

	//strings to concatenate
	string playerIdStr[4] = { "Player 1:", "Player 2:", "Player 3:", "Player 4:" };
	string options[2] = { "Human", "Computer" };
	vector<bool> results; //0 for human and 1 for computer

	//should
	set_deletable(false);
	set_default_size(400, 100);

	Gtk::VBox* contentArea = this->get_vbox();
	contentArea->add(players);
	players.add(instr);

	//set up the seed
	seedLabel.set_justify(Gtk::JUSTIFY_LEFT);
	seedEntry.set_text("0");
	seedBox.pack_start(seedLabel);
	seedBox.pack_start(seedEntry);
	players.pack_start(seedBox);

	//create the groups for the buttons
	int j = 0;
	for(int i = 0; i < 4; i++) {
		playerId[i].set_label(playerIdStr[i]);
		pOptions[i].add(playerId[i]);
		Gtk::RadioButton::Group group = pRButton[j].get_group();

		pRButton[j].set_label(options[0]);
		pOptions[i].add(pRButton[j]);
		j++;

		pRButton[j].set_label(options[1]);
		pRButton[j].set_group(group);
		pOptions[i].add(pRButton[j]);
		j++;

		players.add(pOptions[i]);
	}

	//add the OK buttons
	okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all();
    
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
        	//set up the results for the players and computers
        	for(int i = 0; i < 8; i+=2) {
        		if(pRButton[i].get_active() == 1)
        			results.push_back(0);
        		else 
        			results.push_back(1);
        	}
        	controller_->startGameButtonClicked(seedEntry.get_text(), results);
        	// send results to the model
            break;
    } // switch    	
} // MyDialogBox::MyDialogBox

StartDialog::~StartDialog() {	
	delete okButton;
} // MyDialogBox::~MyDialogBox
