//---------------------------------------------------------------------------

#ifndef GridSizerH
#define GridSizerH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>


//---------------------------------------------------------------------------

class GridSizer
{
public:
	static void MakeGridColumnFillEmptySpace(TDrawGrid* gridPtr, int colNum, int minColWidth = 65);
};

#endif
