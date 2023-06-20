//#include <windows.h>
#include <tchar.h>
#include <assert.h>
#include <stdio.h>
#include "MBT.h"
#define DEFAULT_PORT             502
#define DEFAULT_SERVER_NAME      _T("172.17.5.90")
#define DEFAULT_PROTOCOL         TRUE /* TCP */
#define DEFAULT_REQUEST_TIMEOUT  1000   /* in ms */
LONG ret;
char pWriteBuffer[] = "This is a small test message.\n";
bool received;
void WINAPI rcb(
   IN HANDLE hSocket,         // socket handle
   IN DWORD callbackContext,  // callback context, handed over at the call
   IN LONG errorCode,         // result of the read operation
   IN BYTE tableType,         // type of MODBUS/TCP tables(MODBUSTCP_TABLE_xxx)
   IN WORD dataStartAddress,  // start address of the registers or coils to be
                              // read
   IN WORD numRead,           // number of the registers or coils to be read
   IN WORD numBytes,          // number of the bytes to be read
   IN LPBYTE pReadBuffer      // memory section with the data to be written
   )
{
  int i;
  printf( "\nread callback called:\n"
          "\tcontext: %lu\n"
          "\terror code: %ld\n"
          "\ttable type: %d\n"
          "\tdata start address: %d\n"
          "\tnumber of read registers/coils: %d\n"
          "\tnumber of read bytes: %d\n"
          "\tread bytes: ",
          callbackContext,
          errorCode,
          tableType,
          dataStartAddress,
          numRead,
          numBytes
          );
  if( errorCode == S_OK )
  {
    for( i = 0; i < numBytes; ++i )
    {
      printf( "%d ", pReadBuffer[i] );
    }
  }
  printf( "\n" );
  received = true;
}
void WINAPI wcb(
   IN HANDLE hSocket,         // socket handle
   IN DWORD callbackContext,  // callback context, handed over at the call
   IN LONG errorCode,         // result of the write operation
   IN BYTE tableType,         // type of MODBUS/TCP tables(MODBUSTCP_TABLE_xxx)
                              // output registers or output coils
   IN WORD dataStartAddress,  // start address of the registers or coils to be
                              // written
   IN WORD numWrite,          // number of the registers or coils to be written
   IN LPBYTE pWriteBuffer     // memory section with the data to be written
   )
{
  int i;
  int numBytes;
  printf( "\nwrite callback called:\n"
          "\tcontext: %lu\n"
          "\terror code: %ld\n"
          "\ttable type: %d\n"
          "\tdata start address: %d\n"
          "\tnumber of written registers/coils: %d\n"
          "\twritten bytes: ",
          callbackContext,
          errorCode,
          tableType,
          dataStartAddress,
          numWrite
          );
  if( errorCode == S_OK )
  {
    switch( tableType )
    {
        case MODBUSTCP_TABLE_OUTPUT_REGISTER:
            numBytes = 2 * numWrite;
            break;
        case MODBUSTCP_TABLE_OUTPUT_COIL:
            numBytes = (numWrite + 7) / 8;
            break;
    }
    for( i = 0; i < numBytes; ++i )
    {
      printf( "%d ", pWriteBuffer[i] );
    }
  }
  printf( "\n" );
  received = true;
}
void WINAPI esrcb(
   IN HANDLE hSocket,         // socket handle
   IN DWORD callbackContext,  // callback context, handed over at the call
   IN LONG errorCode,         // result of the read operation
   IN BYTE tableType,         // type of MODBUS/TCP tables(MODBUSTCP_TABLE_xxx)
   IN WORD dataStartAddress,  // start address of the registers or coils to be
                              // read
   IN WORD numRead,           // number of the registers or coils to be read
   IN WORD numBytes,          // number of the bytes to be read
   IN LPBYTE pReadBuffer      // memory section with the data to be written
   )
{
  int i;
  printf( "\nexception status read callback called:\n"
          "\tcontext: %lu\n"
          "\terror code: %ld\n"
          "\ttable type: %d\n"
          "\tdata start address: %d\n"
          "\tnumber of read registers/coils: %d\n"
          "\tnumber of read bytes: %d\n"
          "\tread bytes: ",
          callbackContext,
          errorCode,
          tableType,
          dataStartAddress,
          numRead,
          numBytes
          );
  if( errorCode == S_OK )
  {
    for( i = 0; i < numBytes; ++i )
    {
      printf( "%d ", pReadBuffer[i] );
    }
  }
  printf( "\n" );
  received = true;
}
int main(int argc, char* argv[])
{
  HANDLE hSocket;
  int i = 1234;
  int ch;
  BYTE pWriteBuffer[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  BYTE pWriteBuffer2[6] = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };
  BYTE pReadBuffer[6];
  ret = MBTInit();
  if( ret == S_OK )
  {
    ret = MBTConnect( DEFAULT_SERVER_NAME, DEFAULT_PORT, DEFAULT_PROTOCOL,
                      DEFAULT_REQUEST_TIMEOUT, &hSocket );
  }
  if( ret == S_OK )
  {
    received = false;
    ret = MBTWriteRegisters(
                hSocket,
                0x0000,
                3,
                (LPBYTE) pWriteBuffer,
                wcb,
                i
                );
  }
  if( ret == S_OK )
  {
    while( !received )
    {
      Sleep( 100 );
    }
  }
  if( ret == S_OK )
  {
    received = false;
    ret = MBTReadRegisters(
                hSocket,
                MODBUSTCP_TABLE_OUTPUT_REGISTER,
                0x0200,
                3,
                NULL,
                rcb,
                i
                );
  }
  if( ret == S_OK )
  {
    while( !received )
    {
      Sleep( 100 );
    }
  }
  if( ret == S_OK )
  {
    received = false;
    ret = MBTWriteCoils(
                hSocket,
                0x0000,
                6,
                (LPBYTE) pWriteBuffer,
                wcb,
                i
                );
  }
  if( ret == S_OK )
  {
    while( !received )
    {
      Sleep( 100 );
    }
  }
  if( ret == S_OK )
  {
    received = false;
    ret = MBTReadCoils(
                hSocket,
                MODBUSTCP_TABLE_OUTPUT_COIL,
                0x0200,
                6,
                NULL,
                rcb,
                i
                );
  }
  if( ret == S_OK )
  {
    while( !received )
    {
      Sleep( 100 );
    }
  }
  if( ret == S_OK )
  {
    received = false;
    // read from a connected socket
    ret = MBTReadExceptionStatus(
      hSocket,         // handle of the connected socket
      NULL,            // memory section from which the data are read
                       // (NULL at asynchronous call)
      esrcb,           // C-callback function, called after termination
                       // of asynchronous reading (NULL at synchronous
                       // call)
      i                // context, handed over to the asynchronous
                       // (callback function (0 at synchronous call)
   );
  }
  if( ret == S_OK )
  {
    while( !received )
    {
      Sleep( 100 );
    }
  }
  printf( "press <RETURN> !\n" );
  scanf( "%c", &ch );
  //****************** Sync calls ********************************************
  if( ret == S_OK )
  {
    printf( "\n\n\n****************** Sync calls ******************\n\n" );
    ret = MBTWriteRegisters(
                hSocket,
                0x0000,
                3,
                (LPBYTE) pWriteBuffer2,
                NULL,
                0
                );
  }
  if( ret == S_OK )
  {
    ret = MBTReadRegisters(
                hSocket,
                MODBUSTCP_TABLE_OUTPUT_REGISTER,
                0x0200,
                3,
                pReadBuffer,
                NULL,
                0
                );
  }
  if( ret == S_OK )
  {
    printf( "\nWrite/Read registers: " );
    for( i = 0; i < 2 * 3; ++i )
    {
      printf( "%d ", pReadBuffer[i] );
    }
    ret = MBTWriteCoils(
                hSocket,
                0x0000,
                6,
                (LPBYTE) pWriteBuffer2,
                NULL,
                0
                );
  }
  if( ret == S_OK )
  {
    ret = MBTReadCoils(
                hSocket,
                MODBUSTCP_TABLE_OUTPUT_COIL,
                0x0200,
                6,
                pReadBuffer,
                NULL,
                0
                );
  }
  if( ret == S_OK )
  {
    printf( "\nWrite/Read coils: " );
    for( i = 0; i < (6 + 7) / 8; ++i )
    {
      printf( "%d ", pReadBuffer[i] );
    }
    ret = MBTReadExceptionStatus(
      hSocket,         // handle of the connected socket
      pReadBuffer,     // memory section from which the data are read
                       // (NULL at asynchronous call)
      NULL,            // C-callback function, called after termination
                       // of asynchronous reading (NULL at synchronous
                       // call)
      0                // context, handed over to the asynchronous
                       // (callback function (0 at synchronous call)
    );
  }
  if( ret == S_OK )
  {
    printf( "\nRead exception status: " );
    for( i = 0; i < 1; ++i )
    {
      printf( "%d ", pReadBuffer[i] );
    }
  }
  if( ret == S_OK )
  {
    ret = MBTDisconnect( hSocket );
  }
  if( ret == S_OK )
  {
    ret = MBTExit();
  }
  if( ret != S_OK )
  {
    fprintf( stderr, "### Error No %ld\n", ret );
  }
  printf( "\npress <RETURN> !\n" );
  scanf( "%c", &ch );
  return 0;
}
