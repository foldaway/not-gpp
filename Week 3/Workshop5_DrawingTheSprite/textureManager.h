#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "constants.h"

class TextureManager {
private:
	UINT width;
	UINT height;
	LP_TEXTURE texture;
	const char *file;
	Graphics *graphics;
	bool initialized;
	HRESULT hr;

public:
	TextureManager();
	virtual ~TextureManager();

	// Returns a pointer to the texture
	LP_TEXTURE getTexture() const { return texture; }

	// Returns the texture width
	UINT getWidth() const { return width; }

	// Return the texture height
	UINT getHeight() const { return height; }

	// Initialize the textureManager
	// Pre: *g points to the Graphics object
	//		*file points to name of texture file loaded
	// Post: The texture file is loaded
	virtual bool initialize(Graphics *g, const char *file);

	// Release resources
	virtual void onLostDevice();

	// Restore resources
	virtual void onResetDevice();
};

#endif
