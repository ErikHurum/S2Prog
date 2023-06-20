// ---------------------------------------------------------------------------

#ifndef DraftUnitH
#define DraftUnitH
#include "ChildUnit.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "AdvEdit.hpp"
#include "RzEdit.hpp"
#include <Vcl.Mask.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

// ---------------------------------------------------------------------------
class TDraftsForm : public TChildForm {
__published: // IDE-managed Components

	TGroupBox *DraftGroupBox;
	TLabel *DFore;
	TLabel *DPort;
	TLabel *DStarboard;
	TLabel *DAft;
	TLabel *At;
	TEdit *EditDraftFore;
	TEdit *EditDraftPort;
	TEdit *EditDraftStarboard;
	TEdit *EditDraftAft;
	TRadioGroup *DraftRadioGroup;
	TGroupBox *SeaWaterGroupBox;
	TEdit *EditSeaWater;
	TLabel *SeaWaterUnit;
	TTimer *Timer1;
	TPaintBox *PaintBox1;
	TEdit *EditAftPort;
	TEdit *EditAftStarboard;
	TEdit *EditFwdPort;
	TEdit *EditFwdStarboard;
	TGroupBox *GroupBox1;
	TShape *ShapeOnline;
	TLabel *Label2;
	TShape *ShapeDrySensor;
	TLabel *Label3;
	TShape *ShapeCalculated;
	TLabel *Label6;
	TLabel *Label4;
	TShape *ShapeNoSensors;
	TShape *ShapeHWAlarm;
	TLabel *Label5;
	TShape *ShapeUnknownError;
	TLabel *Label7;
	TLabel *DraftUnit;
	TLabel *DraftLable;

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall EditExit(TObject *Sender);
	void __fastcall EditKeyPress(TObject *Sender, char &Key);
	void __fastcall EditSeaWaterExit(TObject *Sender);
	void __fastcall EditSeaWaterKeyPress(TObject *Sender, char &Key);
	void __fastcall ReadRegistry(void);
	void __fastcall WriteRegistry(void);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations

	vector<TEdit*>EditDraftList;
	POINT ShipShapePoints[6];
	POINT BargeShapePoints[9];
	int EditDelayCount;
	int PrevItemIdex;
	TEdit *CurrentEditPtr;
	AnsiString RegNameKey;

public: // User declarations

	__fastcall TDraftsForm(TComponent* Owner);
	void CheckDrafts();
	void UpdateValue(TEdit *EditPtr, TLabel *LabelPtr);
	void UpdateValues(void);

};

// ---------------------------------------------------------------------------
extern PACKAGE TDraftsForm *DraftsForm;
// ---------------------------------------------------------------------------
#endif
