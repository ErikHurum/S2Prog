How to compile the sample
=========================

- Copy the configuration files *Conf.h to 'Start\Config\'.

- Copy the remaining source and header files to 'Start\Application' add them to the project.

- Copy the bitmap files to 'System\Simulation\Res\'

- Change SIM_X_Init() in 'System\Simulation\SIM_X.c' to:

void SIM_X_Init() {
  SIM_SetLCDPos(30, 30);       // Define the position of the LCD in the bitmap
  SIM_SetTransColor(0xff0000); // Define the transparent color
}

- Rebuild the project.
