#include <windows.h>
#include "Window.h"

//Global callback declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global thread function declarations
DWORD WINAPI ThreadProc1(LPVOID);
DWORD WINAPI ThreadProc2(LPVOID);

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
	// variable declaration
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;
	//code 
	switch (iMsg)
	{
		case WM_LBUTTONDOWN:
			MessageBox(
				NULL, // parent window we can use hwnd
				TEXT("clicked"), // LPCTSTR (long pointer constant string) window message
				TEXT("Messgae tytle"), //LPCTSTR window title
				MB_OK // button to show in window
			);
			break;
		case WM_CREATE:
			hThread1 = CreateThread(
				NULL,								// type-> LPSECURITY_ATTRIBUTES (ponter to security structures) upto WIndows NT it was vaild. its dealng with inheritance and security
				0,									// type-> DWORD -> Thread stack size (0 means default size)
				(LPTHREAD_START_ROUTINE)ThreadProc1,// type-> LPTHREAD_START_ROUTINE (register your thread fucntion name)
				(LPVOID) hwnd,						// type-> LPVOID (parementers which need to br passed to thread fucntion)
				0,									//type-> DWORD (how to behave 0 means once register run you can also create a macro CREATE_SUSPENDED to run later)
				NULL								//type-> LPWORD (UNique ID) this is handled by OS
			);
			hThread2 = CreateThread(
				NULL,								// type-> LPSECURITY_ATTRIBUTES (ponter to security structures) upto WIndows NT it was vaild. its dealng with inheritance and security
				0,									// type-> DWORD -> Thread stack size (0 means default size)
				(LPTHREAD_START_ROUTINE)ThreadProc2,// type-> LPTHREAD_START_ROUTINE (register your thread fucntion name)
				(LPVOID) hwnd,						// type-> LPVOID (parementers which need to br passed to thread fucntion)
				0,									//type-> DWORD (how to behave 0 means once register run you can also create a macro CREATE_SUSPENDED to run later)
				NULL								//type-> LPWORD (UNique ID) this is handled by OS
			);
			break; 
		case WM_DESTROY:
			if (hThread2)
			{
				CloseHandle(hThread2);
				hThread2 = NULL;
			}
			if (hThread1)
			{
				CloseHandle(hThread1);
				hThread1 = NULL;
			}
			PostQuitMessage(0);	// this sends 0 to while which exits the code
			break;
		default:
			break;
	}
	// Calling default window Produre
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

// defining thread proc 1
DWORD WINAPI ThreadProc1(LPVOID Param)
{
	// variable
	HDC hdc = NULL;	
	ULONG i = 0L;
	TCHAR str[255]; 
	
	// code

	hdc = GetDC((HWND) Param);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc,RGB(0,255,0));
	for (i = 0; i <ULONG_MAX;i++) 
	{
		wsprintf(str,TEXT("Incrementing: %lu"),i);
		TextOut(hdc,5,5,str,wcslen(str));
	}
	if (hdc)
	{
		ReleaseDC((HWND)Param,hdc);
		hdc = NULL;
	}
	return (0);

}

// deine thread proc 2
DWORD WINAPI ThreadProc2(LPVOID Param)
{
	// variable
	HDC hdc = NULL;	
	ULONG i = ULONG_MAX;
	TCHAR str[255]; 
	
	// code

	hdc = GetDC((HWND) Param);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc,RGB(255,0,0));
	for (i=ULONG_MAX; i>=0 ;i--)   // ULONG_MAX is 2^32
	{
		wsprintf(str,TEXT("Decrementing: %lu"),i);
		TextOut(hdc,5,25,str,wcslen(str));
	}
	if (hdc)
	{
		ReleaseDC((HWND)Param,hdc);
		hdc = NULL;
	}
	return 0;

}