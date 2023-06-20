Readme.txt for BSP for STR912

Supported hardware:
===================
The sample project for STR912 CPU is prepared for
ST STR912 Eval boards.

Tested with: IAR KS STR912-SK Rev. A
To use the UART for embOSView,
Jumper L5 has to be set in Position 2-3
to connect UART0 Tx

The sample application can also be used with the ST STR910-EVAL board.
When using this board, define STR910_EK under compiler
options to initialize the LED sample correctly.


Configurations
==============
- Debug_RAM:
  This configuration is prepared for download into
  target RAM using J-Link and CSpy.
  Contains debug information.

  Note: STR912 does not support RAM re-mapping.
  Because FLASH is always located at address 0x0
  you have to program an interrupt jump table into flash
  which allows usage of interrupts when target application
  runs in RAM.
  You can use the IAR flash loader to load the
  interrupt jump table into your flash. Select the
  STR912_JumpTable project, build it and start the CSpy
  Debugger to load the extra output into flash. The
  project also generates an additional file STR912_jumpvect.mot,
  which can be programmed into the flash with a 3rd party tool such
  as J-Flash.

  After loading the vector interrupt table into flash
  the Debug_RAM configuration works as expected.

- Debug_FLASH
  This configuration programs a debug build of your
  project into flash and may be used with J-Link.

- Release_FLASH
  This configuration programs a release build of your
  project into flash and may be used with J-Link.
  A mot file which can be used with third party tools
  is also generated.