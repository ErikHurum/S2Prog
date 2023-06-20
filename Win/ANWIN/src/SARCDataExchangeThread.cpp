//---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
//#include <System.IOUtils.hpp>
#include <Filectrl.hpp>

#include "SARCDataExchangeThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall SARCDataExchangeThread::SARCDataExchangeThread(bool CreateSuspended)
	: TThread(CreateSuspended),updateIntervalSecs(10.0)
{
	NameThreadForDebugging(System::String(L"SARCDataExchangeThread"));
	outputDirPath  = "C:\\exchange";
	outputFilePath = "C:\\exchange\\online_tank_data.txt";

	allowFileLinks = false;

	maxLineLength = 40;
	outBufferSize = PROTank::TankVector.size() * maxLineLength;
	buffPtr = new char[outBufferSize];
}
//---------------------------------------------------------------------------

__fastcall SARCDataExchangeThread::~SARCDataExchangeThread(void)
{
	delete[] buffPtr;
}
//---------------------------------------------------------------------------
void __fastcall SARCDataExchangeThread::Execute()
{

	int DelayCnt = 0;
	while (!Terminated)
	{
		if ( DelayCnt++ < updateIntervalSecs ){
			Sleep(1000);
		}else{
			DelayCnt = 0;
			ExportData();
		}
	}
	return;
}


/// Try re-writing the output file. If success then return true, else false.
bool __fastcall SARCDataExchangeThread::ExportData()
{
	bool dirOK = false;
	bool retval = false;
	ofstream outputFile;

	try {
		if (DirectoryExists(outputDirPath)) {
			dirOK = true;
		}else{

			//TDirectory::CreateDirectoryA((const System::UnicodeString)outputDirPath);
			//TDirectory::CreateDirectory("C:\\exchange");
			dirOK = CreateDir(outputDirPath);
		}

		if (dirOK) {
			outputFile.open(outputFilePath.c_str(), ofstream::out | ofstream::trunc);  // Open out-file

			if (!outputFile.fail()) {
				int charsToOutput = 0;										// Fill output buffer
				charsToOutput = FillOutputBuffer();

				if (charsToOutput > 0) {
					outputFile.write((const char*)buffPtr, charsToOutput);	// write data to disk
					retval = !(outputFile.fail() || outputFile.bad());		// retval is true if all OK
				}
			}
		}
	}
	catch (...) {
		// TODO: output warning if appropriate, or log error if possible
    	retval = false;
	}

	if (outputFile.is_open()) {
		outputFile.close();
	}

	return retval;
}



int __fastcall SARCDataExchangeThread::FillOutputBuffer()
{
	int cursor = 0;
	float Trim = PROSystemData::TXUSystemData->TrimValue * PROProjectInfo::LengthBetweenPP;
	float List = PROSystemData::TXUSystemData->ListValue * RAD_FACTOR;
	float DftFwd = PRODraftSystem::PRODraftSysPtr->DftFwd;
	float DftAft = PRODraftSystem::PRODraftSysPtr->DftAft;
	float SwDns  = PROSystemData::SeaWaterDensity;
	int CurrentTime = time(NULL);
	{
   		int buffSpaceLeft = outBufferSize - cursor;			// Avoid overflows

		int charsWritten = snprintf(buffPtr + cursor, buffSpaceLeft,
		"%d %d %.3f %.2f %.2f %.2f %.5f\n",
		0,
		CurrentTime,
		Trim,
		List,
		DftFwd,
		DftAft,
		SwDns);

		if (charsWritten > 0 && charsWritten < buffSpaceLeft) {
			cursor += charsWritten;							// Write succeeded
		} else {
			cursor = 0;										// Write failed, buffer is full .. should never happen
		}
	}
	vector<PROTank*>::iterator tankIter = PROTank::TankVector.begin();

	while (tankIter != PROTank::TankVector.end()) {

		int tankNo = (*tankIter)->ANPro3Id;
		float volume = (*tankIter)->Volume;
		float Ullage = (*tankIter)->UllageRef;
		float Level  = (*tankIter)->LevelAtRef;
		float density = (*tankIter)->Density;
		float temperature = (*tankIter)->Temperature;
		int hwFailure = (*tankIter)->HWFailure ? 1 : 0;

		int buffSpaceLeft = outBufferSize - cursor;			// Avoid overflows

		// Put CSV line for this tank into the output buffer:
		int charsWritten = snprintf(buffPtr + cursor, buffSpaceLeft,
				"%d %.3f %.3f %.3f %.3f %.1f %d\n",
				tankNo,
				volume,
				Ullage,
				Level,
				density,
				temperature,
				hwFailure);

		if (charsWritten > 0 && charsWritten < buffSpaceLeft) {
			cursor += charsWritten;							// Write succeeded
		} else {
			cursor = 0;										// Write failed, buffer is full .. should never happen
			break;
		}

		++tankIter;
	}


	return cursor;
}
