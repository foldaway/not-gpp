
#ifndef _CONSTANTS_H            // prevent multiple definitions if this 
#define _CONSTANTS_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
// Transparent color: Magenta
#define TRANSCOLOR SETCOLOR_ARGB(0, 255, 0, 255)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Spacewar";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float ROTATION_RATE = 180.0f;				// degreees per second
const float SCALE_RATE = 0.2f;					// % change per second
const float SHIP_SPEED = 100.0f;				// pixels per second
const float SHIP_SCALE = 1.5f;					// starting ship scale

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR SHIP_LEFT_KEY = VK_LEFT;	// Left arrow key
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;	// Right arrow key

// graphic images
const char NEBULA_IMAGE[] = "pictures\\orion.jpg";
const char PLANET_IMAGE[] = "pictures\\planet.png";
const char SHIP_IMAGE[] = "pictures\\ship.png";
const char SHIP2_IMAGE[] = "pictures\\ship2.png";

const int SHIP_WIDTH = 32;
const int SHIP_HEIGHT = 32;
const int SHIP_COLS = 2;
const int SHIP_START_FRAME = 0;
const int SHIP_END_FRAME = 3;
const float SHIP_ANIMATION_DELAY = 0.2f;

#endif
