#include "TDUIncludes.h"

TDUTempGraphWin::~TDUTempGraphWin(void)
{
}

const GUI_POINT XLine[] = {
{  0,  0},
{    0, 160}, {    0, 165}, {    0, 160},
{   10, 160}, {   10, 165}, {   10, 160},
{   20, 160}, {   20, 165}, {   20, 160},
{   30, 160}, {   30, 165}, {   30, 160},
{   40, 160}, {   40, 165}, {   40, 160},
{   50, 160}, {   50, 165}, {   50, 160},
{   60, 160}, {   60, 165}, {   60, 160},
{   70, 160}, {   70, 165}, {   70, 160},
{   80, 160}, {   80, 165}, {   80, 160},
{   90, 160}, {   90, 165}, {   90, 160},
{  100, 160}, {  100, 165}, {  100, 160},
{  110, 160}, {  110, 165}, {  110, 160},
{  120, 160}, {  120, 165}, {  120, 160},
{  130, 160}, {  130, 165}, {  130, 160},
{  140, 160}, {  140, 165}, {  140, 160},
{  150, 160}, {  150, 165}, {  150, 160},
{  160, 160}, {  160, 165}, {  160, 160},
{  170, 160}, {  170, 165}, {  170, 160},
{  180, 160}, {  180, 165}, {  180, 160},
{  190, 160}, {  190, 165}, {  190, 160},
{  200, 160}, {  200, 165}, {  200, 160},
{  200, 160},			
};
const GUI_POINT YLine[] = {
{  0,  0},
{  0,   0}, {  5,   0}, {  0,   0},
{  0,  10}, {  5,  10}, {  0,  10},
{  0,  20}, {  5,  20}, {  0,  20},
{  0,  30}, {  5,  30}, {  0,  30},
{  0,  40}, {  5,  40}, {  0,  40},
{  0,  50}, {  5,  50}, {  0,  50},
{  0,  60}, {  5,  60}, {  0,  60},
{  0,  70}, {  5,  70}, {  0,  70},
{  0,  80}, {  5,  80}, {  0,  80},
{  0,  90}, {  5,  90}, {  0,  90},
{  0, 100}, {  5, 100}, {  0, 100},
{  0, 110}, {  5, 110}, {  0, 110},
{  0, 120}, {  5, 120}, {  0, 120},
{  0, 130}, {  5, 130}, {  0, 130},
{  0, 140}, {  5, 140}, {  0, 140},
{  0, 150}, {  5, 150}, {  0, 150},
{  0, 160}
};
const GUI_POINT aPoints[] = {
{  0, 20},
{ 10, 25},
{ 20, 30},
{ 30, 35},
{ 40, 20},
{ 50, 22},
{ 60, 31},
{ 70, 26},
{ 80, 18},
{ 90, 15},
};

//	static I16 aY[100];

TDUTempGraphWin::TDUTempGraphWin(void)
{
//	hFramWin = FRAMEWIN_CreateAsChild( 0, 0, 286, 198, TempWindow->WinHandl, "Graph", cbEventHandler,WM_CF_SHOW);
//	hFramWin = FRAMEWIN_Create( "Graph", cbEventHandler, 0, 0, 0, 286, 198);
}

void TDUTempGraphWin::ExecTempGraph(void)
{
	hFramWin = FRAMEWIN_CreateAsChild( 0, 0, 286, 198, TempWindow->WinHandl, "Temperature graph", cbEventHandler,WM_CF_SHOW);
	int i;
//	for (i = 0; i < GUI_COUNTOF(aY); i++) {
	for (i = 0; i < 200; i++) {
		//aY[i] = rand() % 50;
	}
}

void TDUTempGraphWin::cbEventHandler(WM_MESSAGE * pMsg)
{
	//WM_HWIN hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		case WM_NOTIFY_PARENT:
		{
			int NCode;//, Id;
			//Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch (NCode)
			{
				case WM_NOTIFICATION_RELEASED:    /* React only if released */
//				case WM_NOTIFICATION_CLICKED:
				{
//					UserTouch = true;
				}
				break;
			}
		}
		break;
		case WM_PAINT:
			GUI_SetBkColor(TDU_C_BACK_DEFAULT);
			GUI_Clear();
			GUI_SetColor(TDU_C_TEXT_DEFAULT);

			GUI_DrawPolyLine(XLine, GUI_COUNTOF(XLine), 10,10);
			GUI_DrawPolyLine(YLine, GUI_COUNTOF(YLine), 10,10);

		//	GUI_DrawGraph(aY, GUI_COUNTOF(aY), 10, 10);
			GUI_SetLineStyle(GUI_LS_DOT);
			GUI_DrawPolyLine(aPoints, GUI_COUNTOF(aPoints), 10, 10);
		break;
		case WM_CREATE:
		break;
		default:
			WM_DefaultProc(pMsg);
  }
}

