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
File        : GUIAllocX.c
Purpose     : Dynamic memory management
----------------------------------------------------------------------
*/

#include <stddef.h>
#include <string.h>

#include "GUI_Protected.h"
#include "GUIDebug.h"

#if (GUI_SELECT_ALLOC == 1)

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
*       Defines
*
**********************************************************************
*/
#ifndef   GUI_ALLOC_LOCATION
  #define GUI_ALLOC_LOCATION
#endif

#ifndef   GUI_MEM_ALLOC        /* Allows us in some systems to place the GUI memory */
  #define GUI_MEM_ALLOC        /* in a different memory space ... eg "__far"        */
#endif

#define NET(x)   (U32)(x - sizeof(MEM_TAG) - sizeof(U32))
#define GROSS(x) (U32)(x + sizeof(MEM_TAG) + sizeof(U32))

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_HEAP
*
* Purpose:
*   32 bit aligned memory block to be managed by the memory management.
*/
typedef union {
  U32 aDummy[GUI_ALLOC_SIZE / 4]; /* Required for proper alignement */
  U8  abHeap[GUI_ALLOC_SIZE];
} GUI_HEAP;

/*********************************************************************
*
*       MEM_TAG
*
* Purpose:
*   Memory information structure.
*/
typedef struct {
  U32 Block; /* Index of block which refers to this memory block */
  U32 Size;  /* Gross size of memory block */
} MEM_TAG;

/*********************************************************************
*
*       FREE_TAG
*
* Purpose:
*   Used to link free blocks of memory. Locations of these tags are the
*   unused memory areas of free blocks.
*/
typedef struct FREE_TAG FREE_TAG;
typedef struct TAG      TAG;

struct FREE_TAG {
  FREE_TAG * pNext; /* Pointer to next free tag */
  FREE_TAG * pPrev; /* Pointer to previous free tag */
  TAG      * pTag;  /* Pointer to memory tag */
};

/*********************************************************************
*
*       TAG
*/
struct TAG {
  MEM_TAG  MemTag;
  FREE_TAG FreeTag;
};

/*********************************************************************
*
*       BLOCK
*/
typedef struct {
  #if GUI_DEBUG_LEVEL > 0
    U8 InUse;
  #endif
  union {
    GUI_HMEM NextBlock; /* If block is free, handle of next block */
    TAG *    pTag;      /* If block is in use, pointer to memory tag */
  } u;
} BLOCK;

/*********************************************************************
*
*       FREE_MEM
*/
typedef struct {
  U32        MinSize;       /* Minimum size of memory blocks linked in the list */
  FREE_TAG * pFirstFreeTag; /* Pointer to first tag */
} FREE_MEM;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static int _LockCnt;       /* If >0 moving of memory is not allowed */
static U8  _IsInitialized; /* 1 if already initialized */
static U32 _NumFreeBytes;  /* Number of free bytes */
static U32 _NumFreeBlocks; /* Number of free blocks */

static int  _MaxRequestPercent = 90;

static GUI_MEM_ALLOC GUI_HEAP GUI_Heap GUI_ALLOC_LOCATION; /* Heap to be managed */

static BLOCK    _aBlock[GUI_MAXBLOCKS]; /* Array of blocks */
static GUI_HMEM _FirstFreeBlock;        /* Index of first free block */

static FREE_MEM _aFreeMem[16];          /* List of free memory */

/*********************************************************************
*
*       Static code, internal
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetMinIndex
*
* Purpose:
*   Calculates the index of the free memory list to be used to store
*   memory of the given size.
*
* Return value:
*   Index of the free memory list
*/
static int _GetMinIndex(U32 Size) {
  int Index;
  for (Index = GUI_COUNTOF(_aFreeMem) - 1; Index >= 0; Index--) {
    if (Size > _aFreeMem[Index].MinSize) {
      break;
    }
  }
  return Index;
}

/*********************************************************************
*
*       _GetFreeTag
*
* Purpose:
*   Returns a free memory tag of the requested size or greater
*/
static TAG * _GetFreeTag(U32 Size) {
  TAG * pTag = NULL;
  int Index;
  /* Iterate over free memory list */
  Index = _GetMinIndex(Size);
  for (; Index < GUI_COUNTOF(_aFreeMem); Index++) {
    /* Check if one or more entry exist */
    if (_aFreeMem[Index].pFirstFreeTag) {
      /* Set tag pointer to first entry */
      pTag = _aFreeMem[Index].pFirstFreeTag->pTag;
      /* Check if the requested size is larger than the size of the block */
      if (Size > pTag->MemTag.Size) {
        /* Iterate over list until size does match */
        while (Size > pTag->MemTag.Size) {
          if (pTag->FreeTag.pNext) {
            pTag = pTag->FreeTag.pNext->pTag;
          } else {
            break; /* No further pointer */
          }
        }
      } else {
        break; /* Ok, we found one */
      }
    } else {
      /* No entry, no tag */
      pTag = NULL;
    }
  }
  return pTag;
}

/*********************************************************************
*
*       _WriteTagData
*
* Purpose:
*   Routine to write the tag data: memory tag, free tag and 
*   additional size information at end of block.
*/
static void _WriteTagData(TAG * pTag, GUI_HMEM Block, U32 Size, FREE_TAG * pNext) {
  /* Memory tag info */
  pTag->MemTag.Block  = Block;
  pTag->MemTag.Size   = Size;
  /* Free tag info */
  pTag->FreeTag.pNext = pNext;
  pTag->FreeTag.pTag  = pTag;
  /* Additional size information at end of block */
  *((U32 *)((U32)pTag + Size - sizeof(U32))) = Size;
}


/*********************************************************************
*
*       _Unlink
*
* Purpose:
*   Disengages a free memory list entry from the list
*/
static void _Unlink(FREE_TAG * pFreeTag, FREE_TAG ** ppFirsFreeTag) {
  FREE_TAG * pNext;
  FREE_TAG * pPrev;
  pNext = pFreeTag->pNext;
  pPrev = pFreeTag->pPrev;
  if (pNext) {
    pNext->pPrev = pPrev;
  }
  if (pPrev) {
    pPrev->pNext = pNext;
  } else {
    *(ppFirsFreeTag) = pNext;
  }
}

/*********************************************************************
*
*       _Append
*
* Purpose:
*   Appends a free memory list entry to the list
*/
static void _Append(FREE_TAG * pFreeTag, FREE_TAG ** ppFirsFreeTag) {
  FREE_TAG * pFirsFreeTag;
  pFirsFreeTag = *ppFirsFreeTag;
  if (pFirsFreeTag) {
    pFirsFreeTag->pPrev = pFreeTag;
  }
  pFreeTag->pNext     = pFirsFreeTag;
  pFreeTag->pPrev     = NULL;
  *(ppFirsFreeTag)    = pFreeTag;
}

/*********************************************************************
*
*       _RemoveFreeMemory
*
* Purpose:
*   Removes the given memory block from the according list and subtracts
*   the block size from the free bytes.
*/
static void _RemoveFreeMemory(TAG * pTag) {
  int Index;

  /* Get index of free memory list */
  Index = _GetMinIndex(pTag->MemTag.Size);
  /* Subtract free bytes */
  _NumFreeBytes -= pTag->MemTag.Size;
  /* Disengage from list */
  _Unlink(&pTag->FreeTag, &_aFreeMem[Index].pFirstFreeTag);
}

/*********************************************************************
*
*       _AddFreeMemory
*
* Purpose:
*   Adds the given memory block to the free memory and adds the block size
*   to the free bytes. If adjacent blocks at top or bottom are also free,
*   the routine will merge them together with the given block.
*/
static void _AddFreeMemory(U32 Size, void * p) {
  int Index;
  TAG * pTag;
  U32 AddrMem;
  U32 AddrEnd;
  
  /* End address of heap */
  AddrEnd = (U32)GUI_Heap.abHeap + GUI_ALLOC_SIZE - 1;
  /* Check if next adjacent block can be merged */
  AddrMem = (U32)p + Size;
  if (AddrMem <= AddrEnd) {
    pTag = (TAG *)AddrMem;
    /* If block member of memory tag is 0, it is empty and should be merged */
    if (pTag->MemTag.Block == 0) {
      /* Add size of merged block */
      Size += pTag->MemTag.Size;
      /* Remove merged block */
      _RemoveFreeMemory(pTag);
    }
  }
  /* Check if previous adjacent block can be merged */
  if ((U8 *)p > GUI_Heap.abHeap) {
    U32 SizePrev;
    SizePrev = *(U32 *)((U32)p - sizeof(U32));
    AddrMem = (U32)p - SizePrev;
    pTag = (TAG *)AddrMem;
    /* If block member of memory tag is 0, it is empty and should be merged */
    if (pTag->MemTag.Block == 0) {
      /* Add size of merged block */
      Size += pTag->MemTag.Size;
      /* Remove merged block */
      _RemoveFreeMemory(pTag);
      /* Adjust pointer */
      p = pTag;
    }
  }
  /* Get the index of the free memory list */
  Index = _GetMinIndex(Size);
  /* Make tag pointer */
  pTag = (TAG *)p;
  /* Write memory tag information */
  _WriteTagData(pTag, 0, Size, _aFreeMem[Index].pFirstFreeTag);
  /* Add to free memory list */
  _Append(&pTag->FreeTag, &_aFreeMem[Index].pFirstFreeTag);
  /* Adjust free bytes */
  _NumFreeBytes += Size;
}

/*********************************************************************
*
*       _RemoveHoles
*
* Purpose:
*   Removes all holes from memory and resets the list of free memory
*
* Return value:
*   1 if no hole detected
*/
static int _RemoveHoles(void) {
  TAG * pTag;
  U32 Addr;
  U32 Size;
  U32 AddrCur;
  U32 AddrEnd;
  U32 FreeBytes;
  int NoHoleDetected;
  int i;
  
  NoHoleDetected = 1;
  FreeBytes      = 0;
  AddrCur        = (U32)GUI_Heap.abHeap;
  AddrEnd        = AddrCur + GUI_ALLOC_SIZE - 1;
  /* Iterate over whole heap */
  do {
    U32 SizeCur;
    pTag    = (TAG *)AddrCur;
    SizeCur = pTag->MemTag.Size;
    /* Check if we have a block at the current address */
    if ((pTag->MemTag.Block == 0) && ((AddrCur + SizeCur) < AddrEnd)) {
      U32 SizeBlock;
      U32 AddrBlock;
      NoHoleDetected = 0;
      AddrBlock = AddrCur + SizeCur;
      /* Move all blocks above the hole */
      do {
        U32 AddrNew;
        GUI_HMEM hBlock;
        pTag                 = (TAG *)AddrBlock;
        hBlock               = pTag->MemTag.Block;
        SizeBlock            = pTag->MemTag.Size;
        AddrNew              = AddrBlock - SizeCur;
        _aBlock[hBlock].u.pTag = (TAG *)AddrNew;
        memmove((void *)(AddrNew), (void *)(AddrBlock), SizeBlock);
        AddrBlock += SizeBlock;
      } while (AddrBlock < AddrEnd);
      FreeBytes += SizeCur;
      AddrEnd   -= SizeCur;
    } else {
      AddrCur += SizeCur;
    }
  } while(AddrCur < AddrEnd);
  /* Continue only if at least one hole has been found */
  if (NoHoleDetected == 0) {
    /* Check if last block is free memory. If yes add size to free bytes */
    Size = *(U32 *)(AddrEnd + 1 - sizeof(U32));
    Addr = AddrEnd + 1 - Size;
    pTag = (TAG *)Addr;
    if (pTag->MemTag.Block == 0) {
      FreeBytes += pTag->MemTag.Size;
    }
    /* Clear free memory list */
    for (i = 0; i < GUI_COUNTOF(_aFreeMem); i++) {
      _aFreeMem[i].pFirstFreeTag = NULL;
    }
    /* Set free bytes to 0 */
    _NumFreeBytes = 0;
    /* Add the one and only free memory block */
    _AddFreeMemory(FreeBytes, (void *)((U32)GUI_Heap.abHeap + GUI_ALLOC_SIZE - FreeBytes));
  }
  return NoHoleDetected;
}

/*********************************************************************
*
*       _InitOnce
*
* Purpose:
*   Initialization of memory management. Empty blocks will be joined
*   together, the minimum size of the list of free blocks will be
*   initialized and the one and only free memory block will be added.
*/
static void _InitOnce(void) {
  int i;
  /* Return if already initialized */
  if (_IsInitialized) {
    return;
  }
  _IsInitialized = 1;
  /* Create linked list of empty blocks */
  for (i = 0; i < GUI_COUNTOF(_aBlock) - 1; i++) {
    _aBlock[i].u.NextBlock = i + 1;
  }
  _FirstFreeBlock = 1;
  _NumFreeBlocks  = GUI_COUNTOF(_aBlock) - 1;
  /* Initialize list of free memory free blocks */
  for (i = 0; i < GUI_COUNTOF(_aFreeMem); i++) {
    _aFreeMem[i].MinSize = 32 << i;
  }
  /* Add the one and only initial memory block */
  _AddFreeMemory(GUI_ALLOC_SIZE, GUI_Heap.abHeap);
}

/*********************************************************************
*
*       _PopFreeBlock
*
* Purpose:
*   Returns a free block index and removes it from the list of free blocks.
*/
static GUI_HMEM _PopFreeBlock(void) {
  GUI_HMEM hMem;
  /* Return if no free block is available */
  if (_NumFreeBlocks == 0) {
    return 0;
  }
  _NumFreeBlocks--;
  hMem = _FirstFreeBlock;
  _FirstFreeBlock = _aBlock[_FirstFreeBlock].u.NextBlock;
  #if GUI_DEBUG_LEVEL > 0
    _aBlock[hMem].InUse = 1;
  #endif
  return hMem;
}

/*********************************************************************
*
*       _PushFreeBlock
*
* Purpose:
*   Adds a free block index to the list of free blocks.
*/
static void _PushFreeBlock(GUI_HMEM hMem) {
  _NumFreeBlocks++;
  _aBlock[hMem].u.NextBlock = _FirstFreeBlock;
  #if GUI_DEBUG_LEVEL > 0
    _aBlock[hMem].InUse = 0;
  #endif
  _FirstFreeBlock = hMem;
}

/*********************************************************************
*
*       _SizeToLegalSize
*
* Purpose:
*   Makes sure, that the size is not smaller than the minimum block size.
*/
static U32 _SizeToLegalSize(U32 Size) {
  Size = (Size < _aFreeMem[0].MinSize) ? _aFreeMem[0].MinSize : (Size + ((1 << 2) - 1)) & ~((1 << 2) - 1);
  return GROSS(Size);
}

/*********************************************************************
*
*       Static code, used by public code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetSize
*
* Purpose:
*   Returns the number of available bytes of the given block.
*/
static GUI_ALLOC_DATATYPE _GetSize(GUI_HMEM  hMem) {
  TAG * pTag;
  pTag = _aBlock[hMem].u.pTag;
  return NET(pTag->MemTag.Size);
}

/*********************************************************************
*
*       _Alloc
*
* Purpose:
*   Allocates a new memory block of the requested size. The minimum size 
*   of a free block is the smallest legal size of a free block. If the 
*   requested size is less it will be enlarged to the minimum legal size.
*
* Return value:
*   Handle of the memory block, 0 if the requested number of bytes are not available
*/
static GUI_HMEM _Alloc(GUI_ALLOC_DATATYPE Size) {
  GUI_HMEM hMem;
  GUI_ALLOC_DATATYPE OldSize;
  TAG * pTag;
  _InitOnce();

  /* Adjust size */
  Size = _SizeToLegalSize(Size);
  /* Get pointer to free memory block */
  do {
    /* Get free memory tag */
    pTag = _GetFreeTag(Size);
    if (pTag == NULL) {
      /* Check if the memory is locked */
      if (_LockCnt) {
        /* If memory is locked, return */
        return 0;
      } else {
        /* If there is no memory block available remove the holes */
        if (_RemoveHoles()) {
          /* If there is no hole of the requested size, return */
          return 0;
        }
      }
    }
  } while (pTag == NULL);
  /* Get block index to be returned */
  hMem = _PopFreeBlock();
  /* Save old size of memory block */
  OldSize = pTag->MemTag.Size;
  /* Make sure rest of block is not too small */
  if ((U32)(OldSize - Size) < GROSS(_aFreeMem[0].MinSize)) {
    Size = OldSize;
  }
  /* Remove block from free memory */
  _RemoveFreeMemory(pTag);
  /* Set memory pointer */
  _aBlock[hMem].u.pTag = pTag;
  /* Write tag information */
  _WriteTagData(pTag, hMem, Size, NULL);
  /* Add rest of block to empty memory */
  if (OldSize > Size) {
    _AddFreeMemory(OldSize - Size, (void *)((U32)pTag + Size));
  }

  return hMem;
}

/*********************************************************************
*
*       _Free
*
* Purpose:
*   Adds the given memory block to the free memory.
*/
static void _Free(GUI_HMEM hMem) {
  TAG * pTag;
  #if GUI_DEBUG_LEVEL > 0
  if (_aBlock[hMem].InUse == 0) {
    GUI_DEBUG_ERROROUT("Block already free");
    return;
  }
  #endif
  pTag = _aBlock[hMem].u.pTag;
  #ifdef WIN32
    GUI_MEMSET((U8 *)&pTag->FreeTag, 0xcc, NET(pTag->MemTag.Size));
  #endif
  /* Add block to free memory */
  _AddFreeMemory(pTag->MemTag.Size, pTag);
  /* Put block into list of free blocks */
  _PushFreeBlock(hMem);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
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
    if (_aBlock[hMem].InUse == 0) {
      GUI_DEBUG_ERROROUT("Dereferencing free block");
    }
  #endif
  return (void *)&_aBlock[hMem].u.pTag->FreeTag;
}

/*********************************************************************
*
*       GUI_ALLOC_GetNumFreeBytes
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetNumFreeBytes(void) {
  _InitOnce();
  return NET(_NumFreeBytes);
}

/*********************************************************************
*
*       GUI_ALLOC_GetNumFreeBlocks
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetNumFreeBlocks(void) {
  _InitOnce();
  return _NumFreeBlocks;
}

/*********************************************************************
*
*       GUI_ALLOC_GetNumUsedBytes
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetNumUsedBytes(void) {
  _InitOnce();
  return GUI_COUNTOF(GUI_Heap.abHeap) - _NumFreeBytes;
}

/*********************************************************************
*
*       GUI_ALLOC_GetNumUsedBlocks
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetNumUsedBlocks(void) {
  _InitOnce();
  return GUI_COUNTOF(_aBlock) - _NumFreeBlocks;
}

/*********************************************************************
*
*       GUI_ALLOC_GetMaxSize
*
* Purpose:
*   Returns the biggest available blocksize (without relocation).
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_GetMaxSize(void) {
  GUI_ALLOC_DATATYPE MaxSize = 0;
  int Index;
  TAG * pTag;
  _InitOnce();
  for (Index = GUI_COUNTOF(_aFreeMem) - 1; Index >= 0; Index--) {
    if (_aFreeMem[Index].pFirstFreeTag) {
      pTag = _aFreeMem[Index].pFirstFreeTag->pTag;
      break;
    } else {
      pTag = NULL;
    }
  }
  while (pTag) {
    if ((U32)MaxSize < pTag->MemTag.Size) {
      MaxSize = pTag->MemTag.Size;
    }
    pTag = pTag->FreeTag.pNext ? pTag->FreeTag.pNext->pTag : NULL;
  }
  return NET(MaxSize);
}

/*********************************************************************
*
*       GUI_ALLOC_RequestSize
*/
GUI_ALLOC_DATATYPE GUI_ALLOC_RequestSize(void) {
  GUI_ALLOC_DATATYPE MaxSize;
  GUI_LOCK();
  MaxSize = GUI_ALLOC_GetMaxSize();
  if ((U32)MaxSize > 0x400000L) {
    MaxSize = (MaxSize / 100) * _MaxRequestPercent;
  } else {
    MaxSize = ((U32)MaxSize * _MaxRequestPercent) / 100;
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

void GUIAlloc1_C(void);   /* Avoid empty object files */
void GUIAlloc1_C(void) {}

#endif /* (GUI_SELECT_ALLOC == 1) */

/*************************** End of file ****************************/
