CXX= g++
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS = subject.o model.o Game.o Card.o Command.o Table.o Player.o Human.o Computer.o controller.o DeckGUI.o StartDialog.o view.o main.o
EXEC = straights

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)

DeckGUI.o: DeckGUI.h DeckGUI.cpp
StartDialog.o: StartDialog.h StartDialog.cpp controller.h
model.o: subject.h model.h model.cpp Game.h
Game.o: Game.h Game.cpp Card.o Command.o Table.o Player.o Human.o Computer.o
Card.o: Card.h Card.cpp
Command.o: Command.h Command.cpp Card.h
Table.o: Table.h Table.cpp Card.h
Player.o: Player.h Player.cpp Table.h
Human.o: Human.h Human.cpp Player.h
Computer.o: Computer.h Computer.cpp Player.h
subject.o: subject.h subject.cpp
controller.o: controller.h model.h Card.h controller.cpp
view.o: view.h observer.h controller.h model.h subject.h DeckGUI.h view.cpp Card.h StartDialog.h StartDialog.cpp
main.o: view.h controller.h model.h main.cpp
