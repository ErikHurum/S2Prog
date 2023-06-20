//---------------------------------------------------------------------------

#ifndef FlashProgProgStringH
#define FlashProgProgStringH
//---------------------------------------------------------------------------
  #include <stdlib.h>
  #include <dinkumware\iostream.h>
  #include <dinkumware\fstream.h>
  #include <dinkumware\iomanip.h>
  #include <system.hpp>


class FlashProgProgString
{
public:

  int   Size,		   // Size of allocated Memory block
        NumberOfBytes; // Number of bytes read from file

  char* DataPtr;  // Pointer to memory block
  char*	CurrentPlace;	  // Pointer to current place in memory block
  char* OldPlace; // Pointer to previous place in memory block

	FlashProgProgString(int NewSize);	// Capacity
	FlashProgProgString(AnsiString buff);
	~FlashProgProgString(void);


  bool ReadFile(const char* FileName);
  bool WriteFile(const char* FileName);
  int  GetSize(void);

};
#endif