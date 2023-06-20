Readme.txt for BSP for AT91SAM9260

Supported hardware:
===================
The sample project for ATMEL AT91SAM9260 is prepared
to run on an ATMEL AT91SAM9260-EK eval board,
but may be used on other target hardware as well.

Configurations
==============
- Debug_SIM:
  This configuration may be used to debug an application using
  CSpy simulator debugger.
  The OS timer interrupt is simulated by the macro file
  AT91SAM9260_SIM.mac

- Debug_SDRAM:
  The Debug_SDRAM configuration is setup to load the
  application into external SDRAM
  using CSpy and J-Link.
  The macro file AT91SAM9260_SDRAM.mac
  initializes the SDRAM controller and SDRAM.

Using different target hardware may require modifications.

