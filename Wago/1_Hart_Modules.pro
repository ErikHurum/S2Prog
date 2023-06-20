CoDeSys+╢   М                  Wago Hart 1 Hart modules @       1.0 @   2.3.9.44?  Erik Hurum Syvertsen @   ConfigExtension         CommConfigEx7             CommConfigExEnd   MEХ                  IB                    % QB                    %   ME_End   CMй      CM_End   CT┼              CT_End   ME1               ETHERNET TCP/IP + RS232 IB                    % QB                    %   ME_End   CME     CM_End   CTa             CT_End   ME╢                 IB                    % QB                    %   ME_End   CM╩     CM_End   CTц             CT_End   P¤         P_End   CT             CT_End   P/         P_End   CTJ             CT_Endq   IX                    %   CC{     CC_End   CTЧ             CT_End╛   IX                   %   CC╚     CC_End   CTф             CT_End   IX                   %   CC     CC_End   CT1             CT_EndX   IX                   %   CCb     CC_End   CT~             CT_Endе   IB                   %   CCп     CC_End   CT╦             CT_EndЄ   IW                   %   CC№     CC_End   CT             CT_End?   IW                   %   CCI     CC_End   CTe             CT_EndМ   QB                    %   CCЦ     CC_End   CT▓             CT_End┘   QB                   %   CCу     CC_End   CT              CT_End   MET                 IB                    % QB                    %   ME_End   CMh     CM_End   CTД             CT_End   ME┘                 IB                    % QB                    %   ME_End   CMэ     CM_End   CT	             CT_End   ConfigExtensionEnd?    @                                     OН'U 7   D:\Wago\Lib\ @      ════════             Ц╘ЁM        є;  @   Z   C:\PROGRAM FILES (X86)\WAGO SOFTWARE\CODESYS V2.3\TARGETS\WAGO\LIBRARIES\32_BIT\VISUAL.LIB          SET_FLASHING_SEQUENCE               EN            ¤           Activate the function    POINTER_TO_POINTER_TO_ARRAY           ¤        "    Address pointer on the sequences       SET_FLASHING_SEQUENCE                                      MН'U  А                  SET_FLASHING_SEQUENCE_INDEX               EN            ¤           Activate the function 	   IMMEDIATE            ¤        Q    FALSE: It is begun after the end of the current sequence with the new sequence.    INDEX           ¤ 	           Index of the new sequence       SET_FLASHING_SEQUENCE_INDEX                                      MН'U  А                  START_FLASHING_SEQUENCE               EN            ¤           Activate the function       START_FLASHING_SEQUENCE                                      MН'U  А                  STOP_FLASHING_SEQUENCE               EN            ¤           Activate the function       STOP_FLASHING_SEQUENCE                                      MН'U  А                  VISUAL_VERSION               EN            ¤           Activate the function       VISUAL_VERSION                                     MН'U  А              D:\WAGO\LIB\WAGOLIBHART_03.LIB.          HART_B2UNITSYMBOL           psHelp                      ¤               	   bUnitCode           ¤                  HART_b2UnitSymbol    Q       Q                              MН'U  А                  HART_B2UNITTEXT           psHelp                      ¤               	   bUnitCode           ¤                  HART_b2UnitText    Q       Q                              MН'U  А                  HART_CHECKMODULERESPONSECODE           sStatus_apx1    Q       Q     ¤               sStatus_apx2    Q       Q     ¤               
   abResponse   	  ь                       ¤                  dwError           ¤            	   dwWarning           ¤               sStatus    Q       Q    ¤                        MН'U  А                  HART_CHECKSENSORRESPONSECODE           sStatus_apx1    Q       Q     ¤               
   abResponse   	  ь                       ¤                  dwError           ¤            	   dwWarning           ¤               sStatus    Q       Q    ¤                        MН'U  А               	   HART_CMD0           wState            ¤ .           Statemashine 	   abRequest   	  ь                        ¤ 0           
   abResponse   	  ь                        ¤ 1              bCurrentIndex            ¤ 3       )    Index of HART module in g_atHARTModules    oMailBox                                           HART_MBX   ¤ 5       J    Mailbox client to transfer request/response via kbus to/from HART module 
   xMailStart             ¤ 6              dwMailError            ¤ 7              sMailStatus    Q       Q     ¤ 8              iMailRespLen            ¤ 9           	   dwWarning            ¤ ;       +    Response code and CTRL analysis variables    i            ¤ >                 bModule           ¤ "       M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤ #       q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤ )              sStatus    Q       Q    ¤ *              stData        	            
   tHART_CMD0  ¤ +                 xStart            ¤ &       г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               	   HART_CMD1           wState            ¤ !           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ #              bHartCmd            ¤ $           	   abCmdData   	  ь                        ¤ %              bCmdDataCount            ¤ &       Q    Number of bytes for additional request params - CMD1 do not need request params 	   xCmdStart             ¤ '                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤               sStatus    Q       Q    ¤               stData              
   tHART_CMD1  ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD11           wState            ¤ -           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ /              bHartCmd            ¤ 0           	   abCmdData   	  ь                        ¤ 1              bCmdDataCount            ¤ 2       /    Number of bytes for additional request params 	   xCmdStart             ¤ 3              i            ¤ 5                 bModule           ¤         M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤ !       q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    sTag    	       	    ¤ "       
    Unit tag       dwError           ¤ (              sStatus    Q       Q    ¤ )              stData        	            
   tHART_CMD0  ¤ *                 xStart            ¤ %       г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD12           wState            ¤             Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ "              bHartCmd            ¤ #           	   abCmdData   	  ь                        ¤ $              bCmdDataCount            ¤ %       /    Number of bytes for additional request params 	   xCmdStart             ¤ &                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤               sStatus    Q       Q    ¤               sMessage    !       !    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD13           wState            ¤ "           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ $              bHartCmd            ¤ %           	   abCmdData   	  ь                        ¤ &              bCmdDataCount            ¤ '       /    Number of bytes for additional request params 	   xCmdStart             ¤ (                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤               sStatus    Q       Q    ¤               stData                 tHART_CMD13  ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD14           wState            ¤ (           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ *              bHartCmd            ¤ +           	   abCmdData   	  ь                        ¤ ,              bCmdDataCount            ¤ -       /    Number of bytes for additional request params 	   xCmdStart             ¤ .                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤ #              sStatus    Q       Q    ¤ $              stData                   tHART_CMD14  ¤ %                 xStart            ¤         г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD15           wState            ¤ '           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ )              bHartCmd            ¤ *           	   abCmdData   	  ь                        ¤ +              bCmdDataCount            ¤ ,       /    Number of bytes for additional request params 	   xCmdStart             ¤ -                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤ "              sStatus    Q       Q    ¤ #              stData        	               tHART_CMD15  ¤ $                 xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD16           wState            ¤             Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ "              bHartCmd            ¤ #           	   abCmdData   	  ь                        ¤ $              bCmdDataCount            ¤ %       /    Number of bytes for additional request params 	   xCmdStart             ¤ &              pabHelp    	                               ¤ (                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤               sStatus    Q       Q    ¤               dwFinalAssemblyNumber           ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD17           wState            ¤             Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ "              bHartCmd            ¤ #           	   abCmdData   	  ь                        ¤ $              bCmdDataCount            ¤ %       /    Number of bytes for additional request params 	   xCmdStart             ¤ &              i            ¤ (                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    sMessage    !       !    ¤                  dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD18           wState            ¤ "           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ $              bHartCmd            ¤ %           	   abCmdData   	  ь                        ¤ &              bCmdDataCount            ¤ '       /    Number of bytes for additional request params 	   xCmdStart             ¤ (              i            ¤ *                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    stData                 tHART_CMD13  ¤                  dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD19           wState            ¤             Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ "              bHartCmd            ¤ #           	   abCmdData   	  ь                        ¤ $              bCmdDataCount            ¤ %       /    Number of bytes for additional request params 	   xCmdStart             ¤ &              pabHelp    	                               ¤ (              i            ¤ )                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    dwFinalAssemblyNumber           ¤                  dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               	   HART_CMD2           wState            ¤ !           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ #              bHartCmd            ¤ $           	   abCmdData   	  ь                        ¤ %              bCmdDataCount            ¤ &       /    Number of bytes for additional request params 	   xCmdStart             ¤ '                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤               sStatus    Q       Q    ¤               stData             
   tHART_CMD2  ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               	   HART_CMD3           wState            ¤ (           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ *              bHartCmd            ¤ +           	   abCmdData   	  ь                        ¤ ,              bCmdDataCount            ¤ -       Q    Number of bytes for additional request params - CMD3 do not need request params 	   xCmdStart             ¤ .                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤ #              sStatus    Q       Q    ¤ $              stData                        
   tHART_CMD3  ¤ %                 xStart            ¤         г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD33        
   oCustomCmd                                  HART_CMDCustom   ¤ 8              bHartCmd            ¤ 9           	   abCmdData   	  ь                        ¤ :              bCmdDataCount            ¤ ;       /    Number of bytes for additional request params 	   xCmdStart             ¤ =              wState            ¤ >              pabHelp    	                               ¤ ?              i            ¤ @                 bModule           ¤ $       M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤ %       q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    bVarCodeSlot0           ¤ &       "    Transmitter var. code for slot 0    bVarCodeSlot1           ¤ '       "    Transmitter var. code for slot 1    bVarCodeSlot2           ¤ (       "    Transmitter var. code for slot 2    bVarCodeSlot3           ¤ )       "    Transmitter var. code for slot 3       dwError           ¤ /              sStatus    Q       Q    ¤ 0              stDataSlot0              
   tHART_CMD1  ¤ 1              stDataSlot1              
   tHART_CMD1  ¤ 2              stDataSlot2              
   tHART_CMD1  ¤ 3              stDataSlot3              
   tHART_CMD1  ¤ 4                 xStart            ¤ ,       г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD34           wState            ¤             Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ "              bHartCmd            ¤ #           	   abCmdData   	  ь                        ¤ $              bCmdDataCount            ¤ %       /    Number of bytes for additional request params 	   xCmdStart             ¤ &              i            ¤ (                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    rPVDumpingValue            ¤                  dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD35           wState            ¤ "           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ $              bHartCmd            ¤ %           	   abCmdData   	  ь                        ¤ &              bCmdDataCount            ¤ '       /    Number of bytes for additional request params 	   xCmdStart             ¤ (              i            ¤ *                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    stData                 tHART_CMD35  ¤                  dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD38           wState            ¤            Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ !              bHartCmd            ¤ "           	   abCmdData   	  ь                        ¤ #              bCmdDataCount            ¤ $       /    Number of bytes for additional request params 	   xCmdStart             ¤ %              i            ¤ '                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD40           wState            ¤ !           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ #              bHartCmd            ¤ $           	   abCmdData   	  ь                        ¤ %              bCmdDataCount            ¤ &       /    Number of bytes for additional request params 	   xCmdStart             ¤ '              i            ¤ )                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart    rPVCurrentLevel            ¤        W    transmit the "fixed PV current level" and returns the actual "fixed PV current level"         MН'U  А               
   HART_CMD44        
   oCustomCmd                                  HART_CMDCustom   ¤ "              bHartCmd            ¤ #           	   abCmdData   	  ь                        ¤ $              bCmdDataCount            ¤ %       /    Number of bytes for additional request params 	   xCmdStart             ¤ '              wState            ¤ (              pabHelp    	                               ¤ )              i            ¤ *                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    bPrimaryVarUnitCode           ¤             Unit code for primary variable       dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD45           wState            ¤             Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ "              bHartCmd            ¤ #           	   abCmdData   	  ь                        ¤ $              bCmdDataCount            ¤ %       /    Number of bytes for additional request params 	   xCmdStart             ¤ &              i            ¤ (                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    rPVMeasuredCurrent            ¤                  dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD46           wState            ¤             Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ "              bHartCmd            ¤ #           	   abCmdData   	  ь                        ¤ $              bCmdDataCount            ¤ %       /    Number of bytes for additional request params 	   xCmdStart             ¤ &              i            ¤ (                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    rPVMeasuredCurrent            ¤                  dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD48           wState            ¤ %           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ¤ '              bHartCmd            ¤ (           	   abCmdData   	  ь                        ¤ )              bCmdDataCount            ¤ *       /    Number of bytes for additional request params 	   xCmdStart             ¤ +              i            ¤ -                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤                sStatus    Q       Q    ¤ !              stData                   tHART_CMD48  ¤ "                 xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD50        
   oCustomCmd                                  HART_CMDCustom   ¤ (              bHartCmd            ¤ )           	   abCmdData   	  ь                        ¤ *              bCmdDataCount            ¤ +       /    Number of bytes for additional request params 	   xCmdStart             ¤ -              wState            ¤ .              pabHelp    	                               ¤ /              i            ¤ 0                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ¤               sStatus    Q       Q    ¤                bVarCode_Primary           ¤ !       ,    Transmitter var. code for primary variable    bVarCode_Secondary           ¤ "       .    Transmitter var. code for secondary variable    bVarCode_Tertiary           ¤ #       -    Transmitter var. code for tertiary variable    bVarCode_4th           ¤ $       (    Transmitter var. code for 4th variable       xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD51        
   oCustomCmd                                  HART_CMDCustom   ¤ (              bHartCmd            ¤ )           	   abCmdData   	  ь                        ¤ *              bCmdDataCount            ¤ +       /    Number of bytes for additional request params 	   xCmdStart             ¤ -              wState            ¤ .              pabHelp    	                               ¤ /              i            ¤ 0                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    bVarCode_Primary           ¤        ,    Transmitter var. code for primary variable    bVarCode_Secondary           ¤        .    Transmitter var. code for secondary variable    bVarCode_Tertiary           ¤        -    Transmitter var. code for tertiary variable    bVarCode_4th           ¤        (    Transmitter var. code for 4th variable       dwError           ¤ #              sStatus    Q       Q    ¤ $                 xStart            ¤         г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               
   HART_CMD53        
   oCustomCmd                                  HART_CMDCustom   ¤ $              bHartCmd            ¤ %           	   abCmdData   	  ь                        ¤ &              bCmdDataCount            ¤ '       /    Number of bytes for additional request params 	   xCmdStart             ¤ )              wState            ¤ *              pabHelp    	                               ¤ +              i            ¤ ,                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    bTransmitterVariable           ¤             Transmitter variable to be set    bTransmitterUnitCode           ¤        $    Unit code for transmitter variable       dwError           ¤               sStatus    Q       Q    ¤                   xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А               	   HART_CMD6           wState            ¤ 0           State mashine 
   oCustomCmd                                  HART_CMDCustom   ¤ 2              bHartCmd            ¤ 3           	   abCmdData   	  ь                        ¤ 4              bCmdDataCount            ¤ 5       /    Number of bytes for additional request params 	   xCmdStart             ¤ 6       	    Helpers    i            ¤ 8                 bModule           ¤        Z    	Index of plugged HART module start with one - DPV1-Slot
						   		number start with 2    bChannel           ¤        ~    	The channel of the I/O-Module where the HART device is
						   		connected (called Index DPV1). Valid values are 1 and 2.    bPollingAddress           ¤        b   	Polling Adress (0Ц15). Using the polling address structure
								of the HART protocol, up to 15 devices can be connected in
								a multidrop network.  
								The analog current of a HART device can be fixed by setting
								its polling address to a number other than zero.								 
								With the HART protocol, each field instrument should be
								configured with different polling addresses or tag numbers
								before being connected to a multidrop networkЧotherwise,
								the master will not be able to establish communication with								 
								the slave devices.
							      dwError           ¤ ,              sStatus    Q       Q    ¤ -                 xStart            ¤ '       ╕    A raising edge will start the execution of the HART command.
						   When finished or after a timeout xStart is set to false - Check 
						   wError on the falling edge of xStart         MН'U  А                  HART_CMDCUSTOM           wState            ¤            Statemashine 	   abRequest   	  ь                        ¤             
   abResponse   	  ь                        ¤ !              bCurrentIndex            ¤ #       )    Index of HART module in g_atHARTModules    oMailBox                                           HART_MBX   ¤ %       J    Mailbox client to transfer request/response via kbus to/from HART module 
   xMailStart             ¤ &              dwMailError            ¤ '              sMailStatus    Q       Q     ¤ (              iMailRespLen            ¤ )           	   dwWarning            ¤ +       +    Response code and CTRL analysis variables    bComErrorCount            ¤ -       2    Number of failed requests on communication error    i            ¤ 0                 bModule           ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ¤        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. 	   bHART_CMD           ¤            The HARD-Command       dwError           ¤               sStatus    Q       Q    ¤                  xStart            ¤        г    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart    abData    	  ь                      ¤        ;    Additional request data and response data after execution 
   bDataCount           ¤        +    Number of additional request informations         MН'U  А                  HART_DATE2PAB           sHelp    !       !     ¤               pabHelp    	                                ¤ 	              wYear            ¤ 
              wMonth            ¤               wDay            ¤               i            ¤                  dDate           ¤               pabIn    	                              ¤                  HART_DATE2pab                                     MН'U  А                  HART_FDT           wState            ¤            Statemashine    oTON                    TON   ¤             Watchdogtimer for statemashine 	   xWatchDog             ¤        -    Enable or disable Watchdog for statemashine 	   wStateOld            ¤        (    Persist the last state of statemashine    xReset             ¤        *    Performs a auto reset if timeout elapsed    bModule            ¤        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bCurrentIndex            ¤        )    Index of HART module in g_atHARTModules    stDpv1Request             	   tHART_FDT   ¤     IW                   %           stDpv1Response             	   tHART_FDT   ¤      QW                   %        	   abRequest   	  ь                        ¤ "              bRequestLength            ¤ #           
   abResponse   	  ь                        ¤ $              bResponseLength            ¤ %              oMailBox                                           HART_MBX   ¤ '       J    Mailbox client to transfer request/response via kbus to/from HART module 
   xMailStart             ¤ (           
   xMailReset             ¤ )              dwMailError            ¤ *              sMailStatus    Q       Q     ¤ +              iMailRespLen            ¤ ,           Little helpers    i            ¤ /                 tTimeOut    ╚п     ¤ 	           Watchdog Timeout       bMsgId           ¤        -    Id of actual processed message from FDT-DTM    dwError           ¤               sStatus    Q       Q    ¤                        MН'U  А               	   HART_INFO           wState            ¤               bCount            ¤        &    Number of found HART modules 750-482    stMIA                   MODULE_INFO_ACCESS   ¤               astMI   	  ?                     MODULE_INFO           ¤               oReadPAE                 READ_INPUT_WORD   ¤        A    Functionblock from mod_com.lib to read from input process image    bStatusByte            ¤         I    Used to check status byte of HART module for shor circuit and open loop    xModComError             ¤ !       ?    Indicates the result of READ_INPUT_WORD and WRITE_OUTPUT_WORD    oCmd0                            	   HART_CMD0   ¤ $           
   xCmd0Start             ¤ %              dwCmd0Error            ¤ &              sCmd0Status    Q       Q     ¤ '           
   stCmd0Data        	            
   tHART_CMD0   ¤ (           Little helpers 
   bActModule            ¤ +       &    Used to iterate all modules/Channels    bActChannel            ¤ ,       &    Used to iterate all modules/Channels    i            ¤ -                 xStart            ¤            Set program  active       dwError           ¤               sStatus    Q       Q    ¤                  xReset            ¤                    MН'U  А                  HART_MBX           wState            ¤            Statemashine    abMbxPAE   	                          ¤            Input data of HART Mailbox    abMbxPAA   	                          ¤            Output data of HART Mailbox 	   pawMbxPAE    	                               ¤        .    Input data of HART Mailbox - readed by modcom	   pawMbxPAA    	                               ¤        0    Output data of HART Mailbox - written by modcom   oReadPAE                 READ_INPUT_WORD   ¤        A    Functionblock from mod_com.lib to read from input process image 	   oWritePAA                 WRITE_OUTPUT_WORD   ¤         C    Functionblock from mod_com.lib to write into output process image    oReadPAA                 READ_OUTPUT_WORD   ¤ !       B    Functionblock from mod_com.lib to read from output process image    xModComError             ¤ "       ?    Indicates the result of READ_INPUT_WORD and WRITE_OUTPUT_WORD    xModComWrite             ¤ #       9    Indicates that data have to be written to process image    wReadPAA            ¤ $       +    Used read back current state of togglebit    bMbxSt            ¤ &       1    MbxStatusByte (Togglebit ist MSB: 0x00 or 0x80)    bMbxRet            ¤ '       <    MbxReturnValue (Indicate succes or failure of down/up-load    dwMbxCrc            ¤ (       8    Checksum for mailbox communication as sum of all bytes    dwMbxCrcCalc            ¤ )       8    Checksum for mailbox communication as sum of all bytes    bWriteIndex            ¤ +       3    Index of actual read position in 'pabDpv1Request' 
   bReadIndex            ¤ ,       5    Index of actual write position in 'pabDpv1Response'    i            ¤ -              oWatchdogTimer                    TON   ¤ /           
   wState_old            ¤ 0                 wMbxInputOffset           ¤        9    Physical startaddress of mailbox in input process image    wMbxOutputOffset           ¤ 	       :    Physical startaddress of mailbox in output process image    pabDpv1Request    	  ь                            ¤ 
              iRequestLength           ¤            Length of request telegram    pabDpv1Response    	  ь                            ¤                  dwError           ¤               sStatus    Q       Q    ¤               iResponseLength           ¤            Length of response telegram       xStart            ¤        П    A raising edge will start the execution. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         MН'U  А                  HART_PAB2DATE           sHelp                ¤                  pabIn    	                              ¤                  HART_pab2DATE                                     MН'U  А                  HART_PAB2DWORD           pabHelp    	                               ¤               dwOut            ¤                  pabIn    	                              ¤                  HART_pab2DWORD                                     MН'U  А                  HART_PAB2DWSERIALNUMBER           pabHelp    	                               ¤               dwOut            ¤                  pabIn    	                              ¤                  HART_pab2dwSerialNumber                                     MН'U  А                  HART_PAB2REAL           pabHelp    	                               ¤               rOut             ¤                  pabIn    	                              ¤                  HART_pab2REAL                                      MН'U  А                  HART_PAB2SDESC           abHelp   	                           ¤               dwHelp            ¤ 	              psHelp                      ¤ 
              i            ¤               k            ¤            	   Index7001                            pabIn    	                              ¤        "    Raw data of packted asscii bytes       HART_pab2sDesc                                         MН'U  А                  HART_PAB2SMSG           abHelp   	                           ¤               dwHelp            ¤ 	              psHelp     !       !          ¤ 
              i            ¤               k            ¤            	   Index7001                            pabIn    	                              ¤        "    Raw data of packted asscii bytes       HART_pab2sMsg    !       !                              MН'U  А                  HART_PAB2STAG           abHelp   	                           ¤               dwHelp            ¤ 	              psHelp     	       	          ¤ 
              i            ¤               k            ¤            	   Index7001                            pabIn    	                              ¤        "    Raw data of packted asscii bytes       HART_pab2sTag    	       	                              MН'U  А                  HART_REAL2PAB           pabHelp    	                               ¤                  rValue            ¤               pabIn    	                              ¤                  HART_REAL2pab                                      MН'U  А                  HART_STRING2PAB           iLen            ¤            Length of input string    pabHelp    	                                ¤            
   dwHelpChar            ¤            1 converted byte 
   dwHelpQuad            ¤        1    4 converted char's, stored in the lower 24 bits    pabHelpQuad    	                               ¤               i            ¤               k            ¤               xLast             ¤                  sInput    !       !    ¤        $    String to convert in packted ASCII    iCount           ¤ 	       `    Number of characters(8, 16, 32) to convert (Example: 8 characters are packted into 6 databytes    pabOut    	                              ¤ 
                 HART_STRING2pab                                     MН'U  А                  HART_UNITCODESTRINGS           xAssignFlag            ¤               i            ¤               asHARTUnitCodeText   	  ▓                  (  
		(*   1 *)'Inches of Water (68 ░F)',
		(*   2 *)'Inches of Mercury (0░C)',
		(*   3 *)'Feet of Water (68 ░F)',
		(*   4 *)'Millimeters of Water (68 ░F)',
		(*   5 *)'Millimeters of Mercury (0░C)',
		(*   6 *)'Pounds per Square Inch',
		(*   7 *)'Bars',
		(*   8 *)'Millibars',
		(*   9 *)'Grams per Square Centimeter',
		(*  10 *)'Kilograms per SquareCentimeter',
		(*  11 *)'Pascals',
		(*  12 *)'Kilopascals',
		(*  13 *)'Torr',
		(*  14 *)'Atmospheres',
		(*  15 *)'Cubic Feet per Minute',
		(*  16 *)'Gallons per Minute (US)',
		(*  17 *)'Liters per Minute',
		(*  18 *)'Imperial Gallons per Minute',
		(*  19 *)'Cubic Meters per Hour',
		(*  20 *)'Feet per Second',
		(*  21 *)'Meters per Second',
		(*  22 *)'Gallons per Second (US)',
		(*  23 *)'Million Gallons per Day',
		(*  24 *)'Liters per Second',
		(*  25 *)'Million Liters per Day',
		(*  26 *)'Cubic Feet per Second',
		(*  27 *)'Cubic Feet per Day',
		(*  28 *)'Cubic Meters per Second',
		(*  29 *)'Cubic Meters per Day',
		(*  30 *)'Imperial Gallons per Hour',
		(*  31 *)'Imperial Gallons per Day',
		(*  32 *)'Degrees Celsius',
		(*  33 *)'Degrees Fahrenheit',
		(*  34 *)'Degrees Rankin',
		(*  35 *)'Kelvin',
		(*  36 *)'Millivolts',
		(*  37 *)'Ohms',
		(*  38 *)'Herts',
		(*  39 *)'Milliamperes',
		(*  40 *)'Gallons',
		(*  41 *)'Liters',
		(*  42 *)'Imperial Gallons',
		(*  43 *)'Cubic Meters',
		(*  44 *)'Feet',
		(*  45 *)'Meters',
		(*  46 *)'Barrels',
		(*  47 *)'Inches',
		(*  48 *)'Centimeters',
		(*  49 *)'Millimeters',
		(*  50 *)'Minutes',
		(*  51 *)'Seconds',
		(*  52 *)'Hours',
		(*  53 *)'Days',
		(*  54 *)'Centistokes centi',
		(*  55 *)'Centipoise',
		(*  56 *)'Microsiemens',
		(*  57 *)'Percent',
		(*  58 *)'Volts',
		(*  59 *)'pH',
		(*  60 *)'Grams',
		(*  61 *)'Kilograms',
		(*  62 *)'Metric Tons',
		(*  63 *)'Pounds',
		(*  64 *)'Short Tons',
		(*  65 *)'Long Tons',
		(*  66 *)'Milli Siemens per Centimeter',
		(*  67 *)'Micro Siemens per Centimeter',
		(*  68 *)'Newton',
		(*  69 *)'Newton Meter',
		(*  70 *)'Grams per Second',
		(*  71 *)'Grams per Minute',
		(*  72 *)'Grams per Hour',
		(*  73 *)'Kilograms per Second',
		(*  74 *)'Kilograms per Minute',
		(*  75 *)'Kilograms per Hour',
		(*  76 *)'Kilograms per Day',
		(*  77 *)'Metric Tons per Minute',
		(*  78 *)'Metric Tons per Hour',
		(*  79 *)'Metric Tons per Day',
		(*  80 *)'Pounds per Second',
		(*  81 *)'Pounds per Minute',
		(*  82 *)'Pounds per Hour',
		(*  83 *)'Pounds per Day',
		(*  84 *)'Short Topns per Minute',
		(*  85 *)'Short Tons per Hour',
		(*  86 *)'Short Tons per Day',
		(*  87 *)'Long Tons per Hour',
		(*  88 *)'Long Tons per Day',
		(*  89 *)'Deka Therm',
		(*  90 *)'Specific Gravity Units',
		(*  91 *)'Grams per Cubic Centimeter',
		(*  92 *)'Kilograms per Cubic Meter',
		(*  93 *)'Pounds per Gallon (US)',
		(*  94 *)'Pounds per Cubic Feet',
		(*  95 *)'Grams per Milliliter',
		(*  96 *)'Kilograms per Liter',
		(*  97 *)'Grams per Liter',
		(*  98 *)'Pounds per Cubic inch',
		(*  99 *)'Short Topns per Cubic Yard',
		(* 100 *)'Degrees Twaddell',
		(* 101 *)'Degree Brix',
		(* 102 *)'Degrees Baume Heavy',
		(* 103 *)'Degrees Baume Light',
		(* 104 *)'Degrees API',
		(* 105 *)'Percent Solids per Weight',
		(* 106 *)'Percent Solids per Volume',
		(* 107 *)'Degrees Balling',
		(* 108 *)'Proof per Volume',
		(* 109 *)'Proof per Mass',
		(* 110 *)'Bushels',
		(* 111 *)'Cubic Yards',
		(* 112 *)'Cubic Feet',
		(* 113 *)'Cubic Inches',
		(* 114 *)'Inches per Second',
		(* 115 *)'Inches per Minute',
		(* 116 *)'Feet per Minute',
		(* 117 *)'Degrees per Second',
		(* 118 *)'Revolutions per Second',
		(* 119 *)'Revolutions per Minute',
		(* 120 *)'Meters per Hour',
		(* 121 *)'Normal Cubic Meters per Hour',
		(* 122 *)'Normal Liters per Hour',
		(* 123 *)'Standard Cubic Feet per Minute',
		(* 124 *)'Liquid Barrel (=31.5 US gal)',
		(* 125 *)'Ounce',
		(* 126 *)'Foot Pounds Force',
		(* 127 *)'Kilo Watt',
		(* 128 *)'Kilo Watt Hour',
		(* 129 *)'Horsepower',
		(* 130 *)'Cubic Feet per Hour',
		(* 131 *)'Cubic Meters per Minute',
		(* 132 *)'Barrels per Second',
		(* 133 *)'Barrels per Minute',
		(* 134 *)'Barrels per Hour',
		(* 135 *)'Barrels per Day',
		(* 136 *)'Gallons per Hour (US)',
		(* 137 *)'Imperial Gallons per Second',
		(* 138 *)'Liters per Hour',
		(* 139 *)'Parts per Million',
		(* 140 *)'Mega Calories per Hour',
		(* 141 *)'Mega Joule per Hour',
		(* 142 *)'British Thermal Unit per Hour',
		(* 143 *)'Degrees',
		(* 144 *)'Radians',
		(* 145 *)'Inches of water at 4 ░C',
		(* 146 *)'Micrograms per liter',
		(* 147 *)'Micrograms per cubic liter',
		(* 148 *)'Percent consistency',
		(* 149 *)'Volume percent',
		(* 150 *)'Percent Steam Quality',
		(* 151 *)'Feet-Inch-1/16ths',
		(* 152 *)'Cubic Feet per Pound',
		(* 153 *)'Picofarads',
		(* 154 *)'Mililiters per liter',
		(* 155 *)'Microliters per liter',
		(* 160 *)'Percent Plato',
		(* 161 *)'Percent lower explosion level',
		(* 162 *)'Mega Calorie',
		(* 163 *)'Kohms',
		(* 164 *)'Mega Joule',
		(* 165 *)'British Thermal Unit',
		(* 166 *)'Normal Cubic Meter',
		(* 167 *)'Normal Liter "MKS System"',
		(* 168 *)'Standard Cubic Feet (US)',
		(* 169 *)'Parts per bilion',
		(* 170-219 - HART spec. expansion table *)
		(* 235 *)'Gallons per Day (US)',
		(* 236 *)'Hectoliters',
		(* 237 *)'MegaPascals',
		(* 238 *)'in H2O (4░C)',
		(* 239 *)'mm H2O (4░C)', 
		(* 240-249 - manufacturer specific defs. *)
		(* 250 *)'Not Used',
		(* 251 *)'None',
		(* 252 *)'Unknown Units',
		(* 253 *)'Special'п            Inches of Water (68 ░F)         Inches of Mercury (0░C)         Feet of Water (68 ░F)         Millimeters of Water (68 ░F)         Millimeters of Mercury (0░C)         Pounds per Square Inch         Bars      	   Millibars         Grams per Square Centimeter         Kilograms per SquareCentimeter         Pascals         Kilopascals         Torr         Atmospheres         Cubic Feet per Minute         Gallons per Minute (US)         Liters per Minute         Imperial Gallons per Minute         Cubic Meters per Hour         Feet per Second         Meters per Second         Gallons per Second (US)         Million Gallons per Day         Liters per Second         Million Liters per Day         Cubic Feet per Second         Cubic Feet per Day         Cubic Meters per Second         Cubic Meters per Day         Imperial Gallons per Hour         Imperial Gallons per Day         Degrees Celsius         Degrees Fahrenheit         Degrees Rankin         Kelvin      
   Millivolts         Ohms         Herts         Milliamperes         Gallons         Liters         Imperial Gallons         Cubic Meters         Feet         Meters         Barrels         Inches         Centimeters         Millimeters         Minutes         Seconds         Hours         Days         Centistokes centi      
   Centipoise         Microsiemens         Percent         Volts         pH         Grams      	   Kilograms         Metric Tons         Pounds      
   Short Tons      	   Long Tons         Milli Siemens per Centimeter         Micro Siemens per Centimeter         Newton         Newton Meter         Grams per Second         Grams per Minute         Grams per Hour         Kilograms per Second         Kilograms per Minute         Kilograms per Hour         Kilograms per Day         Metric Tons per Minute         Metric Tons per Hour         Metric Tons per Day         Pounds per Second         Pounds per Minute         Pounds per Hour         Pounds per Day         Short Topns per Minute         Short Tons per Hour         Short Tons per Day         Long Tons per Hour         Long Tons per Day      
   Deka Therm         Specific Gravity Units         Grams per Cubic Centimeter         Kilograms per Cubic Meter         Pounds per Gallon (US)         Pounds per Cubic Feet         Grams per Milliliter         Kilograms per Liter         Grams per Liter         Pounds per Cubic inch         Short Topns per Cubic Yard         Degrees Twaddell         Degree Brix         Degrees Baume Heavy         Degrees Baume Light         Degrees API         Percent Solids per Weight         Percent Solids per Volume         Degrees Balling         Proof per Volume         Proof per Mass         Bushels         Cubic Yards      
   Cubic Feet         Cubic Inches         Inches per Second         Inches per Minute         Feet per Minute         Degrees per Second         Revolutions per Second         Revolutions per Minute         Meters per Hour         Normal Cubic Meters per Hour         Normal Liters per Hour         Standard Cubic Feet per Minute         Liquid Barrel (=31.5 US gal)         Ounce         Foot Pounds Force      	   Kilo Watt         Kilo Watt Hour      
   Horsepower         Cubic Feet per Hour         Cubic Meters per Minute         Barrels per Second         Barrels per Minute         Barrels per Hour         Barrels per Day         Gallons per Hour (US)         Imperial Gallons per Second         Liters per Hour         Parts per Million         Mega Calories per Hour         Mega Joule per Hour         British Thermal Unit per Hour         Degrees         Radians         Inches of water at 4 ░C         Micrograms per liter         Micrograms per cubic liter         Percent consistency         Volume percent         Percent Steam Quality         Feet-Inch-1/16ths         Cubic Feet per Pound      
   Picofarads         Mililiters per liter         Microliters per liter         Percent Plato         Percent lower explosion level         Mega Calorie         Kohms      
   Mega Joule         British Thermal Unit         Normal Cubic Meter         Normal Liter "MKS System"         Standard Cubic Feet (US)         Parts per bilion         Gallons per Day (US)         Hectoliters         MegaPascals         in H2O (4░C)         mm H2O (4░C)         Not Used         None         Unknown Units         Special        ¤               asHARTUnitCodeAbbr   	  ▓                  ░  
		(*   1 *)'InH2O',
		(*   2 *)'InHg',
		(*   3 *)'FtH2O',
		(*   4 *)'mmH2O',
		(*   5 *)'mmHg',
		(*   6 *)'PSI',
		(*   7 *)'bar',
		(*   8 *)'mbar',
		(*   9 *)'g/cm2',
		(*  10 *)'kg/cm2',
		(*  11 *)'PA',
		(*  12 *)'kPA',
		(*  13 *)'torr',
		(*  14 *)'ATM',
		(*  15 *)'ft3/min',
		(*  16 *)'gal/min',
		(*  17 *)'l/min',
		(*  18 *)'ImpGal/min',
		(*  19 *)'m3/hr',
		(*  20 *)'ft/s',
		(*  21 *)'mtr/s',
		(*  22 *)'gal/sec',
		(*  23 *)'MilGal/day',
		(*  24 *)'lt/sec',
		(*  25 *)'MilL/day',
		(*  26 *)'ft3/sec',
		(*  27 *)'ft3/day',
		(*  28 *)'m3/sec',
		(*  29 *)'m3/day',
		(*  30 *)'ImpGal/hr',
		(*  31 *)'ImpGal/day',
		(*  32 *)'░C',
		(*  33 *)'░F',
		(*  34 *)'░R',
		(*  35 *)'Kelvin',
		(*  36 *)'mV',
		(*  37 *)'Ohm',
		(*  38 *)'Hz',
		(*  39 *)'mA',
		(*  40 *)'gal',
		(*  41 *)'lt',
		(*  42 *)'ImpGal',
		(*  43 *)'m3',
		(*  44 *)'ft',
		(*  45 *)'m',
		(*  46 *)'bbl',
		(*  47 *)'in',
		(*  48 *)'cm',
		(*  49 *)'mm',
		(*  50 *)'min',
		(*  51 *)'sec',
		(*  52 *)'hr',
		(*  53 *)'day',
		(*  54 *)'stokes',
		(*  55 *)'cpoise',
		(*  56 *)'uMho',
		(*  57 *)'%',
		(*  58 *)'V',
		(*  59 *)'pH',
		(*  60 *)'g',
		(*  61 *)'kg',
		(*  62 *)'MetTon',
		(*  63 *)'lb',
		(*  64 *)'ShTon',
		(*  65 *)'LTon',
		(*  66 *)'mSiemen/cm',
		(*  67 *)'uSiemen/cm',
		(*  68 *)'N',
		(*  69 *)'NM',
		(*  70 *)'g/s',
		(*  71 *)'g/min',
		(*  72 *)'g/hr',
		(*  73 *)'kg/s',
		(*  74 *)'kg/min',
		(*  75 *)'kg/hr',
		(*  76 *)'kg/day',
		(*  77 *)'MetTon/min',
		(*  78 *)'MetTon/hr',
		(*  79 *)'MetTon/day',
		(*  80 *)'lb/s',
		(*  81 *)'lb/min',
		(*  82 *)'lb/hr',
		(*  83 *)'lb/day',
		(*  84 *)'ShTon/min',
		(*  85 *)'ShTon/hr',
		(*  86 *)'ShTon/day',
		(*  87 *)'LTon/hr',
		(*  88 *)'LTon/day',
		(*  89 *)'DekaTherm',
		(*  90 *)'SGU',
		(*  91 *)'g/cm3',
		(*  92 *)'kg/m3',
		(*  93 *)'lb/gal',
		(*  94 *)'lb/ft3',
		(*  95 *)'g/ml',
		(*  96 *)'kg/l',
		(*  97 *)'g/l',
		(*  98 *)'lb/CuIn',
		(*  99 *)'ShTon/CuYd',
		(* 100 *)'░Twad',
		(* 101 *)'░Brix',
		(* 102 *)'░BaumHv',
		(* 103 *)'░BaumLt',
		(* 104 *)'░API',
		(* 105 *)'%Sol/wt',
		(* 106 *)'%Sol/vol',
		(* 107 *)'░Ball',
		(* 108 *)'proof/vol',
		(* 109 *)'proof/mass',
		(* 110 *)'bush',
		(* 111 *)'yd3',
		(* 112 *)'ft3',
		(* 113 *)'in3',
		(* 114 *)'in/s',
		(* 115 *)'in/min',
		(* 116 *)'ft/min',
		(* 117 *)'deg/s',
		(* 118 *)'rev/s',
		(* 119 *)'rpm',
		(* 120 *)'mtr/hr',
		(* 121 *)'m3/hr',
		(* 122 *)'l/hr',
		(* 123 *)'ft3/min',
		(* 124 *)'bblLiq',
		(* 125 *)'ounce',
		(* 126 *)'ftpf',
		(* 127 *)'kW',
		(* 128 *)'kWh',
		(* 129 *)'HP',
		(* 130 *)'ft3/hr',
		(* 131 *)'m3/min',
		(* 132 *)'bbl/s',
		(* 133 *)'bbl/min',
		(* 134 *)'bbl/hr',
		(* 135 *)'bbl/day',
		(* 136 *)'gal/hr',
		(* 137 *)'ImpGal/s',
		(* 138 *)'l/hr',
		(* 139 *)'ppm',
		(* 140 *)'MCal/hr',
		(* 141 *)'MJ/hr',
		(* 142 *)'BTU/hr',
		(* 143 *)'░',		
		(* 144 *)'Rads',
		(* 145 *)'in',
		(* 146 *)'ug/lt',
		(* 147 *)'ug/lt3',
		(* 148 *)'%',
		(* 149 *)'%',
		(* 150 *)'%StmQual', 
		(* 151 *)'Ftin16',   
		(* 152 *)'ft3/lb',   
		(* 153 *)'pF',       
		(* 154 *)'mlt/lt',
		(* 155 *)'ult/lt',
		(* 160 *)'%Plato',  
		(* 161 *)'%StmQual',
		(* 162 *)'MCal', 
		(* 163 *)'kOhm', 
		(* 164 *)'MJ',   
		(* 165 *)'BTU',  
		(* 166 *)'m3',   
		(* 167 *)'lt',
		(* 168 *)'ft3',
		(* 169 *)'parts/bilion',
		(* 170-219 - HART spec. expansion table *)
		(* 235 *)'Gal/day',
		(* 236 *)'hlt',
		(* 237 *)'MPa',
		(* 238 *)'in',
		(* 239 *)'mm',
		(* 240-249 - manufacturer specific defs. *)    
		(* 250 *)'',       
		(* 251 *)'-',      
		(* 252 *)'?',      
		(* 253 *)'spec'п            InH2O         InHg         FtH2O         mmH2O         mmHg         PSI         bar         mbar         g/cm2         kg/cm2         PA         kPA         torr         ATM         ft3/min         gal/min         l/min      
   ImpGal/min         m3/hr         ft/s         mtr/s         gal/sec      
   MilGal/day         lt/sec         MilL/day         ft3/sec         ft3/day         m3/sec         m3/day      	   ImpGal/hr      
   ImpGal/day         ░C         ░F         ░R         Kelvin         mV         Ohm         Hz         mA         gal         lt         ImpGal         m3         ft         m         bbl         in         cm         mm         min         sec         hr         day         stokes         cpoise         uMho         %         V         pH         g         kg         MetTon         lb         ShTon         LTon      
   mSiemen/cm      
   uSiemen/cm         N         NM         g/s         g/min         g/hr         kg/s         kg/min         kg/hr         kg/day      
   MetTon/min      	   MetTon/hr      
   MetTon/day         lb/s         lb/min         lb/hr         lb/day      	   ShTon/min         ShTon/hr      	   ShTon/day         LTon/hr         LTon/day      	   DekaTherm         SGU         g/cm3         kg/m3         lb/gal         lb/ft3         g/ml         kg/l         g/l         lb/CuIn      
   ShTon/CuYd         ░Twad         ░Brix         ░BaumHv         ░BaumLt         ░API         %Sol/wt         %Sol/vol         ░Ball      	   proof/vol      
   proof/mass         bush         yd3         ft3         in3         in/s         in/min         ft/min         deg/s         rev/s         rpm         mtr/hr         m3/hr         l/hr         ft3/min         bblLiq         ounce         ftpf         kW         kWh         HP         ft3/hr         m3/min         bbl/s         bbl/min         bbl/hr         bbl/day         gal/hr         ImpGal/s         l/hr         ppm         MCal/hr         MJ/hr         BTU/hr         ░         Rads         in         ug/lt         ug/lt3         %         %         %StmQual         Ftin16         ft3/lb         pF         mlt/lt         ult/lt         %Plato         %StmQual         MCal         kOhm         MJ         BTU         m3         lt         ft3         parts/bilion         Gal/day         hlt         MPa         in         mm                   -         ?         spec        ¤ ║           	   Index7001                                HART_UnitCodeStrings                                      MН'U  А                  HART_VERSION           bMajor           ¤               bMinor           ¤                      HART_VERSION                                     MН'U  А           [   C:\PROGRAM FILES (X86)\WAGO SOFTWARE\CODESYS V2.3\TARGETS\WAGO\LIBRARIES\32_BIT\MOD_COM.LIB          ADD_PI_INFORMATION               EN            ¤               pAccess                    MODULE_INFO_ACCESS       ¤               pInfo                  MODULE_INFO       ¤                  ADD_PI_INFORMATION                                      MН'U  А                  CRC16           CRCHI            ¤               CRCLO            ¤               INDEX            ¤               STATE            ¤                  INPUT           ¤ 	              EN            ¤ 
                 CRC           ¤                        MН'U  А                  FBUS_ERROR_INFORMATION                
   FBUS_ERROR            ¤               ERROR           ¤                        MН'U  А                  GET_DIGITAL_INPUT_OFFSET                   DIG_IN_OFFSET           ¤               ERROR           ¤                        MН'U  А                  GET_DIGITAL_OUTPUT_OFFSET                   DIG_OUT_OFFSET           ¤               ERROR           ¤                        MН'U  А                  KBUS_ERROR_INFORMATION                
   KBUS_ERROR            ¤               BITLEN           ¤            	   TERMINALS           ¤            	   RESERVED1           ¤            	   RESERVED2           ¤               FAIL_ADDRESS           ¤                        MН'U  А                  MOD_COM_VERSION               EN            ¤                  MOD_COM_VERSION                                     MН'U  А                  PI_INFORMATION                   ANALOG_OUTLENGTH           ¤               ANALOG_INLENGTH           ¤               DIGITAL_OUTLENGTH           ¤               DIGITAL_INLENGTH           ¤               OUTPUTBITS_OFFSET           ¤               INPUTBITS_OFFSET           ¤                        MН'U  А                  READ_INPUT_BIT               WORD_ADDRESS           ¤               BIT_ADDRESS           ¤                  VALUE            ¤               ERROR            ¤                        MН'U  А                  READ_INPUT_WORD               WORD_ADDRESS           ¤                  VALUE           ¤               ERROR            ¤                        MН'U  А                  READ_OUTPUT_BIT               WORD_ADDRESS           ¤               BIT_ADDRESS           ¤                  VALUE            ¤               ERROR            ¤                        MН'U  А                  READ_OUTPUT_WORD               WORD_ADDRESS           ¤                  VALUE           ¤               ERROR            ¤                        MН'U  А                  SET_DIGITAL_INPUT_OFFSET               EN            ¤               DIG_IN_OFFSET           ¤                  ENO            ¤               ERROR           ¤ 	                       MН'U  А                  SET_DIGITAL_OUTPUT_OFFSET               EN            ¤               DIG_OUT_OFFSET           ¤                  ENO            ¤               ERROR           ¤ 	                       MН'U  А                  SLAVE_ADDRESS                   SLAVE_ADDRESS           ¤                        MН'U  А                  WRITE_OUTPUT_BIT               WORD_ADDRESS           ¤               BIT_ADDRESS           ¤               VALUE            ¤                  ERROR            ¤                        MН'U  А                  WRITE_OUTPUT_WORD               WORD_ADDRESS           ¤               VALUE           ¤                  ERROR            ¤                        MН'U  А           \   C:\PROGRAM FILES (X86)\WAGO SOFTWARE\CODESYS V2.3\TARGETS\WAGO\LIBRARIES\32_BIT\STANDARD.LIB          ASCIIBYTE_TO_STRING               byt           ¤                  ASCIIBYTE_TO_STRING                                         MН'U  А                  CONCAT               STR1               ¤               STR2               ¤                  CONCAT                                         MН'U  А                  CTD           M             ¤            Variable for CD Edge Detection      CD            ¤            Count Down on rising edge    LOAD            ¤ 	           Load Start Value    PV           ¤ 
           Start Value       Q            ¤            Counter reached 0    CV           ¤            Current Counter Value             MН'U  А                  CTU           M             ¤             Variable for CU Edge Detection       CU            ¤        
    Count Up    RESET            ¤ 	           Reset Counter to 0    PV           ¤ 
           Counter Limit       Q            ¤            Counter reached the Limit    CV           ¤            Current Counter Value             MН'U  А                  CTUD           MU             ¤             Variable for CU Edge Detection    MD             ¤             Variable for CD Edge Detection       CU            ¤ 
       
    Count Up    CD            ¤            Count Down    RESET            ¤            Reset Counter to Null    LOAD            ¤            Load Start Value    PV           ¤            Start Value / Counter Limit       QU            ¤            Counter reached Limit    QD            ¤            Counter reached Null    CV           ¤            Current Counter Value             MН'U  А                  DELETE               STR               ¤               LEN           ¤ 	              POS           ¤ 
                 DELETE                                         MН'U  А                  F_TRIG           M             ¤                  CLK            ¤            Signal to detect       Q            ¤ 	           Edge detected             MН'U  А                  FIND               STR1               ¤ 	              STR2               ¤ 
                 FIND                                     MН'U  А                  INSERT               STR1               ¤ 	              STR2               ¤ 
              POS           ¤                  INSERT                                         MН'U  А                  LEFT               STR               ¤               SIZE           ¤                  LEFT                                         MН'U  А                  LEN               STR               ¤                  LEN                                     MН'U  А                  MID               STR               ¤               LEN           ¤ 	              POS           ¤ 
                 MID                                         MН'U  А                  R_TRIG           M             ¤                  CLK            ¤            Signal to detect       Q            ¤ 	           Edge detected             MН'U  А               
   REAL_STATE               RESET            ¤            Reset the variable       ERROR           ¤            Error detected             MН'U  А                  REPLACE               STR1               ¤ 	              STR2               ¤ 
              L           ¤               P           ¤                  REPLACE                                         MН'U  А                  RIGHT               STR               ¤               SIZE           ¤                  RIGHT                                         MН'U  А                  RS               SET            ¤               RESET1            ¤ 	                 Q1            ¤                        MН'U  А                  RTC           M             ¤               DiffTime            ¤                  EN            ¤               PDT           ¤                  Q            ¤               CDT           ¤                        MН'U  А                  SEMA           X             ¤                  CLAIM            ¤ 
              RELEASE            ¤                  BUSY            ¤                        MН'U  А                  SR               SET1            ¤               RESET            ¤                  Q1            ¤                        MН'U  А                  STANDARD_VERSION               EN            ¤                  STANDARD_VERSION                                     MН'U  А                  STRING_COMPARE               STR1               ¤               STR2               ¤                  STRING_COMPARE                                      MН'U  А                  STRING_TO_ASCIIBYTE               str               ¤                  STRING_TO_ASCIIBYTE                                     MН'U  А                  TOF           M             ¤            internal variable 	   StartTime            ¤            internal variable       IN            ¤        ?    starts timer with falling edge, resets timer with rising edge    PT           ¤            time to pass, before Q is set       Q            ¤        2    is FALSE, PT seconds after IN had a falling edge    ET           ¤            elapsed time             MН'U  А                  TON           M             ¤            internal variable 	   StartTime            ¤            internal variable       IN            ¤        ?    starts timer with rising edge, resets timer with falling edge    PT           ¤            time to pass, before Q is set       Q            ¤        0    is TRUE, PT seconds after IN had a rising edge    ET           ¤            elapsed time             MН'U  А                  TP        	   StartTime            ¤            internal variable       IN            ¤        !    Trigger for Start of the Signal    PT           ¤        '    The length of the High-Signal in 10ms       Q            ¤            The pulse    ET           ¤        &    The current phase of the High-Signal             MН'U  А           b   C:\PROGRAM FILES (X86)\WAGO SOFTWARE\CODESYS V2.3\TARGETS\WAGO\LIBRARIES\32_BIT\SYSLIBCALLBACK.LIB          SYSCALLBACKREGISTER            	   iPOUIndex           ¤        !    POU Index of callback function.    Event            	   RTS_EVENT  ¤            Event to register       SysCallbackRegister                                      MН'U  А                  SYSCALLBACKUNREGISTER            	   iPOUIndex           ¤        !    POU Index of callback function.    Event            	   RTS_EVENT  ¤            Event to register       SysCallbackUnregister                                      MН'U  А                         DTM        
   xInfoReset             Г               dwInfoError            Г               sInfoStatus    Q       Q     Г            FDT-DTM-Interface 	   xFdtReset             Г 	           	   bFdtMsgId            Г 
           
   dwFdtError            Г            
   sFdtStatus    Q       Q     Г               xDummy             Г                                MН'U  @                  PLC_PRG           Visu_DTM             .               _ImpVarEnEno_46_2                            _ImpVarEnEno_46_4                                             MН'U  @                  PV           Pv1   	                          ╡     QW                   %           Pv2   	                          ╡     QW@                  %           Pv3   	                          ╡     QWА                  %           ErrStat1             ╡     QX                   %           ErrStat2             ╡     QX                  %           ErrStat3             ╡     QX                  %           ErrStat4             ╡ 	    QX                  %           ErrStat5             ╡ 
    QX                  %           ErrStat6             ╡     QX                  %        	   OpenLoop1             ╡     QX   @               %        	   OpenLoop2             ╡     QX   A               %        	   OpenLoop3             ╡     QX   B               %        	   OpenLoop4             ╡     QX   C               %        	   OpenLoop5             ╡     QX   D               %        	   OpenLoop6             ╡     QX   E               %        
   ShortCirc1             ╡     QX   А               %        
   ShortCirc2             ╡     QX   Б               %        
   ShortCirc3             ╡     QX   В               %        
   ShortCirc4             ╡     QX   Г               %        
   ShortCirc5             ╡     QX   Д               %        
   ShortCirc6             ╡     QX   Е               %                            MН'U  @                  PV_1        
   xInfoReset             ┤               dwInfoError            ┤               sInfoStatus    Q       Q     ┤            Operate with module    bModule           ┤ 	       =    Physical position of HART-Module 750-482 behind the 750-841    bChannel           ┤ 
       >    The 750-482 offer two chanels, select channel 1 or channel 2    oCmd3                       	   HART_CMD3   ┤        7    FB for universal HART command 3: "read all variables" 
   stCmd3Data                        
   tHART_CMD3   ┤        3    This structure keep the response data from sensor 
   xCmd3Start             ┤        %    Execute HART_CMD3 on a raising edge    dwCmd3Error            ┤        "    0==Success, all other are errors    sCmd3Status    Q       Q     ┤        '    A textual description of "dwCmd3Error"
   oFtrigCmd3                 F_TRIG   ┤        0    Detects falling edge  cycled execution of CMD3    oTonCmd3                    TON   ┤        $    Timer for cycled execution of CMD3    IsError             ┤            True if Hart Com Error	   udiCountSuccessful            ┤               udiCountError            ┤                                MН'U  @                  PV_2        
   xInfoReset             п               dwInfoError            п               sInfoStatus    Q       Q     п            Operate with module    bModule           п 	       =    Physical position of HART-Module 750-482 behind the 750-841    bChannel           п 
       >    The 750-482 offer two chanels, select channel 1 or channel 2    oCmd3                       	   HART_CMD3   п        7    FB for universal HART command 3: "read all variables" 
   stCmd3Data                        
   tHART_CMD3   п        3    This structure keep the response data from sensor 
   xCmd3Start             п        %    Execute HART_CMD3 on a raising edge    dwCmd3Error            п        "    0==Success, all other are errors    sCmd3Status    Q       Q     п        '    A textual description of "dwCmd3Error"
   oFtrigCmd3                 F_TRIG   п        0    Detects falling edge  cycled execution of CMD3    oTonCmd3                    TON   п        $    Timer for cycled execution of CMD3    IsError             п            True if Hart Com Error	   udiCountSuccessful            п               udiCountError            п                                MН'U  @                  RUN_PRG           Run            П               aFS   	                         FLASHING_SEQUENCE   ▌    	(Colour:=GREEN, Frequency:=0, Relation:=128, NextIndex:=0),
																				(Colour:=RED, Frequency:=0, Relation:=128, NextIndex:=0),
																				(Colour:=ORANGE, Frequency:=0, Relation:=128, NextIndex:=0)                         LED_COLOURS              А                               LED_COLOURS              А                               LED_COLOURS              А            П               ptFS                    FLASHING_SEQUENCE        П               _ImpVar_143_20                           _ImpVar_143_24                           _ImpVar_143_25                            _ImpVar_143_29                            _ImpVar_143_31                                             MН'U  @                  STOP_PRG           Stop            Р               aFS   	                         FLASHING_SEQUENCE   ▌    	(Colour:=GREEN, Frequency:=0, Relation:=128, NextIndex:=0),
																				(Colour:=RED, Frequency:=0, Relation:=128, NextIndex:=0),
																				(Colour:=ORANGE, Frequency:=0, Relation:=128, NextIndex:=0)                         LED_COLOURS              А                               LED_COLOURS              А                               LED_COLOURS              А            Р               ptFS                    FLASHING_SEQUENCE        Р               _ImpVar_144_33                           _ImpVar_144_37                           _ImpVar_144_38                            _ImpVar_144_42                            _ImpVar_144_44                                             MН'U  @                   
 +  .      Г   К   ┤   ¤   п   Й             -   Ж   	   /   З   √   ╡   Р   П   ( ЦC     K   дC    K   ▓C    K   └C    K   ╒C                тC        +           █   █       ёт}U╙│╥Б┘ `ч▐S            Tcp/Ip  TCP-871-HART-Test-1 3S Tcp/Ip driver    ;   щ  Address IP address or hostname 
   192.168.227.200    ш  Port     Ч	7   d   Motorola byteorder                No    Yes у          █       ёт}U╙│╥Б┘ `ч▐S            Tcp/Ip  TCP-871-HART-Test-1 3S Tcp/Ip driver    ;   щ  Address IP address or hostname 
   192.168.227.200    ш  Port     Ч	7   d   Motorola byteorder                No    Yes   K         @   MН'U"t     ,   нТ                     CoDeSys 1-2.2   р     ════════                     ╬.  L       ы      
   Є         є         ў          °                    "          $                                                   '          (          ▒          │          ╡          ╣          ║         ╢          ╧          ╨          ╤         ╝          ╛          └          ┬          ─         ╞      А   ╩       P  ╚          ╠         ╬       А  ╥                    ~          А          С          Т          У          Ф          Х          Ц          Ч          Ш          Щ          Б          В          Г          Д          Е          Ж          З       @  И       @  К       @  Л       @  М       @  П       @  в         а         и          Ю       А  M         N          O          P          `         a          t          y          z          b         c          X          d         e         _          Q          \         R          K          U         X         Z         т          ф         ц      
   ш         ъ         ь         ю         ё         я          Ё          Є         є          Ї          ї          ў      (                                                                        "         !          #          $         Ы          ^          f         g          h          i          j          k         F          H         J         L          N         P         R          U         S          T          V          W          д          е          l          o          p          q          r          s         u          ▐          v         ж          з          |         ~         А         x          z      (   й          л         %         н          о          п         @         ▌          ф          ╪         &          Ё          	                   ц          ч          ш         щ          ъ         к          ▓          ┤          м          н          п          ░          ╖          ╕          ╛          ь          э                            I         J         K          	          L         M          Щ                             ▐          P         Q          S          )          	          	          Б           	          +	       @  ,	       @  -	          ════                                                                                                        ╤.  Є         є         ў          °                    "          $                                                   '          (          ▒          │          ╡          ╣          ║         ╢          ╧          ╨          ╤         ╝          ╛          └          ┬          ─         ╞      А   ╩       P  ╚          ╠         ╬       А  ╥          Ж       0 0И       ╨ К       0  П       H  в         и         a          t          y          z          b          c          X          d         e         _         \         R          K          U        UDPX         Z         т          ф         ц      
   ш         ъ         ь         ю         ё         я          Ё          Є         є          Ї          ї          ў      (   "          #         $          Ы          g          h          i          j          k         F          H         J         L          N         P         R          U         S          T          V          W          д          o          p          q          r          s          u          ▐          v         w          з         |         ~         А         x          z      (   й          %         н          о          п         @         ▌          р         с      X  ф          ╪         &        асЁ          	                   ц          ч          ш         щ          ъ         к          ▓          ┤          м          н          п          ░          ╖          ╕          ╛          ы          ь         э          ■                                                                      I         J         K          	          L         M          Щ                             ▐          P         Q          S          )          	          	          Б           	          +	       @  ,	       @  -	          ════                            ╬.  Є         є         ў          °                    "          $                                                   '          (          ▒          │          ╡          ╣          ║         ╢          ╧          ╨          ╤         ╝          ╛          └          ┬          ─         ╞      А   ╩       P  ╚          ╠         ╬       А  ╥          Ж       0 0И       а К       0  П       H  в         и         a          t          y          z          b          c          X          d         e         _         \         R          K          U        UDPX         Z         т          ф         ц      
   ш         ъ         ь         ю         ё         я          Ё          Є         є          Ї          ї          ў      (   "          #         $          Ы          g          h          i          j          k         F          H         J         L          N         P         R          U         S          T          V          W          д          o          p          q          r          s          u          ▐          v         w          з         |         ~         А         x          z      (   й          %         н          о          п         @         ▌          р         с      X  ф          ╪         &        асЁ          	                   ц          ч          ш         щ          ъ         к          ▓          ┤          м          н          п          ░          ╖          ╕          ╛          ы          ь         э          ■                                                  I         J         K          	          L         M          Щ                             ▐          P         Q          S          )          	          	          Б           	          +	       @  ,	       @  -	          ════                                                                                                                                                                                                    ════∙     ════════                                                   з  	   	   Name                     
   Index                            SubIndex                            Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Variable    	                 
   Value                Variable       Min                Variable       Max                Variable          5  
   	   Name                     
   Index                            SubIndex                            Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write    	   Type          ~         INT   UINT   DINT   UDINT   LINT   ULINT   SINT   USINT   BYTE   WORD   DWORD   REAL   LREAL   STRING    
   Value                Type       Default                Type       Min                Type       Max                Type          5  
   	   Name                     
   Index                            SubIndex                            Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write    	   Type          ~         INT   UINT   DINT   UDINT   LINT   ULINT   SINT   USINT   BYTE   WORD   DWORD   REAL   LREAL   STRING    
   Value                Type       Default                Type       Min                Type       Max                Type          d        Member    	                    Index-Offset                            SubIndex-Offset                            Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Min                Member       Max                Member          Я  	   	   Name                        Member    	                 
   Value                Member    
   Index                            SubIndex                            Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Min                Member       Max                Member          з  	   	   Name                     
   Index                            SubIndex                            Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Variable    	                 
   Value                Variable       Min                Variable       Max                Variable                         Є     ════════               В   _Dummy@    @   @@    @   @             дя@             дя@@   @     Аv@@   ; @+   ё     ════════                                  Аv@      4@   ░             Аv@      D@   ░                       └       @                           Аf@      4@     Аf@                Аv@     Аf@     @u@     Аf@        ў┴ы            Module.Root-1__not_found__    Hardware configuration     IB          % QB          % MB          %   o    Module.K_Bus1Module.Root    K-Bus     IB          % QB          % MB          %   o    Module.Type_49_1_Channels1Module.K_Bus   Parameter.INTTypePAAssignment10000Module.Type_49_1_ChannelsPLCPLC  INTParameter.INTTypeModule10001Module.Type_49_1_Channelspluggedplugged  INT50750-0484#12 2 AI 4-20mA HART Ex-i (12 Bytes, Mode 8)     IB          % QB          % MB          %	   M     cable break channel 1Channel.BOOLOnX_I1Module.Type_49_1_Channels         IX          %    M     short cirquit channel 1Channel.BOOLOnX_I2Module.Type_49_1_Channels         IX         %    M     cable break channel 2Channel.BOOLOnX_I3Module.Type_49_1_Channels         IX         %    M     short cirquit channel 2Channel.BOOLOnX_I4Module.Type_49_1_Channels         IX         %    M     !mailbox response, first byte of 6Channel.BYTEOnB_I5Module.Type_49_1_Channels         IB         %    M     input word 1Channel.WORDOnW_I6Module.Type_49_1_Channels         IW         %    M     input word 2Channel.WORDOnW_I7Module.Type_49_1_Channels         IW         %    M     control byteChannel.BYTEOnB_Q8Module.Type_49_1_Channels        QB          %    M      mailbox request, first byte of 6Channel.BYTEOnB_Q9Module.Type_49_1_Channels        QB         %    o     Module.FB_VARS2Module.Root    Fieldbus variables    IB          % QB          % MB          %    o     Module.FLAG_VARS3Module.Root    Flag variables    IB          % QB          % MB          %    MН'U	OН'U     ════════           VAR_GLOBAL
END_VAR
                                                                                  "   , п п :             MН'U                   start   Called when program starts   RUN_PRG_   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR    ╬.     stop   Called when program stops   STOP_PRG_   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR    ╬.     before_reset   Called before reset takes place    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.     after_reset   Called after reset took place    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.     shutdownC   Called before shutdown is performed (Firmware update over ethernet)    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.     excpt_watchdog%   Software watchdog of IEC-task expired    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.     excpt_fieldbus   Fieldbus error    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  	   ╬.     excpt_ioupdate
   KBus error    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  
   ╬.     excpt_dividebyzero*   Division by zero. Only integer operations!    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.     excpt_noncontinuable   Exception handler    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.     after_reading_inputs   Called after reading of inputs    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.     before_writing_outputs    Called before writing of outputs    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.  
   debug_loop   Debug loop at breakpoint    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     ╬.     online_change+   Is called after CodeInit() at Online-Change    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  !   ╬.     before_download$   Is called before the Download starts    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  "   ╬.     event_login/   Is called before the login service is performed    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  ї  ╬.     eth_overload   Ethernet Overload    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  ю  ╬.     eth_network_ready@   Is called directly after the Network and the PLC are initialised    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  я  ╬.  
   blink_codeN   New blink code / Blink code cleared ( Call STATUS_GET_LAST_ERROR for details )    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  Ё  ╬.     interrupt_0(   Interrupt Real Time Clock (every second)    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  ш  ╬.  $√   , Ц Ц !№               ════════           Standard Ц╘ЁM	Ц╘ЁM      ════════                         	MН'U     ════════           VAR_CONFIG
END_VAR
                                                                                   '              , 2 2 ╜Ш           Global_Variables MН'U	MН'U     ════════        8   VAR_GLOBAL
	Run_out: BOOL;
	Stop_Out: BOOL;
END_VAR
                                                                                               '           -   , d d я╩           Globale_Variablen MН'U	MН'U-     ════════        ╚   VAR_GLOBAL

	awPfcInMon AT %IW256 : ARRAY[0..255] OF WORD;
	awPfcOutMon AT %QW256 : ARRAY[0..255] OF WORD;

	wFromAristonToHart1 AT %MW0 : WORD;
	wToAristonFromHart1 AT %MW1 : WORD;

END_VAR
                                                                                               '           Ж   , } } у           Globale_Variablen_1 MН'U	MН'UЖ     ════════           VAR_GLOBAL
END_VAR
                                                                                               '           	   , Ц Ц !№           Variable_Configuration MН'U	MН'U	     ════════           VAR_CONFIG
END_VAR
                                                                                               '           /   , п п :           Variablen_Konfiguration MН'U	MН'U/     ════════           VAR_CONFIG
END_VAR
                                                                                               '           З   ,     Лf           Variablen_Konfiguration_1 MН'U	MН'UЗ     ════════           VAR_CONFIG
END_VAR
                                                                                                 ~   |0|0 @t    @R   Arial @       HH':'mm':'ss @      dd'-'MM'-'yyyy   dd'-'MM'-'yyyy HH':'mm':'ssЇ   Р                               ,              ╠3                 
    @ А          @      DEFAULT             System      ~   |0|0 @t    @R   Arial @       HH':'mm':'ss @      dd'-'MM'-'yyyy   dd'-'MM'-'yyyy HH':'mm':'ssЇ   Р                      )   HH':'mm':'ss @                             dd'-'MM'-'yyyy @       '            Г   , d d я╩           DTM MН'U	MН'U      ════════          PROGRAM DTM
VAR
	(* Identication of HART-modules and access synchronisation *)
	xInfoReset : BOOL;
	dwInfoError : DWORD;
	sInfoStatus: STRING;

	(* FDT-DTM-Interface *)
	xFdtReset : BOOL;
	bFdtMsgId : BYTE;
	dwFdtError : DWORD;
	sFdtStatus: STRING;
	xDummy: BOOL;
END_VAR     b(* This program identifies all connected HART-modules and coordinate the MailBox communication. *) TRUEA
xInfoReset	HART_INFO         dwInfoError    M(* This program work as ModbusTCP/HART-Gateway on WAGO-Ethernet-Controller *) At#40sHART_FDT           	bFdtMsgIdk                  .   ,     Ц{           PLC_PRG MН'U	MН'U      ════════        3   PROGRAM PLC_PRG
VAR
	Visu_DTM: BOOL;


END_VAR)                       Visu_DTM@                                  DTM                                                   Visu_DTM@                    	             PV                             d                  ╡   ,     Лf           PV MН'U	MН'U      ════════        !  PROGRAM PV
VAR
	Pv1 AT %QW256: ARRAY [1..8] OF REAL;
	Pv2 AT %QW320: ARRAY [1..8] OF REAL;
	Pv3 AT %QW384: ARRAY [1..8] OF REAL;
	ErrStat1 AT %QX256.0: BOOL := 0;
	ErrStat2 AT %QX256.1: BOOL := 0;
	ErrStat3 AT %QX256.2: BOOL := 0;
	ErrStat4 AT %QX256.3: BOOL := 0;
	ErrStat5 AT %QX256.4: BOOL := 0;
	ErrStat6 AT %QX256.5: BOOL := 0;

	OpenLoop1 AT %QX256.64:BOOL := 0;
	OpenLoop2 AT %QX256.65:BOOL := 0;
	OpenLoop3 AT %QX256.66:BOOL := 0;
	OpenLoop4 AT %QX256.67:BOOL := 0;
	OpenLoop5 AT %QX256.68:BOOL := 0;
	OpenLoop6 AT %QX256.69:BOOL := 0;

	ShortCirc1 AT %QX256.128:BOOL := 0;
	ShortCirc2 AT %QX256.129:BOOL := 0;
	ShortCirc3 AT %QX256.130:BOOL := 0;
	ShortCirc4 AT %QX256.131:BOOL := 0;
	ShortCirc5 AT %QX256.132:BOOL := 0;
	ShortCirc6 AT %QX256.133:BOOL := 0;

END_VARJ  PV_1;
PV_2;

Pv1[1]:=PV_1.stCmd3Data.rVarPrimary;
Pv1[2]:=PV_2.stCmd3Data.rVarPrimary;


Pv2[1]:=PV_1.stCmd3Data.rVarSecondary;
Pv2[2]:=PV_2.stCmd3Data.rVarSecondary;

Pv3[1]:=PV_1.stCmd3Data.rVarCurrent;
Pv3[2]:=PV_2.stCmd3Data.rVarCurrent;

ErrStat1 :=PV_1.IsError;
ErrStat2 :=PV_2.IsError;

OpenLoop1 := %IX0.0;
OpenLoop2 := %IX0.3;
OpenLoop3 := %IX6.0;
OpenLoop4 := %IX6.3;
OpenLoop5 := %IX12.0;
OpenLoop6 := %IX12.3;

ShortCirc1 := %IX0.1;
ShortCirc2 := %IX0.4;
ShortCirc3 := %IX6.1;
ShortCirc4 := %IX6.4;
ShortCirc5 := %IX12.1;
ShortCirc6 := %IX12.4;
               ┤   , } } у           PV_1 MН'U	MН'U      ════════        Є  PROGRAM PV_1
VAR
	(* Identication of HART-modules and access synchronisation *)
	xInfoReset : BOOL;
	dwInfoError : DWORD;
	sInfoStatus: STRING;

	(* Operate with module *)
	bModule : BYTE := 1; (* Physical position of HART-Module 750-482 behind the 750-841 *)
	bChannel: BYTE := 1; (* The 750-482 offer two chanels, select channel 1 or channel 2 *)

	(* HART CMD3 *)
	oCmd3 	   : HART_CMD3; (* FB for universal HART command 3: "read all variables" *)
	stCmd3Data : tHART_CMD3;(* This structure keep the response data from sensor *)
	xCmd3Start : BOOL;   (* Execute HART_CMD3 on a raising edge *)
	dwCmd3Error: DWORD;	 (* 0==Success, all other are errors *)
	sCmd3Status: STRING; (* A textual description of "dwCmd3Error"*)
	oFtrigCmd3 : F_TRIG; (* Detects falling edge  cycled execution of CMD3 *)
	oTonCmd3   : TON; (* Timer for cycled execution of CMD3 *)
	IsError	   : BOOL:=0; (* True if Hart Com Error	*)
	(* Statistik *)
	udiCountSuccessful : UDINT;
	udiCountError : UDINT;
END_VAR     c(* This program  identifies all connected HART-modules and coordinate the MailBox communication. *) TRUEA
xInfoReset	HART_INFO  sCmd3Status      dwInfoError    (* Read all variables *)oCmd3bModulebChannelA
xCmd3Start	HART_CMD3  sCmd3Status 
stCmd3Data      dwCmd3Error     	CMD3_BUSYЕ
oFtrigCmd3A
xCmd3StartF_TRIG           
ON_ERROR_3dwCmd3ErrorA16#0000NE  IsError     udiCountSuccessfulA1ADD  udiCountSuccessful     	CMD3_BUSYTRUE    
ON_ERROR_3udiCountErrorA1ADD  udiCountError    
CMD3_BUSY oTonCmd3Б
xCmd3StartAt#3sTON        
xCmd3Startk                  п   ,   д           PV_2 MН'U	MН'U      ════════        Є  PROGRAM PV_2
VAR
	(* Identication of HART-modules and access synchronisation *)
	xInfoReset : BOOL;
	dwInfoError : DWORD;
	sInfoStatus: STRING;

	(* Operate with module *)
	bModule : BYTE := 1; (* Physical position of HART-Module 750-482 behind the 750-841 *)
	bChannel: BYTE := 2; (* The 750-482 offer two chanels, select channel 1 or channel 2 *)

	(* HART CMD3 *)
	oCmd3 	   : HART_CMD3; (* FB for universal HART command 3: "read all variables" *)
	stCmd3Data : tHART_CMD3;(* This structure keep the response data from sensor *)
	xCmd3Start : BOOL;   (* Execute HART_CMD3 on a raising edge *)
	dwCmd3Error: DWORD;	 (* 0==Success, all other are errors *)
	sCmd3Status: STRING; (* A textual description of "dwCmd3Error"*)
	oFtrigCmd3 : F_TRIG; (* Detects falling edge  cycled execution of CMD3 *)
	oTonCmd3   : TON; (* Timer for cycled execution of CMD3 *)
	IsError	   : BOOL:=0; (* True if Hart Com Error	*)
	(* Statistik *)
	udiCountSuccessful : UDINT;
	udiCountError : UDINT;
END_VAR     c(* This program  identifies all connected HART-modules and coordinate the MailBox communication. *) TRUEA
xInfoReset	HART_INFO  sCmd3Status      dwInfoError    (* Read all variables *)oCmd3bModulebChannelA
xCmd3Start	HART_CMD3  sCmd3Status 
stCmd3Data      dwCmd3Error     	CMD3_BUSYЕ
oFtrigCmd3A
xCmd3StartF_TRIG           
ON_ERROR_3dwCmd3ErrorA16#0000NE  IsError     udiCountSuccessfulA1ADD  udiCountSuccessful     	CMD3_BUSYTRUE    
ON_ERROR_3udiCountErrorA1ADD  udiCountError    
CMD3_BUSY oTonCmd3Б
xCmd3StartAt#3sTON        
xCmd3Startk                  П   , п п ▌           RUN_PRG MН'U	MН'U      ════════        k  PROGRAM RUN_PRG
VAR
	Run: BOOL := TRUE;
	aFS					: ARRAY [0..2] OF FLASHING_SEQUENCE := 	(Colour:=GREEN, Frequency:=0, Relation:=128, NextIndex:=0),
																				(Colour:=RED, Frequency:=0, Relation:=128, NextIndex:=0),
																				(Colour:=ORANGE, Frequency:=0, Relation:=128, NextIndex:=0);
	ptFS				: POINTER TO FLASHING_SEQUENCE;
END_VAR)                       Run                           Run_out8                                Stop_Out@                   	      	      aFS                     
             ADR                                                  	      	      ptFS                                 TRUE                            ptFS                                   ADR                                                     3                SET_FLASHING_SEQUENCEи                                                                     TRUE                            FALSE(                           0                  3                SET_FLASHING_SEQUENCE_INDEX╪                                                                            TRUE                   /                START_FLASHING_SEQUENCE╕                                        d                  Р   , ╚ ╚ .Ў           STOP_PRG MН'U	MН'U      ════════        q  PROGRAM STOP_PRG
VAR
	Stop: BOOL := TRUE;
	aFS					: ARRAY [0..2] OF FLASHING_SEQUENCE := 	(Colour:=GREEN, Frequency:=0, Relation:=128, NextIndex:=0),
																				(Colour:=RED, Frequency:=0, Relation:=128, NextIndex:=0),
																				(Colour:=ORANGE, Frequency:=0, Relation:=128, NextIndex:=0);
	ptFS				: POINTER TO FLASHING_SEQUENCE;
END_VAR

)                       Stop                            Stop_out@                                Run_out8                                aFS     !                	             ADR                                         "                      ptFS  !         #                      TRUE      $       	               ptFS      %                             ADR         $                               &          
   4                SET_FLASHING_SEQUENCEи         #   %                                   '                      TRUE      (                      FALSE(     )                      2     *             4                SET_FLASHING_SEQUENCE_INDEX╪         '   (   )                                       +                      TRUE      ,             0                START_FLASHING_SEQUENCE╕         +                               d                   К   , Ц Ц !№           PLc_visu MН'U
    @════MН'U   d                                                                                                        
    @        р< ∙еlЁ                              Visu_PV                                         Ї Р        @	                                               @                                                                                                                 
    @        d P Н ╣ n     @                    DTM @╚╚╚     ▄▄▄             @        Ї Р        @	    PLC_PRG.Visu_DTM                 @       Э                                 └└└     А   АА   А   АА   А А А ААА                  Й   , Ц Ц !№           Visu_PV MН'U
    @════MН'U   j                                                                                                          
    @            ═Q ц (   ╫╫╫                                                     @                           у ╝    	   Arial @                       @                                                                                                           
    @          P ═;ц E  ╫╫╫                                                     @                           у ╝    	   Arial @                       @                                                                                                          
    @         к ╣ё ц ═     А                                                     Primary Variable @                           ы ╝    	   Arial @                       @                                                                                                           
    @         ╚ Я ф ^ ╓   ╫╫╫                                                PV_5.stCmd3Data.rVarPrimary   %s  @                           ы ╝    	   Arial @                       @                                                                                                           
    @        к ╚ ш ф ╔ ╓   ╫╫╫                                                PV_5.stCmd3Data.sUnitSymPrimary   %s  @                          ы ╝    	   Arial @                       @                                                                                                           
    @        Ё ╚ ▒ф P╓   ╫╫╫                                                PV_5.stCmd3Data.sUnitTxtPrimary   %s  @                          ы Р    	   Arial @                       @                                                                                                          
    @         Ё ╣7ц   А                                                       Secondary Variable @                           ы ╝    	   Arial @                       @                                                                                                           
    @         Я *^   ╫╫╫                                                 PLC_PRG.stCmd3Data.rVarSecondary   %s  @                          ы ╝    	   Arial @                       @                                                                                                           
    @        к ш *╔   ╫╫╫                                             $   PLC_PRG.stCmd3Data.sUnitSymSecondary   %s  @                          ы ╝    	   Arial @                       @                                                                                                           
    @        Ё ▒*P  ╫╫╫                                             $   PLC_PRG.stCmd3Data.sUnitTxtSecondary   %s  @                          ы Р    	   Arial @                       @                                                                                                          
    @         6╣}ц Y  А А                                                     Third Variable @                           ы ╝    	   Arial @                       @                                                                                                           
    @         TЯ pZ ^  ╫╫╫                                                PLC_PRG.stCmd3Data.rVarThird   %s  @                      	    ы ╝    	   Arial @                       @                                                                                                           
    @        к Tш p╔ b  ╫╫╫                                                 PLC_PRG.stCmd3Data.sUnitSymThird   %s  @                      
    ы ╝    	   Arial @                       @                                                                                                           
    @        Ё T▒pPb  ╫╫╫                                                 PLC_PRG.stCmd3Data.sUnitTxtThird   %s  @                          ы Р    	   Arial @                       @                                                                                                          
    @         |╣├ц Я  ╪╝з                                                     Fourth Variable @                           ы ╝    	   Arial @                       @                                                                                                           
    @         ЪЯ ╢^ и  ╫╫╫                                                PLC_PRG.stCmd3Data.rVarFourth   %s  @                          ы ╝    	   Arial @                       @                                                                                                           
    @        к Ъш ╢╔ и  ╫╫╫                                             !   PLC_PRG.stCmd3Data.sUnitSymFourth   %s  @                          ы ╝    	   Arial @                       @                                                                                                           
    @        Ё Ъ▒╢Pи  ╫╫╫                                             !   PLC_PRG.stCmd3Data.sUnitTxtFourth   %s  @                          ы Р    	   Arial @                       @                                                                                                          
    @        ╥ d ╣л EЗ   √ки                                                     Current @                           ы ╝    	   Arial @                       @                                                                                                           
    @        ▄ В ]Ю М                                                      PV_5.stCmd3Data.rVarCurrent   %s  @                          ы ╝    	   Arial @                       @                                                                                                           
    @        hВ жЮ ЗР                                                   "   PLC_PRG.stCmd3Data.sUnitSymPrimary   mA @                          ы ╝    	   Arial @                       @                                                                                                           
    @        
 d ┐ Г d s    ╫╫╫                                                    HART_CMD3 @                          у ╝    	   Arial @                       @                                                                                                           
    @        
 
 ╡ ) _     ╫╫╫                                                    HART_INFO @                           у ╝    	   Arial @                       @                                                                                                           
    @         2 ╣N ц @                                                      PV_5.sInfoStatus   %s  @                          ё Р    	   Arial @                       @                                                                                                           
    @         ╓╣Єц р                                                     PLC_PRG.sCmd3Status   %s  @                          ё Р    	   Arial @                       @                                                                                                           
    @        а Їп'   ╫╫╫                                                PLC_PRG.udiCountSuccessful   Successful : %i @                          Ё ╝    	   Arial @                       @                                                                                                           
    @        а п1"   ╫╫╫                                                PLC_PRG.udiCountError   Failures       : %i @                          Ё ╝    	   Arial @                       @                                     └└└     А   АА   А   АА   А А А ААА                  ¤   , K K ╓▒         !   Visual.lib 2.12.10 14:48:34 @вХўL(   WagoLibHART_03.lib 6.6.11 11:53:52 @░гьM"   mod_com.lib 2.12.10 14:48:32 @аХўL#   Standard.lib 2.12.10 14:48:34 @вХўL)   SYSLIBCALLBACK.LIB 2.12.10 14:48:32 @аХўL   O   SET_FLASHING_SEQUENCE @      FLASHING_SEQUENCE       LED_COLOURS                !   SET_FLASHING_SEQUENCE_INDEX @           START_FLASHING_SEQUENCE @           STOP_FLASHING_SEQUENCE @           VISUAL_VERSION @              Globale_Variablen @        .       HART_b2UnitSymbol @   	   tHART_2AI       tHART_2AI_MODE8    
   tHART_CMD0    
   tHART_CMD1       tHART_CMD13       tHART_CMD14       tHART_CMD15    
   tHART_CMD2    
   tHART_CMD3       tHART_CMD35       tHART_CMD48    	   tHART_FDT                  HART_b2UnitText @       "   HART_CheckModuleResponseCode @       "   HART_CheckSensorResponseCode @          HART_CMD0 @          HART_CMD1 @          HART_CMD11 @          HART_CMD12 @          HART_CMD13 @          HART_CMD14 @          HART_CMD15 @          HART_CMD16 @          HART_CMD17 @          HART_CMD18 @          HART_CMD19 @          HART_CMD2 @          HART_CMD3 @          HART_CMD33 @          HART_CMD34 @          HART_CMD35 @          HART_CMD38 @          HART_CMD40 @          HART_CMD44 @          HART_CMD45 @          HART_CMD46 @          HART_CMD48 @          HART_CMD50 @          HART_CMD51 @          HART_CMD53 @          HART_CMD6 @          HART_CMDCustom @          HART_DATE2pab @          HART_FDT @          HART_INFO @          HART_MBX @          HART_pab2DATE @          HART_pab2DWORD @          HART_pab2dwSerialNumber @          HART_pab2REAL @          HART_pab2sDesc @          HART_pab2sMsg @          HART_pab2sTag @          HART_REAL2pab @          HART_STRING2pab @          HART_UnitCodeStrings @          HART_VERSION @             Globale_Variablen @          ]   ADD_PI_INFORMATION @      ADD_DESC       MODULE_INFO       MODULE_INFO_ACCESS                   CRC16 @           FBUS_ERROR_INFORMATION @           GET_DIGITAL_INPUT_OFFSET @           GET_DIGITAL_OUTPUT_OFFSET @           KBUS_ERROR_INFORMATION @           MOD_COM_VERSION @           PI_INFORMATION @           READ_INPUT_BIT @           READ_INPUT_WORD @           READ_OUTPUT_BIT @           READ_OUTPUT_WORD @           SET_DIGITAL_INPUT_OFFSET @           SET_DIGITAL_OUTPUT_OFFSET @           SLAVE_ADDRESS @           WRITE_OUTPUT_BIT @           WRITE_OUTPUT_WORD @              Globale_Variablen @           !   ASCIIBYTE_TO_STRING @                  CONCAT @        	   CTD @        	   CTU @        
   CTUD @           DELETE @           F_TRIG @        
   FIND @           INSERT @        
   LEFT @        	   LEN @        	   MID @           R_TRIG @           REAL_STATE @          REPLACE @           RIGHT @           RS @        	   RTC @        
   SEMA @           SR @           STANDARD_VERSION @          STRING_COMPARE @          STRING_TO_ASCIIBYTE @       	   TOF @        	   TON @           TP @              Global Variables 0 @           b   SysCallbackRegister @   	   RTS_EVENT       RTS_EVENT_FILTER       RTS_EVENT_SOURCE                   SysCallbackUnregister @              Globale_Variablen @           Version @                        , п п :           2 є  є                             
             ·   ,     Лf        °   ,   д                      POUs                 DTM  Г                   PLC_PRG  .                   PV  ╡                   PV_1  ┤                   PV_2  п                  RUN_PRG  П                   STOP_PRG  Р                 
   Data types                    Visualizations                 PLc_visu  К                  Visu_PV  Й                     Global Variables                 Global_Variables                     Globale_Variablen  -                   Globale_Variablen_1  Ж                   Variable_Configuration  	                   Variablen_Konfiguration  /                   Variablen_Konfiguration_1  З                                                ════════             Ч╘ЁM╬.             ╤.      ╬.                	   localhost            P      	   localhost            P      	   localhost            P     d╬─O  √HР