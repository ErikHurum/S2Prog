class LCKYEntry {
public:
	static vector<float>TrimTable;
	static vector<float>AngleTable;
	static float MinTrim;
	static float MaxTrim;


	float xVal;
	vector<float>FloodingAngle;
	LCConstEntry KY[MAX_TRIM_ENTRIES][MAX_ANGLE_ENTRIES];

	LCKYEntry(TSNConfigString &ConfigString, bool TurnTable);
	float GetKY(float Trim, float List);
	float GetFloodingAngle(float Trim);
};

