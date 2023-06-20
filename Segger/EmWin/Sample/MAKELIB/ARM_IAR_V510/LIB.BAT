@ECHO OFF
GOTO START

******************************************************************************
*
* File      : Lib.bat
* Parameters: None
* Purpose   : Put all (object) files in linklist into the library
*
* This file is written for IAR ARM tool chain
*
******************************************************************************
:START

ECHO MAKELIB.BAT:         Creating GUI target library using IAR ARM tool-chain

REM ****************************************
REM   Create library
REM ****************************************

ECHO create Lib\GUI_TARGET.a > temp\LIB.script
COPY temp\LIB.script+temp\Lib.dat temp\LIB.script
ECHO save>>temp\LIB.script
ECHO end>>temp\LIB.script
ar -M<temp\LIB.script
