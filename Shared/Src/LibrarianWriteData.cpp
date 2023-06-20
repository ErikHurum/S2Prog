//---------------------------------------------------------------------------

#pragma hdrstop

#include "TSNIncludes.h"

//---------------------------------------------------------------------------
#ifdef ANWIN
#pragma package(smart_init)
#endif
extern TSNUart *fake_uart_port_for_tcp_clientPtr;
/** Global functions for writing data to Program Objects.
 *
 *
 *
 */

/////////////////////////////////////////////////////////////////////////////
//
// ValueId = Value key
// ObjPtr  = Pointer to object
// InputValue   = Input string
// Flag    = Optional flag indicating the source of the input
int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, AnsiString InputValue, bool Local, bool NoErrorMessage, unsigned IDNum, int UnitId, int CurrentUnit)
{
    int Status=E_NO_ERR;
    if ( ObjPtr ) {
        if ( Master || ObjPtr->WritePermission(IDNum) ) {
#ifdef S2TXU
            OS_Use(&UnitSema);
#endif
            if ( UnitId != -1 || CurrentUnit != -1 ) {
                int OrgCurrentUnit = System_Unit[UnitId].CurrentUnit;
                System_Unit[UnitId].CurrentUnit = CurrentUnit;
                Status = ObjPtr->PutValue(ValueId, Index,InputValue,Local);
                System_Unit[UnitId].CurrentUnit = OrgCurrentUnit;
            } else {
                /*
                float Value;
                int DecPnt;
                ObjPtr->GetValue(ValueId, 0, Value, DecPnt,UnitId);
                */
                Status      = ObjPtr->PutValue(ValueId, Index,InputValue,Local,&UnitId);
                CurrentUnit = System_Unit[UnitId].CurrentUnit;
            }
#ifdef S2TXU
            OS_Unuse(&UnitSema);
#endif
        } else {
            Status = E_NO_INPUT_PERMISSION;
        }
    } else {
        //switch ( ValueId ) {
        //  default:
        Status = E_NO_ERR;
        //}
    }
    switch ( Status ) {
	case E_LOCAL_ONLY     :
		break;  // Don't send the input
	case E_NO_INPUT_PERMISSION:
		if ( !Local || Master ) break;
	default:
		if ( Local && !NoErrorMessage ) {
			InputErrorMessage(GetErrorMsg(Status));
		}
		break;
	case E_NO_ERR:
        if ( Local && !Master ) {
            //start the input response timeout timer
            //          ObjPtr->StartTimer();
            QueueANPRO10_COMMAND_201X Cmd;
            Cmd.TxInfo.Port      = fake_uart_port_for_tcp_clientPtr;
            Cmd.TxInfo.rxAddr    = DEVICE_MASTER;
            Cmd.TxInfo.rxId      = DEVICE_TCU;

            Cmd.Data.CommandNo   = CMD_TXU_INPUT_PACKET;
            Cmd.Data.ndb         = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ValueId     = ValueId;
            Cmd.Data.ObjectId    = ObjPtr->IDNumber;
            Cmd.Data.UnitId      = UnitId;
            Cmd.Data.CurrentUnit = CurrentUnit;
            strcpy((char*)Cmd.Data.InputBuffer, InputValue.c_str());
            Cmd.Data.AlternativeInput  = 0.0;
            Cmd.Data.Index             = Index;
            ANPRO10SendUrgent(&Cmd);
        } else if ( Master ) {
            QueueANPRO10_COMMAND_201X Cmd;
            Cmd.TxInfo.Port      = fake_uart_port_for_tcp_clientPtr;
            Cmd.TxInfo.rxAddr    = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId      = DEVICE_BROADCAST_TXU;
            Cmd.Data.CommandNo   = CMD_TXU_INPUT_PACKET_RES;
            Cmd.Data.ndb         = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ValueId     = ValueId;
            Cmd.Data.ObjectId    = ObjPtr->IDNumber;
            Cmd.Data.UnitId      = UnitId;
            Cmd.Data.CurrentUnit = CurrentUnit;
            strcpy((char*)Cmd.Data.InputBuffer, InputValue.c_str());
            Cmd.Data.AlternativeInput  = 0.0;
            Cmd.Data.Index             = Index;
            ANPRO10SendUrgent(&Cmd);
        }
        break;
    }
    return(Status);
}


int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, AnsiString InputValue, bool Local, bool NoErrorMessage, unsigned IDNum, int UnitId, int CurrentUnit)
{
    return LibPutValue(ValueId, 0, ObjPtr, InputValue, Local, NoErrorMessage, IDNum, UnitId, CurrentUnit);
}


int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, AnsiString InputValue, unsigned IDNum)
{
    return(LibPutValue(ValueId,Index, ObjPtr,InputValue,true,IDNum));
}


int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, AnsiString InputValue, unsigned IDNum)
{
    return(LibPutValue(ValueId,0,ObjPtr,InputValue,IDNum));
}


int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, int InputValue, unsigned IDNum)
{
    return(LibPutValue(ValueId,Index, ObjPtr,(AnsiString)InputValue,true,IDNum));
}


int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, int InputValue, unsigned IDNum)
{
    return(LibPutValue(ValueId,0, ObjPtr,InputValue,IDNum));
}


int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, float InputValue, unsigned IDNum)
{
    int Status=E_NO_ERR;
    if ( ObjPtr ) {
        if ( Master || ObjPtr->WritePermission(IDNum) ) {
            Status = ObjPtr->PutFloatValue(ValueId,InputValue);
        } else {
            Status = E_NO_INPUT_PERMISSION;
        }
    }
    return Status;
}


int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, float InputValue, unsigned IDNum)
{
    return LibPutValue(ValueId, 0, ObjPtr, InputValue, IDNum);
}


int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, unsigned IDNum)
{
    return(LibPutValue(ValueId,Index, ObjPtr,"",true,IDNum));
}


int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, unsigned IDNum)
{
    return(LibPutValue(ValueId,0, ObjPtr,"",IDNum));
}

