// ---------------------------------------------------------------------------
#ifndef MainUnitH
#define MainUnitH
#include "ChildUnit.h"
#include "nrclasses.hpp"
#include "nrcomm.hpp"
#include "nrdataproc.hpp"
#include <IdAntiFreezeBase.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdContext.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdHTTPServer.hpp>
#include <IdIPWatch.hpp>
#include <IdSocketHandle.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdUDPServer.hpp>
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.IdAntiFreeze.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Buttons.hpp>
#include "nrsocket.hpp"
#include "nrsemaphore.hpp"
#include <IdGlobal.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <System.ImageList.hpp>
#include <IdScheduler.hpp>
#include <IdSchedulerOfThread.hpp>
#include <IdSchedulerOfThreadDefault.hpp>
#include <System.SysUtils.hpp>

#include "Anpro_Net.h"
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "LiteCall.hpp"
#include "LiteConsts.hpp"
#include "MemDS.hpp"
#include "DAScript.hpp"
#include "LiteScript.hpp"
#include <IdAntiFreeze.hpp>
#include "RzStatus.hpp"
#include "RzTreeVw.hpp"
#include "nrterminal.hpp"
#include "AdvLabel.hpp"
#include "AdvReflectionLabel.hpp"
#include "GradientLabel.hpp"
#include "AdvMenus.hpp"
#include "AdvMenuStylers.hpp"
#include "asgprint.hpp"
#include <VCLTee.Chart.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.TeeData.hpp>
#include <VCLTee.TeeDBCrossTab.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "DBAdvGrid.hpp"
#include <Vcl.Graphics.hpp>
#include <Vcl.Grids.hpp>
#include <VCLTee.Series.hpp>
#include "AdvSmoothSplashScreen.hpp"
#include "PictureContainer.hpp"
#include <Vcl.XPMan.hpp>
//#include "nrlogfile.hpp"
/*
#include <System.Actions.hpp>
#include <System.Win.TaskbarCore.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.CustomizeDlg.hpp>
#include <Vcl.Taskbar.hpp>
#include <Vcl.XPMan.hpp>
*/
// ---------------------------------------------------------------------------
#include "DataLogThreadUnit.h"
#include "SensorLogThreadUnit.h"
#include "AdvProgr.hpp"
#include "AdvProgressBar.hpp"
#include "W7Classes.hpp"
#include "W7ProgressBars.hpp"

// ---------------------------------------------------------------------------
class TMainForm : public TForm {
__published: // IDE-managed Components
    TToolBar *ToolBar2;
    TPanel *Panel1;
    TPanel *AlarmPanel;
    TPanel *TrimPanel;
    TLabel *TrimUnit;
    TLabel *TrimValue;
	TLabel *Label1;
    TPanel *ListPanel;
    TLabel *ListUnit;
    TLabel *ListValue;
    TLabel *Label2;
    TPanel *DraftPanel;
    TLabel *DraftValue;
    TLabel *DraftUnit;
    TLabel *Label3;
	TPanel *SystemPanel;
    TPanel *OpModePanel;
    TLabel *Label4;
    TOpenDialog *OpenDialog;
	TTimer *UpdateHeadingTimer;
    TTimer *StartupTimer;
    TPrinterSetupDialog *PrinterSetupDialog1;
	TTimer *UpdateConfigFileTimer;
    TToolButton *ToolButtonCargo;
    TImageList *ImageList2;
    TToolButton *ToolButtonBallast;
    TToolButton *ToolButtonService;
    TTimer *AlarmTimer;
    TTimer *Midas1ExportTimer;
    TIdUDPClient *IdUDPClient1;
    TIdUDPServer *IdUDPServer1;
    TIdIPWatch *IdIPWatch;
    TIdTCPServer *IdTCPServer1;
    TIdTCPClient *IdTCPClient1;
    TIdTCPServer *PVCSTCPServer;
    TIdTCPServer *PVCSAlarmServer;
    TTimer *NetReceiveRestartTimer;
	TTimer *DelayedRunTimer;
    TIdHTTPServer *HTTMLServer;
    TPanel *DisplacementPanel;
    TLabel *DisplacementValue;
    TLabel *DisplacementUnit;
    TLabel *Label7;
    TComboBox *OpModeComboBox;
    TTimer *ExitTimeoutTimer;
    TnrComm *nrComm1;
    TnrDataProcessor *nrDataProcessor1;
	TIdAntiFreeze *IdAntiFreeze1;
	TLabel *AlarmLabel;
	TLabel *SystemOKLabel;
	TToolButton *ToolButtonTankPressure;
	TToolButton *ToolButtonTemp;
	TToolButton *ToolButtonLinePressure;
	TToolButton *DraftToolButton;
	TToolButton *ToolButton1;
	TToolButton *ToolButtonWashTrack;
	TToolButton *ToolButtonLoadCalc;
	TPanel *ComStatusPanel;
	TnrSemaphore *nrSemaphore1;
	TLiteConnection *WashTrackLiteConnection;
	TLiteConnection *AlarmLogLiteConnection;
	TRzTreeView *RzTreeView1;
	TSplitter *Splitter1;
	TnrComm *HattelandSCOM;
	TTimer *ExplorerExecuteDelayTimer;
	TLabel *Label5;
	TLabel *FreeBoardValue;
	TLabel *FreeBoardUnit;
	TAdvMainMenu *MainMenu1;
	TMenuItem *File2;
	TMenuItem *Communicationsetup1;
	TMenuItem *Printsetup1;
	TMenuItem *System2;
	TMenuItem *Units2;
	TMenuItem *Window2;
	TMenuItem *Help2;
	TMenuItem *Help3;
	TMenuItem *SysteminfoandSetup1;
	TMenuItem *SysteminfoandSetup2;
	TMenuItem *Hardwareinfo1;
	TMenuItem *Drafts1;
	TMenuItem *Drafts3;
	TMenuItem *SIuintset1;
	TMenuItem *USunitset1;
	TMenuItem *Userunitset1;
	TMenuItem *Setup1;
	TMenuItem *Cascade1;
	TMenuItem *Cascade2;
	TMenuItem *ileVertically1;
	TMenuItem *ileVertically2;
	TMenuItem *ArrangeAll1;
	TMenuItem *Styles;
	TMenuItem *ToolBarItem;
	TMenuItem *ImportExporttoBinnenmaat1;
	TMenuItem *Exit1;
	TMenuItem *N6;
	TMenuItem *Freewindow1;
	TAdvMenuStyler *AdvMenuStyler1;
	TLiteConnection *DataLogLiteConnection;
	TMenuItem *View1;
	TMenuItem *Protocols1;
	TLiteSQL *LiteSQLDataLog;
	TLiteQuery *LiteQueryDataLog;
	TMenuItem *DatalogMenuItem;
	TLiteQuery *LiteQueryCargoTypes;
	TLiteConnection *SensorLogLiteConnection;
	TLiteQuery *LiteQuerySensorLog;
	TAdvSmoothSplashScreen *AdvSmoothSplashScreen1;
	TMenuItem *Setup;
	TProgressBar *StaticDataAdvProgress;
	TLabel *UpdatingDatabaseLabel;
	TLiteQuery *LiteQueryAlarmLog;
	TTimer *AlarmLogCleanTimer;

    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FileExit1Execute(TObject *Sender);
    void __fastcall ComPortSetupClick(TObject *Sender);
	void __fastcall SIuintset2Click(TObject *Sender);
    void __fastcall Systeminfo1Click(TObject *Sender);
    void __fastcall Userunitset12Click(TObject *Sender);
    void __fastcall USunitset2Click(TObject *Sender);
    void __fastcall Printersetup1Click(TObject *Sender);
    void __fastcall Tankinfo1Click(TObject *Sender);
    void __fastcall HelpAbout1Execute(TObject *Sender);
    void __fastcall UpdateHeadingTimerTimer(TObject *Sender);
    void __fastcall TreeView1Expanding(TObject *Sender, TTreeNode *Node,
        bool &AllowExpansion);
    void __fastcall StartupTimerTimer(TObject *Sender);
    void __fastcall AlarmPanelClick(TObject *Sender);
	void __fastcall Setup2Click(TObject *Sender);
    void __fastcall SystemPanelClick(TObject *Sender);
    void __fastcall AlarmReport1Click(TObject *Sender);
    void __fastcall ADConverterinfo1Click(TObject *Sender);
    void __fastcall DraftPanelClick(TObject *Sender);
    void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
    void __fastcall ToolButtonCargoClick(TObject *Sender);
    void __fastcall ToolButtonBallastClick(TObject *Sender);
    void __fastcall ToolButtonServiceClick(TObject *Sender);
    void __fastcall ImportExporttoBinnenmaat1Click(TObject *Sender);
    void __fastcall Basiccargotypes1Click(TObject *Sender);
    void __fastcall UpdateConfigFileTimerTimer(TObject *Sender);
    void __fastcall AlarmTimerTimer(TObject *Sender);
    void __fastcall Midas1ExportTimerTimer(TObject *Sender);
    void __fastcall PVCS1Click(TObject *Sender);
    void __fastcall NetReceiveRestartTimerTimer(TObject *Sender);
	void __fastcall IdTCPServer1Execute(TIdContext *AContext);
    void __fastcall PVCSTCPServerExecute(TIdContext *AContext);
    void __fastcall PVCSAlarmServerExecute(TIdContext *AContext);
    void __fastcall HTTMLServerConnect(TIdContext *AContext);
    void __fastcall HTTMLServerCommandGet(TIdContext *AContext,
        TIdHTTPRequestInfo *ARequestInfo, TIdHTTPResponseInfo *AResponseInfo);
    void __fastcall OpModeComboBoxChange(TObject *Sender);
    void __fastcall ExitTimeoutTimerTimer(TObject *Sender);
    void __fastcall ToolBarItem2Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
	void __fastcall nrDataProcessor1DataPacket(TObject *Sender,
        TnrDataPacket *Packet);
    void __fastcall nrDataProcessor1DataPackets0PacketLength
        (TnrDataPacket *Packet, BYTE chData, bool &IsHandled);
    void __fastcall nrComm1AfterSend(TObject *Com);
	void __fastcall nrDataProcessor1Timeout(TObject *Sender);
	void __fastcall WindowTileItemClick(TObject *Sender);
	void __fastcall WindowTileItem2Click(TObject *Sender);
	void __fastcall WindowCascadeItemClick(TObject *Sender);
	void __fastcall WindowArrangeItemClick(TObject *Sender);
	void __fastcall WindowMinimizeItemClick(TObject *Sender);
	void __fastcall DelayedRunTimerTimer(TObject *Sender);
	void __fastcall Style1Click(TObject *Sender);
	void __fastcall ToolButtonTankPressureClick(TObject *Sender);
	void __fastcall ToolButtonTempClick(TObject *Sender);
	void __fastcall ToolButtonLinePressureClick(TObject *Sender);
	void __fastcall DraftToolButtonClick(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall ToolButtonWashTrackClick(TObject *Sender);
	void __fastcall ToolButtonLoadCalcClick(TObject *Sender);
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
		  TIdSocketHandle *ABinding);
	void __fastcall IdTCPServer1Exception(TIdContext *AContext, Exception *AException);
	void __fastcall PVCSTCPServerException(TIdContext *AContext, Exception *AException);
	void __fastcall PVCSAlarmServerException(TIdContext *AContext, Exception *AException);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall IdTCPServer1Connect(TIdContext *AContext);
	void __fastcall PVCSTCPServerConnect(TIdContext *AContext);
	void __fastcall PVCSTCPServerDisconnect(TIdContext *AContext);
	void __fastcall PVCSAlarmServerConnect(TIdContext *AContext);
	void __fastcall PVCSAlarmServerDisconnect(TIdContext *AContext);
	void __fastcall IdTCPServer1Disconnect(TIdContext *AContext);
	void __fastcall nrComm1FatalError(TObject *Sender, DWORD ErrorCode, DWORD Detail,
		  UnicodeString ErrorMsg, bool &RaiseException);
	void __fastcall Freewindow1Click(TObject *Sender);
	void __fastcall RzTreeView1Collapsing(TObject *Sender, TTreeNode *Node, bool &AllowCollapse);
	void __fastcall RzTreeView1Change(TObject *Sender, TTreeNode *Node);
	void __fastcall RzTreeView1Click(TObject *Sender);
	void __fastcall ExplorerExecuteDelayTimerTimer(TObject *Sender);
	void __fastcall Protocols1Click(TObject *Sender);
	void __fastcall DatalogMenuItemClick(TObject *Sender);
	void __fastcall SetupClick(TObject *Sender);
	void __fastcall AlarmLogCleanTimerTimer(TObject *Sender);






private: // User declarations
	bool ThemeChanged;
	TTreeNode *TreeNodeList;
	int TreeNodeListKey[TOTAL_PICTURES];

	void SetTreeNodes(void);

	void ReadIniFile(void);
	void WriteIniFile(void);

	bool HasIniFile;
	AnsiString OldProgVersion;
	time_t MainStartTime;
	time_t myStartTime;
	bool HasConfigFile;
	// bool HasLoadCalc;
	bool HasCargoTPDrawing;
	bool HasBallastTPDrawing;
	bool HasServiceTPDrawing;
	bool HasVoidSpaceTPDrawing;
	bool HasTWM_TPDrawing;
	// DNV class reqirements:
	bool NetworkHasBeenOK;
	bool CommunicationFault;
	bool AbortPVCSThread;

	TTreeNode *previousNode;
	// bool HasFileList[TOTAL_PICTURES];
	// AnsiString SurvData;
	// AnsiString SysName;
	// Communication
	AnsiString CompPortName;
	vector<AnsiString>FileNameVector;
	vector<AnsiString>ScreenNameVector;
	int PrevTotalCount;
	int UDPFailCount;
	bool RunMultiple;
    bool useNexComBuzzer;
	bool hasHattelandSCOM;
	volatile bool useHattelandSCOM;
	unsigned short HattelandSCOMPort;
	unsigned MinBackLight;
	volatile bool isBright;
	static AnsiString PVCSTitle;
	static AnsiString LoadCalcTitle;
	static AnsiString LoadCalcName;
	bool __fastcall CheckIfProjectExist();
	void __fastcall FindProject();
	void RestoreData(void);
	void SaveData(void);
    void RestoreClass(AnsiString ClassNamePtr, int TypePtr, bool InitMax,
		int TopPtr, int LeftPtr, int WidthPtr, int HeightPtr, int TankIDNumber);
    bool ZeroSetDlg(AnsiString ZeroText);
    /* AnsiString Check_file(const char* fileName);
	 //  void NetMsg(char* netmsg);
     void ConfigMsg(char* Cmsg);
     char* property_file;
     int RxFailCnt;
     //  TColor CargoTypeColor[MAX_COLOR_CARGO_TYPES];
     int MainTankIndex;
	 void __fastcall CreateMDIChild(const AnsiString Name);
     virtual __fastcall TMainForm(TComponent *Owner);
     */
    // Alarm and sytem faults:
    void AlarmBlink();
	void SystemPanelBlink();
    void NetworkFaultBlink();
    // virtual serial driver:
	void OnStartChildProcess();
	AnsiString RegNameKey;

	void __fastcall ReadRegistry(void);
	void __fastcall ReadPVCSRegistry(void);
	void __fastcall ReadCameloadRegistry(void);

	void __fastcall WriteRegistry(void);
	void __fastcall OnPVCS(void);
	int __fastcall GetNumberOfPvcsScreens(AnsiString Path);
	bool __fastcall GetPvcsScreenInfo(AnsiString Path, int ScreenCount);

	static AnsiString PVCSPath;

	int __fastcall Filter(unsigned int code, struct _EXCEPTION_POINTERS *ep);
	int __fastcall GetCommandId(AnsiString Command);
	void __fastcall LoadCalcClick(TObject *Sender);
	static BOOL EnumWindowsProc(HWND hwnd, LPARAM lParam);
	static BOOL EnumLoadCalcWindowsProc(HWND hwnd, LPARAM lParam);
	bool __fastcall IsLoadCalcActive(DWORD *aProcess = NULL);
	bool __fastcall ExitProgram(void);
	void __fastcall ReadComPortsFromRegistry(void);

	void __fastcall ShowWarningForm(void);
	void __fastcall InitEmptyDatabase1(void);
	void __fastcall InitEmptyDatabase2(void);
	void __fastcall InitEmptyDatabase3(void);
	void __fastcall InitEmptyDatabase4(void);
    void __fastcall CreateDatabase1IfDontExist(TLiteQuery *LiteQueryPtr);

	void __fastcall GetVersionInformation(void);
	void __fastcall RzTreeClick(TTreeNode *Node);



public: // User declarations
	__fastcall TMainForm(TComponent* Owner);
	void ErrorMsg(AnsiString msg);

    // System setup
    bool ConfigLoaded;
    bool HaveNewConfig;
	bool FindComPort;
	int  ComRetryCnt;
    unsigned CurrentSearchComPortIndex;
    vector<unsigned>ComPorts;
	// AnsiString CurrentProjectName;
	WinUart *WinUartPtr;
	TThread *XMLDataExchangeThreadPtr;
	TThread *SARCDataExchangeThreadPtr;
	TThread *SimulatorThread;
	TThread *LoadCalcXMLExpThreadPtr;
	DataLogThread *DataLogThreadPtr;
	SensorLogThread *SensorLogThreadPtr;

	AnsiString ErrorMsgString;
    // AnsiString ProjectDir;
	TStringList *ProjectNameList;
    AnsiString DataSourceName;
    AnsiString HostIP;
	AnsiString HostIP2;
	AnsiString TCU_IP_Address;
	int TCU_TCP_Port;
	int TCU_UDP_Port;
	bool IsServer;
	bool Redundancy;
	int UDPPort;
    int TCPPort;
    int PVCSPort;
	int MyAddress;
	int ScreenSize[2];
	int BaudRate;
	int DataBits;
	AnsiString StopBits;
	AnsiString Parity;
	// Communication
	bool SimulatorFlag;
	static AnsiString LoadCalcPath;
	AnsiString MemName;
	AnsiString strMutexName;
	HANDLE m_hAccessMutex; // Handle to Access Mutex
	HANDLE LoadCalcAccessMutex; // Handle to Access Mutex
	AnsiString LoadCalcXMLFileName;
	AnsiString LoadCalcRegKey;
	TStringList* MyUSBComList;

	int NetRxSize;
	int NetTxSize;
	char NetRxBuf[UNPACK_BLOCK_SIZE];
	char NetTxBuf[UNPACK_BLOCK_SIZE];

	volatile float LastSyncTime;
	volatile float LastReqTime;
	volatile float LastAckTime;
	volatile bool  ComFailure;
	AnsiString BinnenmatDir;
	TStringList  *ANWinClients;
	TStringList  *PVCSClients;
	bool DataLogEnable;
	int DataLogInterval;
	int DataLogDays;
	bool SensorLogEnable;
	int SensorLogInterval;
	int SensorLogDays;

	bool __fastcall CheckNetwork();
	void __fastcall SyncReceived(void);
	void __fastcall StopXMLExport(void);
	void __fastcall StartSARCDataExport(void);
	void __fastcall StopSARCDataExport(void);
	void __fastcall TCPClientSendToServer(TIdTCPClient *TCPClient, char *BufPtr,
		int Size);
	void __fastcall TCPClientSendToServer(char *BufPtr, int Size);
	void __fastcall SubClassTPanelWndProc(Messages::TMessage &Message);
	void __fastcall ReadRegistryDataPath(void);
	bool __fastcall SendSCOM_BuzzerCommand(bool Active);
	void __fastcall SendSCOM_MinBackLightCommand(unsigned char Value);
	void __fastcall SendSCOM_Buttons_MinBrightnessCommand(unsigned char Value);
	void __fastcall SendSCOM_Buttons_BrightnessAutoFollow(unsigned char Value);
	void __fastcall SendSCOM_BackLight_Control_Selection(unsigned char Value);
	bool __fastcall SendSCOM_UserBrightnessControl(unsigned char Value);
	unsigned char  __fastcall ReadSCOM_BRU(void);
	bool __fastcall SendSCOM_Command(unsigned char MsgBuf[], unsigned Size);
	void __fastcall SendSCOM(unsigned char MsgBuf[], unsigned Size);
	void __fastcall UpdateSplashProgress(int Delay);
	void __fastcall UpdateSplashProgress(int Delay, AnsiString Message);


	/////////////////////////////////////////////////////////////////////////////
	//
	// ANWIN Net related codes begin
	//
	// -hkim-
	//
	/////////////////////////////////////////////////////////////////////////////
	Anpro_Net		anpro_net;

	/////////////////////////////////////////////////////////////////////////////
	//
	// ANWIN Net related codes end
	//
	/////////////////////////////////////////////////////////////////////////////
};

// ---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
// ---------------------------------------------------------------------------
#endif