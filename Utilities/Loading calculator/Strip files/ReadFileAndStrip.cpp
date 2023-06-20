//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <fstream.h>



#include "ReadFileAndStrip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReadFileFormat *ReadFileFormat;
//---------------------------------------------------------------------------
__fastcall TReadFileFormat::TReadFileFormat(TComponent* Owner)
: TForm(Owner)
{
	Initialize();
}
//---------------------------------------------------------------------------

void __fastcall TReadFileFormat::ReadFileButtonClick(TObject *Sender)
{
	if ( LoadDialog->Execute() ) {
		ProgressBar1->Visible = true;
		ProgressBar1->Max = MAX_LINES;
		TankNameEdit->Visible = true;
		String FileName = LoadDialog->FileName;
		ZerosetTables();
		NumberOfInColumn = ColoumnsEdit->Text.ToInt();
		CheckInValueTypes();
		ReadFromFile(FileName.c_str());
		ProgressBar1->Visible = false;
		TankNameEdit->Visible = false;
	}
}
//---------------------------------------------------------------------------

void TReadFileFormat::ReadFromFile(wchar_t *fileName)
{
	FileLineList->Clear();
	ifstream ReadInFile(fileName);
	if ( ReadInFile ) {
		bool ReadError = false;
		char buf[50];
		int TankIndex=0;
		ReadInFile.seekg(0);
		// clear the state flags
		ReadInFile.clear();
		// output each word
		while ( ReadInFile >> buf ) {
			if ( !ReadError ) {
				int Key = FindKey(buf);
				switch ( Key ) {
				default:
					break;
				case DENSITY:
					ReadInFile >> Density[TankIndex];
					break;
				case ONLINE     :
					IsOnline[TankIndex] = true;
					break;
				case FRAME      :
                	{
						char FFrame[BUF_SIZE];
						char LFrame[BUF_SIZE];
						ReadInFile >> FFrame;
						ReadInFile >> LFrame;
						FirstFrame[TankIndex] = FFrame;
						LastFrame[TankIndex]  = LFrame;
					}
					break;
				case HEAVY_FUEL :
				case DIESEL     :
				case LUBRICANT  :
				case FRESHWATER :
				case MISC       :
				case BALLAST    :
				case CARGO      :
					TType[TankIndex] =  Key;
					break;
				case TANK_NAME:
					{
						ReadInFile >> buf;
						AnsiString Name = (String)buf;
						TankName[TankIndex] = Name;
						TankComboBox->Items->Add(Name);
						ProgressBar1->Position = 0;
						TankNameEdit->Text = TankName[TankIndex];
						int Column=0;
						int Row=0;
						ReadInFile >> buf;
						while ( !ReadError && (Column<NumberOfInColumn)&&( FindKey(buf)!= END )  ) {
							String tempValue = buf;
							float tempFloat;
							try {
								tempFloat = tempValue.ToDouble();
							} catch ( const exception& e ) {
								ReadError = true;
								// cout << "Got an exception: " << e.what() << endl;
							}
							if ( !ReadError ) {
								*((InValuesListPtr[Column])+(TankIndex*MAX_LINES)+Row) = tempFloat;
								if ( ReadInFile >> buf ) {
								} else {
									ReadError = true;
								}
							}
							if ( Column>=(NumberOfInColumn-1) ) {
								if ( !TrimCheckBox->Checked || ValuesApproved(Column,TankIndex,Row) ) {
									Row++;
									ProgressBar1->StepIt();
								} else {
									//Row=Row;
								}
								Column=0;
							} else {
								Column++;
							}
						}
						NumberOfRowInTank[TankIndex] = Row;
						TankIndex++;
						NumberOfTanks = TankIndex;
					}
					break;
				}  // End of switch
			}
		}
	}//end of file
	ReadInFile.close();
}
//---------------------------------------------------------------------------

bool TReadFileFormat::ValuesApproved(int Column,int TankIndex,int Row)
{
	bool OKValues = false;
	float tempFloat = *((InValuesListPtr[Column])+(TankIndex*MAX_LINES)+Row);
	if ( tempFloat == 0.000 ) {
		OKValues = true;	//Trim 0=0
	} else {
		OKValues = false;	//Trim !=0
	}
	return OKValues;
}
//---------------------------------------------------------------------------


void __fastcall TReadFileFormat::ValuePopupClick(TObject *Sender)
{
	TMenuItem *TempItem = (TMenuItem *)Sender;
//  TPopupMenu *PMPtr =(TPopupMenu *)Sender;
	if ( TempItem ) {
		CurrentValuePtr->Text = TempItem->Caption.c_str() ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TReadFileFormat::ValueEnter(TObject *Sender)
{
	CurrentValuePtr =(TEdit *)Sender;
}
//---------------------------------------------------------------------------

void __fastcall TReadFileFormat::SaveFileButtonClick(TObject *Sender)
{
	if ( SaveDialog->Execute() ) {
		ProgressBar1->Visible = true;
		ProgressBar1->Max = MAX_LINES;
		TankNameEdit->Visible = true;
		String FileName = SaveDialog->FileName;
		CheckOutValueTypes();
		WriteToFile(FileName.c_str());
		ProgressBar1->Visible = false;
		TankNameEdit->Visible = false;
	}
}
//---------------------------------------------------------------------------

void TReadFileFormat::WriteToFile(wchar_t *fileName)
{
	ofstream WriteOutFile(fileName);
	if ( WriteOutFile ) {
		WriteOutFile.clear();
		WriteOutFile << endl;
		WriteOutFile << ValueListString.c_str() << endl;
		WriteOutFile << endl;
		for ( int TankIndex=0; TankIndex<NumberOfTanks; TankIndex++ ) {
			WriteOutFile << endl;
			WriteOutFile << "Tank " << TankName[TankIndex].c_str() << endl;
			ProgressBar1->Max = NumberOfRowInTank[TankIndex];
			ProgressBar1->Position = 0;
			TankNameEdit->Text = TankName[TankIndex];
			for ( int Row =0; Row<NumberOfRowInTank[TankIndex]; Row++ ) {
				ProgressBar1->StepIt();
				for ( int Column =0; Column<NumberOfOutColumn; Column++ ) {
					if ( OutValuesListPtr[Column] != *Ignore ) {
						float tempValue = *((OutValuesListPtr[Column])+(TankIndex*MAX_LINES)+Row);
						String tempStrValue;
						tempStrValue = tempStrValue.FormatFloat("0.000",tempValue);
						WriteOutFile << tempStrValue.c_str();
						WriteOutFile << '\t';
					}
				}
				WriteOutFile << endl;
			}
			WriteOutFile << endl;
		}
		WriteOutFile.close();
	}
}
//---------------------------------------------------------------------------

void TReadFileFormat::CheckInValueTypes(void)
{
	for ( int l=0;l<MAX_VALUES;l++ ) {
		InValuesListPtr[l]= NULL;
	}
	for ( int l=0;l<NumberOfInColumn;l++ ) {
		if ( InValueList[l]->Text== "Level" ) {
			InValuesListPtr[l]= *Level;
		} else if ( InValueList[l]->Text== "Ullage" ) {
			InValuesListPtr[l]= *Ullage;
		} else if ( InValueList[l]->Text== "Sounding" ) {
			InValuesListPtr[l]= *Sounding;
		} else if ( InValueList[l]->Text== "Volume" ) {
			InValuesListPtr[l]= *Volume;
		} else if ( InValueList[l]->Text== "LCG" ) {
			InValuesListPtr[l]= *LCG;
		} else if ( InValueList[l]->Text== "TCG" ) {
			InValuesListPtr[l]= *TCG;
		} else if ( InValueList[l]->Text== "VCG" ) {
			InValuesListPtr[l]= *VCG;
		} else if ( InValueList[l]->Text== "Swl" ) {
			InValuesListPtr[l]= *Swl;
		} else if ( InValueList[l]->Text== "LCF" ) {
			InValuesListPtr[l]= *LCF;
		} else if ( InValueList[l]->Text== "TCF" ) {
			InValuesListPtr[l]= *TCF;
		} else if ( InValueList[l]->Text== "Ixx" ) {
			InValuesListPtr[l]= *Ixx;
		} else if ( InValueList[l]->Text== "Iyy" ) {
			InValuesListPtr[l]= *Iyy;
		} else if ( InValueList[l]->Text== "Trim" ) {
			InValuesListPtr[l]= *Trim;
		} else if ( InValueList[l]->Text== "Pressure" ) {
			InValuesListPtr[l]= *Pressure;
		} else if ( InValueList[l]->Text== "Unknown" ) {
			InValuesListPtr[l]= *Unknown;
		} else { /*if(InValueList[l]->Text== "Ignore")*/
			InValuesListPtr[l]= *Ignore;
		}
	}
}
//---------------------------------------------------------------------------

void TReadFileFormat::CheckOutValueTypes(void)
{
	for ( int l=0;l<MAX_VALUES;l++ ) {
		OutValuesListPtr[l]= *Ignore;
	}
	NumberOfOutColumn = 0;
	for ( int l=0;l<OutValueListEntries;l++ ) {
		if ( OutValueList[l]->Text== "Level" ) {
			NumberOfOutColumn++;
			LevelEnabled  = true;
			OutValuesListPtr[l]= *Level;
		} else if ( OutValueList[l]->Text== "Ullage" ) {
			NumberOfOutColumn++;
			UllageEnabled  = true;
			OutValuesListPtr[l]= *Ullage;
		} else if ( OutValueList[l]->Text== "Sounding" ) {
			NumberOfOutColumn++;
			SoundingEnabled  = true;
			OutValuesListPtr[l]= *Sounding;
		} else if ( OutValueList[l]->Text== "Volume" ) {
			NumberOfOutColumn++;
			VolumeEnabled  = true;
			OutValuesListPtr[l]= *Volume;
		} else if ( OutValueList[l]->Text== "LCG" ) {
			NumberOfOutColumn++;
			LCGEnabled  = true;
			OutValuesListPtr[l]= *LCG;
		} else if ( OutValueList[l]->Text== "TCG" ) {
			NumberOfOutColumn++;
			TCGEnabled  = true;
			OutValuesListPtr[l]= *TCG;
		} else if ( OutValueList[l]->Text== "VCG" ) {
			NumberOfOutColumn++;
			VCGEnabled  = true;
			OutValuesListPtr[l]= *VCG;
		} else if ( OutValueList[l]->Text== "Swl" ) {
			NumberOfOutColumn++;
			SwlEnabled  = true;
			OutValuesListPtr[l]= *Swl;
		} else if ( OutValueList[l]->Text== "LCF" ) {
			NumberOfOutColumn++;
			LCFEnabled  = true;
			OutValuesListPtr[l]= *LCF;
		} else if ( OutValueList[l]->Text== "TCF" ) {
			NumberOfOutColumn++;
			TCFEnabled  = true;
			OutValuesListPtr[l]= *TCF;
		} else if ( OutValueList[l]->Text== "Ixx" ) {
			NumberOfOutColumn++;
			IxxEnabled  = true;
			OutValuesListPtr[l]= *Ixx;
		} else if ( OutValueList[l]->Text== "Iyy" ) {
			NumberOfOutColumn++;
			IyyEnabled  = true;
			OutValuesListPtr[l]= *Iyy;
		} else if ( OutValueList[l]->Text== "Trim" ) {
			NumberOfOutColumn++;
			TrimEnabled  = true;
			OutValuesListPtr[l]= *Trim;
		} else if ( OutValueList[l]->Text== "Pressure" ) {
			NumberOfOutColumn++;
			PressureEnabled  = true;
			OutValuesListPtr[l]= *Trim;
		} else if ( OutValueList[l]->Text== "Unknown" ) {
			NumberOfOutColumn++;
			UnknownEnabled  = true;
			OutValuesListPtr[l]= *Unknown;
		} else if ( OutValueList[l]->Text== "Ignore" ) {
			//NumberOfOutColumn++;
			OutValuesListPtr[l]= *Ignore;
		}
	}
	ValueListString = "";
	for ( int l=0;l<NumberOfOutColumn;l++ ) {
		ValueListString =(String)ValueListString+OutValueList[l]->Text+'\t';
	}
}
//---------------------------------------------------------------------------

//Start converting of tables:
void __fastcall TReadFileFormat::ConvertButtonClick(TObject *Sender)
{
	if ( SaveDialog->Execute() ) {
		ProgressBar1->Visible = true;
		ProgressBar1->Max = MAX_LINES;
		TankNameEdit->Visible = true;
		String FileName = SaveDialog->FileName;
		CheckOutValueTypes();
		UpdateLimits();
		CheckValues();
		ConvertTables();
		WriteConvertedTables(FileName.c_str());
		ProgressBar1->Visible = false;
		TankNameEdit->Visible = false;
		GraphTabSheet->TabVisible = true;
	}
}
//---------------------------------------------------------------------------

void TReadFileFormat::ConvertTables(void)
{
//	double Density = 1.000;
//        TankData *PrevTnkPtr = NULL;
	float LevelFact  = pow10(3- LevelRadioGroup->ItemIndex);
	float CGFact     = pow10(3- CGRadioGroup->ItemIndex);
	float VolumeFact = 1.0;
	float FSMFact    = 1.0;
	if ( !VolumeRadioGroup->ItemIndex )	VolumeFact = 1000.0;
	if ( !FSMRadioGroup->ItemIndex ) FSMFact = 100.0;
	for ( int TIndex=0;TIndex<NumberOfTanks;TIndex++ ) {
		TankData *TankPtr = new TankData;
		Tank[TIndex] = TankPtr;
		TankPtr->Name = TankName[TIndex].c_str();
		TankPtr->Entries1 = NumberOfRowInTank[TIndex];
		TankPtr->Entries2 = NumberOfRowInTank[TIndex];
		TankPtr->Entries3 = NumberOfRowInTank[TIndex];
		TankPtr->Entries4 = NumberOfRowInTank[TIndex];
		TankPtr->Entries5 = NumberOfRowInTank[TIndex];
		ProgressBar1->Max = NumberOfRowInTank[TIndex];
		ProgressBar1->Position = 0;
		TankNameEdit->Text = TankName[TIndex];
		for ( int l=0;l<NumberOfRowInTank[TIndex];l++ ) {
			ProgressBar1->StepIt();
			if ( LevelEnabled ) {
				TankPtr->Level1[l] = (Level[TIndex][l]-Level[TIndex][0])/LevelFact;
				TankPtr->Level2[l] = TankPtr->Level1[l];
				TankPtr->Level3[l] = TankPtr->Level1[l];
				TankPtr->Level4[l] = TankPtr->Level1[l];
			}
			if ( UllageEnabled ) {
				TankPtr->Ullage[l] = Ullage[TIndex][l]/LevelFact;
				TankPtr->Level1[l] = TankPtr->Ullage[l];
				TankPtr->Level2[l] = TankPtr->Ullage[l];
				TankPtr->Level3[l] = TankPtr->Ullage[l];
				TankPtr->Level4[l] = TankPtr->Ullage[l];
			}
			if ( SoundingEnabled ) {
				TankPtr->Sounding[l] = Sounding[TIndex][l]/LevelFact;
			}
			if ( VolumeEnabled ) {
				TankPtr->Volume[l]  = Volume[TIndex][l]/VolumeFact;
				TankPtr->SoundingVol[l] = Volume[TIndex][l];
			}
			if ( LCGEnabled ) {
				TankPtr->LCG[l] = LCG[TIndex][l]/CGFact;
			}
			if ( TCGEnabled ) {
				TankPtr->TCG[l] = TCG[TIndex][l]/CGFact;
			}
			if ( VCGEnabled ) {
				TankPtr->VCG[l]= VCG[TIndex][l]/CGFact;
			}
			if ( SwlEnabled ) {
				TankPtr->Swl[l] = Swl[TIndex][l]/CGFact;
			}
			if ( LCFEnabled ) {
				TankPtr->LCF[l] = LCF[TIndex][l]/CGFact;
			}
			if ( TCFEnabled ) {
				TankPtr->TCF[l] = TCF[TIndex][l]/CGFact;
			}
			if ( IxxEnabled ) {
				TankPtr->Ixx[l] = Ixx[TIndex][l]/FSMFact;
				TankPtr->FSM[l] = TankPtr->Ixx[l];
			}
			if ( IyyEnabled ) {
				TankPtr->Iyy[l] = Iyy[TIndex][l]/FSMFact;
			}
			if ( PressureEnabled ) {
				double Level = TankPtr->Pressure[l]/TankPtr->Density;
				TankPtr->Level1[l] = Level;
				TankPtr->Level2[l] = TankPtr->Level1[l];
				TankPtr->Level3[l] = TankPtr->Level1[l];
				TankPtr->Level4[l] = TankPtr->Level1[l];
			}
			if ( TrimEnabled ) {
				TankPtr->Trim[l] = Trim[TIndex][l];
			}
			if ( UnknownEnabled ) {
				TankPtr->Unknown[l] = Unknown[TIndex][l];
			}
		}
		TankPtr->Density  = Density[TIndex];
		TankPtr->IsOnline = IsOnline[TIndex];
		TankPtr->TankType = TType[TIndex];
		TankPtr->FirstFrame = FirstFrame[TIndex];
		TankPtr->LastFrame  = LastFrame[TIndex];
	}
}
//---------------------------------------------------------------------------

bool TReadFileFormat::CheckValues(void)
{
	bool HasWarning = false;
	MessageListBox->Visible = false;
	MessageListBox->Clear();
	for ( int TIndex=0;TIndex<NumberOfTanks;TIndex++ ) {
		bool HasWarningInTank = false;
		MessageListBox->Items->Add((String)"Tank index:"+TIndex+" Tank name:"+TankName[TIndex]);
		for ( int l=1;l<NumberOfRowInTank[TIndex];l++ ) {
			if ( LevelEnabled ) {
				if ( !(Level[TIndex][l] >= Level[TIndex][l-1]) ||
					 !(fabs(Level[TIndex][l-1]-Level[TIndex][l])< OtherDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next Level at "+Level[TIndex][l-1]);
				}
			}
			if ( UllageEnabled ) {
				if ( !(Ullage[TIndex][l] <= Ullage[TIndex][l-1]) ||
					 !(fabs(Ullage[TIndex][l-1]-Ullage[TIndex][l])< OtherDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next Ullage at "+Ullage[TIndex][l-1]);
				}
			}
			if ( SoundingEnabled ) {
				if ( !(Sounding[TIndex][l] >= Sounding[TIndex][l-1]) ||
					 !(fabs(Sounding[TIndex][l-1]-Sounding[TIndex][l])< OtherDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next Sounding at "+Sounding[TIndex][l-1]);
				}
			}
			if ( VolumeEnabled ) {
				if ( !(Volume[TIndex][l] >= Volume[TIndex][l-1]) ||
					 !(fabs(Volume[TIndex][l-1]-Volume[TIndex][l])< OtherDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next Volume at "+Volume[TIndex][l-1]);
				}
			}
			if ( LCGEnabled ) {
				if ( !(fabs(LCG[TIndex][l-1]-LCG[TIndex][l])< CGDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next LCG at "+LCG[TIndex][l-1]);
				}
			}
			if ( TCGEnabled ) {
				if ( !(fabs(TCG[TIndex][l-1]-TCG[TIndex][l])< CGDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next TCG at "+TCG[TIndex][l-1]);
				}
			}
			if ( VCGEnabled ) {
				if ( !(VCG[TIndex][l] >= VCG[TIndex][l-1]) ||
					 !(fabs(VCG[TIndex][l-1]-VCG[TIndex][l])< CGDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next VCG at "+VCG[TIndex][l-1]);
				}
			}
			if ( SwlEnabled ) {
				if ( !(fabs(Swl[TIndex][l-1]-Swl[TIndex][l])< OtherDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next Swl at "+Swl[TIndex][l-1]);
				}
			}
			if ( LCFEnabled ) {
				if ( !(fabs(LCF[TIndex][l-1]-LCF[TIndex][l])< CFDiffLimit ) ) {
					HasWarning = true;
					MessageListBox->Items->Add((String)"Fault for next LCF at "+LCF[TIndex][l-1]);
				}
			}
			if ( TCFEnabled ) {
				if ( !(fabs(TCF[TIndex][l-1]-TCF[TIndex][l])< CFDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next TCF at "+TCF[TIndex][l-1]);
				}
			}
			if ( IxxEnabled ) {
				if ( !(fabs(Ixx[TIndex][l-1]-Ixx[TIndex][l])< 100 ) ) {	//RBMARK OtherDiffLimit
					HasWarning = true;
					MessageListBox->Items->Add((String)"Fault for next Ixx at "+Ixx[TIndex][l-1]);
				}
			}
			if ( IyyEnabled ) {
				if ( !(fabs(Iyy[TIndex][l-1]-Iyy[TIndex][l])< OtherDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next Iyy at "+Iyy[TIndex][l-1]);
				}
			}
			if ( TrimEnabled ) {
				if ( !(fabs(Trim[TIndex][l-1]-Trim[TIndex][l])< OtherDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next Trim at "+Trim[TIndex][l-1]);
				}
			}
			if ( UnknownEnabled ) {
				if ( !(fabs(Unknown[TIndex][l-1]-Unknown[TIndex][l])< OtherDiffLimit ) ) {
					HasWarningInTank = true;
					MessageListBox->Items->Add((String)"Fault for next Unknown at "+Unknown[TIndex][l-1]);
				}
			}
			if ( HasWarningInTank ) {
				HasWarning = true;
			}
		}
		if ( HasWarning ) {
			MessageListBox->Visible = true;
		}
	}
	return HasWarning;
}
//---------------------------------------------------------------------------

void TReadFileFormat::WriteConvertedTables(wchar_t *fileName)
{
	ofstream OutFile;
	OutFile.open(fileName);
	TankData *TPtr     = NULL;

	for ( int i=0; i < NumberOfTanks; i++ ) {
		if ( VolumeEnabled ) {
			MinimizeHeightVol(&OutFile,Tank[i],VolumeLimit);
		}
		if ( SoundingEnabled ) {
			MinimizeSoundingVol(&OutFile,Tank[i],VolumeLimit);
		}
		if ( LCGEnabled ) {
			MinimizeCG(&OutFile,Tank[i],CenterOfGravityLimit);
		}
		if ( IxxEnabled ) {
			MinimizeFSM(&OutFile,Tank[i],FreeSurfaceMomentLimit);
		}
		if ( LCFEnabled ) {
			MinimizeCF(&OutFile,Tank[i],CenterOfFlotationLimit);
		}
	}
	OutFile.setf(ios::fixed);

	for ( int i=0,Cnt=1; i < NumberOfTanks; i++ ) {
		TPtr = Tank[i];
		String Ttype;
		switch ( TPtr->TankType ) {
		case HEAVY_FUEL :
			Ttype = "HFOTank";
			break;
		case DIESEL     :
			Ttype = "DieselOilTank";
			break;
		case LUBRICANT  :
			Ttype = "LubricantsTank";
			break;
		case FRESHWATER :
			Ttype = "FreshWaterTank";
			break;
		case MISC       :
			Ttype = "MiscTank";
			break;
		case BALLAST    :
			Ttype = "BallastTank";
            break;
		case CARGO      :
			Ttype = "CargoTank";
			break;
		}
		OutFile << Ttype.c_str() << "\t" << endl;
		OutFile << "\tName\t" << TPtr->Name.c_str() << endl;

		if ( TPtr->IsOnline ) {
			AnsiString idString;
			idString.sprintf("0x%0x", 0x41a0000+Cnt++);
			OutFile <<  "\tProTank " << idString.c_str() << endl;
		}
		OutFile << "\tFrame  " <<  TPtr->FirstFrame.c_str() << "\t" << TPtr->LastFrame.c_str() << endl << endl;
		//OutFile << "\tMAX_TABLE_ULLAGE";
		//OutFile << setw(8) << setprecision(3) << TPtr->Level1[TPtr->Entries1-1] << endl;
		if ( VolumeEnabled ) {
			OutFile << "\tLevelVolTable" << endl;
			for ( int j=0; j < TPtr->Entries1; j++ ) {
				OutFile << '\t';
				OutFile << setw(8) << setprecision(3) << TPtr->Level1[j] << "\t";
				OutFile << setw(8) << setprecision(3) << TPtr->Volume[j] << endl;
			}
			OutFile << "\tEndTable" << endl << endl;
		}
		if ( SoundingEnabled ) {
			OutFile << "\tSoundingTable" << endl;
			for ( int j=0; j < TPtr->Entries5; j++ ) {
				OutFile << '\t';
				OutFile << setw(8) << setprecision(3) << TPtr->Sounding[j] << "\t";
				OutFile << setw(8) << setprecision(3) << TPtr->SoundingVol[j] << endl;
			}
			OutFile << "\tEndTable" << endl << endl;
		}
		if ( LCFEnabled ) {
			OutFile << "\tCF_Table" << endl;
			OutFile << "\Order       LCF     TCF" << endl;
			for ( int j=0; j < TPtr->Entries4; j++ ) {
				OutFile << '\t';
				OutFile << setw(10) << setprecision(3) << TPtr->Level4[j];
				OutFile << setw(10) << setprecision(3) << TPtr->LCF[j];
				OutFile << setw(10) << setprecision(3) << TPtr->TCF[j] << endl;
			}
			OutFile << "\tEndTable" << endl << endl;
		}
		if ( LCGEnabled ) {
			OutFile << "\tCG_Table" << endl;
			OutFile << "\tOrder       VCG     TCG     LCG" << endl;
			for ( int j=0; j < TPtr->Entries2; j++ ) {
				OutFile << '\t';
				OutFile << setw(10) << setprecision(3) << TPtr->Level2[j];
				OutFile << setw(10) << setprecision(3) << TPtr->VCG[j];
				OutFile << setw(10) << setprecision(3) << TPtr->TCG[j];
				OutFile << setw(10) << setprecision(3) << TPtr->LCG[j] << endl;
			}
			OutFile << "\tEndTable" << endl << endl;
		}
		if ( IxxEnabled ) {
			OutFile << "\tTFS_Table" << endl;
			for ( int j=0; j < TPtr->Entries3; j++ ) {
				OutFile << '\t';
				OutFile << setw(8) << setprecision(3) << TPtr->Level3[j];
				OutFile << setw(11) << setprecision(3) << TPtr->FSM[j] << endl;
			}
			OutFile << "\tEndTable" << endl << endl;
		}
		OutFile << "End" << endl << endl;
	}
	OutFile.close();



}
//---------------------------------------------------------------------------

void TReadFileFormat::UpdateLimits(void){
	try {
		VolumeLimit = VolumeLimitEdit->Text.ToDouble();
	} catch ( const exception& e ) {
		VolumeLimit = VOL_LIMIT;
	}
	try {
		CenterOfGravityLimit = CenterOfGravityLimitEdit->Text.ToDouble();
	} catch ( const exception& e ) {
		CenterOfGravityLimit = CG_LIMIT;
	}
	try {
		FreeSurfaceMomentLimit = FreeSurfaceMomentLimitEdit->Text.ToDouble();
	} catch ( const exception& e ) {
		FreeSurfaceMomentLimit = FSM_LIMIT;
	}
	try {
		CenterOfFlotationLimit = CenterOfFlotationLimitEdit->Text.ToDouble();
	} catch ( const exception& e ) {
		CenterOfFlotationLimit = CF_LIMIT;
	}
	try {
		CGDiffLimit = CGDiffLimitEdit->Text.ToDouble();
	} catch ( const exception& e ) {
		CGDiffLimit = CG_DIFFERENCE_LIMIT;
	}
	try {
		CFDiffLimit = CFDiffLimitEdit->Text.ToDouble();
	} catch ( const exception& e ) {
		CFDiffLimit = CF_DIFFERENCE_LIMIT;
	}
	try {
		OtherDiffLimit = OtherDiffLimitEdit->Text.ToDouble();
	} catch ( const exception& e ) {
		OtherDiffLimit = BIG_DIFFERENCE_LIMIT;
	}
}
//---------------------------------------------------------------------------

void TReadFileFormat::ZerosetTables(void){
	for ( int i=0; i<MAX_TANKS; i++ ) {
		for ( int j=0; j<MAX_LINES; j++ ) {
			Level[i][j]=0;
			Ullage[i][j]=0;
			Sounding[i][j]=0;
			Volume[i][j]=0;
			LCG[i][j]=0;
			TCG[i][j]=0;
			VCG[i][j]=0;
			Swl[i][j]=0;
			LCF[i][j]=0;
			TCF[i][j]=0;
			Ixx[i][j]=0;
			Iyy[i][j]=0;
			Trim[i][j]=0;
			Pressure[i][j]=0;
			Unknown[i][j]=0;
			Ignore[i][j]=0;
		}
	}
}
//---------------------------------------------------------------------------

void TReadFileFormat::Initialize(void){
	FileLineList  = new TStringList();
	InValueListEntries=0;
	InValueList[InValueListEntries++] = Value1;
	InValueList[InValueListEntries++] = Value2;
	InValueList[InValueListEntries++] = Value3;
	InValueList[InValueListEntries++] = Value4;
	InValueList[InValueListEntries++] = Value5;
	InValueList[InValueListEntries++] = Value6;
	InValueList[InValueListEntries++] = Value7;
	InValueList[InValueListEntries++] = Value8;
	InValueList[InValueListEntries++] = Value9;
	InValueList[InValueListEntries++] = Value10;
	InValueList[InValueListEntries++] = Value11;
	InValueList[InValueListEntries++] = Value12;
	InValueList[InValueListEntries++] = Value13;
	InValueList[InValueListEntries++] = Value14;
	OutValueListEntries=0;
	OutValueList[OutValueListEntries++] = Value101;
	OutValueList[OutValueListEntries++] = Value102;
	OutValueList[OutValueListEntries++] = Value103;
	OutValueList[OutValueListEntries++] = Value104;
	OutValueList[OutValueListEntries++] = Value105;
	OutValueList[OutValueListEntries++] = Value106;
	OutValueList[OutValueListEntries++] = Value107;
	OutValueList[OutValueListEntries++] = Value108;
	OutValueList[OutValueListEntries++] = Value109;
	OutValueList[OutValueListEntries++] = Value110;
	OutValueList[OutValueListEntries++] = Value111;
	OutValueList[OutValueListEntries++] = Value112;
	OutValueList[OutValueListEntries++] = Value113;
	OutValueList[OutValueListEntries++] = Value114;
	LevelEnabled    = false;
	UllageEnabled   = false;
	SoundingEnabled = false;
	VolumeEnabled   = false;
	LCGEnabled = false;
	TCGEnabled = false;
	VCGEnabled = false;
	SwlEnabled = false;
	LCFEnabled = false;
	TCFEnabled = false;
	IxxEnabled = false;
	IyyEnabled = false;
	TrimEnabled = false;
	PressureEnabled = false;
	UnknownEnabled  = false;

	VolumeLimitEdit->Text = VOL_LIMIT;
	CenterOfGravityLimitEdit->Text = CG_LIMIT;
	FreeSurfaceMomentLimitEdit->Text = FSM_LIMIT;
	CenterOfFlotationLimitEdit->Text = CF_LIMIT;
	CGDiffLimitEdit->Text = CG_DIFFERENCE_LIMIT;
	CFDiffLimitEdit->Text = CF_DIFFERENCE_LIMIT;
	OtherDiffLimitEdit->Text = BIG_DIFFERENCE_LIMIT;

	String InitialDir = (String) "G:\\Prosjekt Oversikt\\";
	LoadDialog->InitialDir = InitialDir;
	SaveDialog->InitialDir = InitialDir;



}
//---------------------------------------------------------------------------




void __fastcall TReadFileFormat::TankComboBoxChange(TObject *Sender){
	int TIndex = TankComboBox->ItemIndex;
	if ( TIndex >= 0 ) {
		Series7->Clear();
		float LevelFact  = pow10(3- LevelRadioGroup->ItemIndex);

		for ( int i=0; i <Tank[TIndex]->Entries1; i++ ) {
			Series7->AddXY(Tank[TIndex]->Level1[i]/LevelFact,Tank[TIndex]->Volume[i],"",(TColor)clTeeColor);
			//Series7->AddXY(Tank[TIndex]->Volume[i],Tank[TIndex]->Level1[i]/LevelFact,"",(TColor)clTeeColor);
		}
	}
}
//---------------------------------------------------------------------------






