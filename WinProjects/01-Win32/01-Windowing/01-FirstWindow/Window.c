#include <windows.h>

//Global callback declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// LRESULT -> Long_ptr -> long
// CALLBACK -> --stdcall -> -far -pascal
// WndProc # function name
// HWND -> HANDLE -> PVOID -> VOID *
// UINT -> Unsigned INT
// WPARAM -> WORD -> Unsigned INT
// LPARAM -> Long_ptr -> long

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdLine, int iCmdShow)
{
	//WINAPI -> --stdcall -> -far -pascal
	//WinMain # function name
	//HINSTANCE # handle to process instance -> VOID *
	//LPSTR # long ptr to str -> char **

	WNDCLASSEX wndclass;	// WNDCLASSEX # windows class extended struct 
	HWND	   hwnd;
	MSG		   msg;			//Message struct
	TCHAR      szClassName[] = TEXT("MyWindow_Amod");

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
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	   // handle to icon -> same as cursor # return type HICON
	wndclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);	   // handle to icon small

	//Register the above window class
	RegisterClassEx(&wndclass);

	//Create the window in Memory
	hwnd = CreateWindow(
		szClassName,
		TEXT("Amod Wani"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//Show the window on the desktop
	ShowWindow(hwnd, iCmdShow);

	//Update on paint window on the desktop
	UpdateWindow(hwnd);

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
	//code 
	switch (iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
	}
	// Calling default window Produre
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
