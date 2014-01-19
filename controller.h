#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include "model.h"
#include "Card.h"

#include <gtkmm.h>
#include <vector>
#include <string>

class Model;

class Controller {
public:
	Controller( Model* );
   	void startGameButtonClicked(std::string, std::vector<bool> &);
   	void play(Card &);
   	void discard(Card &);
   	void rageButtonClicked();
private:
   	Model *model_;
}; // Controller


#endif

