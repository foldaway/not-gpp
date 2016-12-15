#ifndef _CONSTANTS_H            // prevent multiple definitions if this 
#define _CONSTANTS_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

// Useful macros

// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }

//Constants

// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Game Engine Part 1";
const bool FULLSCREEN = false;				// windowed or fullscreen
const UINT GAME_WIDTH = 700;				// width of game in pixels
const UINT GAME_HEIGHT = 500;				// height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;					// Target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;					// Minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;		// Minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;	// Maximum time used in calculations

#endif
