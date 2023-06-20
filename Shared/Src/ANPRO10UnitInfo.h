#pragma once
#ifndef ANPRO10UNITINFO_H
#define ANPRO10UNITINFO_H
class ANPRO10UnitInfo    // TXU status
{
private:
	bool HasInfo      ;
	bool SignalHasInfo;

	U8 LastOSErr;
	U32 LastErrAddr;
	U8 FlashErrStatus;
	char LastOSErrTask[0x20];

public:
	U8				UnitID;
	U8				UnitAdress;
	U8				ProgramType; // 0 = Bootloader, 1 = Application
	U8				ErrorStatus;

	char SystemID[ANPRO10_ID_LENGTH];
	U16				DataVersion;
	ProgramVersionInfo	ProgramVersion;
	ProgramVersionInfo	BootVersion;
	time_t	   ProgrDate;
	TSN_TASK		*pTask;
	time_t 		UpdateTime;
	ANPRO10UnitInfo();
	void Update_Unit_Info(ANPRO10_COMMAND_2001 *InfoStruct);
	void VersionControl(TSNUart *Port);

};

#endif
