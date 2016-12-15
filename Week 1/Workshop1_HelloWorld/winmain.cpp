#define WIN32_LEAN_AND_MEAN

#include <windows.h>

// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

// Global variable
HINSTANCE hinst;

// Constants
const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Hello World";   // title bar text
const int  WINDOW_WIDTH = 400;             // width of window
const int  WINDOW_HEIGHT = 400;             // height of window

bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;

	// Fill in the window class structure wiht parameters
	// that describes the main window
	wcx.cbSize = sizeof(wcx);								// size structure
	wcx.style = CS_HREDRAW | CS_VREDRAW;					// redraw if size changes
	wcx.lpfnWndProc = WinProc;								// points to window procedure
	wcx.cbClsExtra = 0;										// no extra class memory
	wcx.cbWndExtra = 0;										// no extra windows memory
	wcx.hInstance = hInstance;								// handle to instance
	wcx.hIcon = NULL;								
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);				// predefined arrow
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);// black background brush
	wcx.lpszMenuName = NULL;								// name of menu resource
	wcx.lpszClassName = CLASS_NAME;							// name of window class
	wcx.hIconSm = NULL;										// small class icon

	// Register the windows class
	// RegisterClassEx return 0 on error
	if (RegisterClassEx(&wcx) == 0)			// if error
		return false;

	// Create Window
	hwnd = CreateWindow(
		CLASS_NAME,											// name of the window class
		APP_TITLE,											// title bar text
		WS_OVERLAPPEDWINDOW,								// window style
		CW_USEDEFAULT,										// default horizontal position of winodow
		CW_USEDEFAULT,										// default vertical position of window
		WINDOW_WIDTH,										// width of window
		WINDOW_HEIGHT,										// height of window
		(HWND)NULL,											// no parent window
		(HMENU)NULL,										// no menu
		hInstance,											// handle to application instance
		(LPVOID)NULL);										// no window parameter

	// if there was an error creating the window
	if (!hwnd)
		return false;

	// Show the window
	ShowWindow(hwnd, nCmdShow);

	// Send a WM_PAINT msg 
	UpdateWindow(hwnd);
	return true;		
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			// tell Windows to kill this program
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	MSG msg;

	//Create the window
	if (!CreateMainWindow(hInstance, nCmdShow))
		return false;

	// main message loop
	int done = 0;
	while (!done)
	{
		// PeekMessage is a non_blocking method for checking for Windows Messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//look for quite message
			if (msg.message == WM_QUIT)
				done = 1;

			//decode and pass messages onto WinProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return  msg.wParam;
}