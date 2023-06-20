//---------------------------------------------------------------------------
#pragma once
#ifndef TSNConfigStringH
#define TSNConfigStringH


enum ReadAction {
    Normal,UntilNoMore,UntilEnd
};

class TSNConfigString {
private:
    bool NoMemory;
public:

    int   Size,          // Size of allocated Memory block
    NumberOfBytes; // Number of bytes read from file

    char* DataPtr;  // Pointer to memory block
    char* CurrentPlace;     // Pointer to current place in memory block
    char* OldPlace; // Pointer to previous place in memory block
    int   PreviousLineCnt;

    TSNConfigString(void);
    TSNConfigString(int NewSize);   // Capacity
    TSNConfigString(AnsiString buff);
    TSNConfigString(char *Buff, int NewSize, bool NoMemory=false);

    ~TSNConfigString(void);

    int LineCount;

	bool ReadFile(char* FileName);
	bool WriteFile(char* FileName, bool Reset);

    void SetToPreviousWord(void);
    AnsiString NextW(int &CommentErrorLine);
    AnsiString NextWord(int &CommentErrorLine, int EndKey=0);
    AnsiString GetRemainingLine(int &CommentErrorLine);
    AnsiString GetConfigRevisionText(int &CommentErrorLine);
    bool FindWord(AnsiString myWord);
    bool FindBeforeWord(AnsiString myWord);
    bool FindFirstWord(AnsiString myWord);

    int  GetSize(void);
    int  GetCurrentLine(void);
    AnsiString  GetCurrentLineStr(void);


    double ReadDouble(int &CommentErrorLine, int EndKey=0);
    long ReadLong(int &CommentErrorLine, int EndKey=0);
    long ReadHex(int &CommentErrorLine, int EndKey=0);
    long ReadInteger(int &CommentErrorLine, int EndKey=0);

    void AddString(AnsiString NewString);
    bool Write(char *fmt, ...);

};
//---------------------------------------------------------------------------
#endif
