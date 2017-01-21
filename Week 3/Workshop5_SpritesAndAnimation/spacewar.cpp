#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar() {}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar() {
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd) {
    Game::initialize(hwnd); // throws GameError

	// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// ship texture
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	// ship2 texture
	if (!ship2Texture.initialize(graphics, SHIP2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2 texture"));

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// ship
	if (!ship.initialize(graphics, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));

	// ship2
	if (!ship2.initialize(graphics, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &ship2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2"));

	// place planet in center of screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	ship.setX(GAME_WIDTH / 4);
	ship.setY(GAME_HEIGHT / 4);
	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	ship.setCurrentFrame(SHIP_START_FRAME);
	ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	ship.setDegrees(45.0f);

	ship2.setX(GAME_WIDTH * 3 / 4);
	ship2.setY(GAME_HEIGHT / 4);
	ship2.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	ship2.setCurrentFrame(SHIP_START_FRAME);
	ship2.setFrameDelay(SHIP_ANIMATION_DELAY);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update() {
	ship.update(frameTime);
	ship2.update(frameTime);

	// Rotate ship
	ship.setDegrees(ship.getDegrees() + frameTime * ROTATION_RATE);

	// Make ship smaller
	ship.setScale(ship.getScale() - frameTime * SCALE_RATE);

	// Move ship right
	ship.setX(ship.getX() + frameTime * SHIP_SPEED);

	if (ship.getX() > GAME_WIDTH) {
		ship.setX((float)-ship.getWidth());
		ship.setScale(SHIP_SCALE);
	}

	if (input->isKeyDown(SHIP_RIGHT_KEY)) {
		ship2.setDegrees(ship2.getDegrees() + frameTime * ROTATION_RATE);
	}
	if (input->isKeyDown(SHIP_LEFT_KEY)) {
		ship2.setDegrees(ship2.getDegrees() - frameTime * ROTATION_RATE);
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai() {}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions() {}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render() {
	graphics->spriteBegin();                // begin drawing sprites

	nebula.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene
	ship.draw();							// add the ship to the scene
	ship2.draw();

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll() {
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	shipTexture.onLostDevice();
	ship2Texture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll() {
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();
	shipTexture.onResetDevice();
	ship2Texture.onResetDevice();

	Game::resetAll();
    return;
}
