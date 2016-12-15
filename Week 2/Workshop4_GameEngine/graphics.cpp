#include "graphics.h"

// Constructor
Graphics::Graphics() {
	direct3d = NULL;
	device3d = NULL;
	fullscreen = false;
	width = GAME_WIDTH;    // width & height are replaced in initialize()
	height = GAME_HEIGHT;
	backColor = SETCOLOR_ARGB(255, 0, 0, 128); // Dark blue
}


// Destructor
Graphics::~Graphics() {
	releaseAll();
}

// Release all
void Graphics::releaseAll() {
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}

void Graphics::initD3Dpp() {
	try {
		ZeroMemory(&d3dpp, sizeof(d3dpp));				// fill the structure with 0
		// fill in the parameters we need
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullscreen)									// if fullscreen
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;	// 24 bit color
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	// use desktop setting
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing D3D presentation parameters"));
	}
}

void Graphics::initialize(HWND hw, int w, int h, bool full) {
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;

	//initialize Direct3D
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

	initD3Dpp();	// init D3D presentation parameters

	// determine if graphics card supports harware texturing and lighting and vertex 
	// shaders
	D3DCAPS9 caps;
	DWORD behavior;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	// If device doesn't support HW T&L or doesn't support 1.1 vertex 
	// shaders in hardware, then switch to software vertex processing.
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	// use software only processing
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;	// use hardware only processing

	//create Direct3D device
	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		behavior,
		&d3dpp,
		&device3d);

	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));
}

// Display the backbuffer
HRESULT Graphics::showBackbuffer() {
	result = E_FAIL;    // default to fail, replace on success

	// Display backbuffer to screen
	result = device3d->Present(NULL, NULL, NULL, NULL);

	return result;
}

// Test for lost device
HRESULT Graphics::getDeviceState() {
	result = E_FAIL;	// Default to fail, replace on success
	if (device3d == NULL)
		return result;

	result = device3d->TestCooperativeLevel();
	return result;
}

// Reset the graphics device
HRESULT Graphics::reset() {
	result = E_FAIL;					// Default to fail, replace on success
	initD3Dpp();						// Init D3D presentation parameters
	result = device3d->Reset(&d3dpp);	// Attempt to reset graphics device
	return result;
}
