#pragma once
#ifndef TSNINCLUDES_H
    #define TSNINCLUDES_H


    #include <math.h>
    #include <algorithm>
    #include <iterator>
    #include <functional>
    #include <set>
    #include <list>
    #include <memory>
    #include <map>
    #include <vector>
    #include <queue>



//RBMARK is included in "ANPro10Inc.h":
    #ifdef ANTDUSIM
        #pragma warning( disable : 4060 4065 4101 4244 4267 4305 4311 4800)
    #endif

    #ifdef S2TXU
        #include "2410addr.h"
        #include "2410lib.h"
        #include "rtos.h"
        #include "GUI.h"
// #include "C:\Program Files\IAR Systems\Embedded Workbench 5.0\ARM\PowerPac\RTOS\Inc\RTOS.h"
    #endif
    #ifdef BORLAND
        #include <Menus.hpp>
        #include <stdlib.h>
		#include "dinkumware\iostream.h"
		#include "dinkumware\fstream.h"
		#include "dinkumware\iomanip.h"
		#include <dstring.h>
    #endif
    #ifndef MIN
        #define MIN(a, b) (((a) < (b)) ? (a) : (b))
    #endif
    #ifndef MAX
        #define MAX(a, b) (((a) < (b)) ? (b) : (a))
    #endif

//For all
//TSN Help Objects
    #include "TSNTimer.h"

// TSN Communication
	#include "ANPRO10Inc.h"
    #if defined(ANBOOTLOADER) || defined(ANFLASH)
        #include "ANPRO10UnitInfo.h"
    #endif
    #if defined(S2TXU) || defined(ANBOOTLOADER)
        #include "mx29LV160TB.h"
    #endif
    #include "TSNConfigUtilities.h"
    #include "TSNConfigInfo.h"

//PRogramObjectBase
    #include "PRogramObjectBase.h"
    #include "CargoTypeObject.h"
    #include "CTOUser.h"

    #include "PROUser.h"
// Tables
	#include "TsnTable.h"
    #include "TSNTable1Degree.h"
    #include "TSNTable2Degree.h"
    #include "TSNTableCenterOfFlotation.h"
    #include "TSNTableLevelCorrection.h"
    #ifdef ANWIN
        #include "TSNTable1Degree.h"
    #endif
// Settings
    #include "TSNSaveSettings.h"

// Timers
    #include "InputResponseTimer.h"

// Nodes and Node list:
    #include "PRONode.h"
    #include "PROLinkedList.h"
    #include "PROSafeLinkedList.h"

// Controll
// Alarm relay, flash, horn, lamp, buzzer on TCU
    #include "PROControl.h"
    #include "CtrlAlarmRelay.h"
    #include "CtrlBuzzer.h"
    #include "CtrlLight.h"
    #include "CtrlHorn.h"
    #include "CtrlLamp.h"
//IOComponents
    #include "PROIOComponent.h"
//IOComponents Digital
    #include "DigitalInput.h"
//IOComponents Analog
    #include "AnalogInput.h"
    #include "AITempSensor.h"
    #include "AITempSensor_Pt100.h"
    #include "AITempSensor_Pt1000.h"
    #include "AITempSensor_AD590.h"
    #include "AIPressSensor.h"
    #include "AIPressSensor_mV.h"
    #include "AIPressSensor_mA.h"
    #include "AIAtmPressSensor_mA.h"
    #include "AIAtmPressSensor_mV.h"
    #include "AIDiffPressSensor_mA.h"
    #include "AIRadarSensor.h"
    #include "AIRadarSensor_mA.h"
    #include "AIRadarSensorHart.h"
    #include "AIFloatSensor_mA.h"
    #include "AIInclinometer.h"
    #include "AIInclinometerN2.h"
    #include "AIInclinometer_mA.h"
    #include "AILevelSwitch_mA.h"
    #include "AILevelSwitchVega.h"
    #include "AILevelSwitchSensor_mV.h"
    #include "AILevelSwitchOptical_mA.h"
    #include "AIWaterIngressSensor.h"
    #include "AIWIngressTempSensor.h"
    #include "AITempSensor_mA.h"
    #include "AITempSensor_Hart.h"
    #include "AIVoltageSensor.h"
    #include "AICoilInSensor.h"
    #include "AIMetriTapeSensor.h"
    #include "AIAirPurgePressSensor.h"
    #include "AIModbusPressSensor_mA.h"
    #include "AIModbusDiffPressSensor_mA.h"
    #include "AIFuseSensor.h"
    #include "AI_AC_Sensor.h"
    #include "AILNGFloat.h"
    #include "AIWashTrackSensor.h"

//PRogramObject
    #include "AlarmBasic.h"
    #include "AlarmOverfill.h"
    #include "AlarmHighLevel.h"
    #include "AlarmLowLevel.h"
    #include "AlarmLoLoLevel.h"
    #include "AlarmHighTemp.h"
    #include "AlarmLowTemp.h"
    #include "AlarmLowBotTemp.h"
    #include "AlarmHighBotTemp.h"
    #include "AlarmLowTemp.h"
    #include "AlarmHighPressure.h"
    #include "AlarmHighPressVac.h"
    #include "AlarmHighIGP.h"
    #include "AlarmHighVapRet.h"
    #include "AlarmLowPressure.h"
    #include "AlarmLowPressVac.h"
    #include "AlarmLowIGP.h"
    #include "AlarmLowVapRet.h"
    #include "AlarmIntLowPressure1.h"
    #include "AlarmIntLowPressure2.h"
    #include "AlarmIntHighPressure1.h"
    #include "AlarmIntHighPressure2.h"
    #include "AlarmMainWaterIngress.h"
    #include "AlarmPreWaterIngress.h"
    #include "AlarmWaterDetect.h"
    #include "AlarmmAmpOpenLoop.h"
    #include "AlarmmAmpShortCircuit.h"
    #include "AlarmSensorConvError.h"
    #include "AlarmSensorConCalError.h"
    #include "AlarmHartSensorComError.h"
    #include "AlarmHartSensorShortCircuit.h"
    #include "AlarmHartSensorOpenLoop.h"
    #include "AlarmAirPurgeSensorFailure.h"
    #include "AlarmLowVoltage.h"
    #include "AlarmHighVoltage.h"
    #include "AlarmCriticalComFailure.h"
    #include "AlarmAtmOutOfRange.h"
    #include "AlarmModbusInCoil.h"
    #include "AlarmLevelSwitch.h"
    #include "AlarmLevelSwitchTest.h"
    #include "AlarmLevelSwitchLight.h"
    #include "AlarmLevelSwitchDead.h"
    #include "AlarmLevelSwitchFailure.h"
    #include "AlarmHighLinePressure.h"
    #include "AlarmHiHiLinePressure.h"
    #include "AlarmLowLinePressure.h"
    #include "AlarmVoidSpace.h"
    #include "AlarmLevelChange.h"
    #include "AlarmLevelDifference.h"
    #include "AlarmTXUComFailure.h"
    #include "AlarmModbusComFailure.h"
    #include "AlarmFuse.h"
    #include "AlarmAC_Voltage.h"
    #include "AlarmInclinometerFailure.h"
    #include "AlarmTCMPresetTimePassed.h"
    #include "AlarmTCMLowSpeed.h"
    #include "PROProjectInfo.h"
    #include "PRogramObject.h"
    #include "PROXRefObject.h"
//#include "AnPro3Object.h"

    #include "LoadReport.h"

// TPCx
    #include "ANPRO1Const.h"
    #include "ANPRO1Packets.h"
    #include "ANPRO1.h"
    #include "TPCWindow.h"
    #include "TPCWindow140.h"
    #include "TPCWindow196.h"
    #include "TPCWindow350.h"
    #include "TPCAlarmWindow.h"
    #include "TPCxObject.h"
    #include "ModbusConst.h"
    #include "ModbusPro.h"
    #include "ModbusUnit.h"
    #include "ModbusObject.h"
    #include "ModbusCoil.h"
    #include "ModbusCoilIn.h"
    #include "ModbusCoilOut.h"
    #include "ModbusCoilHistory.h"
    #include "ModbusRegister.h"
    #include "ModbusRegisterIn.h"
    #include "ModbusRegBitIn.h"
    #include "ModbusRegisterOut.h"
    #include "ModbusRegBitOut.h"
    #include "ModbusRegisterHistory.h"
    #include "ModbusWago473RegisterIn.h"
    #include "ModbusWago479RegisterIn.h"
    #include "ModbusWago482RegisterIn.h"
    #include "ModbusWago485RegisterIn.h"
    #include "ModbusWago487RegisterIn.h"
    #include "ModbusMultiple.h"

	// Scanjet washing machines
    #include "circularbuffer.h"
	#include "TankWashingMachine.h"
	#include "TankWashingMachineCollection.h"
	#include "PROTankWashingMachine.h"
	#include "TankWashingMachineRun.h"
	#include "TankWashingMachineRunCollection.h"
	#include "TankWashingCleaningMedia.h"
	#include "TankWashingCompoundLogObject.h"
	#include "TankWashingCalcParameters.h"
	#include "TankWashingAPI.h"

    #include "PROWaterHeater.h"

//#include "TPC350.h"
// all PRogramObject
    #include "PROSystemData.h"

    #include "PROWaterIngress.h"
    #include "PROLevelSwitch.h"
    #include "PROAtmReference.h"
    #include "PROInclinometer.h"
    #include "PRODraft.h"
    #include "PRODraftSystem.h"
    #include "PROTank.h"
    #include "PROTankSum.h"

    #include "PROTankEmpty.h"
    #include "PROCargoTank.h"
    #include "PROBallastTank.h"
    #include "PROServiceTank.h"
    #include "PROVoidSpace.h"
    #include "PROTankPressure.h"
    #include "PROTankPressureSum.h"
    #include "PROTankPressureEmpty.h"
    #include "PROLinePressure.h"
    #include "PROLinePressureSum.h"
    #include "PROLinePressureEmpty.h"
    #include "PROTemperature.h"
    #include "PROTempSum.h"
    #include "PROTempEmpty.h"
// Simulator for Demo
    #include "IOSimulator.h"

	#include "ANPRO10Object.h"
    #include "IOUnit.h"
    #include "SignalConverter.h"
    #include "SCADCard.h"
    #include "SCWaterIngress.h"
    #include "IOUnitZBAna.h"
    #include "IOUnitZBHart.h"
    #include "IOUnitZB485.h"
    #include "PROPrinter.h"
    #include "AlarmIOComFailure.h"
    #include "AlarmSCComFailure.h"

// TCU TDU
    #include "PROTanksystemUnit.h"
	#include "Anpro3object.h"
	#include "SaabProtocol.h"

// Data structures

    #include "FixedVariables.h"

    #include "TSNExtern.h"

    #ifdef WIN32
        #if defined(ANWIN) || defined(ANFLASH)
            #include <SyncObjs.hpp>
        #else
            #include "ANCriticalSection.h"
        #endif
        #include "TSNUart.h"
        #include "WinUart.h"
    #else
// #include "ANCriticalSection.h"
    #endif
    #ifdef ANWIN
        #include <LCConstants.h>
        #include <TSNTableCrossCurve.h>
        #include <LCFrameData.h>
        #include <LCSectionData.h>
        #include <LCLocationData.h>
        #include <LCConstEntry.h>
        #include <LCKYEntry.h>
        #include <LCStabCalc.h>
        #include <LCSteelWeight.h>
        #include <TSNTableHydrostatic.h>
        #include <TSNTableDamageCase.h>
        #include <TSNTableCenterOfGravity.h>
        #include <TSNTableKY.h>
        #include <LCShipData.h>
        #include <LCSolidData.h>
        #include <LCVariableSolidData.h>
        #include <LCTankData.h>
        #include <LCOpeningData.h>
    #endif
#endif


