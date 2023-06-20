//////////////////////////////////////////////////////////
//
//	Graph object
//
//////////////////////////////////////////////////////////

Graph::Graph(short x, short y, short W, short H,float MinX, float MaxX,
			 float MinY, float MaxY, DirType Dir)
:XMin(MinX),XMax(MaxX),YMin(MinY),YMax(MaxY),PlotBuffer(NULL),PlotPtr(0),
Direction(Dir)

{
	grafPort *ScreenPort;
	XScale = 1000.0/(XMax - XMin);
	YScale = 1000.0/(YMax - YMin);

	GetPort(&ScreenPort);
	InitPort(&WinPort);
	ClipRegion((region*)SubRgn);
	MovePortTo(x,y);
	PortSize(Width,Height);
	PortOrigin(lowerLeft);
	SetRect( &virtRect,(int)(XMin*XScale),(int)(YMin*YScale),(int)(XMax*XScale),(int)(YMax*YScale));
	VirtualRect( &virtRect );
	SetLocal();
	SetRect( &GrafArea   ,1,1,Width,Height);
	SetRect( &FrameArea  ,0,0,Width,Height);
	ClipRect(NULL);
	ProtectRect(&FrameArea);
	FrameRect(&FrameArea);
	PenColor(Black);
	PaintRect( &GrafArea);
	ClipRect( &GrafArea );
	SetVirtual();
	ProtectRect(NULL);
	SetPort(ScreenPort);
	ClipRegion((region*)SubRgn);
}


Graph::Graph(short x, short y, short W, short H,float MinX, float MaxX,
			 float MinY, float MaxY, short XTics, short YTics, short BSize,
			 short XTxtSpt, short XDecPnt, DirType Dir, char* txt)
:XPos(x),YPos(y),Width(W),Height(H),
XMin(MinX),XMax(MaxX),YMin(MinY),YMax(MaxY),PlotBuffer(NULL),
BufSize(BSize),Direction(Dir)
{
	Scale(MinX,MaxX,MinY, MaxY, XTics, YTics, XTxtSpt, XDecPnt, txt);

	if( BufSize ) {
		PlotBuffer = new point[BufSize];
	}

}

void Graph::Scale(float MinX,float MaxX,float MinY, float MaxY, short XTics,
				  short YTics, short XTxtSpt, short XDecPnt, char* txt  )
{
	short XOrg;
	short YOrg ;
	short SYCor ;
	short TxtXPos ;
	short XStpCnt  = 0 ;
	char Buf[10] ;

	switch( Direction ) {
		case LeftAxis :
			XOrg = 7*XFact;
			break;
		case RightAxis :
			XOrg = 6*XFact;
			break;
	}
	if( Abu ) {
		YOrg = ABU_YFACT + 2*ABU_YCOR;
		SYCor = 0 ;
	} else {
		YOrg = AWS_YFACT;
		SYCor = AWS_YCOR ;
		PenColor(Green);
	}
	XMin = MinX;
	YMin = MinY;
	XMax = MaxX;
	YMax = MaxY;
	XScale = 1000/(XMax - XMin);
	YScale = 1000/(YMax - YMin);

	PlotPtr = 0;

	grafPort *ScreenPort;
	GetPort(&ScreenPort);
	//PushGrafix(&OldPort);
	InitPort(&WinPort);
	ClipRegion((region*)SubRgn);
	MovePortTo(XPos,YPos-4*YCor);
	PortSize(Width,Height+4*YCor);
	PortOrigin(lowerLeft);

#ifdef VXWORKS
	SetFont(&sys08_8x8);
#else
	SetFont(Font[FONT_SYSTEM08].Ptr);
#endif

	switch( Direction ) {
		case LeftAxis   :
			PLine( Width-1,YOrg,XOrg, YOrg);
			PLine( XOrg, YOrg,XOrg, Height);
			TxtXPos = XOrg ;
			MoveTo( XOrg,0);
			break;
		case RightAxis  :
			PLine( 1,YOrg,Width-XOrg, YOrg);
			PLine( Width-XOrg, YOrg, Width-XOrg, Height);
			TxtXPos = Width - XOrg -2*XFact ;
			MoveTo( Width-XOrg, 0);
			break;
	}
	//LineTo(Width,Height);
	switch( Direction ) {
		case LeftAxis   :
			TextAlign(alignCenter,alignBottom);
			{
				float LocScale = (Width-XOrg)/( XMax - XMin);
				float XStep = ( XMax - XMin ) / XTics ;
				short YP = 2*YCor ;
				XTics += 2;
				for( float XVal=XMin; XTics-- ; XVal += XStep ) {
					float XP = (XVal-XMin)*LocScale;
					XStpCnt++ ;
					if( XStpCnt >= XTxtSpt ) {
						YP = 3*YCor ;
					} else {
						YP = 2*YCor ;
					}
					PLine((int)XP+XOrg,YOrg,(int)XP+XOrg,YOrg-YP);
					if( XStpCnt >= XTxtSpt ) {
						if( !Abu ) {
							PenColor(Green);
						}
						sprintf(Buf,"%*.*f",5,XDecPnt,fabs(XVal));
						if( XVal > XMin ) PWrite_on_p(XP+XOrg-XFact,SYCor,"%-s",Buf);
						XStpCnt = 0;
						PenColor(White) ;
					}
				}
			}
			TextAlign(alignRight,alignMiddle);
			{
				float LocScale = (Height-YOrg)/( YMax - YMin);
				float YStep = ( YMax - YMin ) / YTics;
				YTics ++ ;
				for( float YVal=YMin; YTics-- ; YVal += YStep ) {
					int YP = (int)round((YVal-YMin)*LocScale)+YOrg;
					PLine(XOrg,YP,XOrg-4,YP);
					if( !Abu ) {
						PenColor(Green);
					}
					if( (MaxY-MinY) > 100 ) {
						PWrite_on_p(XOrg-5,YP,"%5.0f",YVal);
					} else {
						PWrite_on_p(XOrg-5,YP,"%5.1f",YVal);
					}
					PenColor(White) ;
				}
			}
			break;
		case RightAxis :
			TextAlign(alignCenter,alignBottom);
			{
				float LocScale = (Width-XOrg)/( XMax - XMin);
				float XStep = ( XMax - XMin ) / XTics;
				short XT = XTics + 1 ;
				for( float XVal=XMin; XT-- ; XVal += XStep ) {
					float XP = (XVal-XMin)*LocScale;
					PLine((int)XP,YOrg,(int)XP,YOrg-2*YCor);
				}
				XStep = ( XMax - XMin ) / (XTics / XTxtSpt);
				XTics /= XTxtSpt ;
				XTics -- ;
				if( !Abu ) {
					PenColor(Green);
				}
				for( float XVal=XMin+XStep; XTics-- ; XVal += XStep ) {
					float XP = (XVal-XMin)*LocScale;
					ProtectRect(&screenR);
					sprintf(Buf,"%*.*f",5,XDecPnt,fabs(XVal));
					if( XVal > XMin ) PWrite_on_p(XP-XFact,SYCor,"%s",Buf);
					ProtectRect(NULL);
				}
				PenColor(White) ;
			}
			TextAlign(alignLeft,alignMiddle);
			{
				float LocScale = (Height-YOrg)/( YMax - YMin);
				float YStep = ( YMax - YMin ) / YTics;
				YTics ++ ;
				for( float YVal=YMin; YTics-- ; YVal += YStep ) {
					int YP = (int)round((YVal-YMin)*LocScale)+YOrg;
					PLine(Width-XOrg,YP,Width-XOrg+4,YP);
					ProtectRect(&screenR);
					if( !Abu ) {
						PenColor(Green);
					}
					if( (MaxY-MinY) > 100 ) {
						PWrite_on_p(Width-XOrg+7,YP,"%5.0f",YVal);
					} else {
						Write_on_p(Width-XOrg+7,YP,"%5.1f",YVal);
					}
					PenColor(White) ;
					ProtectRect(NULL);
				}
			}
			break;
	}
	if ( Abu){
		PWrite_on_p(TxtXPos,3*YCor-2,txt);
		SetFont(NULL);
	}else {
		PenColor(Green);
		PWrite_on_p(TxtXPos,3*YCor,txt);
#ifdef VXWORKS
		SetFont(&sys_72_8x19);
#else
		SetFont(Font[FONT_SYSTEM72].Ptr);
#endif
	}
	SetPort(ScreenPort);
	InitPort(&PlotPort);
	ClipRegion((region*)SubRgn);
	switch( Direction ) {
		case LeftAxis  :
			MovePortTo(XPos+XOrg,YPos);
			break;
		case RightAxis :
			MovePortTo(XPos,YPos);
			break;
	}
	PortSize(Width-XOrg,Height-YOrg);
	PortOrigin(lowerLeft);

	SetRect( &virtRect,(int)(XMin*XScale),(int)(YMin*YScale),(int)(XMax*XScale),(int)(YMax*YScale));
	VirtualRect( &virtRect );
	SetLocal();
	SetRect( &GrafArea   ,1,1,Width,Height);
	ClipRect(NULL);

	PenColor(Black);
	ClipRect( &GrafArea );
	SetVirtual();
	SetPort(ScreenPort);
	ProtectRect(NULL);

}

void Graph::Move(float x, float y)
{
	int XVal = (int)(x*XScale);
	int YVal = (int)(y*YScale);
	grafPort *ScreenPort;
	GetPort(&ScreenPort);
	SetPort(&PlotPort);
	ClipRegion((region*)SubRgn);
	MoveTo(XVal,YVal);
	SetPort(ScreenPort);
	if( PlotBuffer ) {
		PlotPtr =1;
		PlotBuffer[0].X =XVal;
		PlotBuffer[0].Y =YVal;
	}
}

void Graph::ScrollLine(float x, float y, short Color)
{
	int YVal = (int)(y*YScale);
	grafPort *ScreenPort;
	GetPort(&ScreenPort);
	SetPort(&PlotPort);
	ClipRegion((region*)SubRgn);
	PenColor(Color);
	if( PlotPtr >= BufSize ) {
		RasterOp(zCLEARz);
		GUI_DrawPolyLine(&PlotBuffer[1], PlotPtr-1, PlotBuffer[0].X, PlotBuffer[0].Y);
		PolyLine(PlotPtr,PlotBuffer);
		for( short i=0; i < BufSize-1; i++ ) {
			PlotBuffer[i].Y = PlotBuffer[i+1].Y;
		}
		PlotBuffer[BufSize -1].Y = YVal;
	} else {
		int XVal = (int)(x*XScale);
		PlotBuffer[PlotPtr].X = XVal;
		PlotBuffer[PlotPtr].Y = YVal;
		PlotPtr++;
	}
	RasterOp(zREPz);
	ProtectRect(&GrafArea);
	PolyLine(PlotPtr,PlotBuffer);
	ProtectRect(NULL);
	SetPort(ScreenPort);
}

void Graph::DrawLine(float x, float y, short Color)
{
	int XVal = (int)(x*XScale);
	int YVal = (int)(y*YScale);
	point NewPos,OldPos;
	OldPos.X = PlotPort.pnLoc.X;
	OldPos.Y = PlotPort.pnLoc.Y;
	if( XVal == OldPos.X ) OldPos.X++;
	if( YVal == OldPos.Y ) OldPos.Y++;
	NewPos.X = XVal;
	NewPos.Y = YVal;
	rect PRect;
	Pt2Rect(&NewPos,&OldPos,&PRect);
	grafPort *ScreenPort;
	GetPort(&ScreenPort);
	SetPort(&PlotPort);
	ClipRegion((region*)SubRgn);
	PenColor(Color);

	ProtectRect(&PRect);
	LineTo(XVal,YVal);
	ProtectRect(NULL);
	SetPort(ScreenPort);
}

void Graph::DrawXAxes(short Color)
{
	point MinPos,MaxPos;
	MinPos.X = (int)(XMin*XScale);
	MinPos.Y = 0;
	MaxPos.X = (int)(XMax*XScale);
	MaxPos.Y = 1;
	rect PRect;
	Pt2Rect(&MinPos,&MaxPos,&PRect);
	grafPort *ScreenPort;
	GetPort(&ScreenPort);
	SetPort(&PlotPort);
	ClipRegion((region*)SubRgn);
	PenColor(Color);
	PenDash(1);
	MoveTo(MinPos.X, 0);
	ProtectRect(&PRect);
	LineTo(MaxPos.X, 0);
	ProtectRect(NULL);
	PenDash(0);
	SetPort(ScreenPort);
}

void Graph::DrawLimit(short y, short Color)
{
	point MinPos,MaxPos;
	MinPos.X = (int)(XMin*XScale);
	MinPos.Y = y;
	MaxPos.X = (int)(XMax*XScale);
	MaxPos.Y = y+1;
	rect PRect;
	Pt2Rect(&MinPos,&MaxPos,&PRect);
	grafPort *ScreenPort;
	GetPort(&ScreenPort);
	SetPort(&PlotPort);
	ClipRegion((region*)SubRgn);
	PenColor(Color);
	PenDash(1);
	MoveTo(MinPos.X, y);
	ProtectRect(&PRect);
	LineTo(MaxPos.X, y);
	ProtectRect(NULL);
	SetPort(ScreenPort);
}

void Graph::DrawMaxLimit(float y, short Color)
{
	int YVal = (int)(y*YScale);
	//if ( MaxLimit != MAXSHORT ) DrawLimit(MaxLimit,Black);
	//MaxLimit   = YVal;
	DrawLimit(YVal,Color);
}

void Graph::ClrScr(void)
{
	grafPort *ScreenPort;
	GetPort(&ScreenPort);
	SetPort(&PlotPort);
	ClipRegion((region*)SubRgn);

	SetRect( &GrafArea,(int)(XMin*XScale),(int)(YMin*YScale),(int)(XMax*XScale),(int)(YMax*YScale));
	ProtectRect(&GrafArea);
	EraseRect(&GrafArea);
	ProtectRect(NULL);
	SetPort(ScreenPort);
}

Graph::~Graph(void)
{
	if( PlotBuffer ) delete PlotBuffer;
	PlotBuffer = NULL;
}

