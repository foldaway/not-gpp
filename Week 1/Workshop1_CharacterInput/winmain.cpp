#define WIN32_LEAN_AND_MEAN

#include <windows.h>

// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

// Global variables
HINSTANCE hinst;
HDC hdc;							// handle to device context
TCHAR ch = ' ';						// character entered
RECT rect;							// rectangle structure
PAINTSTRUCT ps;						// used in WM_PAINT

// Constants
const char CLASS_NAME[] = "Keyboard";
const char APP_TITLE[] = "Character Input";
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

LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		// Tell windows to kill this program
		PostQuitMessage(0);
		return 0;

	case WM_CHAR:
		switch (wParam) {
		case 0x08:					// backspace
		case 0x09:					// tab
		case 0x0A:					// linefeed
		case 0x0D:					// carriage return
		case 0x1B:					// escape
			MessageBeep((UINT)-1);	// Beep but do not display
			return 0;

		default:								// Displayable character
			ch = (TCHAR)wParam;					// Get the character
			InvalidateRect(hwnd, NULL, TRUE);	// Force WM_PAINT
			return 0;
		}

	case WM_PAINT:	// The window needs to be redrawn
		hdc = BeginPaint(hwnd, &ps);	// Get handle to device context
		GetClientRect(hwnd, &rect);		// Get the window rectangle
		// Display the character
		TextOut(hdc, rect.right / 2, rect.bottom / 2, &ch, 1);
		EndPaint(hwnd, &ps);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;

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