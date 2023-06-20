Readme.txt for BSP for STR750

Supported hardware:
===================
The sample project for STR750 CPU is prepared for
ST STR750 Eval boards.

Configurations
==============

- Debug_RAM:
  This configuration is prepared for download into
  target RAM using J-Link and CSpy.
  Contains debug information.
  The switches for Boot option have to be set to SRAM
  SW1 Boot0: 0
  SW2 Boot1: 1

- Debug_Flash:
  This configuration is prepared for download into
  target flash using J-Link and CSpy.
  Contains debug information.
  The switches for Boot option have to be set to Flash
  SW1 Boot0: 0
  SW2 Boot1: 0

- Release_FLASH:
  Uses the IAR flash-loader to download the program
  into Flash.
  A mot-file which can be used by third party tools
  is also generated.
  The switches for Boot option have to be set to Flash
  SW1 Boot0: 0
  SW2 Boot1: 0

