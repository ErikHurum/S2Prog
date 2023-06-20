typedef struct {
	float Location,Weight;
}WeightEntry;

class LCSteelWeight
{
private:
	vector<WeightEntry>WeightData;
	float Offset;

public:
    static LCSteelWeight  *SteelWeightDistibution;

	LCSteelWeight(float pOffset=0.0);
	int   LoadConfigString(TSNConfigString &ConfigString);
    float GetWeightAtLocation(float Location);
    float GetSectionWeight(float FirstFrame, float LastFrame);
};



