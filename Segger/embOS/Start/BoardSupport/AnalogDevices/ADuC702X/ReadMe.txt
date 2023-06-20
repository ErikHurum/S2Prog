Readme.txt for BSP for ADuC702x

Supported hardware:
===================
The sample project for ADI 702x CPUs is prepared for
Analog devices ADuC702x Eval boards and may be used 
for ADuC7019, ADuC7020..27 CPUs.

Configurations
==============
- Debug_RAM:
  This configuration is prepared for download into 
  target RAM using J-Link and CSpy. A call of 
  ADuC702x_RAM.mac ensures that RAM is mapped at 0x00.

- Debug_FLASH:
  This configuration is prepared for download into 
  target FLASH using J-Link and CSpy. A call of 
  ADuC702x_FLASH.mac ensures that FLASH is mapped 
  at 0x00.

- Release_FLASH:
  This configuration is prepared for download into 
  target FLASH using J-Link and CSpy. A call of 
  ADuC702x_FLASH.mac ensures that FLASH is mapped 
  at 0x00.
