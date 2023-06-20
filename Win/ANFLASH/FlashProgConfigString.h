//---------------------------------------------------------------------------
#ifndef FlashProgConfigStringH
#define FlashProgConfigStringH
//---------------------------------------------------------------------------
  #include <stdlib.h>
  #include <dinkumware\iostream.h>
  #include <dinkumware\fstream.h>
  #include <dinkumware\iomanip.h>


class FlashProgConfigString
{
public:

  int   Size,		   // Size of allocated Memory block
        NumberOfBytes; // Number of bytes read from file

  char* DataPtr;  // Pointer to memory block
  char*	CurrentPlace;	  // Pointer to current place in memory block
  char* OldPlace; // Pointer to previous place in memory block

	FlashProgConfigString(int NewSize);	// Capacity
	FlashProgConfigString(AnsiString buff);
	~FlashProgConfigString(void);


  bool ReadFile(const char* FileName);
  bool WriteFile(const char* FileName);
  int  GetSize(void);
  void Insert(int Pos,char* SubStr);

};
#endif
