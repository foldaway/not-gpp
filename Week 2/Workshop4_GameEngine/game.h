#ifndef _GAME_H
#define _GAME_H
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <mmsystem.h>
#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "gameError.h"

class Game {
protected:
	// Common game properties
	Graphics *graphics;			// Pointer to graphics
	Input *input;				// Pointer to input
	HWND hwnd;					// Window handle
	HRESULT hr;					// Standard return type
	LARGE_INTEGER timeStart;	// Performance counter start value
	LARGE_INTEGER timeEnd;		// Performance counter end value
	LARGE_INTEGER timerFreq;		// Performance counter frequency
	float frameTime;			// Time required for last frame
	float fps;					// Frames per second
	DWORD sleepTime;			// Number of milli-seconds to sleep between frames
	bool paused;				// True if game is paused
	bool initialized;

public:
	// Constructor
	Game();

	//Destructor
	virtual ~Game();

	// Member functions

	// Window message handler
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Initialize the game
	// Pre: hwnd is handle to window
	virtual void initialize(HWND hwnd);

	// Call run repeatedly by the main message loop in WinMain
	virtual void run(HWND);

	// Call when the graphics device was lost
	// Release all reserved video memory so graphics device may be reset
	virtual void releaseAll();

	// Recreate all surfaces and reset all entities
	virtual void resetAll();

	// Delete all reserved memory
	virtual void deleteAll();

	// Render game items
	virtual void renderGame();

	virtual void render() = 0;

	// Handle lost graphics device
	virtual void handleLostGraphicsDevice();

	// Return pointer to Graphics
	Graphics* getGraphics() { return graphics; }

	// Return pointer to Input
	Input* getInput() { return input; }

	// Exit the game
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }

	// Pure virtual function declarations
	// These functions must be overwritten in any class that inherits from Game

	// Update game items
	virtual void update() = 0;

	// Perform AI calculations
	virtual void ai() = 0;

	// Check for collisions
	virtual void collisions() = 0;

	// Render graphics
	// Call graphics->spriteBegin();
	//		draw sprites
	// Call graphics->spriteEnd();
	//		draw non-sprites
};

#endif
