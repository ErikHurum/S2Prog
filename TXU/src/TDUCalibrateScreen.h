#pragma once
class TDUCalibrateScreen:public TDUBasicWin
{
private:
    int aPhysX[2], aPhysY[2], aLogX[2], aLogY[2];
    int CalCnt;
		time_t ExitDelay;
	BUTTON_Handle CloseButton;
  //static void CalibrationMessage(int LogX, int LogY, const char * pString);
  //static void DispStringCentered(const char * pString);
public:
	TDUCalibrateScreen(void);
	~TDUCalibrateScreen(void);

  void Exec(void);

	static void cbEventHandler(WM_MESSAGE* pMsg);

};
