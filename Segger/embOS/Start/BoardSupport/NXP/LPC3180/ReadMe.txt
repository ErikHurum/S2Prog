Readme.txt for BSP for LPC3180

Supported hardware:
===================
The sample project for NXP LPC3180 is prepared
to run on an NXP LPC3000 eval board,
but may be used on other target hardware as well.

Configurations
==============
- Debug_RAM:
  This configuration is prepared for download into
  internal RAM using J-Link and CSpy. A call of
  LPC3180_RAM.mac ensures that internal RAM
  is mapped at 0x00.
