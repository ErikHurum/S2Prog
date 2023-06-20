Readme.txt for BSP for AT91M55800

Supported hardware:
===================
The sample project for ATMEL AT91M55800 is
useable for various target boards with an
ATMEL AT91M55800 CPU
The samples were built for and tested with
an ATMEL AT91EB55 eval board

Configurations
==============
- Debug_RAM:
  This configuration is prepared for download into
  external RAM using J-Link and CSpy. A call of
  JTAG_AT91M55_RAM.mac ensures that external RAM access
  is initialized and RAM is mapped at 0x00.
  Depending on the specific target hardware,
  JTAG_AT91M55_RAM.mac,
  AT91M55_cstartup_V4.s79 and
  AT91M55_RAM.xcl
  may have to be modified to fit the memory addresses
  and sizes.

