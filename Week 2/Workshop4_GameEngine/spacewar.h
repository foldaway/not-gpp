#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"

class Spacewar : public Game {
private:

public:
	// Constructor
	Spacewar();

	//Destructor
	virtual ~Spacewar();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();			// Pure virtual functions from Game must be overwritten
	void ai();				// "
	void collisions();		// "
	void render();			// "
	void releaseAll();
	void resetAll();
};

#endif