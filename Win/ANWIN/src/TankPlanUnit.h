//---------------------------------------------------------------------------
#ifndef TankPlanUnitH
#define TankPlanUnitH
#include "ChildUnit.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "CargoLegendObject.h"
#include "RzPanel.hpp"
#include "ES.BaseControls.hpp"
#include "ES.PaintBox.hpp"
#include "ES.Labels.hpp"
#include "AdvMenus.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>


#define MAX_DRAWINGPOINT_TANK  500
#define MAX_LEGENDS             10

typedef struct {
	POINT Point;
    POINT DefaultPoint;
} PointStruct;

typedef struct {
    PointStruct ObjPoint;
	PROTank*    TankPtr;
}TankPointStruct;

typedef struct {
	PointStruct ObjPoint;
	PROTank*    TankPtr;
	int         AlarmTypeId;
	int         AlarmIndex;
}AlarmPointStruct;

typedef struct{
    TShape* Shape;
    TLabel* CargoLabel;
    TLabel* WeightLabel;
    TLabel* VolumeLabel;
    TRzPanel* Panel;
} LegendStruct;
//---------------------------------------------------------------------------
class TTankPlanDrawingForm : public TChildForm {
    __published:    // IDE-managed Components
    TPanel *PaintBoxPanel;
    TTimer *PaintBoxTimer;
    TPopupMenu *TankPopupMenu;
    TMenuItem *Showtank;
    TMenuItem *Change;
    TTimer *LegendTimer;
    TPrintDialog *PrintDialog1;
    TPrinterSetupDialog *PrinterSetupDialog1;
    TPanel *Panel11;
    TGroupBox *OpModeGroupBox;
    TComboBox *OpModeComboBox;
    TGroupBox *TankValuesGroupBox;
    TLabel *ULabel;
    TLabel *VolumProsentLabel;
    TLabel *Weight;
    TLabel *Volum;
    TLabel *temp;
    TLabel *UValueLabel;
    TLabel *VProsentValueLabel;
    TLabel *WValueLabel;
    TLabel *TValueLabel;
    TLabel *UUnitLabel;
    TLabel *VProsentUnitLabel;
    TLabel *WUnitLabel;
    TLabel *VUnitLabel;
    TLabel *TUnitLabel;
    TLabel *TankNameLabel;
    TGroupBox *CargoTypeGroupBox;
    TLabel *CargoTypeLabel;
    TShape *CargoColorShape;
    TButton *ShowHideButton;
    TButton *PrintButton;
    TGroupBox *LegendGroupBox;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *WeightUnitLabel2;
    TLabel *VolumeUnitLabel2;
    TLabel *VolumeUnitLabel1;
    TLabel *WeightUnitLabel1;
    TScrollBar *ScrollBar1;
    TGroupBox *ValueTypeGroupBox;
    TLabel *ValueTypeLabel;
    TLabel *ValueUnitLabel;
    TButton *SelectValueButton;
    TGroupBox *GroupBox2;
    TLabel *OpModeLabel;
    TLabel *VValueLabel;
	TRzPanel *Panel1;
	TShape *Shape1;
	TLabel *CargoLabel1;
	TLabel *VolumeLabel1;
	TLabel *sumLabel1;
	TRzPanel *Panel2;
	TShape *Shape2;
	TLabel *CargoLabel2;
	TLabel *VolumeLabel2;
	TLabel *sumLabel2;
	TRzPanel *Panel3;
	TShape *Shape3;
	TLabel *CargoLabel3;
	TLabel *VolumeLabel3;
	TLabel *sumLabel3;
	TRzPanel *Panel4;
	TShape *Shape4;
	TLabel *CargoLabel4;
	TLabel *VolumeLabel4;
	TLabel *sumLabel4;
	TRzPanel *Panel5;
	TShape *Shape5;
	TLabel *CargoLabel5;
	TLabel *VolumeLabel5;
	TLabel *sumLabel5;
	TRzPanel *Panel6;
	TShape *Shape6;
	TLabel *CargoLabel6;
	TLabel *VolumeLabel6;
	TLabel *sumLabel6;
	TRzPanel *Panel7;
	TShape *Shape7;
	TLabel *CargoLabel7;
	TLabel *VolumeLabel7;
	TLabel *sumLabel7;
	TRzPanel *Panel8;
	TShape *Shape8;
	TLabel *CargoLabel8;
	TLabel *VolumeLabel8;
	TLabel *sumLabel8;
	TRzPanel *Panel9;
	TShape *Shape9;
	TLabel *CargoLabel9;
	TLabel *VolumeLabel9;
	TLabel *sumLabel9;
	TRzPanel *Panel10;
	TShape *Shape10;
	TLabel *CargoLabel10;
	TLabel *VolumeLabel10;
	TLabel *sumLabel10;
	TEsPaintBox *EsPaintBox1;
	TAdvPopupMenu *AdvPopupMenu1;
	void __fastcall ShowHideButtonMouseDown(TObject *Sender,
                                            TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ShowtankClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall PaintBoxTimerTimer(TObject *Sender);
    void __fastcall SelectValueButtonClick(TObject *Sender);
    void __fastcall ScrollBar1Scroll(TObject *Sender, TScrollCode ScrollCode,
                                     int &ScrollPos);
    void __fastcall LegendTimerTimer(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall PrintButtonClick(TObject *Sender);
    void __fastcall OpModeComboBoxChange(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall EsPaintBox1Paint(TObject *Sender, TCanvas *Canvas, TRect &Rect);
	void __fastcall EsPaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);


private:    // User declarations
	bool NoReSize;
	bool RefreshForm;
    bool HasValueAndNameIndex;
	vector<HRGN> TankRegion;
	map<int,PROTank*>TankRegionNameMap;
	vector< vector<PointStruct> >TankPoint;
    vector<TankPointStruct>TankNamePoint;
    vector<TankPointStruct>TankValuePoint;
	vector<AlarmPointStruct>TankAlarmPoint;
	vector<TankPointStruct>TankSensorPoint;
	vector<TankPointStruct>TankReferencePoint;
	vector<TColor>TankCargoColorVect;
	vector<TColor>AlarmColorVect;
	bool AlarmBlink;
	float ScaleCoeffW;
	float ScaleCoeffH;
    float MaxX;
    float MinX;
    float MaxY;
    float MinY;
    int SpaceRound;
    void __fastcall use_file(const char* fileName);
    TStringList* LineList;
    bool HoldUpdate;

	vector<CargoLegend*>LegendList;
	LegendStruct PanelList[MAX_LEGENDS];
    int StartShowCT;
    int ValueKey;

	void __fastcall PopupMenuValueTypeExecute(TObject *Sender);
    void __fastcall FindTankPoints(void);
    void __fastcall SetTankXYPoints(int index);
    bool __fastcall SetTankNamePoints(int index);
	bool __fastcall SetTankValuePoints(int index);
    bool __fastcall SetTankAlarmPoints(int index);
    void __fastcall CopyTankNamePointsToValuePoints(void);
    void __fastcall RecalcXYPoints(void);
    void __fastcall ScaleTPDrawing(void);
    void __fastcall DrawAllTanks(TCanvas *Canvas);
    void __fastcall CreatePolygonRegion(void);
    void __fastcall ShowTankNames(TCanvas *Canvas);
    void __fastcall HideTankNames(void);
	virtual void __fastcall UpdateValues(void);

	virtual void __fastcall BlankValues(AnsiString Msg);
	void __fastcall UppdateValue(TCanvas *Canvas);
	void __fastcall UppdateAlarms(TCanvas *Canvas);

	void __fastcall FindCargoTypes(void);
    void __fastcall SetTankPopupMenu(void);
	void __fastcall CargoPopupExecute(TObject *Sender);
	void __fastcall CreateLegendList(void);
	void __fastcall AssignToPanelList(int Index, TShape* PShape,TLabel* PCargoLabel,TLabel* PsumLabel,TLabel* PVolumeLabel,TRzPanel* Panel);
	void __fastcall UpdateLegend(int Index, TColor CargoColor,AnsiString CargoName,AnsiString WeightStr,AnsiString VolumeStr,bool Visible);
	void __fastcall MakeLabelList(void);
	void __fastcall WriteRegistry(void);
	void __fastcall PaintTankPlan(void);
	TMenuItem* __fastcall AddToSubmMenu(ValueList *tmpList, volatile int *Start, int ValueEntries);

protected:
	AnsiString RegNameKey;
	void __fastcall ReadRegistry(void);
	virtual void __fastcall UpdateStringGrids(void);
	virtual void __fastcall GetTankDisplayColors(PROTank *pTank, System::Uitypes::TColor *backgroundColor, System::Uitypes::TColor *foregroundColor);

public:     // User declarations
    __fastcall TTankPlanDrawingForm(TComponent* Owner,vector<PRogramObjectBase*> ObjVector, const char* fileName);

};
//---------------------------------------------------------------------------
extern PACKAGE TTankPlanDrawingForm *TankPlanDrawingForm;
//---------------------------------------------------------------------------
#endif