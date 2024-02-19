#include <vcl.h>
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#pragma hdrstop
// #include "StdAboutBoxForm.h"
#include "AlarmUnit.h"
#include "AlarmReportUnit.h"
#include "AlarmLogUnit.h"
#include <assert.h>
class TMainForm;
extern PACKAGE TMainForm *MainForm;
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "frCoreClasses"
#pragma link "frxSmartMemo"
#pragma resource "*.dfm"

static const TColor clOrangeRed = (TColor)0x000045FF;
TAlarmForm *AlarmForm;

static short SeqTable[] = {
    SVT_AL_LOCATION, SVT_AL_DESCRIPTION, SVT_AL_LIMIT, SVT_AL_VALUE,
    SVT_AL_UNIT, SVT_AL_ACT_DATE_TIME, SVT_AL_AKN_DATE_TIME};
static TColor ColorState;
// ---------------------------------------------------------------------------

__fastcall TAlarmForm::TAlarmForm(TComponent* Owner) : TChildForm(Owner) {

}
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::RefreshStringTimer(TObject *Sender) {
	if (ColorState == clBlack) {
		ColorState = clRed;
		StringGridRefreshTimer->Interval = 250;
	}
	else {
		ColorState = clBlack;
		StringGridRefreshTimer->Interval = 750;
	}
	ActiveAlarmsVector = AlarmBasic::PROActiveAlarmList.GetVector(); ;
	AcknowAlarmsVector = AlarmBasic::PROAcknowAlarmList.GetVector(); ;

	int CurrentRow = 1;
	int ActiveListSize = ActiveAlarmsVector.size();
	int AcknowListSize = AcknowAlarmsVector.size();
	int CurrentRows    = ActiveListSize + AcknowListSize;
	if (CurrentRows){
		AlarmStringGrid->RowCount =CurrentRows + 1;
		if (!ActiveAlarmsVector.empty()) {
			for (int i = 0; i < ActiveListSize; i++) {
				AlarmBasic *ElementPtr = (AlarmBasic*)ActiveAlarmsVector[i];
				if (ElementPtr) {
					for (unsigned Column = 0; Column < NELEMENTS(SeqTable);	Column++) {
						AlarmStringGrid->Cells[Column][CurrentRow]   = LibGetValue(SeqTable[Column], ElementPtr);
						AlarmStringGrid->Objects[Column][CurrentRow] = (TObject*)ElementPtr;
					}
					CurrentRow++;
				}
			}
		}
		if (!AcknowAlarmsVector.empty()) {
			for (int i = 0; i < AcknowListSize; i++) {
				AlarmBasic *ElementPtr = (AlarmBasic*)AcknowAlarmsVector[i];
				if (ElementPtr) {
					for (unsigned Column = 0; Column < NELEMENTS(SeqTable);	Column++) {
						AlarmStringGrid->Cells[Column][CurrentRow]   = LibGetValue(SeqTable[Column], ElementPtr);
						AlarmStringGrid->Objects[Column][CurrentRow] = NULL;
					}
					CurrentRow++;
				}
			}
		}
	}else{
		AlarmStringGrid->RowCount  = 2;
		for (int i = 0; i < AlarmStringGrid->ColCount; i++) {
			AlarmStringGrid->Cells[i][1] = "";
		}
	}
}
#pragma warn -8028
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::FormClose(TObject *Sender, TCloseAction &Action) {
	Action = caFree;
}
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::AckBitBtnClick(TObject *Sender) {
	SendAlarmSilence();
	AckSelectedAlarm();
}
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::SilenceBitBtnClick(TObject *Sender) {
	SendAlarmSilence();
}
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::PrintAlarmLog(TObject *Sender) {
	frxReportAlarmList->ShowReport();
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

bool __fastcall TAlarmForm::AckAllAlarms(void) {
    bool AckOK = false;
	if (ViewModePC) {
		MessageDlg(
            "You don't have permission to reset alarms,\nReset alarms on the TCU.",
            mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}
	else {
		vector<PRogramObjectBase*>ActiveAlarmsVector =
			AlarmBasic::PROActiveAlarmList.GetVector(); ;
        if (!ActiveAlarmsVector.empty()) {
            int ListSize = ActiveAlarmsVector.size();
            for (int i = 0; i < ListSize; i++) {
				AlarmBasic *TempElement = (AlarmBasic*)ActiveAlarmsVector[i];
                if (!(NetworkOK || UseNetwork) ||
                    AlarmCriticalComFailure::ComFailure) {
                    TempElement->MoveAlarmToAknowledge();
                }
				else {
                    TempElement->SendData(CMD_PRO_ALARM_ACK);
                }
				AckOK |= true;
            }
        }
    }
    return (AckOK);
}

void __fastcall TAlarmForm::AlarmStringGridDrawCell(TObject *Sender, int ACol,
    int ARow, TRect &Rect, TGridDrawState State) {
    TStringGrid* StringGrid = static_cast<TStringGrid*>(Sender);
    assert(StringGrid != NULL);

    TCanvas* SGCanvas = StringGrid->Canvas;
    SGCanvas->Font = StringGrid->Font;

    RECT RText = static_cast<RECT>(Rect);

    const bool fixed = State.Contains(gdFixed);
    const bool focused = State.Contains(gdFocused);
    bool selected = State.Contains(gdSelected);
    if (!StringGrid->Options.Contains(goDrawFocusSelected)) {
        selected &= focused;
    }
    const AnsiString text(StringGrid->Cells[ACol][ARow]);
    const bool IsActive((bool)StringGrid->Objects[ACol][ARow]);
    // Quick and dirty
    // if the cell is fixed (headers)
    if (fixed) {
        TColor tmpBkCol;
        TColor tmpTxtCol;
        if (!ARow) {
            tmpBkCol = StringGrid->FixedColor;
            tmpTxtCol = clBtnText;
        }
        else {
            if (IsActive) {
                tmpBkCol = clRed;
                tmpTxtCol = ColorState;
            }
            else {
				tmpBkCol = clWhite;
                tmpTxtCol = clRed;
            }
        }
        SGCanvas->Brush->Color = tmpBkCol;
        SGCanvas->Font->Color = tmpTxtCol;
        SGCanvas->FillRect(Rect);
        Frame3D(SGCanvas, Rect, clBtnHighlight, clBtnShadow, 1);
    }
    // if the cell is selected
    else if (selected || (ARow == ActiveRow)) {
        TColor tmpBkCol;
        TColor tmpTxtCol;
        if (IsActive) {
            tmpBkCol = clRed; // clFuchsia;
            if (ColorState == clBlack) {
                tmpTxtCol = clWhite;
            }
            else {
                tmpTxtCol = clRed;
            }
        }
        else {
            tmpBkCol = clWhite;
            tmpTxtCol = clRed;
        }
        SGCanvas->Brush->Color = tmpBkCol;
        SGCanvas->Font->Color = tmpTxtCol;
        SGCanvas->FillRect(Rect);
    }
    // if the cell is normal
    else {
        TColor tmpBkCol;
        TColor tmpTxtCol;
        if (IsActive) {
            tmpBkCol = clRed;
            tmpTxtCol = ColorState;
        }
        else {
            tmpBkCol = clLtGray;
            tmpTxtCol = clRed;
        }
        SGCanvas->Brush->Color = tmpBkCol;
		SGCanvas->Font->Color = tmpTxtCol;
        SGCanvas->FillRect(Rect);
    }
    // if the cell is focused
    if (focused) {
        DrawFocusRect(SGCanvas->Handle, &RText);
    }
    // draw the text
    RText.left += 2;
    RText.top += 2;
    DrawText(SGCanvas->Handle, text.c_str(), text.Length(), &RText,
        DT_LEFT | DT_VCENTER | DT_SINGLELINE);

}
// ---------------------------------------------------------------------------

bool __fastcall TAlarmForm::AckSelectedAlarm(void) {
    bool AckOK = false;
    if (ViewModePC) {
        MessageDlg(
            "You don't have permission to reset alarms,\nReset alarms on the TCU.",
            mtConfirmation, TMsgDlgButtons() << mbOK, 0);
    }
    else {
        AlarmBasic *SelectedAlarm = NULL;
        if (AlarmStringGrid->Row >= 0 && AlarmStringGrid->Col >= 0)
			SelectedAlarm = (AlarmBasic*)AlarmStringGrid->Objects[ActiveColumn][ActiveRow];
		if (SelectedAlarm) {
            if (!(NetworkOK || UseNetwork) ||
                AlarmCriticalComFailure::ComFailure) {
                SelectedAlarm->MoveAlarmToAknowledge();
            }
            else {
                SelectedAlarm->SendData(CMD_PRO_ALARM_ACK);
            }
        }
        else {
            AckOK = AckFirstAlarm();
        }
    }
    return (AckOK);
}

// ---------------------------------------------------------------------------

bool __fastcall TAlarmForm::AckFirstAlarm(void) {
    bool AckOK = false;
    AlarmBasic::PROActiveAlarmList.Protect();
    if (!AlarmBasic::PROActiveAlarmList.isEmpty()) {
        PRONode *TNode = AlarmBasic::PROActiveAlarmList.getHead();
        TNode = TNode->getNext();
        AlarmBasic *TempElement = (AlarmBasic*)TNode->getElement();
        if (TempElement) {
            if (!(NetworkOK || UseNetwork) ||
                AlarmCriticalComFailure::ComFailure) {
                TempElement->MoveAlarmToAknowledge();
            }
            else {
                TempElement->SendData(CMD_PRO_ALARM_ACK);
            }
            AckOK = true;
        }
    }
    AlarmBasic::PROActiveAlarmList.UnProtect();
    return (AckOK);
}

void __fastcall TAlarmForm::AlarmStringGridSelectCell(TObject *Sender, int ACol,
    int ARow, bool &CanSelect) {
    TStringGrid* StringGrid = static_cast<TStringGrid*>(Sender);
    assert(StringGrid != NULL);

    ActiveColumn = ACol;
    ActiveRow = ARow;
}
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::AlarmStringGridDblClick(TObject *Sender) {
	AckSelectedAlarm();
}
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::FormCreate(TObject *Sender) {
    AlarmStringGrid->DoubleBuffered = true;
    AlarmStringGrid->Cells[0][0] = "Location";
	AlarmStringGrid->Cells[1][0] = "Description";
    AlarmStringGrid->Cells[2][0] = "Limit";
    AlarmStringGrid->Cells[3][0] = "Current value";
    AlarmStringGrid->Cells[4][0] = "Unit";
    AlarmStringGrid->Cells[5][0] = "Time raised";
    AlarmStringGrid->Cells[6][0] = "Reset";
    AlarmStringGrid->ColWidths[0] = 150;
    AlarmStringGrid->ColWidths[1] = 130;
    AlarmStringGrid->ColWidths[2] = 100;
    AlarmStringGrid->ColWidths[3] = 100;
    AlarmStringGrid->ColWidths[4] = 84;
    AlarmStringGrid->ColWidths[5] = 130;
    AlarmStringGrid->ColWidths[6] = 130;
	String ShipName = LibGetValue(SVT_SHIP_NAME,  PROProjectInfo::PROProjectInfoPtr);
	String ProjName = LibGetValue(SVT_SYSTEM_ID,  PROProjectInfo::PROProjectInfoPtr);
	String DataVersion = LibGetValue(SVT_DATA_VERSION, PROProjectInfo::PROProjectInfoPtr);
	String ProgVersion = LibGetValue(SVT_UNIT_PROGRAM_VERSION, PROTanksystemUnit::MySelf);

	// ShipLabel->Caption ="Ship: "+ ShipName;
	// ProdLabel->Caption = (String) ProjName+"  "+ProgVersion;
	// DataVersionLabel->Caption =(String)"Data:"+DataVersion;
	ActiveColumn = 0;
	ActiveRow = 0;
// Refresh();

}
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::FormDestroy(TObject *Sender) {
	AlarmForm = NULL;

}
// ---------------------------------------------------------------------------

void __fastcall TAlarmForm::FormShortCut(TWMKey &Msg, bool &Handled) {
    switch (Msg.CharCode & 0xFF) {
    case VK_F12:
        Handled = true;
        SendAlarmSilence();
        int KeyData = Msg.KeyData >> 16;
		if (KeyData & KF_ALTDOWN) {
            AckAllAlarms();
        }
        else {
            AckSelectedAlarm();
        }
        break;
    }

}
// ---------------------------------------------------------------------------
void __fastcall TAlarmForm::AlarmLogButtonClick(TObject *Sender)
{
	TChildForm *FormPtr = (TChildForm*)Application->FindComponent("AlarmLogForm");
	if ( FormPtr ) {
		FormPtr->BringToFront();
	}else{
		Application->CreateForm(__classid(TAlarmLogForm), &AlarmLogForm);
		FormPtr = (TChildForm*)AlarmLogForm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TAlarmForm::frxReportAlarmListBeforePrint(TfrxReportComponent *Sender)
{
	TfrxCrossView *Cross = dynamic_cast<TfrxCrossView*>(Sender) ;
	if (Cross) {
		  for(int i = 0; i< AlarmStringGrid->RowCount; i++){
			for(int j = 0; j < AlarmStringGrid->ColCount;j++){
			  Variant pRows[] = {i};
			  Variant pCols[] = {j};
			  Variant pStrs[] = {AlarmStringGrid->Cells[j][i]};
			  Cross->AddValue((const Variant*)pRows,ARRAYSIZE(pRows)-1,(const Variant*)pCols,ARRAYSIZE(pCols)-1,(const Variant*)pStrs,ARRAYSIZE(pStrs)-1);
			}
		  }
	}
}
//---------------------------------------------------------------------------

