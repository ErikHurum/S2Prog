#include <TSNIncludes.h>
#pragma hdrstop


///////////////////////////////////////////////////////////
//
//	 Menu definitions for ANWin
//
//
//
//
///////////////////////////////////////////////////////////


ValueList LCStabCalc::StabCalcValueList[] =  {
	{L_WORD679          ,L_WORD237,SVT_S_DISPLACEMENT},
	{L_WORD713          ,L_WORD237,SVT_S_DEADWEIGHT},
	{L_WORD682          ,L_WORD237,SVT_S_VCG},
	{L_WORD683          ,L_WORD237,SVT_S_LIST},
	{L_WORD426          ,L_WORD237,SVT_S_TRIM},
	{L_WORD769          ,L_WORD237,SVT_S_LIST_ANGLE},
	{L_WORD768          ,L_WORD237,SVT_S_TRIM_ANGLE},
	{L_WORD684          ,L_WORD237,SVT_S_DFT_MS},
	{L_WORD685          ,L_WORD237,SVT_S_LIQ_WGT},
	{L_WORD686          ,L_WORD237,SVT_S_SOL_WGT},
	{L_WORD735          ,L_WORD421,SVT_S_DFT_MS_P},
	{L_WORD736          ,L_WORD422,SVT_S_DFT_MS_S},
	{L_WORD734          ,L_WORD420,SVT_S_DFT_F},
	{L_WORD737          ,L_WORD423,SVT_S_DFT_A},
	{L_WORD431          ,L_WORD237,SVT_S_DFT_MRK},
	{L_WORD688          ,L_WORD237,SVT_S_TFS_MOM},
	{L_WORD689          ,L_WORD237,SVT_S_TOTAL_L_MOM},
	{L_WORD690          ,L_WORD237,SVT_S_TOTAL_T_MOM},
	{L_WORD691          ,L_WORD237,SVT_S_TOTAL_V_MOM},
	{L_WORD692          ,L_WORD237,SVT_S_VCG_SOL},
	{L_WORD693          ,L_WORD237,SVT_S_VCG_ADJ},
	{L_WORD694          ,L_WORD237,SVT_S_MAX_VCG},
	{L_WORD695          ,L_WORD237,SVT_S_VCG_MARGIN},
	{L_WORD696          ,L_WORD237,SVT_S_DAM_MAX_VCG},
    {L_WORD697          ,L_WORD237,SVT_S_DAM_VCG_MARGIN},
    {L_WORD698          ,L_WORD237,SVT_S_IMMERSION},
	{L_WORD699          ,L_WORD237,SVT_S_KM},
	{L_WORD700          ,L_WORD237,SVT_S_GM_SOL},
	{L_WORD701          ,L_WORD237,SVT_S_GM_LIQ},
    {L_WORD702          ,L_WORD237,SVT_S_TCF},
    {L_WORD703          ,L_WORD237,SVT_S_LCF},
	{L_WORD714          ,L_WORD237,SVT_S_LCB},
	{L_WORD704          ,L_WORD237,SVT_S_TCG},
	{L_WORD705          ,L_WORD237,SVT_S_LCG},
	{L_WORD706          ,L_WORD237,SVT_S_GZ},
	{L_WORD707          ,L_WORD237,SVT_S_GZ_30},
	{L_WORD708          ,L_WORD237,SVT_S_GZ_MAX},
	{L_WORD709          ,L_WORD237,SVT_S_GZ_ANGLE},
	{L_WORD710          ,L_WORD237,SVT_S_GZ_A0_30},
	{L_WORD711          ,L_WORD237,SVT_S_GZ_A30_40},
	{L_WORD740          ,L_WORD237,SVT_S_GZ_A0_40},

	{L_WORD717          ,L_WORD237,SVT_S_MAX_BM_FRAME_NAME},
	{L_WORD715          ,L_WORD237,SVT_S_MAX_BM},
	{L_WORD717          ,L_WORD237,SVT_S_MAX_SF_FRAME_NAME},
	{L_WORD716          ,L_WORD237,SVT_S_MAX_SF},


	{L_WORD9            ,L_WORD237,SVT_CARGO_WEIGHT},
	{L_WORD47           ,L_WORD237,SVT_BALLAST_WEIGHT},
	{L_WORD48           ,L_WORD237,SVT_HEAVY_FUEL_WEIGHT},
	{L_WORD49           ,L_WORD237,SVT_DIESEL_OIL_WEIGHT},
	{L_WORD50           ,L_WORD237,SVT_LUBRICANTS_WEIGHT},
	{L_WORD51           ,L_WORD237,SVT_FRESH_WATER_WEIGHT},
	{L_WORD52           ,L_WORD237,SVT_MISC_WEIGHT},
	{L_WORD733          ,L_WORD237,SVT_SOLIDS_WEIGHT},
	{L_WORD642          ,L_WORD237,SVT_VOID_SPACE_WEIGHT},
};


LCStabCalc *LCStabCalc::StabCalc= NULL;
bool LCStabCalc::MidShipRef     = true;
LCStabCalc::LCStabCalc(void)
{
	StabCalc = this;
	if ( LCShipData::IsOnline ) {
		SWDensity = PROSystemData::SeaWaterDensity;
	} else {
		SWDensity = DNS_SEA_WATER;
	}
	MaxSfFrame          = NULL;
	MaxBmFrame          = NULL;
	Displacement        = 0.0;
	List                = 0.0;
	List_in_rad         = 0.0;
	Trim                = 0.0;
	Trim_in_rad         = 0.0;
	DraftMS             = 0.0;
	DraftMSP            = 0.0;
	DraftMSS            = 0.0;
	DraftF              = 0.0;
	DraftA              = 0.0;
	DraftMrk            = 0.0;
	Immersion           = 0.0;
	VCG                 = 0.0;
	VCGSolid            = 0.0;
	VCGCorrection       = 0.0;
	MaxVCG              = 0.0;
	VCGMargin           = 0.0;
	DamageMaxVCG        = 0.0;
	DamageVCGMarg       = 0.0;
	KM                  = 0.0;
	GMSolid             = 0.0;
	GMCorrected         = 0.0;
	TCF                 = 0.0;
	LCF                 = 0.0;
	LCB                 = 0.0;
	UnadjustedLCB       = 0.0;
	TCG                 = 0.0;
	LCG                 = 0.0;
	Total_L_Moment      = 0.0;
	Total_T_Moment      = 0.0;
	Total_V_Moment      = 0.0;
	TFS_Moment          = 0.0;
	GZ                  = 0.0;
	GZ30                = 0.0;
	GZMax               = 0.0;
	GZAngle             = 0.0;
	GZArea0_30          = 0.0;
	GZArea30_40         = 0.0;
	GZArea0_40          = 0.0;
	FldAng              = 0.0;
	ReserveDownflooding = 0.0;
}

///////////////////////////////////////////////////////////
//
//	 List calculation for ships using KY-curves
//
//	 Calculate KY for given Angle and displacement using KY-tables
//	 Angle >=0
//
///////////////////////////////////////////////////////////



float LCStabCalc::CalculateGZ(float Angle)
{
	float DraftCF = DraftMS-LCF*sin(Trim_in_rad);
	if ( TSNTableKY::KY_Table ) {
		return(TSNTableKY::KY_Table->Calc_GZ(VCG,DraftMS, DraftCF,Displacement, Trim, Angle));
	} else return(0.0);
}

void LCStabCalc::Calc_List(void)
{
	////////////////////////////////////////////////////////////////////
	//
	// Make a GZ table from 0^
	// GZ_ENTRIES = number of entries in the table
	// GZ_ANGLE_STEP = table resolution.
	// The standard, and according to rules is that
	// the table shall be calculated for the range
	// 0~60^
	// A preliminary maximum GZ is found when the table is
	// made. The final maximum GZ is found as the derived of the
	// second degree interpolation curve found when calculating the
	// preliminary GZ max.
	// The accuracy is slightly improved by direct search for the maximum
	// based on direct GZ-calculation. However, the the time saving
	// by the current aproach justifies use of the current algoritm
	//
	////////////////////////////////////////////////////////////////////

	float Angle    = 0.0;
	float Max      = 0.0;
	int   MaxIndex = 0;
	GZ_Table.Clear();
	for ( int i=0; i < GZ_ENTRIES; i++ ) {
		float NewGZ = CalculateGZ(Angle);
		GZ_Table.NewValue(Angle,NewGZ);
		if ( NewGZ > Max ) {
			Max      = NewGZ;
			MaxIndex = i;
		}
		Angle += GZ_ANGLE_STEP;
	}
	GZ_Table.MakeConstants();
	GZ_Table.FindMinMax();
	GZAngle     = GZ_Table.DerivedMax(MaxIndex);
	GZMax       = GZ_Table.Calc_Y(GZAngle);

	float a = 0.0;
	float b = GZAngle;
	float AbsTCG = fabs(TCG);
	float Diff,x;
	int   ExitCnt = 0;
	////////////////////////////////////////////////////////////////////////
	//
	// Use binary search for intercept of THA and GZ. The solution must be
	// in the interval between 0.0 and GZMax. In case of no solution
	// force exit according to requirements from DNV. ( All iteration
	// loops shall have loop control ("safety exit")
	// The idea of this algoritm is that the ship will be in balance
	// when GZ and TCG are equal.
	// Some vesses, with special hull shape, will have two or more
	// GZ-max points under certain cirumstances. In such cases, the correct
	// list may not be found.
	//
	////////////////////////////////////////////////////////////////////////
	do {
		x = ( a + b )/2.0;
		Diff = AbsTCG*cos(x)-GZ_Table.Calc_Y(x);

		if ( Diff > 0 )	a = x;
		else b = x;
	} while ( fabs(Diff) > 0.0001 && ExitCnt++ < 50 );
	GZ  = GZ_Table.Calc_Y(x);

	if ( TCG < 0.0 ) x = -x;
	List_in_rad = x;
	List        = tan(x)*PROProjectInfo::Width;
	GZ30        = GZ_Table.Calc_Y(30/RAD_FACTOR);

	GZArea0_30  = GZ_Table.Area(0.0,30/RAD_FACTOR,16);
	GZArea30_40 = GZ_Table.Area(30/RAD_FACTOR,40/RAD_FACTOR,5);
	GZArea0_40  = GZArea0_30+GZArea30_40;
}




/////////////////////////////////////////////////////////////////////////
//
//	Calculates the weights for liquids and	solids aboard the vessel.
// The Transverce, vertical and longitudinal moments are calculated.
// The light ship is included.
// The total transverce free surface moments of inertia is calculated
//
/////////////////////////////////////////////////////////////////////////

void LCStabCalc::Add_Weights(void)
{
	LCLocationData::ResetWeights();
	Total_L_Moment = LCShipData::LCShip->LTrimMoment;
	Total_T_Moment = LCShipData::LCShip->TTrimMoment;
	Total_V_Moment = LCShipData::LCShip->VTrimMoment;
	LCLocationData::Liquid_Weight  = 0.0;
	LCLocationData::Solid_Weight   = 0.0;
	TFS_Moment     = 0.0;

	// Set all section weights to 0.0
	for ( unsigned i=0; i < LCSectionData::Table.size(); i++ ) {
		LCSectionData::Table[i]->DeadWeight = 0.0;
	}
	for ( unsigned i=0; i < LCLocationData::Table.size(); i++ ) {
		LCLocationData *L = LCLocationData::Table[i];
		L->CalculateMoments(&Total_L_Moment,&Total_T_Moment,&Total_V_Moment,&TFS_Moment);
		//if ( NewInput ) return;
	}
	Displacement = LCShipData::LCShip->Weight + LCLocationData::Liquid_Weight + LCLocationData::Solid_Weight;
}

void LCStabCalc::Adjust_Draft(void)
{
	DraftMS = TSNTableHydrostatic::Disp_Tab->GetDraft(Displacement*1.025/SWDensity,Trim)+LCShipData::LCShip->KeelThikness;
}


// Created 21/11/01 RB/EHS
// Improved search
#define LOOP_CNT_LIMIT 20
void LCStabCalc::FindTrim(void)
{
	float OldTrim  = 0.0;
	float MinTrim  = TSNTableHydrostatic::LCB_Tab->MinTrim;
	float MaxTrim  = TSNTableHydrostatic::LCB_Tab->MaxTrim;
	int ExitCnt = 0;
	while ( (  fabs( LCG - LCB ) >= 0.002 )
			&& ( fabs(MaxTrim-MinTrim) > 0.001 )
			&& ( MaxTrim > MinTrim )
			&& ( ExitCnt++ < LOOP_CNT_LIMIT )
		  ) {
		Trim = (MinTrim+MaxTrim)/2.0;
		// Have the trim changed that much that we should make a new draft
		// calculation?
		if ( fabs(OldTrim-Trim) > 0.10 ) {
			Adjust_Draft();
			OldTrim = Trim;
		}
		LCB = TSNTableHydrostatic::LCB_Tab->GetValue(DraftMS,Trim);

		// Find out which interval we should continue in
		// Find out which interval we should continue in
		if ( LCG < LCB ) {
			MaxTrim = Trim;
		} else {
			MinTrim = Trim;
		}
	}
	// Har vi funnet riktig trim basert på LCB?

	float trimMaxDiff = fabs(MinTrim-TSNTableHydrostatic::LCB_Tab->MaxTrim);
	float trimMinDiff = fabs(MaxTrim-TSNTableHydrostatic::LCB_Tab->MinTrim);
	float trimDiff    = min(trimMaxDiff,trimMinDiff);// Check if we have aproached the end of the range for the table
	if ( ( MaxTrim < MinTrim ) || ( trimDiff < 0.002 ) || ( ExitCnt >= LOOP_CNT_LIMIT ) ) {
		float MCTTrim = (LCG - UnadjustedLCB)*Displacement / TSNTableHydrostatic::MCT_Tab->GetValue(DraftMS,Trim);
    	// Trim based on MCT must exceed this limt. If not, use the other based on seach, changing LCB
		if (fabs(MCTTrim) > fabs(Trim)) {
			Trim = MCTTrim;
		}
	} else {
		if ( ( MaxTrim < MinTrim ) || ( ExitCnt >= LOOP_CNT_LIMIT ) ) {
			// It seems that we have to find the trim based on a basic calculation,
			// using moment to change trim.
			float NewTrim = (LCG - UnadjustedLCB)*Displacement / TSNTableHydrostatic::MCT_Tab->GetValue(DraftMS,Trim);
			// First see if we are nearby and can use MCT.
			if ( fabs(NewTrim - Trim ) > 0.1 ) {
				Trim = (LCG - UnadjustedLCB)*Displacement / TSNTableHydrostatic::MCT_Tab->GetValue(DraftMS,0.0);
			} else {
				Trim = NewTrim;
			}
		}
	}

	// Have the trim changed that much that we should make a new draft
	// calculation?
	if ( fabs(OldTrim - Trim) > 0.10 ) Adjust_Draft();
}
#undef LOOP_CNT_LIMIT

///////////////////////////////////////////////////////////////////////////
//
//  Calculate the stability
//
//  If trim corrected hydrostatic tables are available, the routine will
//  make a binary within the trim range from the hydrostatics.
//  The aproach is to change the adjust the ship trim until the
//  longitudinal centre of buoyancy is equal to the centre of gravity
//  At that point the ship will be in equilibrium.
//
//  Because of class rules, a safety exit must be available. A counter limits
//  the number of trials. If this aproach was unsuccessful, the basic
//  trim calculation is based on moment to change trim. The result will be
//  less accurate.
//
//	  Some hydrostatic tables refers to the centre of flotation instead of the
//   mid ship. If that is the case, a correction for the draft calculations
//   must be done after finalizing all the hydrostatics.
//
///////////////////////////////////////////////////////////////////////////

void LCStabCalc::Calculate(void)
{
	SWDensity =     PROSystemData::SeaWaterDensity;
	LCShipData::LCShip->GetTrimListData();
	Add_Weights();

	Trim    = 0.0;
	List    = 0.0;
	Adjust_Draft();
	VCGSolid      = Total_V_Moment/Displacement;
	VCGCorrection = TFS_Moment/Displacement;
	VCG           = VCGSolid + VCGCorrection;
	LCG           = Total_L_Moment/Displacement;
	TCG           = Total_T_Moment/Displacement;


	LCB = TSNTableHydrostatic::LCB_Tab->GetValue(DraftMS,0.0);
	UnadjustedLCB  = LCB;
	FindTrim();
	if ( fabs(Trim) > 6.0 ) {
		Trim = 0.0;
	}
	Trim_in_rad = asin(Trim/PROProjectInfo::LengthBetweenPP);

	LCF = TSNTableHydrostatic::LCF_Tab->GetValue(DraftMS,Trim);

	Calc_List();

	TCF = TSNTableHydrostatic::TCF_Tab->GetValue(DraftMS,Trim);

	KM  = TSNTableHydrostatic::KMT_Tab->GetValue(DraftMS ,Trim);

	GMSolid         = KM - VCGSolid;
	GMCorrected     = KM - VCG;
	if ( TSNTableHydrostatic::MaxVCG_Tab ) {
		MaxVCG    = TSNTableHydrostatic::MaxVCG_Tab->GetValue(DraftMS,Displacement,Trim);
		VCGMargin = MaxVCG - VCG;
	} else {
		MaxVCG = 0.0;
	}
	if ( TSNTableHydrostatic::DamageMaxVCG_Tab ) {
		DamageMaxVCG  = TSNTableHydrostatic::DamageMaxVCG_Tab->GetValue(DraftMS,Displacement,Trim);
		DamageVCGMarg = DamageMaxVCG - VCG;
	} else {
		DamageMaxVCG = 0.0;
	}
	if ( TSNTableHydrostatic::FloodinAngle_Tab ) {
		FldAng = TSNTableHydrostatic::FloodinAngle_Tab->GetValue(DraftMS,Displacement,Trim)/RAD_FACTOR;
	}
	ReserveDownflooding = LCOpeningData::FindDownfloodingPoint(DraftMS,Trim_in_rad,0.0);
	{
		float Margin = MAXFLOAT;
		float FldAng = 90.0;
		for ( float Angle=0.0; Angle <= 70.0; Angle += 5.0 ) {
			float tmpMargin = LCOpeningData::FindDownfloodingPoint(DraftMS,Trim_in_rad,Angle/RAD_FACTOR);
			if ( FldAng != 90.0 && tmpMargin <= 0.0 ) {
				FldAng = Angle;
			}
		}

	}

	//if ( NewInput ) return;

	// Is the hydrostatic tables based on draft at centre of flotation
	// or midship? If so correct the draft to midship
	if ( !MidShipRef ) {
		DraftMS += Trim*LCF/PROProjectInfo::LengthBetweenPP;
	}
	DraftF   = DraftMS+Trim/2.0;
	DraftA   = DraftF-Trim;
	DraftMSS = DraftMS+List/2.0;
	DraftMSP = DraftMSS - List;

	DraftMrk  = DraftA+Trim*LCShipData::LCShip->APP_to_Mark/PROProjectInfo::LengthBetweenPP;
	Immersion = TSNTableHydrostatic::TPM_Tab->GetValue(DraftMS,Trim);
}

/////////////////////////////////////////////////////////////////////
//  Sharing force/Bending moment.
//
//
/////////////////////////////////////////////////////////////////////

float LCStabCalc::Calc_Buoyancy(void)
{
	float TotBuoyancy = 0.0;
	for ( unsigned i=0; i < LCSectionData::Table.size(); i++ ) {
		TotBuoyancy += LCSectionData::Table[i]->GetBuoyancy(DraftA, Trim_in_rad);
	}
	return TotBuoyancy;
}

///////////////////////////////////////////////////////////////
//
// Locate maximum sharing force and bending moment
//
///////////////////////////////////////////////////////////////

void LCStabCalc::FindMaxSfBm(void)
{
	float MaxSf=0.0   ,MaxBm=0.0;
	LCFrameData *MxSfFrame=NULL,*MxBmFrame=NULL;

	for ( unsigned i=0; i < LCFrameData::FrameList.size(); i++ ) {
		LCFrameData *F = LCFrameData::FrameList[i];
		if ( F->HasStrengthCheck ) {
			float MySf = fabs(F->Sf );
			if ( MySf > MaxSf ) {
				MaxSf = MySf;
				MxSfFrame = F;
			}
			float MyBm = fabs(F->CorrBm );
			if ( MyBm > MaxBm ) {
				MaxBm = MyBm;
				MxBmFrame = F;
			}
		}
	}
	MaxSfFrame = MxSfFrame;
	MaxBmFrame = MxBmFrame;

}

///////////////////////////////////////////////////////////////
//
// Strength calculation.
// This module calculates the longitudinal bending moment and share
// force
//
///////////////////////////////////////////////////////////////

void LCStabCalc::Strength(void)
{
	// Correct the buoyancy. The total bouyancy must be
	// equal to the displacement. This should increase the
	// accuracy of the strength calculation.
	float TotBuoyancy        =  Calc_Buoyancy();
	float BuoyancyCorrection =  1.0;
	if ( TotBuoyancy ) BuoyancyCorrection = Displacement/TotBuoyancy;

	// SF & BM is by definition 0.0 at the FPP and APP, but
	// here we have decided first and last frame !
	// The variable FppSection is  the index to FPP
	// The variable AppSection is  the index to APP
	// Anyway start at the very first frame instead of APP
	LCSectionData::AppSection = 0;
	if ( LCShipData::BMCalcAftToFore ) {
		LCFrameData::Table[LCSectionData::AppSection]->Sf = 0.0;
		LCFrameData::Table[LCSectionData::AppSection]->Bm = 0.0;
		for ( unsigned i=LCSectionData::AppSection; i < LCSectionData::Table.size(); i++ ) {
			LCSectionData::Table[i]->CalculateLoadAft(BuoyancyCorrection);
		}
	} else {
		LCFrameData::Table[LCSectionData::FppSection]->Sf = 0.0;
		LCFrameData::Table[LCSectionData::FppSection]->Bm = 0.0;
		vector<LCSectionData*>::reverse_iterator pBIt;
		for ( pBIt=LCSectionData::Table.rbegin(); pBIt!=LCSectionData::Table.rend(); pBIt++ ) {
			LCSectionData* SPtr = *pBIt;
			SPtr->CalculateLoadFwd(BuoyancyCorrection);
		}
		/*
		for ( int i=(int)LCSectionData::Table.size()-1; i >= LCSectionData::AppSection; i-- ) {
			LCSectionData::Table[i]->CalculateLoadFwd(BuoyancyCorrection);
		}
		*/
	}


	/////////////////////////////////////////////////////////////////
	//
	// The idea is that the bending moment shall be 0 at the last frame.
	// Normally, this will not be the case. Because of deviation in
	// buoyancy and weight distribution, the result is normally a
	// bending moment at the last frame. This bending moment is to be
	// considered as an accumulated error. The aproach to rectify this
	// problem is to adjust the direction of the bending moment curve down
	// so that is pass through 0 at the last frame.
	// Ref. Kompendium R-106.80 Lasting - Lossing, page 117 ~ 119
	//



	if ( LCShipData::BMCalcAftToFore ) {
		// Should maybe be FirstFrame??
		LCFrameData *F   = LCSectionData::Table[LCSectionData::FppSection]->LastFrame;
		// BM error from the last calculated frame, which is at FPP
		// in this case
		float BM_Error = F->Bm;	// TM
		float TotDist  = F->DistToFrame0;
		/*
		// Must have selectable zero BM definition point at PP or very end

		if( LoadCalcVersion >= LC_CALC_VERSION7) {
			TotDist -= SectionData::Table[0]->LastFrame->DistToFrame0;
		}
		*/
		for ( unsigned i=LCSectionData::AppSection; i < LCSectionData::Table.size(); i++ ) {
			LCSectionData::Table[i]->CorrectSfBmAft(BM_Error,TotDist);
		}
	} else {
		// BM error from the last calculated frame, which is at APPSection
		float BM_Error = LCSectionData::Table[LCSectionData::AppSection]->FirstFrame->Bm; // TM
		float TotDist  = LCSectionData::Table[LCSectionData::FppSection]->FirstFrame->DistToFrame0-
						 LCSectionData::Table[0]->FirstFrame->DistToFrame0;
		vector<LCSectionData*>::reverse_iterator pBIt;
		for ( pBIt=LCSectionData::Table.rbegin(); pBIt!=LCSectionData::Table.rend(); pBIt++ ) {
			LCSectionData* SPtr = *pBIt;
			SPtr->CorrectSfBmFwd(BM_Error,TotDist);
		}
		/*
		for ( unsigned i=LCSectionData::Table.size()-1; i >= LCSectionData::AppSection; i-- ) {
			LCSectionData::Table[i]->CorrectSfBmFwd(BM_Error,TotDist);
		}
		*/
	}
	for ( unsigned i=LCSectionData::AppSection; i < LCSectionData::Table.size(); i++ ) {
		LCSectionData::Table[i]->FirstFrame->CalcPercent();
	}
	LCSectionData::Table.back()->LastFrame->CalcPercent();

	FindMaxSfBm();

}

/////////////////////////////////////////////////////////////
//
// Check results against IMO requirements and other limits
//
/////////////////////////////////////////////////////////////
void LCStabCalc::CheckResult(void)
{
	WarningList.clear();
	IMOCriteriaList.clear();
	if ( Trim < TSNTableHydrostatic::LCB_Tab->MinTrim || Trim > TSNTableHydrostatic::LCB_Tab->MaxTrim ) {
		WarningList.push_back("Trim exceeds the values for which the hydrostatic tables has been predefined");
	}
	{
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_GM_LIQ, this,&Myunitstr);
		if ( GMCorrected < IMO_GM_MIN ) {
			AnsiString Message = "IMO Criteria not fulfilled : GM corrected for liquid "+ValueStr+" "+Myunitstr+" < 0.15 meter.";
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "IMO Criteria fulfilled : GM corrected for liquid "+ValueStr+" "+Myunitstr+" > 0.15 meter.";
			IMOCriteriaList.push_back(Message);
		}
	}
	{
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_GZ_30, this,&Myunitstr);
		if ( GZ30 < IMO_GZ30_MIN ) {
			AnsiString Message = "IMO Criteria not fulfilled : GZ at 30 degrees: "+ValueStr+" "+Myunitstr+" < 0.20 meter.";
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "IMO Criteria fulfilled : GZ at 30 degrees: "+ValueStr+" "+Myunitstr+" > 0.20 meter.";
			IMOCriteriaList.push_back(Message);
		}
	}
	{
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_GZ_ANGLE, this,&Myunitstr);
		if ( GZAngle < IMO_GZMAX_ANGLE ) {
			AnsiString Message = "IMO Criteria not fulfilled : GZ max angle: "+ValueStr+" "+Myunitstr+" < 25 degrees.";
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "IMO Criteria fulfilled : GZ max angle: "+ValueStr+" "+Myunitstr+" > 25 degrees.";
			IMOCriteriaList.push_back(Message);
		}
	}
	{
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_GZ_A0_30, this,&Myunitstr);
		if ( GZArea0_30 < IMO_GZAREA0_30 ) {
			AnsiString Message = "IMO Criteria not fulfilled : GZ area 0-30 degrees: "+ValueStr+" "+Myunitstr+" < 0.055 meter*rad.";
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "IMO Criteria fulfilled : GZ area 0-30 degrees: "+ValueStr+" "+Myunitstr+" > 0.055 meter*rad.";
			IMOCriteriaList.push_back(Message);
		}
	}
	{
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_GZ_A30_40, this,&Myunitstr);
		if ( GZArea30_40 < IMO_GZAREA30_40 ) {
			AnsiString Message = "IMO Criteria not fulfilled : GZ area 30-40 degrees: "+ValueStr+" "+Myunitstr+" < 0.03 meter*rad.";
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "IMO Criteria fulfilled : GZ area 30-40 degrees: "+ValueStr+" "+Myunitstr+" > 0.03 meter*rad.";
			IMOCriteriaList.push_back(Message);
		}
	}
	{
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_GZ_A0_40, this,&Myunitstr);
		if ( GZArea0_40 < IMO_GZAREA0_40 ) {
			AnsiString Message = "IMO Criteria not fulfilled : GZ area 0-40 degrees: "+ValueStr+" "+Myunitstr+" < 0.09 meter*rad.";
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "IMO Criteria fulfilled : GZ area 0-40 degrees: "+ValueStr+" "+Myunitstr+" > 0.09 meter*rad.";
			IMOCriteriaList.push_back(Message);
		}
	}
	{
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_DFT_MS, this,&Myunitstr);
		if ( DraftMS > LCShipData::MaxSummerDraft ) {
			AnsiString Message = "IMO Criteria not fulfilled : Max summer draft "+ValueStr+" "+Myunitstr+" > ";
			Message += LibGetValue(SVT_LS_MAX_SUMMER_DRAFT, LCShipData::LCShip,&Myunitstr);
			Message += " "+Myunitstr;
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "IMO Criteria fulfilled : Max summer draft "+ValueStr+" "+Myunitstr+" < ";
			Message += LibGetValue(SVT_LS_MAX_SUMMER_DRAFT, LCShipData::LCShip,&Myunitstr);
			Message += " "+Myunitstr;
			IMOCriteriaList.push_back(Message);
		}
	}

	if ( TSNTableHydrostatic::MaxVCG_Tab ) {
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_VCG_MARGIN, this,&Myunitstr);
		if ( VCGMargin <= 0.0 ) {
			AnsiString Message = "Criteria not fulfilled : VCG margin according to Max VCG curve."+ValueStr+" "+Myunitstr;
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "Criteria fulfilled : VCG margin according to Max VCG curve."+ValueStr+" "+Myunitstr;
			IMOCriteriaList.push_back(Message);
		}
	}
	if ( TSNTableHydrostatic::DamageMaxVCG_Tab ) {
		AnsiString Myunitstr;
		AnsiString ValueStr = LibGetValue(SVT_S_DAM_VCG_MARGIN, this,&Myunitstr);
		if ( DamageVCGMarg <= 0.0 ) {
			AnsiString Message = "Criteria not fulfilled : VCG margin according to DamageMax VCG curve."+ValueStr+" "+Myunitstr;
			WarningList.push_back(Message);
			IMOCriteriaList.push_back(Message);
		} else {
			AnsiString Message = "Criteria fulfilled : VCG margin according to DamageMax VCG curve."+ValueStr+" "+Myunitstr;
			IMOCriteriaList.push_back(Message);
		}
	}
	if ( !LCShipData::Stability_Only ) {
		{
			AnsiString Myunitstr;
			AnsiString ValueStr = LibGetValue(SVT_F_SFSEAPRCNT, MaxSfFrame,&Myunitstr);
			if ( MaxSfFrame && fabs(MaxSfFrame->SfSeaPrcnt) >= 100.0 ) {
				AnsiString Message = "Criteria not fulfilled : Too high share force for seagoing:"+ValueStr+" "+Myunitstr+".";
				WarningList.push_back(Message);
				IMOCriteriaList.push_back(Message);
			} else {
				AnsiString Message = "Criteria fulfilled : Share force OK for seagoing:"+ValueStr+" "+Myunitstr+".";
				IMOCriteriaList.push_back(Message);
			}
		}
		{
			AnsiString Myunitstr;
			AnsiString ValueStr = LibGetValue(SVT_F_SFHRBPRCNT, MaxSfFrame,&Myunitstr);
			if ( MaxSfFrame && fabs(MaxSfFrame->SfHrbPrcnt) >= 100.0 ) {
				AnsiString Message = "Criteria not fulfilled : Too high share force for harbour:"+ValueStr+" "+Myunitstr+".";
				WarningList.push_back(Message);
				IMOCriteriaList.push_back(Message);
			} else {
				AnsiString Message = "Criteria fulfilled : Share force OK for harbour:"+ValueStr+" "+Myunitstr+".";
				IMOCriteriaList.push_back(Message);
			}
		}
		{
			AnsiString Myunitstr;
			AnsiString ValueStr = LibGetValue(SVT_F_BMSEAPRCNT, MaxBmFrame,&Myunitstr);
			if ( MaxBmFrame && fabs(MaxBmFrame->BmSeaPrcnt) >= 100.0 ) {
				AnsiString Message = "Criteria not fulfilled : Too high bending moment for seagoing:"+ValueStr+" "+Myunitstr+".";
				WarningList.push_back(Message);
				IMOCriteriaList.push_back(Message);
			} else {
				AnsiString Message = "Criteria fulfilled : Bending moment OK for seagoing:"+ValueStr+" "+Myunitstr+".";
				IMOCriteriaList.push_back(Message);
			}
		}
		{
			AnsiString Myunitstr;
			AnsiString ValueStr = LibGetValue(SVT_F_BMHRBPRCNT, MaxBmFrame,&Myunitstr);
			if ( MaxBmFrame && fabs(MaxBmFrame->BmHrbPrcnt) >= 100.0 ) {
				AnsiString Message = "Criteria not fulfilled : Too high bending moment for harbour:"+ValueStr+" "+Myunitstr+".";
				WarningList.push_back(Message);
				IMOCriteriaList.push_back(Message);
			} else {
				AnsiString Message = "Criteria fulfilled : Bending moment OK for harbour:"+ValueStr+" "+Myunitstr+".";
				IMOCriteriaList.push_back(Message);
			}
		}
	}
}

float LCStabCalc::GetDamageMargin(int Case)
{
	return(TSNTableDamageCase::DamageCaseTable->DamageCondTable[Case]->GetValue(DraftMS,Displacement,Trim)-VCG);
}



void LCStabCalc::LoadCalc(void)
{
	if ( StabCalc ) {
		StabCalc->Calculate();
		if ( !LCShipData::Stability_Only ) {
			StabCalc->Strength();
		}
		StabCalc->CheckResult();
	}
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int LCStabCalc::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_S_DISPLACEMENT   :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = Displacement;
			break;
		case SVT_S_VCG   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = VCG;
			break;
		case SVT_S_LIST  :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = List;
			break;
		case SVT_S_TRIM  :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = Trim;
			break;
		case SVT_S_LIST_ANGLE    :
			DecPnt     = 2;
			Unit       = ANGLE_UNIT;
			MyRetValue = List_in_rad;
			break;
		case SVT_S_TRIM_ANGLE    :
			DecPnt     = 2;
			Unit       = ANGLE_UNIT;
			MyRetValue = Trim_in_rad;
			break;
		case SVT_S_LIQ_WGT  :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = LCLocationData::Liquid_Weight;
			break;
		case SVT_S_SOL_WGT  :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = LCLocationData::Solid_Weight;
			break;
		case SVT_S_DEADWEIGHT :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = LCLocationData::Solid_Weight+LCLocationData::Liquid_Weight;
			break;
		case SVT_S_DFT_MS   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DraftMS;
			break;
		case SVT_S_DFT_MS_P    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DraftMSP;
			break;
		case SVT_S_DFT_MS_S    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DraftMSS;
			break;
		case SVT_S_DFT_F    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DraftF;
			break;
		case SVT_S_DFT_A    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DraftA;
			break;
		case SVT_S_DFT_MRK  :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DraftMrk;
			break;
		case SVT_S_TFS_MOM  :
			DecPnt     = 1;
			Unit       = MOMENT_UNIT;
			MyRetValue = TFS_Moment;
			break;
		case SVT_S_TOTAL_L_MOM    :
			DecPnt     = 1;
			Unit       = MOMENT_UNIT;
			MyRetValue = Total_L_Moment;
			break;
		case SVT_S_TOTAL_T_MOM    :
			DecPnt     = 1;
			Unit       = MOMENT_UNIT;
			MyRetValue = Total_T_Moment;
			break;
		case SVT_S_TOTAL_V_MOM    :
			DecPnt     = 1;
			Unit       = MOMENT_UNIT;
			MyRetValue = Total_V_Moment;
			break;
		case SVT_S_VCG_SOL  :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = VCGSolid;
			break;
		case SVT_S_VCG_ADJ  :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = VCGCorrection;
			break;
		case SVT_S_MAX_VCG  :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			if ( TSNTableHydrostatic::MaxVCG_Tab ) {
				MyRetValue = MaxVCG;
			} else {
				Status = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_S_VCG_MARGIN  :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			if ( TSNTableHydrostatic::MaxVCG_Tab ) {
				MyRetValue = VCGMargin;
			} else {
				Status = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_S_DAM_MAX_VCG    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			if ( TSNTableHydrostatic::DamageMaxVCG_Tab ) {
				MyRetValue = DamageMaxVCG;
			} else {
				Status = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_S_DAM_VCG_MARGIN    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			if ( TSNTableHydrostatic::DamageMaxVCG_Tab ) {
				MyRetValue = DamageVCGMarg;
			} else {
				Status = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_S_IMMERSION   :
			DecPnt     = 1;
			Unit       = IMMERSION_UNIT;
			MyRetValue = Immersion;
			break;
		case SVT_S_KM    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = KM;
			break;
		case SVT_S_GM_SOL   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = GMSolid;
			break;
		case SVT_S_GM_LIQ   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = GMCorrected;
			break;
		case SVT_S_TCF   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = TCF;
			break;
		case SVT_S_LCF   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = LCF;
			break;
		case SVT_S_LCB   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = LCB;
			break;
		case SVT_S_TCG   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = TCG;
			break;
		case SVT_S_LCG   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = LCG;
			break;
		case SVT_S_GZ    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = GZ;
			if ( GZ == 0.0 ) {
				Status     = GETVAL_SHIP_UPRIGHT;
			}
			break;
		case SVT_S_GZ_30    :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = GZ30;
			break;
		case SVT_S_GZ_MAX   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = GZMax;
			break;
		case SVT_S_GZ_ANGLE    :
			DecPnt     = 2;
			Unit       = ANGLE_UNIT;
			MyRetValue = GZAngle;
			break;
		case SVT_S_GZ_A0_30    :
			DecPnt     = 3;
			Unit       = GZ_AREA_UNIT;
			MyRetValue = GZArea0_30;
			break;
		case SVT_S_GZ_A30_40   :
			DecPnt     = 3;
			Unit       = GZ_AREA_UNIT;
			MyRetValue = GZArea30_40;
			break;
		case SVT_S_GZ_A0_40    :
			DecPnt     = 3;
			Unit       = GZ_AREA_UNIT;
			MyRetValue = GZArea0_40;
			break;
		case SVT_S_FLOODING_ANGLE    :
			DecPnt     = 2;
			Unit       = ANGLE_UNIT;
			MyRetValue = FldAng;
			if ( !TSNTableHydrostatic::FloodinAngle_Tab ) {
				Status     = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_S_REM_TO_FLOODING:
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = ReserveDownflooding;
			break;
		case SVT_CARGO_WEIGHT       :
		case SVT_BALLAST_WEIGHT     :
		case SVT_HEAVY_FUEL_WEIGHT  :
		case SVT_DIESEL_OIL_WEIGHT  :
		case SVT_LUBRICANTS_WEIGHT  :
		case SVT_FRESH_WATER_WEIGHT :
		case SVT_MISC_WEIGHT        :
		case SVT_VOID_SPACE_WEIGHT  :
			{
				int TType = TANKTYPE_NONE;
				switch ( ValueId ) {
					case SVT_CARGO_WEIGHT    :
						TType = TANKTYPE_CARGO;
						break;
					case SVT_BALLAST_WEIGHT    :
						TType = TANKTYPE_BALLAST;
						break;
					case SVT_HEAVY_FUEL_WEIGHT :
						TType = TANKTYPE_HFO;
						break;
					case SVT_DIESEL_OIL_WEIGHT :
						TType = TANKTYPE_DO;
						break;
					case SVT_LUBRICANTS_WEIGHT :
						TType = TANKTYPE_LUB;
						break;
					case SVT_FRESH_WATER_WEIGHT:
						TType = TANKTYPE_FW;
						break;
					case SVT_MISC_WEIGHT       :
						TType = TANKTYPE_MISC;
						break;
					case SVT_VOID_SPACE_WEIGHT  :
						TType = TANKTYPE_VOIDSPACE;
						break;
				}
				MyRetValue = LCLocationData::WeightSum[TType];
			}
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			break;
		case SVT_SOLIDS_WEIGHT:
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = 0.0;
			for ( int TType=TANKTYPE_CSOLID; TType <=TANKTYPE_VSOLID; TType++ ) {
				MyRetValue +=LCLocationData::WeightSum[TType];
			}
			break;
		case SVT_S_MAX_BM      :
			if ( MaxBmFrame ) {
				MaxBmFrame->GetValue(SVT_F_CORR_BM,Index,MyRetValue,DecPnt,Unit);
			} else {
				Status     = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_S_MAX_SF      :
			if ( MaxSfFrame ) {
				MaxSfFrame->GetValue(SVT_F_SF,Index,MyRetValue,DecPnt,Unit);
			} else {
				Status     = GETVAL_NOT_AVAILABLE;
			}
			break;
		default:
			Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
			break;
	}
	return(Status);
}

int LCStabCalc::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_S_MAX_BM_FRAME_NAME :
			if ( MaxBmFrame ) {
				MaxBmFrame->GetStringValue(SVT_PRO_NAME,Index,MyString);
			}
			break;
		case SVT_S_MAX_SF_FRAME_NAME :
			if ( MaxSfFrame ) {
				MaxSfFrame->GetStringValue(SVT_PRO_NAME,Index,MyString);
			}
			break;
		default:
			Status = PRogramObjectBase::GetStringValue(ValueId,Index, MyString);
			break;
	}
	return(Status);
}

int LCStabCalc::GetFloatValue(int ValueId, int Index, float &MyValue) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_S_DISPLACEMENT:
        MyValue  = Displacement;
        break;
    default:
        Status = PRogramObjectBase::GetFloatValue(ValueId, Index, MyValue);
        break;
    }
    return (Status);
}

int LCStabCalc::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	return(PRogramObjectBase::PutValue( ValueId, Index, NewValue, Local,UnitId));
}

int LCStabCalc::PutFloatValue( int ValueId, float NewValue)
{
	return(PRogramObjectBase::PutFloatValue(ValueId,NewValue));
}


ValueList *LCStabCalc::GetValueInfoTable(int &Entries, int Index)
{
	return GetValueInfoTableStatic(Entries,Index);
}

ValueList *LCStabCalc::GetValueInfoTableStatic(int &Entries, int Index, bool Redundancy) {
    Entries = NELEMENTS(StabCalcValueList);
    ValueList *tmpPtr  = StabCalcValueList;
    return(tmpPtr);
}

