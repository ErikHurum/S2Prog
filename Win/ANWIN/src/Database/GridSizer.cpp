//---------------------------------------------------------------------------

#pragma hdrstop

#include "GridSizer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

///
///
///
void GridSizer::MakeGridColumnFillEmptySpace(TDrawGrid* gridPtr, int colNum, int minColWidth)
{

	int otherColWidths = 0;

	// determine the width of the columns other than the one we are resizing:
	for (int i = 0; i < gridPtr->ColCount; i++) {
		if (i != colNum) {
			otherColWidths += gridPtr->ColWidths[i] + gridPtr->GridLineWidth;
		}
	}
	// determine what width the column we are resizing needs:
	int newColWidth = gridPtr->ClientWidth - otherColWidths - gridPtr->GridLineWidth;

	if (newColWidth < minColWidth) {
		newColWidth = minColWidth;
	}
	gridPtr->ColWidths[colNum] = newColWidth;
}
