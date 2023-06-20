Readme.txt for BSP for LPC2106

Supported hardware:
===================
The sample project for NXP LPC2106 is prepared
to run on an IAR LPC2106 Kickstart eval board,
but may be used on other target hardware as well.

Configurations
==============
- Debug_RAM:
  This configuration is prepared for download into
  internal RAM using J-Link and CSpy. A call of
  LPC2xxx_RAM.mac ensures that internal RAM
  is mapped at 0x00.

- Debug_FLASH:
  This configuration is prepared for debugging and
  can be downloaded into internal FLASH using J-Link
  and CSpy.
  A call of LPC2xxx_FLASH.mac ensures that
  FLASH is mapped at 0x00.

- Release_FLASH:
  This configuration is prepared to build a "release"
  output which can be downloaded into FLASH
  using CSPy and IAR Flashloader.
  A call of LPC2xxx_FLASH.mac ensures that FLASH
  is mapped at 0x00.
  A mot file which may be used with third party tools
  is also generated.

