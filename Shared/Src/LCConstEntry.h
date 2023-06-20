class LCConstEntry {
private:
	float   a,b,c;

  
public:
	float Value;
	int   Constants;

	LCConstEntry(void);
	void MakeConstants(float x1,float y1, float x2, float y2);
	void MakeConstants(float x1,float y1, float x2, float y2, float x3, float y3);
	float Calc(float Val);
	float DerivedMax(void);
};

