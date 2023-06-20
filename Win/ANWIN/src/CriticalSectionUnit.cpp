//---------------------------------------------------------------------------

#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>

#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "CriticalSectionUnit.h"
ANPRO10CriticalSection::ANPRO10CriticalSection(void) {
	// Create critical section and threads
	MyLock = new TCriticalSection();

}
ANPRO10CriticalSection::~ANPRO10CriticalSection(void) {
	delete MyLock;
}
void ANPRO10CriticalSection::Acquire(void) {
	MyLock->Acquire();
}
void ANPRO10CriticalSection::Release(void) {
	MyLock->Release();
}


