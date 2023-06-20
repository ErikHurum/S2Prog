@ECHO OFF
GOTO START

******************************************************************************
*
* File      : CC.bat
* Parameters: %1 Name of file to compile (without extension; .c is added)
* Purpose   : Compile one file and add it to the list of files to put in
*             Library
*
* This file as is uses the IAR Compiler for R32C targets.
*
******************************************************************************

:START

ECHO                           Compiling %1.c

ICCR32C --silent -e -o Temp\Output\ --double=32 --code_model=f --data_model=f -D NDEBUG --fp_model=full -Ohs --align_func=1 Temp\Source\%1.c

IF ERRORLEVEL 1 PAUSE

ECHO f-m Temp\Output\%1,Lib\GUI,,>>Temp\Output\OBJ.DAT

