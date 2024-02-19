#pragma once
#ifndef SaabProtocolH
#define SaabProtocolH
typedef struct {
	int      ValKey;
    unsigned First_Tank,
             Number_of_Tanks;
} BlockDef;
typedef struct {
	int  Key;
	int  ValueKey;
	int  Scale;
	bool Sign;
	int  ObjType;
	int Action;
} SaabData;

///////////////////////////////////////////////////////////////
//
// Saab protocol object.
//
// This module contains Saab protocol support. Use the Saab documentation for
// reference.
//
// Revision history:
// Created: ??? EHS
///////////////////////////////////////////////////////////////

class SaabProtcol:public PRogramObject {
private:
	int CurrentRequest;
	int TCUAddress;
	int WinUart;

public:
	static set<PRogramObjectBase*>ObjectSet;
	static vector<SaabProtcol*>SaabProtcolVector;
	vector<BlockDef>BlockVector;
	vector<SaabData>ExtraParameters;
	int Delay;

	SaabProtcol(int PortNum,unsigned IDNumber=0);
	~SaabProtcol(void);
	void Initiate(void);
	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);

	void SendString(TSNUart *PortPtr, char *TxBuf, int OutPtr);
	void AddAlarmStatus(char *OutBuf, int &OutPtr, int Index, int ObjectType);

	void SAABSendRequest(TSNUart *PortPtr);
	void SAABHandleInput(TSNUart *PortPtr, U8 Data);
	bool SAABHandleAnswer(TSNUart *PortPtr);
	void SAABHandleRequest(TSNUart *PortPtr);
	void SaabComTask(TSNUart *PortPtr);
	static SaabProtcol* FindSaabProtocolObject(int portNo);


};

#endif
