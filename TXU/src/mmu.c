/************************************************
    NAME    : MMU.C
    DESC	  :
    Revision: 2002.2.28 ver 0.0
 ************************************************/

#include "def.h"
#include "TSNConstants.h"
#include "2410addr.h"
#include "2410lib.h"
#include "2410slib.h"
#include "mmu.h"

// 1) Only the section table is used.
// 2) The cachable/non-cachable area can be changed by MMT_DEFAULT value.
//    The section size is 1MB.



void MMU_Init(void) {
    //========================== IMPORTANT NOTE =========================
    //The current stack and code area can't be re-mapped in this routine.
    //If you want memory map mapped freely, your own sophisticated MMU
    //initialization code is needed.
    //===================================================================

    MMU_DisableDCache();
    MMU_DisableICache();

    //If write-back is used,the DCache should be cleared.
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 8; j++) {
            MMU_CleanInvalidateDCacheIndex((i << 26) | (j << 5));
        }
    }
    MMU_InvalidateICache();

#if 0
    //To complete MMU_Init() fast, Icache may be turned on here.
    MMU_EnableICache();
#endif

    MMU_DisableMMU();
    MMU_InvalidateTLB();

    //MMU_SetMTT(int vaddrStart,int vaddrEnd,int paddrStart,int attr)
    MMU_SetMTT(0x00000000, 0x01b00000, 0x30000000, RW_CB);  //bank0 RAM
    MMU_SetMTT(0x04000000, 0x0405ffff, 0x00000000, RO_NCNB);   //bank0	flash boot loader

    MMU_SetMTT(0x04060000, 0x07ffffff, 0x00060000, RW_NCNB);   //bank0	flash program
    MMU_SetMTT(0x08000000, 0x2fffffff, 0x08000000, RW_NCNB);    //bank1

    MMU_SetMTT(0x30000000, 0x307fffff, 0x30000000, RW_CB);     //	 RAM size 0x800000 ( IC14 )
    MMU_SetMTT(0x30800000, 0x30ffffff, 0x31000000, RW_CB);     //	 RAM size 0x800000 ( IC14 )

    MMU_SetMTT(0x31000000, 0x317fffff, 0x32000000, RW_CB);     //	 RAM size 0x800000 ( IC15 ) 
    MMU_SetMTT(0x31800000, 0x31ffffff, 0x33000000, RW_CB);     //	 RAM size 0x800000 ( IC15 ) 

    MMU_SetMTT(0x34000000, 0x3fffffff, 0x34000000, RW_NCNB);     //    Was RW_NCNB
    MMU_SetMTT(0x40000000, 0x47ffffff, 0x40000000, RW_NCNB);   //SFR

    MMU_SetMTT(0x48000000, 0x5affffff, 0x48000000, RW_NCNB);   //SFR
    MMU_SetMTT(0x5b000000, 0xffffffff, 0x5b000000, RW_FAULT); //not used

    MMU_SetTTBase(_MMUTT_STARTADDRESS);
    MMU_SetDomain(0x55555550 | DOMAIN1_ATTR | DOMAIN0_ATTR);
    //DOMAIN1: no_access, DOMAIN0,2~15=client(AP is checked)
    MMU_SetProcessId(0x0);
    MMU_EnableAlignFault();

    MMU_EnableMMU();
    MMU_EnableICache();
    MMU_EnableDCache(); //DCache should be turned on after MMU is turned on.
}


// attr=RW_CB,RW_CNB,RW_NCNB,RW_FAULT
void ChangeRomCacheStatus(int attr) {
    MMU_DisableDCache();
    MMU_DisableICache();
    //If write-back is used,the DCache should be cleared.
    for (int i = 0; i < 64; i++) for (int j = 0; j < 8; j++) MMU_CleanInvalidateDCacheIndex((i << 26) | (j << 5));
    MMU_InvalidateICache();
    MMU_DisableMMU();
    MMU_InvalidateTLB();
    MMU_SetMTT(0x00000000, 0x07ffffff, 0x00000000, attr);  //bank0
    MMU_SetMTT(0x08000000, 0x0fffffff, 0x08000000, attr);  //bank1
    MMU_EnableMMU();
    MMU_EnableICache();
    MMU_EnableDCache();
}


void MMU_SetMTT(int vaddrStart, int vaddrEnd, int paddrStart, int attr) {
    U32 *pTT = (U32 *)_MMUTT_STARTADDRESS + (vaddrStart >> 20);
    int nSec = (vaddrEnd >> 20) - (vaddrStart >> 20);
    for (int i = 0; i <= nSec; i++) *pTT++ = attr | (((paddrStart >> 20) + i) << 20);
}






