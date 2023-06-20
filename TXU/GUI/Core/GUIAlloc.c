/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2007  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.14 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIAlloc.C
Purpose     : Dynamic memory management
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <string.h>           /* for memcpy, memset */

#include "GUI_Protected.h"
#include "GUIDebug.h"

#if (GUI_SELECT_ALLOC == 0)

/*********************************************************************
*
*       Internal memory management
*
**********************************************************************
*/

#ifndef GUI_ALLOC_ALLOC

#if GUI_ALLOC_SIZE==0
  #error GUI_ALLOC_SIZE needs to be > 0 when using this module
#endif

/*********************************************************************
*
*       Defines, config defaults
*
**********************************************************************
*/

/* Permit automatic defragmentation when necessary */
#ifndef GUI_ALLOC_AUTODEFRAG
  #define GUI_ALLOC_AUTODEFRAG 1
#endif

#ifndef GUI_BLOCK_ALIGN        /* 2 means 4 bytes, 1 means 2 bytes      */
  #define GUI_BLOCK_ALIGN 2    /* 1 can be used on 16-bit CPUs and CPUs */
#endif                         /* which do not require aligned 32-bit   */
                               /* values (such as x86)                  */ 
#ifndef GUI_ALLOC_LOCATION
  #define GUI_ALLOC_LOCATION
#endif

#ifndef GUI_MEM_ALLOC          /* Allows us in some systems to place the GUI memory */
  #define GUI_MEM_ALLOC        /* in a different memory space ... eg "__far"        */
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define HMEM2PTR(hMem) (void*)&GUI_Heap.abHeap[_aBlock[hMem].Off]

#if GUI_MAXBLOCKS >= 256
  #define HANDLE U16
#else
  #define HANDLE U8
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef union {
  int aintHeap[GUI_ALLOC_SIZE / 4];   /* Required for proper alignement */
  U8  abHeap[GUI_ALLOC_SIZE];
} GUI_HEAP;

typedef struct {
  GUI_ALLOC_DATATYPE Off;  /* Offset of memory area          */
  GUI_ALLOC_DATATYPE Size; /* Usable size of allocated block */
  HANDLE Next;             /* Next handle in linked list     */
  HANDLE Prev;
} BLOCK;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

GUI_MEM_ALLOC GUI_HEAP GUI_Heap GUI_ALLOC_LOCATION;         /* Public for debugging only */

static BLOCK _aBlock[GUI_MAXBLOCKS];

struct {
  int       NumUsedBlocks, NumFreeBlocks, NumFreeBlocksMin; /* For statistical purposes only */
  GUI_ALLOC_DATATYPE NumUsedBytes,  NumFreeBytes,  NumFreeBytesMin;
} GUI_ALLOC;

static char _IsInitialized;
static int  _LockCnt;
static int  _FirstFreeHandle = 1;
static int  _MaxRequestPercent = 90;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Size2LegalSize
*
* Return value:
*   Legal allocation size
*/
static GUI_ALLOC_DATATYPE _Size2LegalSize(GUI_ALLOC_DATATYPE size) {
  return (size + ((1 << GUI_BLOCK_ALIGN) - 1)) & ~((1 << GUI_BLOCK_ALIGN) - 1);
}
  
/*********************************************************************
*
*       _GetSize
*/
static GUI_ALLOC_DATATYPE _GetSize(GUI_HMEM  hMem) {
  return _aBlock[hMem].Size;
}

/*********************************************************************
*
*       _Free
*/
static void _Free(GUI_HMEM hMem) {
  int Next, Prev;
  GUI_ALLOC_DATATYPE Size;
  GUI_DEBUG_LOG1("\nGUI_ALLOC_Free(%d)", hMem);
  /* Do some error checking ... */
  #if GUI_DEBUG_LEVEL>0
    /* Block not allocated ? */
    if (_aBlock[hMem].Size == 0) {
      GUI_DEBUG_ERROROUT("GUI_ALLOC_Free(): Invalid hMem");
      return;
    }
  #endif
  Size = _aBlock[hMem].Size;
  #ifdef WIN32
    GUI_MEMSET(&GUI_Heap.abHeap[_aBlock[hMem].Off], 0xcc, Size);
  #endif
  GUI_ALLOC.NumFreeBytes += Size;
  GUI_ALLOC.NumUsedBytes -= Size;
  _aBlock[hMem].Size = 0;
  if (_FirstFreeHandle > hMem) {
    _FirstFreeHandle = hMem;
  }
  Next = _aBlock[hMem].Next;
  Prev = _aBlock[hMem].Prev;
  _aBlock[Prev].Next = Next;
  if (Next) {
    _aBlock[Next].Prev = Prev;
  }
  GUI_ALLOC.NumFreeBlocks++;
  GUI_ALLOC.NumUsedBlocks--;
}

/*********************************************************************
*
*       _FindFreeHandle
*
* Return value:
*   Free handle
*/
static GUI_HMEM _FindFreeHandle(void) {
  int i;
  for (i = _FirstFreeHandle; i < GUI_MAXBLOCKS; i++) {
    if (_aBlock[i].Size == 0) {
      _FirstFreeHandle = i;
      return i;
    }
  }
  GUI_DEBUG_ERROROUT1("Insufficient memory handles configured (GUI_MAXBLOCKS == %d (See GUIConf.h))", GUI_MAXBLOCKS);
  return GUI_HMEM_NULL;
}

/*********************************************************************
*
*       _FindHole
*
* Return value:
*   Index of memory hole (if available)
*   -1 if not available
*/
static GUI_HMEM _FindHole(GUI_ALLOC_DATATYPE Size) {
  int i, iNext;
  for (i = 0; (iNext = _aBlock[i].Next) != 0; i = iNext) {
    GUI_ALLOC_DATATYPE NumFreeBytes;
    NumFreeBytes = _aBlock[iNext].Off - (_aBlock[i].Off + _aBlock[i].Size);
    if (NumFreeBytes >= Size) {
      return i;
    }
  }
  /* Check last block */
  if (GUI_ALLOC_SIZE - (_aBlock[i].Off + _aBlock[i].Size) >= Size) {
    return i;
  }
  return -1;
}

/*********************************************************************
*
*       _CreateHole
*
* Return value:
*   Offset to the memory hole (if available)
*   -1 if not available
*/
static GUI_HMEM _CreateHole(GUI_ALLOC_DATATYPE Size) {
  int i, iNext;
  int r = -1;
  for (i=0; (iNext =_aBlock[i].Next) !=0; i= iNext) {
    GUI_ALLOC_DATATYPE NumFreeBytes;
    NumFreeBytes = _aBlock[iNext].Off- (_aBlock[i].Off+_aBlock[i].Size);
    if (NumFreeBytes < Size) {
      GUI_ALLOC_DATATYPE NumBytesBeforeBlock;
      NumBytesBeforeBlock = _aBlock[iNext].Off - (_aBlock[i].Off + _aBlock[i].Size);
      if (NumBytesBeforeBlock) {
        U8 * pData;
        pData = &GUI_Heap.abHeap[_aBlock[iNext].Off];
        memmove(pData - NumBytesBeforeBlock, pData, _aBlock[iNext].Size);
        _aBlock[iNext].Off -=NumBytesBeforeBlock;
      }
    } else {
      break;
    }
  }
  /* Check last block */
  if (GUI_ALLOC_SIZE - (_aBlock[i].Off + _aBlock[i].Size) >= Size) {
    r = i;
  }
  return r;
}

/*********************************************************************
*
*       _CheckInit
*/
static void _CheckInit(void) {
  if (!_IsInitialized) {
    GUI_ALLOC_Init();
  }
}

/*********************************************************************
*
*       _GetNumFreeBytes
*/
static GUI_ALLOC_DATATYPE _GetNumFreeBytes(void) {
  if (_LockCnt) {
    return GUI_ALLOC_GetMaxSize();
  } else {
    return GUI_ALLOC.NumFreeBytes;  
  }
}

/*********************************************************************
*
*       _Alloc
*/
static GUI_HMEM _Alloc(GUI_ALLOC_DATATYPE size) {
  GUI_ALLOC_DATATYPE Off;
  int Next;
  GUI_HMEM hMemNew, hMemIns;
  _CheckInit();
  size = _Size2LegalSize(size);
  /* Check if memory is available at all ...*/
  if (size > _GetNumFreeBytes()) {
    GUI_DEBUG_WARN1("GUI_ALLOC_Alloc: Insufficient memory configured (Trying to alloc % bytes)", size);
    return 0;
  }
  /* Locate free handle */
  if ((hMemNew = _FindFreeHandle()) == 0) {
    return 0;
  }
  /* Locate or Create hole of sufficient size */
  hMemIns = _FindHole(size);
  #if GUI_ALLOC_AUTODEFRAG
    if (hMemIns == -1) {
      if (_LockCnt == 0) {
        hMemIns = _CreateHole(size);
      }
    }
  #endif
  /* Occupy hole */
  if (hMemIns == -1) {
    GUI_DEBUG_ERROROUT1("GUI_ALLOC_Alloc: Could not allocate %d bytes",size);
    return 0;
	}
  Off = _aBlock[hMemIns].Off + _aBlock[hMemIns].Size;
  Next = _aBlock[hMemIns].Next;
  _aBlock[hMemNew].Size  = size;
  _aBlock[hMemNew].Off   = Off;
  if ((_aBlock[hMemNew].Next  = Next) >0) {
    _aBlock[Next].Prev = hMemNew;  
  }
  _aBlock[hMemNew].Prev  = hMemIns;
  _aBlock[hMemIns].Next  = hMemNew;
  /* Keep track of number of blocks and av. memory */
  GUI_ALLOC.NumUsedBlocks++;
  GUI_ALLOC.NumFreeBlocks--;
  if (GUI_ALLOC.NumFreeBlocksMin > GUI_ALLOC.NumFreeBlocks) {
    GUI_ALLOC.NumFreeBlocksMin = GUI_ALLOC.NumFreeBlocks;
  }
  GUI_ALLOC.NumUsedBytes += size;
  GUI_ALLOC.NumFreeBytes -= size;
  if (GUI_ALLOC.NumFreeBytesMin > GUI_ALLOC.NumFreeBytes) {
    GUI_ALLOC.NumFreeBytesMin = GUI_ALLOC.NumFreeBytes;
  }
  return hMemNew;
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_ALLOC_Init
*/
void GUI_ALLOC_Init(void) {
  GUI_DEBUG_LOG("\nGUI_ALLOC_Init...");
  GUI_ALLOC.NumFreeBlocksMin = GUI_ALLOC.NumFreeBlocks = GUI_MAXBLOCKS - 1;
  GUI_ALLOC.NumFreeBytesMin  = GUI_ALLOC.NumFreeBytes  = GUI_ALLOC_SIZE;
  GUI_ALLOC.NumUsedBlocks    = 0;
  GUI_ALLOC.NumUsedBytes     = 0;
  _aBlock[0].Size = (1 << GUI_BLOCK_ALIGN);  /* Occupy minimum for a block */
  _aBlock[0].Off  = 0;
  _aBlock[0].Next = 0;
  _IsInitialized  = 1;
}

/*********************************************************************
*
*       GUI_ALLOC_AllocNoInit
*/
GUI_HMEM GUI_ALLOC_AllocNoInit(GUI_ALLOC_DATATYPE Size) {
  GUI_HMEM hMem;
  if (Size == 0) {
    return (GUI_HMEM)0;
  }
  GUI_LOCK();
  GUI_DEBUG_LOG2("\nGUI_ALLOC_AllocNoInit... requesting %d, %d avail", Size, GUI_ALLOC.NumFreeBytes);
  hMem = _Alloc(Size);
  GUI_DEBUG_LOG1("\nGUI_ALLOC_AllocNoInit : Handle", hMem);
  GUI_UNLOCK();
  return hMem;
}

/*********************************************************************
*
*       GUI_ALLOC_h2p
*/
void * GUI_ALLOC_h2p(GUI_HMEM  hMem) {
  GUI_ASSERT_LOCK();
  #if GUI_DEBUG_LEVEL > 0
    if (!hMem) {
      GUI_DEBUG_ERROROUT("\n"__FILE__ " GUI_ALLOC_h2p: illegal argument (0 handle)");
      return 0;
    }
    if (_aBlock[hMem].Size == 0) {
      GUI_DEBUG_ERROROUT("Dereferencing free block");
    }

  #endif
  return HMEM2PTR(hMem);
}

/*********************************************************************
*
*       GUI_ALLOC_GetNumFreeBytes
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetNumFreeBytes(void) {
  _CheckInit();
  return GUI_ALLOC.NumFreeBytes;
}

/*********************************************************************
*
*       GUI_ALLOC_GetNumFreeBlocks
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetNumFreeBlocks(void) {
  _CheckInit();
  return GUI_ALLOC.NumFreeBlocks;
}

/*********************************************************************
*
*       GUI_ALLOC_GetNumUsedBytes
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetNumUsedBytes(void) {
  _CheckInit();
  return GUI_ALLOC.NumUsedBytes;
}

/*********************************************************************
*
*       GUI_ALLOC_GetNumUsedBlocks
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetNumUsedBlocks(void) {
  _CheckInit();
  return GUI_ALLOC.NumUsedBlocks;
}

/*********************************************************************
*
*       GUI_ALLOC_GetMaxSize
*
* Purpose:
*   Returns the biggest available blocksize (without relocation).
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetMaxSize(void) {
  GUI_ALLOC_DATATYPE r = 0;
  GUI_ALLOC_DATATYPE NumFreeBytes;
  int i, iNext;

  GUI_LOCK();
  _CheckInit();
  for (i = 0; (iNext =_aBlock[i].Next) != 0; i = iNext) {
    NumFreeBytes = _aBlock[iNext].Off - (_aBlock[i].Off + _aBlock[i].Size);
    if (NumFreeBytes > r) {
      r = NumFreeBytes;
    }
  }
  /* Check last block */
  NumFreeBytes = (GUI_ALLOC_SIZE - (_aBlock[i].Off + _aBlock[i].Size));
  if (NumFreeBytes > r) {
    r = NumFreeBytes;
  }
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_ALLOC_RequestSize
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_RequestSize(void) {
  GUI_ALLOC_DATATYPE MaxSize;
  GUI_LOCK();
  MaxSize = GUI_ALLOC_GetMaxSize();
  if ((U32)MaxSize > 0x400000) {
    MaxSize = (MaxSize / 100) * _MaxRequestPercent;
  } else {
    MaxSize = (MaxSize * _MaxRequestPercent) / 100;
  }
  GUI_UNLOCK();
  return MaxSize;
}

/*********************************************************************
*
*       GUI_ALLOC_Lock
*
* Purpose:
*   The function increments the lock counter. If the lock counter is >0
*   the internal memory management should not shift allocated memory.
*/
void GUI_ALLOC_Lock(void) {
  _LockCnt++;
}

/*********************************************************************
*
*       GUI_ALLOC_Unlock
*
* Purpose:
*   The function decrements the lock counter. If the lock counter is >0
*   the internal memory management should not shift allocated memory.
*/
void GUI_ALLOC_Unlock(void) {
  _LockCnt--;
}

#else

/*********************************************************************
*
*       External memory management functions
*
* The functions below will generate code only if the GUI memory
* management is not used (GUI_ALLOC_ALLOC defined).
*
* Note:
* The memory block allocated is bigger than the requested one, as we
* store some add. information (size of the memory block) there.
*
**********************************************************************
*/

typedef struct {
  union {
    GUI_ALLOC_DATATYPE Size;
    int Dummy;               /* Needed to guarantee alignment on 32 / 64 bit CPUs */
  } Info;      /* Unnamed would be best, but is not supported by all compilers */
} INFO;

/*********************************************************************
*
*       _GetSize
*/
static GUI_ALLOC_DATATYPE _GetSize(GUI_HMEM  hMem) {
  INFO * pInfo;
  pInfo = (INFO *)GUI_ALLOC_H2P(hMem);
  return pInfo->Info.Size;
}

/*********************************************************************
*
*       _Free
*/
static void _Free(GUI_HMEM  hMem) {
  GUI_ALLOC_FREE(hMem);
}

/*********************************************************************
*
*       GUI_ALLOC_AllocNoInit
*/
GUI_HMEM GUI_ALLOC_AllocNoInit(GUI_ALLOC_DATATYPE Size) {
  GUI_HMEM hMem;
  if (Size == 0) {
    return (GUI_HMEM)0;
  }
  hMem= GUI_ALLOC_ALLOC(Size + sizeof(INFO));
  /* Init info structure */
  if (hMem) {
    INFO * pInfo;
    pInfo = (INFO *)GUI_ALLOC_H2P(hMem);
    pInfo->Info.Size = Size;
  }
  return hMem;
}

/*********************************************************************
*
*       GUI_ALLOC_h2p
*/
void* GUI_ALLOC_h2p(GUI_HMEM  hMem) {
  U8 * p;
  p = (U8*)GUI_ALLOC_H2P(hMem);    /* Pointer to memory block from memory manager */
  p += sizeof(INFO);               /* Convert to pointer to usable area */
  return p;
}

/*********************************************************************
*
*       GUI_ALLOC_GetMaxSize
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetMaxSize(void) {
  return GUI_ALLOC_GETMAXSIZE();
}

/*********************************************************************
*
*       GUI_ALLOC_RequestSize
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_RequestSize(void) {
  return GUI_ALLOC_GETMAXSIZE();
}

/*********************************************************************
*
*       GUI_ALLOC_Lock
*/
void GUI_ALLOC_Lock(void) {
}

/*********************************************************************
*
*       GUI_ALLOC_Unlock
*/
void GUI_ALLOC_Unlock(void) {
}

/*********************************************************************
*
*       GUI_ALLOC_Init
*/
void GUI_ALLOC_Init(void) {
  #ifdef GUI_ALLOC_INIT
    GUI_ALLOC_INIT();
  #endif
}

#endif

/*********************************************************************
*
*       Public code, common memory management functions
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_ALLOC_GetSize
*
*  Parameter
*    hMem      Handle of the memory block. A 0-handle is permitted; return value is 0 in this case.
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetSize(GUI_HMEM  hMem) {
  GUI_ALLOC_DATATYPE r;

  r = 0;
  if (hMem) {
    r = _GetSize(hMem);
  }
  return r;
}

/*********************************************************************
*
*       GUI_ALLOC_Free
*/
void GUI_ALLOC_Free(GUI_HMEM hMem) {
  if (hMem == GUI_HMEM_NULL) { /* Note: This is not an error, it is permitted */
    return;
  }
  GUI_LOCK();
  GUI_DEBUG_LOG1("\nGUI_ALLOC_Free(%d)", hMem);
  _Free(hMem);
  GUI_UNLOCK();
}


/*********************************************************************
*
*       GUI_ALLOC_FreePtr
*/
void GUI_ALLOC_FreePtr(GUI_HMEM *ph) {
  GUI_LOCK();
  GUI_ALLOC_Free(*ph);
  *ph =0;
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_ALLOC_FreePtrArray
*/
void GUI_ALLOC_FreePtrArray(GUI_HMEM * pArray, int NumElems) {
  int i;
  for (i = 0; i < NumElems; i++) {
    GUI_ALLOC_FreePtr(&pArray[i]);
  }
}

#else

void GUI_Alloc_C(void);   /* Avoid empty object files */
void GUI_Alloc_C(void) {}

#endif /* (GUI_SELECT_ALLOC == 0) */

/*************************** End of file ****************************/
