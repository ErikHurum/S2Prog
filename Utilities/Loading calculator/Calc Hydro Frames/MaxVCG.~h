//---------------------------------------------------------------------------

#ifndef MaxVCGH
#define MaxVCGH
//---------------------------------------------------------------------------
#endif



// #define NO_OF_COL		5 // Number of coloumns in the original file
/*
#define TRIM 			0
#define VCG				1  */
/*
#define CMD_LIST_SIZE 2
typedef struct
{
	char Name[80];
	int  Code;
} Cmd;
#define MAX_ENTRIES  		1000
#define MAX_NO_OF_TRIM 6
 */
typedef struct
{
	int Entries;
	float Draft[MAX_VCG_ENTRIES],
			MaxVCG[MAX_VCG_ENTRIES];
} Limit;

// int FindKey(char *Str);
// bool IsLinear(float x1, float x2, float x3, float y1, float y2, float y3, float Limit);
 #define VCG_LIMIT 			0.01

int VCGLinear(int Start, int Stop, int j);
int MinimizeMaxVCG(ofstream* Out, int Entries);


void StartMakeVcg(void);
