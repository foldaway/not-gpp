#include "game.h"

// Constructor
Game::Game() {
	input = new Input();		// Initialize keyboard input immediately
	// Additional initialization is handled in later call to input->initialize()
	paused = false;
	graphics = NULL;
	initialized = false;
}

// Desctructor
Game::~Game() {
	deleteAll();				// Free all reserved memory
	ShowCursor(true);			// Show cursor
}

// Window message handler
LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (initialized) {			// Do not process messages if not initialized
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN: case WM_SYSKEYDOWN:    // key down
			input->keyDown(wParam);
			return 0;
		case WM_KEYUP: case WM_SYSKEYUP:        // key up
			input->keyUp(wParam);
			return 0;
		case WM_CHAR:                           // character entered
			input->keyIn(wParam);
			return 0;
		case WM_MOUSEMOVE:                      // mouse moved
			input->mouseIn(lParam);
			return 0;
		case WM_INPUT:                          // raw mouse data in
			input->mouseRawIn(lParam);
			return 0;
		case WM_LBUTTONDOWN:                    // left mouse button down
			input->setMouseLButton(true);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_LBUTTONUP:                      // left mouse button up
			input->setMouseLButton(false);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_MBUTTONDOWN:                    // middle mouse button down
			input->setMouseMButton(true);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_MBUTTONUP:                      // middle mouse button up
			input->setMouseMButton(false);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_RBUTTONDOWN:                    // right mouse button down
			input->setMouseRButton(true);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_RBUTTONUP:                      // right mouse button up
			input->setMouseRButton(false);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_XBUTTONDOWN: case WM_XBUTTONUP: // mouse X button down/up
			input->setMouseXButton(wParam);
			input->mouseIn(lParam);             // mouse position
			return 0;
		case WM_DEVICECHANGE:                   // check for controller insert
			input->checkControllers();
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);	// let Windows handle it
}

// Initialize the game
void Game::initialize(HWND hw) {
	hwnd = hw;								// Save window handle
	// Initialize graphics
	graphics = new Graphics();
	// Throws GameError
	graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);
	// Initialize input, do not capture mouse
	input->initialize(hwnd, false);			// Throws GameError

	// Attempt to set up high resolution timer
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	QueryPerformanceCounter(&timeStart);	// Get starting time
	initialized = true;
}

// Handle lost graphics device
void Game::handleLostGraphicsDevice() {
	// Test for and handle lost device
	hr = graphics->getDeviceState();

	if (FAILED(hr)) {		// If graphics device is not in a valid state
		// If the device is lost and not available for reset
		if (hr == D3DERR_DEVICELOST) {
			Sleep(100);		// Yield CPU time (100 milli-seconds)
			return;
		}
		// The device was lost but is now available for reset
		else if (hr == D3DERR_DEVICENOTRESET) {
			releaseAll();
			hr = graphics->reset();		// Attempt to reset graphics device
			if (FAILED(hr))				// If reset failed
				return;

			resetAll();
		}
		else {
			return;			// Other device error
		}
	}
}

void Game::renderGame() {
	// Start rendering
	if (SUCCEEDED(graphics->beginScene())) {
		// render is a pure virtual function that must be provided in the inheriting class
		render();			// Call render in derived class

		// Stop rendering
		graphics->endScene();
	}

	handleLostGraphicsDevice();

	// Display the back buffer on the screen
	graphics->showBackbuffer();
}

void Game::run(HWND hwnd) {
	if (graphics == NULL)	// Graphics not initialized
		return;

	// Calculate elapsed time of last frame, save in frameTime
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;

	// Power saving code, requires winmm.lib
	// If not enough time has elapsed for desired frame rate
	if (frameTime < MIN_FRAME_TIME) {
		sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1);			// Request 1ms resolution for windows timer
		Sleep(sleepTime);			// Release cpu for sleepTime
		timeEndPeriod(1);			// End 1ms timer resolution
		return;
	}

	if (frameTime > 0.0)
		fps = (fps * 0.99f) + (0.01f / frameTime);	// Average fps

	if (frameTime > MAX_FRAME_TIME)	// If frame rate is very slow
		frameTime = MAX_FRAME_TIME;	// Limit maximum frameTime

	timeStart = timeEnd;

	// update(), ai(), and collisions() are pure virtual functions
	// These functions must be provided in the class that inherits from Game
	if (!paused) {
		update();
		ai();
		collisions();
		input->vibrateControllers(frameTime);
	}

	renderGame();				// Draw all game items
	input->readControllers();	// Read state of controllers

	// Clear input
	// Call this after all key checks are done
	input->clear(inputNS::KEYS_PRESSED);
}

// Release all reserved video memory so graphics device may be reset
void Game::releaseAll() {}

// Recreate all surfaces and reset all entities
void Game::resetAll() {}

// Delete all reserved memory
void Game::deleteAll() {
	releaseAll();
	SAFE_DELETE(graphics);
	SAFE_DELETE(input);
	initialized = false;
}
