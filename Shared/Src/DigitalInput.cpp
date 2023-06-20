#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

int DigitalInput::NumberOfPRO=0;

DigitalInput::DigitalInput(void)
{
	Failure= false;
	Init();
}

void DigitalInput::Init(void)
{
	NumberOfPRO++;
	IDNumber = (C_IOC_DIGITAL_IN << 16 )+NumberOfPRO;
	SerialNumber = "None";
	TCUAddress = 0;
	//TCUPort = 0;
	TCUPortNo = 0;
	IOType = 0;
	IOAddress = 0;
	IOChannel = 0;
	ADCardChannel = 0;
}

DigitalInput::~DigitalInput(void)
{
}



///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString DigitalInput::MakeConfigString(int ExtraTabs)
{
	AnsiString LocalString;
	LocalString +=TabStr2+KeyWord(C_DI_START_COMMON)+CrLfStr;
//    LocalString +=TabStr3+KeyWord(C_DI_TYPE)+(AnsiString)Type+CrLfStr;
	if ( SerialNumber.IsEmpty()) {
		 SerialNumber = "None";
	}
	LocalString +=TabStr3+KeyWord(C_DI_SERIALNO)+SerialNumber+CrLfStr;

	LocalString +=TabStr3+KeyWord(C_TCU_ADDRESS)+(AnsiString)TCUAddress+CrLfStr;
	//   LocalString +=TabStr3+KeyWord(C_TCU_PORT)+(AnsiString)TCUPort+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_TCU_PORT_NO)+(AnsiString)TCUPortNo+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_IO_TYPE)+KeyWord(IOType)+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_IO_ADDRESS)+(AnsiString)IOAddress+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_IO_CHANNEL)+(AnsiString)IOChannel+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_ADCARD_CH)+(AnsiString)ADCardChannel+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_DI_END_COMMON)+CrLfStr;

	LocalString += PROIOComponent::MakeConfigString();
	return (LocalString);
}
//---------------------------------------------------------------------------

bool DigitalInput::LoadConfigString(TSNConfigString &ConfigString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning("Digital Input",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning("Digital Input",InputKeyWord,ConfigString.LineCount);
					break;
				case C_DI_END_COMMON:
					break;
				case C_DI_SERIALNO:
					SerialNumber = ConfigString.NextWord(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_TCU_ADDRESS:
					TCUAddress = ConfigString.ReadLong(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_TCU_PORT_NO:
					TCUPortNo = ConfigString.ReadLong(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_IO_TYPE:
					{
						AnsiString temp = ConfigString.NextWord(ErrorLine);
						if ( !ErrorLine ) {
							IOType = FindConfigKey(temp);
						}
						NoError = !ErrorLine;
					}
					break;
				case C_IO_ADDRESS:
					IOAddress = ConfigString.ReadLong(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_IO_CHANNEL:
					IOChannel = ConfigString.ReadLong(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_ADCARD_CH:
					ADCardChannel = ConfigString.ReadLong(ErrorLine);
					NoError = !ErrorLine;
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_DI_END_COMMON ) );
	return (NoError);
}
//---------------------------------------------------------------------------


///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int DigitalInput::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ){
	//	default:
	MyString = "";
	Status = GETVAL_NOT_AVAILABLE;
	//		break;
	//}
	return(Status);
}

int DigitalInput::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId )
	// {
	//	default:
	Status = GETVAL_NOT_AVAILABLE;
	//		  break;
	//}
	return(Status);
}

int DigitalInput::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	//switch ( ValueId ){
	//	default:
	Status = E_INPUT_ERR;
	//		break;
	//}
	if ( Status==E_NO_ERR ) {
		SetModifiedFlag();
	}
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int DigitalInput::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId )
	// {
	//   default:
	Status = E_NOT_ADJUSTABLE;
	//		break;
	//}
	return(Status);
}
//end librerian


float DigitalInput::Calculate(void)
{
	return (0.0);
}
