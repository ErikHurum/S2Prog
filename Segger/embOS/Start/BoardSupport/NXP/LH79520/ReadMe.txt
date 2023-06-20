Readme.txt for BSP for LH79520

Supported hardware:
===================
The sample project for LH79520 CPU is prepared for
SHARP LH79520 Eval boards.

Configurations
==============
- Debug_RAM:
  This configuration is prepared for download into 
  target RAM using J-Link and CSpy.
  Contains debug information.  
  
- Release_ROM
  Creates an out file (Motorola) which needs to be programmed
  into the flash with a 3rd party tool such as J-Flash.
  Does not contain debug information.
