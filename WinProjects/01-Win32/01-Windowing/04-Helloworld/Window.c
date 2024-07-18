#include <windows.h>
#include "Window.h"

//Global callback declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;	// WNDCLASSEX # windows class extended struct 
	HWND	   hwnd;
	MSG		   msg;			//Message struct
	TCHAR      szClassName[] = TEXT("MyWindow_Amod"); // TEXT is text in unicode string

	//code
	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX)); // allocate 0 in the memory

	//Initializing Window Class
	wndclass.cbSize			= sizeof(WNDCLASSEX);				   // cb stands for count of bytes
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;			   // window type STyle
	wndclass.cbClsExtra	    = 0;								   // count of bytes Class Extra information
	wndclass.cbWndExtra		= 0;								   // count of bytes Window Extra information
	wndclass.lpfnWndProc	= WndProc;							   // long pointer Function of window procedure
	wndclass.lpszClassName	= szClassName;						   // long pointer zero terminated string Class Name
	wndclass.lpszMenuName	= NULL;								   // long pointer zero terminated string Menu Name
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH); // handle to brush Background BLACK_BRUSH->gives background black -> GetStockObject returns HGDIOBJ -> GDIOBJ.DILL  
	wndclass.hInstance		= hInstance;						   // 
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);	       // handle to cursor -> LoadCursor(hinstance,Identify of default cursor) #passed null to take default instance if not we have to load .cur file # return typr HCURSOR
	wndclass.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(AMOD_ICON));	   // handle to icon -> same as cursor # return type HICON
	wndclass.hIconSm		= LoadIcon(hInstance, MAKEINTRESOURCE(AMOD_ICON));	   // handle to icon small

	//Register the above window class
	RegisterClassEx(&wndclass); // return type ATOM 

	//Create the window in Memory return type handle 32 bit unsigned int
	// this also calls WM_CREATE
	hwnd = CreateWindow(
		szClassName,			// window class name
		TEXT("Amod Wani"),		// caption bar text
		WS_OVERLAPPEDWINDOW,	// MAcro(unsingned unique int) window style overlapped window is made by 6 style WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_THICKFRAME | WS_Caption | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
		CW_USEDEFAULT,			// use default value this is for x value  
		CW_USEDEFAULT,			// use default value this is for y value
		CW_USEDEFAULT,			// use default value this is for width in pixels 
		CW_USEDEFAULT,			// use default value this is for height in pixels 
		NULL,					// this value is for parent window handle we can use null or HWND_DESKTOP
		NULL,					// this value is for menu handle null means no menu 
		hInstance,				// this process who is showing this window handle 
		NULL					// extra infomation for this window 
	);

	//Show the window on the desktop
	ShowWindow(hwnd, iCmdShow); // Show the window on the desktop second parameter how to show parameters
								// iCmdShow default value is SW_SHOWNORMAL or SW_MAXIMUM or SW_MINIMUM or SW_HIDE 

	//Update on paint window on the desktop
	UpdateWindow(hwnd);        // paint the window

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}

//window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Varibale declaration
	HDC hdc = NULL;
	static PAINTSTRUCT ps;		// Such variable which are used for other message also make them static
	static RECT rect;
	TCHAR str[] = TEXT("Hello, world from Windev 2024");
	//code 
	switch (iMsg)
	{
		case WM_PAINT:
			// Get the client area rectange of our window
			// GetClientRect(hwnd,&rect);	
			// hdc handle to device context
			hdc = BeginPaint(hwnd, &ps); // get the painter hdc to do our window
			SetBkColor(hdc,RGB(0,0,0)); //tell the painter hdc to set background text color to black 
			SetTextColor(hdc,RGB(0,255,0)); // tell hdc to set text color to green
			// tell the painter hdc 4 things 
			// which text to draw, what is the len of text to draw -1 means len of string
			// in which client area rect draw the text
			// how should i draw text 
			DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE); 
			// relase the memory pointer
			// which was allocated in BeginPaint
			EndPaint(hwnd, &ps);
			break;
		case WM_SIZE:
			GetClientRect(hwnd,&rect);	
			break;
		case WM_CREATE:
			ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
			ZeroMemory((void*)&rect, sizeof(RECT));
			break;
		case WM_DESTROY:
			PostQuitMessage(0);	// this sends 0 to while which exits the code
			break;
		default:
			break;
	}
	// Calling default window Produre
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
