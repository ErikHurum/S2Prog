#include "TDUIncludes.h"



TDUTankCleaningWin::TDUTankCleaningWin(void)
{
	countTimerTicks = 0;
	
	CreateTankButtonGrid();

	ResetWinRefreshTimer(UI_Refresh_Timer_First_Wait_Secs);
}


TDUTankCleaningWin::~TDUTankCleaningWin(void)
{
}


/// Virtual method declared in class TDUPresentWin
void TDUTankCleaningWin::SetButton(void)
{
	bool Enable[NUMBER_OF_BUTTONS]={
		(bool)(NumberOfPages>1),
		(bool)(NumberOfPages>1),
		false,
		(bool)!PROPrinter::ObjectSet.empty(),
		false
	};
	ButWindow->EnableButtons(Enable);

	if (!PROTank::TankVector.empty())
	{
		ButWindow->ChangeButtonText(L_WORD87,L_WORD88,L_WORD89,L_WORD237,L_WORD90);
	} 
}


void TDUTankCleaningWin::ButtonClicked(int btnID)
{
	switch ( btnID ) {
	case TDU_BUTTON_ID_PW1:
		if ( CurrentPage <= 0 ) {
			CurrentPage = 0;
		} else {
			CurrentPage--;
		}
		MoveWin();
		break;
	case TDU_BUTTON_ID_PW2:
		if ( CurrentPage >= (NumberOfPages-1) ) {
			CurrentPage = (NumberOfPages-1);
		} else {
			CurrentPage++;
		}
		MoveWin();
		break;
	}

}


void TDUTankCleaningWin::MoveWin(void)
{
	int y =  -CurrentPage * PWinYSize;
	WM_MoveChildTo(MainWinHandle, 0, y);
}


void TDUTankCleaningWin::UnitClicked(WM_HWIN hWin,int btnHandle)
{
	PROTank *pTank = FindTankByButtonHandle(btnHandle);

	// Use tank 
	if (pTank != NULL)
	{
		TankCleaningDetailsWindow->SetTankToDisplay(pTank);
		MainWindow->SetWindow(TDU_TANK_CLEANING_DETAILS_WIN);

		TankCleaningDetailsWindow->TableUpdate();
		WM_InvalidateWindow(TankCleaningDetailsWindow->WinHandl);	
	}
}


void TDUTankCleaningWin::cbEventHandler(WM_MESSAGE* pMsg)
{
	WM_HWIN hWin = pMsg->hWin;

	switch ( pMsg->MsgId ) {
	case WM_PAINT:
		//Protect();
		GUI_SetBkColor(TDU_C_BACK_DEFAULT);
		GUI_Clear();
		GUI_SetColor(TDU_C_PW_TEXT);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_SetFont(&TDU_FONT_BIG);
		UpdateFields(true);
		
		if (countTimerTicks > 0)								// Changing gui element colors etc too early will crash the program..
		{
			UpdateButtonColors();
		}
		//UnProtect();
		break;
	case WM_CREATE:
		break;
	case WM_TIMER:
		if (pMsg->Data.v == hTimer)
		{
			WM_InvalidateWindow(MainWinHandle);					// schedule redrawing of this window
			ResetWinRefreshTimer(UI_Refresh_Timer_Interval_Secs);
			countTimerTicks++;
		}
		break;
	case WM_NOTIFY_PARENT:
		{
			int ncode, handle;
			handle = pMsg->hWinSrc;							// Id of widget
			ncode = pMsg->Data.v;							// Notification code
			if (ncode == WM_NOTIFICATION_CLICKED)			//WM_NOTIFICATION_RELEASED)
			{
				UnitClicked(hWin, handle);
			}
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}



/// Static function EventLoopTankCleaningWindow
void TDUTankCleaningWin::EventLoopTankCleaningWindow(WM_MESSAGE * pMsg)
{
	// Route events to the tank cleaning window or just let the base system handle it
	switch ( pMsg->MsgId ) {
	case WM_PAINT:
	case WM_CREATE:
	case WM_NOTIFY_PARENT:
	case WM_TIMER:
		if (TankCleaningWindow != NULL)
		{
			TankCleaningWindow->cbEventHandler(pMsg);
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}



PROTank* TDUTankCleaningWin::FindTankByButtonHandle(BUTTON_Handle handle)
{
	PROTank *pTank = NULL;
	vector<TDUTankCleaningWin_ButtonToTankMapping>::iterator iter = tankMapVector.begin();

	// Get a pointer to the tank that was clicked
	for (; iter != tankMapVector.end(); iter++)
	{
		if (handle == (*iter).btnHandle)
		{
			pTank = (*iter).pTank;
			break;
		}
	}
	return pTank;
}



void TDUTankCleaningWin::ResetWinRefreshTimer(int seconds)
{
	int updateTimeMillis = seconds * 1000;

	if (hTimer == 0)
	{
		hTimer = WM_CreateTimer(MainWinHandle, UI_Refresh_Timer_UserId, updateTimeMillis, 0);
	}
	else
	{
		WM_RestartTimer(hTimer, updateTimeMillis);
	}
}



void TDUTankCleaningWin::UpdateButtonColors(void)
{
	vector<TDUTankCleaningWin_ButtonToTankMapping>::iterator it = tankMapVector.begin();
	vector<TDUTankCleaningWin_ButtonToTankMapping>::iterator end = tankMapVector.end();

	for (;it != end; it++)
	{
		TDUTankCleaningWin_ButtonToTankMapping btm = *it;
		PROTank* pTank = btm.pTank;
		BUTTON_Handle btnHandle = btm.btnHandle;

		if (pTank != NULL)
		{
			bool washRunning = TankWashingAPI::GetPROTankWashingStatus(pTank);

			if (washRunning)
			{
				BUTTON_SetBkColor(btnHandle, BUTTON_CI_UNPRESSED, UI_Button_Running_Tank_Color);
			}
			else
			{
				BUTTON_SetBkColor(btnHandle, BUTTON_CI_UNPRESSED, UI_Button_Idle_Tank_Color);
			}
		}
	}
}


void TDUTankCleaningWin::CreateTankButtonGrid(void)
{
	// Build up a grid of pointers to TWM objects. We'll use this to figure out how to place elements on the screen:
	vector< vector< vector< PROTank* > > > tankGrid;		// levels: page, row, column
	unsigned maxCol = 0;									// Essentially gives the number of columns of the whole tank grid

	vector<PROTank*>::iterator tankIter = PROTank::TankVector.begin();
	vector<PROTank*>::iterator tankEnd = PROTank::TankVector.end();
	
	for (;tankIter != tankEnd; tankIter++)
	{
		PROTank *pTank = *tankIter;
		if (pTank->TankWashingMachineVector.empty() == false)
		{
			unsigned row = pTank->TDUTankPlacement.ypos;
			unsigned col = pTank->TDUTankPlacement.xpos;
			unsigned page = pTank->TDUTankPlacement.page;

			if ((page+1) > tankGrid.size())					// Add a page if necessary
			{
				tankGrid.resize(page+1);
			}
						
			if (row >= tankGrid[page].size())				// Add row on this page if necessary
			{
				tankGrid[page].resize( row+1 );
			}

			if (col >= tankGrid[page][row].size())			// Add columns if necessary
			{
				tankGrid[page][row].resize(col+1, NULL);

				if (col > maxCol)
				{
					maxCol = col;
				}
			}

			tankGrid[page][row][col] = pTank;
		}
	}
	

	// Do calculations. You can change these constants to alter the positioning of buttons:
	const int minStartY = 8;
	const int minStartX = 8;
	const int btnWidth = 40;
	const int btnHeight = 30;
	const int btnSpacingHoriz = 5;
	const int btnSpacingVert = 5;
	const int screenCenterX = PWinXSize / 2 - 18;
	const int screenCenterY = PWinYSize / 2;

	// May be necessary with multiple pages:
	NumberOfPages = tankGrid.size();
	CurrentPage = 0;

	// Create window controls/widgets
	MainWinHandle = WM_CreateWindowAsChild(  0, 0, PWinXSize, PWinYSize * NumberOfPages,  WinHandl, WM_CF_SHOW, TDUTankCleaningWin::EventLoopTankCleaningWindow, 0);
	WM_EnableMemdev(MainWinHandle);

	int tankCount = 0;
	int tankButtonId = TDU_TANK_CLEANING_BUTTON_0_ID;
	

	for (unsigned pageCount = 0; pageCount < tankGrid.size(); pageCount++)
	{
		unsigned numRowsOnPage = tankGrid[pageCount].size();
		int pageGridHeight = (btnHeight * numRowsOnPage) + (btnSpacingVert * (numRowsOnPage-1));
		int pageGridWidth = (btnWidth * maxCol) + (btnSpacingHoriz * (maxCol-1));

		int startX = screenCenterX - (pageGridWidth / 2);		
		int drawPosY = (pageCount * PWinYSize) + (screenCenterY - pageGridHeight / 2);

		if (startX < minStartX)
		{
			startX = minStartX;
		}
		if (drawPosY < minStartY)
		{
			drawPosY = minStartY;
		}
	
		
		// Draw buttons representing tanks:
		for (unsigned rowDraw = 0; rowDraw < tankGrid[pageCount].size(); rowDraw++)
		{
			int drawPosX = startX;

			for (unsigned colDraw = 0; colDraw < tankGrid[pageCount][rowDraw].size(); colDraw++)
			{
				if (tankGrid[pageCount][rowDraw][colDraw] != NULL)
				{
					// Create button representing a cargo tank:
					PROTank *pTank = tankGrid[pageCount][rowDraw][colDraw];
					BUTTON_Handle btnHandle = BUTTON_CreateEx(drawPosX, drawPosY, btnWidth, btnHeight, MainWinHandle, WM_CF_SHOW, 0, tankButtonId);
					BUTTON_SetBkColor(btnHandle, 0, UI_Button_Idle_Tank_Color); 
					BUTTON_SetText(btnHandle, tankGrid[pageCount][rowDraw][colDraw]->Name.c_str() );

					// Store info about the button created. Need to remember which tank it represents, for later use:
					int btnId = WM_GetId(btnHandle);
					TDUTankCleaningWin_ButtonToTankMapping btnMapTank(btnHandle, pTank);
					tankMapVector.push_back(btnMapTank);
				
					tankCount++;
					tankButtonId++;
				}
				// Advance to drawing the next button to the right
				drawPosX += btnWidth + btnSpacingHoriz;
			}

			// Advance to drawing the next row
			drawPosY += btnHeight + btnSpacingVert;
		}
	}
}

