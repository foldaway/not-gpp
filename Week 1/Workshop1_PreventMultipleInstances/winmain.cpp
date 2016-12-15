#define WIN32_LEAN_AND_MEAN

#include <windows.h>

// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool AnotherInstance();
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

// Global variables
HINSTANCE hinst;

// Constants
const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Prevent Multiple";
const int  WINDOW_WIDTH = 400;		// width of window
const int  WINDOW_HEIGHT = 300;		// height of window

bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASSEX wcx;
	HWND hwnd;

	// Fill in the window class structure with parameters
	// that describe the main window
	wcx.cbSize = sizeof(wcx);					// Size of structure
	wcx.style = CS_HREDRAW | CS_VREDRAW;		// Redraw if size changes
	wcx.lpfnWndProc = WinProc;					// Points to window procedure
	wcx.cbClsExtra = 0;							// No extra class memory
	wcx.cbWndExtra = 0;							// No extra window memory
	wcx.hInstance = hInstance;					// Handle to instance
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);	// Predefined arrow
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	// Black background brush
	wcx.lpszMenuName = NULL;					// Name of menu resource
	wcx.lpszClassName = CLASS_NAME;				// Name of window class
	wcx.hIconSm = NULL;							// Small class icon

	// Register Window class
	// RegisterClassEx returns 0 on error
	if (RegisterClassEx(&wcx) == 0)				// If error
		return false;

	// Create window
	hwnd = CreateWindow(
		CLASS_NAME,					// Name of the window class
		APP_TITLE,					// Title bar text
		WS_OVERLAPPEDWINDOW,		// Window style
		CW_USEDEFAULT,				// Default horizontal position of window
		CW_USEDEFAULT,				// Default vertical position of window
		WINDOW_WIDTH,				// Width of window
		WINDOW_HEIGHT,				// Height of window
		(HWND)NULL,					// No parent window
		(HMENU)NULL,				// No menu
		hInstance,					// Handle to application instance
		(LPVOID)NULL);				// No window parameters

	// If there was an error creating the window
	if (!hwnd)
		return false;

	// Show the window
	ShowWindow(hwnd, nCmdShow);

	// Send a WM_PAINT message to the window procedure
	UpdateWindow(hwnd);
	return true;
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		// Tell windows to kill this program
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool AnotherInstance() {
	HANDLE ourMutex;

	// Attempt to create a mutex using our unique string
	ourMutex = CreateMutex(NULL, true, "Use_a_different_string_here_for_each_program_48161-XYZZY");
	
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;	// Another instance was found

	return false;		// We are the only instance
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;

	// Prevent multiple instances
	if (AnotherInstance())
		return false;

	// Create the window
	if (!CreateMainWindow(hInstance, nCmdShow))
		return false;

	// Main message loop
	int done = 0;
	while (!done) {
		// PeekMessage is a non-blocking method for checking windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Look out for quit message
			if (msg.message == WM_QUIT)
				done = 1;

			// Decode and pass messages to WinProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}