#pragma once

class TDUMultipageTankDetails : public TDUBasicWin {
private:
    static unsigned IdSet1[];
    static unsigned IdSet2[];
    static unsigned IdSet3[];
    static unsigned IdSet4[];
    static unsigned IdSet5[];
    WM_HWIN hMultiPage, hFrameWin, hDialog;
// Dialog1
    WM_HWIN hButApplyDensity, hRadioLinAPI;
    WM_HWIN hCheckMeasDens, hTextMeasDens;
    //API
    WM_HWIN hTextAPI, hTextAPI1, hTextAPI2, hTextAPI1Unit, hTextAPI2Unit;
    WM_HWIN hDropdAPI, hEditAPI1, hEditAPI2;
    //Linear
    WM_HWIN hTextLin, hCheckLin;
    WM_HWIN hEditSimDens, hTextSimDens, hTextSimDensUnit;
    WM_HWIN hTextRef1, hTextRef2, hTextCoeff;
    WM_HWIN hEditTemp1, hEditTemp2, hEditDens1, hEditDens2, hEditCoeff;
    WM_HWIN hTextTemp1Unit, hTextTemp2Unit, hTextDens1Unit, hTextDens2Unit, hTextCoeffUnit;

// Dialog2
    WM_HWIN hButApplyAlarm;
    WM_HWIN hButUnlock2;
    WM_HWIN hOverfill, hHighLev, hLowLev, hHighTemp, hLowTemp, hHighPress, hLowPress;
    WM_HWIN hEditOverfill, hEditHighLev, hEditLowLev, hEditHighTemp, hEditLowTemp, hEditHighPress, hEditLowPress;
    WM_HWIN hTextOverfill, hTextHighLev, hTextLowLev, hTextHighTemp, hTextLowTemp, hTextHighPress, hTextLowPress;
    WM_HWIN hCheckOverfill,hCheckHighLev,hCheckLowLev,hCheckHighTemp,hCheckLowTemp,hCheckHighPress,hCheckLowPress;
// Dialog3
    WM_HWIN hButZeroPress, hButZeroLevel,hButUnlock3,
    hButLevelAdj,hButSoundingAdj,hButUllageAdj,hButUTIUllageAdj, hButVolumeAdj,hButWeightAdj;
// Dialog4
    WM_HWIN hButUnlock4;
    WM_HWIN hTextSnsLoc1, hTextSnsLoc2, hTextSnsLoc3, hTextSnsLoc4, hTextSnsLoc5;
    WM_HWIN hTextSnsUnit1, hTextSnsUnit2, hTextSnsUnit3, hTextSnsUnit4, hTextSnsUnit5;
    WM_HWIN hEditSnsGain1, hEditSnsGain2, hEditSnsGain3, hEditSnsGain4, hEditSnsGain5;
    WM_HWIN hEditSnsOffset1, hEditSnsOffset2, hEditSnsOffset3, hEditSnsOffset4, hEditSnsOffset5;
    WM_HWIN hEditSnsValue1, hEditSnsValue2, hEditSnsValue3, hEditSnsValue4, hEditSnsValue5;
    WM_HWIN hCheckSnsEna1, hCheckSnsEna2, hCheckSnsEna3, hCheckSnsEna4, hCheckSnsEna5;

// Dialog5
    WM_HWIN hButUnlock5;
    WM_HWIN hTextLevOffset    , hEditLevOffset    , hTextLevOffsetU;
    WM_HWIN hTextTabOffset    , hEditTabOffset    , hTextTabOffsetU;
    WM_HWIN hTextExpFactOffset, hTextExpFactOffsetU, hEditExpFactOffset;
    vector<PRogramObjectBase *>CurrentListPtr;
    void DisableLevelAdjustButtons(void);
    void EnableLevelAdjustButtons(void);
    void DisableLevelMeasuredDnsCheckBox(void);
    void EnableOrDisableAllControls(void);
    void EnableOrDisableAlarmSettingsControls(bool notLocked, bool LockedByConfig);

    //void StartLockTimer(WM_HWIN hDlg);


     bool alarmSettingsLocked;           // if true then alarm settings can be locked, otherwise they cannot ever be locked

public:
    TDUMultipageTankDetails(void);
    ~TDUMultipageTankDetails(void);
//  PRogramObject *CurrentPROPtr;
    PRogramObject *CurrentPROPtr;
    bool Closed;
    static const GUI_WIDGET_CREATE_INFO aDialogCreate1[];
    static const GUI_WIDGET_CREATE_INFO aDialogCreate2[];
    static const GUI_WIDGET_CREATE_INFO aDialogCreate3[];
    static const GUI_WIDGET_CREATE_INFO aDialogCreate4[];
    static const GUI_WIDGET_CREATE_INFO aDialogCreate5[];
    //static const GUI_WIDGET_CREATE_INFO aDialogCreate5[];
    //static const GUI_WIDGET_CREATE_INFO aDialogCreate6[];
    static void cbDialog1(WM_MESSAGE *pMsg);
    static void cbDialog2(WM_MESSAGE *pMsg);
    static void cbDialog3(WM_MESSAGE *pMsg);
    static void cbDialog4(WM_MESSAGE *pMsg);
    static void cbDialog5(WM_MESSAGE *pMsg);
    //static void cbDialog5(WM_MESSAGE * pMsg);
    //static void cbDialog6(WM_MESSAGE * pMsg);
    static void cbFrameWin(WM_MESSAGE *pMsg);
    void CreateMultiPage(WM_HWIN hCurrentWin, PRogramObject *PROPtr);
    void Update(void);
// Dialog1
    void GetDialog1Handles(void);
    void InitDialog1(void);
    void UseAPI(void);
    void UseLinear(void);
    void UpdateDialog1(void);
    void SetNewValueDialog1(int key, AnsiString ValueString);
    void SetAllNewValueDialog1(void);
// Dialog2
    void GetDialog2Handles(void);
    void InitDialog2(void);
    void UpdateDialog2(void);
    void SetNewValueDialog2(int key, AnsiString ValueString);
    void SetAllNewValueDialog2(void);
// Dialog3
    void GetDialog3Handles(void);
    void InitDialog3(void);
    void UpdateDialog3(void);
    void SetNewValueDialog3(int key, AnsiString ValueString);
// Dialog4
    void GetDialog4Handles(void);
    void InitDialog4(void);
    void UpdateDialog4(void);
    void SetNewValueDialog4(int key, AnsiString ValueString);

// Dialog5
    void GetDialog5Handles(void);
    void InitDialog5(void);
    void UpdateDialog5(void);
    void SetNewValueDialog5(int key, AnsiString ValueString);
};
