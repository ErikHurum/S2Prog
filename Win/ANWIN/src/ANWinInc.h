//---------------------------------------------------------------------------
#ifndef ANWinIncH
#define ANWinIncH
#undef _HAS_STD_BYTE
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#ifdef ANWIN
//#include <SQL_Queries.hpp>
#include "WinUart.h"

// Washtrack includes
#include "UnitOfWork.h"
#include "SQLiteAccessor.h"
#include "TWMRepository.h"
#include "TWMRunRepository.h"
#include "TankWashingException.h"

#include "GridSizer.h"

#endif

extern bool NetworkOK;
extern bool UseNetwork;
extern bool UseANWinNetwork;

#endif

