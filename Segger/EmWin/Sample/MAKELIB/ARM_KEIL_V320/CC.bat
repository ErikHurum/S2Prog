@ECHO OFF
GOTO START

******************************************************************************
*
* File      : CC.bat
* Parameters: %1 Name of file to compile (without extension; .c is added)
* Purpose   : Compile one file and add it to the list of files to put in
*             Library
*
* This file as is uses the Keil ARM Compiler
*
******************************************************************************

:START

ECHO CC.BAT:              Compiling %1.c with Keil ARM compiler
armcc --device DARMP -c -Otime  --apcs /interwork -O3 temp\Source\%1.c -otemp\Output\%1.o -I%TOOLPATH%\RV31\INC -DGUI_TRIAL_VERSION=1
IF ERRORLEVEL 1 PAUSE
ECHO temp\Output\%1.o>>temp\Lib.DAT

