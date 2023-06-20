

#ifndef __ISHARTDRV_H__
#define __ISHARTDRV_H__


#define MAX_NR_OF_DEVICES      256
#define MAX_NR_OF_CARDS  MAX_NR_OF_DEVICES  // old define for compatibility reasons


/******************************/
/* alle möglichen Fehlercodes */
/******************************/
#define HART_NO_ERROR                 0	// success
#define HART_OPEN_ERROR               1	// no access to device
#define HART_DEVICE_NOT_FOUND         2	// device with ID not found
#define HART_DRIVER_ERROR             3	// driver operation failed
#define HART_INVALID_PARAMETER        4	// 
#define HART_STATE_ERROR              5	// operation not allowed in current state
#define HART_DEVICE_TIMEOUT           6
#define HART_TRANSMIT_BUFFER_BUSY     7	// device is transmitting a message
#define HART_RECEIVE_BUFFER_EMPTY     8	// no message received
#define HART_THREAD_NOT_STARTED       9	// Thread konnte nicht gestartet werden bzw. läuft nicht
#define HART_THREAD_ALREADY_STARTED  10	// Thread läuft doch schon, erst beenden

#define HART_BUFFER_OVERRUN          11

#define HART_DEVICE_NOT_INITIALIZED  12
#define HART_DEVICE_REMOVED          13  // Gerät abgezogen
#define HART_DEVICE_ALREADY_IN_USE   15  // Gerät ist bereits von diesem oder einem anderen Programm in Benutzung
#define HART_INSUFFICIENT_RESOURCE   16  // cannot allocate resource to access hardware

#define HART_FIRMWARE_FATAL_ERROR    17  // firmware stopped working, unplug device

#define HART_CONNECTION_FAILED       20  // tcpip-connection to a device over network failed
#define HART_HARDWARE_MISMATCH       21  // the requested isNetcube module has a different fieldbus type (no HART module)

#define HART_THREAD_IS_BLOCKED       35	// callbackthread is blocked, stopping thread failed

#define HART_DEVICE_NOT_LICENCED     40	// need a licence number under NT4


/*************************************************************************.KA*
   .TITEL  [ HAMA Primitive Number                                          ]
  ----------------------------------------------------------------------------
   .BESCHREIBUNG
    The macros defines the service primitives of the HART Master.
*************************************************************************.KE*/
#define HAMA_PRIM_TRANSMIT_REQ      0x00 /* 00000000b */
#define HAMA_PRIM_TRANSMIT_CON_POS  0x40 /* 01000000b */
#define HAMA_PRIM_TRANSMIT_CON_NEG  0xc0 /* 11000000b */
#define HAMA_PRIM_BURST_IND         0x80 /* 10000000b */
#define HAMA_PRIM_UNKNOWN           0xFF /* 11111111b */


/* verschiedene Gerätetypen, die für die Funktionen isHART_GetDriverConfiguration, */
/* isHART_GetDriverConfiguration und isHART_AttachedDevices benötigt werden.       */
#define DEVTYPE_NO_DEV     0
#define DEVTYPE_USB        1   // isHRT USB(eX)
#define DEVTYPE_PCI        2   // currently no product existent
#define DEVTYPE_PCMCIA     3   // currently no product existent
#define DEVTYPE_STICK      4   // the H@rt Stick
#define DEVTYPE_BLUETOOTH  5   // the H@rt BluePack (connection over Bluetooth)
#define DEVTYPE_NETCUBE    6   // isNet H@rt module
#define DEVTYPE_BLUEP_USB  7   // the H@rt BluePack (connection over USB cable)

/* Flags und Konstanten, die für isHART_AttachedDevices benötigt werden */
#define FIND_UNCONFIGURED 0x20
#define FIND_CONFIGURED   0x40
#define FIND_ALL_DEVICES  0x60
#define FIND_NEXT         0x80

/* Konstanten, die für isHART_NotifyPnP benötigt werden */
#define NOTIFY_SET   1
#define NOTIFY_PULSE 2
#define NOTIFY_END   3   /* der Event-Mechanismus wird wieder abgeschaltet, hEvent muß NULL sein */


#pragma pack(push, 1)
typedef struct
{
	BYTE DeviceType;     /* no device = 0, USB = 1, PCI = 2, PCMCIA = 3 ... */
	DWORD DeviceID;
	BOOLEAN bAttached;   /* dieses Gerät ist angeschlossen */
	BOOLEAN bInUse;      /* das Gerät wird gerade benutzt */
} DeviceInfo_type;
#pragma pack(pop)


/**********************************/
/* und die Funktionsdeklarationen */
/**********************************/

#ifdef __cplusplus
extern "C" {
#endif

/* Funktionen in der Dll */
BYTE __cdecl isHART_DeviceInit(BYTE DeviceNr, BOOLEAN bPrimary);
BYTE __cdecl isHART_DynamicInit(char* pStrHardware, BYTE* pDeviceNr, BOOLEAN bPrimary);
BYTE __cdecl isHART_Send(BYTE DeviceNr, BYTE nrOfPreambles, BYTE nLength, BYTE* pSendBuffer);
BYTE __cdecl isHART_Receive(BYTE DeviceNr, BYTE* pEvtPrimitive, BYTE* pLength, BYTE* pReceiveBuffer);
BYTE __cdecl isHART_SetParam(BYTE DeviceNr, BYTE nNrOfRetries);
BYTE __cdecl isHART_GetParam(BYTE DeviceNr, BYTE* pNrOfRetries);
BYTE __cdecl isHART_CloseDevice(BYTE DeviceNr);

BYTE __cdecl isHART_GetDriverConfiguration(BYTE DeviceNr, DeviceInfo_type* pInfo);
BYTE __cdecl isHART_SetDriverConfiguration(BYTE DeviceNr, DeviceInfo_type* pInfo, void* pData);
BYTE __cdecl isHART_AttachedDevices(BYTE flag, DeviceInfo_type* pInfo);
BYTE __cdecl isHART_NotifyPnP(HANDLE hEvent, BYTE flag);


/* diesselben Funktionen mit einer anderen Aufrufkonvention z.B. für Visual Basic */
BYTE __stdcall isHARTvb_DeviceInit(BYTE DeviceNr, BOOLEAN bPrimary);
BYTE __stdcall isHARTvb_DynamicInit(char* pStrHardware, BYTE* pDeviceNr, BOOLEAN bPrimary);
BYTE __stdcall isHARTvb_Send(BYTE DeviceNr, BYTE nrOfPreambles, BYTE nLength, BYTE* pSendBuffer);
BYTE __stdcall isHARTvb_Receive(BYTE DeviceNr, BYTE* pEvtPrimitive, BYTE* pLength, BYTE* pReceiveBuffer);
BYTE __stdcall isHARTvb_SetParam(BYTE DeviceNr, BYTE nNrOfRetries);
BYTE __stdcall isHARTvb_GetParam(BYTE DeviceNr, BYTE* pNrOfRetries);
BYTE __stdcall isHARTvb_CloseDevice(BYTE DeviceNr);

BYTE __stdcall isHARTvb_GetDriverConfiguration(BYTE DeviceNr, DeviceInfo_type* pInfo);
BYTE __stdcall isHARTvb_SetDriverConfiguration(BYTE DeviceNr, DeviceInfo_type* pInfo, void* pData);
BYTE __stdcall isHARTvb_AttachedDevices(BYTE flag, DeviceInfo_type* pInfo);
BYTE __stdcall isHARTvb_NotifyPnP(HANDLE hEvent, BYTE flag);

/* Prototyp für Rückrufe */
void __cdecl MessageHandler(BYTE DeviceNr, void* pContext);
typedef void (__cdecl *pMessageHandler)(BYTE, void*);

BYTE __cdecl isHART_StartMessageHandler(BYTE DeviceNr,
										pMessageHandler CallbackFunc,
										void* pContext);
BYTE __cdecl isHART_StopMessageHandler(BYTE DeviceNr);

#ifdef __cplusplus
}
#endif

/* Funktionszeiger zum dynamischen Laden der Dll unter C++ */
typedef BYTE (__cdecl *pHART_DeviceInit)(BYTE DeviceNr, BOOLEAN bPrimary);
typedef BYTE (__cdecl *pHART_Send)(BYTE DeviceNr, BYTE nrOfPreambles, BYTE nLength, BYTE* pSendBuffer);
typedef BYTE (__cdecl *pHART_Receive)(BYTE DeviceNr, BYTE* pEvtPrimitive, BYTE* pLength, BYTE* pReceiveBuffer);
typedef BYTE (__cdecl *pHART_SetParam)(BYTE DeviceNr, BYTE nNrOfRetries);
typedef BYTE (__cdecl *pHART_GetParam)(BYTE DeviceNr, BYTE* pNrOfRetries);
typedef BYTE (__cdecl *pHART_CloseDevice)(BYTE DeviceNr);
typedef BYTE (__cdecl *pHART_GetDriverConfiguration)(BYTE DeviceNr, DeviceInfo_type* pInfo);
typedef BYTE (__cdecl *pHART_SetDriverConfiguration)(BYTE DeviceNr, DeviceInfo_type* pInfo, void* pData);
typedef BYTE (__cdecl *pHART_AttachedDevices)(BYTE flag, DeviceInfo_type* pInfo);
typedef BYTE (__cdecl *pHART_NotifyPnP)(HANDLE hEvent, BYTE flag);
typedef BYTE (__cdecl *pHART_StartMessageHandler)(BYTE DeviceNr,
												  pMessageHandler CallbackFunc,
												  void* pContext);
typedef BYTE (__cdecl *pHART_StopMessageHandler)(BYTE DeviceNr);


/* Makros für die Zuweisung der Funktionszeiger unter C++ */
#define FUNCPTR_DEVICEINIT(hDll) (pHART_DeviceInit)GetProcAddress(hDll, _T("isHART_DeviceInit"))
#define FUNCPTR_SEND(hDll)       (pHART_Send)GetProcAddress(hDll, _T("isHART_Send"))
#define FUNCPTR_RECEIVE(hDll)    (pHART_Receive)GetProcAddress(hDll, _T("isHART_Receive"))
#define FUNCPTR_SETPARAM(hDll)   (pHART_SetParam)GetProcAddress(hDll, _T("isHART_SetParam"))
#define FUNCPTR_GETPARAM(hDll)   (pHART_GetParam)GetProcAddress(hDll, _T("isHART_GetParam"))
#define FUNCPTR_CLOSE(hDll)      (pHART_CloseDevice)GetProcAddress(hDll, _T("isHART_CloseDevice"))
#define FUNCPTR_GETDRVCFG(hDll)  (pHART_GetDriverConfiguration)GetProcAddress(hDll, _T("isHART_GetDriverConfiguration"))
#define FUNCPTR_SETDRVCFG(hDll)  (pHART_SetDriverConfiguration)GetProcAddress(hDll, _T("isHART_SetDriverConfiguration"))
#define FUNCPTR_ATTACHED(hDll)   (pHART_AttachedDevices)GetProcAddress(hDll, _T("isHART_AttachedDevices"))
#define FUNCPTR_NOTIFYPNP(hDll)  (pHART_NotifyPnP)GetProcAddress(hDll, _T("isHART_NotifyPnP"))

#define FUNCPTR_STARTCALLBACK(hDll) (pHART_StartMessageHandler)GetProcAddress(hDll, _T("isHART_StartMessageHandler"))
#define FUNCPTR_STOPCALLBACK(hDll)  (pHART_StopMessageHandler)GetProcAddress(hDll, _T("isHART_StopMessageHandler"))

#endif // __ISHARTDRV_H__
