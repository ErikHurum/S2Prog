Readme.txt for BSP for OkI ML674050_60 CPUs

Supported hardware:
===================
The sample project for OkI ML674050_60 CPUs is prepared
to run on the the OKI AME-51-AS eval board,
but may be used on other target hardware as well.

Configurations
==============

- Debug_RAM:
  The Debug_RAM configuration is setup to run an application from
  CSpy in target RAM using J-Link.
  To use this configuration on the AME-51-AS Evalboard, set the DIP
  switch as follows:
  ON OFF OFF ON OFF ON ON OFF (1..8)

- Debug_FLASH:
  This configuration is prepared for debugging and
  can be downloaded into internal FLASH using J-Link
  and CSpy.
  To use this configuration on the AME-51-AS Evalboard, set the DIP
  switch as follows:
  ON OFF OFF OFF OFF ON ON OFF (1..8)

- Release_FLASH:
This configuration is prepared to build a "release"
  output which can be downloaded into FLASH
  using CSPy and IAR Flashloader.
  To use this configuration on the AME-51-AS Evalboard, set the DIP
  switch as follows:
  ON OFF OFF OFF OFF ON ON OFF (1..8)
