@ECHO OFF
GOTO START

******************************************************************************
*
* File      : Prep.bat
* Parameters: None
* Purpose   : Sets path and other environment variables as required by tool chain
*
* This file as is uses the Keil MDK Compiler for ARM targets.
*
******************************************************************************

:START

ECHO Prep.bat:            Preparing environment

IF "%_PREP_KEIL_%" == "_PREP_KEIL_" GOTO END
SET _PREP_KEIL_=_PREP_KEIL_

SET TOOLPATH=C:\Keil\ARM
SET PATH=%TOOLPATH%\BIN31;%PATH%

:END

