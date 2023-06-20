#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif
vector<PROUser*> PROUser::UsersVector;

PROUser::PROUser()
{
	// This is just temporarily. When reading the ID-number from Config this is replaced
	IDNumber = (C_PRO_USER << 16) + (UsersVector.size()+1);
}

PROUser::~PROUser(void)
{
}

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

void PROUser::WriteConfigToFile(TSNConfigString &ConfigString)
{
	AnsiString LocalString;
	LocalString +=KeyWord(C_PRO_USER)+CrLfStr;
	LocalString +=TabStr1+KeyWord(C_PRO_USER_NAME)+Name+CrLfStr;
	LocalString +=TabStr1+KeyWord(C_PRO_USER_PASSWORD)+PassWord+CrLfStr;
	LocalString +=TabStr1+KeyWord(C_PRO_USER_ID_NUMBER)+PassWord+CrLfStr;
	LocalString += KeyWord(C_PRO_END)+CrLfStr;
	ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int PROUser::LoadConfigFromFile(TSNConfigString &ConfigString)
{
    SetLineNumber(ConfigString.LineCount);
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning("PROUser",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning("PROUser",InputKeyWord,ConfigString.LineCount);
					break;
				case C_AI_END:			// If AI type not found can continue with this
				case C_AL_END:
				case C_PRO_END:
				case C_PRO_END_COMMON:
				case C_PRO_END_PRO:
					break;
				case C_PRO_USER_NAME:
					Name = ConfigString.GetRemainingLine(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_PRO_USER_PASSWORD:
					Name = ConfigString.NextWord(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_PRO_USER_ID_NUMBER:
					IDNumber = ConfigString.ReadInteger(ErrorLine);
					break;

			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
	UsersVector.push_back(this);

	return ErrorLine;

}
//---------------------------------------------------------------------------
int PROUser::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	return(PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit));
}

int PROUser::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		default:
			Status = PRogramObjectBase::GetStringValue(ValueId,Index, MyString);
			break;
	}
	return(Status);
}

int PROUser::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	return(PRogramObjectBase::PutValue( ValueId, Index, NewValue, Local,UnitId));
}

int PROUser::PutFloatValue( int ValueId, float NewValue)
{
	return(PRogramObjectBase::PutFloatValue(ValueId,NewValue));
}

void PROUser::SetReadVectors(void)
{
	PROCargoObjVector         = GetReadPermissionVector(PROCargoTank::AllObjVector);
	PROBallastObjVector       = GetReadPermissionVector(PROBallastTank::AllObjVector);
	PROServiceObjVector       = GetReadPermissionVector(PROServiceTank::AllHeavyFuelOilVector);
	PROHeavyFuelObjVector     = GetReadPermissionVector(PROServiceTank::AllHeavyFuelOilVector);
	PRODieselOilObjVector     = GetReadPermissionVector(PROServiceTank::AllDieselVector);
	PROLubricantsObjVector    = GetReadPermissionVector(PROServiceTank::AllLubricantsVector);
	PROMiscObjVector          = GetReadPermissionVector(PROServiceTank::AllMiscVector);
	PROFreshWaterObjVector    = GetReadPermissionVector(PROServiceTank::AllFreshWaterVector);
	PROTempObjVector          = GetReadPermissionVector(PROTemperature::AllObjVector);
	PROTankPressObjVector     = GetReadPermissionVector(PROTankPressure::AllObjVector);
	PROLPressObjVector        = GetReadPermissionVector(PROLinePressure::ObjVector);
	PROVoidSpaceVector        = GetReadPermissionVector(PROVoidSpace::AllObjVector);
	PROWaterIngrVector        = GetReadPermissionVector(PROWaterIngress::AllObjVector);
	PROLevelSwitchVector      = GetReadPermissionVector(PROLevelSwitch::AllObjVector);
}

