#ifndef _SPACEWAR_H
#define _SPACEWAR_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"

// class declaration to be inserted here
class Spacewar : public Game {
private:
	// variables

public:
	// Constructors
	Spacewar();
	
	// Destroy
	virtual ~Spacewar();

	// Initalize the game
	void initialize(HWND hwnd);
	void update();				// must override pure cirtual from Game
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
};


#endif