#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include <Registry.hpp>

#include "LoadCalcReportUnit.h"
#include "LoadCalcUnit.h"
#include "NewSolidsUnit.h"
USEFORM("src\LoadCalcMessagesUnit.cpp", LoadCalcMessagesForm);
USEFORM("src\LCTrimListUnit.cpp", TrimListSrcDlg);
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "AeroButtons"
#pragma resource "*.dfm"

TLoadcalcForm *LoadcalcForm;
 AnsiString TLoadcalcForm::RegNameKey;

// ---------------------------------------------------------------------------
__fastcall TLoadcalcForm::TLoadcalcForm(TComponent* Owner) : TChildForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TLoadcalcForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	WriteRegistry();
	TForm *WinPtr = (TForm*)Application->FindComponent("TrimListSrcDlg");
    if (WinPtr) {
		WinPtr->Close();
    }

	RemoveMenuItems(PopupMenuCargoType->Items);
	Action = caFree;

}

// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::SetLabelList(void) {
    StabResultsLabels.push_back(Label1);
    StabResultsLabels.push_back(Label2);
    StabResultsLabels.push_back(Label3);
    StabResultsLabels.push_back(Label4);
    StabResultsLabels.push_back(Label5);
    StabResultsLabels.push_back(Label6);
    StabResultsLabels.push_back(Label7);
    StabResultsLabels.push_back(Label8);
	StabResultsLabels.push_back(Label9);
    StabResultsLabels.push_back(Label10);
    StabResultsLabels.push_back(Label11);
    StabResultsLabels.push_back(Label12);
    StabResultsLabels.push_back(Label13);
    StabResultsLabels.push_back(Label94);

    StabResultsLabels.push_back(Label59);
    StabResultsLabels.push_back(Label65);

    StabResultsLabels.push_back(Label15);
    StabResultsLabels.push_back(Label16);
    StabResultsLabels.push_back(Label17);
    StabResultsLabels.push_back(Label18);
    StabResultsLabels.push_back(Label19);
    StabResultsLabels.push_back(Label20);
    StabResultsLabels.push_back(Label21);
    StabResultsLabels.push_back(Label22);
    StabResultsLabels.push_back(Label92);

    StabResultsUnits.push_back(Label47);
    StabResultsUnits.push_back(Label48);
    StabResultsUnits.push_back(Label49);
    StabResultsUnits.push_back(Label50);
    StabResultsUnits.push_back(Label51);
	StabResultsUnits.push_back(Label52);
    StabResultsUnits.push_back(Label53);
    StabResultsUnits.push_back(Label54);
    StabResultsUnits.push_back(Label55);
	StabResultsUnits.push_back(Label56);
    StabResultsUnits.push_back(Label57);
    StabResultsUnits.push_back(Label58);
    StabResultsUnits.push_back(Label93);
    StabResultsUnits.push_back(Label96);

    StabResultsUnits.push_back(Label61);
    StabResultsUnits.push_back(Label67);

    StabResultsUnits.push_back(Label69);
    StabResultsUnits.push_back(Label70);
    StabResultsUnits.push_back(Label78);
    StabResultsUnits.push_back(Label80);
    StabResultsUnits.push_back(Label82);
    StabResultsUnits.push_back(Label84);
    StabResultsUnits.push_back(Label86);
    StabResultsUnits.push_back(Label88);
    StabResultsUnits.push_back(Label91);

    StabResults.push_back(Label35);
    StabResults.push_back(Label36);
    StabResults.push_back(Label37);
    StabResults.push_back(Label38);
    StabResults.push_back(Label39);
    StabResults.push_back(Label40);
    StabResults.push_back(Label41);
    StabResults.push_back(Label42);
    StabResults.push_back(Label43);
    StabResults.push_back(Label44);
    StabResults.push_back(Label45);
    StabResults.push_back(Label46);
    StabResults.push_back(Label14);
    StabResults.push_back(Label95);

    StabResults.push_back(Label60);
    StabResults.push_back(Label66);

    StabResults.push_back(Label68);
    StabResults.push_back(Label71);
    StabResults.push_back(Label79);
    StabResults.push_back(Label81);
    StabResults.push_back(Label83);
	StabResults.push_back(Label85);
    StabResults.push_back(Label87);
    StabResults.push_back(Label89);
	StabResults.push_back(Label90);

    //////////////////////////////////////////////////
    // GZ results
    //////////////////////////////////////////////////
    GZResultsLabels.push_back(GZLabel);
    GZResultsLabels.push_back(GZ30Label);
    GZResultsLabels.push_back(GZMaxLabel);
    GZResultsLabels.push_back(GZMaxAngleLabel);
    GZResultsLabels.push_back(GZArea030Label);
    GZResultsLabels.push_back(GZ3040Label);
    GZResultsLabels.push_back(GZ040Label);
    GZResultsLabels.push_back(FloodingAngleLabel);
    GZResultsLabels.push_back(FloodingTextLabel);

    GZResults.push_back(GZ);
    GZResults.push_back(GZ30);
    GZResults.push_back(GZmax);
    GZResults.push_back(GZMaxAngle);
    GZResults.push_back(GZ030);
    GZResults.push_back(GZ3040);
	GZResults.push_back(GZ040);
    GZResults.push_back(FloodingAngle);
    GZResults.push_back(Flooding);

    GZResultsUnits.push_back(GZUnit);
    GZResultsUnits.push_back(GZ30Unit);
    GZResultsUnits.push_back(GZmaxUnit);
    GZResultsUnits.push_back(AngleUnit);
    GZResultsUnits.push_back(GZ030Unit);
    GZResultsUnits.push_back(GZ3040Unit);
	GZResultsUnits.push_back(GZ040Unit);
	GZResultsUnits.push_back(FloodingAngleUnit);
    GZResultsUnits.push_back(FloodingUnit);
}

// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::UpdateLabels(void) {
	const int ValueList[] = {
        SVT_S_DFT_F, SVT_S_DFT_MS, SVT_S_DFT_A, SVT_S_TRIM, SVT_S_LIST_ANGLE,
        SVT_S_DEADWEIGHT, SVT_S_DISPLACEMENT, SVT_S_IMMERSION, SVT_S_VCG_ADJ,
        SVT_S_VCG_MARGIN, SVT_S_KM, SVT_S_GM_LIQ, SVT_S_LCG, SVT_S_TCG,
        SVT_S_MAX_SF, SVT_S_MAX_BM, SVT_CARGO_WEIGHT, SVT_BALLAST_WEIGHT,
        SVT_HEAVY_FUEL_WEIGHT, SVT_DIESEL_OIL_WEIGHT, SVT_LUBRICANTS_WEIGHT,
        SVT_FRESH_WATER_WEIGHT, SVT_MISC_WEIGHT, SVT_VOID_SPACE_WEIGHT,
        SVT_SOLIDS_WEIGHT};

	for (unsigned i = 0; i < StabResultsLabels.size() && i <
        NELEMENTS(ValueList); i++) {
        AnsiString Myunitstr;

        AnsiString ValNameStr = LibGetValue(SVT_VALUE_NAME, ValueList[i],
            LCStabCalc::StabCalc, 0);
        AnsiString ValueStr = LibGetValue(ValueList[i], LCStabCalc::StabCalc,
            &Myunitstr);
        // Set colours
        TLabel* ValueLabelPtr = StabResultsLabels[i];
        AnsiString Message;
        switch (ValueList[i]) {
        case SVT_S_TRIM: {
                float Trim = LCStabCalc::StabCalc->Trim;
                if (Trim < TSNTableHydrostatic::LCB_Tab->MinTrim || Trim >
                    TSNTableHydrostatic::LCB_Tab->MaxTrim) {
                    WarningLabelTrim->Visible = true;
                }
                else {
                    WarningLabelTrim->Visible = false;
                }
            } break;
        case SVT_S_MAX_SF: {
                if (LCStabCalc::StabCalc->MaxSfFrame &&
					LCStabCalc::StabCalc->MaxSfFrame->SfSeaPrcnt >= 100.0) {
					ValueLabelPtr->Font->Color = clRed;
                }
                else {
                    ValueLabelPtr->Font->Color = clGreen;
                }
                AnsiString tmpStr;
				LCStabCalc::StabCalc->GetStringValue(SVT_S_MAX_SF_FRAME_NAME, 0,
                    tmpStr);
                Label101->Caption = tmpStr;
			} break;
        case SVT_S_MAX_BM: {
                if (LCStabCalc::StabCalc->MaxBmFrame &&
                    LCStabCalc::StabCalc->MaxBmFrame->BmSeaPrcnt >= 100.0) {
                    ValueLabelPtr->Font->Color = clRed;
                }
                else {
                    ValueLabelPtr->Font->Color = clGreen;
                }
                AnsiString tmpStr;
                LCStabCalc::StabCalc->GetStringValue(SVT_S_MAX_BM_FRAME_NAME, 0,
                    tmpStr);
                Label103->Caption = tmpStr;
            } break;
        case SVT_S_GM_LIQ:
            if (LCStabCalc::StabCalc->GMCorrected < IMO_GM_MIN) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
                ValueLabelPtr->Font->Color = clGreen;
            }
            break;
        case SVT_S_DFT_MS:
            if (LCStabCalc::StabCalc->DraftMS >
                LCShipData::LCShip->MaxSummerDraft) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
                ValueLabelPtr->Font->Color = clGreen;
            }
			break;
        case SVT_S_VCG_MARGIN:
            if (TSNTableHydrostatic::MaxVCG_Tab) {
                if (LCStabCalc::StabCalc->VCGMargin <= 0.0) {
                    ValueLabelPtr->Font->Color = clRed;
                }
                else {
                    ValueLabelPtr->Font->Color = clGreen;
                }
            }
            else {
                StabResultsLabels[i]->Visible = false;
                StabResultsUnits[i]->Visible = false;
                ValueLabelPtr->Visible = false;
            }
            break;
        case SVT_S_DAM_MAX_VCG:
            if (TSNTableHydrostatic::DamageMaxVCG_Tab) {
                if (LCStabCalc::StabCalc->DamageVCGMarg <= 0.0) {
                    ValueLabelPtr->Font->Color = clRed;
                }
                else {
                    ValueLabelPtr->Font->Color = clGreen;
                }
            }
            else {
                StabResultsLabels[i]->Visible = false;
                StabResultsUnits[i]->Visible = false;
                ValueLabelPtr->Visible = false;
            }
            break;
        default:
            // if ( Refresh) StabResultsLabels[i]->Caption = ValNameStr;
            break;
        }
        if (Refresh) {
            StabResultsLabels[i]->Caption = ValNameStr;
            StabResultsUnits[i]->Caption = Myunitstr;
        }
        StabResults[i]->Caption = ValueStr;
	}

    const int ValueList2[] = {
        SVT_S_GZ, SVT_S_GZ_30, SVT_S_GZ_MAX, SVT_S_GZ_ANGLE, SVT_S_GZ_A0_30,
        SVT_S_GZ_A30_40, SVT_S_GZ_A0_40, SVT_S_FLOODING_ANGLE,
        SVT_S_REM_TO_FLOODING};

    for (unsigned i = 0; i < GZResultsLabels.size() && i <
        NELEMENTS(ValueList2); i++) {
        AnsiString Message;
        AnsiString Myunitstr;

        AnsiString ValNameStr = LibGetValue(SVT_VALUE_NAME, ValueList2[i],
            LCStabCalc::StabCalc, 0);
        AnsiString ValueStr = LibGetValue(ValueList2[i], LCStabCalc::StabCalc,
            &Myunitstr);
        // Set colours
        TLabel* ValueLabelPtr = GZResultsLabels[i];
        switch (ValueList2[i]) {
        case SVT_S_GZ_30:
            if (LCStabCalc::StabCalc->GZ30 < IMO_GZ30_MIN) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
                ValueLabelPtr->Font->Color = clGreen;
            }
            break;
        case SVT_S_GZ_ANGLE:
            if (LCStabCalc::StabCalc->GZAngle < IMO_GZMAX_ANGLE) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
                ValueLabelPtr->Font->Color = clGreen;
            }
            break;
        case SVT_S_GZ_A0_30:
            if (LCStabCalc::StabCalc->GZArea0_30 < IMO_GZAREA0_30) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
				ValueLabelPtr->Font->Color = clGreen;
            }
            break;
        case SVT_S_GZ_A30_40:
            if (LCStabCalc::StabCalc->GZArea30_40 < IMO_GZAREA30_40) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
                ValueLabelPtr->Font->Color = clGreen;
            }
            break;
        case SVT_S_GZ_A0_40:
            if (LCStabCalc::StabCalc->GZArea0_40 < IMO_GZAREA0_40) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
                ValueLabelPtr->Font->Color = clGreen;
            }
            break;
        case SVT_S_FLOODING_ANGLE:
            if (TSNTableHydrostatic::FloodinAngle_Tab) {
                FloodingAngleLabel->Visible = true;
                FloodingAngle->Visible = true;
                FloodingAngleUnit->Visible = true;
                FloodingTextLabel->Visible = false;
                Flooding->Visible = false;
                FloodingUnit->Visible = false;
            }
            else {
                FloodingAngleLabel->Visible = false;
                FloodingAngle->Visible = false;
                FloodingAngleUnit->Visible = false;
                if (!LCOpeningData::Table.empty()) {
                    FloodingTextLabel->Visible = true;
                    Flooding->Visible = true;
                    FloodingUnit->Visible = true;
                }
                else {
                    FloodingTextLabel->Visible = false;
                    Flooding->Visible = false;
					FloodingUnit->Visible = false;
                }
            }
            if (LCStabCalc::StabCalc->FldAng <= 0.0) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
                ValueLabelPtr->Font->Color = clGreen;
            }
            break;
        case SVT_S_REM_TO_FLOODING:
            if (LCStabCalc::StabCalc->ReserveDownflooding <= 0.0) {
                ValueLabelPtr->Font->Color = clRed;
            }
            else {
                ValueLabelPtr->Font->Color = clGreen;
            }
            break;
        default:
            break;
        }
        GZResults[i]->Caption = ValueStr;

        // Refresh
        if (Refresh) {
            if (!ValNameStr.IsEmpty())
                ValueLabelPtr->Caption = ValNameStr;
            GZResultsUnits[i]->Caption = Myunitstr;

        }
    }
    if (Refresh) {
        GZTableValueListEditor->TitleCaptions->BeginUpdate();
        GZTableValueListEditor->TitleCaptions->Clear();
        GZTableValueListEditor->TitleCaptions->Add
            ("Angle(" + GetUnitName(ANGLE_UNIT) + ")");
        GZTableValueListEditor->TitleCaptions->Add
            ("GZ(" + GetUnitName(LENGTH_UNIT) + ")");
        GZTableValueListEditor->Strings->BeginUpdate();
        GZTableValueListEditor->Strings->Clear();
		int Count = 0;
        for (float GZAngle = 0.0; GZAngle <= 60.00 / RAD_FACTOR;
        GZAngle += 1.0 / RAD_FACTOR, Count++) {
            char ResultBuf[BUF_SIZE];
            ConvertFromSi(ResultBuf, GZAngle, 5, 2, ANGLE_UNIT);
            AnsiString TempString = ResultBuf;
            ConvertFromSi(ResultBuf, LCStabCalc::StabCalc->CalculateGZ(GZAngle),
                5, 3, LENGTH_UNIT);
            TempString += "=" + (AnsiString)ResultBuf;
            GZTableValueListEditor->Strings->Add(TempString);
        }
        GZTableValueListEditor->TitleCaptions->EndUpdate();
        GZTableValueListEditor->Strings->EndUpdate();

        if (LCStabCalc::StabCalc->WarningList.empty()) {
            ResultMessagesBitBtn->Font->Color = clGreen;
            ResultMessagesBitBtn->Caption = "Criterias fulfilled";
        }
        else {
            ResultMessagesBitBtn->Font->Color = clRed;
            ResultMessagesBitBtn->Caption = "Criterias not fulfilled";
        }

        if (LCStabCalc::StabCalc->GZ30 < IMO_GZ30_MIN) {
            IMO_GZ30Label->Caption = "GZ > 0.20 meter not fulfilled";
            IMO_GZ30Label->Font->Color = clRed;
        }
        else {
            IMO_GZ30Label->Caption = "GZ > 0.20 meter fulfilled";
            IMO_GZ30Label->Font->Color = clGreen;
        }
        if (LCStabCalc::StabCalc->GZAngle < IMO_GZMAX_ANGLE) {
            IMO_GZMaxAngleLabel->Caption =
                "GZ max angle > 25 deg. not fulfilled";
            IMO_GZMaxAngleLabel->Font->Color = clRed;
        }
        else {
            IMO_GZMaxAngleLabel->Caption = "GZ max angle > 25 deg. fulfilled";
            IMO_GZMaxAngleLabel->Font->Color = clGreen;
        }
		if (LCStabCalc::StabCalc->GZArea0_30 < IMO_GZAREA0_30) {
            IMO_GZArea0_30Label->Caption =
                "GZ area > 0.055 meter*rad not fulfilled";
            IMO_GZArea0_30Label->Font->Color = clRed;
        }
        else {
            IMO_GZArea0_30Label->Caption =
                "GZ area > 0.055 meter*rad fulfilled";
            IMO_GZArea0_30Label->Font->Color = clGreen;
        }
        if (LCStabCalc::StabCalc->GZArea30_40 < IMO_GZAREA30_40) {
            IMO_GZArea30_40Label->Caption =
                "GZ area < 0.03 meter*rad not fulfilled";
            IMO_GZArea30_40Label->Font->Color = clRed;
        }
        else {
            IMO_GZArea30_40Label->Caption =
                "GZ area > 0.03 meter*rad fulfilled";
            IMO_GZArea30_40Label->Font->Color = clGreen;
        }
        if (LCStabCalc::StabCalc->GZArea0_40 < IMO_GZAREA0_40) {
            IMO_GZArea0_40Label->Caption =
                "GZ area < 0.09 meter*rad not fulfilled";
            IMO_GZArea0_40Label->Font->Color = clRed;
        }
        else {
            IMO_GZArea0_40Label->Caption = "GZ area > 0.09 meter*rad fulfilled";
            IMO_GZArea0_40Label->Font->Color = clGreen;
        }
        if (LCStabCalc::StabCalc->GZArea0_40 < IMO_GZAREA0_40) {
            IMO_GZArea0_40Label->Caption =
                "GZ area < 0.09 meter*rad not fulfilled";
            IMO_GZArea0_40Label->Font->Color = clRed;
        }
        else {
            IMO_GZArea0_40Label->Caption = "GZ area > 0.09 meter*rad fulfilled";
            IMO_GZArea0_40Label->Font->Color = clGreen;
        }
        if (LCStabCalc::StabCalc->GMCorrected < IMO_GM_MIN) {
            IMO_GMLabel->Caption =
				"IMO criteria not fulfilled: GM < 0.15 meter";
            IMO_GMLabel->Font->Color = clRed;
        }
        else {
            IMO_GMLabel->Caption = "IMO criteria fulfilled: GM > 0.15 meter";
            IMO_GMLabel->Font->Color = clGreen;
        }

        if (LCStabCalc::StabCalc->DraftMS > LCShipData::LCShip->MaxSummerDraft)
        {
            AnsiString Myunitstr;
            AnsiString SDraft = LibGetValue(SVT_LS_MAX_SUMMER_DRAFT,
                LCShipData::LCShip, &Myunitstr);
            AnsiString Message =
                "IMO Criteria not fulfilled : Max summer draft " + SDraft +
                " " + Myunitstr + " exceeded.";
            IMO_MaxSummerDraftLabel->Caption = Message;
            IMO_MaxSummerDraftLabel->Font->Color = clRed;
        }
        else {
            AnsiString Myunitstr;
            AnsiString SDraft = LibGetValue(SVT_LS_MAX_SUMMER_DRAFT,
                LCShipData::LCShip, &Myunitstr);
            AnsiString Message =
                "IMO Criteria fulfilled : Draft < Max summer draft " + SDraft +
                " " + Myunitstr;
            IMO_MaxSummerDraftLabel->Caption = Message;
            IMO_MaxSummerDraftLabel->Font->Color = clGreen;
        }

        ResultsMemo->Lines->BeginUpdate();
        ResultsMemo->Lines->Clear();
        for (unsigned i = 0;
        i < LCStabCalc::StabCalc->IMOCriteriaList.size(); i++) {
            ResultsMemo->Lines->Add(LCStabCalc::StabCalc->IMOCriteriaList[i]);
        }
        ResultsMemo->Lines->EndUpdate();
    }
    Refresh = false;
}

void __fastcall TLoadcalcForm::FormCreate(TObject *Sender) {

	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\LoadCalcPicture\\";
	if (LCShipData::ClassificationSociety == C_LC_CLASS_DNV) {
        Caption = "Load calculator ( This program does not check damage stability )";
    }
    else {
        Caption = "Load calculator";
	}
	Height = 740;
    Width = 900;
    Tag = C_PROJ_LOADING_COMPUTER;
    SetStrGridValueList();
	SetStrGridOtherValueList();
	CopyObjectTables();
    SetLabelList();
	UserInputMode = false;
	ReadRegistry();
    TabControlChange();
    RefreshOnlineOfflineIndication();
    ShipParticularsMemo->Lines->BeginUpdate();
    ShipParticularsMemo->Lines->Clear(); {
        LCValInfo ValData[] = {
            {(PRogramObjectBase*)PROProjectInfo::PROProjectInfoPtr,
                    SVT_SHIP_LPP, "Length between PP\t:"},
            {(PRogramObjectBase*)PROProjectInfo::PROProjectInfoPtr,
                    SVT_SHIP_WIDTH, "Width\t\t:"},
            {(PRogramObjectBase*)LCShipData::LCShip, SVT_LS_WEIGHT,
                    "Light ship weight\t:"},
            {(PRogramObjectBase*)LCShipData::LCShip, SVT_LS_MAX_SUMMER_DRAFT,
                    "Max summer draft\t:"}, };
        ShipParticularsMemo->Lines->Add("");
        ShipParticularsMemo->Lines->Add("Sign convention:");
        ShipParticularsMemo->Lines->Add("\tTrim aft is negative.");
        ShipParticularsMemo->Lines->Add("\tList port is negative.");
        ShipParticularsMemo->Lines->Add("");
        for (unsigned i = 0; i < NELEMENTS(ValData); i++) {
            AnsiString UnitStr;
            int Status;
			AnsiString tmpStr = ValData[i].Description +
                LibGetValue(ValData[i].ValueKey, 0, 0, ValData[i].ObjPtr, 8,
                SVT_FLAG_NORMAL, &UnitStr, &Status);
            tmpStr += " " + UnitStr;
            ShipParticularsMemo->Lines->Add(tmpStr);
        }
        ShipParticularsMemo->Lines->EndUpdate();
    }
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::FormShow(TObject *Sender) {
    Refresh = true;
	SetHeadings();
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::UpdateStringGrids(void) {
	UpdateStringGrid(CurrentTable, CurrentValueList, LocDataStringGrid);
	UpdateStringGrid(FrameTable, FrameValueList, FramesStringGrid);
	UpdateStringGrid(SectionTable, SectionValueList, SectionsStringGrid);
}

void __fastcall TLoadcalcForm::SetStrGridValueList(void) {
    const int ValueList1[] = {
		SVT_PRO_NAME, SVT_ULLAGE, SVT_WEIGHT, SVT_VOLUME, SVT_VOLPERCENT,
        SVT_DENSITY, SVT_TEMP, SVT_CARGO_TYPE_NAME, SVT_REF_DNS1, SVT_REF_DNS2,
        SVT_REF_TMP1, SVT_REF_TMP2, SVT_COEFF, SVT_VCF, SVT_API, SVT_L_LCG,
        SVT_L_TCG, SVT_L_VCG, SVT_L_TFS, SVT_L_FSM, SVT_L_ONLINE_STATUS};

    const int ValueList2[] = {
		SVT_PRO_NAME, SVT_LEVEL_FC, SVT_WEIGHT, SVT_VOLUME, SVT_VOLPERCENT,
        SVT_DENSITY, SVT_TEMP, SVT_CARGO_TYPE_NAME, SVT_REF_DNS1, SVT_REF_DNS2,
        SVT_REF_TMP1, SVT_REF_TMP2, SVT_COEFF, SVT_API, SVT_L_LCG, SVT_L_TCG,
        SVT_L_VCG, SVT_L_TFS, SVT_L_FSM};

    const int ValueList3[] = {
        SVT_PRO_NAME, SVT_WEIGHT, SVT_L_LENGTH, SVT_L_LCG, SVT_L_TCG, SVT_L_VCG,
    };
    CurrentValueList.clear();
	switch (LocationTabControl->TabIndex) {
    case -1:
    case 0:
        for (unsigned i = 0; i < NELEMENTS(ValueList1); i++) {
            CurrentValueList.push_back((int)ValueList1[i]);
        }
        break;
    case 1:
    case 2:
    case 4:
        for (unsigned i = 0; i < NELEMENTS(ValueList2); i++) {
            CurrentValueList.push_back((int)ValueList2[i]);
        }
        break;
    case 3:
        for (unsigned i = 0; i < NELEMENTS(ValueList3); i++) {
            CurrentValueList.push_back((int)ValueList3[i]);
        }
        break;
    }

}

void __fastcall TLoadcalcForm::SetStrGridOtherValueList(void) {
    const int FValueList[] = {
        SVT_PRO_NAME, SVT_F_DIST_TO_FRAME0, SVT_F_DIST_TO_PREV, SVT_F_BM,
        SVT_F_SF, SVT_F_CORR_BM, SVT_F_BMHRBPRCNT, SVT_F_BMSEAPRCNT,
        SVT_F_SFHRBPRCNT, SVT_F_SFSEAPRCNT, };

    const int SValueList[] = {
        SVT_PRO_NAME, SVT_SEC_DIST_TO_APP, SVT_SEC_STEELW, SVT_SEC_DEADWEIGHT,
        SVT_SEC_BUOYANCY, SVT_SEC_DRAFT, SVT_SEC_LOAD, SVT_SEC_MOM_CHANGE,
        SVT_SEC_AVG_BM, SVT_SEC_AVG_SF, SVT_SEC_LENGTH, };
    FrameValueList.clear();
    for (unsigned i = 0; i < NELEMENTS(FValueList); i++) {
        FrameValueList.push_back((int)FValueList[i]);
    }
    SectionValueList.clear();
    for (unsigned i = 0; i < NELEMENTS(SValueList); i++) {
        SectionValueList.push_back((int)SValueList[i]);
    }

}

void __fastcall TLoadcalcForm::LocationTabControlChange(TObject *Sender) {
    TabControlChange();
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::SetHeadings(void) {
    if (!CurrentTable.empty()) {
        PRogramObjectBase *ElementPtr = (PRogramObjectBase*)CurrentTable[0];
        SetLCHeading(ElementPtr, CurrentValueList, LocDataStringGrid);
    }
    if (!LCFrameData::FrameList.empty()) {
        SetLCHeading((PRogramObjectBase*)LCFrameData::FrameList[0],
            FrameValueList, FramesStringGrid);
    }
    if (!LCSectionData::Table.empty()) {
        SetLCHeading((PRogramObjectBase*)LCSectionData::Table[0],
			SectionValueList, SectionsStringGrid);
    }
}

void __fastcall TLoadcalcForm::SetLCHeading(PRogramObjectBase *ElementPtr,vector<int>ValueList, TAdvStringGrid *StrGrid) {
	if (ElementPtr) {
        StrGrid->ColCount = ValueList.size();
        for (unsigned col = 0; col < ValueList.size(); col++) {
            AnsiString MyNameStr;
            AnsiString Myunitstr;

            MyNameStr = LibGetValue(SVT_VALUE_NAME, ValueList[col],
                ElementPtr, 0);
            LibGetValue(ValueList[col], ElementPtr, &Myunitstr);
            StrGrid->Cells[col][0] = MyNameStr.c_str();
            StrGrid->Cells[col][1] = Myunitstr.c_str();
        }
    }
}

void __fastcall TLoadcalcForm::SetCurrentTable(void) {
    switch (LocationTabControl->TabIndex) {
	case -1:
    case 0:
        CurrentTable = CargoTable;
        break;
    case 1:
        CurrentTable = BallastTable;
        break;
    case 2:
        CurrentTable = ServiceTable;
        break;
    case 3:
        CurrentTable = SolidsTable;
        break;
    case 4:
        CurrentTable = VoidSpaceTable;
        break;
    }

}


void __fastcall TLoadcalcForm::LocDataStringGridMouseDown(TObject *Sender,
    TMouseButton Button, TShiftState Shift, int X, int Y) {

	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
	int tmpCurrentColumn = CurrentColumn;
	int tmpCurrentRow    = CurrentRow;
	StringGrid->MouseToCell(X, Y, tmpCurrentColumn, tmpCurrentRow);
	tmpCurrentColumn = CurrentColumn;
	tmpCurrentRow    = CurrentRow;

    if (CurrentRow > 1) {
		switch (CurrentValueList[CurrentColumn]) {
        case SVT_CARGO_TYPE_NAME:
            FindCargoTypes();
            StringGrid->PopupMenu = PopupMenuCargoType;
            PopuMenupOnlineOffline->AutoPopup = false;
            PopupMenuEnableDisable->AutoPopup = false;
            PopupMenuCargoType->AutoPopup = true;
            break;
        case SVT_PRO_NAME:
            if (CurrentRow >= StringGrid->FixedRows) {
                switch (CurrentTable[CurrentRow - StringGrid->FixedRows]->Type)
                {
                case C_LC_TANK_CARGO:
                case C_LC_TANK_BALLAST:
                case C_LC_TANK_HFO:
                case C_LC_TANK_DO:
                case C_LC_TANK_LUB:
                case C_LC_TANK_FW:
                case C_LC_TANK_MISC:
                case C_LC_TANK_VOIDSPACE: {
                        LCTankData* tmpPtr =
                            (LCTankData*)CurrentTable[CurrentRow -
                            StringGrid->FixedRows];
						if (tmpPtr->IsOnlineTank()) {
                            StringGrid->PopupMenu = PopuMenupOnlineOffline;
                            PopuMenupOnlineOffline->AutoPopup = true;
                            PopupMenuEnableDisable->AutoPopup = false;
                            PopupMenuCargoType->AutoPopup = false;
                            PopupMenuSolid->AutoPopup = false;
                        }
                        else {
                            PopuMenupOnlineOffline->AutoPopup = false;
                            PopupMenuEnableDisable->AutoPopup = false;
                            PopupMenuCargoType->AutoPopup = false;
                            PopupMenuSolid->AutoPopup = false;
                        }
                    } break;
                case C_LC_SOLID_VARIABLE: {
                        LCVariableSolidData* tmpPtr =
                            (LCVariableSolidData*)
							CurrentTable[CurrentRow - StringGrid->FixedRows];
                        StringGrid->PopupMenu = PopupMenuSolid;
                        PopupMenuSolid->AutoPopup = true;
                        PopuMenupOnlineOffline->AutoPopup = false;
                        PopupMenuEnableDisable->AutoPopup = false;
                        PopupMenuCargoType->AutoPopup = false;
                        NewSolidDlg->SetPointer(tmpPtr);
                    } break;
                default:
                    break;
                }
            }
            break;
        default:
            StringGrid->PopupMenu = PopupMenuEnableDisable;
            PopuMenupOnlineOffline->AutoPopup = false;
            PopupMenuEnableDisable->AutoPopup = true;
            PopupMenuCargoType->AutoPopup = false;
            PopupMenuSolid->AutoPopup = false;
            break;
        }
    }
    else {
        PopupMenuEnableDisable->AutoPopup = false;
        PopupMenuCargoType->AutoPopup = false;
        PopuMenupOnlineOffline->AutoPopup = false;
        PopupMenuSolid->AutoPopup = false;
    }

}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::StabcalcTimerTimer(TObject *Sender) {
    if (StabcalcTimer->Interval != 30000)
        StabcalcTimer->Interval = 30000;
    Calculate();
}

// ---------------------------------------------------------------------------
void __fastcall TLoadcalcForm::CopyObjectTables(void) {
	for (unsigned i = 0; i < LCLocationData::CargoTable.size(); i++) {
		CargoTable.push_back((PRogramObjectBase*)LCLocationData::CargoTable[i]);
    }
    for (unsigned i = 0; i < LCLocationData::BallastTable.size(); i++) {
        BallastTable.push_back
            ((PRogramObjectBase*)LCLocationData::BallastTable[i]);
    }
	for (unsigned i = 0; i < LCLocationData::ServiceTable.size(); i++) {
        ServiceTable.push_back
            ((PRogramObjectBase*)LCLocationData::ServiceTable[i]);
    }
    for (unsigned i = 0; i < LCLocationData::SolidsTable.size(); i++) {
        SolidsTable.push_back
            ((PRogramObjectBase*)LCLocationData::SolidsTable[i]);
    }
    for (unsigned i = 0; i < LCLocationData::VoidSpaceTable.size(); i++) {
        VoidSpaceTable.push_back
            ((PRogramObjectBase*)LCLocationData::VoidSpaceTable[i]);
    }
    for (unsigned i = 0; i < LCFrameData::FrameList.size(); i++) {
        FrameTable.push_back((PRogramObjectBase*)LCFrameData::FrameList[i]);
    }
    for (unsigned i = 0; i < LCSectionData::Table.size(); i++) {
		SectionTable.push_back((PRogramObjectBase*)LCSectionData::Table[i]);
    }
}

void __fastcall TLoadcalcForm::Calculate(void) {
    LCStabCalc::StabCalc->Calculate();
    LCStabCalc::StabCalc->Strength();
    LCStabCalc::StabCalc->CheckResult();
    Refresh = true;
	UpdateLabels();
    PaintStrengthGraph();
    PaintGZGraph();
}

void __fastcall TLoadcalcForm::ReadRegistry(void) {
    TRegistry *Registry = new TRegistry;
    try {
        Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_READ;

        // False because we do not want to create it if it doesn't exist
        bool Status = Registry->OpenKey(RegNameKey, false);
        if (Status) {
            if (Registry->ValueExists("PageControl1")) {
                PageControl1->ActivePageIndex =
                    Registry->ReadInteger("PageControl1");
            }
            if (Registry->ValueExists("LocationTabControl")) {
                LocationTabControl->TabIndex =
                    Registry->ReadInteger("LocationTabControl");
            }
            Registry->CloseKey();
        }
    }
    __finally {
        delete Registry;
	}
}

void __fastcall TLoadcalcForm::WriteRegistry(void) {
    TRegistry *Registry = new TRegistry;
    try {
        Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_WRITE;

        // False because we do not want to create it if it doesn't exist
        bool Status = Registry->OpenKey(RegNameKey, true);
        if (Status) {
            Registry->WriteInteger("PageControl1",
            PageControl1->ActivePageIndex);
            Registry->WriteInteger("LocationTabControl",
                LocationTabControl->TabIndex);
            Registry->CloseKey();
        }
    }
    __finally {
        delete Registry;
    }
}

#define COND_SEA        0
#define COND_HARBOUR    1

//////////////////////////////////////////////////////////////////
//
// Cheating a little here. Direct acces to objects values instead
// of via GetValue
//
//////////////////////////////////////////////////////////////////
void __fastcall TLoadcalcForm::PaintStrengthGraph(void) {
    // Strenght
    float TmpMaxSf;
    float TmpMaxBm;
    switch (ConditionRadioGroup->ItemIndex) {
    default:
    case COND_SEA: // 0
        TmpMaxSf = max(LCShipData::LCShip->MaxSfHogSea,
            LCShipData::LCShip->MaxSfSagSea);
        TmpMaxBm = max(LCShipData::LCShip->MaxBmHogSea,
            LCShipData::LCShip->MaxBmSagSea);
        break;
    case COND_HARBOUR: // 1
        TmpMaxSf = max(LCShipData::LCShip->MaxSfHogHrb,
            LCShipData::LCShip->MaxSfSagHrb);
        TmpMaxBm = max(LCShipData::LCShip->MaxBmHogHrb,
            LCShipData::LCShip->MaxBmSagHrb);
        break;
    }
    float MaxSf = ConvertFromSi(NULL, TmpMaxSf * 1.2, 7, 2, WEIGHT_UNIT);
    float MaxBm = ConvertFromSi(NULL, TmpMaxBm * 1.2, 7, 2, MOMENT_UNIT);

    Series1->Title = (String)"Bending moment(" + GetUnitGroupName
        (MOMENT_UNIT) + ")";
    Series2->Title = (String)"Shear force(" + GetUnitGroupName
        (WEIGHT_UNIT) + ")";
    Series1->Clear();
    Series2->Clear();
    Series3->Clear();
    Series4->Clear();
    Series5->Clear();
    Series6->Clear();
    Chart1->BottomAxis->Maximum = PROProjectInfo::LengthBetweenPP + 10.0;
    Chart1->BottomAxis->Minimum = 0;
    Chart1->TopAxis->Maximum = PROProjectInfo::LengthBetweenPP + 10.0;
    Chart1->TopAxis->Minimum = 0;
    Chart1->LeftAxis->Minimum = -MaxBm;
    Chart1->LeftAxis->Maximum = MaxBm;
    Chart1->RightAxis->Minimum = -MaxSf;
    Chart1->RightAxis->Maximum = MaxSf;
    Chart1->Foot->AdjustFrame = false;
    Chart1->Foot->Visible = true;
    Chart1->Foot->Text->Clear();
    Chart1->Foot->Text->Add(ConditionLabel->Caption);
    Chart1->Foot->Font->Color = clBlack;
    // Chart1->Repaint();
    float XValue;
    float YValue;
    String XLabel = "";
    for (unsigned i = 0; i < LCFrameData::FrameList.size(); i++) {
        LCFrameData *FPtr = LCFrameData::FrameList[i];
        if (LCFrameData::FrameInList(FPtr)) {
            XLabel = FPtr->Name;
        }
        else {
            XLabel = "";
        }
        XValue = FPtr->DistToFrame0;

        YValue = ConvertFromSi(NULL, FPtr->CorrBm, 7, 2, MOMENT_UNIT);
        Series1->AddXY(XValue, YValue, XLabel, (TColor)clTeeColor);

        YValue = ConvertFromSi(NULL, FPtr->Sf, 7, 2, WEIGHT_UNIT);
        Series2->AddXY(XValue, YValue, XLabel, (TColor)clTeeColor);
    }

    ////////////////////////////////////////////////////////////
    // Limits
    for (unsigned i = 0; i < LCFrameData::Table.size(); i++) {
        LCFrameData *F = LCFrameData::Table[i];
        float MaxSfLimHog, MaxBmLimHog;
        float MaxSfLimSag, MaxBmLimSag;
        XValue = F->DistToFrame0;
        XLabel = "";

        switch (ConditionRadioGroup->ItemIndex) {
        case COND_HARBOUR:
            MaxSfLimHog = F->Limit[SFHOGHRB];
            MaxBmLimHog = F->Limit[BMHOGHRB];
            MaxSfLimSag = -F->Limit[SFSAGHRB];
            MaxBmLimSag = -F->Limit[BMSAGHRB];
            break;
        default:
        case COND_SEA:
            MaxSfLimHog = F->Limit[SFHOGSEA];
            MaxBmLimHog = F->Limit[BMHOGSEA];
            MaxSfLimSag = -F->Limit[SFSAGSEA];
            MaxBmLimSag = -F->Limit[BMSAGSEA];
            break;
        }
        MaxBmLimHog = ConvertFromSi(NULL, MaxBmLimHog, 7, 2, MOMENT_UNIT);
        MaxSfLimHog = ConvertFromSi(NULL, MaxSfLimHog, 7, 2, WEIGHT_UNIT);
        MaxBmLimSag = ConvertFromSi(NULL, MaxBmLimSag, 7, 2, MOMENT_UNIT);
        MaxSfLimSag = ConvertFromSi(NULL, MaxSfLimSag, 7, 2, WEIGHT_UNIT);
        Series3->AddXY(XValue, MaxBmLimSag, XLabel, (TColor)clTeeColor);
        Series4->AddXY(XValue, MaxBmLimHog, XLabel, (TColor)clTeeColor);
        Series5->AddXY(XValue, MaxSfLimSag, XLabel, (TColor)clTeeColor);
        Series6->AddXY(XValue, MaxSfLimHog, XLabel, (TColor)clTeeColor);
    }
}

void __fastcall TLoadcalcForm::ConditionRadioGroupClick(TObject *Sender) {
    PaintStrengthGraph();
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::PrintGraphBitBtnClick(TObject *Sender) {
    Chart1->Print();
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::PaintGZGraph(void) {
    // Update GZ-curve
    Series7->Clear();
    Series8->Clear();
    GZChart->BottomAxis->Title->Caption = GetUnitName(ANGLE_UNIT);
    GZChart->LeftAxis->Title->Caption = GetUnitName(LENGTH_UNIT);
    GZChart->Foot->AdjustFrame = false;
    GZChart->Foot->Visible = true;
    GZChart->Foot->Text->Clear();
    GZChart->Foot->Text->Add(ConditionLabel->Caption);
    GZChart->Foot->Font->Color = clBlack;
    float YFactor;
    if (GetUnit(LENGTH_UNIT) == U_METER) {
        YFactor = 1.0;
    }
    else {
        YFactor = 1 / FEET_TO_METER;
    }
    GZChart->LeftAxis->Minimum = 0;
    if (LCShipData::GZScale) {
        GZChart->LeftAxis->AutomaticMaximum = false;
        GZChart->LeftAxis->Maximum = YFactor * LCShipData::GZScale;
    }
    else {
        GZChart->LeftAxis->AutomaticMaximum = true;
    }

    // float tempYmax = 1;
    for (int i = 0; i < 60; i++) {
        float Angle = i / RAD_FACTOR;
        float XValue;
        if (GetUnit(ANGLE_UNIT) == U_DEGREES) {
            XValue = i;
        }
        else {
            XValue = Angle;
        }
        float YValue = YFactor * LCStabCalc::StabCalc->CalculateGZ(Angle);
        // if( tempYmax < YValue )  tempYmax = YValue;
        Series7->AddXY(XValue, YValue, "", (TColor)clTeeColor);
    }
    Series8->AddXY(0, 0, "", (TColor)clTeeColor);
	Series8->AddXY(60, LCStabCalc::StabCalc->GMCorrected*YFactor, "", (TColor)clTeeColor);

}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::FindCargoTypes(void) {
	vector<CTOUser*>tmpCargoTypeVector = CTOUser::GetDefinedCargoes();
    if (tmpCargoTypeVector.empty() && !PopupMenuCargoType->Items->Count) {
		for (int index = 0; index <= SizeofBasicCargoNameList; index++) {
            const AnsiString ACaption =
                LibGetValueName(BasicCargoNameList,
                SizeofBasicCargoNameList, index);
            TShortCut AShortCut = NULL;
            const AnsiString tempString =
                AnsiString::StringOfChar('q', index + 1); // IntToStr(temp);
            TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
                PopupMenuCargoTypeExecute, 0, tempString);
            TempItem->Tag = (CTY_NOT_DEFINED << 16) | index;
            PopupMenuCargoType->Items->Add(TempItem);
        }

    }
    if (tmpCargoTypeVector != CargoTypeVector) {
        RemoveMenuItems(PopupMenuCargoType->Items);
        CargoTypeVector = tmpCargoTypeVector;
        for (int index = 0; index <= SizeofBasicCargoNameList; index++) {
            const AnsiString ACaption =
                LibGetValueName(BasicCargoNameList,
                SizeofBasicCargoNameList, index);
            TShortCut AShortCut = NULL;
            const AnsiString tempString =
                AnsiString::StringOfChar('q', index + 1); // IntToStr(temp);
            TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
                PopupMenuCargoTypeExecute, 0, tempString);
            TempItem->Tag = (CTY_NOT_DEFINED << 16) | index;
            PopupMenuCargoType->Items->Add(TempItem);
        }
        if (!CargoTypeVector.empty()) {
            PopupMenuCargoType->Items->Add(NewLine());
            for (unsigned index = 0; index < CargoTypeVector.size(); index++) {
                const AnsiString ACaption = CargoTypeVector[index]->Name;
                TShortCut AShortCut = NULL;
                const AnsiString tempString =
                    AnsiString::StringOfChar('q', index + 1); // IntToStr(temp);
                TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
                    PopupMenuCargoTypeExecute, 0, "");
                TempItem->Caption = ACaption;
                TempItem->Tag = (CargoTypeVector[index]->CargoTypeKey << 16)
                    | CargoTypeVector[index]->BaseCargoType;
                PopupMenuCargoType->Items->Add(TempItem);
            }
        }
    }
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::PopupMenuCargoTypeExecute(TObject *Sender) {
    TMenuItem *TempItem = (TMenuItem*)Sender;
    // TPopupMenu *PMPtr =(TPopupMenu *)Sender;
    int CRow = CurrentRow - 2;
    if (TempItem && CRow >= 0 && int(CurrentTable.size()) > CRow) {
        PRogramObjectBase *PROPtr = CurrentTable[CRow];
        if (PROPtr) {
            int CargoType = TempItem->Tag >> 16;
            int BaseCargo = TempItem->Tag & 0xffff;
            if (CargoType == CTY_NOT_DEFINED) {
                LibPutValue(SVT_BASIC_TYPE, PROPtr, BaseCargo);
            }
            else {
                if (CargoType >= 0)
                    LibPutValue(SVT_CARGO_TYPE, PROPtr, CargoType);
            }
        }
		DeactivateEditTimerTimer();
	}
}

void __fastcall TLoadcalcForm::ClearTanksButtonClick(TObject *Sender) {
    for (unsigned i = 0; i < CurrentTable.size(); i++) {
        LibPutValue(SVT_WEIGHT, CurrentTable[i], "0.0");
    }
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::SaveConditionToolButtonClick(TObject *Sender) {
    if (ConditionSaveDialog->Execute()) {
        ConditionFileName = ConditionSaveDialog->FileName;
        int EndOfPath = ConditionFileName.LastDelimiter("\\:");
        AnsiString SName = ConditionFileName.SubString(EndOfPath + 1,
            ConditionFileName.Length() - EndOfPath);
        int EndOfPath2 = SName.LastDelimiter(".");
        SName = SName.SubString(1, EndOfPath2 - 1);
        ConditionLabel->Caption = SName;
        AnsiString tmpStr = LCShipData::SaveCondition();
        ofstream ConfigStream;
		ConfigStream.open(ConditionFileName.c_str(),
            ios::out | ios::binary | ios::trunc);
        bool StreamStatus = (bool)ConfigStream;
        if (StreamStatus) {
            // DataPtr[Size++] = 26; // EOF mark
            // DataPtr[Size++] = 0;
            ConfigStream.write(tmpStr.c_str(), tmpStr.Length());
        }
    }

}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::NewConditionToolButtonClick(TObject *Sender) {
    for (unsigned i = 0; i < LCLocationData::Table.size(); i++) {
        LibPutValue(SVT_WEIGHT,
            (PRogramObjectBase*)LCLocationData::Table[i], "0.0");
    }

}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::OnlineToolButton1Click(TObject *Sender) {
	LCShipData::IsOnline = !LCShipData::IsOnline;
	for(unsigned i=0; i < CurrentTable.size(); i++){
		PRogramObjectBase * LPtr = (PRogramObjectBase*)CurrentTable[i];
		LibPutValue(SVT_L_ONLINE_STATUS, LPtr, AnsiString(int(LCShipData::IsOnline)));
	}


	RefreshOnlineOfflineIndication();
	StabcalcTimer->Interval = 1000;
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::LoadConditionToolButtonClick(TObject *Sender) {
    if (ConditionOpenDialog->Execute()) {
        ConditionFileName = ConditionOpenDialog->FileName;
        int EndOfPath = ConditionFileName.LastDelimiter("\\:");
        AnsiString SName = ConditionFileName.SubString(EndOfPath + 1,
            ConditionFileName.Length() - EndOfPath);
        int EndOfPath2 = SName.LastDelimiter(".");
        SName = SName.SubString(1, EndOfPath2 - 1);
        ConditionLabel->Caption = SName;
        bool ReadOK = true;
        TSNConfigString ConfigString(CONFIG_FILE_SIZE);
        if (ConfigString.ReadFile(ConditionFileName.c_str())) {
            ReadOK = LCShipData::LoadCondition(ConfigString);
        }
        if (ReadOK) {
            Calculate();
        }
    }

}

// ---------------------------------------------------------------------------
void __fastcall TLoadcalcForm::TabControlChange(void) {
	SetCurrentTable();
    SetStrGridValueList();
    SetHeadings();
    LocDataStringGrid->Repaint();
}

void __fastcall TLoadcalcForm::PrintReportToolButtonClick(TObject *Sender) {
	TBitBtn *btnPtr = (TBitBtn*)Sender;
	PrintReportToolButton->Enabled = false;

	// LINES_PR_PAGE
	// PrintLoadCalcReport();      PrintPage1
/*
	LoadCalcReportForm->PrintPage1();
	LoadCalcReportForm->PrintPage2();
	LoadCalcReportForm->PrintPage3();
	LoadCalcReportForm->PrintPage4();
	LoadCalcReportForm->QRCompositeReport1->Print();
*/
	//frxReportLoadCalc->;
	PrintReportToolButton->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::PreviewReportToolButtonClick(TObject *Sender) {
	TBitBtn *btnPtr = (TBitBtn*)Sender;
	PreviewReportToolButton->Enabled = false;
	QRCopyToTLabel(frxReportLoadCalc,"MemoShipName"     ,SVT_SHIP_NAME   ,PROProjectInfo::PROProjectInfoPtr);
   //	QRCopyToTLabel(frxReportLoadCalc,"MemoProject"      ,SVT_SYSTEM_ID   ,PROProjectInfo::PROProjectInfoPtr);
   //	QRCopyToTLabel(frxReportLoadCalc,"MemoDataRevision" ,SVT_DATA_VERSION,PROSystemData::TXUSystemData);

	/*
	// LINES_PR_PAGE
	// PrintLoadCalcReport();      PrintPage1

	LoadCalcReportForm->PrintPage1();
	LoadCalcReportForm->PrintPage2();
	LoadCalcReportForm->PrintPage3();
	LoadCalcReportForm->PrintPage4();
	// LoadCalcReportForm->QRCompositeReport1->Print();   //must use print instead of preview
	LoadCalcReportForm->QRCompositeReport1->Preview();
	*/
	PrintPage1();
	PrintPage2();
	PrintPage3();
	PrintPage4();
	frxReportLoadCalc->ShowReport();

	PreviewReportToolButton->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::ResultMessagesBitBtnClick(TObject *Sender) {
    TForm *WinPtr = (TForm*)Application->FindComponent("LoadCalcMessagesForm");
    if (WinPtr) {
        WinPtr->BringToFront();
    }
    else {
        Application->CreateForm(__classid(TLoadCalcMessagesForm),
            &LoadCalcMessagesForm);
    }
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::SetupButtonClick(TObject *Sender) { {
        TControl *WinPtr = (TControl*)Application->FindComponent
            ("TrimListSrcDlg");
        if (WinPtr) {
            WinPtr->BringToFront();
        }
        else {
            Application->CreateForm(__classid(TTrimListSrcDlg),
            &TrimListSrcDlg);
        }
    }
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::PrintButtonClick(TObject *Sender) {
    GZChart->Print();
}

// ---------------------------------------------------------------------------
void __fastcall TLoadcalcForm::RefreshOnlineOfflineIndication(void) {
	bool Online = false;
	for(unsigned i=0; !Online && i < CurrentTable.size(); i++){
		LCTankData* tmpPtr = (LCTankData*)CurrentTable[i];
		if (tmpPtr->IsOnline && tmpPtr->IsOnlineTank()) {
			Online = true;
		}
	}
	LCShipData::IsOnline = Online;
	if (LCShipData::IsOnline) {
		OnlineToolButton->Caption = FindDictionaryWord(L_WORD765); // Offline
		OnlineToolButton->ImageIndex = 19;
		OnlineStatusBitBtn->Font->Color = clGreen;
        OnlineStatusBitBtn->Caption = FindDictionaryWord(L_WORD764); // Online
    }
    else {
        OnlineToolButton->Caption = FindDictionaryWord(L_WORD764); // Online
        OnlineToolButton->ImageIndex = 21;
        OnlineStatusBitBtn->Font->Color = clRed;
		OnlineStatusBitBtn->Caption = FindDictionaryWord(L_WORD765); // Offline
	}
}

// ---------------------------------------------------------------------------
void __fastcall TLoadcalcForm::RemoveMenuItems(TMenuItem *ItemPtr) {
	for (int i = 0; i < ItemPtr->Count; i++) {
		TMenuItem *tmpItemPtr = ItemPtr->Items[i];
		delete tmpItemPtr;
	}
	ItemPtr->Clear();
}

void __fastcall TLoadcalcForm::LocDataStringGridDrawCell(TObject *Sender,
	int ACol, int ARow, TRect &Rect, TGridDrawState State) {
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);

	AnsiString Str = StringGrid->Cells[ACol][ARow];
	if (CurrentTable.size() >= 2 ) {
		if (State.Contains(gdFixed)) {
			// Fixed row.
			if (ACol == 0 && ARow >= 2) {
				switch (CurrentTable[ARow - 2]->Type) {
				case C_LC_TANK_CARGO:
				case C_LC_TANK_BALLAST:
				case C_LC_TANK_HFO:
				case C_LC_TANK_DO:
				case C_LC_TANK_LUB:
				case C_LC_TANK_FW:
				case C_LC_TANK_MISC:
				case C_LC_TANK_VOIDSPACE: {
						LCTankData* tmpPtr = (LCTankData*)CurrentTable[ARow - 2];
						if (tmpPtr->IsOnline && tmpPtr->IsOnlineTank()) {
							StringGrid->Canvas->Brush->Color = clGreen;
						}
						else {
							StringGrid->Canvas->Brush->Color = clBtnFace;
							// clYellow;
						}
					} break;
				default:
					StringGrid->Canvas->Brush->Color = clBtnFace;
					break;
				}
			}
			else {
				StringGrid->Canvas->Brush->Color = clBtnFace;
			}
			StringGrid->Canvas->Font->Color = clWindowText;
			StringGrid->Canvas->FillRect(Rect);
			Frame3D(StringGrid->Canvas, Rect, clBtnHighlight, clBtnShadow, 1);
		}
		else if (State.Contains(gdSelected) && UserInputMode) {
			// Selected cell.
			StringGrid->Canvas->Brush->Color = clHighlight;
			StringGrid->Canvas->Font->Color = clHighlightText;
			StringGrid->Canvas->FillRect(Rect);
		}
		else {
			// Normal.
			switch (int(StringGrid->Objects[ACol][ARow])) {
			case SVT_CARGO_TYPE_NAME: {
					LCTankData *ElementPtr = (LCTankData*)CurrentTable[ARow - 2];
					TColor CargoColor = StringGrid->Color;
					if (ElementPtr) {
						switch (ElementPtr->TankType) {
						case TANKTYPE_CARGO:
						case TANKTYPE_BALLAST:
						case TANKTYPE_HFO:
						case TANKTYPE_DO:
						case TANKTYPE_LUB:
						case TANKTYPE_FW:
						case TANKTYPE_MISC:
						case TANKTYPE_VOIDSPACE:
							CargoColor = (TColor)ElementPtr->GetCargoColor();
							break;
						default:
							break;
						}
					}
					StringGrid->Canvas->Brush->Color = CargoColor;
				} StringGrid->Canvas->Font->Color = StringGrid->Font->Color;
				StringGrid->Canvas->FillRect(Rect);
				break;
			default:
				if (!TChildForm::HighLightLines) {
					StringGrid->Canvas->Brush->Color = StringGrid->Color;
				} else if (!(ARow & 1)) {
					StringGrid->Canvas->Brush->Color = StringGrid->Color;
				}else{
					StringGrid->Canvas->Brush->Color = clWebLavender;
				}
				StringGrid->Canvas->Font->Color = StringGrid->Font->Color;
				StringGrid->Canvas->FillRect(Rect);
				break;
			}
		}
		if (!Str.IsEmpty()) {
			if (ARow == 1) {
				int Ltx = StringGrid->Canvas->TextWidth(Str);
				int Htx = StringGrid->Canvas->TextHeight(Str);
				int Xtx = Rect.Left + (((Rect.Right - Rect.Left) - Ltx) / 2);
				int Ytx = Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);
				StringGrid->Canvas->TextRect(Rect, Xtx, Ytx, Str);
			}
			else {
				if (!isalpha(Str[1]) && ARow > 1) {
					int Ltx = StringGrid->Canvas->TextWidth(Str) + 2;
					int Htx = StringGrid->Canvas->TextHeight(Str);
					int Xtx = Rect.Left + (((Rect.Right - Rect.Left) - Ltx));
					int Ytx = Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);

					StringGrid->Canvas->TextRect(Rect, Xtx, Ytx, Str);
				}
				else {
					int Htx = StringGrid->Canvas->TextHeight(Str);
					int Ytx = Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);
					StringGrid->Canvas->TextRect(Rect, Rect.Left + 2, Ytx, Str);
				}
			}
		}
		else {
			StringGrid->Canvas->TextRect(Rect, Rect.Left, Rect.Top, Str);
		}
	}

}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::OnlineOfflineClick(TObject *Sender) {
	TMenuItem* MenuItem = static_cast<TMenuItem*>(Sender);
	int Index = CurrentRow-LocDataStringGrid->FixedRows;
	if (Index >= 0) {
		PRogramObjectBase * LPtr = (PRogramObjectBase*)CurrentTable[Index];
		LibPutValue(SVT_L_ONLINE_STATUS, LPtr, AnsiString(MenuItem->Tag));

	}
}
// ---------------------------------------------------------------------------


void __fastcall TLoadcalcForm::LocDataStringGridExit(TObject *Sender) {
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
    StringGrid->Tag = 0;
	DeactivateEditTimerTimer();
}
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::MenuItemModifySolidClick(TObject *Sender) {
    int modalresult = NewSolidDlg->ShowModal();
    switch (modalresult) {
    case mrOk:
        break;
    case mrYes:
        break;
    case mrCancel:
    default:
        break;
    }

}
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::PrintPage1(void)
{
	QRCopyToTLabel(frxReportLoadCalc,"MemoShipName"     ,SVT_SHIP_NAME   ,PROProjectInfo::PROProjectInfoPtr);
	QRCopyToTLabel(frxReportLoadCalc,"MemoProject"      ,SVT_SYSTEM_ID   ,PROProjectInfo::PROProjectInfoPtr);
	QRCopyToTLabel(frxReportLoadCalc,"MemoDataRevision" ,SVT_DATA_VERSION,PROSystemData::TXUSystemData);

	AnsiString MyTab = "        ";
	AnsiString MemoStr;
	MemoStr = MyTab + MyTab + MyTab +	"L I Q U I D    W E I G H T    L O A D S\r\n";
	MemoStr += MyTab + MyTab + MyTab + "=======================================\r\n";
	MemoStr += "\r\n\r\n";
	MemoStr += "    __________________________________________________________________________\r\n";
	MemoStr += "    Code                      Vol%  Weight   LCG    TCG    VCG    Free S.Mom\r\n";
	AnsiString tmpStr;
	tmpStr.sprintf("                            %-11s%-9s%-7s%-7s%-7s%-10s",
		GetUnitName(PERCENT_UNIT), GetUnitName(WEIGHT_UNIT),
		GetUnitName(LENGTH_UNIT), GetUnitName(LENGTH_UNIT),
		GetUnitName(LENGTH_UNIT), GetUnitName(MOMENT_UNIT));
	MemoStr += tmpStr + "\r\n";
	MemoStr += "    __________________________________________________________________________\r\n";

	for (int TType = TANKTYPE_CARGO; TType <= TANKTYPE_VOIDSPACE; TType++) {
		if (LCLocationData::WeightSum[TType]) {
			MemoStr += MyTab + MyTab + FindDictionaryWord(LCLocationData::TankTypeName[TType])+"\r\n";
			for (unsigned i = 0; i < LCLocationData::Table.size(); i++) {
				LCTankData *Tnk = (LCTankData*)LCLocationData::Table[i];
				if (Tnk->TankType == TType && Tnk->Weight) {
					int Status;
					AnsiString UnitStr;
					AnsiString RStr;
					AnsiString tmpStr = "    ";
					tmpStr += LibGetValue(SVT_PRO_NAME, 0, 0,(PRogramObjectBase*)Tnk, 12, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += tmpStr;
					AnsiString NStr =LibGetValue(SVT_PRO_LONGNAME, 0, 0,(PRogramObjectBase*)Tnk, 14, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					if (!NStr.IsEmpty()) {
						if (TType == TANKTYPE_CARGO) {
							tmpStr = LibGetValue(SVT_CARGO_TYPE_NAME, 0, 0,
								(PRogramObjectBase*)Tnk, 14, SVT_FLAG_NORMAL,
								&UnitStr, &Status);
						}
						else {
							tmpStr = NStr;
						}
					}
					else {
						tmpStr.sprintf("%14s", " ");
					}
					RStr += tmpStr;

					RStr += LibGetValue(SVT_VOLPERCENT, 0, 0,
						(PRogramObjectBase*)Tnk, 6, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += LibGetValue(SVT_WEIGHT, 0, 0,
						(PRogramObjectBase*)Tnk, 9, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += LibGetValue(SVT_L_LCG, 0, 0,
						(PRogramObjectBase*)Tnk, 8, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += LibGetValue(SVT_L_TCG, 0, 0,
						(PRogramObjectBase*)Tnk, 8, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += LibGetValue(SVT_L_VCG, 0, 0,
						(PRogramObjectBase*)Tnk, 8, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += LibGetValue(SVT_L_FSM, 0, 0,
						(PRogramObjectBase*)Tnk, 10, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					MemoStr += RStr+"\r\n";
				}
			}
			MemoStr += "    __________________________________________________________________________\r\n";
			float Weight = 0.0, Vmom = 0.0, Tmom = 0.0, Lmom = 0.0;
			char Buf[BUF_SIZE];
			AnsiString tmpStr;
			float FSMoment = LCTankData::GetFSMoments(TType);

			LCLocationData::GetSolidMoments(TType, &Weight, &Lmom,
				&Tmom, &Vmom);
			if (Weight) {
					float VCGravity = Vmom / Weight;
					float TCGravity = Tmom / Weight;
					float LCGravity = Lmom / Weight;
					ConvertFromSi(Buf, Weight, 9, 1, WEIGHT_UNIT);
					tmpStr.sprintf("%32s%s", " ", Buf);
					ConvertFromSi(Buf, LCGravity, 7, 2, LENGTH_UNIT);
					tmpStr += Buf;
					ConvertFromSi(Buf, TCGravity, 7, 2, LENGTH_UNIT);
					tmpStr += Buf;
					ConvertFromSi(Buf, VCGravity, 7, 2, LENGTH_UNIT);
					tmpStr += Buf;
					ConvertFromSi(Buf, FSMoment, 10, 1, MOMENT_UNIT);
					tmpStr += Buf;
					MemoStr += tmpStr+"\r\n";
			}
		}
	}
	MemoStr += "\r\n";
	MemoStr += MyTab + MyTab + MyTab +	"S O L I D    W E I G H T    L O A D S\r\n";
	MemoStr += MyTab + MyTab + MyTab +	"=====================================\r\n";
	MemoStr += "    __________________________________________________________________________\r\n";
	MemoStr += "    Code                          Weight   LCG    TCG    VCG\r\n";
	tmpStr.sprintf("                                  %-12s%-7s%-7s%-7s",
		GetUnitName(WEIGHT_UNIT), GetUnitName(LENGTH_UNIT),
		GetUnitName(LENGTH_UNIT), GetUnitName(LENGTH_UNIT));
	MemoStr +=tmpStr+"\r\n";
	MemoStr += "    __________________________________________________________________________\r\n";
	for (unsigned i = 0; i < LCLocationData::SolidsTable.size(); i++) {
		LCLocationData *SPtr = LCLocationData::SolidsTable[i];
		if (SPtr->Weight) {
			int Status;
			AnsiString UnitStr;
			AnsiString RStr;
			AnsiString tmpStr = "    ";
			tmpStr += LibGetValue(SVT_PRO_NAME, 0, 0,
				(PRogramObjectBase*)SPtr, 12, SVT_FLAG_NORMAL, &UnitStr,
				&Status);
			RStr += tmpStr;
			AnsiString NStr = LibGetValue(SVT_PRO_LONGNAME, 0, 0,
				(PRogramObjectBase*)SPtr, 14, SVT_FLAG_NORMAL, &UnitStr,
				&Status);
			if (!NStr.IsEmpty()) {
				tmpStr = NStr;
			}
			else {
				tmpStr.sprintf("%14s", " ");
			}
			RStr += tmpStr;

			RStr += LibGetValue(SVT_WEIGHT, 0, 0, (PRogramObjectBase*)SPtr,
				6 + 9, SVT_FLAG_NORMAL, &UnitStr, &Status);
			RStr += LibGetValue(SVT_L_LCG, 0, 0, (PRogramObjectBase*)SPtr,
				7, SVT_FLAG_NORMAL, &UnitStr, &Status);
			RStr += LibGetValue(SVT_L_TCG, 0, 0, (PRogramObjectBase*)SPtr,
				7, SVT_FLAG_NORMAL, &UnitStr, &Status);
			RStr += LibGetValue(SVT_L_VCG, 0, 0, (PRogramObjectBase*)SPtr,
				7, SVT_FLAG_NORMAL, &UnitStr, &Status);
			MemoStr += RStr+"\r\n";
		}
	}
		MemoStr += "    __________________________________________________________________________\r\n";
		float Weight = 0.0, Vmom = 0.0, Tmom = 0.0, Lmom = 0.0;
		char Buf[BUF_SIZE];

		LCLocationData::GetSolidMoments(TANKTYPE_CSOLID, &Weight, &Lmom,
			&Tmom, &Vmom);
		if (Weight) {
			ConvertFromSi(Buf, Weight, 9, 1, WEIGHT_UNIT);
			tmpStr.sprintf("%20s%s", " ", Buf);
			float VCGravity = Vmom / Weight;
			float TCGravity = Tmom / Weight;
			float LCGravity = Lmom / Weight;
			ConvertFromSi(Buf, Weight, 9, 1, WEIGHT_UNIT);
			tmpStr.sprintf("%32s%s", " ", Buf);
			ConvertFromSi(Buf, LCGravity, 7, 2, LENGTH_UNIT);
			tmpStr += Buf;
			ConvertFromSi(Buf, TCGravity, 7, 2, LENGTH_UNIT);
			tmpStr += Buf;
			ConvertFromSi(Buf, VCGravity, 7, 2, LENGTH_UNIT);
			tmpStr += Buf;
			MemoStr += tmpStr+"\r\n";
		}
		int Status;
		AnsiString UnitStr;
		AnsiString RStr;
		//AnsiString tmpStr;
		MemoStr += "\r\n";
		MemoStr += MyTab + MyTab + MyTab +	"W E I G H T    R E S U L T S\r\n";
		MemoStr += "    _______________________________________________________________\r\n";
		MemoStr += "    Description              Weight    Long.     Trans.  Vertical\r\n";
		MemoStr += "                                       moment    moment  moment\r\n";

		tmpStr.sprintf("                             %-10s%-10s%-10s%-10s",
			GetUnitName(WEIGHT_UNIT), GetUnitName(MOMENT_UNIT),
			GetUnitName(MOMENT_UNIT), GetUnitName(MOMENT_UNIT));
		MemoStr += tmpStr+"\r\n";
		MemoStr += "    _______________________________________________________________\r\n";
		RStr = "    Light ship weight.. :";
		RStr += LibGetValue(SVT_LS_WEIGHT, 0, 0,
			(PRogramObjectBase*)LCShipData::LCShip, 10, SVT_FLAG_NORMAL,
			&UnitStr, &Status);
		RStr += LibGetValue(SVT_LS_L_MOM, 0, 0,
			(PRogramObjectBase*)LCShipData::LCShip, 10, SVT_FLAG_NORMAL,
			&UnitStr, &Status);
		RStr += LibGetValue(SVT_LS_T_MOM, 0, 0,
			(PRogramObjectBase*)LCShipData::LCShip, 10, SVT_FLAG_NORMAL,
			&UnitStr, &Status);
		RStr += LibGetValue(SVT_LS_V_MOM, 0, 0,
			(PRogramObjectBase*)LCShipData::LCShip, 10, SVT_FLAG_NORMAL,
			&UnitStr, &Status);
		MemoStr += RStr+"\r\n";
		RStr = "    Deadweight......... :";
		RStr += LibGetValue(SVT_S_DEADWEIGHT, 0, 0,
			(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
			&UnitStr, &Status);
		RStr += LibGetValue(SVT_S_TOTAL_L_MOM, 0, 0,
			(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
			&UnitStr, &Status);
		RStr += LibGetValue(SVT_S_TOTAL_T_MOM, 0, 0,
			(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
			&UnitStr, &Status);
		RStr += LibGetValue(SVT_S_TOTAL_V_MOM, 0, 0,
			(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
			&UnitStr, &Status);
		MemoStr += RStr+"\r\n";
	QRCopyToTLabel(frxReportLoadCalc,"MemoPage1", MemoStr);
}

void __fastcall TLoadcalcForm::frxReportLoadCalcBeforePrint(TfrxReportComponent *Sender)
{
	Sleep(10);
}
//---------------------------------------------------------------------------
void __fastcall TLoadcalcForm::PrintPage2(void)
{
	AnsiString MyTab = "        ";
	AnsiString MemoStr;
	AnsiString tmpStr;
	if (!LCShipData::Stability_Only) {
		MemoStr += MyTab + MyTab + "S T R E N G T H   R E S U L T\r\n";
		MemoStr += MyTab + MyTab + "=============================\r\n";
		MemoStr += "\r\n\r\n";
		MemoStr += "    Frame   Dist      Sf      Sf     Sf     Bm      Bm     Bm \r\n";
		MemoStr += "            to MS             Hrb%   Sea%           Hrb%   Sea%\r\n";
		MemoStr += "    __________________________________________________________________________\r\n";

		tmpStr.sprintf("            %-10s%    -8s%-7s%-7s%-8s%-7s%-7s",
			GetUnitName(LENGTH_UNIT), GetUnitName(WEIGHT_UNIT),
			GetUnitName(PERCENT_UNIT), GetUnitName(PERCENT_UNIT),
			GetUnitName(MOMENT_UNIT), GetUnitName(PERCENT_UNIT),
			GetUnitName(PERCENT_UNIT));
		MemoStr += tmpStr+"\r\n";
		MemoStr += "    __________________________________________________________________________\r\n";
		{
			for (unsigned i = 0; i < LCFrameData::FrameList.size(); i++) {
				int Status;
				AnsiString UnitStr;
				LCFrameData *FPtr = LCFrameData::FrameList[i];
				AnsiString RStr = "    ";
				RStr += LibGetValue(SVT_PRO_NAME, 0, 0,
					(PRogramObjectBase*)FPtr, 6, SVT_FLAG_NORMAL, &UnitStr,
					&Status);
				RStr += LibGetValue(SVT_F_DIST_TO_MIDSHIP, 0, 0,
					(PRogramObjectBase*)FPtr, 8, SVT_FLAG_NORMAL, &UnitStr,
					&Status);
				RStr += LibGetValue(SVT_F_SF, 0, 0, (PRogramObjectBase*)FPtr, 8,
					SVT_FLAG_NORMAL, &UnitStr, &Status);
				RStr += LibGetValue(SVT_F_SFHRBPRCNT, 0, 0,
					(PRogramObjectBase*)FPtr, 7, SVT_FLAG_NORMAL, &UnitStr,
					&Status);
				RStr += LibGetValue(SVT_F_SFSEAPRCNT, 0, 0,
					(PRogramObjectBase*)FPtr, 7, SVT_FLAG_NORMAL, &UnitStr,
					&Status);
				RStr += LibGetValue(SVT_F_CORR_BM, 0, 0,
					(PRogramObjectBase*)FPtr, 8, SVT_FLAG_NORMAL, &UnitStr,
					&Status);
				RStr += LibGetValue(SVT_F_BMHRBPRCNT, 0, 0,
					(PRogramObjectBase*)FPtr, 7, SVT_FLAG_NORMAL, &UnitStr,
					&Status);
				RStr += LibGetValue(SVT_F_BMSEAPRCNT, 0, 0,
					(PRogramObjectBase*)FPtr, 7, SVT_FLAG_NORMAL, &UnitStr,
					&Status);
				MemoStr += RStr+"\r\n";
			}
		}
		MemoStr += "\r\n\r\n";
		MemoStr += MyTab + MyTab + "M A X I M U M   V A L U E S\r\n";
		MemoStr += MyTab + MyTab + "===========================\r\n";
		MemoStr += "\r\n";
		MemoStr += "\r\n";
		{
			int Status;
			AnsiString UnitStr;
			AnsiString RStr = "    Max bending moment... :";
			RStr += LibGetValue(SVT_S_MAX_BM, 0, 0,
				(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
				&UnitStr, &Status);
			RStr += " " + UnitStr + " @ frame ";
			RStr += LibGetValue(SVT_S_MAX_BM_FRAME_NAME, 0, 0,
				(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
				&UnitStr, &Status);
			MemoStr += RStr+"\r\n";

			RStr = "    Max shear force...... :";
			RStr += LibGetValue(SVT_S_MAX_SF, 0, 0,
				(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
				&UnitStr, &Status);
			RStr += " " + UnitStr + " @ frame ";
			RStr += LibGetValue(SVT_S_MAX_SF_FRAME_NAME, 0, 0,
				(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
				&UnitStr, &Status);
			MemoStr += RStr+"\r\n";
		}
	}
	QRCopyToTLabel(frxReportLoadCalc,"MemoPage2", MemoStr);
}

//---------------------------------------------------------------------------
void __fastcall TLoadcalcForm::PrintPage3(void)
{
	AnsiString MyTab = "        ";
	AnsiString MemoStr;
	AnsiString tmpStr;
	MemoStr = MyTab + MyTab + "S T A B I L I T Y    R E S U L T S\r\n";
	MemoStr += MyTab + MyTab + "==================================\r\n";
	AnsiString RStr;
	RStr = AddValue("    Water density....................... :",
		SVT_SEAWATER_DNS, (PRogramObjectBase*)PROSystemData::TXUSystemData, 8);
	MemoStr += RStr;
	RStr = AddValue("    Draught at FP....................... :", SVT_S_DFT_F,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    Draught at midship port............. :",
		SVT_S_DFT_MS_P, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    Draught at midship starboard........ :",
		SVT_S_DFT_MS_S, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    Draught at AP....................... :", SVT_S_DFT_A,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    Trim  (Trim by stern is negative)... :", SVT_S_TRIM,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    List  (List port is negative)....... :",
		SVT_S_LIST_ANGLE, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	MemoStr += "\r\n";
	MemoStr += "\r\n";
	MemoStr += "\r\n";
	RStr = AddValue("    Immersion........................... :",
		SVT_S_IMMERSION, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    VCG solid........................... :", SVT_S_VCG_SOL,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    VCG free liquid adjustment.......... :", SVT_S_VCG_ADJ,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    VCG adjusted........................ :", SVT_S_VCG,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	MemoStr += "\r\n";
	RStr = AddValue("    KM.................................. :", SVT_S_KM,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    GM solid............................ :", SVT_S_GM_SOL,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    GM adjusted for free liquid......... :", SVT_S_GM_LIQ,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	MemoStr += "\r\n";

	if (TSNTableHydrostatic::MaxVCG_Tab) {
		RStr = AddValue("    Max VCG............................. :",
			SVT_S_MAX_VCG, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		MemoStr += RStr;
		RStr = AddValue("    VCG margin.......................... :",
			SVT_S_VCG_MARGIN, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		MemoStr += RStr;
	}
	if (TSNTableHydrostatic::DamageMaxVCG_Tab) {
		RStr = AddValue("    Damage maximum VCG.................. :",
			SVT_S_DAM_MAX_VCG, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		MemoStr += RStr;
		RStr = AddValue("    Damage VCG margin................... :",
			SVT_S_DAM_VCG_MARGIN, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		MemoStr += RStr;
	}
	MemoStr += "\r\n";
	RStr = AddValue("    Deadweight.......................... :",
		SVT_S_DEADWEIGHT, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    Displacement........................ :",
		SVT_S_DISPLACEMENT, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    Longitudinal centre of flotation.... :", SVT_S_LCF,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    Longitudinal centre of gravity...... :", SVT_S_LCG,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    Transverce centre of gravity........ :", SVT_S_TCG,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	MemoStr += "\r\n";
	RStr = AddValue("    GZ.................................. :", SVT_S_GZ,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    GZ at 30^........................... :", SVT_S_GZ_30,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    GZ max.............................. :", SVT_S_GZ_MAX,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    GZ max angle........................ :",
		SVT_S_GZ_ANGLE, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    GZ area 0~30........................ :",
		SVT_S_GZ_A0_30, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    GZ area 30~40....................... :",
		SVT_S_GZ_A30_40, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	RStr = AddValue("    GZ area 0~40........................ :",
		SVT_S_GZ_A0_40, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	MemoStr += RStr;
	if (TSNTableHydrostatic::FloodinAngle_Tab) {
		RStr = AddValue("    Flooding angle...................... :",
			SVT_S_FLOODING_ANGLE, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		MemoStr += RStr;
	}
	else if (!LCOpeningData::Table.empty()) {
		RStr = AddValue("    Reserve to downflooding............. :",
			SVT_S_REM_TO_FLOODING, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		MemoStr += RStr;
	}

	if (LCShipData::ClassificationSociety == C_LC_CLASS_DNV) {
		MemoStr += "\r\n";
		MemoStr += "    **************************************************************************\r\n";
		MemoStr += "    *    This program does not check damage stability. New loading conditons *\r\n";
		MemoStr += "    *    with oil/chemicals/gas cargo that differs significantly from those  *\r\n";
		MemoStr += "    *    in the trim and stability booklet are to be calculated separatly    *\r\n";
		MemoStr += "    *    by yard or consulant with respect to damage stability and submitted *\r\n";
		MemoStr += "    *    to the Administration for approval.                                 *\r\n";
		MemoStr += "    **************************************************************************\r\n";
	}
	MemoStr += "\r\n";
	MemoStr += "\r\n";
	MemoStr += "\r\n";
	MemoStr += "    STABILITY CURVE\r\n";
	tmpStr.sprintf("    Angle(%s)    GZ(%s)    Area(%s)\r\n",
		GetUnitName(ANGLE_UNIT).c_str(), GetUnitName(LENGTH_UNIT).c_str(),
		GetUnitName(GZ_AREA_UNIT).c_str());
	MemoStr += tmpStr;
	MemoStr += "    ==========================================\r\n";
	for (float GZAngle = 0.0; GZAngle < 10.00 / RAD_FACTOR;	GZAngle += 1.0 / RAD_FACTOR) {
		MemoStr += AddStabilityCurve(GZAngle, MyTab);
	}
	for (float GZAngle = 10.0 / RAD_FACTOR; GZAngle < 70.00 / RAD_FACTOR; GZAngle += 10.0 / RAD_FACTOR) {
		MemoStr += AddStabilityCurve(GZAngle, MyTab);
	}

	QRCopyToTLabel(frxReportLoadCalc,"MemoPage3", MemoStr);
}

//---------------------------------------------------------------------------
void __fastcall TLoadcalcForm::PrintPage4(void)
{
	//AnsiString MyTab = "\t";
	AnsiString MemoStr;
	AnsiString tmpStr;
	AnsiString MyTab = "        ";

	if (!LCStabCalc::StabCalc->IMOCriteriaList.empty()) {
		MemoStr = "\r\n";
		MemoStr += "\r\n";
		MemoStr += MyTab + "STRENGTH AND STABILITY CRITERIA ASSESSMENT\r\n";
		MemoStr += MyTab + "==========================================\r\n";
		for (unsigned i = 0;
		i < LCStabCalc::StabCalc->IMOCriteriaList.size(); i++) {
			MemoStr += "    " + LCStabCalc::StabCalc->IMOCriteriaList[i]+"\r\n";
		}
	}

	QRCopyToTLabel(frxReportLoadCalc,"MemoPage4", MemoStr);
}

AnsiString __fastcall TLoadcalcForm::AddValue(AnsiString Txt, int ValueId,PRogramObjectBase* ObjPtr, int Width) {
	int Status;
	AnsiString UnitStr;
	AnsiString RStr = Txt + LibGetValue(ValueId, 0, 0, ObjPtr, Width,		SVT_FLAG_NORMAL, &UnitStr, &Status);
	RStr += " " + UnitStr+"\r\n";
	return RStr;
}

AnsiString __fastcall TLoadcalcForm::AddStabilityCurve(float GZAngle, AnsiString MyTab) {
	char ResultBuf[BUF_SIZE];
	ConvertFromSi(ResultBuf, GZAngle, 5, 2, ANGLE_UNIT);
	AnsiString TempString = (AnsiString)MyTab + (AnsiString)ResultBuf;
	ConvertFromSi(ResultBuf, LCStabCalc::StabCalc->CalculateGZ(GZAngle), 6, 3,	LENGTH_UNIT);
	TempString += MyTab + (AnsiString)ResultBuf;
	ConvertFromSi(ResultBuf, LCStabCalc::StabCalc->GZ_Table.Area(0.0, GZAngle,	40), 5, 3, GZ_AREA_UNIT);
	TempString += MyTab + (AnsiString)ResultBuf + "\r\n";
	return TempString;
}


void __fastcall TLoadcalcForm::LocDataStringGridGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor)
{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);
	ActivateEditTimerTimer(StringGrid);
	CurrentColumn = ACol;
	CurrentRow 	  = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TLoadcalcForm::LocDataStringGridEditCellDone(TObject *Sender, int ACol, int ARow)
{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);

	AnsiString tmpStr = StringGrid->Cells[ACol][ARow];
	StringGridUserInput(StringGrid->Cells[ACol][ARow],
						CurrentTable, CurrentValueList, StringGrid,ACol,ARow);
	Calculate();

}
//---------------------------------------------------------------------------


void __fastcall TLoadcalcForm::LocDataStringGridRightClickCell(TObject *Sender, int ARow, int ACol)
{
	CurrentColumn = ACol;
	CurrentRow = ARow;
}
//---------------------------------------------------------------------------

