#ifndef S2BOOTLOADER
    #include "TSNIncludes.h"
    #pragma hdrstop
    #ifdef BORLAND
        #pragma package(smart_init)
    #endif

    #ifdef BORLAND
        #include <fstream.h>
    #endif
#else
    #include "BootloaderIncludes.h"
#endif

//---------------------------------------------------------------------------

TSNConfigString::TSNConfigString(void):
LineCount(1),PreviousLineCnt(1),Size(0),NumberOfBytes(0)
{
    NoMemory = false;
    DataPtr  = new char[Size+1];
    memset(DataPtr,0,Size);
    CurrentPlace    = DataPtr;
    OldPlace = DataPtr;
}

TSNConfigString::TSNConfigString(int NewSize):
LineCount(1),PreviousLineCnt(1),Size(NewSize),NumberOfBytes(0)
{
    NoMemory = false;
    DataPtr  = new char[Size];
    memset(DataPtr,0,Size);
    CurrentPlace    = DataPtr;
    OldPlace = DataPtr;
}

TSNConfigString::TSNConfigString(AnsiString buff):
LineCount(1),PreviousLineCnt(1),NumberOfBytes(0)
{
    NoMemory = false;
    Size = buff.Length();
    DataPtr  = new char[Size+1];
    memset(DataPtr,0,Size+1);
    CurrentPlace    = DataPtr;
    OldPlace = DataPtr;
    strcpy(DataPtr,buff.c_str());
}

TSNConfigString::TSNConfigString(char* Buff, int NewSize, bool pNoMemory):
LineCount(1),PreviousLineCnt(1),Size(NewSize),NumberOfBytes(0),NoMemory(pNoMemory)
{
    if (NoMemory) {
        DataPtr = Buff;
    }else{
        DataPtr  = new char[Size + 1];
        memcpy(DataPtr,Buff,Size);
    }
    DataPtr[Size] = 0;
    CurrentPlace  = DataPtr;
    OldPlace      = DataPtr;
}


TSNConfigString::~TSNConfigString(void)
{
    if (DataPtr && !NoMemory) {
        delete[] DataPtr;
        DataPtr = NULL;
    }
}

#ifdef S2TXU
bool TSNConfigString::ReadFile(char* FileName)
{
	bool Success = false;
	if ( !stricmp("Settings.s2s",(char*)FileName) ) {
		Success = FlashRead(DataPtr,NumberOfBytes);
	}
	return(Success);
}
#else
bool TSNConfigString::ReadFile(char* FileName)
{
    ifstream ConfigStream;
    ConfigStream.open(FileName,ios::in | ios::binary);
    if ( ConfigStream ) {
        LineCount= 1;
        PreviousLineCnt = 1;
        CurrentPlace    = DataPtr;
        OldPlace = DataPtr;
        // get length of file:
        ConfigStream.seekg (0, ios::end);
        NumberOfBytes = ConfigStream.tellg();
        ConfigStream.seekg (0, ios::beg);

        ConfigStream.read(DataPtr,long(NumberOfBytes));
        //NumberOfBytes = ConfigStream.gcount();
        // Ignore Ctrl Z as terminator
        int Ptr = NumberOfBytes-1;
        while ( Ptr && (DataPtr[Ptr] != 26 ) ) Ptr--;
        if ( Ptr ) {
            NumberOfBytes = Ptr;
        }
        DataPtr[NumberOfBytes] = 0;
        ConfigStream.clear();
        ConfigStream.close();
        return(true);
    }
    return(false);
}
#endif

#ifdef S2TXU
bool TSNConfigString::WriteFile(char* FileName, bool Reset)
{
    const char *FName[2] = {"Settings.s2s","Config.s2c"};
    bool Success = false;
    if ( !stricmp((char*)FName[0],(char*)FileName) ) {
        if ( Reset ) {
            Success =  FlashWriteAll((U32)DataPtr, GetSize());
        } else {
            Success =  FlashWrite((U32)DataPtr, GetSize());
        }
    } else if ( !stricmp((char*)FName[1],(char*)FileName) ) {
        SaveConfig((U32)DataPtr, GetSize());
    }
    return(Success);
}
#else
bool TSNConfigString::WriteFile(char* FileName, bool Reset=false)
{
    ofstream ConfigStream;
    if ( Reset ) {
        ConfigStream.open(FileName,ios::out | ios::binary | ios::trunc);
    } else {
        ConfigStream.open(FileName,ios::out | ios::binary);
    }
    bool StreamStatus = (bool)ConfigStream;
    if ( StreamStatus ) {
        int Size = GetSize();
        //DataPtr[Size++] = 26; // EOF mark
        //DataPtr[Size++] = 0;
		ConfigStream.write(DataPtr,Size);
        ConfigStream.clear();
        ConfigStream.close();

    }
    return(StreamStatus);
}
#endif

void TSNConfigString::SetToPreviousWord(void)
{
    LineCount = PreviousLineCnt;
    CurrentPlace    = OldPlace;
}


// Advance to next token, delimited by s:
AnsiString TSNConfigString::NextW(int &CommentErrorLine)
{
    // Can at maximum return to previous word
    PreviousLineCnt = LineCount;
    CommentErrorLine = 0;
    AnsiString TempString;
    // Are we at the end of the AnsiString??
    if ( *CurrentPlace ) {
        OldPlace       = CurrentPlace;
        char *StartPtr = CurrentPlace;
        while ( *StartPtr && isspace(*StartPtr ) ) {
            if ( *StartPtr == '\n' ) {
                LineCount++;
            }
            StartPtr++;
        }
        if ( *StartPtr ) {
            int NextPtr    = 0;
            int CommentPtr = 0;
            bool Complete = false;
            while ( StartPtr[NextPtr+CommentPtr] && !Complete ) {
				switch ( StartPtr[NextPtr+CommentPtr] ) {
					case '\r':
					case ' ' :   // ANSI White spaces
					case '\t':
					case '\v':
					case '\n':
					case '\f':
						Complete = true;
						break;
					case '/':
						// Checking next one without updating Commentptr
						switch ( StartPtr[NextPtr+CommentPtr+1] ) {
							case '/':
								{
									while ( StartPtr[NextPtr+CommentPtr]  && ( StartPtr[NextPtr+CommentPtr] != '\n') ) {
										CommentPtr++;
									}
									if ( StartPtr[NextPtr+CommentPtr] != '\n'){
										LineCount++;
									}
									Complete = true;
								}
								break;
							case '*':
								{
									int CommentStartLine = LineCount;
									int CommentCnt=1;
									CommentPtr+=2;  // We have allready checked the 2 previous without step
                                    while ( CommentCnt && StartPtr[NextPtr+CommentPtr] ) {
                                        switch ( StartPtr[NextPtr+CommentPtr] ) {
                                            case '*':
                                                if ( StartPtr[NextPtr+CommentPtr+1] == '/' ) {
                                                    CommentPtr++;
                                                    CommentCnt--;
                                                }
                                                break;
                                            case '/':
                                                if ( StartPtr[NextPtr+CommentPtr+1] == '*' ) {
                                                    CommentPtr++;
                                                    CommentCnt++;
                                                }
                                                break;
                                            case '\n':
												LineCount++;
                                                break;
                                        }
                                        CommentPtr++;
                                    }
                                    if ( !StartPtr[NextPtr+CommentPtr] ) {
                                        CommentErrorLine = CommentStartLine;
                                    }
                                    Complete = true;
                                }
                                break;
                            default:
                                TempString += StartPtr[NextPtr+CommentPtr];
                                NextPtr++;
                                break;
                        }
                        break;
                    default:
                        TempString += StartPtr[NextPtr+CommentPtr];
                        NextPtr++;
                        break;
                }
            }
            CurrentPlace      = &StartPtr[NextPtr+CommentPtr];
            // Did we find any word??
            if ( !CommentErrorLine && !NextPtr ) {
                TempString = NextWord(CommentErrorLine);
            }
        } else {
            CommentErrorLine = EOF;
        }
    } else {
        CommentErrorLine = EOF;
    }
    return(TempString);
}

// Advance to next token, delimited by s:
AnsiString TSNConfigString::NextWord(int &CommentErrorLine, int EndKey)
{
    AnsiString tmpStr = NextW(CommentErrorLine);
    if (EndKey) {
        if (CommentErrorLine) {
            CommentErrorLine = LineCount;
            SetToPreviousWord();
            tmpStr = "";
        } else {
            if ( EndKey == FindConfigKey(tmpStr) ) {
                CommentErrorLine = END_FOUND;
                tmpStr = "";
            }
        }
    }
    return tmpStr;
}

AnsiString TSNConfigString::GetRemainingLine(int &CommentErrorLine)
{
    // Can at maximum return to previous word
	PreviousLineCnt = LineCount;
    CommentErrorLine = 0;
    AnsiString TempString;
    // Are we at the end of the String??
    if ( *CurrentPlace ) {
        OldPlace   = CurrentPlace;
        char *StartPtr   = CurrentPlace;
        while ( *StartPtr && isspace(*StartPtr ) ) {
            if ( *StartPtr == '\n' ) {
                LineCount++;
                return(TempString); // Return an empty String
            } else {
                StartPtr++;
            }

        }
        if ( *StartPtr ) {
            int NextPtr    = 0;
            int CommentPtr = 0;
            bool Complete = false;
            while ( StartPtr[NextPtr+CommentPtr] && !Complete ) {
                switch ( StartPtr[NextPtr+CommentPtr] ) {
                    case '\r':
                    case '\n':
                        Complete = true;
                        break;
                    case '/':
                        // Checking next one without updating Commentptr
                        switch ( StartPtr[NextPtr+CommentPtr+1] ) {
                            case '/':
                                {

                                    while ( StartPtr[NextPtr+CommentPtr]  && ( StartPtr[NextPtr+CommentPtr] != '\n') ) {
										CommentPtr++;
                                    }
									if ( StartPtr[NextPtr+CommentPtr] == '\n'){
										//CommentPtr++;
										LineCount++;
										NextPtr++;
									}
									Complete = true;
                                }
                                break;
                            case '*':
                                {
                                    int CommentStartLine = LineCount;
									int CommentCnt=1;
                                    CommentPtr+=2;  // We have allready checked the 2 previous without step
                                    while ( CommentCnt && StartPtr[NextPtr+CommentPtr] ) {
                                        switch ( StartPtr[NextPtr+CommentPtr] ) {
                                            case '*':
                                                if ( StartPtr[NextPtr+CommentPtr+1] == '/' ) {
                                                    CommentPtr++;
                                                    CommentCnt--;
                                                }
                                                break;
                                            case '/':
                                                if ( StartPtr[NextPtr+CommentPtr+1] == '*' ) {
                                                    CommentPtr++;
                                                    CommentCnt++;
                                                }
                                                break;
                                            case '\n':
                                                LineCount++;
                                                break;
                                        }
                                        CommentPtr++;


                                    }
                                    if ( !StartPtr[NextPtr+CommentPtr] ) {
                                        CommentErrorLine = CommentStartLine;
                                    }
                                    Complete = true;
                                }
                                break;
                            case '\r':
								NextPtr++;
								break;
                            default:
                                TempString += StartPtr[NextPtr+CommentPtr];
                                NextPtr++;
                                break;
                        }
                        break;
                    default:
                        TempString += StartPtr[NextPtr+CommentPtr];
                        NextPtr++;
                        break;
                }
            }
			CurrentPlace      = &StartPtr[NextPtr+CommentPtr];
            if ( !CommentErrorLine && !NextPtr ) {
                TempString = GetRemainingLine(CommentErrorLine);
            }
        } else {
            CommentErrorLine = EOF;
        }
    } else {
        CommentErrorLine = EOF;
    }
    return(TempString);
}

AnsiString TSNConfigString::GetConfigRevisionText(int &CommentErrorLine)
{
    // Can at maximum return to previous word
    PreviousLineCnt = LineCount;
    CommentErrorLine = 0;
    // Are we at the end of the String??
    if ( *CurrentPlace ) {
        OldPlace   = CurrentPlace;
        char *EndOfTextPtr = strstr(CurrentPlace,EndConfRevText.c_str());
        if ( EndOfTextPtr) {
            char *tmpPtr       = CurrentPlace;
            while (tmpPtr < EndOfTextPtr ) {
                switch (*tmpPtr++) {
                    case '\n':
                        LineCount++;
                        break;
                    default:
                        break;
                }
            }
            AnsiString TempString(CurrentPlace,EndOfTextPtr-CurrentPlace);
            CurrentPlace = EndOfTextPtr+EndConfRevText.Length();
            return TempString;
        } else {
            CommentErrorLine = EOF;
        }
    } else {
        CommentErrorLine = EOF;
    }
    return("");
}

// Find word
bool TSNConfigString::FindWord(AnsiString myWord)
{
    int CommentErrorLine;
    AnsiString TempString;
    do {
        TempString = NextWord(CommentErrorLine);
    }while ( !CommentErrorLine && (TempString == myWord) );
    return(!CommentErrorLine);
}

// Find First Word
bool TSNConfigString::FindFirstWord(AnsiString myWord)
{
    LineCount= 1;
    PreviousLineCnt = 1;
    CurrentPlace    = DataPtr;
    OldPlace = DataPtr;
    return(FindWord(myWord));
}

// Find word
bool TSNConfigString::FindBeforeWord(AnsiString myWord)
{
    bool Found = FindWord(myWord);
    if ( Found ) {
        SetToPreviousWord();
    }
    return(Found);
}


int TSNConfigString::GetSize(void)
{
    int Size=0;
    while ( DataPtr[Size] ) Size++;
    return(Size);
}
int  TSNConfigString::GetCurrentLine(void)
{
    return LineCount;
}
AnsiString  TSNConfigString::GetCurrentLineStr(void)
{
    return AnsiString(LineCount);
}


double TSNConfigString::ReadDouble(int &CommentErrorLine, int EndKey )
{
    double DoubleValue;
    AnsiString InputKeyWord = NextWord(CommentErrorLine);
    if ( CommentErrorLine ) {
        DoubleValue = 0.0;
    } else {
        char *EndPtr;
        DoubleValue = strtod(InputKeyWord.c_str(), &EndPtr);

        // Did we reach the end of the word?
        if ( *EndPtr ) {
            // If Read until end, check if we have the END
            if ( EndKey && (EndKey == FindConfigKey(InputKeyWord) ) ) {
                CommentErrorLine = END_FOUND;
                DoubleValue = 0;
            } else {
                CommentErrorLine = LineCount;
                SetToPreviousWord();
                DoubleValue = 0;
            }
        }

    }
    return(DoubleValue);
}


long TSNConfigString::ReadLong(int &CommentErrorLine, int EndKey)
{
    long LongValue;
    AnsiString InputKeyWord = NextWord(CommentErrorLine);
    if ( CommentErrorLine ) {
        LongValue = 0;
    } else {
        char *EndPtr;
        LongValue = strtol(InputKeyWord.c_str(), &EndPtr, 10);
        // Did we reach the end of the word?
        if ( *EndPtr ) {
            // If Read until end, check if we have the END
            if ( EndKey && (EndKey == FindConfigKey(InputKeyWord) ) ) {
                CommentErrorLine = END_FOUND;
                LongValue = 0;
            } else {
                CommentErrorLine = LineCount;
                SetToPreviousWord();
                LongValue = 0;
            }
        }
    }
    return(LongValue);
}


long TSNConfigString::ReadHex(int &CommentErrorLine, int EndKey)
{
    long LongValue;
    AnsiString InputKeyWord = NextWord(CommentErrorLine);
    if ( CommentErrorLine ) {
        LongValue = 0;
    } else {
        char *EndPtr;
        LongValue = strtol(InputKeyWord.c_str(), &EndPtr, 16);
        // Did we reach the end of the word?
        if ( *EndPtr ) {
            // If Read until end, check if we have the END
            if ( EndKey && (EndKey == FindConfigKey(InputKeyWord) ) ) {
                CommentErrorLine = END_FOUND;
                LongValue = 0;
            } else {
                CommentErrorLine = LineCount;
                SetToPreviousWord();
                LongValue = 0;
            }
        }
    }
    return(LongValue);
}

long TSNConfigString::ReadInteger(int &CommentErrorLine, int EndKey)
{
    long LongValue;
    AnsiString InputKeyWord = NextWord(CommentErrorLine);
    if ( CommentErrorLine ) {
        LongValue = 0;
    } else {
        char *EndPtr;
        LongValue = strtol(InputKeyWord.c_str(), &EndPtr, 0);
        // Did we reach the end of the word?
        if ( *EndPtr ) {
            // If Read until end, check if we have the END
            if ( EndKey && (EndKey == FindConfigKey(InputKeyWord) ) ) {
                CommentErrorLine = END_FOUND;
                LongValue = 0;
            } else {
                CommentErrorLine = LineCount;
                SetToPreviousWord();
                LongValue = 0;
            }
        }
    }
    return(LongValue);
}

void TSNConfigString::AddString(AnsiString NewString)
{
    int Size =(int) NewString.Length();
    char *InsertPlace = CurrentPlace;
    memcpy((void*)CurrentPlace,NewString.c_str(),Size);
    CurrentPlace += Size;
    for ( int i = 0; i < Size; i++ ) {
        if ( InsertPlace[i] == '\n' ) {
            LineCount++;
        }
    }
}

bool TSNConfigString::Write(char *fmt, ...)
{
    va_list argptr;
    char TempBuf[BUF_SIZE];
    va_start(argptr, fmt);
    int Cnt = vsprintf(TempBuf, fmt, argptr);
    va_end(argptr);
    if ( Cnt != EOF ) {
        char *InsertPlace = CurrentPlace;
        memcpy((void*)CurrentPlace,TempBuf,Cnt);
        CurrentPlace += Cnt;
        for ( int i = 0; i < Cnt; i++ ) {
            if ( InsertPlace[i] == '\n' ) {
                LineCount++;
            }
        }
    }
    return( Cnt != EOF );
}


