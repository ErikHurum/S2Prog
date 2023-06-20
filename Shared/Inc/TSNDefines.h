#ifndef TSNDEFINES
#define TSNDEFINES

#define USE_EMBOS_MEM_POOL  0

#if (defined(S2TXU) || defined(ANBOOTLOADER))
  #define LCD_BACKLIGHT_ADJUST(Adj)  LCD_BackLightAdjust(Adj)

    //#include "TDUIncludes.h"
  //#include "RTOS.h"    /* Definitions for embOS */
  #define CREATE_TASK(pTCB, pName, pFunc, Priority, pStack)  OS_CREATETASK(pTCB, pName, pFunc, Priority, pStack)
  #define START_MT()            OS_Delay(0)
  #define TSN_Delay(t)      OS_Delay(t)
    #define TSN_DelayUntil(t) OS_DelayUntil(t)
  #define SetGuiEvent(PWEventHandl,EventMask,pTCB)     OS_SignalEvent(EventMask,pTCB)
  #define TSN_TASK              OS_TASK
  #define   TSN_MAILBOX         OS_MAILBOX
  #define   TSN_TIMER               OS_TIMER
    #define TSN_Time                OS_Time
  #define   TSN_HANDLE          OS_RSEMA
  #define   TSN_STACKPTR        OS_STACKPTR
  #define   TSN_COM_Send1(c)    OS_COM_Send1(c)
    #define AN_CSEMA OS_CSEMA
    #define AN_SignalCSema(pCSema) OS_SignalCSema(pCSema)

#elif defined(ANTDUSIM)
  #define LCD_BACKLIGHT_ADJUST(Adj)
    #include "stdafx.h"
    extern "C" {
        #include "SIM.h"     /* Definitions for the Win32 simulation */
    }
  #define CREATE_TASK(pTCB, pName, pFunc, Priority, pStack)   SIM_CreateTask(pName, pFunc)
  #define START_MT()  SIM_Start()
  #define TSN_Delay(t)    SIM_Delay(t)
  #define SetGuiEvent(EventHandl,EventMask,pTCB)            TSN_SetGuiEvent(EventHandl)
  #define TSN_TASK      char
  #define   TSN_MAILBOX char
  #define   TSN_TIMER       char
    #define TSN_Time     (int)clock()
  #define   TSN_HANDLE  HANDLE
  #define   TSN_STACKPTR
  #define   TSN_COM_Send1(c)    My_COM_Send1(c)
    #define AN_CSEMA char
    #define AN_SignalCSema(pCSema)
#else
  #define LCD_BACKLIGHT_ADJUST(Adj)

  #define TSN_Delay(t)    Sleep((unsigned long)t)

  #define TSN_TASK      char
  #define   TSN_MAILBOX char
  #define   TSN_TIMER       char
    #define TSN_Time     (int)clock()
  #define   TSN_HANDLE  HANDLE
  #define   TSN_STACKPTR    char

#endif

/////////////////////////////////////////////////////
//
// Additional colors
//
/////////////////////////////////////////////////////
//#define GUI_ORANGE          0x00ffc800
#define GUI_ORANGE        0x0042a4fd


#ifndef BORLAND
#ifndef ANBOOTLOADER
// TDU colours
    #define TDU_C_BACK_DEFAULT      GUI_LIGHTGRAY
    #define TDU_C_TEXT_DEFAULT      GUI_BLACK
// KeyBoard colours
    #define TDU_C_KB_BACK           GUI_DARKGRAY
    #define TDU_C_KB_TEXT           GUI_BLACK
// Heading Windows
    #define TDU_C_HW_BACK           GUI_BLUE
    #define TDU_C_HW_TEXT           GUI_WHITE
// Present Windows
    #define TDU_C_PW_BACK           GUI_BLACK
    #define TDU_C_PW_BACK_ACTIVE    GUI_BLUE
    #define TDU_C_PW_TEXT           GUI_GREEN
    #define TDU_C_PW_TEXT_ACTIVE    GUI_WHITE
// Buttons
    #define TDU_C_BU_BACK           GUI_GRAY
    //#define TDU_C_BU_BACK_OK      0x00AA00                    // Can maybe be removed
    //#define TDU_C_BU_BACK_WARNING GUI_YELLOW              // Can maybe be removed
    //#define TDU_C_BU_BACK_ALARM   GUI_RED                     // Can maybe be removed
    #define TDU_C_BU_TEXT           GUI_BLACK
    //#define TDU_C_BU_TEXT_OK      GUI_WHITE                   // Can maybe be removed
    //#define TDU_C_BU_TEXT_WARNING GUI_BLACK                   // Can maybe be removed
    //#define TDU_C_BU_TEXT_ALARM   GUI_WHITE                   // Can maybe be removed
// Alarms
    #define TDU_C_AL_BACK_ACTIVE    GUI_RED
    #define TDU_C_AL_BACK_ACTIVE_95 GUI_ORANGE
    #define TDU_C_AL_BACK_ACKNOW    GUI_BLACK //GUI_WHITE
    #define TDU_C_AL_BACK_NOAL      0x00AA00
    #define TDU_C_AL_BACK_WARNING   GUI_YELLOW
    #define TDU_C_AL_TEXT_ACTIVE    GUI_WHITE
    #define TDU_C_AL_TEXT_ACKNOW    GUI_WHITE //GUI_RED     //GUI_BLACK
    #define TDU_C_AL_TEXT_NOAL      GUI_WHITE       // GUI_BLACK
    #define TDU_C_AL_TEXT_WARNING   GUI_BLACK
// Config
    #define TDU_C_CONF_BACK         GUI_LIGHTCYAN
    #define TDU_C_CONF_TEXT         GUI_BLACK
// Calibrate
    #define TDU_C_CALIBRATE_BACK    GUI_GRAY


// TDU Fonts
 #include "GUI.h"

    const GUI_FONT TDU_FONT_ST =    GUI_Font13_1;
    const GUI_FONT TDU_FONT_PW =    GUI_Font16_1;
    const GUI_FONT TDU_FONT_HW =    GUI_Font16_1;
    const GUI_FONT TDU_FONT_BU =    GUI_Font13_1;
    const GUI_FONT TDU_FONT_HEADING = GUI_Font13_1;
    const GUI_FONT TDU_FONT_BIG = GUI_Font24_1;

    #define GUI_ID_BUTTON10  (GUI_ID_USER+400)
    #define GUI_ID_BUTTON11  (GUI_ID_USER+401)

    #define GUI_ID_TEXT10    (GUI_ID_USER+510)
    #define GUI_ID_TEXT11    (GUI_ID_USER+511)
    #define GUI_ID_TEXT12    (GUI_ID_USER+512)
    #define GUI_ID_TEXT13    (GUI_ID_USER+513)
    #define GUI_ID_TEXT14    (GUI_ID_USER+514)
    #define GUI_ID_TEXT15    (GUI_ID_USER+515)
    #define GUI_ID_TEXT16    (GUI_ID_USER+516)
    #define GUI_ID_TEXT17    (GUI_ID_USER+517)
    #define GUI_ID_TEXT18    (GUI_ID_USER+518)
    #define GUI_ID_TEXT19    (GUI_ID_USER+519)
    #define GUI_ID_TEXT20    (GUI_ID_USER+520)
    #define GUI_ID_TEXT21    (GUI_ID_USER+521)
    #define GUI_ID_TEXT22    (GUI_ID_USER+522)
    #define GUI_ID_TEXT23    (GUI_ID_USER+523)
    #define GUI_ID_TEXT24    (GUI_ID_USER+524)
    #define GUI_ID_TEXT25    (GUI_ID_USER+525)
    #define GUI_ID_TEXT26    (GUI_ID_USER+526)
    #define GUI_ID_TEXT27    (GUI_ID_USER+527)
    #define GUI_ID_TEXT28    (GUI_ID_USER+528)
    #define GUI_ID_TEXT29    (GUI_ID_USER+529)
    #define GUI_ID_TEXT30    (GUI_ID_USER+530)
    #define GUI_ID_TEXT31    (GUI_ID_USER+531)
    #define GUI_ID_TEXT32    (GUI_ID_USER+532)
    #define GUI_ID_TEXT33    (GUI_ID_USER+533)
    #define GUI_ID_TEXT34    (GUI_ID_USER+534)
    #define GUI_ID_TEXT35    (GUI_ID_USER+535)
    #define GUI_ID_TEXT36    (GUI_ID_USER+536)
    #define GUI_ID_TEXT37    (GUI_ID_USER+537)
    #define GUI_ID_TEXT38    (GUI_ID_USER+538)
    #define GUI_ID_TEXT39    (GUI_ID_USER+539)
    #define GUI_ID_TEXT40    (GUI_ID_USER+540)
    #define GUI_ID_TEXT41    (GUI_ID_USER+541)
    #define GUI_ID_TEXT42    (GUI_ID_USER+542)
    #define GUI_ID_TEXT43    (GUI_ID_USER+543)
    #define GUI_ID_TEXT44    (GUI_ID_USER+544)
    #define GUI_ID_TEXT45    (GUI_ID_USER+545)
    #define GUI_ID_TEXT46    (GUI_ID_USER+546)
    #define GUI_ID_TEXT47    (GUI_ID_USER+547)
    #define GUI_ID_TEXT48    (GUI_ID_USER+548)
    #define GUI_ID_TEXT49    (GUI_ID_USER+549)
    #define GUI_ID_TEXT50    (GUI_ID_USER+550)
    #define GUI_ID_TEXT51    (GUI_ID_USER+551)
    #define GUI_ID_TEXT52    (GUI_ID_USER+552)
    #define GUI_ID_TEXT53    (GUI_ID_USER+553)
    #define GUI_ID_TEXT54    (GUI_ID_USER+554)
    #define GUI_ID_TEXT55    (GUI_ID_USER+555)
    #define GUI_ID_TEXT56    (GUI_ID_USER+556)
    #define GUI_ID_TEXT57    (GUI_ID_USER+557)
    #define GUI_ID_TEXT58    (GUI_ID_USER+558)
    #define GUI_ID_TEXT59    (GUI_ID_USER+559)
    #define GUI_ID_TEXT60    (GUI_ID_USER+560)
    #define GUI_ID_TEXT61    (GUI_ID_USER+561)
    #define GUI_ID_TEXT62    (GUI_ID_USER+562)
    #define GUI_ID_TEXT63    (GUI_ID_USER+563)
    #define GUI_ID_TEXT64    (GUI_ID_USER+564)
    #define GUI_ID_TEXT65    (GUI_ID_USER+565)
    #define GUI_ID_TEXT66    (GUI_ID_USER+566)
    #define GUI_ID_TEXT67    (GUI_ID_USER+567)
    #define GUI_ID_TEXT68    (GUI_ID_USER+568)
    #define GUI_ID_TEXT69    (GUI_ID_USER+569)
    #define GUI_ID_TEXT70    (GUI_ID_USER+570)
    #define GUI_ID_TEXT71    (GUI_ID_USER+571)
    #define GUI_ID_TEXT72    (GUI_ID_USER+572)
    #define GUI_ID_TEXT73    (GUI_ID_USER+573)
    #define GUI_ID_TEXT74    (GUI_ID_USER+574)
    #define GUI_ID_TEXT75    (GUI_ID_USER+575)

    #define GUI_ID_EDIT10    (GUI_ID_USER+610)
    #define GUI_ID_EDIT11    (GUI_ID_USER+611)
    #define GUI_ID_EDIT12    (GUI_ID_USER+612)
    #define GUI_ID_EDIT13    (GUI_ID_USER+613)
    #define GUI_ID_EDIT14    (GUI_ID_USER+614)
    #define GUI_ID_EDIT15    (GUI_ID_USER+615)
    #define GUI_ID_EDIT16    (GUI_ID_USER+616)
    #define GUI_ID_EDIT17    (GUI_ID_USER+617)
    #define GUI_ID_EDIT18    (GUI_ID_USER+618)
    #define GUI_ID_EDIT19    (GUI_ID_USER+619)
    #define GUI_ID_EDIT20    (GUI_ID_USER+620)
    #define GUI_ID_EDIT21    (GUI_ID_USER+621)
    #define GUI_ID_EDIT22    (GUI_ID_USER+622)
    #define GUI_ID_EDIT23    (GUI_ID_USER+623)
    #define GUI_ID_EDIT24    (GUI_ID_USER+624)
    #define GUI_ID_EDIT25    (GUI_ID_USER+625)
    #define GUI_ID_EDIT26    (GUI_ID_USER+626)
    #define GUI_ID_EDIT27    (GUI_ID_USER+627)
    #define GUI_ID_EDIT28    (GUI_ID_USER+628)
    #define GUI_ID_EDIT29    (GUI_ID_USER+629)
    #define GUI_ID_EDIT30    (GUI_ID_USER+630)
    #define GUI_ID_EDIT31    (GUI_ID_USER+631)
    #define GUI_ID_EDIT32    (GUI_ID_USER+632)
    #define GUI_ID_EDIT40    (GUI_ID_USER+640)
    #define GUI_ID_EDIT41    (GUI_ID_USER+641)
    #define GUI_ID_EDIT42    (GUI_ID_USER+642)
    #define GUI_ID_EDIT43    (GUI_ID_USER+643)
    #define GUI_ID_EDIT44    (GUI_ID_USER+644)
    #define GUI_ID_EDIT45    (GUI_ID_USER+645)
    #define GUI_ID_EDIT46    (GUI_ID_USER+646)
    #define GUI_ID_EDIT47    (GUI_ID_USER+647)
    #define GUI_ID_EDIT48    (GUI_ID_USER+648)
    #define GUI_ID_EDIT49    (GUI_ID_USER+649)
    #define GUI_ID_EDIT50    (GUI_ID_USER+650)
    #define GUI_ID_EDIT51    (GUI_ID_USER+651)
    #define GUI_ID_EDIT52    (GUI_ID_USER+652)
    #define GUI_ID_EDIT53    (GUI_ID_USER+653)
    #define GUI_ID_EDIT54    (GUI_ID_USER+654)
    #define GUI_ID_EDIT55    (GUI_ID_USER+655)
    #define GUI_ID_EDIT56    (GUI_ID_USER+656)
    #define GUI_ID_EDIT57    (GUI_ID_USER+657)
    #define GUI_ID_EDIT58    (GUI_ID_USER+658)
    #define GUI_ID_EDIT59    (GUI_ID_USER+659)
    #define GUI_ID_EDIT60    (GUI_ID_USER+660)
    #define GUI_ID_EDIT61    (GUI_ID_USER+661)
    #define GUI_ID_EDIT62    (GUI_ID_USER+662)
    #define GUI_ID_EDIT63    (GUI_ID_USER+663)
    #define GUI_ID_EDIT64    (GUI_ID_USER+664)
    #define GUI_ID_EDIT65    (GUI_ID_USER+665)
    #define GUI_ID_EDIT66    (GUI_ID_USER+666)
    #define GUI_ID_EDIT67    (GUI_ID_USER+667)
    #define GUI_ID_EDIT68    (GUI_ID_USER+668)
    #define GUI_ID_EDIT69    (GUI_ID_USER+669)

    #define GUI_ID_DROPDOWN4   (GUI_ID_USER+704)
    #define GUI_ID_DROPDOWN5   (GUI_ID_USER+705)
    #define GUI_ID_DROPDOWN6   (GUI_ID_USER+706)
    #define GUI_ID_DROPDOWN7   (GUI_ID_USER+707)
    #define GUI_ID_DROPDOWN8   (GUI_ID_USER+708)
    #define GUI_ID_DROPDOWN9   (GUI_ID_USER+709)
    #define GUI_ID_DROPDOWN10  (GUI_ID_USER+710)

    #define GUI_ID_CHECK40  (GUI_ID_USER+840)
    #define GUI_ID_CHECK41  (GUI_ID_USER+841)
    #define GUI_ID_CHECK42  (GUI_ID_USER+842)
    #define GUI_ID_CHECK43  (GUI_ID_USER+843)
    #define GUI_ID_CHECK44  (GUI_ID_USER+844)
    #define GUI_ID_CHECK45  (GUI_ID_USER+845)
    #define GUI_ID_CHECK46  (GUI_ID_USER+846)
    #define GUI_ID_CHECK47  (GUI_ID_USER+847)
    #define GUI_ID_CHECK48  (GUI_ID_USER+848)
    #define GUI_ID_CHECK49  (GUI_ID_USER+849)
    #define GUI_ID_CHECK50  (GUI_ID_USER+850)
    #define GUI_ID_CHECK51  (GUI_ID_USER+851)
    #define GUI_ID_CHECK52  (GUI_ID_USER+852)
    #define GUI_ID_CHECK53  (GUI_ID_USER+853)
    #define GUI_ID_CHECK54  (GUI_ID_USER+854)
    #define GUI_ID_CHECK55  (GUI_ID_USER+855)
    #define GUI_ID_CHECK56  (GUI_ID_USER+856)
    #define GUI_ID_CHECK57  (GUI_ID_USER+857)
    #define GUI_ID_CHECK58  (GUI_ID_USER+858)
    #define GUI_ID_CHECK59  (GUI_ID_USER+849)

    #define GUI_ID_HEADER0  (GUI_ID_USER+900)
    #define GUI_ID_HEADER1  (GUI_ID_USER+901)

    #define MESSAGE_LANGUAGE_CHANGE WM_USER+1
    #define MESSAGE_KEYPAD          WM_USER+10
    #define MESSAGE_KEYPAD_RETURN   WM_USER+11
    #define MESSAGE_PINCODE_RETURN  WM_USER+12

    #define MESSAGE_YES_RETURN      WM_USER+20
    #define MESSAGE_NO_RETURN       WM_USER+21
    #define MESSAGE_CANCEL_RETURN   WM_USER+22
#endif
#endif
inline long double sqr(double x) { return x*x;}

#endif
