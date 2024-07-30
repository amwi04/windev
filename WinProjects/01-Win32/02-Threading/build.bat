cls

del *.obj

del *.exe

cl.exe /c /EHsc /D UNICODE Window.c

rc.exe Window.rc

link.exe Window.obj Window.res user32.lib gdi32.lib kernel32.lib  /SUBSYSTEM:WINDOWS 