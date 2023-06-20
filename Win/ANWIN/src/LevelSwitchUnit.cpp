//---------------------------------------------------------------------------
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#include "TSNDefines.h"
#pragma hdrstop

#include "LevelSwitchUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "RzStatus"
#pragma link "RzButton"
#pragma resource "*.dfm"



const int TLevelSwitchForm::LineHeight = 20;
TLevelSwitchForm *LevelSwitchForm;
//---------------------------------------------------------------------------
__fastcall TLevelSwitchForm::TLevelSwitchForm(TComponent* Owner)
	: TChildForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLevelSwitchForm::InitForm(void){
	ObjectVector = PROLevelSwitch::ObjVector;
	LevelSwicthSystem = LSW_NOT_DEFINED;
	isBlink 	= true;
	StartX 		= 0;
	StartY 		= ( LineHeight - 2 );
	CurrentPage = 0;
	PageCount 	= 0;
	LastPage 	= -1;
	FirstPage 	= 1000; // Just start with a stupid hig number
	MaxXPos 	= 0;
	MaxYPos 	= 0;
	for(int i=0; i <LSW_MAX_PAGES; i++){
		YPosions[i] = 0;
	}

	if (!ObjectVector.empty()) {
		PRogramObjectBase *Element = ObjectVector[0];
		Tag = Element->Type;
		for (unsigned i = 0; i < PROLevelSwitch::ObjVector.size(); i++) {
			PROLevelSwitch *TempElement = (PROLevelSwitch *)ObjectVector[i];
			FirstPage = min(FirstPage, TempElement->Page);
			tmpXPos.push_back(TempElement->XPos);
			tmpYPos.push_back(TempElement->YPos);
		}
		for (unsigned i = 0; i < PROLevelSwitch::ObjVector.size(); i++) {
			PROLevelSwitch *TempElement = (PROLevelSwitch *)ObjectVector[i];
			tmpYPos[i] += GetPageCorrection(TempElement->Page);
			MaxXPos = MAX(MaxXPos,tmpXPos[i]);
			MaxYPos = MAX(MaxYPos,tmpYPos[i]);
			Page.insert(TempElement->Page - FirstPage+1);
			XPos.insert(tmpXPos[i]);
			YPos.insert(tmpYPos[i]);
			YPosions[TempElement->Page] = MAX(tmpYPos[i] ,YPosions[TempElement->Page]);
		}
		PageCount = Page.size();
		if (!PageCount) {
			PageCount = 1;
		}

		int XPosCnt      = XPos.size();
		int YPosCnt      = YPos.size();
		int XStep        = this->Width / (XPosCnt + 1);
		int YStep        = (this->Height - 8) / (YPosCnt + 1);
		int BWidth       = this->Width/(XPosCnt+1);
		int BHeight      = 35;
		int BXCorrection = BWidth / 2;
		int BYCorrection = BHeight / 2;

		/*
		if (PageCount> 1) {
			 ScrollBar1->Visible = true;
		}else{
			ScrollBar1->Visible = false;
		}
		*/
		int TotalHeight = ScrollBox1->Height*PageCount;
		//ScrollBox1->VertScrollBar->Range = BHeight*(MaxYPos+1);    //ScrollBox1->Height*PageCount;
		for (unsigned i = 0; i < PROLevelSwitch::ObjVector.size(); i++) {
			PROLevelSwitch *TempElement = (PROLevelSwitch *)ObjectVector[i];
			int XPosition = XStep * tmpXPos[i] - BXCorrection;
			int YPosition = YStep * tmpYPos[i] - BYCorrection;
			TRzButton *TankButtonPtr 	= new TRzButton(this);
			TankButtonPtr->Caption 		= TempElement->Name;
			TankButtonPtr->Width   		= BWidth;
			TankButtonPtr->Height  		= BHeight;
			TankButtonPtr->Left    		= XPosition;
			TankButtonPtr->Top     		= YPosition;
			TankButtonPtr->Color      	= clGreen;
			TankButtonPtr->Visible    	= true;
			TankButtonPtr->Tag        	= int(TempElement);
			TankButtonPtr->OnClick    	= RzButton1Click;
			TankButtonPtr->Parent     	= ScrollBox1;
			TankButtonPtr->DoubleBuffered = true;
			TankButtonPtr->HotTrack    	= true;
			//TankButtonPtr->TextStyle   = tsRaised;
			TankButtonPtr->Font->Color 	= clWhite;
			TankButtonPtr->ThemeAware  	= false;
			TankButton.push_back(TankButtonPtr);
		}
	}

}
void __fastcall TLevelSwitchForm::RzButton1Click(TObject *Sender)
{
	TRzButton *ButtonPtr = (TRzButton*)Sender;
	if (ButtonPtr->Tag) {
		PROLevelSwitch *TempElement = (PROLevelSwitch *)ButtonPtr->Tag;
		AlarmLevelSwitch *AlPtr = TempElement->LevelSwitchAlPtr;
		switch (AlPtr->State) {
		case AlarmBasic::AlActive :
			if (!(NetworkOK || UseNetwork) ||
				AlarmCriticalComFailure::ComFailure) {
				AlPtr->MoveAlarmToAknowledge();
			}
			else {
				AlPtr->SendData(CMD_PRO_ALARM_ACK);
			}
			break;
		case AlarmBasic::AlIdle :
		case AlarmBasic::AlAknowledged:
		case AlarmBasic::AlBlocked :
			break;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TLevelSwitchForm::Timer1Timer(TObject *Sender)
{
	TTimer *TimerPtr = (TTimer*)Sender;

	for (unsigned i = 0; i < PROLevelSwitch::ObjVector.size(); i++) {
		SetButtonColours(TankButton[i], (PROLevelSwitch*)ObjectVector[i]);
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
void __fastcall TLevelSwitchForm::SetButtonColours(TRzButton *TButton, PROLevelSwitch *LSwitchPtr) {

	if (LSwitchPtr) {
		TColor BackColor1;
		TColor BackColor2;
		if (LSwitchPtr->IsWarning) {
			BackColor1 = TColor(0x00149BF0);//TDU_C_AL_BACK_ACTIVE_95; //$00149BF0
			BackColor2 = TColor(0x000A4D78);//TDU_C_AL_BACK_ACTIVE_95; //$00149BF0
		} else {
			BackColor1 = clRed;
			BackColor2 = TColor(0x00000088);
		}
		switch (LSwitchPtr->LevelSwitchAlPtr->State) {
		case AlarmBasic::AlActive:
			// Let us blink
			if (isBlink) {
				TButton->Color 		 = BackColor1;
  //				TButton->Font->Color = clWhite; //TDU_C_AL_TEXT_ACTIVE;
			} else {
				TButton->Color 		 = BackColor2;//DU_C_AL_TEXT_ACTIVE;
//				TButton->Font->Color = clBlack;
			}
			break;
		case AlarmBasic::AlAknowledged:
			if (TButton->Color != BackColor2) {
				TButton->Color 		 = BackColor2;
				//TButton->Font->Color = TDU_C_AL_TEXT_ACTIVE;
			}
			break;
		case AlarmBasic::AlIdle:
		default:
			if (LSwitchPtr->HWFailure
				|| LSwitchPtr->LevelSwitchSensor->ActiveAlarms
				|| !LSwitchPtr->LevelSwitchSensor->Enable
				|| !LSwitchPtr->LevelSwitchAlPtr->Enable) {
				TButton->Color 		 = TDU_C_AL_BACK_WARNING;
				//TButton->Font->Color = TDU_C_AL_TEXT_WARNING;
			} else if (TButton->Color != TDU_C_AL_BACK_NOAL) {
				TButton->Color 		 = TDU_C_AL_BACK_NOAL;
				//TButton->Font->Color = TDU_C_AL_TEXT_NOAL;
			}
			break;
		}
	} else {
		// Should never get here!
		if (TButton->Color != TDU_C_BU_BACK) {
			TButton->Color 		 = TDU_C_BU_BACK;
			//TButton->Font->Color = TDU_C_BU_TEXT;
			TButton->Visible     = false;
		}
	}

}

int __fastcall TLevelSwitchForm::GetPageCorrection(int CurrentPage){
	int PageCorrection = 0;
	for(int i=0; i < CurrentPage; i++){
		PageCorrection += YPosions[i];
	}
	return PageCorrection;
}
void __fastcall TLevelSwitchForm::RzBitBtn1Click(TObject *Sender)
{
	TRzBitBtn *tmpButtPtr = (TRzBitBtn*)Sender;
	if (tmpButtPtr->ImageIndex == 19) {
		tmpButtPtr->ImageIndex = 20;
		tmpButtPtr->Caption = "Activate";
		LibPutValue(SVT_TANK_STATE_STR_LSW, PROTanksystemUnit::MySelf->IDNumber, PROSystemData::TXUSystemData, tSeaGoing);

	}else{
		tmpButtPtr->ImageIndex = 19;
		tmpButtPtr->Caption = "Deactivate";
        LibPutValue(SVT_TANK_STATE_STR_LSW, PROTanksystemUnit::MySelf->IDNumber, PROSystemData::TXUSystemData, tLoad);
	}
}
//---------------------------------------------------------------------------

void __fastcall TLevelSwitchForm::ScrollBox1Resize(TObject *Sender)
{
	TScrollBox *tmpPtr = (TScrollBox*)Sender;
	int XPosCnt      = XPos.size();
	int YPosCnt      = YPos.size();
	int XStep        = tmpPtr->Width / (XPosCnt + 1);
	int YStep        = (tmpPtr->Height - 8) / (YPosCnt + 1);
	int BWidth       = tmpPtr->Width /(XPosCnt+1);
	int BHeight      = tmpPtr->Height/(YPosCnt+1);//35;
	int BXCorrection = BWidth / 2;
	int BYCorrection = BHeight / 2;

	int TotalHeight = tmpPtr->Height*PageCount;
	//tmpPtr->VertScrollBar->Range = BHeight*(MaxYPos+1);    //ScrollBox1->Height*PageCount;
	//tmpPtr->HorzScrollBar->Range = BWidth *(MaxXPos+1);    //ScrollBox1->Height*PageCount;
	for (unsigned i = 0; i < ObjectVector.size(); i++) {
		PROLevelSwitch *TempElement = (PROLevelSwitch *)ObjectVector[i];
		int XPosition = XStep * tmpXPos[i]  - BXCorrection;
		int YPosition = YStep * tmpYPos[i]  - BYCorrection;
		TankButton[i]->Width   = BWidth;
		TankButton[i]->Height  = BHeight;
		TankButton[i]->Left    = XPosition;
		TankButton[i]->Top     = YPosition;
	}
}
//---------------------------------------------------------------------------


void __fastcall TLevelSwitchForm::FormCreate(TObject *Sender)
{
	TChildForm::Init();
	InitForm();

}
//---------------------------------------------------------------------------


