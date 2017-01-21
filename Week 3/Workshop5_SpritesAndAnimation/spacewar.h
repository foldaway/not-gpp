#ifndef _SPACEWAR_H             // prevent multiple definitions if this 
#define _SPACEWAR_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"

//=============================================================================
// Create game class
//=============================================================================
class Spacewar : public Game
{
private:
    // variables
	TextureManager nebulaTexture;   // nebula texture
	TextureManager planetTexture;   // planet texture
	TextureManager shipTexture;		// ship texture
	TextureManager ship2Texture;
	Image   planet;                 // planet image
	Image   nebula;                 // nebula image
	Image	ship;					// ship image
	Image	ship2;

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
