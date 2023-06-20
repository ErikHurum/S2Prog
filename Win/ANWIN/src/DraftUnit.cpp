#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#pragma hdrstop
#include "DraftUnit.h"
#include <Registry.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "AdvEdit"
#pragma link "RzEdit"
#pragma resource "*.dfm"
TDraftsForm *DraftsForm;

// ---------------------------------------------------------------------------
__fastcall TDraftsForm::TDraftsForm(TComponent* Owner) : TChildForm(Owner) {
	EditDraftFore->Tag 		= SVT_DF;
	EditDraftPort->Tag 		= SVT_DP;
	EditDraftStarboard->Tag = SVT_DS;
	EditDraftAft->Tag 		= SVT_DA;

	EditAftPort->Tag 		= SVT_DAP;
	EditAftStarboard->Tag 	= SVT_DAS;
	EditFwdPort->Tag 		= SVT_DFP;
	EditFwdStarboard->Tag 	= SVT_DFS;

	EditSeaWater->Tag 		= SVT_SEAWATER_DNS;

	DraftUnit->Tag 			= SVT_DF;
	SeaWaterUnit->Tag 		= SVT_SEAWATER_DNS;


    switch (PRODraftSystem::PRODraftSysPtr->DraftSystem) {
	case PRODraftSystem::DftFwdMidShipAftPS:
	case PRODraftSystem::DftCorners:
		EditDraftList.push_back(EditDraftFore);
		EditDraftList.push_back(EditDraftPort);
		EditDraftList.push_back(EditDraftStarboard);
		EditDraftList.push_back(EditDraftAft);
		EditDraftList.push_back(EditAftPort);
		EditDraftList.push_back(EditAftStarboard);
		EditDraftList.push_back(EditFwdPort);
		EditDraftList.push_back(EditFwdStarboard);
		break;
	default:
		EditDraftList.push_back(EditDraftFore);
		EditDraftList.push_back(EditDraftPort);
		EditDraftList.push_back(EditDraftStarboard);
		EditDraftList.push_back(EditDraftAft);
		EditAftPort->Visible = false;
        EditAftStarboard->Visible = false;
        EditFwdPort->Visible = false;
        EditFwdStarboard->Visible = false;
        break;

    }

    UserInputMode = false;
    EditDelayCount = 20;
    ShipShapePoints[0].x = 10;
	ShipShapePoints[0].y = 8;
	ShipShapePoints[1].x = 400;
	ShipShapePoints[1].y = 8;
	ShipShapePoints[2].x = 500;
	ShipShapePoints[2].y = 100;
	ShipShapePoints[3].x = 400;
	ShipShapePoints[3].y = 190;
	ShipShapePoints[4].x = 10;
	ShipShapePoints[4].y = 190;
	ShipShapePoints[5].x = 10;
	ShipShapePoints[5].y = 8;

	BargeShapePoints[0].x = 10;
	BargeShapePoints[0].y = 8;
	BargeShapePoints[1].x = 480;
	BargeShapePoints[1].y = 8;
	BargeShapePoints[2].x = 500;
	BargeShapePoints[2].y = 28;
	BargeShapePoints[3].x = 500;
	BargeShapePoints[3].y = 100;
	BargeShapePoints[4].x = 500;
	BargeShapePoints[4].y = 170;
	BargeShapePoints[5].x = 480;
	BargeShapePoints[5].y = 190;
	BargeShapePoints[6].x = 400;
	BargeShapePoints[6].y = 190;
	BargeShapePoints[7].x = 10;
	BargeShapePoints[7].y = 190;
	BargeShapePoints[8].x = 10;
	BargeShapePoints[8].y = 8;

	AnsiString Tmp;
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\DraftWindow\\";
	ReadRegistry();
}
// ---------------------------------------------------------------------------

void TDraftsForm::UpdateValue(TEdit *EditPtr, TLabel *LabelPtr) {
    // Draft system
}
// ---------------------------------------------------------------------------

void TDraftsForm::UpdateValues(void) {
    if (PRODraftSystem::PRODraftSysPtr) {
		AnsiString tempValue, unitstr;
        if (PrevItemIdex != DraftRadioGroup->ItemIndex) {
            PrevItemIdex = DraftRadioGroup->ItemIndex;
            AnsiString NewLoc = PrevItemIdex;
            LibPutValue(SVT_DRAFT_POINT, PRODraftSystem::PRODraftSysPtr,
                NewLoc);
        }
		for (unsigned i = 0; i < EditDraftList.size(); i++) {
			TEdit *EditPtr = EditDraftList[i];
			if ((CurrentEditPtr == EditPtr) && (UserInputMode)) {
                if (EditDelayCount < 20) {
                    EditDelayCount++;
                }
                else {
                    tempValue =
                        LibGetValue(EditPtr->Tag,
                        PRODraftSystem::PRODraftSysPtr, &unitstr);
					if (EditPtr->Text != tempValue)
                        EditPtr->Text = tempValue;
                    if (DraftUnit->Caption != unitstr)
                        DraftUnit->Caption = unitstr;
                }
            }
            else if (!((CurrentEditPtr == EditPtr) && (UserInputMode))) {
                tempValue =
                    LibGetValue(EditPtr->Tag, PRODraftSystem::PRODraftSysPtr, &unitstr);
                if (EditPtr->Text != tempValue)
                    EditPtr->Text = tempValue;
                if (DraftUnit->Caption != unitstr)
                    DraftUnit->Caption = unitstr;
            }
        }
	}
    else {
        AnsiString tempValue = "No draft sensors!";
        DraftUnit->Caption = tempValue;
    }
    // Sea water density
    if (PROSystemData::TXUSystemData) {
        AnsiString tempValue, unitstr;
        if ((CurrentEditPtr == EditSeaWater) && (UserInputMode)) {
            if (EditDelayCount < 20) {
                EditDelayCount++;
			}
            else {
                tempValue = LibGetValue(SVT_SEAWATER_DNS,
                    PROSystemData::TXUSystemData, &unitstr);
                if (EditSeaWater->Text != tempValue)
                    EditSeaWater->Text = tempValue;
                if (SeaWaterUnit->Caption != unitstr)
                    SeaWaterUnit->Caption = unitstr;
            }
        }
        else if (!((CurrentEditPtr == EditSeaWater) && (UserInputMode))) {
            tempValue = LibGetValue(SVT_SEAWATER_DNS,
                PROSystemData::TXUSystemData, &unitstr);
            if (EditSeaWater->Text != tempValue)
                EditSeaWater->Text = tempValue;
            if (SeaWaterUnit->Caption != unitstr)
                SeaWaterUnit->Caption = unitstr;
		}
    }
}
// ---------------------------------------------------------------------------

void __fastcall TDraftsForm::FormClose(TObject *Sender, TCloseAction &Action) {
	WriteRegistry();
    DraftsForm = NULL;
    Action = caFree;
}
// ---------------------------------------------------------------------------

void __fastcall TDraftsForm::PaintBox1Paint(TObject *Sender) {
	// CreatePolygonRgn(ShipShapePoints,6,ALTERNATE );
	// TColor tempColor = clTeal;
	PaintBox1->Canvas->Pen->Color = clBlack;
	// PaintBox1->Canvas->Brush->Color = tempColor;
	switch (PRODraftSystem::PRODraftSysPtr->DraftSystem) {
	case PRODraftSystem::DftFwdMidShipAftPS:
	case PRODraftSystem::DftCorners:
		PaintBox1->Canvas->Polygon((TPoint*)BargeShapePoints, 8);
        break;
    default:
        PaintBox1->Canvas->Polygon((TPoint*)ShipShapePoints, 5);
        break;

    }

}
// ---------------------------------------------------------------------------

void __fastcall TDraftsForm::Timer1Timer(TObject *Sender) {
	for(unsigned i=0; i < EditDraftList.size(); i++){
		EditDraftList[i]->Color = PRODraftSystem::PRODraftSysPtr->GetColor(EditDraftList[i]->Tag);
		/*
		switch(PRODraftSystem::PRODraftSysPtr->GetStatus(PRODraftSystem::PRODraftSysPtr->GetColor(EditDraftList[i]->Tag))){
			case GETVAL_ERROR           :
			case GETVAL_UNKNOWN_ERROR   :
			case GETVAL_NOT_AVAILABLE   :
			case GETVAL_DRY_SENSOR      :
			case GETVAL_HW_ALARM        :
				EditDraftList[i]->Font->Color = clWhite;
				break;
			case GETVAL_NOT_MEASURED    :
			case GETVAL_NO_ERR          :
			default                     :
				EditDraftList[i]->Font->Color = clBlack;
				break;
		}
		EditDraftList[i]->Font->Color = clBlack;
		*/

	}
	UpdateValues();
}
// ---------------------------------------------------------------------------

void __fastcall TDraftsForm::EditExit(TObject *Sender) {
    if (PRODraftSystem::PRODraftSysPtr && UserInputMode) {
        TEdit *EditPtr = (TEdit*)Sender;
        AnsiString UserInput = EditPtr->Text;
        LibPutValue(EditPtr->Tag, PRODraftSystem::PRODraftSysPtr,
            UserInput.c_str());
        UserInputMode = false;
        EditDelayCount = 20;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TDraftsForm::EditKeyPress(TObject *Sender, char &Key) {
    CurrentEditPtr = (TEdit*)Sender;
	switch (Key) {
    case VK_ESCAPE:
        UserInputMode = false;
        EditDelayCount = 20;
        break;
	case VK_RETURN:
        if (UserInputMode) {
            TEdit *EditPtr = (TEdit*)Sender;
            AnsiString UserInput = EditPtr->Text;
            if (PRODraftSystem::PRODraftSysPtr)
                LibPutValue(EditPtr->Tag, PRODraftSystem::PRODraftSysPtr,
				UserInput.c_str());
        }
        break;
    default:
        UserInputMode = true;
        EditDelayCount = 0;
        break;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TDraftsForm::EditSeaWaterExit(TObject *Sender) {
    if (PROSystemData::TXUSystemData && UserInputMode) {
        TEdit *EditPtr = (TEdit*)Sender;
        AnsiString UserInput = EditPtr->Text;
        LibPutValue(EditPtr->Tag, PROSystemData::TXUSystemData,
            UserInput.c_str());
        UserInputMode = false;
        EditDelayCount = 20;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TDraftsForm::EditSeaWaterKeyPress(TObject *Sender, char &Key) {
    CurrentEditPtr = (TEdit*)Sender;
    switch (Key) {
    case VK_ESCAPE:
        UserInputMode = false;
		EditDelayCount = 20;
        break;
    case VK_RETURN:
        if (UserInputMode) {
            TEdit *EditPtr = (TEdit*)Sender;
            AnsiString UserInput = EditPtr->Text;
            if (PROSystemData::TXUSystemData)
                LibPutValue(EditPtr->Tag, PROSystemData::TXUSystemData,
                UserInput.c_str());
        }
        break;
    default:
        UserInputMode = true;
        EditDelayCount = 0;
        break;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TDraftsForm::ReadRegistry(void) {
    TRegistry *Registry = new TRegistry;
    bool IsDraftAtPP = false;
    try {
        Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_READ;

        // False because we do not want to create it if it doesn't exist
        bool Status = Registry->OpenKey(RegNameKey, false);
        if (Status) {
            if (Registry->ValueExists("DisplayDraftAtPP")) {
                IsDraftAtPP = Registry->ReadBool("DisplayDraftAtPP");
            }
            Registry->CloseKey();
        }
    }
    __finally {
        delete Registry;
    }
    DraftRadioGroup->ItemIndex = int(IsDraftAtPP);
    PrevItemIdex = DraftRadioGroup->ItemIndex;
}

void __fastcall TDraftsForm::WriteRegistry(void) {
    TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
        Registry->Access = KEY_WRITE;

        // False because we do not want to create it if it doesn't exist
        bool Status = Registry->OpenKey(RegNameKey, true);
        if (Status) {
            Registry->WriteBool("DisplayDraftAtPP",
                bool(DraftRadioGroup->ItemIndex));
            Registry->CloseKey();
        }
    }
    __finally {
        delete Registry;
    }
}



void __fastcall TDraftsForm::FormCreate(TObject *Sender)
{
	ShapeOnline->Brush->Color 		= PRODraftSystem::GetStatusColor(GETVAL_NO_ERR			);
	ShapeDrySensor->Brush->Color 	= PRODraftSystem::GetStatusColor(GETVAL_DRY_SENSOR		);
	ShapeNoSensors->Brush->Color 	= PRODraftSystem::GetStatusColor(GETVAL_NOT_AVAILABLE	);
	ShapeHWAlarm->Brush->Color 		= PRODraftSystem::GetStatusColor(GETVAL_HW_ALARM		);
	ShapeCalculated->Brush->Color 	= PRODraftSystem::GetStatusColor(GETVAL_NOT_MEASURED	);
	ShapeUnknownError->Brush->Color = PRODraftSystem::GetStatusColor(GETVAL_UNKNOWN_ERROR	);
}
//---------------------------------------------------------------------------

