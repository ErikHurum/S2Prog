@ECHO OFF
GOTO START

******************************************************************************
*
* File      : Prep.bat
* Parameters: None
* Purpose   : Sets path and other environment variables as required by tool chain
*
* This file as is uses the IAR Compiler for R32C targets.
*
* It needs to be modified if the compiler is installed in a different location.
*
******************************************************************************

:START

@ECHO OFF

ECHO Prep.bat:                 Preparing environment

IF "%_PREP_R32C_%" == "_PREP_R32C_" GOTO CONT
SET _PREP_R32C_=_PREP_R32C_

SET TOOLPATH=C:\Tool\C\IAR\R32C_V130A
SET PATH=%TOOLPATH%\R32C\BIN;%TOOLPATH%\COMMON\BIN;%PATH%

:CONT

SET C_INCLUDE=%TOOLPATH%\R32C\INC
