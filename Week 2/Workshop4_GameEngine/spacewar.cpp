#include "spacewar.h"

// Constructor
Spacewar::Spacewar() {}

// Destructor
Spacewar::~Spacewar() {
	releaseAll();
}

// Initializes the game
void Spacewar::initialize(HWND hwnd) {
	Game::initialize(hwnd);	// throws GameError
	return;
}

// Update all game items
void Spacewar::update() {}

// Artificial Intelligence
void Spacewar::ai() {}

// Handle collisions
void Spacewar::collisions() {}

// Render game items
void Spacewar::render() {}

// The graphics device was lost
// Release all reserved video memory so graphics device may be reset
void Spacewar::releaseAll() {
	Game::releaseAll();
	return;
}

// The graphics device has been reset
// Recreate all surfaces
void Spacewar::resetAll() {
	Game::resetAll();
	return;
}
