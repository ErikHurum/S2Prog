Readme.txt for BSP for STR710

Supported hardware:
===================
The sample project for STR710 CPU is prepared for
ST STR710 Eval boards.

Jumper settings:
================
- RAM:
  BOOTEN(SW15) = 1
  BOOT1 (SW13) = 1
  BOOT0 (SW14) = 0

- FLASH:
  BOOTEN(SW15) = 0
  BOOT1 (SW13) = ANY
  BOOT0 (SW14) = ANY

Configurations
==============

- Debug_RAM:
  This configuration is prepared for download into
  target RAM using J-Link and CSpy.
  Contains debug information.

- Debug_Flash:
  This configuration is prepared for download into
  target flash using J-Link and CSpy.
  Contains debug information.

- Release_FLASH:
  Uses the IAR flash-loader to download the program
  into Flash. To output a mot-file the user can easily
  change the linker settings.

