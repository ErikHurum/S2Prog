Readme.txt for BSP for AT91SAM9261
This project requires IAR Compiler 4.41A
Workbench 4.7A which includes the Flash loader for the
ATMEL AT91SAM9261-EK eval board

Supported hardware:
===================
The sample project for ATMEL AT91SAM9261 is prepared
to run on an ATMEL AT91SAM9261-EK eval board,
but may be used on other target hardware as well.

Configurations
==============
- Debug_iRAM:
  This configuration may be used to debug an application using
  CSpy and J-Link.
  The application runs in internal RAM.
  AT91SAM9261_iRAM.mac maps the RAM at 0x00.

- Debug_Flash:
  This configuration may be used to debug an application using
  CSpy and J-Link.
  The application runs in internal RAM,
  but is downloaded into the dataflash of the Evalboard,
  using IAR CSPy with Flash-loader.
  AT91SAM9261_Flash.mac ensures the bootloader
  finishes its work after reset.

- Release_Flash:
  This configuration is prepared to build an output
  in Motorola format, which can be downloaded into
  external FLASH using 3rd party tools,
  as well as a file in simple format
  which may be programmed into target using
  CSpy with J-Link and IAR flashloader.
  The application is loaded into the internal SRAM
  and therefore the total size is limited to 160KB.

- Debug_SDRAM:
  This configuration may be used to debug an application using
  CSpy and J-Link.
  The application runs in SDRAM.
  AT91SAM9261_SDRAM.mac is used to initialize the SDRAM.

- Release_SDRAM:
  This configuration may be used to generate a release Version
  which contains the application and a bootloader.
  The generated output file can be programmed into the DataFlash
  of the AT91SAM9261-EK eval board.
  After reset, the booloader will load the application into the SDRAM
  and then start the application.
  The application size may be up to 2MByte.

Using different target hardware may require modifications.
