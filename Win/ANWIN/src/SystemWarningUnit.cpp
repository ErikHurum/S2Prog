#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#pragma hdrstop
#include "MainUnit.h"
#include "SystemWarningUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"
TSystemWarningForm *SystemWarningForm;
//---------------------------------------------------------------------------

__fastcall TSystemWarningForm::TSystemWarningForm(TComponent* Owner)
  : TChildForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSystemWarningForm::Timer1Timer(TObject *Sender)
{
	Update(); //Uppdate();
	if (RichEdit1->Lines->Count ){
		if ( RichEdit1->Text == AnsiString("NO WARNINGS!")) {
			RichEdit1->Color = clGreen;
		}else{
			RichEdit1->Color = clYellow;
		}

	}else{
		RichEdit1->Color = clYellow;
	}
}
//---------------------------------------------------------------------------

void __fastcall TSystemWarningForm::Update()
{
//	this->Invalidate();
    Paint();
}
//---------------------------------------------------------------------------

void __fastcall TSystemWarningForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  	Action = caFree;
  	delete freeTextWarningMutex;
}
//---------------------------------------------------------------------------


void __fastcall TSystemWarningForm::AddFreeTextWarning(AnsiString& warning)
{
	double timeNow = time(NULL);

	freeTextWarningMutex->Acquire();
	freeTextWarningVector.insert( freeTextWarningVector.begin(), make_pair(timeNow, warning) );
	freeTextWarningMutex->Release();
	Update();
}
//---------------------------------------------------------------------------

#define TSystemWarningForm_MaxFreeTextWarningsDisplayed 10

void __fastcall TSystemWarningForm::RemoveOldFreeTextWarnings()
{
	freeTextWarningMutex->Acquire();

	if (freeTextWarningVector.size() > TSystemWarningForm_MaxFreeTextWarningsDisplayed) {
		freeTextWarningVector.resize(TSystemWarningForm_MaxFreeTextWarningsDisplayed);
	}

	freeTextWarningMutex->Release();
}
//---------------------------------------------------------------------------


void __fastcall TSystemWarningForm::OnFormPaint(TObject *Sender)
{
    RichEdit1->Lines->Clear();

    if(NetworkOK){

        if ( !MainForm->CheckNetwork() ){
                RichEdit1->Lines->Add("No communication with Target. (Check target and serial lines)");
        }else if(!MainForm->WinUartPtr->SystemMatch){
                RichEdit1->Lines->Add("Configuration file mismatch between Target and Workstation,");
                RichEdit1->Lines->Add("or compatibility problem with program version .");
        }else if(!SysInfoAvailable){
                RichEdit1->Lines->Add("Configuration file mismatch between Target and Workstation,");
                RichEdit1->Lines->Add("or compatibility problem with program version .");
        }else if(!MainForm->ConfigLoaded){
                RichEdit1->Lines->Add("No configuration file loaded.");
                RichEdit1->Lines->Add("Please give the system a few minutes to receive new configuration from TCU.");
        }
  }else{
    if ( MainForm->SimulatorFlag ){
      RichEdit1->Lines->Add("Internal Simulator.");//status;
    }else{
      RichEdit1->Lines->Add("System offline, No link setup to IO-system.");//status;
	  RichEdit1->Lines->Add(MainForm->ErrorMsgString);
    }
  }

	// Output custom warnings
	freeTextWarningMutex->Acquire();
    RemoveOldFreeTextWarnings();

	warningItemVector_t::iterator warningIter = freeTextWarningVector.begin();

	while (warningIter != freeTextWarningVector.end())
	{
		RichEdit1->Lines->Add( (*warningIter).second );
		warningIter++;
	}
	freeTextWarningMutex->Release();


/* RBMARK
  for(int i=0; i < SensorData::Number_of_Sensors; i++){
    SensorData *SPtr = SensorData::Table[i];
    if ( !SPtr->Status.Enable ){

      RichEdit1->Lines->Add((String)SPtr->Tag + " "
                          + SensorType[SPtr->Status.Type] + " Sensor is disabled.");

    }
  }   */
}
//---------------------------------------------------------------------------

void __fastcall TSystemWarningForm::FormCreate(TObject *Sender)
{

	freeTextWarningMutex = new TMutex(true);
	Update(); //Uppdate();
}
//---------------------------------------------------------------------------
