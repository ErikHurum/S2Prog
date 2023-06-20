#include "TSNIncludes.h"
#pragma hdrstop

#include "NewCargoTypeUnit.h"
#include "CargoTypeUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "AdvSelectors"
#pragma link "RzCommon"
#pragma link "RzBorder"
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "MemDS"
#pragma resource "*.dfm"

TNewCargoTypeSetupDlg *NewCargoTypeSetupDlg;
//---------------------------------------------------------------------------
__fastcall TNewCargoTypeSetupDlg::TNewCargoTypeSetupDlg(TComponent* AOwner)
: TForm(AOwner)
{
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::FormShow(TObject *Sender)
{
	UpdateValues();
}

//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::SetLabelList(void)
{
    EditListEntries = 0;
    LabelUnitListEntries = 0;
	ChBoxListEntries = 0;

	API->Tag         = SVT_API;
	MolWeight->Tag   = SVT_MOLMASS;
	Viscosity->Tag   = SVT_VISCOSITY;
	RefDensity1->Tag = SVT_REF_DNS1;
    RefDensity2->Tag = SVT_REF_DNS2;
    RefTemp1->Tag    = SVT_REF_TMP1;
    RefTemp2->Tag    = SVT_REF_TMP2;
    Coefficient->Tag = SVT_COEFF;
	VCF->Tag         = SVT_VCF;
    LowTemp->Tag     = SVT_LO_TEMP_LIMIT;
    HighTemp->Tag    = SVT_HI_TEMP_LIMIT;
	CargoType->Tag   = SVT_CARGO_TYPE_NAME;
    BaseCargo->Tag   = SVT_BASIC_TYPE_NAME;

	EditList[EditListEntries++] = API;
	EditList[EditListEntries++] = MolWeight;
	EditList[EditListEntries++] = Viscosity;
	EditList[EditListEntries++] = RefDensity1;
    EditList[EditListEntries++] = RefDensity2;
    EditList[EditListEntries++] = RefTemp1;
    EditList[EditListEntries++] = RefTemp2;
    EditList[EditListEntries++] = Coefficient;
    EditList[EditListEntries++] = VCF;
    EditList[EditListEntries++] = LowTemp;
    EditList[EditListEntries++] = HighTemp;
    EditList[EditListEntries++] = CargoType;
    EditList[EditListEntries++] = BaseCargo;

	APIUnit->Tag         = SVT_API;
	MolWeightUnit->Tag   = SVT_MOLMASS;
	ViscosityUnit->Tag   = SVT_VISCOSITY;
	RefDensity1Unit->Tag = SVT_REF_DNS1;
    RefDensity2Unit->Tag = SVT_REF_DNS2;
    RefTemp1Unit->Tag    = SVT_REF_TMP1;
    RefTemp2Unit->Tag    = SVT_REF_TMP2;
    CoefficientUnit->Tag = SVT_COEFF;
    VCFUnit->Tag         = SVT_VCF;
	LowTempUnit->Tag     = SVT_LO_TEMP_LIMIT;
    HighTempUnit->Tag    = SVT_HI_TEMP_LIMIT;

	LabelUnitList[LabelUnitListEntries++] = APIUnit;
	LabelUnitList[LabelUnitListEntries++] = MolWeightUnit;
	LabelUnitList[LabelUnitListEntries++] = ViscosityUnit;
	LabelUnitList[LabelUnitListEntries++] = RefDensity1Unit;
    LabelUnitList[LabelUnitListEntries++] = RefDensity2Unit;
    LabelUnitList[LabelUnitListEntries++] = RefTemp1Unit;
    LabelUnitList[LabelUnitListEntries++] = RefTemp2Unit;
    LabelUnitList[LabelUnitListEntries++] = CoefficientUnit;
    LabelUnitList[LabelUnitListEntries++] = VCFUnit;
    LabelUnitList[LabelUnitListEntries++] = LowTempUnit;
    LabelUnitList[LabelUnitListEntries++] = HighTempUnit;

    LowTempCheckBox->Tag   = SVT_LO_TEMP_ENABLE;
	HighTempCheckBox->Tag  = SVT_HI_TEMP_ENABLE;
    ChBoxList[ChBoxListEntries++] = LowTempCheckBox;
    ChBoxList[ChBoxListEntries++] = HighTempCheckBox;

}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::FindBaseCargoTypes(void)
{
	SelectBaseCTListBox->Items->Clear();
	for ( int index=0; index < SizeofBasicCargoNameList; index++ ) {
		SelectBaseCTListBox->Items->Add(FindDictionaryWord(BasicCargoNameList[index].Name));
	}
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::UpdateValues(void)
{
    if ( CurrentCargoType ) {
        for ( int k=0; k<EditListEntries; k++ ) {
            AnsiString TempValue, UnitStr;
			TempValue = LibGetValue(EditList[k]->Tag, CurrentCargoType,&UnitStr);
			EditList[k]->Text = TempValue;
			if ( k<LabelUnitListEntries && LabelUnitList[k] ) {
				LabelUnitList[k]->Caption = UnitStr;
			}
        }
        for ( int k=0; k<ChBoxListEntries; k++ ) {
			String TempValue = LibGetValue(ChBoxList[k]->Tag,CurrentCargoType);
            if ( TempValue == "0" ) {
				ChBoxList[k]->Checked = false;
			} else {
                ChBoxList[k]->Checked = true;
            }
		}
		switch(CurrentCargoType->BaseCargoType) {
			case CTY_API_53E  :
			case CTY_API_54E  :
			case CTY_API_59E  :
			case CTY_API_60E  :
				MolWeightLabel->Visible = true;
				MolWeight->Visible 		= true;
				MolWeightUnit->Visible 	= true;
				break;
			default:
				MolWeightLabel->Visible = false;
				MolWeight->Visible 		= false;
				MolWeightUnit->Visible 	= false;
				break;
		}
		CargoShape->Brush->Color = (TColor) CurrentCargoType->Colour;
		if (OriginalCargoName != CurrentCargoType->Name ) {
			SaveNewButton->Enabled = true;
		}else{
			SaveNewButton->Enabled = false;
		}

	}
}
//--------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::SelectBaseCTListBoxClick(TObject *Sender)
{
    TListBox *pTL = dynamic_cast<TListBox *>(Sender);
    if ( pTL && pTL->ItemIndex>=0 ) {
        LibPutValue(SVT_BASIC_TYPE, CurrentCargoType, BasicCargoNameList[pTL->ItemIndex].Value);
    }
    BaseTypeGroupBox->Visible = false;
	UpdateValues();
	EnableDisableEdit();
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::ChooseCTButtonClick(TObject *Sender)
{
    if ( BaseTypeGroupBox->Visible == true ) {
        BaseTypeGroupBox->Visible = false;
    } else {
        BaseTypeGroupBox->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::EditExit(TObject *Sender)
{
    TEdit *EditPtr = (TEdit *)Sender;
	if ( EditPtr->ReadOnly ) {
	} else {
        String UserInput = EditPtr->Text;
		LibPutValue(EditPtr->Tag, CurrentCargoType, UserInput);
        UpdateValues();
    }
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::EditKeyPress(TObject *Sender,
                                                 char &Key)
{
    TEdit *EditPtr = (TEdit *)Sender;
	String UserInput = EditPtr->Text;
    switch ( Key ) {
    case VK_ESCAPE:
        break;
	case VK_RETURN:
        LibPutValue(EditPtr->Tag, CurrentCargoType, UserInput);
        UpdateValues();
        break;
    default:
		break;
	}
}
//---------------------------------------------------------------------------


void __fastcall TNewCargoTypeSetupDlg::FormClose(TObject *Sender,
											  TCloseAction &Action)
{
	WriteRegistry();
	RzCustomColors1->Colors = CargoColorDialog->CustomColors;
	RzPropertyStore1->Save();
	//RzRegIniFile1->UpdateIniFile();
	//delete CurrentCargoType;

	CurrentCargoType  = NULL;
	//NewCargoTypeSetup = NULL;
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::ChBoxClick(TObject *Sender)
{
    TCheckBox *ChBoxPtr = (TCheckBox *)Sender;
    char *temp;
    if ( ChBoxPtr->Checked ) {
        temp = "1";
    } else {
        temp = "0";
    }
	LibPutValue(ChBoxPtr->Tag,CurrentCargoType,temp);
}
//---------------------------------------------------------------------------


void __fastcall TNewCargoTypeSetupDlg::SaveNewButtonClick(TObject *Sender)
{
//	LibPutValue(SVT_IS_DEFINED, CurrentCargoType, "1");
	//CurrentCargoType->AddToDatabase();

	//UpdateValues();
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::SaveButtonClick(TObject *Sender)
{
//	LibPutValue(SVT_IS_DEFINED, CurrentCargoType,"1");
	//CurrentCargoType->UpdateDatabase();
	//  UpdateValues();
}
//---------------------------------------------------------------------------




void __fastcall TNewCargoTypeSetupDlg::CancelButtonClick(TObject *Sender)
{
	//LibPutValue(SVT_IS_DEFINED, CurrentCargoType, "0");
	//LibPutValue(SVT_CARGO_TYPE_NAME, CurrentCargoType,OrgCargoName);
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::EnableDisableEdit(void)
{
    switch(CurrentCargoType->BaseCargoType){
    case CTY_LINEAR:
        API->Enabled         = false;
        RefDensity1->Enabled = true;
        RefDensity2->Enabled = true;
        RefTemp1->Enabled    = true;
        RefTemp2->Enabled    = true;
        Coefficient->Enabled = true;
        VCF->Enabled         = false;
        break;
    case CTY_SIMPLE_LIN:
    case CTY_BALLAST:
    case CTY_SEA:
    case CTY_FW:
    case CTY_HFO:
    case CTY_DO:
	case CTY_LUB:
        API->Enabled         = false;
		RefDensity1->Enabled = true;
        RefDensity2->Enabled = false;
        RefTemp1->Enabled    = false;
        RefTemp2->Enabled    = false;
        Coefficient->Enabled = false;
        VCF->Enabled         = false;
        break;
    case CTY_API_6A :
    case CTY_API_6B :
    case CTY_API_6D :
        API->Enabled         = true;
        RefDensity1->Enabled = false;
        RefDensity2->Enabled = false;
        RefTemp1->Enabled    = false;
        RefTemp2->Enabled    = false;
        Coefficient->Enabled = false;
        VCF->Enabled         = false;
        break;
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_53E:
        API->Enabled         = false;
        RefDensity1->Enabled = false;
        RefDensity2->Enabled = true;
        RefTemp1->Enabled    = false;
        RefTemp2->Enabled    = true;
        Coefficient->Enabled = false;
        VCF->Enabled         = false;
        break;
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_54E:
        API->Enabled         = false;
        RefDensity1->Enabled = true;
        RefDensity2->Enabled = false;
        RefTemp1->Enabled    = false;
        RefTemp2->Enabled    = false;
        Coefficient->Enabled = false;
		VCF->Enabled         = false;
        break;
	case CTY_API_59A:
    case CTY_API_59B:
    case CTY_API_59D:
    case CTY_API_59E:
        API->Enabled         = false;
        RefDensity1->Enabled = false;
        RefDensity2->Enabled = true;
        RefTemp1->Enabled    = false;
        RefTemp2->Enabled    = true;
        Coefficient->Enabled = false;
        VCF->Enabled         = false;
        break;
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
    case CTY_API_60E:
        API->Enabled         = false;
        RefDensity1->Enabled = true;
        RefDensity2->Enabled = false;
        RefTemp1->Enabled    = false;
        RefTemp2->Enabled    = false;
        Coefficient->Enabled = false;
        VCF->Enabled         = false;
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::FormCreate(TObject *Sender)
{
	CurrentCargoType  = CargoTypeSetupForm->GetCargoTypePtr();
	OriginalCargoName = CurrentCargoType->Name;

	AnsiString TempValue, UnitStr;
	//OrgCargoName = LibGetValue(SVT_CARGO_TYPE_NAME, CurrentCargoType,&UnitStr);
	//LibPutValue(SVT_CARGO_TYPE_NAME, CurrentCargoType, "");
	//CurrentCargoType->Name = "";
	SetLabelList();
	FindBaseCargoTypes();
	EnableDisableEdit();
	//CargoColorDialog->CustomColors->Add("ColorA=808022");
	//CargoColorDialog->CustomColors->Add("ColorI=408090");
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\";
	ReadRegistry();
	//RzCustomColors1->RegIniFile->ReadSections();
	RzPropertyStore1->Load();

	CargoColorDialog->CustomColors = RzCustomColors1->Colors;
 }
//---------------------------------------------------------------------------

void __fastcall TNewCargoTypeSetupDlg::ReadRegistry(void) {
	TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_READ;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, false);
		if (Status) {
			if (Registry->ValueExists("CargoColor1")) {
				CargoColorDialog->CustomColors->Add(Registry->ReadString("CargoColor1"));
			}
			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}

}
//---------------------------------------------------------------------------
void __fastcall TNewCargoTypeSetupDlg::WriteRegistry(void) {
	TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_WRITE;

		// True because we want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, true);
		if (Status) {
			AnsiString tmpStr = CargoColorDialog->CustomColors->Strings[0];
		   //	Registry->WriteString("CargoColor"+i, tmpStr.c_str());
			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}
}

CTOUser* __fastcall TNewCargoTypeSetupDlg::GetCargoTypePtr(void){
	return CurrentCargoType;
}

void __fastcall TNewCargoTypeSetupDlg::SetCargoTypePtr(CTOUser* CargoInfoPtr)
{
	 CurrentCargoType = CargoInfoPtr;
}

void __fastcall TNewCargoTypeSetupDlg::CargoShapeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if ( CargoColorDialog->Execute() ) {
		CurrentCargoType->Colour = CargoColorDialog->Color;
		CargoShape->Brush->Color = (TColor) CargoColorDialog->Color;
		String tempVal = CurrentCargoType->Colour;
		LibPutValue(SVT_COLOUR, CurrentCargoType, tempVal);
/*      if(ShipTankPlan){
	  ShipTankPlan->TPPaintBox->Repaint();
		}    */
	}
}
//---------------------------------------------------------------------------

