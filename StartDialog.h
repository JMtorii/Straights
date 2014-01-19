#ifndef __START_DIALOG_H
#define __START_DIALOG_H
#include "controller.h"
#include <gtkmm.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Controller;

class StartDialog : Gtk::Dialog {
public:
	// Specifies the parent window of the dialog box and the title of the dialog box.
	StartDialog( Gtk::Window & parentWindow, string title, Controller* c);
	virtual ~StartDialog();
	
private:
	Controller *controller_;

	Gtk::VBox players;
	Gtk::Label instr;							
	Gtk::HBox seedBox;
	Gtk::Label seedLabel;						//label to identify the seed textbox
	Gtk::Entry seedEntry;						//textbox for the seed
	Gtk::HBox pOptions[4];
	Gtk::Label playerId[4];						//holds the "Player " text
	Gtk::RadioButton::Group group[4];          	//used to group the radio buttons so only one can be active at a time.
	Gtk::RadioButton pRButton[8];				//radio buttons to identify if each player is either a computer or human
	Gtk::Button* okButton;						//OK button
}; // MyDialogBox
#endif
