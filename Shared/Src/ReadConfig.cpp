#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif


bool ReadConfig(char *fileName)
{                //const char *fileName
  bool NoError = true;
//	InConfigModus = true;
	InitGlobalVariables();

#ifdef S2TXU
	LoadConfigFromFlash();
//#elif ANTDUSIM
#else
	//LoadConfigFromFile("DEMO.S2C");
	NoError = LoadConfigFromFile(fileName);
//	LoadConfigFromFile("C01000.S2C");
//	LoadConfigFromFile("Sales.S2C");
#endif
/*	if(ConfigWarningsString.data()){
		ConfigWarnings->ExecDialogBox(NULL);
	}*/
//	InConfigModus = false;
  return NoError;
}

