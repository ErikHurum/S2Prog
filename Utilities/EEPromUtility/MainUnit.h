//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TOpenDialog *LoadDialog;
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *LabelSensorCount;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	void __fastcall Unpack(void);
	void __fastcall PackSensorData(U8 CP[],bool IsCard=false);
	void __fastcall CalcSensor(SensorInfo *SnsPtr,AnsiString Path);
	void __fastcall CalcCarg(double X[TEMP_ENTRIES], double Y[TEMP_ENTRIES], double F[TEMP_ENTRIES], double G[TEMP_ENTRIES]);
	void __fastcall WriteSensorData(SensorInfo *SnsPtr, double CalcFRO[MAX_MV_CALDATA][TEMP_ENTRIES], double CalcNL1, double CalcNL2, AnsiString Path);
	void __fastcall ReadFromFile(AnsiString FileName);
	void __fastcall WriteADCardData(SensorInfo *SnsPtr, AnsiString Path);

	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
