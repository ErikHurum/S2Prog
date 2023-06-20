Readme.txt for BSP for AT91RM9200

Supported hardware:
===================
The sample project for ATMEL AT91RM9200 is prepared
to run on an ATMEL AT91RM9200-EK eval board

Configurations
==============
- Debug_iRAM:
  Downloads the program into internal RAM using J-Link.
  Internal RAM  is mapped at 0x00.

- Debug_SDRAM:
  Downloads the program into external RAM using J-Link.

- Debug_FLASH:
  Downloads the program into external FLASH using J-Link.
  FLASH is mapped at 0x00.
  Allows debugging in flash.

- Release_FLASH:
  Downloads the program into external FLASH using J-Link.
  FLASH is mapped at 0x00.
