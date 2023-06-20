#include "TDUIncludes.h"
//#include "TDU_Touch_Calibrate.c"



/*********************************************************************
*
*       _DispStringCentered
*
* Purpose:
*   Shows the given text horizontally and vertically centered
*/
static void DispStringCentered(const char *pString) {
    GUI_RECT Rect;
    Rect.x0 = Rect.y0 = 0;
    Rect.x1 = LCD_GetXSize() - 1;
    Rect.y1 = LCD_GetYSize() - 1;
    GUI_DispStringInRect( pString, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER );
}

/*********************************************************************
*
*       _GetPhysValues
*
* Purpose:
*   Asks the user to press the touch screen at the given position
*   and returns the physical A/D values
*/
static void CalibrationMessage(int LogX, int LogY, const char *pString) {
    GUI_RECT Rect;
    int      FontSizeY,
             Align;
    FontSizeY = GUI_GetFontSizeY();
    GUI_Clear();
    GUI_SetColor( GUI_BLACK );
    DispStringCentered( FindDictionaryWord( L_WORD570 ).c_str() ); // Runtime calibration,\n please touch the screen\n at the center of the ring.")
    /* Calculate the rectangle for the string */
    Rect.y0 = LogY - FontSizeY;
    Rect.y1 = LogY + FontSizeY;
    if (LogX < LCD_GetXSize() / 2) {
        Rect.x0 = LogX + 15;
        Rect.x1 = LCD_GetXSize();
        Align = GUI_TA_LEFT;
    } else {
        Rect.x0 = 0;
        Rect.x1 = LogX - 15;
        Align = GUI_TA_RIGHT;
    }
    /* Show the text nearby the ring */
    GUI_DispStringInRect( FindDictionaryWord( L_WORD572 ).c_str(), &Rect, Align | GUI_TA_TOP );
    GUI_DispStringInRect( pString, &Rect, Align | GUI_TA_BOTTOM );
    /* Draw the ring */
    GUI_FillCircle( LogX, LogY, 10 );
    GUI_SetColor( GUI_WHITE );
    GUI_FillCircle( LogX, LogY, 3 );
    GUI_SetColor( GUI_BLACK );
}

TDUCalibrateScreen::~TDUCalibrateScreen(void) {
}

const GUIKey Words[ ] = {
    {CLOSE_BUT_ID_CALIBRATE	,0,L_WORD571 },
};

TDUCalibrateScreen::TDUCalibrateScreen(void) {
    GUI_TOUCH_SetDefaultCalibration();
    CalCnt = 0;
    aLogX[0] = 15;
    aLogY[0] = 15;
    aLogX[1] = LCD_GetXSize() - 15;
    aLogY[1] = LCD_GetYSize() - 15;
    ExitDelay = time( NULL );

    WinHandl  = WM_CreateWindow( 0, 0, LCDXSize, LCDYSize, WM_CF_SHOW, NULL, 0 );
    CloseButton = BUTTON_CreateAsChild( 250, 50, 60, 22, WinHandl, CLOSE_BUT_ID_CALIBRATE, WM_CF_SHOW );
    BUTTON_SetText( CloseButton, "Abort" );
    AddToSKeyList( (GUIKey *)Words, NELEMENTS( Words ) );
    WM_SetCallback( WinHandl, cbEventHandler );
}

void TDUCalibrateScreen::Exec(void) {
    CalCnt = 0;
}

void TDUCalibrateScreen::cbEventHandler(WM_MESSAGE *pMsg) {

//	int NCode, Id;
    switch (pMsg->MsgId) {
    case WM_PAINT:
        GUI_SetBkColor( TDU_C_CALIBRATE_BACK ); GUI_Clear();
        GUI_SetColor( TDU_C_CONF_TEXT );
        GUI_SetTextMode( GUI_TM_TRANS );
        GUI_SetFont( &GUI_Font13_1 );
        CalibrateScreen->UpdateLanguage();

        switch (CalibrateScreen->CalCnt) {
        case 0:
            CalibrationMessage( CalibrateScreen->aLogX[0], CalibrateScreen->aLogY[0], FindDictionaryWord( L_WORD573 ).c_str() ); // _acPos[0]);
            break;
        case 1:
            CalibrationMessage( CalibrateScreen->aLogX[1], CalibrateScreen->aLogY[1], FindDictionaryWord( L_WORD574 ).c_str() ); //_acPos[1]);
            break;
        case 2:
            /* Display the result */
            //GUI_CURSOR_Show();
            GUI_Clear();
            MainWindow->SetPreviousWindow();
            CalibrateScreen->CalCnt = 3;
            break;
        case 3:
            // Exit, do nothing
            break;
        }
        break;
    case WM_CREATE:
        {
            GUI_SetBkColor( TDU_C_CALIBRATE_BACK ); GUI_Clear();
        }
        break;
    case WM_TOUCH:
        {
            GUI_PID_STATE State;
            /* Wait until touch is pressed */
            GUI_TOUCH_GetState( &State );
            if (State.Pressed == 1) {
                if (CalibrateScreen->CalCnt == 0) {
                    // Check the position. Seems reasonable??
                    if (( State.x < CalibrateScreen->aLogX[0] + 30 ) && ( State.y < CalibrateScreen->aLogY[0] + 80 )) {
                        CalibrateScreen->CalCnt = 1;
                        CalibrateScreen->aPhysX[0] = GUI_TOUCH_GetxPhys();
                        CalibrateScreen->aPhysY[0] = GUI_TOUCH_GetyPhys();
                        WM_Paint( CalibrateScreen->WinHandl );
                    }
                } else if (CalibrateScreen->CalCnt == 1) {
                    // Check the position. Seems reasonable??
                    if (( State.x > CalibrateScreen->aLogX[1] - 15 ) && ( State.y > CalibrateScreen->aLogY[1] - 15 )) {
                        CalibrateScreen->CalCnt = 2;
                        CalibrateScreen->aPhysX[1] = GUI_TOUCH_GetxPhys();
                        CalibrateScreen->aPhysY[1] = GUI_TOUCH_GetyPhys();
                        /* Use the physical values to calibrate the touch screen */
                        GUI_TOUCH_Calibrate( 0, CalibrateScreen->aLogX[0], CalibrateScreen->aLogX[1], CalibrateScreen->aPhysX[0], CalibrateScreen->aPhysX[1] );   /* Calibrate X-axis */
                        GUI_TOUCH_Calibrate( 1, CalibrateScreen->aLogY[0], CalibrateScreen->aLogY[1], CalibrateScreen->aPhysY[0], CalibrateScreen->aPhysY[1] );   /* Calibrate Y-axis */
#ifdef S2TXU
                       // WriteLocalSettings();
#endif
                        BUTTON_SetText( CalibrateScreen->CloseButton, FindDictionaryWord( L_WORD18 ).c_str() ); // Close
                        WM_Paint( CalibrateScreen->WinHandl );
                        CalibrateScreen->ExitDelay = time( NULL );
                    }
                } else if (CalibrateScreen->CalCnt == 2) {
                    MainWindow->SetPreviousWindow();
                }
            }
        }
        break;
    case WM_NOTIFY_PARENT:
        {
            int NCode, Id;
            Id    = WM_GetId( pMsg->hWinSrc );        /* Id of widget */
            NCode = pMsg->Data.v;                               /* Notification code */
            switch (NCode) {
            case WM_NOTIFICATION_RELEASED:  /* React only if released */
//				case WM_NOTIFICATION_CLICKED:   /* React only if pressed */
                {
                    switch (Id) {
                    case CLOSE_BUT_ID_CALIBRATE:
                        MainWindow->SetPreviousWindow();
                        CalibrateScreen->CalCnt = 3;
                        break;
                    }
                }
                break;
            }
        }
        break;
    default:
        WM_DefaultProc( pMsg );
    }
}
