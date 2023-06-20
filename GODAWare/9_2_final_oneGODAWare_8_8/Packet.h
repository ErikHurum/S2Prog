#pragma once

enum CommandID {
	CONNECT_CMD, CONNECT_OK, CONNECT_FAIL, 
	LOAD_CMD, LOAD_OK, LOAD_FAIL, 
	SAVE_CMD, SAVE_OK, SAVE_FAIL, 
	DISCONNECT_CMD, DISCONNECT_OK, DISCONNECT_FAIL, 
	GETDEVICEADDR_CMD, GETDEVICEADDR_OK, 
	GETDEVICENUM_CMD, GETDEVICENUM_OK, 
	SETDEVICENUM_CMD, SETDEVICENUM_OK
};

class CPacket : public CObject
{
	DECLARE_SERIAL(CPacket)

public:
	CPacket(void) {}
	~CPacket(void) {}

	CPacket& operator = (const CPacket &p)
	{
		cmdID = p.cmdID;
		dataID = p.dataID;
		sensorID = p.sensorID;

		data.RemoveAll();

		int len = p.data.GetSize();
		for (int i=0;i<len;i++)
		{
			data.Add(p.data[i]);
		}

		return *this;
	}

	CPacket(const CPacket &p)
	{
		*this = p;
	}

	void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		if (ar.IsStoring())
		{

			ar<<(int)cmdID<<sensorID<<dataID;

			int len = data.GetSize();
			ar<<len;
			for (int i=0;i<len;i++)
			{
				ar<<data[i];
			}
		}
		else // Loading
		{
			int temp_cmdID = 0;
			ar>>temp_cmdID>>sensorID>>dataID;
			cmdID = (CommandID)temp_cmdID;

			int len;
			ar>>len;
			for (int i=0;i<len;i++)
			{
				BYTE b;
				ar>>b;
				data.Add(b);
			}

			//data.Serialize(ar);

			//ar>>intNum;
			//if (intNum>0)
			//{
			//	intData = new int[intNum];
			//	for (int i=0;i<intNum;i++)
			//	{
			//		ar>>intData[i];
			//	}
			//}

			//ar>>doubleNum;
			//if (doubleNum>0)
			//{
			//	doubleData = new double[doubleNum];
			//	for (int i=0;i<doubleNum;i++)
			//	{
			//		ar>>doubleData[i];
			//	}
			//}
		}
	}

	CommandID cmdID;
	int dataID;
	int sensorID;
	CArray<BYTE> data;

//	CArray<int> intData;
//	CArray<double> doubleData;

	//int intNum;
	//int * intData;

	//int doubleNum;
	//double * doubleData;
};
