Readme.txt for BSP for AT91M40xxx

Supported hardware:
===================
The sample project for ATMEL AT91M40xxx is
useable for various AT91M40xxx CPUs
It was tested on an AT91EB40A eval board
with an AR91R40008 MCU

Configurations
==============
- Debug_RAM:
  This configuration is prepared for download into
  external RAM using J-Link and CSpy. A call of
  JTAG_AT91M40.mac ensures that RAM access
  is initialized and RAM is mapped at 0x00.
  Depending on the specific target hardware,
  JTAG_AT91M40.mac,
  AT91M40_cstartup_V4.s79 and
  AT91M40_RAM.xcl
  may have to be modified to fit the memory addresses
  and sizes.

- Release_ROM:
  This configuration is prepared to build an output
  in Motorola format, which can be downloaded into
  external FLASH using 3rd party tools,
  as well as a file in simple format
  which may be programmed into target using
  CSpy with J-Link and IAR flashloader.
  Depending on the specific target hardware,
  AT91M40_cstartup_V4.s79 and
  AT91M40_ROM.xcl
  may have to be modified to fit the memory addresses
  and sizes.



