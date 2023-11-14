// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "ProtocolInfoUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Excel_XP_srvr"
#pragma resource "*.dfm"
TProtocolInfoForm *ProtocolInfoForm;

// ---------------------------------------------------------------------------
__fastcall TProtocolInfoForm::TProtocolInfoForm(TComponent* Owner)
	: TForm(Owner) {
    ModbusUnitPtr = NULL;
}

// ---------------------------------------------------------------------------
void __fastcall TProtocolInfoForm::Timer1Timer(TObject *Sender) {
	if (ModbusMap.size()) {

		StringGridInputRegisters->RowCount = ModbusMap.size() + 1;
		int Row = 1;
		multimap<unsigned, ModbusObject*>::iterator ObjMapIterator;
		for (ObjMapIterator = ModbusMap.begin(); ObjMapIterator != ModbusMap.end(); Row++, ObjMapIterator++) {
			ModbusObject *ModbusObjectPtr = (ModbusObject*)(*ObjMapIterator).second; ;
			PRogramObjectBase *ObjectPtr = 	PRogramObjectBase::FindObject(ModbusObjectPtr->GetObjectId());
			if (CheckBoxRegOffset->Checked) {
				StringGridInputRegisters->Cells[0][Row] = ModbusObjectPtr->GetChannel()+1;
			}else{
				StringGridInputRegisters->Cells[0][Row] = ModbusObjectPtr->GetChannel();
			}
			if (CheckBoxHex->Checked) {
				AnsiString HexId;
				HexId.sprintf("0x%08X",ModbusObjectPtr->GetObjectId());
				StringGridInputRegisters->Cells[1][Row] = HexId;
			}else{
				StringGridInputRegisters->Cells[1][Row] = ModbusObjectPtr->GetObjectId();
			}
			if (ObjectPtr) {
				StringGridInputRegisters->Cells[2][Row] = ObjectPtr->Name;
			} else{
				StringGridInputRegisters->Cells[2][Row] = ModbusObjectPtr->Name;
			}
			StringGridInputRegisters->Cells[3][Row] = ModbusObjectPtr->GetValueKey();
			StringGridInputRegisters->Cells[4][Row] = ModbusObjectPtr->GetRegisterType();
			StringGridInputRegisters->Cells[5][Row] = ModbusObjectPtr->GetRegisterValue();
		}
		TSNUart *ComPort = PROTanksystemUnit::GetComPort(SpinEditTCU->Value,ComboBoxComPorts->Text.ToInt());
		if (ComPort) {
			switch(ComPort->Device){
            case C_UART_DEVICE_MODICON_MASTER_TCP   :
            case C_UART_DEVICE_MODICON_MASTER       :
			case C_UART_DEVICE_MODBUS_MASTER_TCP:
			case C_UART_DEVICE_MODBUS_MASTER_INV:
			case C_UART_DEVICE_MODBUS_MASTER:
				switch(ComPort->Device){
                case C_UART_DEVICE_MODICON_MASTER_TCP   :
				case C_UART_DEVICE_MODBUS_MASTER_TCP:
					LabelOperationMode->Caption     = "Master TCP";
					break;
				case C_UART_DEVICE_MODBUS_MASTER_INV:
					LabelOperationMode->Caption     = "Master, exchanged function codes";
					break;
                case C_UART_DEVICE_MODICON_MASTER       :
				case C_UART_DEVICE_MODBUS_MASTER:
					LabelOperationMode->Caption    = "Master";
					break;
				}
				LabelFunctionCodeRead->Caption  = "Input Reg: 0x3. Holding Reg: 0x4 Input Status: 0x1";
				LabelFunctionCodeWrite->Caption = "Reg Multiple: 0x10, Coils Multiple: 0xf";
				break;
			case C_UART_DEVICE_MODBUS_SLAVE_INV     :
				LabelOperationMode->Caption     = "Slave, exchanged function codes";
				LabelFunctionCodeRead->Caption  = "Input Reg: 0x4. Holding Reg: 0x3 Coil Status: 0x2. Input Status: 0x1";
				LabelFunctionCodeWrite->Caption = "Reg: Single: 0x6. Multiple: 0x10, Coils: Single: 0x5 Multiple: 0xf";
				break;
            case C_UART_DEVICE_MODICON_SLAVE_TCP    :
			case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
				LabelOperationMode->Caption     = "Slave TCP";
				LabelFunctionCodeRead->Caption  = "Input Reg: 0x4. Holding Reg: 0x3 Coil Status: 0x2. Input Status: 0x1";
				LabelFunctionCodeWrite->Caption = "Reg: Single: 0x6. Multiple: 0x10, Coils: Single: 0x5 Multiple: 0xf";
				break;
            case C_UART_DEVICE_MODICON_SLAVE        :
			case C_UART_DEVICE_MODBUS_SLAVE         :
				LabelOperationMode->Caption     = "Slave";
				LabelFunctionCodeRead->Caption  = "Input Reg: 0x3. Holding Reg: 0x4 Coil Status: 0x1. Input Status: 0x2";
				LabelFunctionCodeWrite->Caption = "Reg: Single: 0x6. Multiple: 0x10, Coils: Single: 0x5 Multiple: 0xf";
				break;
			};
		}
		if (ModbusUnitPtr) {
			LabelReadInputRegisterStatus->Caption 		=  ModbusUnitPtr->StatusAnalogIn;
			LabelReadInputStatusStatus->Caption 		=  ModbusUnitPtr->StatusDigitalIn;
			LabelWriteHoldingRegisterStatus->Caption 	=  ModbusUnitPtr->StatusAnalogOut;
			LabelWriteCoilStatusStatus->Caption 		=  ModbusUnitPtr->StatusDigitalOut;
		}


	}else{
		StringGridInputRegisters->RowCount = 2;
		for(int i=0; i < StringGridInputRegisters->ColCount; i++){
		   StringGridInputRegisters->Cells[i][1]= "";
		}

	}
}

// ---------------------------------------------------------------------------
void __fastcall TProtocolInfoForm::FormCreate(TObject *Sender) {
	SpinEditTCU->MaxValue = PROTanksystemUnit::TanksystemTCUSet.size() - 1;
	AnsiString Heading[] = {
		"Register", "RefObjectId", "Object Name", "ValueKey", "Type", "Value"};
	for (unsigned i = 0; i < NELEMENTS(Heading); i++) {
		StringGridInputRegisters->Cells[i][0] = Heading[i];
	}
	StringGridInputRegisters->ColWidths[0] = 60;
	StringGridInputRegisters->ColWidths[1] = 100;
	StringGridInputRegisters->ColWidths[2] = 100;
	StringGridInputRegisters->ColWidths[3] = 120;
	StringGridInputRegisters->ColWidths[4] = 100;
	StringGridInputRegisters->ColWidths[5] = 120;
	RegInModbusSet = ModbusRegisterIn::ModbusSet;
	RegInModbusSet.insert(ModbusRegBitIn::ModbusSet.begin(), ModbusRegBitIn::ModbusSet.end());
	CurrentModbusSet = RegInModbusSet;
	// Start with RegisterIn as default
	map<unsigned, ModbusObject*>::iterator ObjMapIterator;
	/*
	 set<PRogramObjectBase *>::iterator pBIt;
	 for (pBIt = RegInModbusSet.begin(); pBIt != RegInModbusSet.end(); pBIt++) {
	 ModbusObject *ModbusObjectPtr = (ModbusObject*)*pBIt;
	 ModbusMap.insert(pair<unsigned, ModbusObject *>(ModbusObjectPtr->GetChannel(), ModbusObjectPtr));
	 }
	 */

	InitSpinBoxes( RegInModbusSet);
	InitSpinBoxes( ModbusRegisterOut::ModbusSet);
	InitSpinBoxes( ModbusCoilIn::ModbusSet);
	InitSpinBoxes( ModbusCoilOut::ModbusSet);
	SortIdNumbers(CurrentModbusSet);
}

// ---------------------------------------------------------------------------
void __fastcall TProtocolInfoForm::SortIdNumbers(set<PRogramObjectBase *>ObjectSet) {
	int TCUNumber = SpinEditTCU->Value;
	int Address = ComboBoxAddress->Text.ToInt();
	int ComPort = ComboBoxComPorts->Text.ToInt();
	ModbusMap.clear();
	map<unsigned, ModbusObject*>::iterator ObjMapIterator;
	// Prepare sorted list of Id numbers;
	set<PRogramObjectBase*>::iterator pBIt;
	for (pBIt = ObjectSet.begin(); pBIt != ObjectSet.end(); pBIt++) {
		ModbusObject *ModbusObjectPtr = (ModbusObject*)*pBIt;
		if (ModbusObjectPtr->GetTCUAddress()== TCUNumber && ModbusObjectPtr->GetAddress()== Address && ModbusObjectPtr->GetTCUPortNo() == ComPort) {
			ModbusMap.insert(pair<unsigned, ModbusObject *>(ModbusObjectPtr->GetChannel(), ModbusObjectPtr));
		}
	}
	if (!ObjectSet.empty()) {
		ModbusObject *ModbusObjectPtr = (ModbusObject*)*ObjectSet.begin();
		ModbusUnitPtr =  ModbusObjectPtr->FindUnit();
	}
}

// ---------------------------------------------------------------------------

void __fastcall TProtocolInfoForm::SpinEditTCUChange(TObject *Sender) {
	ComPorts.clear();
	Address.clear();
	InitSpinBoxes( RegInModbusSet);
	InitSpinBoxes( ModbusRegisterOut::ModbusSet);
	InitSpinBoxes( ModbusCoilIn::ModbusSet);
	InitSpinBoxes( ModbusCoilOut::ModbusSet);
	SortIdNumbers(CurrentModbusSet);
}
// ---------------------------------------------------------------------------

void __fastcall TProtocolInfoForm::TabControl1Change(TObject *Sender) {
	switch (TabControl1->TabIndex) {
	case 0:
		CurrentModbusSet = RegInModbusSet;
		break;
	case 1:
		CurrentModbusSet = ModbusRegisterOut::ModbusSet;
		break;
	case 2:
		CurrentModbusSet = ModbusCoilIn::ModbusSet;
		break;
	case 3:
		CurrentModbusSet = ModbusCoilOut::ModbusSet;
		break;
	}

	SortIdNumbers(CurrentModbusSet);
}


// ---------------------------------------------------------------------------
void __fastcall TProtocolInfoForm::InitSpinBoxes(set<PRogramObjectBase *>ObjectSet) {

	int TCUNumber = SpinEditTCU->Value;

	set<PRogramObjectBase*>::iterator pBIt;
	for (pBIt = ObjectSet.begin(); pBIt != ObjectSet.end();	pBIt++) {
		ModbusObject *ModbusObjectPtr = (ModbusObject*)*pBIt;
		if (ModbusObjectPtr->GetTCUAddress() == TCUNumber ) {
			ComPorts.insert(ModbusObjectPtr->GetTCUPortNo());
			Address.insert(ModbusObjectPtr->GetAddress());
		}
	}
	{
		bool isFirst = true;
		ComboBoxComPorts->Items->Clear();
		set<unsigned>::iterator ComPortIt;
		for (ComPortIt = ComPorts.begin(); ComPortIt != ComPorts.end();	ComPortIt++) {
			AnsiString tmpStr = AnsiString((*ComPortIt));
			if (isFirst) {
				isFirst = false;
				ComboBoxComPorts->Text = tmpStr;
			}
			ComboBoxComPorts->Items->Add(tmpStr);
		}
	}
	{
		bool isFirst = true;
		ComboBoxAddress->Items->Clear();
		set<unsigned>::iterator AddressIt;
		for (AddressIt = Address.begin(); AddressIt != Address.end();AddressIt++) {
			AnsiString tmpStr = AnsiString((*AddressIt));
			if (isFirst) {
				isFirst = false;
				ComboBoxAddress->Text = tmpStr;
			}
			ComboBoxAddress->Items->Add(tmpStr);
		}
	}
	// Prepare sorted list of Id numbers;
	SortIdNumbers(CurrentModbusSet);

}
void __fastcall TProtocolInfoForm::ComboBoxComPortsChange(TObject *Sender)
{
	SortIdNumbers(CurrentModbusSet);
	if (ModbusUnitPtr ) {
		GroupBoxComStatus->Visible = ModbusUnitPtr->GetIsMaster();
	}
}
//---------------------------------------------------------------------------

void __fastcall TProtocolInfoForm::Button1Click(TObject *Sender)
{
	// Connect to Excel
	ExcelApplication1->Connect();
	// add a workbook
	ExcelApplication1->Workbooks->Add(Variant(1), 0);
	// open the workbook
	ExcelWorkbook1->ConnectTo(ExcelApplication1->Workbooks->get_Item
		(Variant(1)));
	ExcelWorkbook1->Activate(0);
	// open the workbook to the first worksheet
	ExcelWorksheet1->ConnectTo(ExcelWorkbook1->Worksheets->get_Item
		(Variant(1)));
	ExcelWorksheet1->Activate(0);
	// Set visible
	ExcelApplication1->set_Visible(true, true);

	for (int Row = 0; Row < StringGridInputRegisters->RowCount; Row++) {
		for (int Col = 0; Col < StringGridInputRegisters->ColCount; Col++) {
			ExcelWorksheet1->Cells->set_Item(Variant(Row + 3), Variant(Col + 1), Variant(WideString(StringGridInputRegisters->Cells[Col][Row])));
		}

	}
	// disconnect from Excel
	ExcelWorksheet1->Disconnect();
	ExcelWorkbook1->Disconnect();
	ExcelApplication1->Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TProtocolInfoForm::FormClose(TObject *Sender, TCloseAction &Action)

{
    Action = caFree;

}
//---------------------------------------------------------------------------

