#include "ConstantsANWIN.h"
#pragma hdrstop
#include "TankDetailUnit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "LiteCall"
#pragma link "MemDS"
#pragma link "DASQLMonitor"
#pragma link "LiteSQLMonitor"
#pragma resource "*.dfm"
TTankDetailsForm2 *TankDetailsForm2;
//---------------------------------------------------------------------------
__fastcall TTankDetailsForm2::TTankDetailsForm2(TComponent* Owner)
	: TChildForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTankDetailsForm2::PaintBox1Paint(TObject *Sender)
{
	PaintBox1->Canvas->Pen->Color = clBlack;
	POINT ShipShapePoints[]={
		{	150,	20   },
		{	400,	20   },
		{	500,	80   },
		{	500,   320   },
		{	400,   380   },
		{	150,   380   },
		{	 50,   320   },
		{	 50,    80   },
		{	150,	20   },
	};
	int MaxX = 550;
	int MaxY = 400;
	float XScale = float(PaintBox1->Width) /float(MaxX);
	float YScale = float(PaintBox1->Height) /float(MaxY);
	int NumberOfElements =  NELEMENTS(ShipShapePoints);
	for(int i=0; i < NumberOfElements; i++){
		ShipShapePoints[i].x *= XScale;
		ShipShapePoints[i].y *= YScale;
	}
	PaintBox1->Canvas->Polygon((TPoint*)ShipShapePoints, NumberOfElements-1);


}
//---------------------------------------------------------------------------


void __fastcall TTankDetailsForm2::Timer1Timer(TObject *Sender)
{
	PaintBox1->Refresh();
}
//---------------------------------------------------------------------------

