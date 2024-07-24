#include <windows.h>
//#include <mmsystem.h> // play sound api which is included in windows.h

#include "Window.h"

// import libarary here instead of passing it in link.exe command line
#pragma comment(lib,"winmm.lib") // winmm is the lib required for play sound

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
	// TCHAR str[] = TEXT("Hello, world from Windev 2024");
	HBRUSH hBrush = NULL;

	static int iPaintFlags = 0; // it should retain its value across calls
	//code 
	switch (iMsg)
	{
		case WM_PAINT:
			// Get the client area rectange of our window
			GetClientRect(hwnd,&rect);	
			// hdc handle to device context
			hdc = BeginPaint(hwnd, &ps); // get the painter hdc to do our window
			// SetBkColor(hdc,RGB(0,0,0)); //tell the painter hdc to set background text color to black 
			// SetTextColor(hdc,RGB(0,255,0)); // tell hdc to set text color to green
			// DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			switch (iPaintFlags)
			{
				case 1:
					hBrush = CreateSolidBrush(RGB(255,0,0)); // creata a grey color brush
					break;
				case 2:
					hBrush = CreateSolidBrush(RGB(0,255,0)); // creata a grey color brush
					break;
				case 3:
					hBrush = CreateSolidBrush(RGB(0,0,255)); // creata a grey color brush
					break;
				case 5:
					hBrush = CreateSolidBrush(RGB(255,255,255)); // creata a grey color brush
					break;
				case 4:
					hBrush = CreateSolidBrush(RGB(0,0,0)); // creata a grey color brush
					break;
				case 6:
					hBrush = CreateSolidBrush(RGB(0,255,255)); // creata a grey color brush
					break;
				case 7:
					hBrush = CreateSolidBrush(RGB(255,0,255)); // creata a grey color brush
					break;
				case 8:
					hBrush = CreateSolidBrush(RGB(255,255,0)); // creata a grey color brush
					break;
				default:
					hBrush = CreateSolidBrush(RGB(128,128,128)); // creata a grey color brush
					break;

			} 
			//give the brush to the painter 
			SelectObject(hdc, hBrush);
			// fill client area rect with the color of the selected brush
			FillRect(hdc, &rect,hBrush);
			// release the brush
			if (hBrush != NULL)
			{
				// safe release the brush
				DeleteObject(hBrush);
				hBrush = NULL;
			}
			if (hdc != NULL) // or we can write if (hdc)
			{
				EndPaint(hwnd, &ps);
				hdc = NULL;
			}
			break;
		case WM_TIMER:
			// stop/kill the timer TIMER_1
			KillTimer(hwnd, TIMER_1);
			if (iPaintFlags > 8)
			{
				iPaintFlags = 0;
			}
			iPaintFlags++;
			InvalidateRect(hwnd, NULL, TRUE); //NULL means everthing we can use only &rect also
			// again start the timer
			SetTimer(hwnd, TIMER_1,1000,NULL);
			break;
		case WM_SIZE:
			break;
		case WM_CREATE:
			ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
			ZeroMemory((void*)&rect, sizeof(RECT));
			//start music
			PlaySound(
                MAKEINTRESOURCE(AMOD_WAVE),
                GetModuleHandle(NULL),
                SND_ASYNC | SND_LOOP | SND_RESOURCE
            );
			//setting timer TIMER_1
			SetTimer(hwnd, TIMER_1,1000,NULL);
			break;
		case WM_DESTROY:
            // stop playing the music
            PlaySound(NULL,0,0);
			PostQuitMessage(0);	// this sends 0 to while which exits the code
			break;
		default:
			break;
	}
	// Calling default window Produre
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
