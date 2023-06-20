#define LC_CALC_VERSION1		1
#define LC_CALC_VERSION2		2			//29 JAN 2009 EHS

#define BMHOGHRB 			 			0
#define BMHOGSEA 			 			1
#define BMSAGHRB 			 			2
#define BMSAGSEA 			 			3
#define SFHOGHRB 			 			4
#define SFHOGSEA 			 			5
#define SFSAGHRB 			 			6
#define SFSAGSEA			 			7
#define MAX_FRAME_LIMITS 		        8


#define FRAME_AREA_ENTRIES              50

#define NOT_FOUND			            -1
#define MAX_TRIM_ENTRIES				15
#define MAX_ANGLE_ENTRIES				20

#define BUOYANCY_ENTRIES  				FRAME_AREA_ENTRIES

#define GZ_ENTRIES		 				30
#define MAX_GZ_ANGLE	 				(60.0 / RAD_FACTOR)    // 60 ^ list maximum
#define GZ_ANGLE_STEP	 				( MAX_GZ_ANGLE / GZ_ENTRIES )
#define IMO_GM_MIN 						0.15
#define IMO_GZ30_MIN 					0.20
#define IMO_GZMAX_ANGLE 				(25.0/RAD_FACTOR)
#define IMO_GZAREA0_30  				0.055
#define IMO_GZAREA30_40 				0.03
#define IMO_GZAREA0_40  				0.09

#define FLOAT_ZERO 						0.00001




