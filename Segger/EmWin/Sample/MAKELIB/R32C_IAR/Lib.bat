@ECHO OFF
GOTO START

******************************************************************************
*
* File      : Lib.bat
* Parameters: None
* Purpose   : Put all (object) files in linklist into the library
*
* This file as is uses the IAR Compiler for R32C targets.
*
******************************************************************************

:START

ECHO d-c R32C>Temp\Output\PARA.DAT
COPY Temp\Output\PARA.DAT+Temp\Output\OBJ.DAT Temp\Output\LIB.PAR
ECHO Q>>Temp\Output\LIB.PAR
XLIB Temp\Output\LIB.PAR

IF ERRORLEVEL 1 PAUSE

