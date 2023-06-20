#pragma once

#include "stdafx.h"

void WarnMessageBox (unsigned id);
int ConfirmMessageBox (unsigned id);
void InfoMessageBox (unsigned id);
void SaveInfoMessageBox(unsigned id, bool saveOK);
bool GetNumMessageBox (unsigned id, double& result);
bool GetNumMessageBox (unsigned id, double low, double high, double& result);
bool GetNumMessageBox (unsigned id, int& result);
bool GetNumMessageBox (unsigned id, int low, int high, int& result);
bool GetStrMessageBox (unsigned id, CString& result);
void InitMessage();