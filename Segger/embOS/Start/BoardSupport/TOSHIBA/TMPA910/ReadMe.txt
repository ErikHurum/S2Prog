Readme.txt for BSP for Toshiba TMPA910 start project.
This project was built for the IAR Compiler V4.42A
and Workbench 4.7A

Supported hardware:
===================
The sample project for the TOSHIBA TMPA910 CPU
is prepared to run on a TOPAS910 eval board,
but may be used on other target hardware as well.

Configurations
==============

- Debug_SDRAM:
  This configuration may be used to debug an application using
  CSpy and J-Link.
  The application runs in SDRAM and uses a debug/profiling library.
  TMPA910_SDRAM.mac is used to initialize the SDRAM.

- Release_Flash:
  This configuration is prepared to build an output
  in Motorola format, which can be downloaded into
  external FLASH using programming tools like J-Link
  and J-Flash.

Using different target hardware may require modifications.
