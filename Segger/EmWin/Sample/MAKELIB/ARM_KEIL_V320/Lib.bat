@ECHO OFF
GOTO START

******************************************************************************
*
* File      : Lib.bat
* Parameters: None
* Purpose   : Put all (object) files in linklist into the library
*
* This file is written for Keil MDK tool chain
*
******************************************************************************
:START

ECHO MAKELIB.BAT:         Creating GUI target library using IAR ARM tool-chain

REM ****************************************
REM   Create library
REM ****************************************

IF EXIST Lib\GUI_TARGET.LIB DEL Lib\GUI_TARGET.LIB
armar lib\GUI.lib -r --via temp\lib.dat
IF ERRORLEVEL 1 PAUSE
