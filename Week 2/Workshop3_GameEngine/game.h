#ifndef _GAME_H
#define _GAME_H
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <Mmsystem.h>
#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "gameError.h"

class Game
{
protected:
	// common game properties
	Graphics *graphics;			// pointer to graphics
	Input *input;				// pointer to Input
	HWND hwnd;					// window handle
	HRESULT hr;					// standard return type
	LARGE_INTEGER timeStart;	// Performance Counter start value
	LARGE_INTEGER timeEnd;		// Performace Counter end value
	LARGE_INTEGER timerFreq;		// Performace Coutner frequency
	float frameTime;			// Time required for last frame
	float fps;					// frames per seconds
	DWORD sleepTime;			// number of milliseconds to sleep between frames
	bool paused;				// true if game is paused
	bool initalized;

public:
	// Constructor
	Game();
	// Destructor
	virtual ~Game();

	// Member functions

	// Window message handler
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Initialise the game
	// Pre:hwnd is handle to window
	virtual void initialize(HWND hwnd);

	// Call run repeatedly by the main message loop in WinMain
	virtual void run(HWND);

	// Call when the graphics device was losts
	// Relesase all reserved video memory so graphics device may be reset.
	virtual void releaseAll();

	// Recreaste all surfaces and reset all entites
	virtual void resetAll();

	// Delete all reserved memory
	virtual void deleteAll();

	// Render game items
	virtual void renderGame();
	virtual void render() = 0;

	// Handle lost graphics device
	virtual void handleLostGraphicsDevice();

	// Return pointer to Graphics
	Graphics* getGraphics() { return graphics;}

	// Return pointer to Input
	Input* getInput() { return input; }

	// Exit the game
	void exitGame()  { PostMessage(hwnd, WM_DESTROY, 0, 0); }

	// Pure virtual function declarations
	// Thes functions MUST be written in any class that inherits from Game

	// Update game items
	virtual void update() = 0;

	// Perform AI calcuations
	virtual void ai() = 0;

	// Check for collisions
	virtual void collisions() = 0;
	// Render graphics 
	// Call graphics->sprteBegin();
	//		draw sprties
	// Call graphics->spriteEnd();
	//		draw non-sprites


};

#endif