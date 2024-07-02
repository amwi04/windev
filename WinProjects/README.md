Notes:

## 25/06/2024

- H
- H is for Handle with is nothing but PVIOD -> VOID *
- H is a opque pointer 
- EG: HWND, HINSTANCE, HBRUSH, HFONT, HPEN

- lpszCmdLine (long pointer zero terminated string cmd line) command line argument
- iCmdShow (int command line show)
### Hungarian Notation (by Charles Simonyii was from hungary so hungarian notation)
1. variable name should start with varibale type
2. after that 1st word should be captaial 
3. if a variable has multiple word then it should start with captial letter
4. if a variable is pointer began with p then use rule 1 to 4
5. if a variable is global then start with g 

Example: 
   ```c 
   float roi;
   // In hungarian notations
   fRateOfInterest;

    double populationgrowthrate; //global

    // In hungarian notations
    gdPopulationGrowthRate

    //pointer variable of hbrush

    phBrush

   ```

## 26/06/2024

`__stdcall` is the calling convention used for the function. This tells the compiler the rules that apply for setting up the stack, pushing arguments and getting a return value.
and who will clear memory function it self or the caller function

There are a number of other calling conventions, `__cdecl`, `__thiscall`, `__fastcall` and the wonderfully named `__declspec(naked)`. `__stdcall` is the standard calling convention for Win32 system calls.
## 1/7/2024

both calls same function __mainCRTStartup() main C runtime startup function
```
main() -> WinMain()
   |         |
   V         V 
   __mainCRTStartup()
            |
            V
         _start()
```

Window is structral and function unit og GUI programming

```
Primay header contains magic number and pointer to entry point function (WinMain)
Magic number for Windows in MZ (mark zbikoski)

                                                                Primay Header                   Stack
humam readable -> Complier   -> Data region   ->    Linker   -> Data region         -> Loader ->Data region  
.c/.cpp           Cl.exe        Text region         link.exe    Text region            Win OS   text region
                                (machine readable)              Symbol Table                    Symbol table
                                 (.obj)                         (OS understable .exe)           (now they are process in memory)        
                                 COFF(common                    PE-COFF (Portable 
                                 object file program)           executable common 
                                                                object file program)

```

stack is always in memory and its a process 

MS-DOS - 1980-1985
Single tasking/Real Mode OS

Gary Kildall -> 1970-80 => 1974 => IC 8080
Tim Patterson -> 86-DOS -> 8086
Bill Gates    -> MS-DOS
XPARC -> xerox 


## 2/7/2024

A21 gate is opened to give full protected mode 
