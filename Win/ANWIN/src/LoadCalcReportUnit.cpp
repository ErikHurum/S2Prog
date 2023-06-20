// ---------------------------------------------------------------------------
#include "ANWinInc.h"
#pragma hdrstop
#include "ConstantsANWIN.h"
USEFORM("src\StdAboutBoxForm.cpp", StdAboutBox);
#include <Registry.hpp>
// #include "StdAboutBoxForm.h"
#include "LoadCalcUnit.h"

#include "LoadCalcReportUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoadCalcReportForm *LoadCalcReportForm;

// ---------------------------------------------------------------------------
__fastcall TLoadCalcReportForm::TLoadCalcReportForm(TComponent* Owner)
	: TForm(Owner) {
	/*
	ShipLabel1->Caption = (String)"Ship: " + PROProjectInfo::PROProjectInfoPtr->Name;
	ShipLabel2->Caption = ShipLabel1->Caption;
	ShipLabel3->Caption = ShipLabel1->Caption;
	ShipLabel4->Caption = ShipLabel1->Caption; {

		TLoadcalcForm *WinPtr = (TLoadcalcForm*)Application->FindComponent
			("LoadcalcForm");
		if (WinPtr) {
			ConditionNameLabel1->Caption = WinPtr->ConditionFileName;
		}
		else {
			ConditionNameLabel1->Caption = "Error, no loadcalc window!";
		}
	}

	ConditionNameLabel2->Caption = ConditionNameLabel1->Caption;
	ConditionNameLabel3->Caption = ConditionNameLabel1->Caption;
	ConditionNameLabel4->Caption = ConditionNameLabel1->Caption;

	{
		struct TransArray {
			WORD LanguageID, CharacterSet;
		};

		DWORD VerInfo, VerSize;
		HANDLE MemHandle;
		LPVOID MemPtr, BufferPtr;
		UINT BufferLength;
		TransArray *Array;
		char QueryBlock[40];

		// Get the product name and version from the
		// applications version information.
		AnsiString Path(Application->ExeName);
		VerSize = GetFileVersionInfoSize(Path.c_str(), &VerInfo);
		if (VerSize > 0) {
			MemHandle = GlobalAlloc(GMEM_MOVEABLE, VerSize);
			MemPtr = GlobalLock(MemHandle);
			GetFileVersionInfo(Path.c_str(), VerInfo, VerSize,
				MemPtr);
			VerQueryValue(MemPtr, "\\VarFileInfo\\Translation",
				&BufferPtr, &BufferLength);
			Array = (TransArray*)BufferPtr;

			// Get the product name.
			wsprintf(QueryBlock,
				"\\StringFileInfo\\%04x%04x\\ProductName",
				Array[0].LanguageID, Array[0].CharacterSet);
			VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
			// Set the product name caption.

			AnsiString ProductName = (char *)BufferPtr;
			/*
			 // Get the product version.
			 wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\ProductVersion",
			 Array[0].LanguageID, Array[0].CharacterSet);
			 VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
			 // Set the version caption.
			 Version->Caption = (char *)BufferPtr;
			 */
			// Get the product copyright.
			wsprintf(QueryBlock,
				"\\StringFileInfo\\%04x%04x\\LegalCopyright",
				Array[0].LanguageID, Array[0].CharacterSet);
			VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
			// Set the copyright caption.
			AnsiString Copyright = (char *)BufferPtr;

			// Get the product FileVersion.
			wsprintf(QueryBlock,
				"\\StringFileInfo\\%04x%04x\\FileVersion",
				Array[0].LanguageID, Array[0].CharacterSet);
			VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
			// Set the version caption.
			AnsiString FileVersion = (char *)BufferPtr;

			// Get the product Date.
			wsprintf(QueryBlock,
				"\\StringFileInfo\\%04x%04x\\Comments",
				Array[0].LanguageID, Array[0].CharacterSet);
			VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
			// Set the Date caption.
			AnsiString Date = (char *)BufferPtr;
			ProdLabel1->Caption = ProductName + "  " + FileVersion;

			GlobalUnlock(MemPtr);
			GlobalFree(MemHandle);
		}
		else {
			ProdLabel1->Caption = "No version info";
		}
	}
	*/
}
// ---------------------------------------------------------------------------

void __fastcall TLoadCalcReportForm::PrintPage1(void) {
/*
	AnsiString MyTab = "        ";

	QRMemo1->Lines->Clear();
	QRMemo1->Lines->Add(MyTab + MyTab + MyTab +
		"L I Q U I D    W E I G H T    L O A D S");
	QRMemo1->Lines->Add(MyTab + MyTab + MyTab +
		"=======================================");
	QRMemo1->Lines->Add("");
	QRMemo1->Lines->Add("");
	QRMemo1->Lines->Add
		("    __________________________________________________________________________"
		);
	QRMemo1->Lines->Add
		("    Code                    Vol%  Weight   LCG    TCG    VCG    Free S.Mom"
		);
	AnsiString tmpStr;
	tmpStr.sprintf("                            %-6s%-9s%-7s%-7s%-7s%-10s",
		GetUnitName(PERCENT_UNIT), GetUnitName(WEIGHT_UNIT),
		GetUnitName(LENGTH_UNIT), GetUnitName(LENGTH_UNIT),
		GetUnitName(LENGTH_UNIT), GetUnitName(MOMENT_UNIT));
	QRMemo1->Lines->Add(tmpStr);

	QRMemo1->Lines->Add
		("    __________________________________________________________________________"
		);
	for (int TType = TANKTYPE_CARGO; TType <= TANKTYPE_VOIDSPACE; TType++) {
		if (LCLocationData::WeightSum[TType]) {
			QRMemo1->Lines->Add(MyTab + MyTab + FindDictionaryWord
				(LCLocationData::TankTypeName[TType]));
			for (unsigned i = 0; i < LCLocationData::Table.size(); i++) {
				LCTankData *Tnk = (LCTankData*)LCLocationData::Table[i];
				if (Tnk->TankType == TType && Tnk->Weight) {
					int Status;
					AnsiString UnitStr;
					AnsiString RStr;
					AnsiString tmpStr = "    ";
					tmpStr += LibGetValue(SVT_PRO_NAME, 0, 0,
						(PRogramObjectBase*)Tnk, 8, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += tmpStr;
					AnsiString NStr =
						LibGetValue(SVT_PRO_LONGNAME, 0, 0,
						(PRogramObjectBase*)Tnk, 14, SVT_FLAG_NORMAL, &UnitStr,
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
						(PRogramObjectBase*)Tnk, 7, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += LibGetValue(SVT_L_TCG, 0, 0,
						(PRogramObjectBase*)Tnk, 7, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += LibGetValue(SVT_L_VCG, 0, 0,
						(PRogramObjectBase*)Tnk, 7, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					RStr += LibGetValue(SVT_L_FSM, 0, 0,
						(PRogramObjectBase*)Tnk, 10, SVT_FLAG_NORMAL, &UnitStr,
						&Status);
					QRMemo1->Lines->Add(RStr);
				}
			}
			QRMemo1->Lines->Add
				("    __________________________________________________________________________"
				); {
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
					QRMemo1->Lines->Add(tmpStr);
				}
			}
		}
	}

	QRMemo1->Lines->Add("");
	QRMemo1->Lines->Add(MyTab + MyTab + MyTab +
		"S O L I D    W E I G H T    L O A D S");
	QRMemo1->Lines->Add(MyTab + MyTab + MyTab +
		"=====================================");
	QRMemo1->Lines->Add
		("    __________________________________________________________________________"
		);
	QRMemo1->Lines->Add
		("    Code                          Weight   LCG    TCG    VCG");
	tmpStr.sprintf("                                  %-9s%-7s%-7s%-7s",
		GetUnitName(WEIGHT_UNIT), GetUnitName(LENGTH_UNIT),
		GetUnitName(LENGTH_UNIT), GetUnitName(LENGTH_UNIT));
	QRMemo1->Lines->Add(tmpStr);
	QRMemo1->Lines->Add
		("    __________________________________________________________________________"
		); {
		for (unsigned i = 0; i < LCLocationData::SolidsTable.size(); i++) {
			LCLocationData *SPtr = LCLocationData::SolidsTable[i];
			if (SPtr->Weight) {
				int Status;
				AnsiString UnitStr;
				AnsiString RStr;
				AnsiString tmpStr = "    ";
				tmpStr += LibGetValue(SVT_PRO_NAME, 0, 0,
					(PRogramObjectBase*)SPtr, 8, SVT_FLAG_NORMAL, &UnitStr,
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
				QRMemo1->Lines->Add(RStr);
			}
		}
		QRMemo1->Lines->Add
			("    __________________________________________________________________________"
			); {
			float Weight = 0.0, Vmom = 0.0, Tmom = 0.0, Lmom = 0.0;
			char Buf[BUF_SIZE];
			AnsiString tmpStr;

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
				QRMemo1->Lines->Add(tmpStr);
			}
		}
	} {
		int Status;
		AnsiString UnitStr;
		AnsiString RStr;
		AnsiString tmpStr;
		QRMemo1->Lines->Add("");
		QRMemo1->Lines->Add(MyTab + MyTab + MyTab +
			"W E I G H T    R E S U L T S");
		QRMemo1->Lines->Add
			("    _______________________________________________________________"
			);
		QRMemo1->Lines->Add
			("    Description              Weight    Long.     Trans.  Vertical"
			);
		QRMemo1->Lines->Add
			("                                       moment    moment  moment");

		tmpStr.sprintf("                             %-10s%-10s%-10s%-10s",
			GetUnitName(WEIGHT_UNIT), GetUnitName(MOMENT_UNIT),
			GetUnitName(MOMENT_UNIT), GetUnitName(MOMENT_UNIT));
		QRMemo1->Lines->Add(tmpStr);
		QRMemo1->Lines->Add
			("    _______________________________________________________________"
			);
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
		QRMemo1->Lines->Add(RStr);
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
		QRMemo1->Lines->Add(RStr);
	}
	*/
}

void __fastcall TLoadCalcReportForm::PrintPage2(void) {
/*
	AnsiString tmpStr;
	AnsiString MyTab = "        ";
	// QRMemo1->Lines->Clear();
	if (!LCShipData::Stability_Only) {
		QRMemo2->Lines->Add(MyTab + MyTab + "S T R E N G T H   R E S U L T");
		QRMemo2->Lines->Add(MyTab + MyTab + "=============================");
		QRMemo2->Lines->Add(MyTab);
		QRMemo2->Lines->Add(MyTab);
		QRMemo2->Lines->Add
			("    Frame   Dist      Sf      Sf     Sf     Bm      Bm     Bm ");
		QRMemo2->Lines->Add
			("            to MS             Hrb%   Sea%           Hrb%   Sea%");
		QRMemo2->Lines->Add
			("    __________________________________________________________________________"
			);

		tmpStr.sprintf("            %-10s%    -8s%-7s%-7s%-8s%-7s%-7s",
			GetUnitName(LENGTH_UNIT), GetUnitName(WEIGHT_UNIT),
			GetUnitName(PERCENT_UNIT), GetUnitName(PERCENT_UNIT),
			GetUnitName(MOMENT_UNIT), GetUnitName(PERCENT_UNIT),
			GetUnitName(PERCENT_UNIT));
		QRMemo2->Lines->Add(tmpStr);
		QRMemo2->Lines->Add
			("    __________________________________________________________________________"
			); {
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
				QRMemo2->Lines->Add(RStr);
			}
		} QRMemo2->Lines->Add("");
		QRMemo2->Lines->Add("");
		QRMemo2->Lines->Add(MyTab + MyTab + "M A X I M U M   V A L U E S");
		QRMemo2->Lines->Add(MyTab + MyTab + "===========================");
		QRMemo2->Lines->Add("");
		QRMemo2->Lines->Add(""); {
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
			QRMemo2->Lines->Add(RStr);

			RStr = "    Max shear force...... :";
			RStr += LibGetValue(SVT_S_MAX_SF, 0, 0,
				(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
				&UnitStr, &Status);
			RStr += " " + UnitStr + " @ frame ";
			RStr += LibGetValue(SVT_S_MAX_SF_FRAME_NAME, 0, 0,
				(PRogramObjectBase*)LCStabCalc::StabCalc, 10, SVT_FLAG_NORMAL,
				&UnitStr, &Status);
			QRMemo2->Lines->Add(RStr);
		}
	}
	*/
}

void __fastcall TLoadCalcReportForm::PrintPage3(void) {
/*
	// QRMemo1->Lines->Clear();
	AnsiString tmpStr;
	AnsiString MyTab = "        ";
	QRMemo3->Lines->Add(MyTab + MyTab + "S T A B I L I T Y    R E S U L T S");
	QRMemo3->Lines->Add(MyTab + MyTab + "==================================");
	AnsiString RStr;
	RStr = AddValue("    Water density....................... :",
		SVT_SEAWATER_DNS, (PRogramObjectBase*)PROSystemData::TXUSystemData, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Draught at FP....................... :", SVT_S_DFT_F,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Draught at midship port............. :",
		SVT_S_DFT_MS_P, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Draught at midship starboard........ :",
		SVT_S_DFT_MS_S, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Draught at AP....................... :", SVT_S_DFT_A,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Trim  (Trim by stern is negative)... :", SVT_S_TRIM,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    List  (List port is negative)....... :",
		SVT_S_LIST_ANGLE, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	QRMemo3->Lines->Add("");
	QRMemo3->Lines->Add("");
	QRMemo3->Lines->Add("");
	RStr = AddValue("    Immersion........................... :",
		SVT_S_IMMERSION, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    VCG solid........................... :", SVT_S_VCG_SOL,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    VCG free liquid adjustment.......... :", SVT_S_VCG_ADJ,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    VCG adjusted........................ :", SVT_S_VCG,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	QRMemo3->Lines->Add("");
	RStr = AddValue("    KM.................................. :", SVT_S_KM,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    GM solid............................ :", SVT_S_GM_SOL,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    GM adjusted for free liquid......... :", SVT_S_GM_LIQ,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	QRMemo3->Lines->Add("");

	if (TSNTableHydrostatic::MaxVCG_Tab) {
		RStr = AddValue("    Max VCG............................. :",
			SVT_S_MAX_VCG, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		QRMemo3->Lines->Add(RStr);
		RStr = AddValue("    VCG margin.......................... :",
			SVT_S_VCG_MARGIN, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		QRMemo3->Lines->Add(RStr);
	}
	if (TSNTableHydrostatic::DamageMaxVCG_Tab) {
		RStr = AddValue("    Damage maximum VCG.................. :",
			SVT_S_DAM_MAX_VCG, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		QRMemo3->Lines->Add(RStr);
		RStr = AddValue("    Damage VCG margin................... :",
			SVT_S_DAM_VCG_MARGIN, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		QRMemo3->Lines->Add(RStr);
	}
	QRMemo3->Lines->Add("");
	RStr = AddValue("    Deadweight.......................... :",
		SVT_S_DEADWEIGHT, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Displacement........................ :",
		SVT_S_DISPLACEMENT, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Longitudinal centre of flotation.... :", SVT_S_LCF,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Longitudinal centre of gravity...... :", SVT_S_LCG,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    Transverce centre of gravity........ :", SVT_S_TCG,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	QRMemo3->Lines->Add("");
	RStr = AddValue("    GZ.................................. :", SVT_S_GZ,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    GZ at 30^........................... :", SVT_S_GZ_30,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    GZ max.............................. :", SVT_S_GZ_MAX,
		(PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    GZ max angle........................ :",
		SVT_S_GZ_ANGLE, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    GZ area 0~30........................ :",
		SVT_S_GZ_A0_30, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    GZ area 30~40....................... :",
		SVT_S_GZ_A30_40, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	RStr = AddValue("    GZ area 0~40........................ :",
		SVT_S_GZ_A0_40, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
	QRMemo3->Lines->Add(RStr);
	if (TSNTableHydrostatic::FloodinAngle_Tab) {
		RStr = AddValue("    Flooding angle...................... :",
			SVT_S_FLOODING_ANGLE, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		QRMemo3->Lines->Add(RStr);
	}
	else if (!LCOpeningData::Table.empty()) {
		RStr = AddValue("    Reserve to downflooding............. :",
			SVT_S_REM_TO_FLOODING, (PRogramObjectBase*)LCStabCalc::StabCalc, 8);
		QRMemo3->Lines->Add(RStr);
	}

	if (LCShipData::ClassificationSociety == C_LC_CLASS_DNV) {
		QRMemo3->Lines->Add("");
		QRMemo3->Lines->Add
			("    **************************************************************************"
			);
		QRMemo3->Lines->Add
			("    *    This program does not check damage stability. New loading conditons *"
			);
		QRMemo3->Lines->Add
			("    *    with oil/chemicals/gas cargo that differs significantly from those  *"
			);
		QRMemo3->Lines->Add
			("    *    in the trim and stability booklet are to be calculated separatly    *"
			);
		QRMemo3->Lines->Add
			("    *    by yard or consulant with respect to damage stability and submitted *"
			);
		QRMemo3->Lines->Add
			("    *    to the Administration for approval.                                 *"
			);
		QRMemo3->Lines->Add
			("    **************************************************************************"
			);
	}
	QRMemo3->Lines->Add("");
	QRMemo3->Lines->Add("");
	QRMemo3->Lines->Add("");
	QRMemo3->Lines->Add("    STABILITY CURVE");
	tmpStr.sprintf("    Angle(%s)    GZ(%s)    Area(%s)",
		GetUnitName(ANGLE_UNIT).c_str(), GetUnitName(LENGTH_UNIT).c_str(),
		GetUnitName(GZ_AREA_UNIT).c_str());
	QRMemo3->Lines->Add(tmpStr);
	QRMemo3->Lines->Add("    ==========================================");
	for (float GZAngle = 0.0; GZAngle < 10.00 / RAD_FACTOR;
	GZAngle += 1.0 / RAD_FACTOR) {
		AddStabilityCurve(QRMemo3, GZAngle, MyTab);
	}
	for (float GZAngle = 10.0 / RAD_FACTOR; GZAngle < 70.00 / RAD_FACTOR;
	GZAngle += 10.0 / RAD_FACTOR) {
		AddStabilityCurve(QRMemo3, GZAngle, MyTab);
	}
	QRMemo3->Lines->Add("");
	*/
}

void __fastcall TLoadCalcReportForm::PrintPage4(void) {
/*
	// QRMemo1->Lines->Clear();
	AnsiString tmpStr;
	AnsiString MyTab = "        ";

	if (!LCStabCalc::StabCalc->IMOCriteriaList.empty()) {
		QRMemo4->Lines->Add("");
		QRMemo4->Lines->Add("");
		QRMemo4->Lines->Add
			(MyTab + "STRENGTH AND STABILITY CRITERIA ASSESSMENT");
		QRMemo4->Lines->Add
			(MyTab + "==========================================");
		for (unsigned i = 0;
		i < LCStabCalc::StabCalc->IMOCriteriaList.size(); i++) {
			QRMemo4->Lines->Add
				("    " + LCStabCalc::StabCalc->IMOCriteriaList[i]);
		}
	}
  */
}

AnsiString __fastcall TLoadCalcReportForm::AddValue(AnsiString Txt, int ValueId,
	PRogramObjectBase* ObjPtr, int Width) {
	int Status;
	AnsiString UnitStr;
	AnsiString RStr = Txt + LibGetValue(ValueId, 0, 0, ObjPtr, Width,
		SVT_FLAG_NORMAL, &UnitStr, &Status);
	RStr += " " + UnitStr;
	return RStr;
}
/*
void __fastcall TLoadCalcReportForm::AddStabilityCurve(TQRMemo *QRMemo,
	float GZAngle, AnsiString MyTab) {
	char ResultBuf[BUF_SIZE];
	ConvertFromSi(ResultBuf, GZAngle, 5, 2, ANGLE_UNIT);
	AnsiString TempString = (AnsiString)MyTab + (AnsiString)ResultBuf;
	ConvertFromSi(ResultBuf, LCStabCalc::StabCalc->CalculateGZ(GZAngle), 6, 3,
		LENGTH_UNIT);
	TempString += MyTab + (AnsiString)ResultBuf;
	ConvertFromSi(ResultBuf, LCStabCalc::StabCalc->GZ_Table.Area(0.0, GZAngle,
		40), 5, 3, GZ_AREA_UNIT);
	TempString += MyTab + (AnsiString)ResultBuf;
	//QRMemo->Lines->Add(TempString);
}
*/
void __fastcall TLoadCalcReportForm::QRCompositeReport1AddReports
	(TObject *Sender) {
	/*
	QRCompositeReport1->Reports->Clear();
	QRCompositeReport1->Reports->Add(QRPQuickrep1);
	QRCompositeReport1->Reports->Add(QRPQuickrep2);
	QRCompositeReport1->Reports->Add(QRPQuickrep3);
	QRCompositeReport1->Reports->Add(QRPQuickrep4);
	*/

}
// ---------------------------------------------------------------------------
