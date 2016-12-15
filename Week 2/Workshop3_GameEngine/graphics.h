#ifndef _GRAPHICS_H             // prevent multiple definitions if this 
#define _GRAPHICS_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include "constants.h"
#include "gameError.h"

#pragma comment(lib, "d3d9.lib")

// DirectX pointer types
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D       LPDIRECT3D9


// Color defines
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

class Graphics
{
private:
	// DirectX pointers and stuff
	LP_3D       direct3d;
	LP_3DDEVICE device3d;
	D3DPRESENT_PARAMETERS d3dpp;

	// other variables
	HRESULT     result;         // standard Windows return codes
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;

	COLOR_ARGB backColor;

	// (For internal engine use only. No user serviceable parts inside.)
	// Initialize D3D presentation parameters
	void    initD3Dpp();

public:
	// Constructor
	Graphics();

	// Destructor
	virtual ~Graphics();

	// Releases direct3d and device3d.
	void    releaseAll();

	// Initialize DirectX graphics
	// Throws GameError on error
	// Pre: hw = handle to window
	//      width = width in pixels
	//      height = height in pixels
	//      fullscreen = true for full screen, false for window
	void    initialize(HWND hw, int width, int height, bool fullscreen);

	//Set colour used to clear screen
	void setBackColor(COLOR_ARGB c) { backColor = c; };

	// Display the offscreen backbuffer to the screen.
	HRESULT showBackbuffer();

	// get functions
	// Return direct3d
	LP_3D get3D()					{ return direct3d; }

	// Return device3d
	LP_3DDEVICE get3Ddevice()		{ return device3d; }

	// Return handle to device context (window)
	HDC getDC()						{ return GetDC(hwnd); }

	// Reset the graphics device
	HRESULT reset();

	// Test for lost device
	HRESULT getDeviceState();

	// Clear backbuffer and BeginScene()
	HRESULT beginScene()
	{
		result = E_FAIL;
		if (device3d == NULL)
			return result;
		// clear backbuffer to backColor
		device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
		result = device3d->BeginScene();					// begin scene for drawing
		return result;
	}

	// EndScene
	HRESULT endScene()
	{
		result = E_FAIL;
		if (device3d)
			result = device3d->EndScene();
		return result;
	}

};

#endif