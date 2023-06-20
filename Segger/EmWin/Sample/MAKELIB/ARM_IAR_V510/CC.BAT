@ECHO OFF
GOTO START

******************************************************************************
*
* File      : CC.bat
* Parameters: %1 Name of file to compile (without extension; .c is added)
* Purpose   : Compile one file and add it to the list of files to put in
*             Library
*
* This file as is uses the IAR ARM Compiler
*
******************************************************************************

:START

ECHO CC.BAT:              Compiling %1.c with IAR ARM compiler
ICCARM -D OS_LIBMODE_DP -o temp\Output\ -Oh --cpu_mode arm --endian little --cpu ARM7TDMI --interwork -e --require_prototypes --silent temp\Source\%1.c
IF ERRORLEVEL 1 PAUSE
ECHO addmod temp\Output\%1.o>>temp\Lib.DAT

