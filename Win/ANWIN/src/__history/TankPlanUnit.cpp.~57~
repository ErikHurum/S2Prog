#include "ANWinInc.h"
#pragma hdrstop
USEFORM("TankObjectUnit.cpp", TankObjectForm);
#include <fstream.h>
#include <iostream.h>
#include <iomanip.h>
#include "stdio.h"
#include <dir.h>
#include <stdlib.h>
#include <Printers.hpp>
#include <Registry.hpp>
#include "TankPlanUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "RzPanel"
#pragma link "ES.BaseControls"
#pragma link "ES.PaintBox"
#pragma link "AdvMenus"
#pragma resource "*.dfm"
#pragma warn -8057
TTankPlanDrawingForm *TankPlanDrawingForm;
//-----------------------------------------------
#pragma warn -8057
//-----------------------------------------------
__fastcall TTankPlanDrawingForm::TTankPlanDrawingForm(TComponent* Owner,
											  vector<PRogramObjectBase*> ObjVector, const char* fileName)    : TChildForm(Owner,ObjVector,fileName)
{
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::PopupMenuValueTypeExecute(TObject *Sender){
    TMenuItem *TempItem = (TMenuItem *)Sender;
    if (TempItem) {
        ValueKey    = TempItem->Tag;
        ValueTypeLabel->Caption = TempItem->Caption;
		RefreshForm = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::AssignToPanelList(int Index, TShape* Shape,TLabel* CargoLabel,TLabel* sumLabel,TLabel* VolumeLabel, TRzPanel* Panel)
{
	LegendStruct tmpLegend = {Shape,CargoLabel,sumLabel,VolumeLabel,Panel};
	PanelList[Index] = tmpLegend;
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::MakeLabelList(void)
{
	int counter=0;
	AssignToPanelList(counter++,Shape1 ,CargoLabel1 ,sumLabel1 ,VolumeLabel1 ,Panel1 );
	AssignToPanelList(counter++,Shape2 ,CargoLabel2 ,sumLabel2 ,VolumeLabel2 ,Panel2 );
	AssignToPanelList(counter++,Shape3 ,CargoLabel3 ,sumLabel3 ,VolumeLabel3 ,(TRzPanel*)Panel3 );
	AssignToPanelList(counter++,Shape4 ,CargoLabel4 ,sumLabel4 ,VolumeLabel4 ,(TRzPanel*)Panel4 );
	AssignToPanelList(counter++,Shape5 ,CargoLabel5 ,sumLabel5 ,VolumeLabel5 ,(TRzPanel*)Panel5 );
	AssignToPanelList(counter++,Shape6 ,CargoLabel6 ,sumLabel6 ,VolumeLabel6 ,(TRzPanel*)Panel6 );
	AssignToPanelList(counter++,Shape7 ,CargoLabel7 ,sumLabel7 ,VolumeLabel7 ,(TRzPanel*)Panel7 );
	AssignToPanelList(counter++,Shape8 ,CargoLabel8 ,sumLabel8 ,VolumeLabel8 ,(TRzPanel*)Panel8 );
	AssignToPanelList(counter++,Shape9 ,CargoLabel9 ,sumLabel9 ,VolumeLabel9 ,(TRzPanel*)Panel9 );
	AssignToPanelList(counter++,Shape10,CargoLabel10,sumLabel10,VolumeLabel10,(TRzPanel*)Panel10);
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::use_file(const char* fileName)
{
    char old_dir[MAXDIR];
    if (getcurdir(0, old_dir)) {
        exit(1);
	}
	int Cnt = 0;
   if (!chdir(SurveyorDirPath.c_str())) {
		ifstream InDrawFile(fileName);
		if (InDrawFile) {
			char c[2000];
			while ( InDrawFile.getline(c,sizeof(InDrawFile))) {
				LineList->Add(c);
				Cnt++;
			}

		} else {
		}
	}
    AnsiString temp = "\\"+(AnsiString)old_dir;
    if (chdir(temp.c_str())) {
		exit(1);
    }
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::FindTankPoints()
{
	int Ind=-1;
	while ((LineList->Count-1 > ++Ind) && (LineList->Strings[Ind].Trim() != "ENTITIES")) {
	};

    // while(LineList->Strings[++Ind].Trim() != "LWPOLYLINE"){
    // };

	do {
		if (LineList->Strings[Ind].Trim() == "AcDbPolyline" &&
			LineList->Strings[Ind+1].Trim() == "90" &&
			(LineList->Strings[Ind+2].Trim()).ToInt()>0) {
			SetTankXYPoints(Ind);

		}
		if (LineList->Strings[Ind].Trim()=="AcDbText" && LineList->Strings[Ind+1].Trim()=="10") {
			AnsiString tmpStr = LineList->Strings[Ind+10].SubString(1, 3);
			if ( tmpStr == "_tn" ) {
				SetTankNamePoints(Ind);
			} else if ( tmpStr == "_tv" ) {
                SetTankValuePoints(Ind);
            } else if ( tmpStr == "_ta" ) {
                SetTankAlarmPoints(Ind);
            }
        }
    }while (LineList->Strings[Ind++].Trim() != "ENDSEC" );
	if (!TankValuePoint.empty() && !TankNamePoint.empty() ) {
        HasValueAndNameIndex    = true;
        ShowHideButton->Visible = false;
    } else {
		CopyTankNamePointsToValuePoints();
    }
    if ( MaxX == MinX) {
        MinX = MaxX -100;
    }
	ScaleCoeffW = (MaxX - MinX)/(Width -40);
	ScaleCoeffH = (MaxY - MinY)/(Height -300);
    LineList->Clear();

}


void __fastcall  TTankPlanDrawingForm::SetTankXYPoints(int index )
{
	++index; // 90
//  int NumberOfCorner =(LineList->Strings[++index].Trim()).ToDouble();
    int NumberOfCorner =(LineList->Strings[++index].Trim()).ToInt();
/*  ++index; // 70
    ++index; // 70
    ++index; // 43
    ++index; // 43     */
    if (NumberOfCorner>0) {
        String T;
        while (LineList->Strings[++index +1].Trim() != "10" ) {
        }
        vector<PointStruct>tmpPVect;
        for (int k=0; k<NumberOfCorner; k++) {
            ++index; // 10
            float X = _wtof(LineList->Strings[++index].Trim().c_str());
            ++index; // 20
            float Y = _wtof(LineList->Strings[++index].Trim().c_str());
            PointStruct tmpPoint = {{X,Y},{X,Y}};
            tmpPVect.push_back( tmpPoint);
			MaxX = max(X,MaxX);
            MinX = min(X,MinX);
            MaxY = max(Y,MaxY);
            MinY = min(Y,MinY);
        }
		TankPoint.push_back(tmpPVect);
	}
}
//---------------------------------------------------------------------------

bool __fastcall  TTankPlanDrawingForm::SetTankNamePoints(int index)
{
    bool tankFound = false;
    ++index; // 10
	float X = _wtof(LineList->Strings[++index].Trim().c_str());
	++index; // 20
	float Y = _wtof(LineList->Strings[++index].Trim().c_str());
	AnsiString temp = LineList->Strings[index+6].SubString(5, 10);
	PROTank *TempPRO = (PROTank*)FindCompFromTagName(Tag, temp);
	if (TempPRO) {
		TankPointStruct tmpPoint = {{{X,Y},{X,Y}},TempPRO};
        TankNamePoint.push_back(tmpPoint);
        tankFound = true;
    }
	return tankFound;
}
//---------------------------------------------------------------------------

bool __fastcall  TTankPlanDrawingForm::SetTankValuePoints(int index)
{
    bool tankFound = false;
    ++index; // 10
    float X = _wtof(LineList->Strings[++index].Trim().c_str());
    ++index; // 20
    float Y = _wtof(LineList->Strings[++index].Trim().c_str());
    AnsiString temp = LineList->Strings[index+6].SubString(5, 10);
	PROTank *TempPRO = (PROTank*)FindCompFromTagName(Tag, temp);
	if (TempPRO) {
		TankPointStruct tmpPoint = {{{X,Y},{X,Y}},TempPRO};
        TankValuePoint.push_back(tmpPoint);
		tankFound = true;
    }
    return tankFound;
}
//---------------------------------------------------------------------------

bool __fastcall  TTankPlanDrawingForm::SetTankAlarmPoints(int index) {
    bool tankFound = false;
	++index; // 10
    float X = _wtof(LineList->Strings[++index].Trim().c_str());
    ++index; // 20
	float Y = _wtof(LineList->Strings[++index].Trim().c_str());
	AnsiString 	tmpStr1		 	= LineList->Strings[index + 6].SubString(5, 10);
	int 		SeparatorPos1 	= tmpStr1.AnsiPos(' ');
	AnsiString 	TankNumber 	 	= tmpStr1.SubString(1,SeparatorPos1-1);
	AnsiString  tmpStr2 		= tmpStr1.SubString(SeparatorPos1+1,tmpStr1.Length()-SeparatorPos1);
	int 		SeparatorPos2 	= tmpStr2.AnsiPos(' ');
	AnsiString 	AlarmIdTypeStr	= tmpStr2.SubString(1,SeparatorPos2-1);
	int         AlarmIdType     = AlarmIdTypeStr.ToInt();
	AnsiString  tmpStr3 		= tmpStr2.SubString(SeparatorPos2+1,tmpStr2.Length()-SeparatorPos2);
	int         AlarmIndex	    = tmpStr3.ToInt()-1;

	//AlarmIdTypeStr.ToInt();
	PROTank *TempPRO = (PROTank *)FindCompFromTagName(Tag, TankNumber);
	if ( TempPRO ) {
		AlarmPointStruct tmpPoint = { { { X, Y }, { X, Y } }, TempPRO,AlarmIdType,AlarmIndex };
		TankAlarmPoint.push_back(tmpPoint);
		AlarmColorVect.push_back(clBtnFace);
		tankFound = true;
    }
    return tankFound;
}


//---------------------------------------------------------------------------
void __fastcall  TTankPlanDrawingForm::CopyTankNamePointsToValuePoints(void)
{
    TankValuePoint = TankNamePoint;
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::CreatePolygonRegion()
{
    AnsiString ErrorTank;
    if (!TankRegion.empty()) {
        for(unsigned i=0; i < TankRegion.size(); i++){
            DeleteObject(TankRegion[i]);
        }
        TankRegion.clear();
    }
    TankRegionNameMap.clear();
    for (unsigned j=0; j<TankPoint.size(); j++) {
        POINT tmpArray[MAX_DRAWINGPOINT_TANK];
        for (unsigned i=0; i < TankPoint[j].size(); i++) {
            tmpArray[i] = TankPoint[j][i].Point;
        }
        HRGN tmpRgn = CreatePolygonRgn(tmpArray,TankPoint[j].size(),ALTERNATE );
        TankRegion.push_back(tmpRgn);
    }
    // Let us make a link between any region to tanks. A tank can then be in several regions
    for (unsigned j=0; j<TankNamePoint.size(); j++) {
        for(unsigned i=0; i < TankRegion.size(); i++){
            if ( PtInRegion(TankRegion[i],TankNamePoint[j].ObjPoint.Point.x,TankNamePoint[j].ObjPoint.Point.y) ){
                if ( TankRegionNameMap.insert(pair<int, PROTank*>(i, TankNamePoint[j].TankPtr)).second){
                }else{
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::RecalcXYPoints()
{
    for (unsigned j=0; j<TankPoint.size(); j++) {
        for (unsigned k=0; k<TankPoint[j].size(); k++) {
            TankPoint[j][k].DefaultPoint.x= TankPoint[j][k].DefaultPoint.x - MinX ;
            TankPoint[j][k].DefaultPoint.y= MaxY - TankPoint[j][k].DefaultPoint.y ;
        }
    }
    for (unsigned j=0; j<TankNamePoint.size(); j++) {
        TankNamePoint[j].ObjPoint.DefaultPoint.x= TankNamePoint[j].ObjPoint.DefaultPoint.x - MinX;
        TankNamePoint[j].ObjPoint.DefaultPoint.y= MaxY - TankNamePoint[j].ObjPoint.DefaultPoint.y;
    }
	for (unsigned j=0; j<TankValuePoint.size(); j++) {
		TankValuePoint[j].ObjPoint.DefaultPoint.x= TankValuePoint[j].ObjPoint.DefaultPoint.x - MinX;
		TankValuePoint[j].ObjPoint.DefaultPoint.y= MaxY - TankValuePoint[j].ObjPoint.DefaultPoint.y;
	}
	for (unsigned j=0; j<TankAlarmPoint.size(); j++) {
		TankAlarmPoint[j].ObjPoint.DefaultPoint.x= TankAlarmPoint[j].ObjPoint.DefaultPoint.x - MinX;
		TankAlarmPoint[j].ObjPoint.DefaultPoint.y= MaxY - TankAlarmPoint[j].ObjPoint.DefaultPoint.y;
	}
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::ScaleTPDrawing()
{
	if (SpaceRound) {
		PaintBoxPanel->Height = (MaxY - MinY)/ScaleCoeffH +2*SpaceRound;
		PaintBoxPanel->Width  = (MaxX - MinX)/ScaleCoeffW +SpaceRound;
	}

	for (unsigned j=0; j<TankPoint.size(); j++) {
		for (unsigned k=0; k<TankPoint[j].size(); k++) {
            TankPoint[j][k].Point.x= TankPoint[j][k].DefaultPoint.x/ScaleCoeffW +SpaceRound/2;
            TankPoint[j][k].Point.y= TankPoint[j][k].DefaultPoint.y/ScaleCoeffH +SpaceRound;
        }
    }
    for (unsigned j=0; j<TankNamePoint.size(); j++) {
        TankNamePoint[j].ObjPoint.Point.x= TankNamePoint[j].ObjPoint.DefaultPoint.x/ScaleCoeffW +SpaceRound/2;
		TankNamePoint[j].ObjPoint.Point.y= TankNamePoint[j].ObjPoint.DefaultPoint.y/ScaleCoeffH +SpaceRound;
    }
	for (unsigned j=0; j<TankValuePoint.size(); j++) {
		TankValuePoint[j].ObjPoint.Point.x= TankValuePoint[j].ObjPoint.DefaultPoint.x/ScaleCoeffW +SpaceRound/2;
		TankValuePoint[j].ObjPoint.Point.y= TankValuePoint[j].ObjPoint.DefaultPoint.y/ScaleCoeffH +SpaceRound;
	}
	for (unsigned j=0; j<TankAlarmPoint.size(); j++) {
		TankAlarmPoint[j].ObjPoint.Point.x= TankAlarmPoint[j].ObjPoint.DefaultPoint.x/ScaleCoeffW +SpaceRound/2;
		TankAlarmPoint[j].ObjPoint.Point.y= TankAlarmPoint[j].ObjPoint.DefaultPoint.y/ScaleCoeffH +SpaceRound;
	}
}
//---------------------------------------------------------------------------


void __fastcall  TTankPlanDrawingForm::DrawAllTanks(TCanvas *Canvas)
{
	for (unsigned j=0; j<TankPoint.size(); j++) {
		map<int, PROTank*>::iterator TankMapIterator = TankRegionNameMap.find(j);
		PROTank *tempTank;
		if ( TankMapIterator != TankRegionNameMap.end() ) {
            tempTank = TankMapIterator->second;
        } else {
			tempTank = NULL;
        }
		/*Canvas->Pen->Color = clBlack;
		if (tempTank) {
			Canvas->Brush->Color = (TColor)tempTank->CargoType->Colour;;
		} else {
			Canvas->Brush->Color = clBtnFace;
		}*/
		TColor textColor = clBlack;
		TColor backgroundColor = clBtnFace;

		GetTankDisplayColors(tempTank, &backgroundColor, &textColor);
		Canvas->Pen->Color = textColor;
		Canvas->Brush->Color = backgroundColor;
		POINT tmpArray[MAX_DRAWINGPOINT_TANK];
		unsigned Sz = TankPoint[j].size();
		for (unsigned i=0; i < TankPoint[j].size(); i++) {
			tmpArray[i] = TankPoint[j][i].Point;
		}
		Canvas->Polygon((TPoint*)tmpArray,TankPoint[j].size()-1);
		/*
		// To display the sensor and referece locations
		if (tempTank) {
			float XScale = CargoPaintBox->Width/PROProjectInfo::PROProjectInfoPtr->LengthBetweenPP;
			float YScale = CargoPaintBox->Height/PROProjectInfo::PROProjectInfoPtr->Width;
			int XPos = XScale*(PROProjectInfo::PROProjectInfoPtr->LengthBetweenPP/2-tempTank->DLManMsrPntToSns);
			int YPos = YScale*(PROProjectInfo::PROProjectInfoPtr->Width/2-tempTank->DTManMsrPntToSns);
			CargoPaintBox->Canvas->AngleArc(XPos,YPos,10,0.0,360.0);
		}
		*/
	}
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::ShowTankNames(TCanvas *Canvas)
{
	for (unsigned j=0; j<TankNamePoint.size(); j++) {
		Canvas->Brush->Color  = clWebLemonChiffon;//clYellow;
		Canvas->Pen->Color    = clWebLemonChiffon;//clYellow;
		Canvas->Font->Color   = clWindowText;
		AnsiString NameOnTank = TankNamePoint[j].TankPtr->Name;
		Canvas->TextOut(TankNamePoint[j].ObjPoint.Point.x,TankNamePoint[j].ObjPoint.Point.y-10 ,NameOnTank);
    }
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::HideTankNames()
{
}
//---------------------------------------------------------------------------


void __fastcall TTankPlanDrawingForm::ShowHideButtonMouseDown(TObject *Sender,
														  TMouseButton Button, TShiftState Shift, int X, int Y)
{
	EsPaintBox1->Repaint();
	HoldUpdate = true;
}
//---------------------------------------------------------------------------


void __fastcall  TTankPlanDrawingForm::BlankValues(AnsiString Msg)
{
    TankNameLabel->Caption = Msg;
    UValueLabel->Caption = "";
    VProsentValueLabel->Caption = "";
    WValueLabel->Caption = "";
    VValueLabel->Caption = "";
    TValueLabel->Caption = "";
    CargoColorShape->Brush->Color = clBtnFace;
    CargoTypeLabel->Caption = "";
    OpModeLabel->Caption = "";
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::UpdateValues(void)
{
    if (CurrentTankPtr) {
        AnsiString tempValue,unitstr, VolumeUnitStr,WeightUnitStr;
        TankNameLabel->Caption = CurrentTankPtr->Name;
        CargoColorShape->Brush->Color = ((PROTank*)CurrentTankPtr)->CargoType->Colour;
        CargoTypeLabel->Caption = LibGetValue(SVT_CARGO_TYPE_NAME,CurrentTankPtr);

        tempValue = LibGetValue(SVT_VOLUME,CurrentTankPtr,&VolumeUnitStr);
        tempValue = LibGetValue(SVT_WEIGHT,CurrentTankPtr,&WeightUnitStr);
        VolumeUnitLabel1->Caption = VolumeUnitStr;
        VolumeUnitLabel2->Caption = VolumeUnitStr;
		WeightUnitLabel1->Caption = WeightUnitStr;
		WeightUnitLabel2->Caption = WeightUnitStr;

        if ( CurrentTankPtr->Type == C_PRO_CARGO ) {
			//Ullage
            if (ULabel->Caption != "Ullage") ULabel->Caption = "Ullage";
            UValueLabel->Caption = LibGetValue(SVT_ULLAGE_UTI,CurrentTankPtr,&unitstr);
            UUnitLabel->Caption = unitstr;
        } else {
            //Level
			if (ULabel->Caption != "Level") ULabel->Caption = "Level";
			UValueLabel->Caption = LibGetValue(SVT_LEVEL_REF,CurrentTankPtr,&unitstr);
            UUnitLabel->Caption = unitstr;
        }
//Volume%
        VProsentValueLabel->Caption = LibGetValue(SVT_VOLPERCENT,CurrentTankPtr,&unitstr);
//Weight
        WValueLabel->Caption = LibGetValue(SVT_WEIGHT,CurrentTankPtr,&unitstr);
        WUnitLabel->Caption = unitstr;
//Volume
		VValueLabel->Caption = LibGetValue(SVT_VOLUME,CurrentTankPtr,&unitstr);
        VUnitLabel->Caption = unitstr;
//Temp
        TValueLabel->Caption = LibGetValue(SVT_TEMP,CurrentTankPtr,&unitstr);
        TUnitLabel->Caption = unitstr;
// OpMode
        OpModeLabel->Caption = LibGetValue(SVT_TANK_STATE_STR,CurrentTankPtr,&unitstr);

    }
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::ShowtankClick(TObject *Sender)
{
    if ( CurrentTankPtr && CurrentTankPtr->ReadPermission() ) {
        AnsiString WinName = "TankObject"+CurrentTankPtr->IdNumString();
        TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
        if (WinPtr) {
            WinPtr->BringToFront();
        }else{
            Application->CreateForm(__classid(TTankObjectForm), &TankObjectForm);
            WinPtr = (TChildForm*)TankObjectForm;
            WinPtr->Name = WinName;
        }
		WinPtr->SetObjectPtr((PROXRefObject*)CurrentTankPtr);
    }
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::UppdateValue(TCanvas *Canvas)
{
	bool HasUnit=false;
	if (ValueKey>0) {
		for (unsigned j=0; j<TankValuePoint.size(); j++) {
			AnsiString tempValue,unitstr;
			Canvas->Brush->Color = clWebLemonChiffon;//clYellow;
			Canvas->Pen->Color = clWebLemonChiffon;//clYellow;
			Canvas->Font->Color = clWindowText;
			PROTank *tempTank = TankValuePoint[j].TankPtr;
			if ( tempTank->ReadPermission()) {
				tempValue = LibGetValue(ValueKey,tempTank,&unitstr);
				Canvas->TextOut(TankValuePoint[j].ObjPoint.Point.x,TankValuePoint[j].ObjPoint.Point.y-10,tempValue);
				if (!HasUnit) {
					HasUnit =true;
					ValueUnitLabel->Caption = unitstr;
				}
			}
		}
	}
	if ( HasValueAndNameIndex ) {
		ShowTankNames(Canvas);
	}

}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::UppdateAlarms(TCanvas *Canvas)
{
	for (unsigned j=0; j<TankAlarmPoint.size(); j++) {
		AnsiString tempValue,unitstr;
		Canvas->Brush->Color = clWebLemonChiffon;//clYellow;
		Canvas->Pen->Color   = clWebLemonChiffon;//clYellow;
		Canvas->Font->Color  = clWindowText;
		PROTank *tempTank 	 = TankAlarmPoint[j].TankPtr;
		unsigned AlarmTypeId = TankAlarmPoint[j].AlarmTypeId;
		unsigned Alarmindex  = TankAlarmPoint[j].AlarmIndex;
		int x           	 = TankAlarmPoint[j].ObjPoint.Point.x;
		int y           	 = TankAlarmPoint[j].ObjPoint.Point.y;

		if ( tempTank->ReadPermission()) {
			switch(AlarmTypeId){
			case ID_AL_TWM_LOW_SPEED:
				{
					vector<PROTankWashingMachine *> TankWashingMachineVector = tempTank->TankWashingMachineVector;
					if ( !TankWashingMachineVector.empty()&& Alarmindex < TankWashingMachineVector.size() ){
						PROTankWashingMachine* TWMPtr = TankWashingMachineVector[Alarmindex];
						AlarmBasic::AlarmState State= TWMPtr->GetLowSpeedAlarmState();
						//        AlIdle,AlActive,AlAknowledged,AlBlocked,AlError
						switch( TWMPtr->GetRunningState()){
							case tcmos_running	:
								switch(State){
									case AlarmBasic::AlIdle:
										if ( AlarmBlink ){
											Canvas->Brush->Color = clGreen;
										}else{
											Canvas->Brush->Color = clBtnFace;
										}
										break;
									case AlarmBasic::AlActive:
										if ( AlarmBlink ){
											Canvas->Brush->Color = clRed;
										}else{
											Canvas->Brush->Color = clBtnFace;
										}
										break;
									case AlarmBasic::AlAknowledged:
										Canvas->Brush->Color = clRed;
										break;
									case AlarmBasic::AlBlocked:
										Canvas->Brush->Color = clYellow;
										break;
									case AlarmBasic::AlError:
									default:
										Canvas->Brush->Color = clGreen;
										break;
								}
								break;
							case tcmos_idle     :
								Canvas->Brush->Color = clBtnFace;
								break;
						}
						Canvas->FloodFill(x, y, clBlack, fsBorder);
						if ( AlarmColorVect[j] != Canvas->Brush->Color ){
							AlarmColorVect[j] = Canvas->Brush->Color;
							RefreshForm = true;
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
	AlarmBlink = !AlarmBlink; // Blink
}


//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::FormClose(TObject *Sender,
											TCloseAction &Action)
{
	WriteRegistry();
	NoReSize = true;
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall TTankPlanDrawingForm::PaintBoxTimerTimer(TObject *Sender)
{
	if (!HoldUpdate) {
		RefreshForm = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::LegendTimerTimer(TObject *Sender)
{
    if (!HoldUpdate) {
        CreateLegendList();
    }
    FindCargoTypes();
}
//---------------------------------------------------------------------------
void __fastcall TTankPlanDrawingForm::UpdateLegend(int Index, TColor CargoColor,AnsiString CargoName,AnsiString WeightStr,AnsiString VolumeStr,bool Visible)
{
    if ( Visible ) {
        PanelList[Index].Shape->Brush->Color = CargoColor;
        PanelList[Index].CargoLabel->Caption = CargoName;
        PanelList[Index].VolumeLabel->Caption= VolumeStr;
		PanelList[Index].WeightLabel->Caption= WeightStr;
    }
    PanelList[Index].Panel->Visible      = Visible;

}

void  __fastcall  TTankPlanDrawingForm::CreateLegendList()
{
// CargoLegend *TempLegendList[MAX_CARGOTYPES];
// First add the pre defined types
	for (int index=0; index < SizeofBasicCargoNameList; index++) {
        bool CargoActive=false;
        for (int TNo=0;!CargoActive && (TNo < (int)ObjectVector.size()); TNo++) {
            PROTank *TElement = (PROTank*)ObjectVector[TNo];

            if (TElement && ( TElement->CargoType->CargoTypeKey  == CTY_NOT_DEFINED)
                && ( TElement->CargoType->BaseCargoType == index )) {
				CargoActive = true;
                LegendList.push_back(new CargoLegend(TElement->CargoType,ObjectVector));
            }
        }
    }

// Then add the user defined types

    for (int index=0; index < MAX_CARGOTYPES; index++) {
        if ( CTOUser::CargoTable[index]->IsTheCargoDefined()) {
            bool CargoActive=false;
            for (int TNo=0;!CargoActive && (TNo < (int)ObjectVector.size()); TNo++) {
                PROTank *TElement = (PROTank*)ObjectVector[TNo];
                if (TElement && TElement->CargoType->CargoTypeKey == CTOUser::CargoTable[index]->CargoTypeKey ) {
                    CargoActive = true;
                    AnsiString CargoName = LibGetValue(SVT_CARGO_TYPE,TElement);
                    LegendList.push_back(new CargoLegend(CTOUser::CargoTable[index],ObjectVector));
                }
            }
        }
    }
    if (!LegendList.empty() > 0) {
        unsigned Start = 0;
        if (LegendList.size()>5) {
            Label4->Visible = true;
            Label3->Visible = true;
            VolumeUnitLabel2->Visible = true;
            WeightUnitLabel2->Visible = true;
        } else {
            Label4->Visible = false;
            Label3->Visible = false;
            VolumeUnitLabel2->Visible = false;
            WeightUnitLabel2->Visible = false;
        }
        if (LegendList.size()>10) {
            Start = StartShowCT;
            int Diff = Start + 10 - LegendList.size();
            if ( Diff > 0) {
                Start -= Diff;
            }
            ScrollBar1->Max = LegendList.size() - 10;
            ScrollBar1->Visible = true;
        } else {
            ScrollBar1->Max = 0;// NumberOfLegends;
            ScrollBar1->Visible = false;
        }
        for (unsigned counter=0; counter<10; counter++) {
            if (counter<LegendList.size() && Start<LegendList.size()) {
                AnsiString VolumeStr =   FloatToAnsiString(LegendList[Start]->Volume,8,1);
                AnsiString WeightStr =   FloatToAnsiString(LegendList[Start]->Weight,8,1);
                UpdateLegend(counter, LegendList[Start]->CargoColor,LegendList[Start]->CargoName,WeightStr,VolumeStr,true);
                Start++;
                /* TODO -oErik -cMissing code : UnitSystem must be added */
            } else {
                UpdateLegend(counter, clWhite,"","","",false);
            }
        }
        for (unsigned counter=0; counter<LegendList.size(); counter++) {
            delete LegendList[counter];
        }
        LegendList.clear();
    }
/* RBMARK
    VolumeUnitLabel1->Caption = LibGetValue(SVT_VOLUME,);
    WeightUnitLabel1->Caption = LibGetValue(SVT_WEIGHT,);
    VolumeUnitLabel2->Caption = VolumeUnitLabel1->Caption;
    WeightUnitLabel2->Caption = WeightUnitLabel1->Caption;
*/
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::FindCargoTypes(void)
{
	SetTankPopupMenu();
    CreateLegendList(); //same test for uppdateing
}
//---------------------------------------------------------------------------

void __fastcall  TTankPlanDrawingForm::SetTankPopupMenu()
{
    vector<CTOUser*>tmpCargoTypeVector = CTOUser::GetDefinedCargoes();
    if (tmpCargoTypeVector.empty()&& !TankPopupMenu->Items->Items[1]->Count) {
		for ( int index=0; index <= SizeofBasicCargoNameList; index++ ) {
            const AnsiString ACaption = LibGetValueName(BasicCargoNameList,SizeofBasicCargoNameList,index);
            TShortCut AShortCut = NULL;
            const AnsiString tempString = AnsiString::StringOfChar('q', index+1);//IntToStr(temp);
            TMenuItem *TempItem = NewItem(ACaption,AShortCut,false,true,CargoPopupExecute,0,tempString);
            TempItem->Tag = (CTY_NOT_DEFINED << 16) | index;
            TankPopupMenu->Items->Items[1]->Add(TempItem);
        }
    }
    if (tmpCargoTypeVector != CargoTypeVector) {
        RemoveMenuItems(TankPopupMenu->Items->Items[1]);
        CargoTypeVector = tmpCargoTypeVector;
        for ( int index=0; index <= SizeofBasicCargoNameList; index++ ) {
            const AnsiString ACaption = LibGetValueName(BasicCargoNameList,SizeofBasicCargoNameList,index);
            TShortCut AShortCut = NULL;
            const AnsiString tempString = AnsiString::StringOfChar('q', index+1);//IntToStr(temp);
            TMenuItem *TempItem = NewItem(ACaption,AShortCut,false,true,CargoPopupExecute,0,tempString);
            TempItem->Tag = (CTY_NOT_DEFINED << 16) | index;
            TankPopupMenu->Items->Items[1]->Add(TempItem);
		}
		 /* TODO -oEHS -cCritical : Fix cargotype bug later. Disable for now */
		/*
		if (!CargoTypeVector.empty()) {
            TankPopupMenu->Items->Items[1]->Add(NewLine());
            for ( unsigned index=0; index < CargoTypeVector.size(); index++ ) {
                    const AnsiString ACaption = CargoTypeVector[index]->Name;
                    TShortCut AShortCut = NULL;
                    const AnsiString tempString = AnsiString::StringOfChar('q', index+1);//IntToStr(temp);
                    TMenuItem *TempItem = NewItem(ACaption,AShortCut,false,true,CargoPopupExecute,0,tempString);
                    TempItem->Tag = (CargoTypeVector[index]->CargoTypeKey << 16) | CargoTypeVector[index]->BaseCargoType;
                    TankPopupMenu->Items->Items[1]->Add(TempItem);
            }
		}
		*/
    }
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::CargoPopupExecute(TObject *Sender)
{
    TMenuItem *TempItem = (TMenuItem *)Sender;
    AnsiString CName    = TempItem->Caption;
//  TPopupMenu *PMPtr =(TPopupMenu *)Sender;
    if (TempItem) {
        if (CurrentTankPtr) {
            int CargoType = TempItem->Tag >> 16;
            int BaseCargo = TempItem->Tag & 0xffff;
            if ( CargoType == CTY_NOT_DEFINED ) {
                LibPutValue(SVT_BASIC_TYPE, CurrentTankPtr, BaseCargo);
            } else {
                LibPutValue(SVT_CARGO_TYPE, CurrentTankPtr, CargoType);
            }
        }
    }
	EsPaintBox1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::SelectValueButtonClick(TObject *Sender)
{
    TButton *BPtr =(TButton*)Sender;
    BPtr->PopupMenu->Popup(BPtr->ClientOrigin.x+5 ,BPtr->ClientOrigin.y+5);
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::ScrollBar1Scroll(TObject *Sender,
                                                   TScrollCode ScrollCode, int &ScrollPos)
{
	StartShowCT =  ScrollPos;
    CreateLegendList();
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::FormResize(TObject *Sender)
{
	if(this){
		if (!NoReSize && MaxX ) {
			if ( MaxX == MinX) {
				MinX = MaxX -100;
			}
			ScaleCoeffW = (MaxX - MinX)/(Width -40);

			int heightDiv = Height - 300;
			if (heightDiv > 0) {

				ScaleCoeffH = (MaxY - MinY)/(heightDiv);
				ScaleTPDrawing();
				CreatePolygonRegion();
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::FormShow(TObject *Sender)
{
	WindowState = wsNormal;
}
//---------------------------------------------------------------------------




void __fastcall TTankPlanDrawingForm::PrintButtonClick(TObject *Sender)
{
/*
  TPrinter *Prntr = Printer();
  TRect   MyRect, MyOther;

MyRect = TRect::Rect(10,10,100,100);

MyOther = Rect(10,111,100, 201);

  //Rect(200,200,(Prntr->PageWidth-200),(Prntr->PageHeight-200));
  TRect r = Rect(200,200,1000,1000);
  Prntr->BeginDoc();
  TRect r2;
  Prntr->Canvas->CopyMode = cmSrcCopy;
  //r = Rect(0, 0, Prntr->Width, Prntr->Height);
  Prntr->Canvas->CopyRect(r, TPPaintBox->Canvas, r);
  Prntr->EndDoc();
 */
}
//---------------------------------------------------------------------------
void __fastcall TTankPlanDrawingForm::ReadRegistry(void)
{
    TRegistry *Registry = new TRegistry;
    try {
        Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access  = KEY_READ;

        // False because we do not want to create it if it doesn't exist
        bool Status = Registry->OpenKey(RegNameKey,false);
        if ( Status ) {
            if ( Registry->ValueExists("ValueKey") ) {

                //PopupMenuValueType->Items->MenuIndex = Registry->ReadInteger("PopupMenuValueIndex");
                ValueKey = Registry->ReadInteger("ValueKey");
                if (!ObjectVector.empty() ) {
                    PROTank *Element = (PROTank*)ObjectVector[0];
                    ValueTypeLabel->Caption = LibGetValue( SVT_VALUE_NAME, ValueKey, Element,0);
                }
                //AnsiString Myunitstr;
                //LibGetValue(ValueKey,CurrentTankPtr,&Myunitstr);
            }
            Registry->CloseKey();
        }
    }
    __finally
    {
        delete Registry;
    }
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::WriteRegistry(void)
{
    TRegistry *Registry = new TRegistry;
    try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
        Registry->Access  = KEY_WRITE;

        // False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey,true);
        if (Status) {
			//Registry->WriteInteger("PopupMenuValueIndex", PopupMenuValueType->Items->MenuIndex);
            Registry->WriteInteger("ValueKey", ValueKey);
            Registry->CloseKey();
        }
    }
    __finally
    {
        delete Registry;
    }
}


//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::PaintTankPlan(void)
{
}


void __fastcall TTankPlanDrawingForm::OpModeComboBoxChange(TObject *Sender)
{
    TComboBox *ComboBoxPtr =   (TComboBox*)Sender;
    if (ComboBoxPtr->ItemIndex >= 0) {
        AnsiString NewState = (AnsiString)ComboBoxPtr->ItemIndex;
		switch ( Tag ) {
        default               :
            break;
        case C_PRO_TANK       :
            break;
        case C_PRO_CARGO      :
            LibPutValue( SVT_TANK_STATE_STR_CGO,PROSystemData::TXUSystemData, NewState);
            break;
        case C_PRO_BALLAST    :
            LibPutValue( SVT_TANK_STATE_STR_BAL,PROSystemData::TXUSystemData, NewState);
            break;
        case C_PRO_HFO        :
        case C_PRO_DO         :
        case C_PRO_LUB        :
        case C_PRO_FW         :
        case C_PRO_MISC       :
            break;
        case C_PRO_TANKPRESS  :
            LibPutValue( SVT_TANK_STATE_STR_PRE,PROSystemData::TXUSystemData, NewState);
            break;
        case C_PRO_TEMP       :
        case C_PRO_LINEPRESS:
            break;
        }
    }
}
//---------------------------------------------------------------------------



void __fastcall TTankPlanDrawingForm::FormDestroy(TObject *Sender)
{
	for (unsigned j=0; j<TankRegion.size(); j++) {
		//if (TankRegion[j]) {
			DeleteObject(TankRegion[j]);
		//}
	}
	delete LineList;

	RemoveMenuItems(TankPopupMenu->Items->Items[1]);
	RemoveMenuItems(PopupMenuValueType->Items);

}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::UpdateStringGrids(void) {
	bool NeedRefresh = false;
	for(unsigned i=0; !NeedRefresh && i < ObjectVector.size(); i++){
		PROTank *Element = (PROTank*)ObjectVector[i];
		TColor tmpCol = Element->CargoType->Colour;
		if (tmpCol != TankCargoColorVect[i]){
			NeedRefresh =true;
			TankCargoColorVect[i] =  tmpCol;
		}
	}
	//NeedRefresh = IsAlarmChange();
	//NeedRefresh = true; /* TODO 1 -oEHS -cCosmetic : Should also check for change of alarm colors */
	if ( NeedRefresh || RefreshForm ){
		RefreshForm = false;
		EsPaintBox1->Repaint();
	}
	if (!HoldUpdate) {
		if (CurrentTankPtr ) {
			UpdateValues();
		}
	}
	TankState tmpState = PROXRefObject::VectorGetState(ObjectVector);
	OpModeComboBox->Text = PROXRefObject::GetStateString(tmpState);
}
//---------------------------------------------------------------------------


void __fastcall TTankPlanDrawingForm::GetTankDisplayColors(PROTank *pTank, System::Uitypes::TColor *backgroundColor, System::Uitypes::TColor *foregroundColor)
{
	*foregroundColor = clBlack;

	if (pTank) {
		*backgroundColor = (TColor)pTank->CargoType->Colour;
	} else {
		*backgroundColor = clBtnFace;
	}
}


void __fastcall TTankPlanDrawingForm::FormCreate(TObject *Sender)
{
	NoReSize = true;
	HasValueAndNameIndex = false;
	MaxX = -MAXFLOAT+1;
	MinX = MAXFLOAT;
	MaxY = -MAXFLOAT+2;
    MinY = MAXFLOAT;
    HoldUpdate = true;
    ScaleCoeffW = Width;
    ScaleCoeffH = Height;
    SpaceRound = 15;
    LineList  = new TStringList();
	ValueKey = SVT_ULLAGE;
    for(unsigned i=0; i < ObjectVector.size(); i++){
        PROTank *Element = (PROTank*)ObjectVector[i];
		TColor tmpCol = Element->CargoType->Colour;
		TankCargoColorVect.push_back(tmpCol);
	}
	use_file(myFileName.c_str());
	if (!ObjectVector.empty() ) {
		PROTank *Element = (PROTank*)ObjectVector[0];
		Tag = Element->Type;
		FindTankPoints();
		RecalcXYPoints();
        ScaleTPDrawing();       // EHSMark
		CreatePolygonRegion(); // EHSMark
        MakeLabelList();
        FindCargoTypes();
		SetPopupMenuValueType(PopupMenuValueType);
    }
    {
        AnsiString VolumeUnitStr,WeightUnitStr;
        PROTank *TnkPtr = (PROTank*)ObjectVector[0];
        LibGetValue(SVT_VOLUME,TnkPtr,&VolumeUnitStr);
        LibGetValue(SVT_WEIGHT,TnkPtr,&WeightUnitStr);
        VolumeUnitLabel1->Caption = VolumeUnitStr;
        VolumeUnitLabel2->Caption = VolumeUnitStr;
        WeightUnitLabel1->Caption = WeightUnitStr;
		WeightUnitLabel2->Caption = WeightUnitStr;
    }
	RefreshForm = true;
	HoldUpdate  = false;
	NoReSize	= false;
	TChildForm::FormCreate(Sender);

}
//---------------------------------------------------------------------------


void __fastcall TTankPlanDrawingForm::EsPaintBox1Paint(TObject *Sender, TCanvas *Canvas, TRect &Rect)
{
	//Canvas->Pen->Color 	 = clBlack;
	//Canvas->Brush->Color = clBtnFace;
	Canvas->FillRect(Rect);
	DrawAllTanks(Canvas);
	UppdateValue(Canvas);
	UppdateAlarms(Canvas);
	ShowTankNames(Canvas);
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanDrawingForm::EsPaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	bool bInside = false;
	int tankno=0;
	while ( !bInside && tankno<(int)TankPoint.size() && tankno < (int)TankRegion.size() && !TankPoint[tankno].empty()) {
		bInside =  PtInRegion(TankRegion[tankno],X,Y);
		if ( !bInside ){
			tankno++;
		}
	}
	if (bInside) {
		map<int, PROTank*>::iterator TankMapIterator = TankRegionNameMap.find(tankno);
		if ( TankMapIterator != TankRegionNameMap.end() ) {
			CurrentTankPtr = TankMapIterator->second;
			UpdateValues();
		} else {
			BlankValues("(no tank)");
		}
	} else {
		CurrentTankPtr = NULL;
		BlankValues("(no tank)");
	}
}
//---------------------------------------------------------------------------






