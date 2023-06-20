@ECHO OFF
ECHO MakeLib.bat:              Starting build process
goto Start

******************************************************************************
*
* File      : MakeLib.bat
* Parameters: 2 (optional)
*             %1: Source path   Default: GUI
*             %2: Config path1  Default: Config
*             %3: Config path2  Default: -
* Purpose   : Generate a library of the GUI
*             It takes the GUI sources and configuration files and generates
*             a library
*
* Input:      Sources:             GUI\...\*.c
*             Configuration files: Config\*.h
* Output:     Lib\GUI.lib   (extension depends on tool chain)
*
*
* This file does not need to be modified; it does not contain any target
* dependencies.
*
******************************************************************************

:START

REM **************************************************************************
REM   Prepare environment
REM **************************************************************************

CALL PREP.BAT

REM **************************************************************************
REM   Prepare working folders
REM **************************************************************************

IF "%OS%" == "Windows_NT" GOTO WinNT_0
DELTREE /Y Temp
DELTREE /Y Lib
GOTO CONT_0
:WinNT_0
IF EXIST Temp RD Temp /S/Q
IF EXIST Lib  RD Lib /S/Q
:CONT_0
MD Temp
MD Temp\Source
MD Temp\Output
MD Lib

REM **************************************************************************
REM   Copy source files
REM **************************************************************************

IF NOT "%1" == "" SET SOURCE_PATH=%1
IF     "%1" == "" SET SOURCE_PATH=GUI
IF EXIST %SOURCE_PATH%\Core\GUI.h GOTO COPY_SOURCE
ECHO MakeLib.bat:              No GUI files!
PAUSE
:COPY_SOURCE
ECHO MakeLib.bat:              Copying source files (*.bat, *.c, *.h) from %SOURCE_PATH%

FOR %%i IN (C, BAT)    DO IF EXIST %SOURCE_PATH%\AntiAlias\*.%%i     XCOPY %SOURCE_PATH%\AntiAlias\*.%%i     Temp\Source /Q
FOR %%i IN (C, BAT)    DO IF EXIST %SOURCE_PATH%\ConvertColor\*.%%i  XCOPY %SOURCE_PATH%\ConvertColor\*.%%i  Temp\Source /Q
FOR %%i IN (C, BAT)    DO IF EXIST %SOURCE_PATH%\ConvertMono\*.%%i   XCOPY %SOURCE_PATH%\ConvertMono\*.%%i   Temp\Source /Q
FOR %%i IN (C, H, BAT) DO IF EXIST %SOURCE_PATH%\Core\*.%%i          XCOPY %SOURCE_PATH%\Core\*.%%i          Temp\Source /Q
FOR %%i IN (C, BAT)    DO IF EXIST %SOURCE_PATH%\Font\*.%%i          XCOPY %SOURCE_PATH%\Font\*.%%i          Temp\Source /Q

IF DEFINED SKIP_DRIVER GOTO SKIP_DRIVER
FOR %%i IN (C, H, BAT) DO IF EXIST %SOURCE_PATH%\DisplayDriver\*.%%i XCOPY %SOURCE_PATH%\DisplayDriver\*.%%i Temp\Source /Q
:SKIP_DRIVER

IF DEFINED SKIP_MEMDEV GOTO SKIP_MEMDEV
FOR %%i IN (C, BAT)    DO IF EXIST %SOURCE_PATH%\MemDev\*.%%i        XCOPY %SOURCE_PATH%\MemDev\*.%%i        Temp\Source /Q
:SKIP_MEMDEV

IF DEFINED SKIP_PNG GOTO SKIP_PNG
FOR %%i IN (C, H, BAT) DO IF EXIST %SOURCE_PATH%\PNG\*.%%i           XCOPY %SOURCE_PATH%\PNG\*.%%i           Temp\Source /Q
:SKIP_PNG

IF DEFINED SKIP_TTF GOTO SKIP_TTF
FOR %%i IN (C, H, BAT) DO IF EXIST %SOURCE_PATH%\TrueType\*.%%i      XCOPY %SOURCE_PATH%\TrueType\*.%%i      Temp\Source /Q
:SKIP_TTF

IF DEFINED SKIP_VNC GOTO SKIP_VNC
FOR %%i IN (C, H, BAT) DO IF EXIST %SOURCE_PATH%\VNC\*.%%i           XCOPY %SOURCE_PATH%\VNC\*.%%i           Temp\Source /Q
:SKIP_VNC

IF DEFINED SKIP_WM GOTO SKIP_WM
FOR %%i IN (C, H, BAT) DO IF EXIST %SOURCE_PATH%\Widget\*.%%i        XCOPY %SOURCE_PATH%\Widget\*.%%i        Temp\Source /Q
FOR %%i IN (C, H, BAT) DO IF EXIST %SOURCE_PATH%\WM\*.%%i            XCOPY %SOURCE_PATH%\WM\*.%%i            Temp\Source /Q
:SKIP_WM

SET SOURCE_PATH=

REM **************************************************************************
REM   Copy configuration files
REM **************************************************************************

IF NOT "%2" == "" SET CONFIG_PATH0=%2
IF     "%2" == "" SET CONFIG_PATH0=Config
IF NOT "%3" == "" SET CONFIG_PATH1=%3
IF EXIST %CONFIG_PATH0%\LCDConf.h GOTO COPY_CONFIG
IF EXIST %CONFIG_PATH1%\LCDConf.h GOTO COPY_CONFIG
ECHO MakeLib.bat:              LCDConf.h not found!
PAUSE
IF EXIST %CONFIG_PATH0%\GUIConf.h GOTO COPY_CONFIG
IF EXIST %CONFIG_PATH1%\GUIConf.h GOTO COPY_CONFIG
ECHO MakeLib.bat:              GUIConf.h not found in %CONFIG_PATH0%!
PAUSE
:COPY_CONFIG
IF EXIST %CONFIG_PATH0%\LCDConf.h COPY %CONFIG_PATH0%\LCDConf.h Temp\Source /y
IF EXIST %CONFIG_PATH1%\LCDConf.h COPY %CONFIG_PATH1%\LCDConf.h Temp\Source /y
IF EXIST %CONFIG_PATH0%\GUIConf.h COPY %CONFIG_PATH0%\GUIConf.h Temp\Source /y
IF EXIST %CONFIG_PATH1%\GUIConf.h COPY %CONFIG_PATH1%\GUIConf.h Temp\Source /y

SET CONFIG_PATH0=
SET CONFIG_PATH1=

REM **************************************************************************
REM   Compile source files
REM **************************************************************************

FOR %%i IN (Temp\Source\CC*.bat) DO CALL %%i

REM **************************************************************************
REM   Link
REM **************************************************************************

CALL LIB.bat

REM **************************************************************************
REM   Delete working folders
REM **************************************************************************

IF "%OS%" == "Windows_NT" GOTO WinNT_1
DELTREE /Y Temp
GOTO READY
:WinNT_1
IF EXIST Temp RD Temp /S/Q
:READY

