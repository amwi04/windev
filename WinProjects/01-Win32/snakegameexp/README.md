

open x64 Native Command Prompt

C:\WinProjects\01-Win32\01-Windowing\01-FirstWindow>cl.exe /c /EHsc Window.c
Microsoft (R) C/C++ Optimizing Compiler Version 19.39.33523 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

Window.c

C:\WinProjects\01-Win32\01-Windowing\01-FirstWindow>link.exe Window.obj user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
Microsoft (R) Incremental Linker Version 14.39.33523.0
Copyright (C) Microsoft Corporation.  All rights reserved.


notes:

Block Letter Words -> typedef -> HWND,LRESULT, CALLBACK,LPSTR,HINSTANCE,UINT,WPARAM,PVOID,LONG_PTR,TCHAR
				   -> struct -> WNDCLASSEX, MSG etc..
				   -> Macros -> CS_HREDRAW, CS_REDRAW, TDC_ARROW, WM_DESTROY, NULL 