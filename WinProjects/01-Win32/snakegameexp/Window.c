#include <windows.h>
//#include <mmsystem.h> // play sound api which is included in windows.h
#include <math.h>
#include "Window.h"
#include <stdio.h>

// import libarary here instead of passing it in link.exe command line
#pragma comment(lib,"winmm.lib")

//Global callback declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int euclidean_distance(
	int ,int ,int ,int ,int ,int ,int ,int
);

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SIZE_SNAKE 10
#define LENGTH_SNAKE 10

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;	 
	HWND	   hwnd;
	MSG		   msg;			
	TCHAR      szClassName[] = TEXT("MyWindow_Amod"); 

	//code
	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));

	//Initializing Window Class
	wndclass.cbSize			= sizeof(WNDCLASSEX);				   
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;			   
	wndclass.cbClsExtra	    = 0;
	wndclass.cbWndExtra		= 0;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.lpszClassName	= szClassName;
	wndclass.lpszMenuName	= NULL;
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);  
	wndclass.hInstance		= hInstance; 
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(AMOD_ICON));
	wndclass.hIconSm		= LoadIcon(hInstance, MAKEINTRESOURCE(AMOD_ICON));

	RegisterClassEx(&wndclass); 

	hwnd = CreateWindow(
		szClassName,			// window class name
		TEXT("Amod Wani"),		// caption bar text
		WS_OVERLAPPEDWINDOW,	// MAcro(unsingned unique int) window style overlapped window is made by 6 style WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_THICKFRAME | WS_Caption | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
		0,//CW_USEDEFAULT,			// use default value this is for x value  
		0,//CW_USEDEFAULT,			// use default value this is for y value
		WINDOW_WIDTH,			// use default value this is for width in pixels 
		WINDOW_HEIGHT,			// use default value this is for height in pixels 
		NULL,					// this value is for parent window handle we can use null or HWND_DESKTOP
		NULL,					// this value is for menu handle null means no menu 
		hInstance,				// this process who is showing this window handle 
		NULL					// extra infomation for this window 
	);

	ShowWindow(hwnd, iCmdShow); 
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}

//window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) // 0 >, 1v , 2< , 3^, 4 ., 5 restart
{
	// Varibale declaration
	HDC hdc = NULL;
	static PAINTSTRUCT ps;
	static RECT rect;
	HBRUSH hBrush = NULL;
	static int direction = 0; // 0 >, 1v , 2< , 3^, 4 ., 5 restart

	static int left_top_x;
	static int left_top_y;
	static int right_bottom_x;
	static int right_bottom_y;
	static int x_move = 0; 
	static int y_move = 0;
	static int restart;
	static int snake_size = 1;
	static int snake_body[WINDOW_HEIGHT*WINDOW_WIDTH/10][4];
	static int frame = 0;
	static int left_top_x_food;
	static int left_top_y_food;
	static int right_bottom_x_food;
	static int right_bottom_y_food;
	TCHAR str[255];
	TCHAR debug[255];
	static int just = 0;
	switch (iMsg)
	{
		case WM_PAINT:
			GetClientRect(hwnd,&rect);	
			hdc = BeginPaint(hwnd, &ps);
			
			SetBkColor(hdc,RGB(0,0,0)); 
			SetTextColor(hdc,RGB(255,255,255));
			wsprintf(str,TEXT("Score: %d"),snake_size-1);
			DrawText(hdc, str, -1, &rect, DT_LEFT | DT_SINGLELINE);

			hBrush = CreateSolidBrush(RGB(255,0,0)); 
			SelectObject(hdc, hBrush);
			for (int i=1; i<snake_size; i++)
			{			
				snake_body[i][0] = snake_body[i-1][0];
				snake_body[i][1] = snake_body[i-1][1];
				snake_body[i][2] = snake_body[i-1][2];
				snake_body[i][3] = snake_body[i-1][3];
				Rectangle(hdc,snake_body[i][0],snake_body[i][1],snake_body[i][2],snake_body[i][3]);
			}
			snake_body[0][0] = (WINDOW_WIDTH/2) - (SIZE_SNAKE/2) + x_move;
			snake_body[0][1] = (WINDOW_HEIGHT/2) - (SIZE_SNAKE/2) + y_move;
			snake_body[0][2] = (WINDOW_WIDTH/2) + (SIZE_SNAKE/2) + x_move;
			snake_body[0][3] = (WINDOW_HEIGHT/2) + (SIZE_SNAKE/2) + y_move;
			Rectangle(hdc,snake_body[0][0],snake_body[0][1],snake_body[0][2],snake_body[0][3]);
			if (
				euclidean_distance(
					snake_body[0][0],snake_body[0][1],snake_body[0][2],snake_body[0][3],
					left_top_x_food,left_top_y_food,right_bottom_x_food,right_bottom_y_food
				) < SIZE_SNAKE 
			)
			{
				left_top_x_food = rand() % WINDOW_WIDTH-10;
				left_top_y_food = rand() % WINDOW_HEIGHT-10;
				right_bottom_x_food = left_top_x_food + SIZE_SNAKE;
				right_bottom_y_food = left_top_y_food + SIZE_SNAKE;
				snake_size = snake_size + 1;
			}
			hBrush = CreateSolidBrush(RGB(0,255,0)); 
			SelectObject(hdc, hBrush);
			Rectangle(hdc,left_top_x_food,left_top_y_food,right_bottom_x_food,right_bottom_y_food);
			if (hBrush != NULL)
			{
				DeleteObject(hBrush);
				hBrush = NULL;
			}
			if (hdc != NULL) // or we can write if (hdc)
			{
				EndPaint(hwnd, &ps);
				hdc = NULL;
			}
			break;
		case WM_KEYDOWN:
			switch(LOWORD(wParam))
			{
				case VK_RIGHT:
					if (direction != 2)
					{
						direction = 0;
					}
				break;
				case VK_LEFT:
					if (direction !=0)
					{
						direction = 2;
					}
				break;
				case VK_UP:
					if (direction != 1)
					{
						direction = 3;
					}
				break;
				case VK_DOWN:
					if (direction != 3)
					{
						direction = 1;
					}
				break;
				break;
				default:
				break;
			}
			break;
		case WM_TIMER:
			KillTimer(hwnd, TIMER_1);
			if (direction == 0)
			{
				x_move = x_move + SIZE_SNAKE;
				if (snake_body[0][2] >= WINDOW_WIDTH - 15)
				{
					direction = 4;
				}
			}
			if (direction == 1)
			{
				y_move = y_move + SIZE_SNAKE;
				if (snake_body[0][3] >= WINDOW_HEIGHT - 40)
				{
					direction = 4;
				}
			}
			if (direction == 2)
			{
				x_move = x_move - SIZE_SNAKE;
				if (snake_body[0][0] <= 0)
				{
					direction = 4;
				}
			}
			if (direction == 3)
			{
				y_move = y_move - SIZE_SNAKE;
				if (snake_body[0][1] <= 0)
				{
					direction = 4;
				}
			}
			if (direction == 4)
			{
            	PlaySound(NULL,0,0);
				restart = MessageBox(
					NULL,
					TEXT("Restart"),
					TEXT("Game Ended"),
					MB_OK
				);
				if (restart == IDOK) 
				{
					direction = 5;
				}
			}
			if (direction == 5)
			{
				x_move = 1;
				y_move = 1;
				direction = 0;
				PlaySound(
                	MAKEINTRESOURCE(AMOD_WAVE),
                	GetModuleHandle(NULL),
                	SND_ASYNC | SND_LOOP | SND_RESOURCE
            	);
				snake_size = 1;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, TIMER_1,100,NULL);
			break;
		case WM_SIZE:
			break;
		case WM_CREATE:
			ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
			ZeroMemory((void*)&rect, sizeof(RECT));
			left_top_x_food = rand() % WINDOW_WIDTH;
			left_top_y_food = rand() % WINDOW_HEIGHT;
			right_bottom_x_food = left_top_x_food + SIZE_SNAKE;
			right_bottom_y_food = left_top_y_food + SIZE_SNAKE;
			//start music
			PlaySound(
                MAKEINTRESOURCE(AMOD_WAVE),
                GetModuleHandle(NULL),
                SND_ASYNC | SND_LOOP | SND_RESOURCE
            );
			SetTimer(hwnd, TIMER_1,1,NULL);
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

int euclidean_distance(
	int left_top_x,int left_top_y,int right_bottom_x,int right_bottom_y,
	int left_top_x_food,int left_top_y_food,int right_bottom_x_food,int right_bottom_y_food
)
{
	int d = sqrt(pow(left_top_x - left_top_x_food ,2) + pow(left_top_y - left_top_y_food,2)); 
	int d1 = sqrt(pow(right_bottom_x - right_bottom_x_food ,2) + pow(right_bottom_y - right_bottom_y_food,2)); 
	if (d > d1) return d1;
	else return d;
}
