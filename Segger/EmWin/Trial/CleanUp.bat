@ECHO OFF

ECHO CLEAN.BAT:    Deleting temporary files

FOR %%i IN (OPT, PLG, APS, NCB, DEP, MAK) DO IF EXIST *.%%i DEL *.%%i

IF "%OS%" == "Windows_NT" GOTO WinNT

DELTREE /Y Debug
DELTREE /Y Release

GOTO READY

:WinNT

IF EXIST Debug   RD Debug   /S/Q
IF EXIST Release RD Release /S/Q

:READY
