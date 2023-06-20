Readme.txt for BSP for TMS470R1B1M

Supported hardware:
===================
The sample project for TMS470R1B1M CPU is prepared for
TI TMS470R1B1M Eval boards.

Configurations
==============

- Debug_RAM:
  This configuration is prepared for download into
  target RAM using J-Link and CSpy.
  Contains debug information.
  A call of the debugger macro file
  TMS470R1B1M_RAM.mac is required to map the internal
  RAM at 0x00.

- Debug_Flash:
  This configuration is prepared for download into
  target flash using J-Link and CSpy.
  Contains debug information.
  Use TMS470R1B1M_FLASH.mac only if needed to unlock FLASH.
  The internal RAM is used at address 0x400000.
  If this RAM location shall to be modified, the startup
  code in Startup_TMS470R1B1M.s79 has to be modified

- Release_FLASH:
  Uses the IAR flash-loader to download the program
  into Flash. A mot-file which may be used with
  third party tools is generated also.
  Use TMS470R1B1M_FLASH.mac only if needed to unlock FLASH.
  The internal RAM is used at address 0x400000.
  If this RAM location shall to be modified, the startup
  code in Startup_TMS470R1B1M.s79 has to be modified
