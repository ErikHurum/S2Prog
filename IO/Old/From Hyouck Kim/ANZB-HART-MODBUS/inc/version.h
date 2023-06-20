/****************************************************************************
 **             - version.h -
 **
 **     This file declares the version no. and changes in the project.
 **
 **
 ***************************************************************************/

#define PROG_VERSION    100           // version of the program
#define COMP_VERSION     1            // compability with the PC on structs and com.
#define STORE_VERSION    2            // Store format in the EEPROM

/*******************************************************************************
  Revision list.

  Program:
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 31                       Released: In progress
      -
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 30                       Released: 08-mar-10
      - Add two buffer for sending EEPROM data to AD card (parallel access) with overwrite protection.
      - Asking for AD config when sending EEPROMdata to get immidiate update.
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 29                       Released: 13-jan-10
      - Correct reading of WIS sensor data when in combination with AD card on IO module
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 28                       Released: 14-oct-09
      - Uses external bus to UART(ADcard com) (ExiInt.c, RS485.c)
      - Removed Frame and Overrun count for USART com. (UsartInt.c, UsartPro.c)
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 27                       Released: 19-sep-09
      - Removed 4 of 5 nop in Write16552 and Read16552 functions to reduce time in interruptroutines
        (RS485.c)
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 26                       Released: 15-sep-09
      - Implemented stop of timers on TX complete to avoid stopping timers after 200ms (UsartInt.c)
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 25                       Released: 12-aug-09
      - Changed to while loop to avoid missing characters in CPU UART (UsartInt.c)
      - Add Overrun and Frame error counts for CPU UAST. Sending in Stack package (UsartInt.c, UsartPro.c)
      - Implement timer to start transmitt (after on-delay)(Main.c, UsartPro.c) .
      - Implement us of TXC interrupt to turn off transmitter immidiate after last char sent.(UsartInt.c)
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   V 24                       Released: 04-aug-09
      - Correct do-while loop for 16650 UAST to avoid lost interrupt and hang (ExiInt.c)
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 23                        Released: 26-mar-09
      - IAR compiler 3.11B
      - Correct loop / timeout for getting EEPROM data from AD card in (RS485.c)
      - Reads two channels on internal AD to prepare for reading 5V from ZBANA (adc.c)
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 22                        Released: 19-dec-05
      - IAR compiler 3.11A and new embOS
      - Add volatile to variables
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 21                        Released: 26-oct-05
      - Add offset and gain adjustment for each analoge channel on ANA card
      - Add communication of offset and gain and storing in EEPROM
      - Add semaphore to protect the data buffer for AN-ZB485 data
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 20                        Released: 12-oct.05
      - Adjusted AD7715 gain to 0.9995 from 1.0015
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 19                        Released: 12-jul-05
      - Forced TData.RS4.ToTargerBuffer[0] to false.
      - Forced TData.RS4.FromTargetBuffer[*][0] to false
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 18                        Released: 23-nov-04
      - Correct request of measuring data if checking for serienumber
      - Changed gain on AN-ZBANA
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 17                        Released: 23-nov-04
      - Corrected fault in the loop checking the receive buffer. Faults gave 0 pressure / temperature on ANSGVNV
      - Replaced OS_LeaveInterrupt()with OS_LeaveInterruptNoSwitch()
      - Compile with high compression on speed ( appr. half size)
      - Correct request of data if checking for serienumber
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 16                        Released: 18-nov-04
      - Add check for ready for asking for WIS ser. no
      - Add counter (16) in 16552 UART loop for exit
      - Correct request of sensor parameters
      - 40 sec loop for req of all parameters
      - Reset AD / WIS restart flag when sending once
      - Add OS_Delay after switching on power to WIS / AD and switching
        on one and one channel.
      - Add power off and on for RS485 channels if failconunt
      - Add check for packlen > 0 on package from AD card
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 15                        Released: 08-nov-04
      - Made readout of the rx buffer on 16552 on uast-error
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 14                        Released: 03-nov-04
      - Corrected WIS serial no
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 13                        Released: 01-Nov-04
      - Add code to retrieve the serial number from the WIS sensor
      - Changed packet 1161
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 12                        Released: 23-Sep-04
      - Add check on PC16552 ports for receiving data, otherwise re-init the port
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 11                        Released: 22-Sep-04
      - Updated version to Erik
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 10                        Released: 22-Sep-04
      - Increased stack on comunication, Stack: 0, 1, 10, 11
      - Correct to unsigned on fail count
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 9                        Released: 18-Sep-04
      - Correct package CMD_REQ_RS4_ADBUF
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 8                        Released: 18-Sep-04
      - Correct sending AD eeprom data
      - Add package CMD_REQ_RS4_ADBUF
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 7                        Released: 15-Sep-04
      - Correct and redesigned the watchdog function
      - No tasks at same priority
      - Remoced packet for command 1045
      - Add functonality to ask for config data and eepromdata
      - Send eeprom data to host
      -
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 6                        Released: 30-Jul-04
      - Add fail chech on port communication
      - Corrected packaged for measure and raw/cal data

  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 5                        Released: Test version only
      - Add new calibration algoritm to the AD7715 converter.
      -
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 4                        Released: 17-Mar-04
      - Use SetBit / ClrBit with dissabling interrupt
      - Corrected casting of WIS temperature
      - Implemented stack check package
      - Reduced stack size
      - Changed to 1 MHz on AD clock on AN-ZBANA
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 3                        Released: 15-Jan-04
      - Add reset status package of IO-modules to measure data package
      - Add card status package of AN-SGCNV to measure data package
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 2                        Released: 7-Jan-04
      - Add header chekcum on AN-PRO10
      - Changed baud rate to 38400
      - Add timout timer to rx on (RS485 ports) and disable int in routines using TXE bits port
      - Changed RX on time from 20 to 5 ms
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 1                        Released: Test only
      - First version
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Communication:
  V 2                         Released: Next
      -
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 1                         Released: In progress
      - First version
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Store:
  V 2                        Released: Next
      -
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  V 1                         Released: In progress
      - First version
*******************************************************************************/
