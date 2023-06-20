//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FlashProgConfigString.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FlashProgConfigString::FlashProgConfigString(int NewSize):
Size(NewSize),NumberOfBytes(0)
{
	DataPtr  = new char[Size];
	CurrentPlace    = DataPtr;
	OldPlace = DataPtr;
}
//---------------------------------------------------------------------------

FlashProgConfigString::FlashProgConfigString(AnsiString buff):
Size((int)buff.Length()),NumberOfBytes(0)
{
	DataPtr  = new char[Size+1];
	CurrentPlace    = DataPtr;
	OldPlace = DataPtr;
	strcpy(DataPtr,buff.c_str());
}
//---------------------------------------------------------------------------

FlashProgConfigString::~FlashProgConfigString(void)
{
	delete[] DataPtr;
}
//---------------------------------------------------------------------------

bool FlashProgConfigString::ReadFile(const char* FileName)
{
  ifstream ConfigStream;
  ConfigStream.open(FileName,ios::in | ios::binary);
  if( ConfigStream ) {
    CurrentPlace    = DataPtr;
    OldPlace = DataPtr;
    ConfigStream.read(DataPtr,Size);
    NumberOfBytes = ConfigStream.gcount();
    // Ignore Ctrl Z as terminator
    int Ptr = NumberOfBytes-1;
    while( Ptr && (DataPtr[Ptr] != 26 ) ) Ptr--;
    if( Ptr ) {
      NumberOfBytes = Ptr;
    }
    DataPtr[NumberOfBytes] = 0;
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------

bool FlashProgConfigString::WriteFile(const char* FileName)
{
  ofstream ConfigStream;
  ConfigStream.open(FileName,ios::out | ios::binary | ios::trunc);
  bool StreamStatus = ConfigStream;
  if( StreamStatus ) {
    int Size = GetSize();
    //DataPtr[Size++] = 26; // EOF mark
    //DataPtr[Size++] = 0;
    ConfigStream.write(DataPtr,Size);
  }
  return StreamStatus;
}
//---------------------------------------------------------------------------

int FlashProgConfigString::GetSize(void)
{
	int tSize=0;
	while( DataPtr[tSize++] );
	return tSize;
}
//---------------------------------------------------------------------------

void FlashProgConfigString::Insert(int Pos, char* SubStr)
{
  int SubStrLen   = strlen(SubStr);
  int CurrentSize = GetSize();
  if ( (Pos < CurrentSize) && (SubStrLen+CurrentSize < Size) ){
    memmove(&DataPtr[Pos+SubStrLen],&DataPtr[Pos],CurrentSize-Pos);
    memcpy(&DataPtr[Pos],SubStr,SubStrLen);
  }
}
//---------------------------------------------------------------------------


