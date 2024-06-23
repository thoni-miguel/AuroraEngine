@ECHO OFF

ECHO Do you want to generate a project for Visual Studio 2022(1) or a GNU Makefile(2)?
SET /P choice=Enter your choice:

IF %choice% == 1 GOTO VS2022
IF %choice% == 2 GOTO Makefile
IF %choice% == 3 GOTO Exit

:VS2022
call vendor\bin\premake\premake5.exe vs2022
PAUSE
EXIT

:Makefile
call vendor\bin\premake\premake5.exe gmake2
PAUSE
EXIT

:Exit
EXIT

PAUSE