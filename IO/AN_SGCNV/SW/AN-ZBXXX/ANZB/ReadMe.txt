Dear Customer,

This project should serve as an "easy start" with embOS.
All pathes are relative to the project file.
You should therefore be able to copy the
entire directory (including all subdirectories)
to any location on your harddrive.

Please make sure all files are r/w.
If you have CSpy (the IAR debugger),
check out this start application by clicking
the CSpy-symbol in the task bar

Thank you for choosing embOS !

*** Using the starterkit ***
Simply modify the R-project to see some output on PORTB:

void Task0(void) {
  while (1) {
    DDRB = 0xff; PORTB ++; 
    OS_Delay (10);
  }
}
