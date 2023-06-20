//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FlashProgProgString.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FlashProgProgString::FlashProgProgString(int NewSize):
Size(NewSize),NumberOfBytes(0)
{
	DataPtr  = new char[Size];
	CurrentPlace    = DataPtr;
	OldPlace = DataPtr;
}
//---------------------------------------------------------------------------

FlashProgProgString::FlashProgProgString(AnsiString buff):
Size((int)buff.Length()),NumberOfBytes(0)
{
	DataPtr  = new char[Size+1];
	CurrentPlace    = DataPtr;
	OldPlace = DataPtr;
	strcpy(DataPtr,buff.c_str());
}
//---------------------------------------------------------------------------

FlashProgProgString::~FlashProgProgString(void)
{
	delete[] DataPtr;
}
//---------------------------------------------------------------------------

bool FlashProgProgString::ReadFile(const char* FileName)
{
  FILE *InFile;
  InFile = fopen(FileName, "rb");
  if ( InFile ){
    int PosCnt = 0;
    while(!feof(InFile)){
      unsigned char MyChar;
      fread(&DataPtr[PosCnt++], 1, 1, InFile);
    }
    NumberOfBytes = PosCnt;
    DataPtr[NumberOfBytes] = 0;
    fclose(InFile);
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------

bool FlashProgProgString::WriteFile(const char* FileName)
{
  ofstream ProgStream;
  ProgStream.open(FileName,ios::out | ios::binary | ios::trunc);
  bool StreamStatus = ProgStream;
  if( StreamStatus ) {
    int Size = GetSize();
    //DataPtr[Size++] = 26; // EOF mark
    //DataPtr[Size++] = 0;
    ProgStream.write(DataPtr,Size);
  }
  return StreamStatus;
}
//---------------------------------------------------------------------------

int FlashProgProgString::GetSize(void)
{
	int Size=NumberOfBytes;
	return Size;
}
//---------------------------------------------------------------------------


