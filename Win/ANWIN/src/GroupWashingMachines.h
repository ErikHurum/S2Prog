//---------------------------------------------------------------------------

#ifndef GroupWashingMachinesH
#define GroupWashingMachinesH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include "ChildUnit.h"
#include "GroupUnit.h"
#include "TSNIncludes.h"
#include "TankDetailsWashingMachines.h"
#include <Vcl.ExtCtrls.hpp>



using namespace std;

#define TGroupTableWashingMachines_StringColWidth 80


enum TGroupTableWashingMachines_Columns { GTWMC_TankName, GTWMC_WashStatus, GTWMC_Messages,  GTWMC_TimeElapsed };

typedef vector<TGroupTableWashingMachines_Columns> ColumnOrderVector_t;


/// The CargoTankSpecifier class is used withing the washing machines
/// group table for identifying a cargo tank in the list of tanks
/// with washing machine
///
class CargoTankSpecifier : public TObject
{
public:
	inline CargoTankSpecifier(PROTank* tankPtr)
		: TObject()
	{
		CargoTankPtr = tankPtr;
	}

	PROTank* CargoTankPtr;

	TankWashingMachineRun_Statuses tankWashStatus;
	double washStartTime;
	double washEndTime;

};

typedef vector<CargoTankSpecifier*> CargoTankSpecifierVector_t;

//---------------------------------------------------------------------------
class TGroupTableWashingMachines : public TChildForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TStringGrid *CargoTanksGrid;
	TTimer *RowUpdateTimer;
	void __fastcall CargoTankGridClicked(TObject *Sender);
	void __fastcall OnFormResize(TObject *Sender);
	void __fastcall OnFormPaint(TObject *Sender);
	void __fastcall OnRowUpdateTimerTick(TObject *Sender);
	void __fastcall CargoTankGridDblClick(TObject *Sender);

private:	// User declarations
	/// ctsVector is used for making sure cts objects are deleted properly in the destructor
	CargoTankSpecifierVector_t ctsVector;
	ColumnOrderVector_t columnOrderVector;
	int updateCount;
	int fullUpdateEveryN;

	bool mustResizeGrid;
	bool mustRefreshAllData;
	bool mustRefreshElapsedTime;

	void __fastcall InitializeGridColumns();
	void __fastcall RefreshAllData();
	void __fastcall RefreshElapsedTimeColumn();

	void __fastcall FreeCargoTankSpecifiers();

public:		// User declarations
	__fastcall TGroupTableWashingMachines(TComponent* Owner);
	__fastcall ~TGroupTableWashingMachines();
};
//---------------------------------------------------------------------------
extern PACKAGE TGroupTableWashingMachines *GroupTableWashingMachines;
//---------------------------------------------------------------------------
#endif
