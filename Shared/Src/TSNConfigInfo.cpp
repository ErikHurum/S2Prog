#include "TSNIncludes.h"
#pragma hdrstop
#include "TSNVersion.h"
TSNConfigInfo   *TSNConfigInfo::ConfigInfoPtr=NULL;
volatile bool TSNConfigInfo::HasConfigWritePermission = false;

//---------------------------------------------------------------------------
TSNConfigInfo::TSNConfigInfo(void)
{
    ConfigInfoPtr           = this;
    PrevProdNo              = 0;
    PrevPacket              = 0;
    PrevConfigNewFunc       = 0;
    PrevConfigBugFix        = 0;
    ConfigCompatibilityNo   = 0;
    PrevConfigDataRevision  = 0;
    PrevConfigRevisePerson  = "NN";
    PrevConfigRevisionText  = "Comments for previous changes of congfiguration.";
    CurrentDate             = TSNDate();
    PrevDate                = "00.00.0000";
}

TSNConfigInfo::~TSNConfigInfo(void)
{
    ConfigInfoPtr = NULL;
}
//---------------------------------------------------------------------------

void TSNConfigInfo::WriteConfigToFile(TSNConfigString &ConfigString)
{

    AnsiString LocalString;
    LocalString +=KeyWord(C_CONFIG_INFO)+CrLfStr;
    if ( HasConfigWritePermission ) {
        LocalString +=TabStr1+KeyWord(C_CONFIG_CAN_WRITE);
    }
    LocalString +=TabStr1+KeyWord(C_CONFIG_VERSION);
    LocalString +=TabStr1+(AnsiString)VERSION_PROD_NO;
    LocalString +=TabStr1+(AnsiString)VERSION_PACKET;
    LocalString +=TabStr1+(AnsiString)VERSION_CONFIG_NEW_FUNC;
    LocalString +=TabStr1+(AnsiString)VERSION_CONFIG_BUG_FIX;
    LocalString += CrLfStr;
    LocalString +=TabStr2+KeyWord(C_CONFIG_DATE) + " "+(AnsiString)CurrentDate+CrLfStr;;
    LocalString +=TabStr1+KeyWord(C_CONFIG_COMPATI_NO) + " "+(AnsiString)ConfigCompatibilityNo+CrLfStr;;
    LocalString +=TabStr1+KeyWord(C_CONFIG_DATA_REV)+(AnsiString)(PrevConfigDataRevision+1)+CrLfStr;
    LocalString +=TabStr1+KeyWord(C_CONFIG_REV_PERSON)+ConfigRevisePerson+CrLfStr;
    LocalString +=TabStr1+KeyWord(C_CONFIG_REV_TEXT)+ConfigRevisionText;
#ifdef S2TXU
    LocalString +=(AnsiString)"ENDCONFIGREVTEXT"+CrLfStr;
#endif



    LocalString +=KeyWord(C_PRO_END)+CrLfStr;
    LocalString += CrLfStr;

    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int TSNConfigInfo::LoadConfigFromFile(TSNConfigString &ConfigString)
{

    bool NoError = true;
    int ErrorLine=0;
    int Key;
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning("Configuration info",ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning("Configuration info",InputKeyWord,ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_CONFIG_CAN_WRITE:
                HasConfigWritePermission = true;
                break;
            case C_CONFIG_VERSION:
                {
                    PrevProdNo = ConfigString.ReadLong(ErrorLine);
                    PrevPacket = ConfigString.ReadLong(ErrorLine);
                    PrevConfigNewFunc = ConfigString.ReadLong(ErrorLine);
                    PrevConfigBugFix = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_CONFIG_DATE:
                {
                    PrevDate = ConfigString.GetRemainingLine(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_CONFIG_COMPATI_NO:
                {
                    ConfigCompatibilityNo = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_CONFIG_DATA_REV:
                {
                    PrevConfigDataRevision = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_CONFIG_REV_PERSON:
                {
                    PrevConfigRevisePerson  = ConfigString.GetRemainingLine(ErrorLine);
                    ConfigRevisePerson      = PrevConfigRevisePerson;
                    NoError = !ErrorLine;
                }
                break;
            case C_CONFIG_REV_TEXT:
                {
                    PrevConfigRevisionText = ConfigString.GetConfigRevisionText(ErrorLine);
                    ConfigRevisionText     = PrevConfigRevisionText;
                    NoError = !ErrorLine;
                }
                break;
            case C_HIGH_CARGO_NO:
                {
                    int HighestCargoNumber = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_HIGH_TANK_NO:
                {
                    int HighestTankNumber = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_HIGH_TEMP_NO:
                {
                    int HighestTempNumber = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_HIGH_TPRESS_NO:
                {
                    int HighestTPressNumber = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_HIGH_WINGRESS_NO:
                {
                    int HighestWIngressNumber = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
    return ErrorLine;
}
//---------------------------------------------------------------------------

