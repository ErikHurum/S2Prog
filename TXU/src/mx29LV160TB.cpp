#include <string.h>
#include "def.h"
#include "2410addr.h"
#include "2410lib.h"
#include "2410slib.h"
#include "rtos.h"
#include "mmu.h"
#include "ANPRO10Const.h"
#include "TSNConstants.h"
#pragma diag_suppress=Pa082
extern short CurrentDeviceId;

OS_RSEMA FlashSema;


bool MX29LV_ProgFlash(U32 realAddr, U32 data);
bool MX29LV_EraseSector(int targetAddr);
bool MX29LV_EraseSectors(int FirstSector, int LastSector);

bool MX29LV_EraseChip(void);
bool MX29LV_CheckId(void);
bool BlankCheck(int targetAddr, int targetSize);
bool WaitForFlash(void);


#define FLASH_READY_MASK	0x600
#define FLASH_MASK_Q7		0x800080
#define FLASH_MASK_Q6		0x400040
#define FLASH_MASK_Q5		0x200020
#define FLASH_MASK_Q4		0x100010
#define FLASH_MASK_Q3		0x080008
#define FLASH_MASK_Q2		0x040004
#define FLASH_MASK_Q1		0x020002
#define FIRST_CMD		  	0xaa00aa
#define SECOND_CMD			0x550055
#define PROGRAM_CMD			0xa000a0
#define ERASE_CMD		  	0x800080
#define ERASE_ALL_CMD		0x100010
#define ERASE_SEC_CMD		0x300030
#define ID_CMD			 	0x900090
#define RESET_CMD			0xf000f0

U32 FlashBaseAddress = 0x04000000;

// Because KS32C41000_A1 is connected to AM29LV800_A0,
// the addr parameter has to be a WORD address, so called in AMD specification.

#define _WR(addr,data)  *((volatile U32*)(FlashBaseAddress+addr))=(U32)data
#define _RD(addr)       ( *((volatile U32*)(FlashBaseAddress+addr)) )
//#define _WR(addr,data)  *((U32 *)(addr))=(U32)data
//#define _RD(addr)       ( *((U32 *)(addr)) )
#define _RESET()	_WR(0x0,0x00f000f0)


volatile U32 *firstAddr = (volatile U32 *)(FlashBaseAddress + (0x555 << 2)); //(ulong *)(FlashBaseAddress+0x1554);
volatile U32 *secondAddr = (volatile U32 *)(FlashBaseAddress + (0x2aa << 2)); //	(ulong *)(FlashBaseAddress+0xaa8);

//static U32 downloadProgramSize  = 500000;

#ifdef ANBOOTLOADER
extern "C"
{
//extern char ProgramData[];
//extern int ProgramDataSize;
}
#endif

U32 SectorTable1[] = {  // MX29LVB 32bit satt opp i byte mode
    0x00000000 << 1,
    0x00004000 << 1,
    0x00006000 << 1,
    0x00008000 << 1,
    0x00010000 << 1, // First program sector 5
    0x00020000 << 1,
    0x00030000 << 1,
    0x00040000 << 1,
    0x00050000 << 1,
    0x00060000 << 1,
    0x00070000 << 1,
    0x00080000 << 1,
    0x00090000 << 1,
    0x000a0000 << 1,
    0x000b0000 << 1,
    0x000c0000 << 1,
    0x000d0000 << 1,
    0x000e0000 << 1,
    0x000f0000 << 1,
    0x00100000 << 1,
    0x00110000 << 1,
    0x00120000 << 1,
    0x00130000 << 1, // Last program sector 22
    0x00140000 << 1, // First config sector 23
    0x00150000 << 1,
    0x00160000 << 1,
    0x00170000 << 1, // Last config sector 26
    0x00180000 << 1, // First config backup 27
    0x00190000 << 1,
    0x001a0000 << 1,
    0x001b0000 << 1, // Last config backup sector 30
    0x001c0000 << 1, // Setting start 31
    0x001d0000 << 1, // Setting end   32
    0x001e0000 << 1, // Setting start backup 33
    0x001f0000 << 1, // Setting end backup 34
    0x00200000 << 1, // TDU settings 35
    0x00210000 << 1, // TDU settings 36 ( Does not exist ), But will give correct Erase
};

U32 SectorTable2[] = {  // MX29LVB 32bit satt opp i byte mode
    0x00000000 << 1,
    0x00002000 << 1,
    0x00004000 << 1,
    0x00006000 << 1,
    0x00008000 << 1,
    0x0000A000 << 1,
    0x0000C000 << 1,
    0x0000E000 << 1,
    0x00010000 << 1,
    0x00020000 << 1, // First program sector 10
    0x00030000 << 1,
    0x00040000 << 1,
    0x00050000 << 1,
    0x00060000 << 1,
    0x00070000 << 1,
    0x00080000 << 1,
    0x00090000 << 1,
    0x000a0000 << 1,
    0x000b0000 << 1,
    0x000c0000 << 1,
    0x000d0000 << 1,
    0x000e0000 << 1,
    0x000f0000 << 1,
    0x00100000 << 1,
    0x00110000 << 1,
    0x00120000 << 1,  // Program End Sector 25
    0x00130000 << 1, // First config sector 26
    0x00140000 << 1,
    0x00150000 << 1,
    0x00160000 << 1, // Last config sector 29
    0x00170000 << 1, // First config backup 30
    0x00180000 << 1,
    0x00190000 << 1,
    0x001a0000 << 1, // Last config backup sector 33
    0x001b0000 << 1,  // Settings 1
    0x001c0000 << 1,
    0x001d0000 << 1,  // Settings 2
    0x001e0000 << 1,
    0x001f0000 << 1,  // 38, Local settings
    0x00200000 << 1,
    0x00210000 << 1,
    0x00220000 << 1,
    0x00230000 << 1,
    0x00240000 << 1,
    0x00250000 << 1,
    0x00260000 << 1,
    0x00270000 << 1,
    0x00280000 << 1,
    0x00290000 << 1,
    0x002a0000 << 1,
    0x002b0000 << 1,
    0x002c0000 << 1,
    0x002d0000 << 1,
    0x002e0000 << 1,
    0x002f0000 << 1,
    0x00300000 << 1,
    0x00310000 << 1,
    0x00320000 << 1,
    0x00330000 << 1,
    0x00340000 << 1,
    0x00350000 << 1,
    0x00360000 << 1,
    0x00370000 << 1,
    0x00380000 << 1,
    0x00390000 << 1,
    0x003a0000 << 1,
    0x003b0000 << 1,
    0x003c0000 << 1,
    0x003d0000 << 1,
    0x003e0000 << 1,
    0x003f0000 << 1,
    0x00400000 << 1,
    0x00410000 << 1,
    0x00420000 << 1,
    0x00430000 << 1,
    0x00440000 << 1,
    0x00450000 << 1,
    0x00460000 << 1,
    0x00470000 << 1,
    0x00480000 << 1,
    0x00490000 << 1,
    0x004a0000 << 1,
    0x004b0000 << 1,
    0x004c0000 << 1,
    0x004d0000 << 1,
    0x004e0000 << 1,
    0x004f0000 << 1,
    0x00500000 << 1,
    0x00510000 << 1,
    0x00520000 << 1,
    0x00530000 << 1,
    0x00540000 << 1,
    0x00550000 << 1,
    0x00560000 << 1,
    0x00570000 << 1,
    0x00580000 << 1,
    0x00590000 << 1,
    0x005a0000 << 1,
    0x005b0000 << 1,
    0x005c0000 << 1,
    0x005d0000 << 1,
    0x005e0000 << 1,
    0x005f0000 << 1,
    0x00600000 << 1,
    0x00610000 << 1,
    0x00620000 << 1,
    0x00630000 << 1,
    0x00640000 << 1,
    0x00650000 << 1,
    0x00660000 << 1,
    0x00670000 << 1,
    0x00680000 << 1,
    0x00690000 << 1,
    0x006a0000 << 1,
    0x006b0000 << 1,
    0x006c0000 << 1,
    0x006d0000 << 1,
    0x006e0000 << 1,
    0x006f0000 << 1,
    0x00700000 << 1,
    0x00710000 << 1,
    0x00720000 << 1,
    0x00730000 << 1,
    0x00740000 << 1,
    0x00750000 << 1,
    0x00760000 << 1,
    0x00770000 << 1,
    0x00780000 << 1,
    0x00790000 << 1,
    0x007a0000 << 1,
    0x007b0000 << 1,
    0x007c0000 << 1,
    0x007d0000 << 1,
    0x007e0000 << 1,
    0x007f0000 << 1,
};

//#pragma pack(1)
bool IdOk = false;
U32 *SectorTable = NULL;
U32 SectorBootStart = 0;
U32 SectorBootEnd = 0;
U32 SectorProgStart = 0;
U32 SectorProgEnd = 0;
U32 SectorConfigStart = 0;
U32 SectorConfigEnd = 0;
U32 SectorConfigBakStart = 0;
U32 SectorConfigBakEnd = 0;
U32 SectorSettings1Start = 0;
U32 SectorSettings1End = 0;
U32 SectorSettings2Start = 0;
U32 SectorSettings2End = 0;
U32 SectorLocalSettings = 0;

void SetFlashSectorTable(void) {
    switch (GlobalDeviceHWId) {
    case TCU_R1:
    case TDU_R1:
        SectorTable = SectorTable1;
        SectorBootStart = SECTOR_BOOT_START_R1;
        SectorBootEnd = SECTOR_BOOT_END_R1;
        SectorProgStart = SECTOR_PROG_START_R1;
        SectorProgEnd = SECTOR_PROG_END_R1;
        SectorConfigStart = SECTOR_CONFIG_START_R1;
        SectorConfigEnd = SECTOR_CONFIG_END_R1;
        SectorConfigBakStart = SECTOR_CONFIG_BAK_START_R1;
        SectorConfigBakEnd = SECTOR_CONFIG_BAK_END_R1;
        SectorSettings1Start = SECTOR_SETTINGS1_START_R1;
        SectorSettings1End = SECTOR_SETTINGS1_END_R1;
        SectorSettings2Start = SECTOR_SETTINGS2_START_R1;
        SectorSettings2End = SECTOR_SETTINGS2_END_R1;
        SectorLocalSettings = SECTOR_LOCAL_SETTINGS_START_R1;
        break;
    case TCU_R2:
    case TDU_R2:
    default:
        SectorTable = SectorTable2;
        SectorBootStart = SECTOR_BOOT_START_R2;
        SectorBootEnd = SECTOR_BOOT_END_R2;
        SectorProgStart = SECTOR_PROG_START_R2;
        SectorProgEnd = SECTOR_PROG_END_R2;
        SectorConfigStart = SECTOR_CONFIG_START_R2;
        SectorConfigEnd = SECTOR_CONFIG_END_R2;
        SectorConfigBakStart = SECTOR_CONFIG_BAK_START_R2;
        SectorConfigBakEnd = SECTOR_CONFIG_BAK_END_R2;
        SectorSettings1Start = SECTOR_SETTINGS1_START_R2;
        SectorSettings1End = SECTOR_SETTINGS1_END_R2;
        SectorSettings2Start = SECTOR_SETTINGS2_START_R2;
        SectorSettings2End = SECTOR_SETTINGS2_END_R2;
        SectorLocalSettings = SECTOR_LOCAL_SETTINGS_START_R2;
        break;
    }
}

bool MX29LV_CheckId(void) {
    OS_Use(&FlashSema);
    if (!IdOk) {
        U32 manId, devId;
        OS_IncDI();
        _RESET();
        // Word mode, shift address 2bit left due to a2=a0
        *firstAddr = FIRST_CMD;
        *secondAddr = SECOND_CMD;
        *firstAddr = ID_CMD;
        manId = *((volatile U32 *)(FlashBaseAddress + 0));
        _RESET();

        *firstAddr = FIRST_CMD;
        *secondAddr = SECOND_CMD;
        *firstAddr = ID_CMD;
        devId = *((volatile U32 *)(FlashBaseAddress + 4));

        _RESET();
        OS_DecRI();
        // Flash code for 160 device	"2249"
        // Flash code for 640 device	"22CB"
        switch (GlobalDeviceHWId) {
        case TCU_R1:
        case TDU_R1:
            if (manId == 0x00c200c2 && devId == 0x22492249) {
                IdOk = true; // ID OK
                SectorTable = SectorTable1;
            }
            break;
        case TCU_R2:
        case TDU_R2:
            if (manId == 0x00c200c2 && devId == 0x22CB22CB) {
                IdOk = true; // ID OK
                SectorTable = SectorTable2;
            }
            break;
        }
    }
    OS_Unuse(&FlashSema);
    //MX29LV_ProgFlash(FlashBaseAddress,0);
    return (IdOk);
}



bool ProgramMX29LV(U32 FirstSector, U32 targetAddress, U32 srcAddress, U32 targetSize) {
    OS_Use(&FlashSema);
    bool NoError = true;
    targetAddress += SectorTable[FirstSector] + FlashBaseAddress;
    U8 *srcPtr = (U8 *)srcAddress;
    for (int i = 0x0; NoError && i < targetSize; i += 4) {
        U32 tmpData = srcPtr[3] << 24 | srcPtr[2] << 16 | srcPtr[1] << 8 | srcPtr[0];
        srcPtr += 4;
        NoError = MX29LV_ProgFlash(targetAddress + i, tmpData);
    }
    _RESET();
    /*
    srcPtr = (U8*)srcAddress;
    volatile U8 *trgtPtr = (U8*)targetAddress;
    int Cnt;
    for ( Cnt=0; NoError && Cnt < targetSize; Cnt++ ) {
        if ( srcPtr[Cnt] != trgtPtr[Cnt] ) {
            NoError = false;
        }
    }
    */
    /*
    if ( memcmp((char*)srcAddress,(char*)targetAddress,targetSize) ) {
        NoError = false;
    }
    */
    OS_Unuse(&FlashSema);
    return (NoError);
}


bool MarkCompletedMX29LV(U32 LastSector, U32 Size) {
    OS_Use(&FlashSema);
    bool NoError = true;
    //OS_EnterRegion();  // May be required, or a semaphore.

    U32 targetAddress = SectorTable[LastSector + 1] + FlashBaseAddress;
    U32 OKPattern = 0x11223344;
    NoError = MX29LV_ProgFlash(targetAddress - sizeof(U32), OKPattern);
    if (NoError) {
        NoError = MX29LV_ProgFlash(targetAddress - 2 * sizeof(U32), Size);
    }
    OS_Unuse(&FlashSema);
    return (NoError);

    //OS_LeaveRegion();
}

bool GetBlockSizeMX29LV(U32 LastSector, U32 *Size) {
    OS_Use(&FlashSema);

    bool NoError = true;
    //OS_EnterRegion();  // May be required, or a semaphore.

    U32 targetAddress = SectorTable[LastSector + 1] + FlashBaseAddress;
    U32 OKPattern = 0x11223344;

    U32 *targetPtr = (U32 *)targetAddress;
    if (targetPtr[-1] == OKPattern) *Size = targetPtr[-2];
    else NoError = false;
    OS_Unuse(&FlashSema);

    return (NoError);

    //OS_LeaveRegion();
}

bool GetBlockInfoMX29LV(U32 FirstSector, U32 LastSector, U8 **FlashStartPtr, U32 *Size) {
    OS_Use(&FlashSema);
    bool NoError = true;
    //OS_EnterRegion();  // May be required, or a semaphore.

    U32 targetAddress = SectorTable[LastSector + 1] + FlashBaseAddress;
    U32 OKPattern = 0x11223344;

    U32 *targetPtr = (U32 *)targetAddress;
    if (targetPtr[-1] == OKPattern) {
        *Size = targetPtr[-2];
        *FlashStartPtr = (U8 *)SectorTable[FirstSector] + FlashBaseAddress;;
    } else {
        NoError = false;
    }
    OS_Unuse(&FlashSema);

    return (NoError);

    //OS_LeaveRegion();
}
bool CopyFromFlash(U32 FirstSector, U32 LastSector, char *TargetPtr) {
    OS_Use(&FlashSema);
    bool NoError = false;
    U32 *FlashInfoPtr = (U32 *)(SectorTable[LastSector + 1] + FlashBaseAddress);
    if (FlashInfoPtr[-1] == 0x11223344) {
        U32 Size = FlashInfoPtr[-2];
        char *FlashStartPtr = (char *)(SectorTable[FirstSector] + FlashBaseAddress);
        memcpy(TargetPtr, FlashStartPtr, Size);
        NoError = true;
    }
    OS_Unuse(&FlashSema);
    return (NoError);
}
bool GetBlockStart(U32 FirstSector, U32 LastSector, U8 **blockPtr) {
    OS_Use(&FlashSema);
    bool NoError = true;
    U32 *FlashInfoPtr = (U32 *)(SectorTable[LastSector + 1] + FlashBaseAddress);
    if (FlashInfoPtr[-1] == 0x11223344) {
        *blockPtr = (U8 *)(SectorTable[FirstSector] + FlashBaseAddress);
    } else {
        NoError = false;
    }
    OS_Unuse(&FlashSema);
    return (NoError);
}

U32 GetBlockAddress(U32 FirstSector) {
    return SectorTable[FirstSector] + FlashBaseAddress;
}


bool MX29LV_EraseSector(int Sector) {
    OS_Use(&FlashSema);
    bool NoError = true;

    volatile U32 *targetP = (volatile U32 *)(SectorTable[Sector] + FlashBaseAddress);

    OS_IncDI();
    *firstAddr = FIRST_CMD;
    *secondAddr = SECOND_CMD;
    *firstAddr = ERASE_CMD;

    *firstAddr = FIRST_CMD;
    *secondAddr = SECOND_CMD;
    *targetP = ERASE_SEC_CMD;
    OS_DecRI();
    OS_Delay(10);   // If we read toggle bits too early, the status may be incorrect
    int RetryCnt = 0;
    do {
        OS_Delay(700);

    } while (RetryCnt++ < 15 && !BlankCheck(SectorTable[Sector] + FlashBaseAddress, SectorTable[Sector + 1] - SectorTable[Sector]));
    // Not blank, do nothing for now
    if (RetryCnt > 15) NoError = false;
    _RESET();
    OS_Unuse(&FlashSema);
    return (NoError);
}


bool MX29LV_EraseSectors(int FirstSector, int LastSector) {
    bool NoError = true;
    if (FirstSector >= 0 && LastSector >= FirstSector) {
        OS_Use(&FlashSema);
        if (!BlankCheck(SectorTable[FirstSector] + FlashBaseAddress, SectorTable[LastSector] - SectorTable[FirstSector])) {
            OS_IncDI();
            *firstAddr = FIRST_CMD;
            *secondAddr = SECOND_CMD;
            *firstAddr = ERASE_CMD;

            *firstAddr = FIRST_CMD;
            *secondAddr = SECOND_CMD;
            for (int Sector = LastSector; Sector >= FirstSector; Sector--) {
                volatile U32 *targetP = (volatile U32 *)(SectorTable[Sector] + FlashBaseAddress);
                *targetP = ERASE_SEC_CMD;
            }
            OS_DecRI();
            int RetryCnt = 0;
            do {
                OS_Delay(700);
            } while (RetryCnt++ < 15 && !BlankCheck(SectorTable[FirstSector] + FlashBaseAddress, SectorTable[LastSector] - SectorTable[FirstSector]));
            // Not blank, do nothing for now
            if (RetryCnt > 15) NoError = false;
            _RESET();

        }
        OS_Unuse(&FlashSema);

    }
    return (NoError);
}

bool MX29LV_EraseChip(void) {
    OS_Use(&FlashSema);
    // Word mode, shift address 2bit left due to a2=a0
    OS_IncDI();
    *firstAddr = RESET_CMD;
    *firstAddr = FIRST_CMD;
    *secondAddr = SECOND_CMD;
    *firstAddr = ERASE_CMD;

    *firstAddr = FIRST_CMD;
    *secondAddr = SECOND_CMD;
    *firstAddr = ERASE_ALL_CMD;
    OS_DecRI();
    bool NoError = WaitForFlash();
    *firstAddr = RESET_CMD;
    OS_Unuse(&FlashSema);
    return (NoError);
}

bool BlankCheck(int targetAddr, int targetSize) {
    OS_Use(&FlashSema);
    int i;
    volatile U32 *tmpPtr = (volatile U32 *)targetAddr;
    bool NoError = true;
    for (i = 0; NoError && i < targetSize; i += 4) {
        if (*tmpPtr++ != 0xffffffff) {
            // Not blank
            NoError = false;
        }
    }
    OS_Unuse(&FlashSema);
    return (NoError);
}

bool WaitForFlash(void) {   //Check if the bit6 toggle ends.
    volatile U32 flashStatus;
    volatile U32 old = *firstAddr;

    while (true) {
        flashStatus = *firstAddr;
        if ((old & FLASH_MASK_Q6) == (flashStatus & FLASH_MASK_Q6)) return (true);

        if (flashStatus & FLASH_MASK_Q5) {
            old = *firstAddr;
            flashStatus = *firstAddr;
            if ((old & FLASH_MASK_Q6) == (flashStatus & FLASH_MASK_Q6)) {
                return (true);
            } else {
                return (false);
            }
        }
        old = flashStatus;
    }
    //return(false);
}


bool MX29LV_ProgFlash(U32 realAddr, U32 data) {
    OS_Use(&FlashSema);
    int ExitTime = OS_GetTime() + 2;
    _RESET();
    // Word mode, shift address 2bit left due to a2=a0
    volatile U32 *targetP = (volatile U32 *)realAddr;
    OS_IncDI();
    *firstAddr = FIRST_CMD;
    *secondAddr = SECOND_CMD;
    *firstAddr = PROGRAM_CMD;
    *targetP = data;
    OS_DecRI();
    while (ExitTime > OS_GetTime() && (*targetP != data));
    OS_Unuse(&FlashSema);
    return (*targetP == data);
}





