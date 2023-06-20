//---------------------------------------------------------------------------
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#include "TSNDefines.h"
#pragma hdrstop
#include "RzButton.hpp"

#include "ModbusDigitalInputUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"
TModbusDigitalInputForm *ModbusDigitalInputForm;
//---------------------------------------------------------------------------
__fastcall TModbusDigitalInputForm::TModbusDigitalInputForm(TComponent* Owner)
	: TChildForm(Owner)
{
	InitForm();
}
//---------------------------------------------------------------------------
void __fastcall TModbusDigitalInputForm::InitForm(void){
	set<PRogramObjectBase *>::iterator pBIt;
	for (pBIt = ModbusCoilIn::ModbusSet.begin(); pBIt != ModbusCoilIn::ModbusSet.end(); pBIt++) {
		ModbusObject *tmpPtr = (ModbusObject *)*pBIt;
		ObjectVector.push_back(tmpPtr);
		if (tmpPtr->GetAlarmPtr()) {
			myObjectVector[0].push_back(tmpPtr);
		}else{
			myObjectVector[1].push_back(tmpPtr);
		}
	}
	int Sz = ModbusRegBitIn::ModbusSet.size();
	for (pBIt = ModbusRegBitIn::ModbusSet.begin(); pBIt != ModbusRegBitIn::ModbusSet.end(); pBIt++) {
		ModbusObject *tmpPtr = (ModbusObject *)*pBIt;
		ObjectVector.push_back(tmpPtr);
		myObjectVector[2].push_back(tmpPtr);
	}
	PRogramObjectBase *Element = ObjectVector[0];
	Tag = Element->Type;

	TWinControl *ParentPtr[NUMBER_OF_SCROLLBOXES]={ScrollBox1,ScrollBox2,ScrollBox3};
	for(int i=0; i < NUMBER_OF_SCROLLBOXES; i++){
		int XPosCnt      = 1;
		int YPosCnt      = myObjectVector[i].size();
		int BWidth       = ParentPtr[i]->Width/(XPosCnt+1);
		int XStep        = ParentPtr[i]->Width / (XPosCnt + 1);
		int BHeight      = ParentPtr[i]->Height/(YPosCnt+1);;
		int YStep        = BHeight+5;
		int BXCorrection = BWidth / 2;
		int BYCorrection = BHeight / 2;

		//ScrollBox1->VertScrollBar->Range = YStep*ObjectVector.size();
		 // Currently ignore ReadPermission
		int XPos = 1;
		int YPos = 1;
		for (unsigned j=0; j < myObjectVector[i].size(); j++) {
			ModbusObject *tmpPtr = myObjectVector[i][j];
			int XPosition = XStep * XPos - BXCorrection;
			int YPosition = YStep * YPos - BYCorrection;
			YPos++;
			TRzButton *tmpButtonPtr = new TRzButton( ParentPtr[i]);
			TankButton[i].push_back(tmpButtonPtr);
			tmpButtonPtr->Caption 		= tmpPtr->Name+" "+ tmpPtr->Description;
			tmpButtonPtr->Width   		= BWidth;
			tmpButtonPtr->Height  		= BHeight;
			tmpButtonPtr->Left    		= XPosition;
			tmpButtonPtr->Top     		= YPosition;
			tmpButtonPtr->Color      	= clGreen;
			tmpButtonPtr->Visible    	= true;
			tmpButtonPtr->Tag        	= int(tmpPtr);
			tmpButtonPtr->OnClick    	= RzButtonClick;
			tmpButtonPtr->Parent     	= ParentPtr[i];
			tmpButtonPtr->DoubleBuffered = true;
			tmpButtonPtr->HotTrack    	= true;
			//tmpButtonPtr->TextStyle   = tsRaised;
			tmpButtonPtr->Font->Color 	= clWhite;
			tmpButtonPtr->ThemeAware  	= false;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TModbusDigitalInputForm::SetButtonColours(TRzButton *TButton, ModbusObject *ModbusDigInPtr) {

	if (ModbusDigInPtr) {
		AlarmBasic *tmpAlPtr = ModbusDigInPtr->GetAlarmPtr();
		if (tmpAlPtr) {
			switch (ModbusDigInPtr->GetAlarmPtr()->State) {
			case AlarmBasic::AlActive:
				// Let us blink
				if (isBlink) {
					TButton->Color 		 = clRed;
	  //				TButton->Font->Color = clWhite; //TDU_C_AL_TEXT_ACTIVE;
				} else {
					TButton->Color 		 = TColor(0x00000088);;//DU_C_AL_TEXT_ACTIVE;
	//				TButton->Font->Color = clBlack;
				}
				break;
			case AlarmBasic::AlAknowledged:
				if (TButton->Color != TColor(0x00000088)) {
					TButton->Color 		 = TColor(0x00000088);
					//TButton->Font->Color = TDU_C_AL_TEXT_ACTIVE;
				}
				break;
			case AlarmBasic::AlIdle:
			default:
				if (TButton->Color != TDU_C_AL_BACK_NOAL) {
					TButton->Color 		 = TDU_C_AL_BACK_NOAL;
					//TButton->Font->Color = TDU_C_AL_TEXT_NOAL;
				}
				break;
			}
		} else {
			if (ModbusDigInPtr->GetDigitalStatus()){
				TButton->Color 		 = clRed;
			}else{
				TButton->Color 		 = clGreen;
			}
		}
	}

}

//---------------------------------------------------------------------------
void __fastcall TModbusDigitalInputForm::RzButtonClick(TObject *Sender)
{
	TRzButton *ButtonPtr = (TRzButton*)Sender;
	if (ButtonPtr->Tag) {
		ModbusCoilIn *TempElement = (ModbusCoilIn *)ButtonPtr->Tag;
		AlarmBasic *AlPtr = (AlarmBasic*)TempElement->GetAlarmPtr();
		if (AlPtr) {
			switch (AlPtr->State) {
			case AlarmBasic::AlActive :
				if (!(NetworkOK || UseNetwork) ||
					AlarmCriticalComFailure::ComFailure) {
					AlPtr->MoveAlarmToAknowledge();
				}
				else {
					// Must reset on TDU
					//AlPtr->SendData(CMD_PRO_ALARM_ACK);
				}
				break;
			case AlarmBasic::AlIdle :
			case AlarmBasic::AlAknowledged:
			case AlarmBasic::AlBlocked :
				break;
			}
		}
	}

}
void __fastcall TModbusDigitalInputForm::Timer1Timer(TObject *Sender)
{
	TTimer *TimerPtr = (TTimer*)Sender;
	for (unsigned i = 0; i < NUMBER_OF_SCROLLBOXES; i++) {
		for (unsigned j = 0; j < myObjectVector[i].size(); j++) {
			SetButtonColours(TankButton[i][j], (ModbusObject*)myObjectVector[i][j]);
		}
	}
	if (isBlink) {
		isBlink = false;
		TimerPtr->Interval = 1000;
	}else{
		isBlink = true;
		TimerPtr->Interval = 500;
	}
}
//---------------------------------------------------------------------------
void __fastcall TModbusDigitalInputForm::ScrollBox1Resize(TObject *Sender)
{
	static TWinControl *ParentPtr[NUMBER_OF_SCROLLBOXES]={ScrollBox1,ScrollBox2,ScrollBox3};

	for(int i=0; i < NUMBER_OF_SCROLLBOXES; i++){
		//ParentPtr[i]->VertScrollBar->Position = 0;
		TPanel *tmpPtr   = (TPanel*)Sender;
		int XPosCnt      = 1;
		int YPosCnt      = myObjectVector[i].size();
		int BWidth       = ParentPtr[i]->Width/(XPosCnt+1);
		int BHeight      = 35;
		int XStep        = ParentPtr[i]->Width / (XPosCnt + 1);
		int YStep        = BHeight+5;
		int BXCorrection = BWidth / 2;
		int BYCorrection = BHeight / 2;

		int XPos = 1;
		int YPos = 1;

		for (unsigned j = 0; j < myObjectVector[i].size(); j++) {
			int XPosition = XStep * XPos - BXCorrection;
			int YPosition = YStep * YPos - BYCorrection;
			YPos++;
			TankButton[i][j]->Width   = BWidth;
			TankButton[i][j]->Height  = BHeight;
			TankButton[i][j]->Left    = XPosition;
			TankButton[i][j]->Top     = YPosition;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TModbusDigitalInputForm::FormDestroy(TObject *Sender)
{
	for (int i=0; i < NUMBER_OF_SCROLLBOXES; i++) {
		for(unsigned j=0; j < TankButton[i].size(); j++){
			delete TankButton[i][j];
		}
	}
	TChildForm::FormDestroy(Sender);
}
//---------------------------------------------------------------------------



