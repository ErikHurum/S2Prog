class Graph {
private:
	DirType  Direction;
	short    XPos,YPos,
		Width,
		Height,
		BufSize,PlotPtr;
	GUI_POINT *PlotBuffer;
	float    XMin,XMax,YMin,YMax,XScale,YScale;
	rect     GrafArea,FrameArea,virtRect, PlotRect;

public:
	WM_HWIN WinPort, PlotPort;

	void Scale(float MinX,float MaxX,float MinY, float MaxY, short XTics,
			   short YTics, short XTxtSpt, short XDecPnt, char* txt  );

	Graph(short x, short y, short W, short H,float MinX, float MaxX,
		  float MinY, float MaxY, DirType Dir);


	Graph(short x, short y, short W, short H,float MinX, float MaxX,
		  float MinY, float MaxY, short XTics, short YTics, short BSize,
		  short XTxtSpt, short XDecPnt, DirType Dir, char* txt);

	void Move(float x, float y);
	void ScrollLine(float x, float y, short Color);
	void DrawLine(float x, float y, short Color);
	void DrawXAxes(short Color);
	void DrawLimit(short y, short Color);
	void DrawMaxLimit(float y, short Color);


	void ClrScr(void);

	~Graph(void);

};

