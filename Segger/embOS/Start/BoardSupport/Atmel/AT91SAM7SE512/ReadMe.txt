Readme.txt for BSP for AT91SAM7SE512

Supported hardware:
===================
The sample project for ATMEL AT91SAM7SE512 is prepared
to run on an ATMEL AT91SAM7SE512-EK eval board,
but may be used on other target hardware as well.

Configurations
==============
- Debug_RAM:
  This configuration is prepared for download into 
  internal RAM using J-Link and CSpy. A call of 
  ATSAM7SE512_RAM.mac ensures that internal RAM
  is mapped at 0x00.

- Debug_FLASH:
  This configuration is prepared for debugging and
  can be downloaded into internal FLASH using J-Link
  and CSpy.
  A call of AT91SAM7SE512_FLASH.mac ensures that 
  FLASH is mapped at 0x00.

- Release_FLASH:
  This configuration is prepared to build a "release"
  output which can be downloaded into FLASH
  using CSPy and IAR Flashloader.
  A call of AT91SAM7SE512_FLASH.mac ensures that FLASH
  is mapped at 0x00.


