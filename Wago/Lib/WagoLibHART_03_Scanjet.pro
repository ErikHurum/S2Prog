CoDeSys+�   �                    @        @   2.3.9.44�   @   ConfigExtension�         CommConfigEx7             CommConfigExEnd   ME�                  IB                    % QB                    %   ME_End   CM�      CM_End   CT�   ��������   CT_End   ME                 IB                    % QB                    %   ME_End   CM.     CM_End   CTJ  ��������   CT_End   ME�                 IB                    % QB                    %   ME_End   CM�     CM_End   CT�  ��������   CT_End   ME$                 IB                    % QB                    %   ME_End   CM8     CM_End   CTT  ��������   CT_End   ME�                 IB                    % QB                    %   ME_End   CM�     CM_End   CT�  ��������   CT_End   ConfigExtensionEnd/    @                             ��ST -   .\ @      ��������             T�ST        �9  @   [   C:\Program Files (x86)\WAGO Software\CoDeSys V2.3\Targets\WAGO\Libraries\32_Bit\mod_com.lib          ADD_PI_INFORMATION               EN            ��              pAccess                    MODULE_INFO_ACCESS       ��              pInfo                  MODULE_INFO       ��                 ADD_PI_INFORMATION                                      ��ST  �   ����           CRC16           CRCHI            ��              CRCLO            ��              INDEX            ��              STATE            ��                 INPUT           ��	              EN            ��
                 CRC           ��                       ��ST  �   ����           FBUS_ERROR_INFORMATION                
   FBUS_ERROR            ��              ERROR           ��                       ��ST  �   ����           GET_DIGITAL_INPUT_OFFSET                   DIG_IN_OFFSET           ��              ERROR           ��                       ��ST  �   ����           GET_DIGITAL_OUTPUT_OFFSET                   DIG_OUT_OFFSET           ��              ERROR           ��                       ��ST  �   ����           KBUS_ERROR_INFORMATION                
   KBUS_ERROR            ��              BITLEN           ��           	   TERMINALS           ��           	   RESERVED1           ��           	   RESERVED2           ��              FAIL_ADDRESS           ��                       ��ST  �   ����           MOD_COM_VERSION               EN            ��                 MOD_COM_VERSION                                     ��ST  �   ����           PI_INFORMATION                   ANALOG_OUTLENGTH           ��              ANALOG_INLENGTH           ��              DIGITAL_OUTLENGTH           ��              DIGITAL_INLENGTH           ��              OUTPUTBITS_OFFSET           ��              INPUTBITS_OFFSET           ��                       ��ST  �   ����           READ_INPUT_BIT               WORD_ADDRESS           ��              BIT_ADDRESS           ��                 VALUE            ��              ERROR            ��                       ��ST  �   ����           READ_INPUT_WORD               WORD_ADDRESS           ��                 VALUE           ��              ERROR            ��                       ��ST  �   ����           READ_OUTPUT_BIT               WORD_ADDRESS           ��              BIT_ADDRESS           ��                 VALUE            ��              ERROR            ��                       ��ST  �   ����           READ_OUTPUT_WORD               WORD_ADDRESS           ��                 VALUE           ��              ERROR            ��                       ��ST  �   ����           SET_DIGITAL_INPUT_OFFSET               EN            ��              DIG_IN_OFFSET           ��                 ENO            ��              ERROR           ��	                       ��ST  �   ����           SET_DIGITAL_OUTPUT_OFFSET               EN            ��              DIG_OUT_OFFSET           ��                 ENO            ��              ERROR           ��	                       ��ST  �   ����           SLAVE_ADDRESS                   SLAVE_ADDRESS           ��                       ��ST  �   ����           WRITE_OUTPUT_BIT               WORD_ADDRESS           ��              BIT_ADDRESS           ��              VALUE            ��                 ERROR            ��                       ��ST  �   ����           WRITE_OUTPUT_WORD               WORD_ADDRESS           ��              VALUE           ��                 ERROR            ��                       ��ST  �   ����    \   C:\PROGRAM FILES (X86)\WAGO SOFTWARE\CODESYS V2.3\TARGETS\WAGO\LIBRARIES\32_BIT\STANDARD.LIB          ASCIIBYTE_TO_STRING               byt           ��                 ASCIIBYTE_TO_STRING                                         ��ST  �   ����           CONCAT               STR1               ��              STR2               ��                 CONCAT                                         ��ST  �   ����           CTD           M             ��           Variable for CD Edge Detection      CD            ��           Count Down on rising edge    LOAD            ��	           Load Start Value    PV           ��
           Start Value       Q            ��           Counter reached 0    CV           ��           Current Counter Value             ��ST  �   ����           CTU           M             ��            Variable for CU Edge Detection       CU            ��       
    Count Up    RESET            ��	           Reset Counter to 0    PV           ��
           Counter Limit       Q            ��           Counter reached the Limit    CV           ��           Current Counter Value             ��ST  �   ����           CTUD           MU             ��            Variable for CU Edge Detection    MD             ��            Variable for CD Edge Detection       CU            ��
       
    Count Up    CD            ��           Count Down    RESET            ��           Reset Counter to Null    LOAD            ��           Load Start Value    PV           ��           Start Value / Counter Limit       QU            ��           Counter reached Limit    QD            ��           Counter reached Null    CV           ��           Current Counter Value             ��ST  �   ����           DELETE               STR               ��              LEN           ��	              POS           ��
                 DELETE                                         ��ST  �   ����           F_TRIG           M             ��                 CLK            ��           Signal to detect       Q            ��	           Edge detected             ��ST  �   ����           FIND               STR1               ��	              STR2               ��
                 FIND                                     ��ST  �   ����           INSERT               STR1               ��	              STR2               ��
              POS           ��                 INSERT                                         ��ST  �   ����           LEFT               STR               ��              SIZE           ��                 LEFT                                         ��ST  �   ����           LEN               STR               ��                 LEN                                     ��ST  �   ����           MID               STR               ��              LEN           ��	              POS           ��
                 MID                                         ��ST  �   ����           R_TRIG           M             ��                 CLK            ��           Signal to detect       Q            ��	           Edge detected             ��ST  �   ����        
   REAL_STATE               RESET            ��           Reset the variable       ERROR           ��           Error detected             ��ST  �   ����           REPLACE               STR1               ��	              STR2               ��
              L           ��              P           ��                 REPLACE                                         ��ST  �   ����           RIGHT               STR               ��              SIZE           ��                 RIGHT                                         ��ST  �   ����           RS               SET            ��              RESET1            ��	                 Q1            ��                       ��ST  �   ����           RTC           M             ��              DiffTime            ��                 EN            ��              PDT           ��                 Q            ��              CDT           ��                       ��ST  �   ����           SEMA           X             ��                 CLAIM            ��
              RELEASE            ��                 BUSY            ��                       ��ST  �   ����           SR               SET1            ��              RESET            ��                 Q1            ��                       ��ST  �   ����           STANDARD_VERSION               EN            ��                 STANDARD_VERSION                                     ��ST  �   ����           STRING_COMPARE               STR1               ��              STR2               ��                 STRING_COMPARE                                      ��ST  �   ����           STRING_TO_ASCIIBYTE               str               ��                 STRING_TO_ASCIIBYTE                                     ��ST  �   ����           TOF           M             ��           internal variable 	   StartTime            ��           internal variable       IN            ��       ?    starts timer with falling edge, resets timer with rising edge    PT           ��           time to pass, before Q is set       Q            ��       2    is FALSE, PT seconds after IN had a falling edge    ET           ��           elapsed time             ��ST  �   ����           TON           M             ��           internal variable 	   StartTime            ��           internal variable       IN            ��       ?    starts timer with rising edge, resets timer with falling edge    PT           ��           time to pass, before Q is set       Q            ��       0    is TRUE, PT seconds after IN had a rising edge    ET           ��           elapsed time             ��ST  �   ����           TP        	   StartTime            ��           internal variable       IN            ��       !    Trigger for Start of the Signal    PT           ��       '    The length of the High-Signal in 10ms       Q            ��           The pulse    ET           ��       &    The current phase of the High-Signal             ��ST  �   ����    b   C:\PROGRAM FILES (X86)\WAGO SOFTWARE\CODESYS V2.3\TARGETS\WAGO\LIBRARIES\32_BIT\SYSLIBCALLBACK.LIB          SYSCALLBACKREGISTER            	   iPOUIndex           ��       !    POU Index of callback function.    Event            	   RTS_EVENT  ��           Event to register       SysCallbackRegister                                      ��ST  �   ����           SYSCALLBACKUNREGISTER            	   iPOUIndex           ��       !    POU Index of callback function.    Event            	   RTS_EVENT  ��           Event to register       SysCallbackUnregister                                      ��ST  �   ����        /          HART_B2UNITSYMBOL           psHelp                      V               	   bUnitCode           V                  HART_b2UnitSymbol    Q       Q                              ��ST  @   ����           HART_B2UNITTEXT           psHelp                      U               	   bUnitCode           U                  HART_b2UnitText    Q       Q                              ��ST  @   ����           HART_CHECKMODULERESPONSECODE           sStatus_apx1    Q       Q     �               sStatus_apx2    Q       Q     �               
   abResponse   	  �                       �                  dwError           �            	   dwWarning           �               sStatus    Q       Q    �                        ��ST  @   ����           HART_CHECKSENSORRESPONSECODE           sStatus_apx1    Q       Q     �               
   abResponse   	  �                       �                  dwError           �            	   dwWarning           �               sStatus    Q       Q    �                        ��ST  @   ����        	   HART_CMD0           wState            H .           Statemashine 	   abRequest   	  �                        H 0           
   abResponse   	  �                        H 1              bCurrentIndex            H 3       )    Index of HART module in g_atHARTModules    oMailBox                                           HART_MBX   H 5       J    Mailbox client to transfer request/response via kbus to/from HART module 
   xMailStart             H 6              dwMailError            H 7              sMailStatus    Q       Q     H 8              iMailRespLen            H 9           	   dwWarning            H ;       +    Response code and CTRL analysis variables    i            H >                 bModule           H "       M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           H #       q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           H )              sStatus    Q       Q    H *              stData        	            
   tHART_CMD0  H +                 xStart            H &       �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        	   HART_CMD1           wState            S !           Statemashine 
   oCustomCmd                                  HART_CMDCustom   S #              bHartCmd            S $           	   abCmdData   	  �                        S %              bCmdDataCount            S &       Q    Number of bytes for additional request params - CMD1 do not need request params 	   xCmdStart             S '                 bModule           S        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           S        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           S               sStatus    Q       Q    S               stData              
   tHART_CMD1  S                  xStart            S        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD11           wState            M -           Statemashine 
   oCustomCmd                                  HART_CMDCustom   M /              bHartCmd            M 0           	   abCmdData   	  �                        M 1              bCmdDataCount            M 2       /    Number of bytes for additional request params 	   xCmdStart             M 3              i            M 5                 bModule           M         M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           M !       q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    sTag    	       	    M "       
    Unit tag       dwError           M (              sStatus    Q       Q    M )              stData        	            
   tHART_CMD0  M *                 xStart            M %       �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD12           wState            _             Statemashine 
   oCustomCmd                                  HART_CMDCustom   _ "              bHartCmd            _ #           	   abCmdData   	  �                        _ $              bCmdDataCount            _ %       /    Number of bytes for additional request params 	   xCmdStart             _ &                 bModule           _        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           _        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           _               sStatus    Q       Q    _               sMessage    !       !    _                  xStart            _        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD13           wState            R "           Statemashine 
   oCustomCmd                                  HART_CMDCustom   R $              bHartCmd            R %           	   abCmdData   	  �                        R &              bCmdDataCount            R '       /    Number of bytes for additional request params 	   xCmdStart             R (                 bModule           R        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           R        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           R               sStatus    Q       Q    R               stData                 tHART_CMD13  R                  xStart            R        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD14           wState            D (           Statemashine 
   oCustomCmd                                  HART_CMDCustom   D *              bHartCmd            D +           	   abCmdData   	  �                        D ,              bCmdDataCount            D -       /    Number of bytes for additional request params 	   xCmdStart             D .                 bModule           D        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           D        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           D #              sStatus    Q       Q    D $              stData                   tHART_CMD14  D %                 xStart            D         �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD15           wState            X '           Statemashine 
   oCustomCmd                                  HART_CMDCustom   X )              bHartCmd            X *           	   abCmdData   	  �                        X +              bCmdDataCount            X ,       /    Number of bytes for additional request params 	   xCmdStart             X -                 bModule           X        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           X        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           X "              sStatus    Q       Q    X #              stData        	               tHART_CMD15  X $                 xStart            X        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD16           wState            N             Statemashine 
   oCustomCmd                                  HART_CMDCustom   N "              bHartCmd            N #           	   abCmdData   	  �                        N $              bCmdDataCount            N %       /    Number of bytes for additional request params 	   xCmdStart             N &              pabHelp    	                               N (                 bModule           N        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           N        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           N               sStatus    Q       Q    N               dwFinalAssemblyNumber           N                  xStart            N        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD17           wState            a             Statemashine 
   oCustomCmd                                  HART_CMDCustom   a "              bHartCmd            a #           	   abCmdData   	  �                        a $              bCmdDataCount            a %       /    Number of bytes for additional request params 	   xCmdStart             a &              i            a (                 bModule           a        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           a        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    sMessage    !       !    a                  dwError           a               sStatus    Q       Q    a                  xStart            a        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD18           wState            ] "           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ] $              bHartCmd            ] %           	   abCmdData   	  �                        ] &              bCmdDataCount            ] '       /    Number of bytes for additional request params 	   xCmdStart             ] (              i            ] *                 bModule           ]        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ]        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    stData                 tHART_CMD13  ]                  dwError           ]               sStatus    Q       Q    ]                  xStart            ]        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD19           wState            b             Statemashine 
   oCustomCmd                                  HART_CMDCustom   b "              bHartCmd            b #           	   abCmdData   	  �                        b $              bCmdDataCount            b %       /    Number of bytes for additional request params 	   xCmdStart             b &              pabHelp    	                               b (              i            b )                 bModule           b        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           b        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    dwFinalAssemblyNumber           b                  dwError           b               sStatus    Q       Q    b                  xStart            b        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        	   HART_CMD2           wState            T !           Statemashine 
   oCustomCmd                                  HART_CMDCustom   T #              bHartCmd            T $           	   abCmdData   	  �                        T %              bCmdDataCount            T &       /    Number of bytes for additional request params 	   xCmdStart             T '                 bModule           T        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           T        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           T               sStatus    Q       Q    T               stData             
   tHART_CMD2  T                  xStart            T        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        	   HART_CMD3           wState            ^ (           Statemashine 
   oCustomCmd                                  HART_CMDCustom   ^ *              bHartCmd            ^ +           	   abCmdData   	  �                        ^ ,              bCmdDataCount            ^ -       Q    Number of bytes for additional request params - CMD3 do not need request params 	   xCmdStart             ^ .                 bModule           ^        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           ^        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           ^ #              sStatus    Q       Q    ^ $              stData                        
   tHART_CMD3  ^ %                 xStart            ^         �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD33        
   oCustomCmd                                  HART_CMDCustom   o 8              bHartCmd            o 9           	   abCmdData   	  �                        o :              bCmdDataCount            o ;       /    Number of bytes for additional request params 	   xCmdStart             o =              wState            o >              pabHelp    	                               o ?              i            o @                 bModule           o $       M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           o %       q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    bVarCodeSlot0           o &       "    Transmitter var. code for slot 0    bVarCodeSlot1           o '       "    Transmitter var. code for slot 1    bVarCodeSlot2           o (       "    Transmitter var. code for slot 2    bVarCodeSlot3           o )       "    Transmitter var. code for slot 3       dwError           o /              sStatus    Q       Q    o 0              stDataSlot0              
   tHART_CMD1  o 1              stDataSlot1              
   tHART_CMD1  o 2              stDataSlot2              
   tHART_CMD1  o 3              stDataSlot3              
   tHART_CMD1  o 4                 xStart            o ,       �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD34           wState            B             Statemashine 
   oCustomCmd                                  HART_CMDCustom   B "              bHartCmd            B #           	   abCmdData   	  �                        B $              bCmdDataCount            B %       /    Number of bytes for additional request params 	   xCmdStart             B &              i            B (                 bModule           B        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           B        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    rPVDumpingValue            B                  dwError           B               sStatus    Q       Q    B                  xStart            B        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD35           wState            K "           Statemashine 
   oCustomCmd                                  HART_CMDCustom   K $              bHartCmd            K %           	   abCmdData   	  �                        K &              bCmdDataCount            K '       /    Number of bytes for additional request params 	   xCmdStart             K (              i            K *                 bModule           K        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           K        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    stData                 tHART_CMD35  K                  dwError           K               sStatus    Q       Q    K                  xStart            K        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD38           wState            f            Statemashine 
   oCustomCmd                                  HART_CMDCustom   f !              bHartCmd            f "           	   abCmdData   	  �                        f #              bCmdDataCount            f $       /    Number of bytes for additional request params 	   xCmdStart             f %              i            f '                 bModule           f        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           f        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           f               sStatus    Q       Q    f                  xStart            f        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD40           wState            g !           Statemashine 
   oCustomCmd                                  HART_CMDCustom   g #              bHartCmd            g $           	   abCmdData   	  �                        g %              bCmdDataCount            g &       /    Number of bytes for additional request params 	   xCmdStart             g '              i            g )                 bModule           g        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           g        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           g               sStatus    Q       Q    g                  xStart            g        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart    rPVCurrentLevel            g        W    transmit the "fixed PV current level" and returns the actual "fixed PV current level"         ��ST  @   ����        
   HART_CMD44        
   oCustomCmd                                  HART_CMDCustom   r "              bHartCmd            r #           	   abCmdData   	  �                        r $              bCmdDataCount            r %       /    Number of bytes for additional request params 	   xCmdStart             r '              wState            r (              pabHelp    	                               r )              i            r *                 bModule           r        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           r        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    bPrimaryVarUnitCode           r             Unit code for primary variable       dwError           r               sStatus    Q       Q    r                  xStart            r        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD45           wState            i             Statemashine 
   oCustomCmd                                  HART_CMDCustom   i "              bHartCmd            i #           	   abCmdData   	  �                        i $              bCmdDataCount            i %       /    Number of bytes for additional request params 	   xCmdStart             i &              i            i (                 bModule           i        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           i        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    rPVMeasuredCurrent            i                  dwError           i               sStatus    Q       Q    i                  xStart            i        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD46           wState            j             Statemashine 
   oCustomCmd                                  HART_CMDCustom   j "              bHartCmd            j #           	   abCmdData   	  �                        j $              bCmdDataCount            j %       /    Number of bytes for additional request params 	   xCmdStart             j &              i            j (                 bModule           j        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           j        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    rPVMeasuredCurrent            j                  dwError           j               sStatus    Q       Q    j                  xStart            j        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD48           wState            m %           Statemashine 
   oCustomCmd                                  HART_CMDCustom   m '              bHartCmd            m (           	   abCmdData   	  �                        m )              bCmdDataCount            m *       /    Number of bytes for additional request params 	   xCmdStart             m +              i            m -                 bModule           m        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           m        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           m                sStatus    Q       Q    m !              stData                   tHART_CMD48  m "                 xStart            m        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD50        
   oCustomCmd                                  HART_CMDCustom   p (              bHartCmd            p )           	   abCmdData   	  �                        p *              bCmdDataCount            p +       /    Number of bytes for additional request params 	   xCmdStart             p -              wState            p .              pabHelp    	                               p /              i            p 0                 bModule           p        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           p        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.       dwError           p               sStatus    Q       Q    p                bVarCode_Primary           p !       ,    Transmitter var. code for primary variable    bVarCode_Secondary           p "       .    Transmitter var. code for secondary variable    bVarCode_Tertiary           p #       -    Transmitter var. code for tertiary variable    bVarCode_4th           p $       (    Transmitter var. code for 4th variable       xStart            p        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD51        
   oCustomCmd                                  HART_CMDCustom   q (              bHartCmd            q )           	   abCmdData   	  �                        q *              bCmdDataCount            q +       /    Number of bytes for additional request params 	   xCmdStart             q -              wState            q .              pabHelp    	                               q /              i            q 0                 bModule           q        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           q        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    bVarCode_Primary           q        ,    Transmitter var. code for primary variable    bVarCode_Secondary           q        .    Transmitter var. code for secondary variable    bVarCode_Tertiary           q        -    Transmitter var. code for tertiary variable    bVarCode_4th           q        (    Transmitter var. code for 4th variable       dwError           q #              sStatus    Q       Q    q $                 xStart            q         �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        
   HART_CMD53        
   oCustomCmd                                  HART_CMDCustom   s $              bHartCmd            s %           	   abCmdData   	  �                        s &              bCmdDataCount            s '       /    Number of bytes for additional request params 	   xCmdStart             s )              wState            s *              pabHelp    	                               s +              i            s ,                 bModule           s        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           s        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2.    bTransmitterVariable           s             Transmitter variable to be set    bTransmitterUnitCode           s        $    Unit code for transmitter variable       dwError           s               sStatus    Q       Q    s                   xStart            s        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����        	   HART_CMD6           wState            � 0           State mashine 
   oCustomCmd                                  HART_CMDCustom   � 2              bHartCmd            � 3           	   abCmdData   	  �                        � 4              bCmdDataCount            � 5       /    Number of bytes for additional request params 	   xCmdStart             � 6       	    Helpers    i            � 8                 bModule           �        Z    	Index of plugged HART module start with one - DPV1-Slot
						   		number start with 2    bChannel           �        ~    	The channel of the I/O-Module where the HART device is
						   		connected (called Index DPV1). Valid values are 1 and 2.    bPollingAddress           �        b   	Polling Adress (0�15). Using the polling address structure
								of the HART protocol, up to 15 devices can be connected in
								a multidrop network.  
								The analog current of a HART device can be fixed by setting
								its polling address to a number other than zero.								 
								With the HART protocol, each field instrument should be
								configured with different polling addresses or tag numbers
								before being connected to a multidrop network�otherwise,
								the master will not be able to establish communication with								 
								the slave devices.
							      dwError           � ,              sStatus    Q       Q    � -                 xStart            � '       �    A raising edge will start the execution of the HART command.
						   When finished or after a timeout xStart is set to false - Check 
						   wError on the falling edge of xStart         ��ST  @   ����           HART_CMDCUSTOM           wState            Y            Statemashine 	   abRequest   	  �                        Y             
   abResponse   	  �                        Y !              bCurrentIndex            Y #       )    Index of HART module in g_atHARTModules    oMailBox                                           HART_MBX   Y %       J    Mailbox client to transfer request/response via kbus to/from HART module 
   xMailStart             Y &              dwMailError            Y '              sMailStatus    Q       Q     Y (              iMailRespLen            Y )           	   dwWarning            Y +       +    Response code and CTRL analysis variables    bComErrorCount            Y -       2    Number of failed requests on communication error    i            Y 0                 bModule           Y        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bChannel           Y        q    The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. 	   bHART_CMD           Y            The HARD-Command       dwError           Y               sStatus    Q       Q    Y                  xStart            Y        �    A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart    abData    	  �                      Y        ;    Additional request data and response data after execution 
   bDataCount           Y        +    Number of additional request informations         ��ST  @   ����           HART_DATE2PAB           sHelp    !       !     �               pabHelp    	                                � 	              wYear            � 
              wMonth            �               wDay            �               i            �                  dDate           �               pabIn    	                              �                  HART_DATE2pab                                     ��ST  @   ����           HART_FDT           wState            W            Statemashine    oTON                    TON   W             Watchdogtimer for statemashine 	   xWatchDog             W        -    Enable or disable Watchdog for statemashine 	   wStateOld            W        (    Persist the last state of statemashine    xReset             W        *    Performs a auto reset if timeout elapsed    bModule            W        M    Index of plugged HART module start with one - DPV1-Slot number start with 2    bCurrentIndex            W        )    Index of HART module in g_atHARTModules    stDpv1Request             	   tHART_FDT   W     IW                   %           stDpv1Response             	   tHART_FDT   W      QW                   %        	   abRequest   	  �                        W "              bRequestLength            W #           
   abResponse   	  �                        W $              bResponseLength            W %              oMailBox                                           HART_MBX   W '       J    Mailbox client to transfer request/response via kbus to/from HART module 
   xMailStart             W (           
   xMailReset             W )              dwMailError            W *              sMailStatus    Q       Q     W +              iMailRespLen            W ,           Little helpers    i            W /                 tTimeOut    ȯ     W 	           Watchdog Timeout       bMsgId           W        -    Id of actual processed message from FDT-DTM    dwError           W               sStatus    Q       Q    W                        ��ST  @   ����        	   HART_INFO           wState            /               bCount            /        &    Number of found HART modules 750-482    stMIA                   MODULE_INFO_ACCESS   /               astMI   	  ?                     MODULE_INFO           /               oReadPAE                 READ_INPUT_WORD   /        A    Functionblock from mod_com.lib to read from input process image    bStatusByte            /         I    Used to check status byte of HART module for shor circuit and open loop    xModComError             / !       ?    Indicates the result of READ_INPUT_WORD and WRITE_OUTPUT_WORD    oCmd0                            	   HART_CMD0   / $           
   xCmd0Start             / %              dwCmd0Error            / &              sCmd0Status    Q       Q     / '           
   stCmd0Data        	            
   tHART_CMD0   / (           Little helpers 
   bActModule            / +       &    Used to iterate all modules/Channels    bActChannel            / ,       &    Used to iterate all modules/Channels    i            / -                 xStart            /            Set program  active       dwError           /               sStatus    Q       Q    /                  xReset            /                    ��ST  @   ����           HART_MBX           wState            G            Statemashine    abMbxPAE   	                          G            Input data of HART Mailbox    abMbxPAA   	                          G            Output data of HART Mailbox 	   pawMbxPAE    	                               G        .    Input data of HART Mailbox - readed by modcom	   pawMbxPAA    	                               G        0    Output data of HART Mailbox - written by modcom   oReadPAE                 READ_INPUT_WORD   G        A    Functionblock from mod_com.lib to read from input process image 	   oWritePAA                 WRITE_OUTPUT_WORD   G         C    Functionblock from mod_com.lib to write into output process image    oReadPAA                 READ_OUTPUT_WORD   G !       B    Functionblock from mod_com.lib to read from output process image    xModComError             G "       ?    Indicates the result of READ_INPUT_WORD and WRITE_OUTPUT_WORD    xModComWrite             G #       9    Indicates that data have to be written to process image    wReadPAA            G $       +    Used read back current state of togglebit    bMbxSt            G &       1    MbxStatusByte (Togglebit ist MSB: 0x00 or 0x80)    bMbxRet            G '       <    MbxReturnValue (Indicate succes or failure of down/up-load    dwMbxCrc            G (       8    Checksum for mailbox communication as sum of all bytes    dwMbxCrcCalc            G )       8    Checksum for mailbox communication as sum of all bytes    bWriteIndex            G +       3    Index of actual read position in 'pabDpv1Request' 
   bReadIndex            G ,       5    Index of actual write position in 'pabDpv1Response'    i            G -              oWatchdogTimer                    TON   G /           
   wState_old            G 0                 wMbxInputOffset           G        9    Physical startaddress of mailbox in input process image    wMbxOutputOffset           G 	       :    Physical startaddress of mailbox in output process image    pabDpv1Request    	  �                            G 
              iRequestLength           G            Length of request telegram    pabDpv1Response    	  �                            G                  dwError           G               sStatus    Q       Q    G               iResponseLength           G            Length of response telegram       xStart            G        �    A raising edge will start the execution. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart         ��ST  @   ����           HART_PAB2DATE           sHelp                Q                  pabIn    	                              Q                  HART_pab2DATE                                     ��ST  @   ����           HART_PAB2DWORD           pabHelp    	                               E               dwOut            E                  pabIn    	                              E                  HART_pab2DWORD                                     ��ST  @   ����           HART_PAB2DWSERIALNUMBER           pabHelp    	                               �               dwOut            �                  pabIn    	                              �                  HART_pab2dwSerialNumber                                     ��ST  @   ����           HART_PAB2REAL           pabHelp    	                               J               rOut             J                  pabIn    	                              J                  HART_pab2REAL                                      ��ST  @   ����           HART_PAB2SDESC           abHelp   	                           h               dwHelp            h 	              psHelp                      h 
              i            h               k            h            	   Index7001                            pabIn    	                              h        "    Raw data of packted asscii bytes       HART_pab2sDesc                                         ��ST  @   ����           HART_PAB2SMSG           abHelp   	                           k               dwHelp            k 	              psHelp     !       !          k 
              i            k               k            k            	   Index7001                            pabIn    	                              k        "    Raw data of packted asscii bytes       HART_pab2sMsg    !       !                              ��ST  @   ����           HART_PAB2STAG           abHelp   	                           l               dwHelp            l 	              psHelp     	       	          l 
              i            l               k            l            	   Index7001                            pabIn    	                              l        "    Raw data of packted asscii bytes       HART_pab2sTag    	       	                              ��ST  @   ����           HART_REAL2PAB           pabHelp    	                               C                  rValue            C               pabIn    	                              C                  HART_REAL2pab                                      ��ST  @   ����           HART_STRING2PAB           iLen            |            Length of input string    pabHelp    	                                |            
   dwHelpChar            |            1 converted byte 
   dwHelpQuad            |        1    4 converted char's, stored in the lower 24 bits    pabHelpQuad    	                               |               i            |               k            |               xLast             |                  sInput    !       !    |        $    String to convert in packted ASCII    iCount           | 	       `    Number of characters(8, 16, 32) to convert (Example: 8 characters are packted into 6 databytes    pabOut    	                              | 
                 HART_STRING2pab                                     ��ST  @   ����           HART_UNITCODESTRINGS           xAssignFlag            �               i            �               asHARTUnitCodeText   	  �                  (  
		(*   1 *)'Inches of Water (68 �F)',
		(*   2 *)'Inches of Mercury (0�C)',
		(*   3 *)'Feet of Water (68 �F)',
		(*   4 *)'Millimeters of Water (68 �F)',
		(*   5 *)'Millimeters of Mercury (0�C)',
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
		(* 145 *)'Inches of water at 4 �C',
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
		(* 238 *)'in H2O (4�C)',
		(* 239 *)'mm H2O (4�C)', 
		(* 240-249 - manufacturer specific defs. *)
		(* 250 *)'Not Used',
		(* 251 *)'None',
		(* 252 *)'Unknown Units',
		(* 253 *)'Special'�            Inches of Water (68 �F)         Inches of Mercury (0�C)         Feet of Water (68 �F)         Millimeters of Water (68 �F)         Millimeters of Mercury (0�C)         Pounds per Square Inch         Bars      	   Millibars         Grams per Square Centimeter         Kilograms per SquareCentimeter         Pascals         Kilopascals         Torr         Atmospheres         Cubic Feet per Minute         Gallons per Minute (US)         Liters per Minute         Imperial Gallons per Minute         Cubic Meters per Hour         Feet per Second         Meters per Second         Gallons per Second (US)         Million Gallons per Day         Liters per Second         Million Liters per Day         Cubic Feet per Second         Cubic Feet per Day         Cubic Meters per Second         Cubic Meters per Day         Imperial Gallons per Hour         Imperial Gallons per Day         Degrees Celsius         Degrees Fahrenheit         Degrees Rankin         Kelvin      
   Millivolts         Ohms         Herts         Milliamperes         Gallons         Liters         Imperial Gallons         Cubic Meters         Feet         Meters         Barrels         Inches         Centimeters         Millimeters         Minutes         Seconds         Hours         Days         Centistokes centi      
   Centipoise         Microsiemens         Percent         Volts         pH         Grams      	   Kilograms         Metric Tons         Pounds      
   Short Tons      	   Long Tons         Milli Siemens per Centimeter         Micro Siemens per Centimeter         Newton         Newton Meter         Grams per Second         Grams per Minute         Grams per Hour         Kilograms per Second         Kilograms per Minute         Kilograms per Hour         Kilograms per Day         Metric Tons per Minute         Metric Tons per Hour         Metric Tons per Day         Pounds per Second         Pounds per Minute         Pounds per Hour         Pounds per Day         Short Topns per Minute         Short Tons per Hour         Short Tons per Day         Long Tons per Hour         Long Tons per Day      
   Deka Therm         Specific Gravity Units         Grams per Cubic Centimeter         Kilograms per Cubic Meter         Pounds per Gallon (US)         Pounds per Cubic Feet         Grams per Milliliter         Kilograms per Liter         Grams per Liter         Pounds per Cubic inch         Short Topns per Cubic Yard         Degrees Twaddell         Degree Brix         Degrees Baume Heavy         Degrees Baume Light         Degrees API         Percent Solids per Weight         Percent Solids per Volume         Degrees Balling         Proof per Volume         Proof per Mass         Bushels         Cubic Yards      
   Cubic Feet         Cubic Inches         Inches per Second         Inches per Minute         Feet per Minute         Degrees per Second         Revolutions per Second         Revolutions per Minute         Meters per Hour         Normal Cubic Meters per Hour         Normal Liters per Hour         Standard Cubic Feet per Minute         Liquid Barrel (=31.5 US gal)         Ounce         Foot Pounds Force      	   Kilo Watt         Kilo Watt Hour      
   Horsepower         Cubic Feet per Hour         Cubic Meters per Minute         Barrels per Second         Barrels per Minute         Barrels per Hour         Barrels per Day         Gallons per Hour (US)         Imperial Gallons per Second         Liters per Hour         Parts per Million         Mega Calories per Hour         Mega Joule per Hour         British Thermal Unit per Hour         Degrees         Radians         Inches of water at 4 �C         Micrograms per liter         Micrograms per cubic liter         Percent consistency         Volume percent         Percent Steam Quality         Feet-Inch-1/16ths         Cubic Feet per Pound      
   Picofarads         Mililiters per liter         Microliters per liter         Percent Plato         Percent lower explosion level         Mega Calorie         Kohms      
   Mega Joule         British Thermal Unit         Normal Cubic Meter         Normal Liter "MKS System"         Standard Cubic Feet (US)         Parts per bilion         Gallons per Day (US)         Hectoliters         MegaPascals         in H2O (4�C)         mm H2O (4�C)         Not Used         None         Unknown Units         Special        �               asHARTUnitCodeAbbr   	  �                  �  
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
		(*  32 *)'�C',
		(*  33 *)'�F',
		(*  34 *)'�R',
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
		(* 100 *)'�Twad',
		(* 101 *)'�Brix',
		(* 102 *)'�BaumHv',
		(* 103 *)'�BaumLt',
		(* 104 *)'�API',
		(* 105 *)'%Sol/wt',
		(* 106 *)'%Sol/vol',
		(* 107 *)'�Ball',
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
		(* 143 *)'�',		
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
		(* 253 *)'spec'�            InH2O         InHg         FtH2O         mmH2O         mmHg         PSI         bar         mbar         g/cm2         kg/cm2         PA         kPA         torr         ATM         ft3/min         gal/min         l/min      
   ImpGal/min         m3/hr         ft/s         mtr/s         gal/sec      
   MilGal/day         lt/sec         MilL/day         ft3/sec         ft3/day         m3/sec         m3/day      	   ImpGal/hr      
   ImpGal/day         �C         �F         �R         Kelvin         mV         Ohm         Hz         mA         gal         lt         ImpGal         m3         ft         m         bbl         in         cm         mm         min         sec         hr         day         stokes         cpoise         uMho         %         V         pH         g         kg         MetTon         lb         ShTon         LTon      
   mSiemen/cm      
   uSiemen/cm         N         NM         g/s         g/min         g/hr         kg/s         kg/min         kg/hr         kg/day      
   MetTon/min      	   MetTon/hr      
   MetTon/day         lb/s         lb/min         lb/hr         lb/day      	   ShTon/min         ShTon/hr      	   ShTon/day         LTon/hr         LTon/day      	   DekaTherm         SGU         g/cm3         kg/m3         lb/gal         lb/ft3         g/ml         kg/l         g/l         lb/CuIn      
   ShTon/CuYd         �Twad         �Brix         �BaumHv         �BaumLt         �API         %Sol/wt         %Sol/vol         �Ball      	   proof/vol      
   proof/mass         bush         yd3         ft3         in3         in/s         in/min         ft/min         deg/s         rev/s         rpm         mtr/hr         m3/hr         l/hr         ft3/min         bblLiq         ounce         ftpf         kW         kWh         HP         ft3/hr         m3/min         bbl/s         bbl/min         bbl/hr         bbl/day         gal/hr         ImpGal/s         l/hr         ppm         MCal/hr         MJ/hr         BTU/hr         �         Rads         in         ug/lt         ug/lt3         %         %         %StmQual         Ftin16         ft3/lb         pF         mlt/lt         ult/lt         %Plato         %StmQual         MCal         kOhm         MJ         BTU         m3         lt         ft3         parts/bilion         Gal/day         hlt         MPa         in         mm                   -         ?         spec        � �           	   Index7001                                HART_UnitCodeStrings                                      ��ST  @   ����           HART_VERSION           bMajor           `               bMinor           `                      HART_VERSION                                     ��ST  @   ����           PLC_PRG     ~      wCurrentAI1            �     IW                   %        raw 4..20mA Signal    rCurrentAI1             �               dwCountSuccessful            �               dwCountError            � 	           Operate with module    bModule           �               bChannel           �        9    Identication of HART-modules and access synchronisation 
   xInfoReset             �               dwInfoError            �               sInfoStatus    Q       Q     �            FDT-DTM-Interface 	   xFdtReset             �            	   bFdtMsgId            �            
   dwFdtError            �            
   sFdtStatus    Q       Q     �            HART lib version    wHartLibVersion            �            HART CMD0    oCmd0                            	   HART_CMD0   �             
   stCmd0Data        	            
   tHART_CMD0   � !           
   xCmd0Start             � "              dwCmd0Error            � #              sCmd0Status    Q       Q     � $           HART CMD1    oCmd1                       	   HART_CMD1   � '           
   stCmd1Data              
   tHART_CMD1   � (           
   xCmd1Start             � )              dwCmd1Error            � *              sCmd1Status    Q       Q     � +           HART CMD2    oCmd2                       	   HART_CMD2   � .           
   stCmd2Data             
   tHART_CMD2   � /           
   xCmd2Start             � 0              dwCmd2Error            � 1              sCmd2Status    Q       Q     � 2           HART CMD3    oCmd3                       	   HART_CMD3   � 5           
   stCmd3Data                        
   tHART_CMD3   � 6           
   xCmd3Start             � 7              dwCmd3Error            � 8              sCmd3Status    Q       Q     � 9           
   oFtrigCmd3                 F_TRIG   � :       0    Detects falling edge  cycled execution of CMD3    oTonCmd3                    TON   � ;       $    Timer for cycled execution of CMD3    oCmd6                        	   HART_CMD6   � >              bCmd6PollingAdr    
       � ?           
   xCmd6Start             � @              sCmd6Status    Q       Q     � A              dwCmd6Error            � B           HART CMD11    oCmd11                         
   HART_CMD11   � E              stCmd11Data        	            
   tHART_CMD0   � F           	   sCmd11Tag    	      TI XXX  	     � G              xCmd11Start            � H              sCmd11Status    Q       Q     � I              dwCmd11Error            � J           HART CMD12    oCmd12                       
   HART_CMD12   � M              xCmd12Start            � N              dwCmd12Error            � O              sCmd12Status    Q       Q     � P           	   sCmd12Msg    Q       Q     � Q           HART CMD13    oCmd13                       
   HART_CMD13   � T              stCmd13Data                 tHART_CMD13   � U              xCmd13Start            � V              dwCmd13Error            � W              sCmd13Status    Q       Q     � X           HART CMD14    oCmd14                       
   HART_CMD14   � [              stCmd14Data                   tHART_CMD14   � \              xCmd14Start            � ]              sCmd14Status    Q       Q     � ^              dwCmd14Error            � _           HART CMD15    oCmd15                       
   HART_CMD15   � b              stCmd15Data        	               tHART_CMD15   � c              xCmd15Start            � d              dwCmd15Error            � e              sCmd15Status    Q       Q     � f           HART CMD16    oCmd16                        
   HART_CMD16   � i           
   dwCmd16FAN            � j              xCmd16Start            � k              dwCmd16Error            � l              sCmd16Status    Q       Q     � m           HART CMD17    oCmd17                        
   HART_CMD17   � p           
   dwCmd17Msg    !      This is Wago PLC message!     � q              xCmd17Start            � r              dwCmd17Error            � s              sCmd17Status    Q       Q     � t           HART CMD18    oCmd18                        
   HART_CMD18   � w              dwCmd18Data       e    (sTag := 'TI XXX 1',
								  sDescriptor := 'description IJK ',
								  dDate := d#2008-07-30)    	      TI XXX 1       description IJK   ��H   tHART_CMD13   � x              xCmd18Start            � {              dwCmd18Error            � |              sCmd18Status    Q       Q     � }              oFtrigCmd18                 F_TRIG   � ~           	   oTonCmd18                    TON   �            HART CMD19    oCmd19                         
   HART_CMD19   � �           
   dwCmd19FAN           � �              xCmd19Start            � �              dwCmd19Error            � �              sCmd19Status    Q       Q     � �           HART CMD33    oCmd33                                
   HART_CMD33   � �              xCmd33Start             � �              dwCmd33Error            � �              sCmd33Status    Q       Q     � �              stCmd33DataSlot0              
   tHART_CMD1   � �              stCmd33DataSlot1              
   tHART_CMD1   � �              stCmd33DataSlot2              
   tHART_CMD1   � �              stCmd33DataSlot3              
   tHART_CMD1   � �           HART CMD44    oCmd44                         
   HART_CMD44   � �              xCmd44Start             � �              dwCmd44Error            � �              sCmd44Status    Q       Q     � �           HART CMD48    oCmd48                        
   HART_CMD48   � �              stCmd48Data                   tHART_CMD48   � �              xCmd48Start             � �              dwCmd48Error            � �              sCmd48Status    Q       Q     � �           HART CMD50    oCmd50                            
   HART_CMD50   � �              xCmd50Start             � �              dwCmd50Error            � �              sCmd50Status    Q       Q     � �              bCmd50VarCodePrimary            � �              bCmd50VarCodeSecondary            � �              bCmd50VarCodeTertiary            � �              bCmd50VarCode4th            � �           HART CMD51    oCmd51                            
   HART_CMD51   � �              xCmd51Start             � �              dwCmd51Error            � �              sCmd51Status    Q       Q     � �              bCmd51VarCodePrimary            � �              bCmd51VarCodeSecondary            � �              bCmd51VarCodeTertiary            � �              bCmd51VarCode4th            � �           HART CMD53    oCmd53                          
   HART_CMD53   � �              xCmd53Start             � �              dwCmd53Error            � �              sCmd53Status    Q       Q     � �                               ��ST  @   ����            
 �    ����/   ( �=     K   �=    K   �=    K   �=    K   �=                >        +           �   �       ��}Uӳ��� `��S            Tcp/Ip  TCP-871-HART-Test-1 3S Tcp/Ip driver    ;   �  Address IP address or hostname 
   192.168.227.201    �  Port     �	7   d   Motorola byteorder                No    Yes �          �       ��}Uӳ��� `��S            Tcp/Ip  TCP-871-HART-Test-1 3S Tcp/Ip driver    ;   �  Address IP address or hostname 
   192.168.227.201    �  Port     �	7   d   Motorola byteorder                No    Yes   K         @   ��ST�d       ��������                     CoDeSys 1-2.2   ����  ��������                     �.  L       �      
   �         �         �          �                    "          $                                                   '          (          �          �          �          �          �         �          �          �          �         �          �          �          �          �         �      �   �       P  �          �         �       �  �                    ~          �          �          �          �          �          �          �          �          �          �          �          �          �          �          �          �          �       @  �       @  �       @  �       @  �       @  �       @  �         �         �          �       �  M         N          O          P          `         a          t          y          z          b         c          X          d         e         _          Q          \         R          K          U         X         Z         �          �         �      
   �         �         �         �         �         �          �          �         �      �����          �          �      (                                                                        "         !          #          $         �          ^          f         g          h          i          j          k         F          H         J         L          N         P         R          U         S          T          V          W          �          �          l          o          p          q          r          s         u          �          v         �          �      ����|         ~         �         x          z      (   �          �         %         �          �          �         @         �          �          �         &          �          	                   �          �          �         �          �         �          �          �          �          �          �          �          �          �          �          �          �                            I         J         K          	          L         M          �                             �          P         Q          S          )          	          	          �           	          +	       @  ,	       @  -	      ��������        ���������������������������������������������������������������������������������������������������������������������.  �         �         �          �                    "          $                                                   '          (          �          �          �          �          �         �          �          �          �         �          �          �          �          �         �      �   �       P  �          �         �       �  �          �       0 0�       � �       0  �       H  �      �  �         a          t          y          z          b          c          X          d         e         _         \         R          K          U        UDPX         Z         �          �         �      
   �         �         �         �         �         �          �          �         �      �����          �          �      (   "          #         $          �          g          h          i          j          k         F          H         J         L          N         P         R          U         S          T          V          W          �          o          p          q          r          s          u          �          v         w          �         |         ~         �         x          z      (   �          %         �          �          �         @         �          �         �      X  �          �         &        ���          	                   �          �          �         �          �         �          �          �          �          �          �          �          �          �          �          �          �         �          �          �                                       I         J         K          	          L         M          �                             �          P         Q          S          )          	          	          �           	          +	       @  ,	       @  -	      ��������        ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������  ��������              Standard Parameter OD                        ����    ���                  ����    ���                                Choose entry type.      
      BOOL   8-bit-Integer   16-bit-Integer   32-bit-Integer   byte   word   double word   real   string   long real (64-bit)                          low   middle   high                       	   read only
   write only
   read-write                             Standard Variable OD                        ����    ���                  ����    ���                          low   middle   high                       	   read only
   write only
   read-write                                                 �  	   	   Name                 ����
   Index                 ��         SubIndex                 �          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Variable    	             ����
   Value                Variable       Min                Variable       Max                Variable          5  
   	   Name                 ����
   Index                 ��         SubIndex                 �          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write    	   Type          ~         INT   UINT   DINT   UDINT   LINT   ULINT   SINT   USINT   BYTE   WORD   DWORD   REAL   LREAL   STRING    
   Value                Type       Default                Type       Min                Type       Max                Type          5  
   	   Name                 ����
   Index                 ��         SubIndex                 �          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write    	   Type          ~         INT   UINT   DINT   UDINT   LINT   ULINT   SINT   USINT   BYTE   WORD   DWORD   REAL   LREAL   STRING    
   Value                Type       Default                Type       Min                Type       Max                Type          d        Member    	             ����   Index-Offset                 ��         SubIndex-Offset                 �          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Min                Member       Max                Member          �  	   	   Name                 ����   Member    	             ����
   Value                Member    
   Index                 ��         SubIndex                 �          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Min                Member       Max                Member          �  	   	   Name                 ����
   Index                 ��         SubIndex                 �          Accesslevel          !         low   middle   high       Accessright          1      	   read only
   write only
   read-write       Variable    	             ����
   Value                Variable       Min                Variable       Max                Variable                         ����  ��������               �   _Dummy@    @   @@    @   @             ��@             ��@@   @     �v@@   ; @+   ����  ��������                                  �v@      4@   �             �v@      D@   �                       �       @                           �f@      4@     �f@                �v@     �f@     @u@     �f@        ���             Module.Root-1__not_found__    Hardware configuration���� IB          % QB          % MB          %   o     Module.K_Bus1Module.Root    K-Bus     IB          % QB          % MB          %    o     Module.FB_VARS2Module.Root    Fieldbus variables    IB          % QB          % MB          %    o     Module.FLAG_VARS3Module.Root    Flag variables    IB          % QB          % MB          %    o     Module.MB_MASTER4Module.Root    Modbus-Master    IB          % QB          % MB          %    ��ST	��ST     ��������           VAR_GLOBAL
END_VAR
                                                                                  "     ��������              ��ST                   start   Called when program starts    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     stop   Called when program stops    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     before_reset   Called before reset takes place    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     after_reset   Called after reset took place    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     shutdownC   Called before shutdown is performed (Firmware update over ethernet)    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     excpt_watchdog%   Software watchdog of IEC-task expired    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     excpt_fieldbus   Fieldbus error    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  	   �.     excpt_ioupdate
   KBus error    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  
   �.     excpt_dividebyzero*   Division by zero. Only integer operations!    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     excpt_noncontinuable   Exception handler    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     after_reading_inputs   Called after reading of inputs    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     before_writing_outputs    Called before writing of outputs    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.  
   debug_loop   Debug loop at breakpoint    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR     �.     online_change+   Is called after CodeInit() at Online-Change    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  !   �.     before_download$   Is called before the Download starts    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  "   �.     event_login/   Is called before the login service is performed    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  �  �.     eth_overload   Ethernet Overload    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  �  �.     eth_network_ready@   Is called directly after the Network and the PLC are initialised    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  �  �.  
   blink_codeN   New blink code / Blink code cleared ( Call STATUS_GET_LAST_ERROR for details )    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  �  �.     interrupt_0(   Interrupt Real Time Clock (every second)    _   FUNCTION systemevent: DWORD VAR_INPUT dwEvent: DWORD; dwFilter: DWORD; dwOwner: DWORD; END_VAR  �  �.  $����  ��������               ��������           Standard T�ST	T�ST      ��������                         	c�ST     ��������           VAR_CONFIG
END_VAR
                                                                                   '              , X X -a           Globale_Variablen ��ST	��ST     ��������        �  VAR_GLOBAL
	g_atHARTModules : ARRAY [1..gc_bHARTMaxModules] OF tHART_2AI; (* Global List of HART modules - keep current config and state *)
	g_iHARTInfoState: INT; (* 0=> Identication of HART modules not started
							  1=> Identication of HART modules in progress
							  2=> Identication of HART modules finished *)
	(* String pointers to string arrays. Assigned in HART_UnitCodeStrings fcn in HART_Info *)
	g_apasHARTUnitCode : ARRAY [1..256, 0..1] OF DWORD;
END_VAR

VAR_GLOBAL CONSTANT
	gc_HARTBufferSize		: INT  := 236;		(* Defines the max size of transmit/receive buffer for HART-commands *)
	gc_HARTWatchdogCmdTimeout: TIME := t#15s;
	gc_bHARTMaxModules		: BYTE := 22(*8*);		(* controller specific max. count of  mailbox io-modules *)
	gc_bHARTRetries			: BYTE := 2;		(* Number of retries on communication errors before job is marked as failed *)
	gc_xAccept_CTRL_PositiveWithoutData: BOOL := TRUE; (* Accept response, even if "positive-without-data" flag set in CRTL byte *)
END_VAR                                                                                                 ~   |0|0 @t    @R   Arial @       HH':'mm':'ss @       dd'-'MM'-'yyyy   dd'-'MM'-'yyyy HH':'mm':'ss�����                               ,     �   ���  �3 ���   � ���     
    @��  ���     @      DEFAULT             System      ~   |0|0 @t    @R   Arial @       HH':'mm':'ss @       dd'-'MM'-'yyyy   dd'-'MM'-'yyyy HH':'mm':'ss�����                      )   HH':'mm':'ss @                             dd'-'MM'-'yyyy @       '   P   , , , Y5        	   tHART_2AI ��ST	��ST      ��������        >  TYPE tHART_2AI :
(* Represant a HART module 750-482 (2AI 4..20mA HART modul)  *)
STRUCT
	bModule	: BYTE;  		(* Number of HART-module, starting with one - zero means there is no HART module aviable *)
	bState	: BYTE;			(* State of module: 0-Idle, 1-Ch1-busy, 2-Ch2-busy *)
	wMbxInOffset : WORD;	(* Startaddress of MailBox in input process image (PAE) *)
	wMbxOutOffset: WORD;	(* Startaddress of MailBox in output process image (PAA) *)
	stCmd0	: ARRAY [1..2] OF tHART_CMD0;(* connected HART devices on Channel 1 and 2, retrieved with HART_CMD0 *)
END_STRUCT
END_TYPE             O   , B B oK           tHART_2AI_MODE8 ��ST	��ST      ��������        s  TYPE tHART_2AI_MODE8 :
(* Represant the process image of a 750-482 (2AI 4..20mA HART modul) with operating mode number 8 (12 Bytes) *)
STRUCT
	 bCtlSt : BYTE;					(* Control / Status depending of the direction. Data to the modul = control byte. Data from modul = status byte. *)
	 bDummy : BYTE;					(* not used *)
	 abMbx  : ARRAY [0..5] OF BYTE; (* Data of HART Mailbox *)
	 wAI1   : WORD;					(* Analog input value of channel 1 in input direction. Not used in the output direction *)
	 wAI2   : WORD;					(* Analog input value of channel 2 in input direction. Not used in the output direction *)
END_STRUCT
END_TYPE             F   , � � ��        
   tHART_CMD0 ��ST	��ST      ��������        �  TYPE tHART_CMD0 :
(* Represants the resultset of a HART CMD0: 'Read unique identifier' *)
STRUCT
	bManufacturerId		: BYTE; 	(* HART device manufacturer ID *)
	bTypeManufDevice 	: BYTE; 	(* HART device manufacturer Device Type *)
	bPreamblesRequest 	: BYTE; 	(* HART device preambles Requested *)
	bCmdRevision 		: BYTE;		(* HART device command Revision *)
	bXmtrRevision 		: BYTE;		(* HART device transmitter Revision *)
	bSwRevision 		: BYTE;		(* HART device software Revision *)
	bHwRevision 		: BYTE;		(* HART device hardware Revision *)
	bFlags 				: BYTE;		(* HART device flags *)
	dwDeviceId 			: DWORD;	(* HART device ID (HART-ADDRESS-LONG)*)
END_STRUCT
END_TYPE             Z   , � � ��        
   tHART_CMD1 ��ST	��ST      ��������        %  TYPE tHART_CMD1:
(* Represants the resultset of a HART CMD1: 'Read primary variable' *)
STRUCT
	rVarPrimary 		: REAL; 		(* Value of primary HART variable*)
	sUnitSymPrimary		: STRING(10); 	(* Symbol of Unit*)
	sUnitTxtPrimary		: STRING(30); 	(* Description of Unit*)
END_STRUCT
END_TYPE             [   , �  ��           tHART_CMD13 ��ST	��ST      ��������        [  TYPE tHART_CMD13:
(* Represants the resultset of a HART CMD13: 'Read tag, descriptor, date'.
	Also used by HART CMD18: 'Write tag, descriptor, date' *)
STRUCT
	sTag			: STRING(8);	(* Unit tag(8 Characters) 			*)
	sDescriptor		: STRING(16); 	(* Unit description(16 Characters) 	*)
	dDate			: DATE;			(* Unit date						*)
END_STRUCT
END_TYPE             L   , � � ��           tHART_CMD14 ��ST	��ST      ��������        �  TYPE tHART_CMD14 :
(* Represants the result set of the HART CMD14 *)
STRUCT
	dwPVSensorSerialNumber: DWORD; (* Sensors serial number *)
	sPVSensorUnitCode: STRING(30); (* Units code for sensor limits and minimum span *)
	rPVUpperSensorLimit: REAL;	   (* Upper sensor limit *)
	rPVLowerSensorLimit: REAL;	   (* Lower sensor limit *)
	rPVMinimalSpan: REAL;		   (* Minimum span *)
END_STRUCT
END_TYPE             d   , � � ��           tHART_CMD15 ��ST	��ST      ��������        �  TYPE tHART_CMD15:
(* Represants the resultset of a HART CMD15: 'Read output information' *)
STRUCT
	bAlarmSelectCode	: BYTE;
	bTxFunctionCode		: BYTE;
	sPVUnitSym			: STRING(10); 	(* Symbol of Unit*)
	sPVUnitTxt			: STRING(30); 	(* Description of Unit*)
	rUpperRangeValue	: REAL;
	rLowerRangeValue	: REAL;
	rDampingValue		: REAL; 		(* seconds *)
	bWriteProtectCode 	: BYTE;
	bPrivateLabelCode	: BYTE; 		(* Private-label describtor code *)
END_STRUCT
END_TYPE             \   , B B SK        
   tHART_CMD2 ��ST	��ST      ��������        �   TYPE tHART_CMD2:
(* Represants the resultset of a HART CMD2: 'Read current and percent of range' *)
STRUCT
	rVarCurrent		: REAL;		(* Value of current HART variable (mA) *)
	rPercentOfRange	: REAL;		(* Percent of range *)
END_STRUCT
END_TYPE             I   ,     T[        
   tHART_CMD3 ��ST	��ST      ��������        �  TYPE tHART_CMD3:
(* Represants the resultset of a HART CMD3: 'Read current and four (predefined) dynamic variables' *)
STRUCT
	rVarCurrent			: REAL;			(* Value of current HART variable (mA)*)
	rVarPrimary 		: REAL; 		(* Value of primary HART variable*)
	sUnitSymPrimary		: STRING(10); 	(* Symbol of Unit*)
	sUnitTxtPrimary		: STRING(30); 	(* Description of Unit*)
	rVarSecondary		: REAL;			(* Value of secondary HART variable*)
	sUnitSymSecondary	: STRING(10); 	(* Symbol of Unit*)
	sUnitTxtSecondary	: STRING(30); 	(* Description of Unit*)
	rVarThird			: REAL;			(* Value of third HART variable*)
	sUnitSymThird		: STRING(10); 	(* Symbol of Unit*)
	sUnitTxtThird		: STRING(30); 	(* Description of Unit*)
	rVarFourth			: REAL;			(* Value of fourth HART variable *)
	sUnitSymFourth		: STRING(10); 	(* Symbol of Unit*)
	sUnitTxtFourth		: STRING(30); 	(* Description of Unit*)
END_STRUCT
END_TYPE             e   , , , Fa           tHART_CMD35 ��ST	��ST      ��������        '  TYPE tHART_CMD35 :
(* Represants the request set of the HART CMD35 *)
STRUCT
	bPvRangeUnitCode : BYTE;	(* UnitCode of primary variable *)
	rPvUpperRangeValue: REAL; 	(* Upper range of primary variable *)
	rPvLowerRangeValue: REAL;	(* Lower range of primary variable *)
END_STRUCT
END_TYPE             n   , � �            tHART_CMD48 ��ST	��ST      ��������        �  TYPE tHART_CMD48 :
(* Represants the resultset of a HART CMD48: 'Read additional device status' *)
STRUCT
	abDeviceSpecificStatus 		: ARRAY [0..5] OF BYTE;  (* Bytes:  0� 5 *)
	abOperationalModes 			: ARRAY [0..1] OF BYTE;  (* Bytes:  6� 7 *)
	abAnalogOutputsSaturated 	: ARRAY [0..2] OF BYTE;	 (* Bytes:  8�10 *)
	abAnalogOutputsFixed 		: ARRAY [0..2] OF BYTE;  (* Bytes: 11�13 *)
	abTransmitterSpecificStatus : ARRAY [0..10]OF BYTE;  (* Bytes: 14�24 *)
END_STRUCT
END_TYPE             c   , X X ia        	   tHART_FDT ��ST	��ST      ��������          TYPE tHART_FDT:
(* Represants the interface for FDT-DTM-Communication *)
STRUCT
	bMsgNumber 		: BYTE; (* Number of DPV1-Request/Response to process *)
	abDpv1Telegram 	: ARRAY [0..gc_HARTBufferSize] OF BYTE; (* DPV1-Request/Response to process *)
END_STRUCT
END_TYPE             / V   , ��a ��           HART_b2UnitSymbol ��ST	��ST      ��������        {   FUNCTION HART_b2UnitSymbol : STRING
VAR_INPUT
	bUnitCode : BYTE;
END_VAR
VAR
	psHelp : POINTER TO STRING(12);
END_VAR�   psHelp := g_apasHARTUnitCode[bUnitCode, 1];
IF psHelp <> 0 THEN
	HART_b2UnitSymbol := psHelp^;
ELSE
	HART_b2UnitSymbol := '';
END_IF
               U   , X X Ta           HART_b2UnitText ��ST	��ST      ��������        x   FUNCTION HART_b2UnitText : STRING
VAR_INPUT
	bUnitCode : BYTE;
END_VAR
VAR
	psHelp: POINTER TO STRING(30);
END_VAR�   psHelp := g_apasHARTUnitCode[bUnitCode, 0];
IF psHelp <> 0 THEN
	HART_b2UnitText := psHelp^;
ELSE
	HART_b2UnitText := '';
END_IF               �   ,   �           HART_CheckModuleResponseCode ��ST	��ST      ��������        q  PROGRAM HART_CheckModuleResponseCode
(* 	This program check CTRL-Fields in Hart-Master-Device(HMD) response.
	The information is mined from abResponse variable from possition 
		abResponse[4]
		abResponse[5]
		abResponse[6] 
	
	Input
		abResponse 		:= 'response data obtained from MailBox'
	Output
		dwError 		:= '16#08xx_yyzz includes error code consisting of 
							xx = abResponse[4], yy = abResponse[5] and 
							zz = abResponse[6]'
		dwWarning 		:= '16#08xx_yyzz includes warning code consisting of 
							xx = abResponse[4], yy = abResponse[5] and
							zz = abResponse[6]'
		sStatus 		:= 'includes status string about the CTRL'
		
*)
VAR_INPUT
	abResponse : ARRAY [0..gc_HARTBufferSize] OF BYTE;
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	dwWarning : DWORD;
	sStatus : STRING;
END_VAR
VAR
	sStatus_apx1 : STRING;
	sStatus_apx2 : STRING;
END_VAR"  (* Reset output variables *)
dwError := 0;
dwWarning := 0;
sStatus := '';
sStatus_apx1 := '';
sStatus_apx2 := '';

(* Response result in CTRL Byte*)
CASE (abResponse[4] AND 16#07) OF
0: (* Invalid *)
	sStatus := CONCAT(sStatus, 'Invalid');
	dwError := BYTE_TO_DWORD(abResponse[4]);
	dwWarning := 0;
1: (* Invalid *)
	sStatus := CONCAT(sStatus, 'Invalid');
	dwError := BYTE_TO_DWORD(abResponse[4]);
	dwWarning := 0;
2: (* Pending - waiting *)
	sStatus := CONCAT(sStatus, 'Pending - waiting');
	dwError := 0;
	dwWarning := BYTE_TO_DWORD(abResponse[4]);
3: (* Pending - executing *)
	sStatus := CONCAT(sStatus, 'Pending - executing');
	dwError	:= 0;
	dwWarning := BYTE_TO_DWORD(abResponse[4]);
4: (* Positive - with data *)
	sStatus := CONCAT(sStatus, 'Positive - with data');
	dwError := 0;
	dwWarning := 0;
5: (* Positive - without data *)
	sStatus := CONCAT(sStatus, 'Positive - without data');
	dwError := 0;
	IF gc_xAccept_CTRL_PositiveWithoutData THEN
		dwWarning := 0;
	ELSE
		dwWarning := BYTE_TO_DWORD(abResponse[4]);
	END_IF
6,7: (* Negative - with, without data *)
	IF (abResponse[4] AND 16#07) = 6 THEN
		sStatus := CONCAT(sStatus, 'Negative - with data,');
	ELSE
		sStatus := CONCAT(sStatus, 'Negative - without data,');
	END_IF
	(* Error analysis in XCTRL Byte *)
	IF (abResponse[5] AND 16#01) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1, 'more status available');
	END_IF
	IF (abResponse[5] AND 16#02) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1, 'bad communication');
	END_IF
	IF (abResponse[5] AND 16#04) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1, '0 check parameter');
	END_IF
	IF (abResponse[5] AND 16#08) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1, 'reserved');
	END_IF
	IF (abResponse[5] AND 16#F0) > 0 THEN
		(* Error Class *)
		CASE SHR((abResponse[5] AND 16#F0),4) OF
		0:
			sStatus := CONCAT(sStatus, 'unspecified');
		1:
			(* HMD error *)
			sStatus_apx1 := CONCAT(sStatus_apx1, 'HMD err - ');
			CASE abResponse[6] OF
			0:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'unspecific');
			1:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'internal communication fault');
			2:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'parameter error');
			3:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'hardware error');
			4:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'wait timer expired');
			5:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'HART timer expired');
			END_CASE
		2:
			sStatus_apx1 := CONCAT(sStatus_apx1, 'Channel err - ');
			CASE abResponse[6] OF
			0:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'unspecific');
			1:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'line fault');
			2:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'short circuit');
			3:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'open line');
			4:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'low output current');
			5:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'parameter error');
			END_CASE
		3:
			sStatus_apx1 := CONCAT(sStatus_apx1, 'Command err - ');
			sStatus_apx2 := CONCAT(sStatus_apx2, BYTE_TO_STRING(abResponse[6]));
		4:
			sStatus_apx1 := CONCAT(sStatus_apx1, 'Request err - ');
			IF (abResponse[6] AND 16#02) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'receive buffer overflow, ');
			END_IF
			IF (abResponse[6] AND 16#08) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'checksum error, ');
			END_IF
			IF (abResponse[6] AND 16#10) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'framing error, ');
			END_IF
			IF (abResponse[6] AND 16#20) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'overrun error, ');
			END_IF
			IF (abResponse[6] AND 16#40) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'parity error, ');
			END_IF
		5:
			sStatus_apx1 := CONCAT(sStatus_apx1, 'Response err - ');
			IF (abResponse[6] AND 16#01) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'GAP timeout, ');
			END_IF
			IF (abResponse[6] AND 16#02) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'receive buffer overflow, ');
			END_IF
			IF (abResponse[6] AND 16#04) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'timeout, ');
			END_IF
			IF (abResponse[6] AND 16#08) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'checksum error, ');
			END_IF
			IF (abResponse[6] AND 16#10) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'framing error, ');
			END_IF
			IF (abResponse[6] AND 16#20) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'overrun error, ');
			END_IF
			IF (abResponse[6] AND 16#40) > 0 THEN
				sStatus_apx2 := CONCAT(sStatus_apx2, 'parity error, ');
			END_IF

		6:
			sStatus_apx1 := CONCAT(sStatus_apx1, 'Request rejected - ');
			CASE abResponse[6] OF
			0:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'unspecific');
			1:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'compact format not supported');
			2:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'SHC not supported');
			3:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'command not allowed');
			4:
				sStatus_apx2 := CONCAT(sStatus_apx2, 'no resources');
			END_CASE
		7:
			sStatus_apx1 := CONCAT(sStatus_apx1, 'Profile request rejected');
		8:
			sStatus_apx1 := CONCAT(sStatus_apx1, 'Manufacturer profile request rejected');
		END_CASE
	END_IF
	dwError	:= SHL(BYTE_TO_DWORD(abResponse[4]), 16) OR
				SHL(BYTE_TO_DWORD(abResponse[5]), 8) OR
				BYTE_TO_DWORD(abResponse[6]);
	dwWarning := 0;
END_CASE
(* Concate the output strings *)
sStatus := CONCAT(sStatus, sStatus_apx1);
sStatus := CONCAT(sStatus, sStatus_apx2);
(* Get error specific class *)
IF dwError > 0 THEN
	dwError := dwError OR 16#08000000;
END_IF
               �   , � � l�           HART_CheckSensorResponseCode ��ST	��ST      ��������        j  PROGRAM HART_CheckSensorResponseCode
(* 	This function analyses the HART sensor Response Code. The information
	is mined from abResponse variable from possition 
		abResponse[14]
		abResponse[15]
	
	Input
		abResponse 		:= 'response data obtained from MailBox'
	Output
		dwError 		:= '16#0000_xxyy includes error code consisting of 
							xx = abResponse[14] and yy = abResponse[15]'
		dwWarning 		:= '16#0000_xxyy includes warnings code consisting of 
							xx = abResponse[14] and yy = abResponse[15]'
		sStatus 		:= 'includes status string about the Response Code'
		sStatus_apx1 	:= 'includes additional status string 
							about the Response Code'		
		
*)
VAR_INPUT
	abResponse : ARRAY [0..gc_HARTBufferSize] OF BYTE;
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	dwWarning : DWORD;
	sStatus : STRING;
END_VAR
VAR
	sStatus_apx1 : STRING;
END_VARI  (* Reset output variables *)
dwError := 0;
dwWarning := 0;
sStatus := '';
sStatus_apx1 := '';

(* Check 1 Byte, 7-bit for communication error flag *)
IF (abResponse[14] AND 16#80) > 0 THEN
	(* Communication errors *)
	CASE abResponse[14] OF
		16#C0:
			sStatus := CONCAT(sStatus, 'Parity Error, ');
		16#A0:
			sStatus := CONCAT(sStatus, 'Overrun Error, ');
		16#90:
			sStatus := CONCAT(sStatus, 'Framing error, ');
		16#88:
			sStatus := CONCAT(sStatus, 'Checksum error, ');
		16#82:
			sStatus := CONCAT(sStatus, 'Rx buffer overflow, ');
		ELSE
			sStatus := CONCAT(sStatus, 'Unspecific communcation error, ');
	END_CASE
	(* Report the error *)
	dwError := BYTE_TO_DWORD(abResponse[14]);
	dwWarning := 0;

ELSE
	(* Command response problems *)
	CASE abResponse[14] OF
		0:
			sStatus := CONCAT(sStatus, 'Success, ');
			dwError := 0;
			dwWarning := 0;
		2:
			sStatus := CONCAT(sStatus, 'Invalid selection, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		3:
			sStatus := CONCAT(sStatus, 'Passed param. too large, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		4:
			sStatus := CONCAT(sStatus, 'Passed param. too small, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		5:
			sStatus := CONCAT(sStatus, 'Too few data bytes received, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		6:
			sStatus := CONCAT(sStatus, 'Device-specific command error, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		7:
			sStatus := CONCAT(sStatus, 'In write-protect mode, ');
			dwError := 0;
			dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		8:
			sStatus := CONCAT(sStatus, 'Update Failed');
			sStatus := CONCAT(sStatus, 'Update In Progress');
			sStatus := CONCAT(sStatus, 'Set To Nearest Possible Value');
			dwError := 0;
			dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		9:
			sStatus := CONCAT(sStatus, 'Applied Process Too High');
			sStatus := CONCAT(sStatus, 'Lower Range Value Too High');
			sStatus := CONCAT(sStatus, 'Not in Fixed Current Mode');
			dwError := 0;
			dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		10:
			sStatus := CONCAT(sStatus, 'Applied Process Too Low');
			sStatus := CONCAT(sStatus, 'Lower Range Value Too Low');
			sStatus := CONCAT(sStatus, 'MiltiDrop Not Supported');
			dwError := 0;
			dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		11:
			sStatus := CONCAT(sStatus, 'In MultiDrop Mode');
			sStatus := CONCAT(sStatus, 'Invalid Transmitter Variable Code');
			sStatus := CONCAT(sStatus, 'Upper Range Value Too High');
			dwError := 0;
			dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		12:
			sStatus := CONCAT(sStatus, 'Invalid Unit Code');
			sStatus := CONCAT(sStatus, 'Upper Range Value Too Low');
			dwError := 0;
			dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		13:
			sStatus := CONCAT(sStatus, 'Both Range Values Out of Limits');
			sStatus := CONCAT(sStatus, 'Invalid Transfer Function Code');
			dwError := 0;
			dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		14:
			sStatus := CONCAT(sStatus, 'Pushed Upper Range Value Over Limit');
			sStatus := CONCAT(sStatus, 'Span Too Small');
			dwError := 0;
			dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		15:
			sStatus := CONCAT(sStatus, 'Invalid Analogue Output Number Code');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		16:
			sStatus := CONCAT(sStatus, 'Access restricted, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		28:
			sStatus := CONCAT(sStatus, 'Invalid range unit code');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		32:
			sStatus := CONCAT(sStatus, 'Device is busy, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		64:
			sStatus := CONCAT(sStatus, 'Cmd not implemented, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
		ELSE
			sStatus := CONCAT(sStatus, 'Undefined response code, ');
			dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
			dwWarning := 0;
	END_CASE
	(* Field Device Status information *)
	IF (abResponse[15] AND 16#80) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1,'Field device malfunction');
		dwError := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
		dwWarning := 0;
	END_IF
	IF (abResponse[15] AND 16#40) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1,'Conf. changed');
		dwError := 0;
		dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
	END_IF
	IF (abResponse[15] AND 16#20) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1,'Cold start');
		dwError := 0;
		dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
	END_IF
	IF (abResponse[15] AND 16#10) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1,'More status available');
		dwError := 0;
		dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
	END_IF
	IF (abResponse[15] AND 16#08) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1,'Analog output current fixed');
		dwError := 0;
		dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
	END_IF
	IF (abResponse[15] AND 16#04) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1,'Analog output saturated');
		dwError := 0;
		dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
	END_IF
	IF (abResponse[15] AND 16#02) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1,'Non-prim. var. out of limits');
		dwError := 0;
		dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
	END_IF
	IF (abResponse[15] AND 16#01) > 0 THEN
		sStatus_apx1 := CONCAT(sStatus_apx1,'Prim. var. out of limits');
		dwError := 0;
		dwWarning := SHL(BYTE_TO_WORD(abResponse[14]), 8) OR
						BYTE_TO_WORD(abResponse[15]);
	END_IF
END_IF

(* Concate the output strings *)
sStatus := CONCAT(sStatus, sStatus_apx1);
(* Get error specific class *)
IF dwError > 0 THEN
	dwError := dwError OR 16#09000000;
END_IF               H   , : ��3�        	   HART_CMD0 ��ST	��ST      ��������        �	  FUNCTION_BLOCK HART_CMD0
(*	The HART_CMD0 "Read unique identifier".

	The function block sends a HART command 0 request to a HART device and processes the response.
   	There is no need to use this functionblock in your application! You find all informations in "g_atHARTModules" 
	g_atHARTModules : ARRAY [1..8] OF tHART_2AI; (* Global List of HART modules - keep current config and state *) 

	RequestData: 
		None

	ResponseData:
		0	 -> "254" (expansion)
		1	 -> Manufacturer identification code
		2	 -> Manufacturer device type code
		3	 -> Number of preambles required
		4	 -> Universal command revision
		5	 -> Device-specific command revision
		6	 -> Software revision
		7	 -> Hardware revision
		8	 -> Device function flags 	-> Type:(H)
		9�11 -> Device ID number		-> Type:(B)

	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
	'	
*)
VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData: tHART_CMD0;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	abRequest  : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	abResponse : ARRAY [0..gc_HARTBufferSize] OF BYTE;

	bCurrentIndex : BYTE; (* Index of HART module in g_atHARTModules *)

	oMailBox : HART_MBX; (* Mailbox client to transfer request/response via kbus to/from HART module *)
	xMailStart  : BOOL;
	dwMailError  : DWORD;
	sMailStatus : STRING;
	iMailRespLen: INT;

	dwWarning: DWORD; (* Response code and CTRL analysis variables *)

	(* Little helpers *)
	i : INT;

END_VARn"  CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		dwError := 0;
		sStatus:= 'RUNNING';
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO (SIZEOF(abRequest) - 1) DO
			abRequest[i] := 0;
			abResponse[i] := 0;
		END_FOR;
		(* Cleanup result set *)
		stData.bManufacturerId	:= 16#00;		(* HART device manufacturer ID *)
		stData.bTypeManufDevice := 16#00; 		(* HART device manufacturer Device Type *)
		stData.bPreamblesRequest:= 16#00; 		(* HART device preambles Requested *)
		stData.bCmdRevision 	:= 16#00;		(* HART device command Revision *)
		stData.bXmtrRevision 	:= 16#00;		(* HART device transmitter Revision *)
		stData.bSwRevision 		:= 16#00;		(* HART device software Revision *)
		stData.bHwRevision 		:= 16#00;		(* HART device hardware Revision *)
		stData.bFlags 			:= 16#00;		(* HART device flags *)
		stData.dwDeviceId 		:= 16#00000000;	(* HART device ID (HART-ADDRESS-LONG)*)
		wState := 5; (* Go Ahead *)
	END_IF

5: (* Check for invalid module and channel numbers *)
	IF (bModule >0 AND (bModule <= 64)) THEN
		IF (bChannel >0 AND (bChannel <= 2)) THEN
			wState := 6; (* Go Ahead *)
		ELSE
			dwError 	:= 16#00000303;
			sStatus := CONCAT('Invalid param "bChannel" ', BYTE_TO_STRING(bChannel) );
			sStatus := CONCAT(sStatus, '. Valid values between 1..2');
			wState  := 999; (* Go Ahead *)
		END_IF
	ELSE
		dwError := 16#00000302;
		sStatus := CONCAT('Invalid param "bModule" ', BYTE_TO_STRING(bModule) );
		sStatus := CONCAT(sStatus, '. Valid values between 1..64');
		wState  := 999; (* Go Ahead *)
	END_IF

6: (* Check if program HART_INFO is part of your project *)
	CASE g_iHARTInfoState OF
	0: (* HART_INFO is not part of your project - Add HART_INFO program *)
		dwError := 16#00000301;
		sStatus := 'HART_INFO is not part of your project - Add HART_INFO program';
		wState := 999; (* Go Ahead *)
	ELSE
		wState := 7; (* Go Ahead *)
	END_CASE


7: (* Find index of HART module in g_atHARTModules *)
	FOR i := 1 TO gc_bHARTMaxModules(*8*) DO (* Scanjet *)
		IF g_atHARTModules[i].bModule = bModule THEN
			bCurrentIndex := INT_TO_BYTE(i);
			EXIT;
		END_IF
	END_FOR
	IF bCurrentIndex > 0 THEN
		wState := 8; (* Go Ahead *)
	ELSE
		dwError := 16#00000306;
		sStatus := 'Invalid parameter "bModule" points to a non HART module';
		wState := 999; (* Go Ahead *)
	END_IF


8: (* Check if program HART_INFO has identified all HART modules *)
	CASE g_iHARTInfoState OF
	1: (* Identication of connected HART modules in progress - Skip checks to retrieve data*)
		sStatus := 'IDENTICATION OF HART MODULES IN PROGRESS';
		wState := 10; (* Go Ahead *)
	2: (* Identification successful finished - This functionblock is called by a user application*)
		wState := 9; (* Go Ahead *)
	ELSE
		; (* ToDo *)
	END_CASE

9: (*Check if sensor connected *)
	IF g_atHARTModules[bCurrentIndex].stCmd0[bChannel].dwDeviceId <> 0 THEN
		wState := 10; (* Go Ahead *)
	ELSE
		dwError := 16#00000305;
		sStatus := CONCAT('No HART sensor connected to module ', BYTE_TO_STRING(bModule) );
		sStatus := CONCAT(sStatus, ' on channel ');
		sStatus := CONCAT(sStatus, BYTE_TO_STRING(bChannel));
		wState := 999; (* Go Ahead *)
	END_IF

10: (* Check if mailbox channel free or occupied by another instance of HART_CMDx *)
	IF g_atHARTModules[bCurrentIndex].bState = 0 THEN
		g_atHARTModules[bCurrentIndex].bState := 1; (* Occupie mailbox *)
		wState := 20; (* Go Ahead *)
	ELSE
		;(* Wait until communication channel is aviable *)
		(* TODO: Insert Timeout handling *)
	END_IF

20: (* Prepare DPV1-Telegram ... put HART request into PROFIBUS DP write request telegram*)
	abRequest[0]  := 16#5F; 			(* FC - Function code of profibus massege *)
	abRequest[1]  := bModule+1; 		(* SLOT - Slot sign the position of the hard device in the plc start with 2 *)
	CASE bChannel OF 					(* INDEX/Channel - Write index for HART on Profibus/ Channel of HART module *)
	1: abRequest[2]  := 16#91;
	2: abRequest[2]  := 16#D1;
	END_CASE
	abRequest[3]  := 16#07; 			(* LENGTH - Length of HART telegram message *)
	abRequest[4]  := 16#00; 			(* CTRL -  control*)
	abRequest[5]  := 16#00; 			(* XCTRL - extention control*)
	abRequest[6]  := 16#02; 			(* DELIM - *)
	abRequest[7]  := 16#80;				(* ADDRS - HART address of slave - SHORT FORMAT *)
	abRequest[8]  := 16#00; 			(* CMD_SA - *)
	abRequest[9]  := 16#00; 			(* BYTECOUNT - length of hart massege ????*)
	abRequest[10] := 16#00;     		(* CRC - clear *)
	(* Calculate CRC *)
	FOR i:=4 TO 9 DO
		abRequest[10] := abRequest[10] XOR abRequest[i]; (* CRC - XOR over HART telegram without LENGTH field *)
	END_FOR
	xMailStart := TRUE;
	wState := 30; (* Go Ahead *)

30:	(* call mailbox FB to transfer request via KBus to HART module *)
	oMailBox(wMbxInputOffset := g_atHARTModules[bCurrentIndex].wMbxInOffset,
			 wMbxOutputOffset:= g_atHARTModules[bCurrentIndex].wMbxOutOffset,
			 pabDpv1Request := ADR(abRequest),
			 iRequestLength := 11, (* CMD0 needs 11 bytes *)
			 pabDpv1Response := ADR(abResponse),
			 xStart := xMailStart,
			 dwError => dwMailError,
			 sStatus => sMailStatus,
			 iResponseLength => iMailRespLen );
	(* Wait until response received *)
	IF xMailStart = FALSE THEN
		(* Check for basic errors in Mailbox communication *)
		IF dwMailError = 0 THEN
			wState := 40; (* Ignore received data and Go Ahead *)
		ELSE
			dwError := dwMailError;
			sStatus := sMailStatus;
			wState := 999; (* Go Ahead *)
		END_IF
	END_IF

40: (* Cleanup telegram buffer's *)
	FOR i:= 0 TO (SIZEOF(abRequest) - 1) DO
		abRequest[i] := 0;
		abResponse[i]:= 0;
	END_FOR;
	wState := 50; (* Go Ahead *)

50: (* Prepare DPV1-Telegram ... put HART request into PROFIBUS DP write request telegram*)
	abRequest[0]  := 16#5E; 			(* FC - Function code of profibus message *)
	abRequest[1]  := bModule+1; 		(* SLOT - Slot sign the position of the hard device in the plc start with 2 *)
	CASE bChannel OF 					(* INDEX/Channel - Write index for HART on Profibus/ Channel of HART module *)
	1: abRequest[2]  := 16#92;
	2: abRequest[2]  := 16#D2;
	END_CASE
	abRequest[3]  := 16#00; 			(* LENGTH - Length of HART telegram message *)
	xMailStart := TRUE;
	wState := 60; (* Go Ahead *)

60:	(* call mailbox FB to transfer request via KBus to HART module *)
	oMailBox(wMbxInputOffset := g_atHARTModules[bCurrentIndex].wMbxInOffset,
			 wMbxOutputOffset:= g_atHARTModules[bCurrentIndex].wMbxOutOffset,
			 pabDpv1Request := ADR(abRequest),
			 iRequestLength := 4, (* CMD0 needs 4 bytes *)
			 pabDpv1Response := ADR(abResponse),
			 xStart := xMailStart,
			 dwError => dwMailError,
			 sStatus => sMailStatus,
			 iResponseLength => iMailRespLen );
	(* Wait until response received *)
	IF xMailStart = FALSE THEN
		 (* Check for basic errors in MailBox communication *)
		IF dwMailError = 0 THEN
			wState := 70; (* Go Ahead *)
		ELSE
			dwError := dwMailError;
			sStatus := sMailStatus;
			wState := 999; (* Go Ahead *)
		END_IF
	END_IF


70: (* Check HART module response code *)
	HART_CheckModuleResponseCode(abResponse:= abResponse,
								 dwError => dwError,
								 dwWarning => dwWarning,
								 sStatus => sStatus);
	(* In case of error *)
	IF dwError > 0 THEN
		wState := 999; (* Go to error state *)
	ELSE
		IF dwWarning > 0 THEN
			wState := 40; (* In case of warning - Try it again *)
		ELSE (* In case of success *)
			wState := 90; (* Go Ahead *)
		END_IF
	END_IF

90: (* Copy Response data *)
	stData.bManufacturerId	:= abResponse[13];			(* HART device manufacturer ID *)
	stData.bTypeManufDevice := abResponse[14]; 			(* HART device manufacturer Device Type *)
	stData.bPreamblesRequest:= abResponse[15]; 			(* HART device preambles Requested *)
	stData.bCmdRevision 	:= abResponse[16];			(* HART device command Revision *)
	stData.bXmtrRevision 	:= abResponse[17];			(* HART device transmitter Revision *)
	stData.bSwRevision 		:= abResponse[18];			(* HART device software Revision *)
	stData.bHwRevision 		:= abResponse[19];			(* HART device hardware Revision *)
	stData.bFlags 			:= abResponse[20];			(* HART device flags *)
	stData.dwDeviceId 		:= HART_pab2DWORD(ADR(abResponse[21]));	(* HART device ID (HART-ADDRESS-LONG)*)
	dwError := 0;
	IF dwWarning = 0 THEN
		(* No warnings from CTRL or HART response *)
		sStatus := 'Successfuly executed';
	END_IF
	(* Free resources every time *)
	xStart := FALSE;
	g_atHARTModules[bCurrentIndex].bState := 0; (* free mailbox *)
	wState := 0;

ELSE (* ------------------------------------------------------*)
	(* The Error State *)
	xStart := FALSE;
	IF bCurrentIndex > 0 THEN
		g_atHARTModules[bCurrentIndex].bState := 0; (* free mailbox *)
	END_IF
	wState := 0; (* Go Ahead *)
END_CASE;

               S   ,             	   HART_CMD1 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD1
(* The HART_CMD1 "Read primary variable".
   The function block sends a HART command 1 request to a HART device and processes the response. 
	RequestData: 
		None
	ResponseData:
		0	-> PV units code		-> Type:(B)
		1�4	-> Primary variable 	-> Type:(F)

	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData: tHART_CMD1;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params - CMD1 do not need request params *)
	xCmdStart : BOOL;
END_VAR7  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		bHartCmd := 1;
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process result *)
			stData.rVarPrimary 		:= HART_pab2REAL(ADR(abCmdData[1]));
			stData.sUnitSymPrimary	:= HART_b2UnitSymbol(abCmdData[0]);
			stData.sUnitTxtPrimary 	:= HART_b2UnitText(abCmdData[0]);
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               M   , �   �        
   HART_CMD11 ��ST	��ST      ��������          FUNCTION_BLOCK HART_CMD11
(* 	The HART_CMD11 "Read unique identifier associated with input tag".
	
	The function block sends a HART command 11 request to a HART device and processes 
	the response. 

	RequestData: 
		0-5 	-> Unit tag(8 Characters) -> Type:(A)
	ResponseData:
		0	 -> "254" (expansion)
		1	 -> Manufacturer identification code
		2	 -> Manufacturer device type code
		3	 -> Number of preambles required
		4	 -> Universal command revision
		5	 -> Device-specific command revision
		6	 -> Software revision
		7	 -> Hardware revision
		8	 -> Device function flags 	-> Type:(H)
		9�11 -> Device ID number		-> Type:(B)
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	sTag : STRING(8);  	(* Unit tag *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData: tHART_CMD0;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VAR
  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 11;
		HART_STRING2pab(sTag, 8, ADR(abCmdData[0]));
		bCmdDataCount := 6; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process CMD11 response *)
			stData.bManufacturerId	:= abCmdData[1];			(* HART device manufacturer ID *)
			stData.bTypeManufDevice := abCmdData[2]; 			(* HART device manufacturer Device Type *)
			stData.bPreamblesRequest:= abCmdData[3]; 			(* HART device preambles Requested *)
			stData.bCmdRevision 	:= abCmdData[4];			(* HART device command Revision *)
			stData.bXmtrRevision 	:= abCmdData[5];			(* HART device transmitter Revision *)
			stData.bSwRevision 		:= abCmdData[6];			(* HART device software Revision *)
			stData.bHwRevision 		:= abCmdData[7];			(* HART device hardware Revision *)
			stData.bFlags 			:= abCmdData[8];			(* HART device flags *)
			stData.dwDeviceId 		:= HART_pab2DWORD(ADR(abCmdData[9]));	(* HART device ID (HART-ADDRESS-LONG)*)
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               _   , � � ��        
   HART_CMD12 ��ST	��ST      ��������        [  FUNCTION_BLOCK HART_CMD12
(* The HART_CMD12 "Read message".
   The function block sends a HART command 12 request to a HART device and processes the response. 
	RequestData: 
		None
	ResponseData:
		0�23 	-> Message (32 characters) 			-> Type:(A)
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	sMessage: STRING(32);
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;
END_VAR�  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		bHartCmd := 12; (* The HART_CMD12 "Read message" *)
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process CMD12 response *)
			sMessage := HART_pab2sMsg(ADR(abCmdData[0]) );
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               R   , 9 � �_        
   HART_CMD13 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD13
(* The HART_CMD13 "Read tag, descriptor and date".
   The function block sends a HART command 13 request to a HART device and processes the response. 
	RequestData: 
		None
	ResponseData:
		0-5 	-> Unit tag(8 Characters) 			-> Type:(A)
		6-17 	-> Unit description(16 Characters) 	-> Type:(A)
		18-20	-> Unit date						-> Type:(D)
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData: tHART_CMD13;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;
END_VAR3  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		bHartCmd := 13;
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process CMD13 response *)
			stData.sTag 		:= HART_pab2sTag(ADR(abCmdData[0]) );
			stData.sDescriptor 	:= HART_pab2sDesc(ADR(abCmdData[6]));
			stData.dDate 	:= HART_pab2DATE(ADR(abCmdData[18]));
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               D   ,   ��        
   HART_CMD14 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD14
(* 	The HART_CMD14 "Sensor serial number,Units code for sensor limits and minimum span,
	Upper sensor limit, Lower sensor limit, Minimum span".
	
	The function block sends a HART command 14 request to a HART device and processes 
	the response. 

	RequestData: 
		None
	ResponseData:
		0-2		-> 	Sensor serial number				-> 
		3		-> 	Units code for limits and minimum span						
		4-7		-> 	Upper sensor limit					-> Type:(F)
		8-11	-> 	Lower sensor limit					-> Type:(F)
		12-15	-> 	Minimum span						-> Type:(F)
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData: tHART_CMD14;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

END_VAR�  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		bHartCmd := 14;
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process CMD14 response *)
			stData.dwPVSensorSerialNumber:= HART_pab2dwSerialNumber(ADR(abCmdData[0]));
			stData.sPVSensorUnitCode   	 := HART_b2UnitSymbol(abCmdData[3]);
			stData.rPVUpperSensorLimit   := HART_pab2REAL(ADR(abCmdData[4]));
			stData.rPVLowerSensorLimit   :=	HART_pab2REAL(ADR(abCmdData[8]));
			stData.rPVMinimalSpan 	     := HART_pab2REAL(ADR(abCmdData[12]));
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               X   , � ���        
   HART_CMD15 ��ST	��ST      ��������        X  FUNCTION_BLOCK HART_CMD15
(* The HART_CMD15 "Read output information".
   The function block sends a HART command 15 request to a HART device and processes the response.
	RequestData: 
		None
	ResponseData:
		0 		-> Alarm select code
		1		-> Transfer function code		
		2		-> PV range unit code 
		3-6 	-> Upper range value	 -> Type:(F)
		7-10 	-> Lower range value	 -> Type:(F)
		11-14 	-> DampingValue	(seconds)-> Type:(F)
		15		-> Write protect code 	
		16 		-> Private-label describtor code
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData: tHART_CMD15;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;
END_VARv  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		bHartCmd := 15;
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process CMD15 response *)

			stData.bAlarmSelectCode := abCmdData[0];
			stData.bTxFunctionCode 	:= abCmdData[1];
			stData.sPVUnitSym		:= HART_b2UnitSymbol(abCmdData[2]);
			stData.sPVUnitTxt 		:= HART_b2UnitText(abCmdData[2]);
			stData.rUpperRangeValue := HART_pab2REAL(ADR(abCmdData[3]));
			stData.rLowerRangeValue := HART_pab2REAL(ADR(abCmdData[7]));
			stData.rDampingValue    := HART_pab2REAL(ADR(abCmdData[11]));
			stData.bWriteProtectCode:= abCmdData[15];
			stData.bPrivateLabelCode:= abCmdData[16];
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               N   , n n ��        
   HART_CMD16 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD16
(* The HART_CMD16 "Read final assmbly number".
   The function block sends a HART command 16 request to a HART device and processes the response. 
	RequestData: 
		None
	ResponseData:
		0�2 	-> Final assembly number		-> Type:?

	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	dwFinalAssemblyNumber: DWORD;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
END_VAR  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		bHartCmd := 16;
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process result *)
			pabHelp := ADR(dwFinalAssemblyNumber);
			pabHelp^[0] := abCmdData[2];
			pabHelp^[1] := abCmdData[1];
			pabHelp^[2] := abCmdData[0];
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               a   , � � ��        
   HART_CMD17 ��ST	��ST      ��������        r  FUNCTION_BLOCK HART_CMD17
(* The HART_CMD17 "Write message".
   The function block sends a HART command 17 request to a HART device and processes the response. 
	RequestData: 
		0�23 	-> Message (32 characters) 			-> Type:(A)
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	sMessage : STRING(32);
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VARE  (* Reset state machine *)
(* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 17; (* The HART_CMD17 "Write Message"*)
		(* Prepare CMD17 request data *)
		HART_STRING2pab(sMessage, 32, ADR(abCmdData[0]));
		bCmdDataCount := 24; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               ]   ,     �        
   HART_CMD18 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD18
(* The HART_CMD18 "Write tag, descriptor and date".
   The function block sends a HART command 18 request to a HART device and processes the response. 
	RequestData: 
		0-5 	-> Unit tag(8 Characters) 			-> Type:(A)
		6-17 	-> Unit description(16 Characters) 	-> Type:(A)
		18-20	-> Unit date						-> Type:(D)
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	stData	 : tHART_CMD13;
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VAR{  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 18;
		(* Prepare CMD18 request data *)
		HART_STRING2pab(stData.sTag, 8, ADR(abCmdData[0]));
		HART_STRING2pab(stData.sDescriptor, 16, ADR(abCmdData[6]));
		HART_DATE2pab(stData.dDate, ADR(abCmdData[18]));
		bCmdDataCount := 21; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               b   , , , 95        
   HART_CMD19 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD19
(* The HART_CMD19 "Write final assmbly number".
   The function block sends a HART command 19 request to a HART device and processes the response. 
	RequestData: 
		0�2 	-> Final assembly number		-> Type:?
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	dwFinalAssemblyNumber: DWORD;
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	i: INT;
END_VARZ  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 19;
		(* Prepare CMD19 request data *)
		pabHelp := ADR(dwFinalAssemblyNumber);
		abCmdData[2] := pabHelp^[0];
		abCmdData[1] := pabHelp^[1];
		abCmdData[0] := pabHelp^[2];
		bCmdDataCount := 3; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               T   , , , =5        	   HART_CMD2 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD2
(* The HART_CMD2 "Read current and percent of range".
   The function block sends a HART command 2 request to a HART device and processes the response.
	RequestData: 
		None
	ResponseData:
		0�3 -> Current (mA) 		-> Type:(F)
		4�7 -> Percent of range		-> Type:(F)
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData: tHART_CMD2;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;
END_VAR�  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		bHartCmd := 2;
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process result *)
			stData.rVarCurrent 		:= HART_pab2REAL(ADR(abCmdData[0]));
			stData.rPercentOfRange 	:= HART_pab2REAL(ADR(abCmdData[4]));
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               ^   , F > W1        	   HART_CMD3 ��ST	��ST      ��������        {  FUNCTION_BLOCK HART_CMD3
(* The HART_CMD3 "Read all variables".
   The function block sends a HART command 3 request to a HART device and processes the response.
	RequestData: 
		None
	ResponseData:
		0�3 	-> Current (mA)			-> Type:(F)
		4		-> PV units code	
		5�8		-> Primary variable 	-> Type:(F)
		9		-> SV units code
		10�13 	->	Secondary variable 	-> Type:(F)
		14 		->	TV units code
		15�18 	->	Third variable 		-> Type:(F)
		19 		->	FV units code
		20�23 	->	Fourth variable		-> Type:(F)
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData: tHART_CMD3;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params - CMD3 do not need request params *)
	xCmdStart : BOOL;
END_VAR,  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		bHartCmd := 3;
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process CMD3 response *)
			stData.rVarCurrent 		:= HART_pab2REAL(ADR(abCmdData[0]));
			stData.sUnitSymPrimary	:= HART_b2UnitSymbol(abCmdData[4]);
			stData.sUnitTxtPrimary 	:= HART_b2UnitText(abCmdData[4]);
			stData.rVarPrimary 		:= HART_pab2REAL(ADR(abCmdData[5]));
			IF bCmdDataCount >= 13 THEN
			stData.sUnitSymSecondary:= HART_b2UnitSymbol(abCmdData[9]);
			stData.sUnitTxtSecondary:= HART_b2UnitText(abCmdData[9]);
			stData.rVarSecondary	:= HART_pab2REAL(ADR(abCmdData[10]));
			END_IF
			IF bCmdDataCount >= 18 THEN
			stData.sUnitSymThird	:= HART_b2UnitSymbol(abCmdData[14]);
			stData.sUnitTxtThird	:= HART_b2UnitText(abCmdData[14]);
			stData.rVarThird 		:= HART_pab2REAL(ADR(abCmdData[15]));
			END_IF
			IF bCmdDataCount >= 23 THEN
			stData.sUnitSymFourth 	:= HART_b2UnitSymbol(abCmdData[19]);
			stData.sUnitTxtFourth	:= HART_b2UnitText(abCmdData[19]);
			stData.rVarFourth 		:= HART_pab2REAL(ADR(abCmdData[20]));
			END_IF
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               o   , , , �5        
   HART_CMD33 ��ST	��ST      ��������        c  FUNCTION_BLOCK HART_CMD33
(* The functionblock send a the common practice HART_CMD33  "read transmitter variables".
   The function block sends a HART command 33 request to a HART device and processes the response.
	RequestData:		 
		0 		-> Transmitter var. code for slot 0 -> Type:(B)
		1		-> Transmitter var. code for slot 1 -> Type:(B)	
		2		-> Transmitter var. code for slot 2 -> Type:(B)	
		3		-> Transmitter var. code for slot 3 -> Type:(B)
		(truncated after last requested variable)
	ResponseData:
		0 		-> Transmitter var. code for slot 0 -> Type:(B)
		1		-> Unit code for slot 0 			-> Type:(B)	
		2�5 	-> Value slot 0						-> Type:(F)	
		6 		-> Transmitter var. code for slot 1 -> Type:(B)
		7		-> Unit code for slot 1 			-> Type:(B)	
		8�11 	-> Value slot 1						-> Type:(F)
		12 		-> Transmitter var. code for slot 2 -> Type:(B)
		13		-> Unit code for slot 2 			-> Type:(B)	
		14�17 	-> Value slot 2						-> Type:(F)	
		18 		-> Transmitter var. code for slot 3 -> Type:(B)
		19		-> Unit code for slot 3 			-> Type:(B)	
		20�23 	-> Value slot 3						-> Type:(F)		
		(truncated after last requested variable)
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	bVarCodeSlot0 : BYTE;	(* Transmitter var. code for slot 0 *)
	bVarCodeSlot1 : BYTE;	(* Transmitter var. code for slot 1 *)
	bVarCodeSlot2 : BYTE;	(* Transmitter var. code for slot 2 *)
	bVarCodeSlot3 : BYTE;	(* Transmitter var. code for slot 3 *)
END_VAR
VAR_IN_OUT
	xStart 	: BOOL; (* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus	: STRING;
	stDataSlot0: tHART_CMD1;
	stDataSlot1: tHART_CMD1;
	stDataSlot2: tHART_CMD1;
	stDataSlot3: tHART_CMD1;
END_VAR
VAR
	(* Custom HART command *)
	oCustomCmd	: HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData 	: ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)

	xCmdStart : BOOL;
	wState : WORD;
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	i :INT;
END_VAR>	  oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 33;
		(* Prepare CMD33 request data *)
		abCmdData[0] := bVarCodeSlot0;
		abCmdData[1] := bVarCodeSlot1;
		abCmdData[2] := bVarCodeSlot2;
		abCmdData[3] := bVarCodeSlot3;
		(* Truncate request *)
		IF bVarCodeSlot1 = 0 THEN
			bCmdDataCount := 1; (* Request data only for slot 0 *)
		ELSIF bVarCodeSlot2 = 0 THEN
			bCmdDataCount := 2; (* Request data for slots 0 and 1 *)
		ELSIF bVarCodeSlot3 = 0 THEN
			bCmdDataCount := 3; (* Request data for slots 0,1 and 2 *)
		ELSE
			bCmdDataCount := 4; (* Request data for all slots *)
		END_IF
		(* Start execution *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process result *)
			IF bCmdDataCount >= 6 THEN
				(* Data available for slot 0 *)
				stDataSlot0.rVarPrimary 	:= HART_pab2REAL(ADR(abCmdData[2]));
				stDataSlot0.sUnitSymPrimary	:= HART_b2UnitSymbol(abCmdData[1]);
				stDataSlot0.sUnitTxtPrimary := HART_b2UnitText(abCmdData[1]);
			END_IF
			IF bCmdDataCount >= 12 THEN
				(* Data available for slot 1 *)
				stDataSlot1.rVarPrimary 	:= HART_pab2REAL(ADR(abCmdData[8]));
				stDataSlot1.sUnitSymPrimary	:= HART_b2UnitSymbol(abCmdData[7]);
				stDataSlot1.sUnitTxtPrimary := HART_b2UnitText(abCmdData[7]);
			END_IF
			IF bCmdDataCount >= 18 THEN
				(* Data available for slot 2 *)
				stDataSlot2.rVarPrimary 	:= HART_pab2REAL(ADR(abCmdData[14]));
				stDataSlot2.sUnitSymPrimary	:= HART_b2UnitSymbol(abCmdData[13]);
				stDataSlot2.sUnitTxtPrimary := HART_b2UnitText(abCmdData[13]);
			END_IF
			IF bCmdDataCount >= 24 THEN
				(* Data available for slot 3 *)
				stDataSlot3.rVarPrimary 	:= HART_pab2REAL(ADR(abCmdData[20]));
				stDataSlot3.sUnitSymPrimary	:= HART_b2UnitSymbol(abCmdData[19]);
				stDataSlot3.sUnitTxtPrimary := HART_b2UnitText(abCmdData[19]);
			END_IF
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;               B   , � � ��        
   HART_CMD34 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD34
(* The HART_CMD34 "Write primary variable damping value".
   The function block sends a HART command 34 request to a HART device and processes the response. 
	RequestData: 
		0�3 	-> PV Damping value (seconds) 	-> Type:(F)
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	rPVDumpingValue : REAL;
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VAR\  (* Reset state machine *)
(* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 34; (* The HART_CMD34 "Write primary variable damping value"*)
		(* Prepare CMD34 request data *)
		HART_REAL2pab(rPVDumpingValue, ADR(abCmdData[0]));
		bCmdDataCount := 4; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               K   , � � �        
   HART_CMD35 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD35
(* The HART_CMD35 "Write primary variable range values".
   The function block sends a HART command 35 request to a HART device and processes the response. 
	RequestData: 
		0		-> PV Range unit code		-> Type:(B)
		1�4 	-> PV Upper range value 	-> Type:(F)
		5�9 	-> PV Lower range value 	-> Type:(F)
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	stData : tHART_CMD35;
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VAR�  (* Reset state machine *)
(* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 35; (* The HART_CMD35 "Write primary variable range values"*)
		(* Prepare CMD35 request data *)
		abCmdData[0] := stData.bPvRangeUnitCode;
		HART_REAL2pab(stData.rPvUpperRangeValue, ADR(abCmdData[1]));
		HART_REAL2pab(stData.rPvLowerRangeValue, ADR(abCmdData[5]));
		bCmdDataCount := 9; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               f   , � � ��        
   HART_CMD38 ��ST	��ST      ��������        8  FUNCTION_BLOCK HART_CMD38
(* The HART_CMD38 "Reset configuration changed flag".
   The function block sends a HART command 38 request to a HART device and processes the response. 
	RequestData: 
		None
	ResponseData:
		None
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VAR"  (* Reset state machine *)
(* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 38; (* The HART_CMD38 "Reset configuration changed flag"*)
		(* Prepare CMD38 request data *)
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               g   , � � ��        
   HART_CMD40 ��ST	��ST      ��������          FUNCTION_BLOCK HART_CMD40
(* The HART_CMD40 "Enter/Exit primary variable current mode".
   The function block sends a HART command 40 request to a HART device and processes the response. 
	RequestData: 
		0�3 	-> Fixed PV current level (mA) 	-> Type:(F)
				   [send 0.0 to exit Fix-Current-Mode]	
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
	rPVCurrentLevel : REAL; (* transmit the "fixed PV current level" and returns the actual "fixed PV current level" *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VAR�  (* Reset state machine *)
(* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 40; (* "Enter/Exit primary variable current mode"*)
		(* Prepare CMD40 request data *)
		HART_REAL2pab(rPVCurrentLevel, ADR(abCmdData[0]));
		bCmdDataCount := 4; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN
			rPVCurrentLevel := HART_pab2REAL(ADR(abCmdData[0]));
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               r   , � � 1�        
   HART_CMD44 ��ST	��ST      ��������          FUNCTION_BLOCK HART_CMD44
(* The functionblock send a the common practice HART_CMD44  "write primary variable units".
   The function block sends a HART command 44 request to a HART device and processes the response.
	RequestData:		 
		0 		-> Unit code for primary variable 	-> Type:(B)

	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	bPrimaryVarUnitCode  : BYTE;	(* Unit code for primary variable *)
END_VAR
VAR_IN_OUT
	xStart 	: BOOL; (* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus	: STRING;
END_VAR
VAR
	(* Custom HART command *)
	oCustomCmd	: HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData 	: ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)

	xCmdStart : BOOL;
	wState : WORD;
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	i :INT;
END_VARC  oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 44; (* "write primary variable units" *)
		(* Prepare CMD44 request data *)
		abCmdData[0] := bPrimaryVarUnitCode; (* Unit code for primary variable *)
		bCmdDataCount := 1; (* No additional request params needed *)
		(* Start execution *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;               i   , � � ��        
   HART_CMD45 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD45
(* The HART_CMD45 "Trim primary variable current DAC zero".
   The function block sends a HART command 45 request to a HART device and processes the response. 
	RequestData: 
		0�3 	-> Measured current (mA) 	-> Type:(F)				   	
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	rPVMeasuredCurrent : REAL;
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VARa  (* Reset state machine *)
(* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 45; (* The HART_CMD45 "Trim primary variable current DAC zero"*)
		(* Prepare CMD45 request data *)
		HART_REAL2pab(rPVMeasuredCurrent, ADR(abCmdData[0]));
		bCmdDataCount := 4; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               j   , � � ��        
   HART_CMD46 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD46
(* The HART_CMD46 "Trim primary variable current DAC gain".
   The function block sends a HART command 46 request to a HART device and processes the response. 
	RequestData: 
		0�3 	-> Measured current (mA) 	-> Type:(F)				   	
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	rPVMeasuredCurrent : REAL;
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VARa  (* Reset state machine *)
(* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 46; (* The HART_CMD46 "Trim primary variable current DAC gain"*)
		(* Prepare CMD46 request data *)
		HART_REAL2pab(rPVMeasuredCurrent, ADR(abCmdData[0]));
		bCmdDataCount := 4; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               m   , � � ��        
   HART_CMD48 ��ST	��ST      ��������        o  FUNCTION_BLOCK HART_CMD48
(* The HART_CMD48 "Read additional device status".
   The function block sends a HART command 48 request to a HART device and processes the response. 
	RequestData: 
		None
	ResponseData:
		0�5		-> Device specific status		-> Type:(B)
		6�7 	-> Operational modes			-> Type:(B)
		8�10 	-> Analog outputs saturated*	-> Type:(B)
		11�13 	-> Analog outputs fixed*		-> Type:(B)
		14�24 	-> Transmitter specific status	-> Type:(B)

			*[24 bits each: LSB ... MSB refers to AO #1 ... #24] 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	stData : tHART_CMD48;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;

	i: INT;
END_VAR�  (* Reset state machine *)
(* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 48; (* The HART_CMD48 "Read additional device status"*)
		(* Prepare CMD48 request data *)
		bCmdDataCount := 0; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 0 THEN
			FOR i:=0 TO 5 DO
				stData.abDeviceSpecificStatus[i] := abCmdData[i];
			END_FOR
			FOR i:=0 TO 1 DO
				stData.abOperationalModes[i] := abCmdData[6+i];
			END_FOR
			FOR i:=0 TO 2 DO
				stData.abAnalogOutputsSaturated[i] := abCmdData[8+i];
			END_FOR
			FOR i:=0 TO 2 DO
				stData.abAnalogOutputsFixed[i] := abCmdData[11+i];
			END_FOR
			FOR i:=0 TO 9 DO
				stData.abAnalogOutputsFixed[i] := abCmdData[14+i];
			END_FOR
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               p   , B B �K        
   HART_CMD50 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD50
(* The functionblock send a the common practice HART_CMD50  "read dynamic variable assignements".
   The function block sends a HART command 50 request to a HART device and processes the response.
	RequestData:		 
		NONE

	ResponseData:
		0 		-> Transmitter var. code for primary variable 	-> Type:(B)
		1		-> Transmitter var. code for secondary variable -> Type:(B)	
		2		-> Transmitter var. code for tertiary variable 	-> Type:(B)	
		3		-> Transmitter var. code for 4th variable		-> Type:(B)
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
END_VAR
VAR_IN_OUT
	xStart 	: BOOL; (* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus	: STRING;
	bVarCode_Primary  : BYTE;	(* Transmitter var. code for primary variable *)
	bVarCode_Secondary: BYTE;	(* Transmitter var. code for secondary variable *)
	bVarCode_Tertiary : BYTE;	(* Transmitter var. code for tertiary variable *)
	bVarCode_4th	  : BYTE;	(* Transmitter var. code for 4th variable *)
END_VAR
VAR
	(* Custom HART command *)
	oCustomCmd	: HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData 	: ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)

	xCmdStart : BOOL;
	wState : WORD;
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	i :INT;
END_VAR�  oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 50; (* "read dynamic variable assignements" *)
		(* Prepare CMD50 request data *)
		bCmdDataCount := 0; (* No additional request params needed *)
		(* Start execution *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		IF dwError = 16#0000 THEN (* Process result *)
			bVarCode_Primary   := abCmdData[0];	(* Transmitter var. code for primary variable *)
			bVarCode_Secondary := abCmdData[1];	(* Transmitter var. code for secondary variable *)
			bVarCode_Tertiary  := abCmdData[2];	(* Transmitter var. code for tertiary variable *)
			bVarCode_4th 	   := abCmdData[3];	(* Transmitter var. code for 4th variable *)
		END_IF
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;               q   , n n w        
   HART_CMD51 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD51
(* The functionblock send a the common practice HART_CMD51  "write dynamic variable assignements".
   The function block sends a HART command 51 request to a HART device and processes the response.
	RequestData:		 
		0 		-> Transmitter var. code for primary variable 	-> Type:(B)
		1		-> Transmitter var. code for secondary variable -> Type:(B)	
		2		-> Transmitter var. code for tertiary variable 	-> Type:(B)	
		3		-> Transmitter var. code for 4th variable		-> Type:(B)

	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	bVarCode_Primary  : BYTE;	(* Transmitter var. code for primary variable *)
	bVarCode_Secondary: BYTE;	(* Transmitter var. code for secondary variable *)
	bVarCode_Tertiary : BYTE;	(* Transmitter var. code for tertiary variable *)
	bVarCode_4th	  : BYTE;	(* Transmitter var. code for 4th variable *)
END_VAR
VAR_IN_OUT
	xStart 	: BOOL; (* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus	: STRING;
END_VAR
VAR
	(* Custom HART command *)
	oCustomCmd	: HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData 	: ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)

	xCmdStart : BOOL;
	wState : WORD;
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	i :INT;
END_VART  oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 51; (* "read dynamic variable assignements" *)
		(* Prepare CMD51 request data *)
		abCmdData[0] := bVarCode_Primary; 	(* Transmitter var. code for primary variable *)
		abCmdData[1] := bVarCode_Secondary;	(* Transmitter var. code for secondary variable *)
		abCmdData[2] := bVarCode_Tertiary;	(* Transmitter var. code for tertiary variable *)
		abCmdData[3] := bVarCode_4th;		(* Transmitter var. code for 4th variable *)
		bCmdDataCount := 4; (* No additional request params needed *)
		(* Start execution *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;               s   , � � G�        
   HART_CMD53 ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMD53
(* The functionblock send a the common practice HART_CMD53  "write transmitter variable units".
   The function block sends a HART command 53 request to a HART device and processes the response.
	RequestData:		 
		0 		-> Transmitter variable to be set 		-> Type:(B)
		1 		-> Unit code for transmitter variable 	-> Type:(B)

	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	bTransmitterVariable : BYTE; (* Transmitter variable to be set *)
	bTransmitterUnitCode : BYTE; (* Unit code for transmitter variable *)
END_VAR
VAR_IN_OUT
	xStart 	: BOOL; (* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus	: STRING;
END_VAR
VAR
	(* Custom HART command *)
	oCustomCmd	: HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData 	: ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)

	xCmdStart : BOOL;
	wState : WORD;
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	i :INT;
END_VAR�  oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 53; (* "write transmitter variable units" *)
		(* Prepare CMD53 request data *)
		abCmdData[0] := bTransmitterVariable; (* Transmitter variable to be set *)
		abCmdData[1] := bTransmitterUnitCode; (* Unit code for transmitter variable *)
		bCmdDataCount := 2; (* No additional request params needed *)
		(* Start execution *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;               �   , X X @\        	   HART_CMD6 ��ST	��ST      ��������        	  FUNCTION_BLOCK HART_CMD6
(* The HART_CMD6 "Write polling address".
   The function block sends a HART command 6 request to a HART device and processes 
   the response. 

	RequestData: 
		0 	-> Polling address -> Type:?
	ResponseData:
		As in request
 
	dwError: 
		16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
		16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
		16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
		16#00000305 => 'No HART sensor connected to module x on channel y'
		16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
		16#08xxyyzz => 'Response codes from HART module (see HART specification for details)'
		16#0900xxyy => 'Response codes from HART sensor (see HART specification for details)'
*)

VAR_INPUT
	bModule  : BYTE;		(* 	Index of plugged HART module start with one - DPV1-Slot
						   		number start with 2 *)
	bChannel : BYTE;		(* 	The channel of the I/O-Module where the HART device is
						   		connected (called Index DPV1). Valid values are 1 and 2. *)
	bPollingAddress: BYTE; 	(* 	Polling Adress (0�15). Using the polling address structure
								of the HART protocol, up to 15 devices can be connected in
								a multidrop network.  
								The analog current of a HART device can be fixed by setting
								its polling address to a number other than zero.								 
								With the HART protocol, each field instrument should be
								configured with different polling addresses or tag numbers
								before being connected to a multidrop network�otherwise,
								the master will not be able to establish communication with								 
								the slave devices.
							*)
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution of the HART command.
						   When finished or after a timeout xStart is set to false - Check 
						   wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* State mashine *)

	oCustomCmd : HART_CMDCustom;
	bHartCmd : BYTE;
	abCmdData : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bCmdDataCount: BYTE; (* Number of bytes for additional request params *)
	xCmdStart : BOOL;
	(* Helpers *)
	i: INT;
END_VAR  (* Use custom CMD *)
oCustomCmd(	bModule:= bModule,
			bChannel:= bChannel,
			bHART_CMD:= bHartCmd,
			xStart:= xCmdStart,
			abData:= abCmdData,
			bDataCount:= bCmdDataCount,
			dwError=> dwError,
			sStatus=> sStatus);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO gc_HARTBufferSize DO
			abCmdData[i] := 0;
		END_FOR;
		bHartCmd := 6; (* The HART_CMD6 "Write polling address"*)
		(* Prepare CMD6 request data *)
		abCmdData[0] := bPollingAddress;
		bCmdDataCount := 1; (* Number of additional request params *)
		xCmdStart := TRUE;
		wState := 10; (* Go Ahead *)
	END_IF

10: (* Execute HART Command  *)
	IF xCmdStart = FALSE THEN
		xStart := FALSE;
		wState := 0;
	END_IF

END_CASE;
               Y   ,     ~           HART_CMDCustom ��ST	��ST      ��������        �  FUNCTION_BLOCK HART_CMDCustom
(* The functionblock "HART_CMDCustom" allows the execution of any HART_CMD.
   The function block sends a HART command request to a HART device and returns the response as array of byte.
   The interpretation of the response falls into the scope of user. 	 
		dwError: 
			16#00000301 => 'HART_INFO is not part of your project - Add HART_INFO program' 
			16#00000302 => 'Invalid param "bModule" x. Valid values between 1..64'
			16#00000303 => 'Invalid param "bChannel" y. Valid values between 1..2'
			16#00000305 => 'No HART sensor connected to module x on channel y'
			16#00000306 => 'Invalid parameter "bModule" points to a non HART module'
			16#08xxyyzz => 'Response codes from HART module (For details see HART spec )'
			16#0900xxyy => 'Response codes from HART sensor (HART specif.)'
*)

VAR_INPUT
	bModule  : BYTE;	(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bChannel : BYTE;	(* The channel of the I/O-Module where the HART device is connected (called Index DPV1). Valid values are 1 and 2. *)
	bHART_CMD: BYTE;	(* The HARD-Command *)
END_VAR
VAR_IN_OUT
	xStart 		: BOOL; 	(* A raising edge will start the execution of the HART command. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
	abData 		: ARRAY [0..gc_HARTBufferSize] OF BYTE; (* Additional request data and response data after execution *)
	bDataCount 	: BYTE; 	(* Number of additional request informations *)
END_VAR
VAR_OUTPUT
	dwError 	: DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	abRequest  : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	abResponse : ARRAY [0..gc_HARTBufferSize] OF BYTE;

	bCurrentIndex : BYTE; (* Index of HART module in g_atHARTModules *)

	oMailBox : HART_MBX; (* Mailbox client to transfer request/response via kbus to/from HART module *)
	xMailStart  : BOOL;
	dwMailError : DWORD;
	sMailStatus : STRING;
	iMailRespLen: INT;

	dwWarning: DWORD; (* Response code and CTRL analysis variables *)

	bComErrorCount : BYTE; (* Number of failed requests on communication error *)

	(* Little helpers *)
	i : INT;
END_VARY"  CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		dwError := 0;
		bComErrorCount := 0; (* Reset communication error counter *)
		sStatus:= 'RUNNING';
		bCurrentIndex := 0;
		wState := 3; (* Go Ahead *)
	END_IF

3:	(* Check for invalid input params "bModule" and "bChannel" *)
	IF (bModule >0 AND (bModule <= 64)) THEN
		IF (bChannel >0 AND (bChannel <= 2)) THEN
			wState := 4; (* Go Ahead *)
		ELSE
			dwError := 16#00000303;
			sStatus := CONCAT('Invalid param "bChannel" ', BYTE_TO_STRING(bChannel) );
			sStatus := CONCAT(sStatus, '. Valid values between 1..2');
			wState  := 999; (* Go Ahead *)
		END_IF
	ELSE
		dwError 	:= 16#00000302;
		sStatus := CONCAT('Invalid param "bModule" ', BYTE_TO_STRING(bModule) );
		sStatus := CONCAT(sStatus, '. Valid values between 1..64');
		wState  := 999; (* Go Ahead *)
	END_IF

4: (* Check if program HART_INFO has identified all HART modules *)
	CASE g_iHARTInfoState OF
	0: (* HART_INFO is not part of your project - Add HART_INFO program *)
		dwError 	:= 16#00000301;
		sStatus := 'HART_INFO is not part of your project - Add HART_INFO program';
		wState := 999; (* Go Ahead *)
	1: (* Identication of connected HART modules in progress - Just wait here *)
		sStatus := 'IDENTICATION OF HART MODULES IN PROGRESS';
	2: (* Identification successful finished *)
		wState := 5; (* Go Ahead *)
	END_CASE

5: (* Find index of HART module in g_atHARTModules *)
	FOR i := 1 TO gc_bHARTMaxModules(*8*) DO (* Scanjet *)
		IF g_atHARTModules[i].bModule = bModule THEN
			bCurrentIndex := INT_TO_BYTE(i);
			EXIT;
		END_IF
	END_FOR
	IF bCurrentIndex > 0 THEN
		wState := 10; (* Go Ahead *)
	ELSE
		dwError 	:= 16#00000306;
		sStatus := 'Invalid parameter "bModule" points to a non HART module';
		wState := 999; (* Go Ahead *)
	END_IF

10: (* Check if mailbox channel free or occupied by another instance of HART_CMDx *)
	IF g_atHARTModules[bCurrentIndex].bState = 0 THEN
		g_atHARTModules[bCurrentIndex].bState := 1; (* Occupie mailbox *)
		sStatus := 'START MAILBOX COMMUNICATION WITH HART MODULE';
		wState := 15; (* Go Ahead *)
	ELSE
		sStatus := 'MailBox occupied by another channel';
		(* Wait until communication channel is aviable *)
		(* TODO: Insert Timeout handling *)
	END_IF

15: (* Cleanup telegram buffer's *)
	FOR i:= 0 TO (SIZEOF(abRequest) - 1) DO
		abRequest[i] := 0;
		abResponse[i]:= 0;
	END_FOR;
	wState := 20;

20: (* "WRITE_DOWNLOAD_REQUEST" : Prepare DPV1-Telegram ... put HART request into PROFIBUS DP write request telegram*)
	abRequest[0]  := 16#5F; 			(* FC - Function code of profibus massege *)
	abRequest[1]  := bModule+1; 		(* SLOT - Slot sign the position of the hard device in the plc start with 2 *)
	CASE bChannel OF 					(* INDEX/Channel - Write index for HART on Profibus/ Channel of HART module *)
	1: abRequest[2]  := 16#91;
	2: abRequest[2]  := 16#D1;
	END_CASE
	abRequest[3]  := bDataCount + 11; 	(* LENGTH - Length of HART telegram message *)
	abRequest[4]  := 16#00; 			(* CTRL -  control*)
	abRequest[5]  := 16#00; 			(* XCTRL - extention control*)
	abRequest[6]  := 16#82; 			(* DELIM - *)
	abRequest[7]  := 16#80 OR (g_atHARTModules[bCurrentIndex].stCmd0[bChannel].bManufacturerId AND 16#3F);(* ADDRS - Manufactor_ID *)
	abRequest[8]  := g_atHARTModules[bCurrentIndex].stCmd0[bChannel].bTypeManufDevice;    	              (* ADDRS - Manufactor Device Type *)
	abRequest[9]  := DWORD_TO_BYTE(g_atHARTModules[bCurrentIndex].stCmd0[bChannel].dwDeviceId);		      (* ADDRS - DeviceId LL LSB   *)
	abRequest[10] := DWORD_TO_BYTE(SHR(g_atHARTModules[bCurrentIndex].stCmd0[bChannel].dwDeviceId,8));    (* ADDRS - DeviceId LH       *)
	abRequest[11] := DWORD_TO_BYTE(SHR(g_atHARTModules[bCurrentIndex].stCmd0[bChannel].dwDeviceId,16));   (* ADDRS - DeviceId HL       *)
	abRequest[12] := bHART_CMD; 		(* CMD - The HART-Command *)
	abRequest[13] := bDataCount; 		(* BYTECOUNT - length of additional hart request params *)
	IF bDataCount >= 1 THEN
		FOR i:=0 TO bDataCount -1 DO
			abRequest[14+i] := abData[i]; (* Copy additional params into request *)
		END_FOR
	END_IF
	abRequest[14+bDataCount] := 16#00; 	(* CRC - clear *)
	(* Calculate CRC *)
	FOR i:=4 TO 13+bDataCount DO
		abRequest[14+bDataCount] := abRequest[14+bDataCount] XOR abRequest[i]; (* CRC - XOR over HART telegram without LENGTH field *)
	END_FOR
	xMailStart := TRUE;
	wState := 30; (* Go Ahead *)

30:	(* call mailbox FB to transfer request via KBus to HART module *)
	oMailBox(wMbxInputOffset := g_atHARTModules[bCurrentIndex].wMbxInOffset,
			 wMbxOutputOffset:= g_atHARTModules[bCurrentIndex].wMbxOutOffset,
			 pabDpv1Request := ADR(abRequest),
			 iRequestLength := bDataCount +15, (* total length of HART request in bytes *)
			 pabDpv1Response := ADR(abResponse),
			 xStart := xMailStart,
			 dwError => dwMailError,
			 sStatus => sMailStatus,
			 iResponseLength => iMailRespLen );

	(* Wait until response received *)
	IF xMailStart = FALSE THEN
		(* Check for basic errors in Mailbox communication *)
		IF dwMailError = 0 THEN
			wState := 40; (* Ignore response data - Go Ahead *)
		ELSE
			dwError := dwMailError;
			sStatus := sMailStatus;
			wState := 999; (* Go Ahead *)
		END_IF
	END_IF

40: (* Cleanup telegram buffer's *)
	FOR i:= 0 TO (SIZEOF(abRequest) - 1) DO
		abRequest[i] := 0;
		abResponse[i] := 0;
	END_FOR;
	wState := 50; (* Go Ahead *)

50: (* "READ_DOWNLOAD_REQUEST" : Prepare DPV1-Telegram ... put HART request into PROFIBUS DP write request telegram*)
	abRequest[0]  := 16#5E; 			(* FC - Function code of profibus massege *)
	abRequest[1]  := bModule+1; 		(* SLOT - Slot sign the position of the hard device in the plc start with 2 *)
	CASE bChannel OF 					(* INDEX/Channel - Write index for HART on Profibus/ Channel of HART module *)
	1: abRequest[2]  := 16#92;
	2: abRequest[2]  := 16#D2;
	END_CASE
	abRequest[3]  := 16#00; 			(* LENGTH - Length of HART telegram message *)
	xMailStart := TRUE;
	wState := 60; (* Go Ahead *)

60:	(* call mailbox FB to transfer request via KBus to HART module *)
	oMailBox(wMbxInputOffset := g_atHARTModules[bCurrentIndex].wMbxInOffset,
			 wMbxOutputOffset:= g_atHARTModules[bCurrentIndex].wMbxOutOffset,
			 pabDpv1Request := ADR(abRequest),
			 iRequestLength := 4, (* CMD needs 4 bytes *)
			 pabDpv1Response := ADR(abResponse),
			 xStart := xMailStart,
			 dwError => dwMailError,
			 sStatus => sMailStatus,
			 iResponseLength => iMailRespLen );
	(* Wait until response received *)
	IF xMailStart = FALSE THEN
		(* Analyse and process response *)
		IF dwMailError = 0 THEN (* Check for basic errors *)
			wState := 70; (* Go Ahead *)
		ELSE
			dwError := dwMailError;
			sStatus := sMailStatus;
			wState := 999; (* Go Ahead *)
		END_IF
	END_IF

70: (* Check HART module response code *)
	HART_CheckModuleResponseCode(abResponse:= abResponse,
								 dwError => dwError,
								 dwWarning => dwWarning,
								 sStatus => sStatus);
	(* In case of error *)
	IF dwError > 0 THEN
		wState := 999; (* Go to error state *)
	ELSE
		(* In case of warning to
				- waiting pending
				- executing pending or
				- positive without data *)
		IF dwWarning > 0 THEN
			wState := 40; (* Try again *)
		ELSE (* In case of success *)
			wState := 80; (* Go Ahead *)
		END_IF
	END_IF

80:	(* Check response code from HART sensor *)
	HART_CheckSensorResponseCode(abResponse := abResponse,
								 dwError => dwError,
								 dwWarning => dwWarning,
								 sStatus => sStatus	);

	IF dwError = 0 THEN
		(* Success *)
		wState := 90; (* Go Ahead *)
	ELSE
		(* Check for communication errors *)
		IF (dwError AND 16#00000080) > 0 THEN
			bComErrorCount := bComErrorCount +1;
			IF bComErrorCount <= gc_bHARTRetries THEN
				wState := 15; (* Try again *)
				dwError := 0; (* Reset "dwError" in case of retransmission *)
			ELSE
				wState := 999; (* Go to error state *)
			END_IF
		ELSE
			wState := 999; (* Go to error state *)
		END_IF
	END_IF

90: (* Successfuly executed *)
	(* Process CMD Response *)
	bDataCount := INT_TO_BYTE(iMailRespLen -17);
	FOR i:=0 TO bDataCount DO
		abData[i] := abResponse[16+i];
	END_FOR
	dwError 	:= 0;
	IF dwWarning = 0 THEN
		(* No warnings from CTRL or HART response *)
		sStatus := 'Successfuly executed';
	END_IF
	(* Free resources every time *)
	xStart := FALSE;
	g_atHARTModules[bCurrentIndex].bState := 0; (* free mailbox *)
	wState := 0;

ELSE (* Auto Reset on Error ------------------------------------------------------*)
	xStart := FALSE;
	IF bCurrentIndex > 0 THEN
		g_atHARTModules[bCurrentIndex].bState := 0; (* free mailbox *)
	END_IF
	wState := 0; (* Go Ahead *)

END_CASE;

               �   , �  ��           HART_DATE2pab ��ST	��ST      ��������        D  FUNCTION HART_DATE2pab : DWORD
(* Function converts date to ARRAY [0..2] OF BYTE *)
VAR_INPUT
	dDate : DATE;
	pabIn : POINTER TO ARRAY [0..3] OF BYTE;
END_VAR
VAR
	sHelp : STRING(32);
	pabHelp: POINTER TO ARRAY [0..32] OF BYTE;
	wYear : WORD := 0;
	wMonth : WORD := 0;
	wDay : WORD := 0;

	i: INT := 0;
END_VARZ  (* Convert the date to string *)
sHelp := DATE_TO_STRING(dDate);
pabHelp := ADR(sHelp);

(* Parse the date from the string *)
FOR i:= 0 TO 20 DO
	(* Find '#' char in date string *)
	(* Note: ('#' in ascii == 35) *)
	IF (pabHelp^[i]) = 35 THEN
		(* Derive numbers from d#yyyy-mm-dd or
			dt#yyyy-mm-dd-hh-mm-ss notation *)
		(* Note: ('0' in ascii == 48) *)
		wYear := 1000*((pabHelp^[i+1])-48) +
			100*((pabHelp^[i+2])-48) +
			10*((pabHelp^[i+3])-48) +
			1*((pabHelp^[i+4])-48);
		wMonth := 10*(pabHelp^[i+6]-48) +
			1*(pabHelp^[i+7]-48);
		wDay := 10*(pabHelp^[i+9]-48) +
			1*(pabHelp^[i+10]-48);
		(* Jump from FOR *)
		i := 21;
	END_IF
END_FOR

(* Convert Codesys date to HART date *)
wYear := wYear - 1900;

(*  *)
pabIn^[2] := WORD_TO_BYTE(wYear);
pabIn^[1] := WORD_TO_BYTE(wMonth);
pabIn^[0] := WORD_TO_BYTE(wDay);
               W   ,   � ��           HART_FDT ��ST	��ST      ��������           PROGRAM HART_FDT
(* This program work as gateway for wago841-HART-FDT-DTM.
It waits for DPV1-Request over Modbus_TCP in PFC-IN-Area at %IW256.
The DPV1-Response will be written to PFC-OUT-Area at %QW256.
Take care for dont using this Memory area in your application.
If an error occours the program performs a auto reset after the given tTimeout.
*)
VAR_INPUT
	tTimeOut : TIME:= t#45s; (* Watchdog Timeout *)
END_VAR
VAR_IN_OUT

END_VAR
VAR_OUTPUT
	bMsgId : BYTE; 	(* Id of actual processed message from FDT-DTM *)
	dwError : DWORD;
	sStatus : STRING;
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	(* WatchDog *)
	oTON		: TON;		(* Watchdogtimer for statemashine *)
	xWatchDog	: BOOL; 	(* Enable or disable Watchdog for statemashine *)
	wStateOld	: WORD;		(* Persist the last state of statemashine *)
	xReset 		: BOOL; 	(* Performs a auto reset if timeout elapsed *)

	bModule : BYTE; 		(* Index of plugged HART module start with one - DPV1-Slot number start with 2 *)
	bCurrentIndex : BYTE; 	(* Index of HART module in g_atHARTModules *)

	stDpv1Request AT %IW256: tHART_FDT;
	stDpv1Response AT %QW256: tHART_FDT;

	abRequest  : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bRequestLength : BYTE;
	abResponse : ARRAY [0..gc_HARTBufferSize] OF BYTE;
	bResponseLength : BYTE;

	oMailBox : HART_MBX; (* Mailbox client to transfer request/response via kbus to/from HART module *)
	xMailStart  : BOOL;
	xMailReset  : BOOL;
	dwMailError  : DWORD;
	sMailStatus : STRING;
	iMailRespLen: INT;

	(* Little helpers *)
	i : INT;
END_VAR/  CASE wState OF
0: (* IDLE - wait for something to do *)
	bMsgId := stDpv1Request.bMsgNumber; (* Only used to show progress of program *)
	IF stDpv1Request.bMsgNumber <>	stDpv1Response.bMsgNumber THEN
		dwError := 0;
		sStatus:= 'RUNNING';
		xReset := FALSE;
		(* Cleanup telegram buffer's *)
		FOR i:= 0 TO (SIZEOF(abRequest) - 1) DO
			abRequest[i] := 0;
			abResponse[i]:= 0;
		END_FOR;
		bCurrentIndex := 0;
		wState := 2; (* Go Ahead *)
	END_IF

2: (* Identify Slotnumber and channel *)
	bModule := stDpv1Request.abDpv1Telegram[1]-1;
	wState := 3; (* Go Ahead *)

3: (* Check for invalid input params "bModule" *)
	IF (bModule >0 AND (bModule <= 64)) THEN
		wState := 4; (* Go Ahead *)
	ELSE
		dwError 	:= 16#0302;
		sStatus := CONCAT('Invalid param "bModule" ', BYTE_TO_STRING(bModule) );
		sStatus := CONCAT(sStatus, '. Valid values between 1..64');
		wState  := 999; (* Go Ahead *)
	END_IF

4: (* Check if program HART_INFO has identified all HART modules *)
	CASE g_iHARTInfoState OF
	0: (* HART_INFO is not part of your project - Add HART_INFO program *)
		dwError 	:= 16#0301;
		sStatus := 'HART_INFO is not part of your project - Add HART_INFO program';
		wState := 999; (* Go Ahead *)
	1: (* Identication of connected HART modules in progress - just wait *)
		sStatus := 'IDENTICATION OF HART MODULES IN PROGRESS';
	2: (* Identification successful finished *)
		wState := 5; (* Go Ahead *)
	END_CASE

5: (* Find index of HART module in g_atHARTModules *)
	FOR i := 1 TO gc_bHARTMaxModules(*8*) DO (* Scanjet *)
		IF g_atHARTModules[i].bModule = bModule THEN
			bCurrentIndex := INT_TO_BYTE(i);
			EXIT;
		END_IF
	END_FOR
	IF bCurrentIndex > 0 THEN
		wState := 8; (* Go Ahead *)
	ELSE
		dwError 	:= 16#0306;
		sStatus := 'Invalid parameter "bModule" points to a non HART module';
		wState := 999; (* Go Ahead *)
	END_IF

8: (* Check if mailbox channel free or occupied by another instance of HART_CMDx *)
	IF g_atHARTModules[bCurrentIndex].bState = 0 THEN
		g_atHARTModules[bCurrentIndex].bState := 1; (* Occupie mailbox *)
		sStatus := 'Execute FDT job';
		wState := 10; (* Go Ahead *)
	ELSE
		sStatus := 'MailBox occupied by another channel';
		(* Wait until communication channel is aviable *)
		(* TODO: Insert Timeout handling *)
	END_IF

10: (* "WRITE_DOWNLOAD_REQUEST" CMD: Prepare DPV1-Telegram ... put HART request into PROFIBUS DP write request telegram*)
	bRequestLength := stDpv1Request.abDpv1Telegram[3] + 4; (* LengthField + DPV1-Header(3Byte) *)
	FOR i:=0 TO bRequestLength DO
		abRequest[i] :=stDpv1Request.abDpv1Telegram[i];
	END_FOR
	xMailStart := TRUE;
	wState := 20; (* Go Ahead *)

20: (* call mailbox FB to transfer request via KBus to HART module *)
	oMailBox(wMbxInputOffset := g_atHARTModules[bCurrentIndex].wMbxInOffset,
			 wMbxOutputOffset:= g_atHARTModules[bCurrentIndex].wMbxOutOffset,
			 pabDpv1Request := ADR(abRequest),
			 iRequestLength := BYTE_TO_INT(bRequestLength),
			 pabDpv1Response := ADR(abResponse),
			 xStart := xMailStart,
			 dwError => dwMailError,
			 sStatus => sMailStatus,
			 iResponseLength => iMailRespLen );
	(* Wait until response received *)
	IF xMailStart = FALSE THEN
		(* Analyse and process response *)
		IF dwMailError = 0 THEN (* Check for basic errors *)
			(* Check field "Index/Channel" of DPV1-Request *)
			CASE stDpv1Request.abDpv1Telegram[2] OF
			16#80,16#90,16#C0,16#D0 : (* Direct response, without pending for index 80,90,C0,D0  *)
				wState := 80; (* Go Ahead *)
			ELSE
				(* Pending operation need time *)
				wState := 40; (* Go Ahead *)
			END_CASE
		ELSE
			dwError := dwMailError;
			sStatus := sMailStatus;
			wState := 999; (* Go Error *)
		END_IF
	END_IF

40: (* Cleanup telegram buffer's *)
	FOR i:= 0 TO (SIZEOF(abRequest) - 1) DO
		abRequest[i] := 0;
		abResponse[i] := 0;
	END_FOR;
	wState := 50; (* Go Ahead *)

50: (* "READ_DOWNLOAD_REQUEST"  Prepare DPV1-Telegram ... put HART request into PROFIBUS DP write request telegram*)
	abRequest[0]  := 16#5E; 							(* FC - Function code of profibus massege *)
	abRequest[1]  := bModule+1; 						(* SLOT - Slot sign the position of the hard device in the plc start with 2 *)
	abRequest[2]  := stDpv1Request.abDpv1Telegram[2]+1;	(* INDEX/Channel - Write index for HART on Profibus/ Channel of HART module *)
	abRequest[3]  := 16#00; 							(* LENGTH - Length of HART telegram message *)
	xMailStart := TRUE;
	wState := 60; (* Go Ahead *)

60:	(* call mailbox FB to transfer request via KBus to HART module *)
	oMailBox(wMbxInputOffset := g_atHARTModules[bCurrentIndex].wMbxInOffset,
			 wMbxOutputOffset:= g_atHARTModules[bCurrentIndex].wMbxOutOffset,
			 pabDpv1Request := ADR(abRequest),
			 iRequestLength := 4, (* CMD needs 4 bytes *)
			 pabDpv1Response := ADR(abResponse),
			 xStart := xMailStart,
			 dwError => dwMailError,
			 sStatus => sMailStatus,
			 iResponseLength => iMailRespLen );
	(* Wait until response received *)
	IF xMailStart = FALSE THEN
		(* Analyse and process response *)
		IF dwMailError = 0 THEN (* Check for basic errors *)
			wState := 70; (* Go Ahead *)
		ELSE
			dwError 	:= dwMailError;
			sStatus := sMailStatus;
			wState := 999; (* Go Ahead *)
		END_IF
	END_IF

70: (* Check for pending HART operation *)
	IF (abResponse[4] = 16#02 OR abResponse[4] = 16#03 OR abResponse[4] = 16#05) THEN
		(* Try again *)
		wState := 40;
		sStatus := 'Pending operation';
	ELSE
		(* Data received *)
		wState := 80;
	END_IF

80:	(* copy CMD response into PFC-OUT memory *)
	FOR i:=0 TO iMailRespLen DO
		stDpv1Response.abDpv1Telegram[i] := abResponse[i];
	END_FOR
	dwError := 0;
	sStatus := 'Succesful executed';
	(* Free resources every time *)
	g_atHARTModules[bCurrentIndex].bState := 0; (* free mailbox *)
	(* Indicate job as done for FDT-DTM *)
	stDpv1Response.bMsgNumber := stDpv1Request.bMsgNumber;
	wState := 0;


ELSE (* ------------------------------------------------------*)
	(* The Error State - Wait for xReset to start over *)
	IF xReset THEN
		(* Free resources every time *)
		g_atHARTModules[bCurrentIndex].bState := 0; (* free mailbox *)
		(* Indicate job as done for FDT-DTM *)
		stDpv1Response.bMsgNumber := stDpv1Request.bMsgNumber;
		sStatus := 'IDLE';
		xReset := FALSE;

		wState := 0; (* Go Ahead *)
	END_IF
END_CASE;

(* Watchdog for statemachine  *)
IF oTON.Q THEN
	xWatchDog := FALSE;
	sStatus:='ERROR: TIMEOUT - automatic restart follows';
	dwError := 16#0500; 	(* Watchdog time elapsed, see sStatus for details *)
	wState := 999;
	IF dwMailError <> 0 THEN
		xMailStart := FALSE;
		xMailReset := TRUE;
	END_IF
	xReset := TRUE;
END_IF

IF (wState > 0) THEN
	oTON(IN:=xWatchDog , PT:=tTimeOut);
	IF (wStateOld <> wState) THEN
		xWatchDog := FALSE; (* Step has changed *)
	ELSE
		xWatchDog := TRUE; (* Step still active *)
	END_IF
END_IF
wStateOld := wState;
               /   , ��m hv        	   HART_INFO ��ST	��ST      ��������        i  PROGRAM HART_INFO
(* 	This program  identifies all connected HART-modules and coordinate the MailBox communication.
	The current config and state of each HART module is stored in "g_atHARTModules" in VAR GLOBAL's.
	g_atHARTModules : ARRAY [1..8] OF tHART_2AI; (* Global List of HART modules - keep current config and state *) 

	dwError:
		16#00000001 - 'ERROR: No HART modules found';
		16#00000002 - 'ERROR: Number of HART modules exceed the maximum of 8 modules';
		16#00000003 - 'ERROR: HART module number x do not operate in mode 8(Change mode with IOCheck)';
*)

VAR_INPUT
	xStart : BOOL; (* Set program  active *)
END_VAR
VAR_IN_OUT
	xReset : BOOL; (* *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
END_VAR

VAR
	(* Statemashine *)
	wState : WORD;
	bCount : BYTE;	(* Number of found HART modules 750-482 *)

	(* mod_com - needed to find HART modules in process image *)
	stMIA 	: MODULE_INFO_ACCESS;
	astMI : ARRAY[0..63] OF MODULE_INFO;
	oReadPAE : READ_INPUT_WORD; 	(* Functionblock from mod_com.lib to read from input process image *)
	bStatusByte: BYTE; (* Used to check status byte of HART module for shor circuit and open loop *)
	xModComError : BOOL; (* Indicates the result of READ_INPUT_WORD and WRITE_OUTPUT_WORD *)

	(* HART_CMD0 - needed to obtain the long HART address (DeviceId) *)
	oCmd0 : HART_CMD0;
	xCmd0Start  : BOOL;
	dwCmd0Error : DWORD;
	sCmd0Status : STRING;
	stCmd0Data	: tHART_CMD0;

	(* Little helpers *)
	bActModule 	: BYTE; (* Used to iterate all modules/Channels *)
	bActChannel : BYTE; (* Used to iterate all modules/Channels *)
	i: INT;

END_VAR  CASE wState OF
0: (* IDLE - wait for something to do *)
	sStatus:= 'IDLE';
	IF xStart THEN
		HART_UnitCodeStrings();
		g_iHARTInfoState := 1; (* Indicates that identication is in progress *)
		dwError := 0;
		xReset := FALSE;
		wState := 5; (* Go Ahead *)
	END_IF

5: (* Clear list of HART modules "g_atHARTModules" *)
	sStatus:= 'CLEAR';
	bCount := 0;
	FOR i := 1 TO gc_bHARTMaxModules(*8*) DO (* Scanjet *)
		g_atHARTModules[i].bModule :=  0; (* Indicates that there is no HART module aviable *)
		g_atHARTModules[i].bState := 0; (* Idle *)
	END_FOR
	bActModule 	:= 0;
	bActChannel := 0;
	wState := 10; (* Go Ahead *)

10: (* Find the max 8 HART modules *)
	sStatus:= 'FIND';
	ADD_PI_INFORMATION( 1, ADR(stMIA), ADR(astMI[0]) );
	i := 0;
	FOR i := 0 TO 63 DO
		(* Is module a 750-482 or 750-484 ? *)
		IF astMI[i].moduleType = 482 OR astMI[i].moduleType = 484 THEN
			(* Increment module counter *)
			bCount := bCount +1;
			(* Calculate Slot number *)
			g_atHARTModules[bCount].bModule := INT_TO_BYTE(i+1);
			(* calculate byteoffset of mailbox in process image *)
			g_atHARTModules[bCount].wMbxInOffset 	:= (astMI[i].desc.posPAE /16) +1;
			g_atHARTModules[bCount].wMbxOutOffset 	:= (astMI[i].desc.posPAA /16) +1;
			(* Check if HART module working in mode 8 (12Byte) *)
			IF NOT( (astMI[i].desc.sizePAA = 16#60) OR (astMI[i].desc.sizePAA = 16#8C) )THEN (* V3.3/25.02.09/CM *)
				dwError := 16#00000003;
				sStatus:= CONCAT('ERROR: HART module number ', INT_TO_STRING(i +1));
				sStatus:= CONCAT(sStatus, 'do not operate in mode 8(Change mode with IOCheck)');
				wState := 999;
				RETURN;
			END_IF
		END_IF
		(* Check number of HART modules *)
		IF bCount > gc_bHARTMaxModules THEN
			dwError := 16#00000002;
			sStatus:= 'ERROR: Number of HART modules exceed the maximum ';
			wState := 999;
			RETURN;
		END_IF
	END_FOR
	IF bCount = 0 THEN
		dwError := 16#00000001;
		sStatus:= 'ERROR: No HART modules found';
		wState := 999;
	ELSE
		bActModule := 1; (* Start with first HART module *)
		bActChannel := 1; (* Start with the first channel of HART module *)
		wState := 20; (* Go Ahead *)
	END_IF

20: (* Iterate each Channel for all modules to collect the HART-DeviceId *)
	IF bActChannel > 2 THEN
		bActModule := bActModule +1;
		bActChannel := 1;
	END_IF
	IF bActModule <= bCount THEN
		sStatus:= CONCAT( 'IDENTIFY Module ', BYTE_TO_STRING(bActModule) );
		sStatus:= CONCAT( sStatus, ' Channel ');
		sStatus:= CONCAT( sStatus, BYTE_TO_STRING(bActChannel) );
		xCmd0Start := TRUE;
		wState := 30; (* Go Ahead *)
	ELSE
		(* Job is done - nothing else to do *)
		sStatus:= 'OPERATIONAL';
		g_iHARTInfoState := 2; (* Indicates that identication of HART modules have been finished *)
		wState := 999; 		   (* Go and wait for xReset to start over *)
	END_IF

30: (* Identify the long HART addresses(DeviceId) of one connected HART device with HART_CMD0 *)
	oCmd0(	bModule	:= g_atHARTModules[bActModule].bModule,  (* First HART module start with 1 - PBDPV1 Slot start with 2 *)
			bChannel:= bActChannel,
			xStart	:= xCmd0Start,
			dwError	=> dwCmd0Error,
			sStatus	=> sCmd0Status,
			stData	=> stCmd0Data);
	(* Wait for response *)
	IF xCmd0Start = FALSE THEN
		IF dwCmd0Error = 0 THEN
			(* Take data *)
			g_atHARTModules[bActModule].stCmd0[bActChannel] := stCmd0Data;
			wState := 40; (* Go Ahead *)
		ELSE
			(* Do nothing so ignore all errors *)
			(* dwError := dwCmd0Error; *)
			sStatus:= CONCAT('M',BYTE_TO_STRING(bActModule));
			sStatus:= CONCAT(sStatus,'Ch');
			sStatus:= CONCAT(sStatus,BYTE_TO_STRING(bActChannel));
			sStatus:= CONCAT(sStatus,', ');
			sStatus:= CONCAT(sStatus, sCmd0Status);
			wState := 40; (* Go Ahead *)
		END_IF
	END_IF

40: (* Analyse next channel *)
	bActChannel := bActChannel +1; (* Analyse next channel *)
	wState := 20; (* Go Ahead *)

ELSE(* ------------------------------------------------------*)
	(* Wait for xReset to start over *)
	IF xReset THEN
		xReset := FALSE;
		wState := 0; (* Go Ahead *)
	END_IF;
END_CASE


               G   , F  �l           HART_MBX ��ST	��ST      ��������        
  FUNCTION_BLOCK HART_MBX
(* Functionblock sendet ein DPV1-Telegramm �ber die Mailbox der HART-Klemme 750-482 oder 750-484
		dwError:
		 	16#00000201 => 'ERROR: Mailbox - CRC Check failed for uploaded data from HART module' 
			16#00000205 => 'ERROR: WatchDog - No progress, maximum steptime elapsed'
			16#0000xxyy => mailbox specific errorcode where xx=>OpCode and yy=>Reason *)
VAR_INPUT
	wMbxInputOffset : WORD; (* Physical startaddress of mailbox in input process image *)
	wMbxOutputOffset: WORD; (* Physical startaddress of mailbox in output process image *)
	pabDpv1Request 	: POINTER TO ARRAY [0..gc_HARTBufferSize] OF BYTE;
	iRequestLength 	: INT; (* Length of request telegram *)
	pabDpv1Response : POINTER TO ARRAY [0..gc_HARTBufferSize] OF BYTE;
END_VAR
VAR_IN_OUT
	xStart : BOOL; 		(* A raising edge will start the execution. When finished or after a timeout xStart is set to false - Check wError on the falling edge of xStart *)
END_VAR
VAR_OUTPUT
	dwError : DWORD;
	sStatus : STRING;
	iResponseLength : INT; (* Length of response telegram *)
END_VAR
VAR
	wState : WORD; (* Statemashine *)

	abMbxPAE  : ARRAY [0..5] OF BYTE; (* Input data of HART Mailbox *)
	abMbxPAA  : ARRAY [0..5] OF BYTE; (* Output data of HART Mailbox *)

	pawMbxPAE : POINTER TO ARRAY [0..2] OF WORD; (* Input data of HART Mailbox - readed by modcom*)
	pawMbxPAA : POINTER TO ARRAY [0..2] OF WORD; (* Output data of HART Mailbox - written by modcom*)

	oReadPAE : READ_INPUT_WORD; 	(* Functionblock from mod_com.lib to read from input process image *)
	oWritePAA: WRITE_OUTPUT_WORD; 	(* Functionblock from mod_com.lib to write into output process image *)
	oReadPAA: READ_OUTPUT_WORD; 	(* Functionblock from mod_com.lib to read from output process image *)
	xModComError : BOOL; (* Indicates the result of READ_INPUT_WORD and WRITE_OUTPUT_WORD *)
	xModComWrite : BOOL; (* Indicates that data have to be written to process image *)
	wReadPAA: WORD; (* Used read back current state of togglebit *)

	bMbxSt	: BYTE; 	(* MbxStatusByte (Togglebit ist MSB: 0x00 or 0x80) *)
	bMbxRet : BYTE;		(* MbxReturnValue (Indicate succes or failure of down/up-load *)
	dwMbxCrc: DWORD; 	(* Checksum for mailbox communication as sum of all bytes *)
	dwMbxCrcCalc : DWORD; 	(* Checksum for mailbox communication as sum of all bytes *)

	bWriteIndex: BYTE; 	(* Index of actual read position in 'pabDpv1Request' *)
	bReadIndex : BYTE;  (* Index of actual write position in 'pabDpv1Response' *)
	i : INT;

	oWatchdogTimer : TON;
	wState_old : WORD;

END_VAR6(  (* Assign pointer befor use *)
pawMbxPAE := ADR(abMbxPAE);
pawMbxPAA := ADR(abMbxPAA);
(* Read input process image *)
oReadPAE(WORD_ADDRESS:= wMbxInputOffset,
		 VALUE=> pawMbxPAE^[0],
		 ERROR=> xModComError);
oReadPAE(WORD_ADDRESS:= wMbxInputOffset +1,
		 VALUE=> pawMbxPAE^[1],
		 ERROR=> xModComError);
oReadPAE(WORD_ADDRESS:= wMbxInputOffset +2,
		 VALUE=> pawMbxPAE^[2],
		 ERROR=> xModComError);
(* Read back output process image *)
oReadPAA(WORD_ADDRESS:= wMbxOutputOffset,
		 VALUE=> wReadPAA,
		 ERROR=> xModComError);

CASE wState OF
0: (* IDLE - wait for something to do *)
	IF xStart THEN
		dwError := 0;
		sStatus:= 'RUNNING';
		wState := 10; (* Go Ahead *)
	END_IF

10:	(* MBX DLD_START *)
	bWriteIndex := 0; 						(* Set write index on top of request telegram *)
	bMbxSt := abMbxPAE[1];					(* MbxStatusByte: save current state of togglebit , needed to detect changes *)
	abMbxPAA[0] := 16#41;											(*MBX Byte0: Opcode: 41= DLD_START*)
	abMbxPAA[1] := WORD_TO_BYTE(SHR(wReadPAA, 8)) XOR 16#80;		(*MBX Byte1: MbxControlByte (Togglebit ist MSB: 0x00 or 0x80) *)
	abMbxPAA[2] := 0;												(*MBX Byte2: "TableType" -> 0 reserved *)
	abMbxPAA[3] := 16#FE;											(*MBX Byte3: "Transfer Type" -> Byte Array ->16#FE == 254 *)
	abMbxPAA[4] := INT_TO_BYTE(iRequestLength);						(*MBX Byte4: Anzahl Daten LSB *)
	abMbxPAA[5] := 2#10000000;										(*MBX Byte5: Bit 6..7 = 2 Download *)
	(* Write to output process image *)
	xModComWrite := TRUE;
	wState := 20; (* Go Ahead *)

20: (* DLD_CONT: Mailbox continue download  *)
	(* Check if response received, indicated by togglebit in MbxStatusByte *)
	IF ((abMbxPAE[1] AND 16#80) <> (bMbxSt AND 16#80)) THEN
		bMbxSt 	:= abMbxPAE[1]; 				(* MbxStatusByte: save current state of togglebit , needed to detect changes *)
		bMbxRet := abMbxPAE[1] AND 16#7F;		(* MbxReturnValue (Indicate succes or failure of down/up-load *)
		IF (abMbxPAE[0] = abMbxPAA[0]) AND (bMbxRet = 0) THEN  (* Commando has been executed successful *)
			IF (iRequestLength - bWriteIndex) > 0 THEN
				(* More data *)
				abMbxPAA[0] := 16#42;									(* MBX Byte0: Opcode: 42= DLD_CONT*)
				abMbxPAA[1] := WORD_TO_BYTE(SHR(wReadPAA, 8)) XOR 16#80;(* MBX Byte1: Togglebit *)
				abMbxPAA[2] := pabDpv1Request^[bWriteIndex +0];			(* MBX Byte2: Request data *)
				abMbxPAA[3] := pabDpv1Request^[bWriteIndex +1];			(* MBX Byte3: Request data *)
				abMbxPAA[4] := pabDpv1Request^[bWriteIndex +2];			(* MBX Byte4: Request data *)
				abMbxPAA[5] := pabDpv1Request^[bWriteIndex +3];			(* MBX Byte5: Request data *)
				bWriteIndex := bWriteIndex +4;
			ELSE
				(* Download end *)
				abMbxPAA[0] := 16#43;									(* MBX Byte0: Opcode: 43= DLD_END*)
				abMbxPAA[1] := WORD_TO_BYTE(SHR(wReadPAA, 8)) XOR 16#80;(* MBX Byte1: Togglebit *)
				dwMbxCrc :=0;
				FOR i:=0 TO iRequestLength +1 DO
					dwMbxCrc := dwMbxCrc + pabDpv1Request^[i];
				END_FOR
				abMbxPAA[2] := DWORD_TO_BYTE(dwMbxCrc);					(* MBX Byte2: Request data - CRC *)
				abMbxPAA[3] := DWORD_TO_BYTE(SHR(dwMbxCrc,8));			(* MBX Byte3: Request data - CRC *)
				abMbxPAA[4] := DWORD_TO_BYTE(SHR(dwMbxCrc,16));			(* MBX Byte4: Request data - CRC *)
				abMbxPAA[5] := DWORD_TO_BYTE(SHR(dwMbxCrc,24));			(* MBX Byte5: Request data - CRC *)
				wState:=30;
			END_IF
			(* Write to output process image *)
			xModComWrite := TRUE;
		ELSE
			dwError  := (256*abMbxPAE[0]) + bMbxRet; (* 16#xxyy => mailbox specific errorcode xx=>OpCode, yy=>Reason *)
			sStatus := 'ERROR: Mailbox - Download to HART module failed';
			wState  := 999; (* Go Ahead *)
		END_IF
	END_IF

30:	(* Wait for MBX Download end and start upload *)
	IF ((abMbxPAE[1] AND 16#80) <> (bMbxSt AND 16#80)) THEN
		bMbxSt 	:= abMbxPAE[1]; 				(* MbxStatusByte: save current state of togglebit , needed to detect changes *)
		bMbxRet := abMbxPAE[1] AND 16#7F;		(* MbxReturnValue (Indicate succes or failure of down/up-load *)
		IF  ((abMbxPAE[0] = 16#43) AND (bMbxRet = 0)) THEN  (* Command has been executed successful *)
			bReadIndex := 0; (* Set write index on top of response telegram *)
			(* DLD_START: start upload *)
			abMbxPAA[0] := 16#41;									(* MBX Byte0: Opcode: 41= DLD_START*)
			abMbxPAA[1] := WORD_TO_BYTE(SHR(wReadPAA, 8)) XOR 16#80;(* MBX Byte1: Togglebit *)
			abMbxPAA[2] := 16#00;									(* MBX Byte2: reserved*)
			abMbxPAA[3] := 16#FE;									(* MBX Byte3: Datatype "Byte Array" *)
			abMbxPAA[4] := 16#00;									(* MBX Byte4: don't care, length is in the response *)
			abMbxPAA[5] := 2#11000000;								(* MBX Byte5: Bit 6..7 = 3 Upload *)
			(* Write to output process image *)
			xModComWrite := TRUE;
			wState := 40; (* Go Ahead *)
		ELSE
			dwError  := (256*abMbxPAE[0]) + bMbxRet; (* 16#xxyy => mailbox specific errorcode xx=>OpCode, yy=>Reason *)
			sStatus := 'ERROR: Mailbox - Download to HART module failed';
			wState  := 999; (* Go Ahead *)
		END_IF
	END_IF

40: (* MBX Upload DLD_CONT *)
	IF ((abMbxPAE[1] AND 16#80) <> (bMbxSt AND 16#80)) THEN
		bMbxSt 	:= abMbxPAE[1]; 				(* MbxStatusByte: save current state of togglebit , needed to detect changes *)
		bMbxRet := abMbxPAE[1] AND 16#7F;		(* MbxReturnValue (Indicate succes or failure of down/up-load *)
		IF  ((abMbxPAE[0] = abMbxPAA[0]) AND (bMbxRet = 0)) THEN  (* Commando has been executed successful *)
			iResponseLength := BYTE_TO_INT(abMbxPAE[4]);	(*Anzahl Daten HART Response *)
			abMbxPAA[0] := 16#42;									(* MBX Byte0: Opcode: 42= DLD_CONT*)
			abMbxPAA[1] := WORD_TO_BYTE(SHR(wReadPAA, 8)) XOR 16#80;(* MBX Byte1: Togglebit *)
			abMbxPAA[2] := 0;										(* MBX Byte2: dummy value *)
			abMbxPAA[3] := 0;										(* MBX Byte3: dummy value *)
			abMbxPAA[4] := 0;										(* MBX Byte4: dummy value *)
			abMbxPAA[5] := 0;										(* MBX Byte5: dummy value *)
			(* Write to output process image *)
			xModComWrite := TRUE;
			wState:=50;
		ELSE
			dwError  := (256*abMbxPAE[0]) + bMbxRet; (* 16#xxyy => mailbox specific errorcode xx=>OpCode, yy=>Reason *)
			sStatus := 'ERROR: Mailbox - Upload from HART module failed';
			wState  := 999; (* Go Ahead *)
		END_IF
	END_IF

50: (*Read data from table and copy to application area*)
	IF ((abMbxPAE[1] AND 16#80) <> (bMbxSt AND 16#80)) THEN
		bMbxSt 	:= abMbxPAE[1]; 				(* MbxStatusByte: save current state of togglebit , needed to detect changes *)
		bMbxRet := abMbxPAE[1] AND 16#7F;		(* MbxReturnValue (Indicate succes or failure of down/up-load *)
		IF  ((abMbxPAE[0] = abMbxPAA[0]) AND (bMbxRet = 0)) THEN  (* Commando has been executed successful *)
			(* Copy received data into response telegram *)
			pabDpv1Response^[bReadIndex +0] :=abMbxPAE[2];
			pabDpv1Response^[bReadIndex +1] :=abMbxPAE[3];
			pabDpv1Response^[bReadIndex +2] :=abMbxPAE[4];
			pabDpv1Response^[bReadIndex +3] :=abMbxPAE[5];
			bReadIndex := bReadIndex +4;
			IF bReadIndex < iResponseLength THEN
				(* More data to upload *)
				abMbxPAA[0] := 16#42;									(* MBX Byte0: Opcode: 42= DLD_CONT *)
			ELSE
				(* All data received *)
				abMbxPAA[0] := 16#43;									(* MBX Byte0: Opcode: 43= DLD_END *)
				wState := 60; (* Go Ahead *)
			END_IF
			abMbxPAA[1] := WORD_TO_BYTE(SHR(wReadPAA, 8)) XOR 16#80;	(* MBX Byte1: Togglebit *)
			abMbxPAA[2] := 0;											(* MBX Byte2: dummy value *)
			abMbxPAA[3] := 0;											(* MBX Byte3: dummy value *)
			abMbxPAA[4] := 0;											(* MBX Byte4: dummy value *)
			abMbxPAA[5] := 0;											(* MBX Byte5: dummy value *)
			(* Write to output process image *)
			xModComWrite := TRUE;
		ELSE
			dwError  := (256*abMbxPAE[0]) + bMbxRet; (* 16#xxyy => mailbox specific errorcode xx=>OpCode, yy=>Reason *)
			sStatus := 'ERROR: Mailbox - Upload from HART module failed';
			wState  := 999; (* Go Ahead *)
		END_IF
	END_IF

60: (* Wait for MBX Upload end *)
	IF ((abMbxPAE[1] AND 16#80) <> (bMbxSt AND 16#80)) THEN
		bMbxSt 	:= abMbxPAE[1]; 			(* MbxStatusByte: save current state of togglebit , needed to detect changes *)
		bMbxRet := abMbxPAE[1] AND 16#7F;	(* MbxReturnValue (Indicate succes or failure of down/up-load *)
		IF  ((abMbxPAE[0] = 16#43) AND (bMbxRet = 0)) THEN  (* Commando has been executed successful *)
			(* Retrieve transmitted CRC *)
			dwMbxCrc := 	  BYTE_TO_DWORD(abMbxPAE[2])
						+ SHL(BYTE_TO_DWORD(abMbxPAE[3]),8)
						+ SHL(BYTE_TO_DWORD(abMbxPAE[4]),16)
						+ SHL(BYTE_TO_DWORD(abMbxPAE[5]),24);
			(* Calculate CRC *)
			dwMbxCrcCalc := 0;
			FOR i:=0 TO iResponseLength DO
				dwMbxCrcCalc := dwMbxCrcCalc + pabDpv1Response^[i];
			END_FOR
			(* Check calculated against received CRC *)
			IF dwMbxCrc = dwMbxCrcCalc THEN
				xStart := FALSE;
				sStatus := 'Job successful executed';
				wState  := 0; (* Go Ahead *)
			ELSE
				dwError  := 16#0201;
				sStatus := 'ERROR: Mailbox - CRC Check failed for uploaded data from HART module';
				wState  := 999; (* Go Ahead *)
			END_IF
		ELSE
			dwError  := (256*abMbxPAE[0]) + bMbxRet; (* 16#xxyy => mailbox specific errorcode xx=>OpCode, yy=>Reason *)
			sStatus := 'ERROR: Mailbox - Upload from HART module failed';
			wState  := 999; (* Go Ahead *)
		END_IF
	END_IF

ELSE (* ------------------------------------------------------*)
	(* The Error State - Auto reset to start over *)
	xStart := FALSE;
	wState := 0; (* Go Ahead *)
END_CASE

(* Write to process image  ------------------------------------------------- *)
IF xModComWrite THEN
	xModComWrite := FALSE;
	(* Write now *)
	oWritePAA(WORD_ADDRESS:= wMbxOutputOffset +2,
			  VALUE:= pawMbxPAA^[2],
			  ERROR=> xModComError);
	oWritePAA(WORD_ADDRESS:= wMbxOutputOffset +1,
			  VALUE:= pawMbxPAA^[1],
			  ERROR=> xModComError);
	oWritePAA(WORD_ADDRESS:= wMbxOutputOffset,
			  VALUE:= pawMbxPAA^[0],
			  ERROR=> xModComError);
END_IF

(* Watchdog ------------------------------------------------- *)
IF wState <> wState_old THEN
	wState_old:=wState;
	oWatchdogTimer(IN:=FALSE );
ELSE
	oWatchdogTimer(IN:=TRUE , PT:=gc_HARTWatchdogCmdTimeout);
END_IF

IF oWatchdogTimer.Q THEN
	IF NOT( wState=0 OR wState=999 ) THEN
		dwError  := 16#0205;
		sStatus := 'ERROR: WatchDog - No progress, maximum steptime elapsed';
		wState  := 999; (* Go Ahead *)
	END_IF
END_IF

               Q   , � � ��           HART_pab2DATE ��ST	��ST      ��������        �   FUNCTION HART_pab2DATE : DATE
(* Convert a ARRAY [0..2] OF BYTE into a DATE *)
VAR_INPUT
	pabIn : POINTER TO ARRAY [0..3] OF BYTE;
END_VAR
VAR
	sHelp: STRING(30);
END_VAR
/  (*
The HART date format consists of a set of three Bytes
representing

	* day-of-the month (1 to 31),
    * month (1 to 12), and
    * "year minus 1900" (0 to 255).

in pabIn

	pabIn^[0] - days
	pabIn^[1] - months
	pabIn^[2] - years since 1900
*)

sHelp := 'd#';
sHelp := CONCAT(sHelp, WORD_TO_STRING(BYTE_TO_WORD(pabIn^[2]) + 1900));
sHelp := CONCAT(sHelp, '-');
sHelp := CONCAT(sHelp, BYTE_TO_STRING(pabIn^[1]));
sHelp := CONCAT(sHelp, '-');
sHelp := CONCAT(sHelp, BYTE_TO_STRING(pabIn^[0]));

HART_pab2DATE := STRING_TO_DATE(sHelp);
               E   , � � ��           HART_pab2DWORD ��ST	��ST      ��������        �   FUNCTION HART_pab2DWORD : DWORD
(* Convert a ARRAY [0..3] OF BYTE into a DWORD *)
VAR_INPUT
	pabIn : POINTER TO ARRAY [0..3] OF BYTE;
END_VAR
VAR
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	dwOut : DWORD;
END_VAR�   pabHelp := ADR(dwOut);

pabHelp^[0] := pabIn^[0];
pabHelp^[1] := pabIn^[1];
pabHelp^[2] := pabIn^[2];
pabHelp^[3] := pabIn^[3];

HART_pab2DWORD := dwOut;               �   , , , !           HART_pab2dwSerialNumber ��ST	��ST      ��������          FUNCTION HART_pab2dwSerialNumber : DWORD
(* Convert a ARRAY [0..2] OF BYTE that represents serial number into a DWORD *)
VAR_INPUT
	pabIn : POINTER TO ARRAY [0..2] OF BYTE;
END_VAR
VAR
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	dwOut : DWORD;
END_VAR�   pabHelp := ADR(dwOut);

pabHelp^[0] := pabIn^[0];
pabHelp^[1] := pabIn^[1];
pabHelp^[2] := pabIn^[2];

HART_pab2dwSerialNumber := dwOut;
               J   ,   !           HART_pab2REAL ��ST	��ST      ��������        �   FUNCTION HART_pab2REAL : REAL
(* Convert a ARRAY [0..3] OF BYTE into a REAL *)
VAR_INPUT
	pabIn : POINTER TO ARRAY [0..3] OF BYTE;
END_VAR
VAR
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
	rOut : REAL;
END_VAR�   pabHelp := ADR(rOut);

pabHelp^[0] := pabIn^[3];
pabHelp^[1] := pabIn^[2];
pabHelp^[2] := pabIn^[1];
pabHelp^[3] := pabIn^[0];

HART_pab2REAL := rOut;               h   , X X {,           HART_pab2sDesc ��ST	��ST      ��������        e  FUNCTION HART_pab2sDesc : STRING(16)
(* Convert a ARRAY [0..11] OF BYTE into a IEC-STRING(8) according the HART-ASCII-Coding guideline *)
VAR_INPUT
	pabIn : POINTER TO ARRAY [0..11] OF BYTE; (* Raw data of packted asscii bytes *)
END_VAR

VAR
	abHelp : ARRAY [0..32] OF BYTE;
	dwHelp : DWORD;
	psHelp : POINTER TO STRING(16);
	i, k : INT;
END_VAR�  FOR i:=0 TO 3 DO
	dwHelp := BYTE_TO_DWORD(pabIn^[i*3+2]) OR SHL(BYTE_TO_DWORD(pabIn^[i*3 +1]),8) OR SHL(BYTE_TO_DWORD(pabIn^[i*3]),16);
	FOR k:=3 TO 0 BY -1 DO
		(* Unterste 6 byte ausmaskieren *)
		abHelp[i*4 +k] := DWORD_TO_BYTE(dwHelp AND 16#0000003F);
		(* Um 6 Stellen nach rechts schieben *)
		dwHelp := SHR(dwHelp, 6);
		IF abHelp[i*4 +k] < 32 THEN
			abHelp[i*4 +k] := abHelp[i*4 +k] +64;
		END_IF
	END_FOR
END_FOR
psHelp := ADR(abHelp);
HART_pab2sDesc := psHelp^; (* Success *)               k   , � � ��           HART_pab2sMsg ��ST	��ST      ��������        e  FUNCTION HART_pab2sMsg : STRING(32)
(* Convert a ARRAY [0..23] OF BYTE into a IEC-STRING(32) according the HART-ASCII-Coding guideline *)
VAR_INPUT
	pabIn : POINTER TO ARRAY [0..23] OF BYTE; (* Raw data of packted asscii bytes *)
END_VAR

VAR
	abHelp : ARRAY [0..32] OF BYTE;
	dwHelp : DWORD;
	psHelp : POINTER TO STRING(32);
	i, k : INT;
END_VAR�  FOR i:=0 TO 7 DO
	dwHelp := BYTE_TO_DWORD(pabIn^[i*3+2]) OR SHL(BYTE_TO_DWORD(pabIn^[i*3 +1]),8) OR SHL(BYTE_TO_DWORD(pabIn^[i*3]),16);
	FOR k:=3 TO 0 BY -1 DO
		(* Unterste 6 byte ausmaskieren *)
		abHelp[i*4 +k] := DWORD_TO_BYTE(dwHelp AND 16#0000003F);
		(* Um 6 Stellen nach rechts schieben *)
		dwHelp := SHR(dwHelp, 6);
		IF abHelp[i*4 +k] < 32 THEN
			abHelp[i*4 +k] := abHelp[i*4 +k] +64;
		END_IF
	END_FOR
END_FOR
psHelp := ADR(abHelp);
HART_pab2sMsg := psHelp^; (* Success *)               l   , B B e           HART_pab2sTag ��ST	��ST      ��������        `  FUNCTION HART_pab2sTag : STRING(8)
(* Convert a ARRAY [0..5] OF BYTE into a IEC-STRING(8) according the HART-ASCII-Coding guideline *)
VAR_INPUT
	pabIn : POINTER TO ARRAY [0..5] OF BYTE; (* Raw data of packted asscii bytes *)
END_VAR

VAR
	abHelp : ARRAY [0..32] OF BYTE;
	dwHelp : DWORD;
	psHelp : POINTER TO STRING(8);
	i, k : INT;
END_VAR�  FOR i:=0 TO 1 DO
	dwHelp := BYTE_TO_DWORD(pabIn^[i*3+2]) OR SHL(BYTE_TO_DWORD(pabIn^[i*3 +1]),8) OR SHL(BYTE_TO_DWORD(pabIn^[i*3]),16);
	FOR k:=3 TO 0 BY -1 DO
		(* Unterste 6 byte ausmaskieren *)
		abHelp[i*4 +k] := DWORD_TO_BYTE(dwHelp AND 16#0000003F);
		(* Um 6 Stellen nach rechts schieben *)
		dwHelp := SHR(dwHelp, 6);
		IF abHelp[i*4 +k] < 32 THEN
			abHelp[i*4 +k] := abHelp[i*4 +k] +64;
		END_IF
	END_FOR
END_FOR
psHelp := ADR(abHelp);
HART_pab2sTag := psHelp^; (* Success *)               C   , � � ��           HART_REAL2pab ��ST	��ST      ��������        �   FUNCTION HART_REAL2pab: BOOL
(* Convert a REAL into a ARRAY [0..3] OF BYTE  *)
VAR_INPUT
	rValue: REAL;
	pabIn : POINTER TO ARRAY [0..3] OF BYTE;
END_VAR
VAR
	pabHelp : POINTER TO ARRAY [0..3] OF BYTE;
END_VAR�   pabHelp := ADR(rValue);

pabIn^[0] := pabHelp^[3];
pabIn^[1] := pabHelp^[2];
pabIn^[2] := pabHelp^[1];
pabIn^[3] := pabHelp^[0];

(* HART_REAL2pab := TRUE;*)               |   ,   ��           HART_STRING2pab ��ST	��ST      ��������        �  FUNCTION HART_STRING2pab : WORD
(* Convert a a STRING into packted ARRAY [0..n] OF BYTE according the HART-ASCII-Coding guideline
		wError:
			16#0701 => 'Convert-Error, param "sInput" exceed maximum length of 32'
			16#0702 => 'Convert-Error, one character in string is out of range and replaced with '?' 
			16#0703 => 'Convert-Error, param "iCount" have to be 8, 16 or 32' *)
VAR_INPUT
	sInput : STRING(32); (* String to convert in packted ASCII *)
	iCount : INT; 	(* Number of characters(8, 16, 32) to convert (Example: 8 characters are packted into 6 databytes *)
	pabOut : POINTER TO ARRAY [0..23] OF BYTE;
END_VAR
VAR
	iLen : INT; (* Length of input string *)

	pabHelp : POINTER TO ARRAY [0..32] OF BYTE;
	dwHelpChar : DWORD; (* 1 converted byte *)
	dwHelpQuad : DWORD; (* 4 converted char's, stored in the lower 24 bits *)
	pabHelpQuad : POINTER TO ARRAY [0..3] OF BYTE;

	i, k: INT;
	xLast : BOOL;
END_VAR�  iLen := LEN(sInput);
IF iLen > 32 THEN
	HART_STRING2pab := 16#0701;  (* Convert-Error, param "sInput" exceed maximum length of 32 *)
	RETURN;
END_IF

CASE iCount OF
	8,16,32: (* Valid values *)
	;
ELSE (* Invalid values *)
	HART_STRING2pab := 16#0703;  (* Convert-Error, param "iCount" have to be 8, 16 or 32*)
	RETURN;
END_CASE

pabHelp := ADR(sInput);
dwHelpQuad := 16#00000000; (* Reset content *)

FOR i:=0 TO iCount-1 DO
	(* Fill up missing characters with <space> *)
	IF i < iLen THEN
		dwHelpChar := BYTE_TO_DWORD(pabHelp^[i]);
	ELSE
		dwHelpChar := 16#00000020; (* 16#20 ==> <space> *)
	END_IF
	(* Convert lower-case characters to upper-case one *)
	IF dwHelpChar >= 97  AND dwHelpChar <= 172 THEN
		dwHelpChar := dwHelpChar - 32;
	END_IF
	(* Convert according HART-ASCII-TABLE *)
	IF dwHelpChar < 32 OR dwHelpChar > 95 THEN
		HART_STRING2pab := 16#0702;  (* => 'Convert-Error, one character in string is out of range and replaced with '?' *)
		dwHelpChar := 16#0000003F;   (* Replace out of range char's with '?' *)
	ELSIF dwHelpChar >= 64 THEN
		dwHelpChar := dwHelpChar-64; (* Move char from ASCII to PackedASCII *)
	END_IF
	CASE (i MOD 4) OF
	0: (* 1tes Zeichen: Verschieben des 6Bit HART-Zeichens um k*6 Positionen im DWORD *)
		dwHelpChar := SHL(dwHelpChar, 18);
	1: (* 2tes Zeichen *)
		dwHelpChar := SHL(dwHelpChar, 12);
	2: (* 3tes Zeichen *)
		dwHelpChar := SHL(dwHelpChar, 6);
	3: (* 4tes Zeichen *)
		dwHelpChar := SHL(dwHelpChar, 0);
		xLast := TRUE;
	END_CASE
	(* Zusammenf�hren von 4 HART codierten characters in dwHelpQuad *)
	dwHelpQuad := dwHelpQuad OR dwHelpChar;
	IF xLast THEN
		xLast := FALSE;
		(* Die 4 zusammengef�hrten HART characters in Ausgangsarray kopieren *)
		pabHelpQuad := ADR(dwHelpQuad);
		pabOut^[k+2] := pabHelpQuad^[0];
		pabOut^[k+1] := pabHelpQuad^[1];
		pabOut^[k+0] := pabHelpQuad^[2];
		k:=k+3;
		dwHelpQuad := 16#00000000; (* Reset content *)
	END_IF
END_FOR
               �   , � � Uy           HART_UnitCodeStrings ��ST	��ST      ��������        �%  FUNCTION HART_UnitCodeStrings: BOOL
VAR_INPUT
END_VAR
VAR
	xAssignFlag : BOOL := TRUE;
	i : INT := 0;

	asHARTUnitCodeText : ARRAY [1..178] OF STRING(30):=
		(*   1 *)'Inches of Water (68 �F)',
		(*   2 *)'Inches of Mercury (0�C)',
		(*   3 *)'Feet of Water (68 �F)',
		(*   4 *)'Millimeters of Water (68 �F)',
		(*   5 *)'Millimeters of Mercury (0�C)',
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
		(* 145 *)'Inches of water at 4 �C',
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
		(* 238 *)'in H2O (4�C)',
		(* 239 *)'mm H2O (4�C)', 
		(* 240-249 - manufacturer specific defs. *)
		(* 250 *)'Not Used',
		(* 251 *)'None',
		(* 252 *)'Unknown Units',
		(* 253 *)'Special';

	asHARTUnitCodeAbbr : ARRAY [1..178] OF STRING(12):=
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
		(*  32 *)'�C',
		(*  33 *)'�F',
		(*  34 *)'�R',
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
		(* 100 *)'�Twad',
		(* 101 *)'�Brix',
		(* 102 *)'�BaumHv',
		(* 103 *)'�BaumLt',
		(* 104 *)'�API',
		(* 105 *)'%Sol/wt',
		(* 106 *)'%Sol/vol',
		(* 107 *)'�Ball',
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
		(* 143 *)'�',		
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
		(* 253 *)'spec';
    
END_VAR     
Qu  (* Unit Code Assignment *)

(* Do it just once *)
IF xAssignFlag = TRUE THEN
	xAssignFlag := FALSE;

	(* Assign all pointers to empty string *)
	FOR i:=1 TO 256 DO
		g_apasHARTUnitCode[i, 0] := ADR(asHARTUnitCodeText[175]);
		g_apasHARTUnitCode[i, 1] := ADR(asHARTUnitCodeAbbr[175]);
	END_FOR;

	(* Assign text given by HART spec. *)
	(*   1 *) g_apasHARTUnitCode[1, 0] := ADR(asHARTUnitCodeText[1]); (* 'InH2O' *)
	(*   2 *) g_apasHARTUnitCode[2, 0] := ADR(asHARTUnitCodeText[2]); (* 'InHg' *)
	(*   3 *) g_apasHARTUnitCode[3, 0] := ADR(asHARTUnitCodeText[3]); (* 'FtH2O' *)
	(*   4 *) g_apasHARTUnitCode[4, 0] := ADR(asHARTUnitCodeText[4]); (* 'mmH2O' *)
	(*   5 *) g_apasHARTUnitCode[5, 0] := ADR(asHARTUnitCodeText[5]); (* 'mmHg' *)
	(*   6 *) g_apasHARTUnitCode[6, 0] := ADR(asHARTUnitCodeText[6]); (* 'PSI' *)
	(*   7 *) g_apasHARTUnitCode[7, 0] := ADR(asHARTUnitCodeText[7]); (* 'bar' *)
	(*   8 *) g_apasHARTUnitCode[8, 0] := ADR(asHARTUnitCodeText[8]); (* 'mbar' *)
	(*   9 *) g_apasHARTUnitCode[9, 0] := ADR(asHARTUnitCodeText[9]); (* 'g/cm2' *)
	(*  10 *) g_apasHARTUnitCode[10, 0] := ADR(asHARTUnitCodeText[10]); (* 'kg/cm2' *)
	(*  11 *) g_apasHARTUnitCode[11, 0] := ADR(asHARTUnitCodeText[11]); (* 'PA' *)
	(*  12 *) g_apasHARTUnitCode[12, 0] := ADR(asHARTUnitCodeText[12]); (* 'kPA' *)
	(*  13 *) g_apasHARTUnitCode[13, 0] := ADR(asHARTUnitCodeText[13]); (* 'torr' *)
	(*  14 *) g_apasHARTUnitCode[14, 0] := ADR(asHARTUnitCodeText[14]); (* 'ATM' *)
	(*  15 *) g_apasHARTUnitCode[15, 0] := ADR(asHARTUnitCodeText[15]); (* 'ft3/min' *)
	(*  16 *) g_apasHARTUnitCode[16, 0] := ADR(asHARTUnitCodeText[16]); (* 'gal/min' *)
	(*  17 *) g_apasHARTUnitCode[17, 0] := ADR(asHARTUnitCodeText[17]); (* 'l/min' *)
	(*  18 *) g_apasHARTUnitCode[18, 0] := ADR(asHARTUnitCodeText[18]); (* 'ImpGal/min' *)
	(*  19 *) g_apasHARTUnitCode[19, 0] := ADR(asHARTUnitCodeText[19]); (* 'm3/hr' *)
	(*  20 *) g_apasHARTUnitCode[20, 0] := ADR(asHARTUnitCodeText[20]); (* 'ft/s' *)
	(*  21 *) g_apasHARTUnitCode[21, 0] := ADR(asHARTUnitCodeText[21]); (* 'mtr/s' *)
	(*  22 *) g_apasHARTUnitCode[22, 0] := ADR(asHARTUnitCodeText[22]); (* 'gal/sec' *)
	(*  23 *) g_apasHARTUnitCode[23, 0] := ADR(asHARTUnitCodeText[23]); (* 'MilGal/day' *)
	(*  24 *) g_apasHARTUnitCode[24, 0] := ADR(asHARTUnitCodeText[24]); (* 'lt/sec' *)
	(*  25 *) g_apasHARTUnitCode[25, 0] := ADR(asHARTUnitCodeText[25]); (* 'MilL/day' *)
	(*  26 *) g_apasHARTUnitCode[26, 0] := ADR(asHARTUnitCodeText[26]); (* 'ft3/sec' *)
	(*  27 *) g_apasHARTUnitCode[27, 0] := ADR(asHARTUnitCodeText[27]); (* 'ft3/day' *)
	(*  28 *) g_apasHARTUnitCode[28, 0] := ADR(asHARTUnitCodeText[28]); (* 'm3/sec' *)
	(*  29 *) g_apasHARTUnitCode[29, 0] := ADR(asHARTUnitCodeText[29]); (* 'm3/day' *)
	(*  30 *) g_apasHARTUnitCode[30, 0] := ADR(asHARTUnitCodeText[30]); (* 'ImpGal/hr' *)
	(*  31 *) g_apasHARTUnitCode[31, 0] := ADR(asHARTUnitCodeText[31]); (* 'ImpGal/day' *)
	(*  32 *) g_apasHARTUnitCode[32, 0] := ADR(asHARTUnitCodeText[32]); (* '�C' *)
	(*  33 *) g_apasHARTUnitCode[33, 0] := ADR(asHARTUnitCodeText[33]); (* '�F' *)
	(*  34 *) g_apasHARTUnitCode[34, 0] := ADR(asHARTUnitCodeText[34]); (* '�R' *)
	(*  35 *) g_apasHARTUnitCode[35, 0] := ADR(asHARTUnitCodeText[35]); (* 'Kelvin' *)
	(*  36 *) g_apasHARTUnitCode[36, 0] := ADR(asHARTUnitCodeText[36]); (* 'mV' *)
	(*  37 *) g_apasHARTUnitCode[37, 0] := ADR(asHARTUnitCodeText[37]); (* 'Ohm' *)
	(*  38 *) g_apasHARTUnitCode[38, 0] := ADR(asHARTUnitCodeText[38]); (* 'Hz' *)
	(*  39 *) g_apasHARTUnitCode[39, 0] := ADR(asHARTUnitCodeText[39]); (* 'mA' *)
	(*  40 *) g_apasHARTUnitCode[40, 0] := ADR(asHARTUnitCodeText[40]); (* 'gal' *)
	(*  41 *) g_apasHARTUnitCode[41, 0] := ADR(asHARTUnitCodeText[41]); (* 'lt' *)
	(*  42 *) g_apasHARTUnitCode[42, 0] := ADR(asHARTUnitCodeText[42]); (* 'ImpGal' *)
	(*  43 *) g_apasHARTUnitCode[43, 0] := ADR(asHARTUnitCodeText[43]); (* 'm3' *)
	(*  44 *) g_apasHARTUnitCode[44, 0] := ADR(asHARTUnitCodeText[44]); (* 'ft' *)
	(*  45 *) g_apasHARTUnitCode[45, 0] := ADR(asHARTUnitCodeText[45]); (* 'm' *)
	(*  46 *) g_apasHARTUnitCode[46, 0] := ADR(asHARTUnitCodeText[46]); (* 'bbl' *)
	(*  47 *) g_apasHARTUnitCode[47, 0] := ADR(asHARTUnitCodeText[47]); (* 'in' *)
	(*  48 *) g_apasHARTUnitCode[48, 0] := ADR(asHARTUnitCodeText[48]); (* 'cm' *)
	(*  49 *) g_apasHARTUnitCode[49, 0] := ADR(asHARTUnitCodeText[49]); (* 'mm' *)
	(*  50 *) g_apasHARTUnitCode[50, 0] := ADR(asHARTUnitCodeText[50]); (* 'min' *)
	(*  51 *) g_apasHARTUnitCode[51, 0] := ADR(asHARTUnitCodeText[51]); (* 'sec' *)
	(*  52 *) g_apasHARTUnitCode[52, 0] := ADR(asHARTUnitCodeText[52]); (* 'hr' *)
	(*  53 *) g_apasHARTUnitCode[53, 0] := ADR(asHARTUnitCodeText[53]); (* 'day' *)
	(*  54 *) g_apasHARTUnitCode[54, 0] := ADR(asHARTUnitCodeText[54]); (* 'stokes' *)
	(*  55 *) g_apasHARTUnitCode[55, 0] := ADR(asHARTUnitCodeText[55]); (* 'cpoise' *)
	(*  56 *) g_apasHARTUnitCode[56, 0] := ADR(asHARTUnitCodeText[56]); (* 'uMho' *)
	(*  57 *) g_apasHARTUnitCode[57, 0] := ADR(asHARTUnitCodeText[57]); (* '%' *)
	(*  58 *) g_apasHARTUnitCode[58, 0] := ADR(asHARTUnitCodeText[58]); (* 'V' *)
	(*  59 *) g_apasHARTUnitCode[59, 0] := ADR(asHARTUnitCodeText[59]); (* 'pH' *)
	(*  60 *) g_apasHARTUnitCode[60, 0] := ADR(asHARTUnitCodeText[60]); (* 'g' *)
	(*  61 *) g_apasHARTUnitCode[61, 0] := ADR(asHARTUnitCodeText[61]); (* 'kg' *)
	(*  62 *) g_apasHARTUnitCode[62, 0] := ADR(asHARTUnitCodeText[62]); (* 'MetTon' *)
	(*  63 *) g_apasHARTUnitCode[63, 0] := ADR(asHARTUnitCodeText[63]); (* 'lb' *)
	(*  64 *) g_apasHARTUnitCode[64, 0] := ADR(asHARTUnitCodeText[64]); (* 'ShTon' *)
	(*  65 *) g_apasHARTUnitCode[65, 0] := ADR(asHARTUnitCodeText[65]); (* 'LTon' *)
	(*  66 *) g_apasHARTUnitCode[66, 0] := ADR(asHARTUnitCodeText[66]); (* 'mSiemen/cm' *)
	(*  67 *) g_apasHARTUnitCode[67, 0] := ADR(asHARTUnitCodeText[67]); (* 'uSiemen/cm' *)
	(*  68 *) g_apasHARTUnitCode[68, 0] := ADR(asHARTUnitCodeText[68]); (* 'N' *)
	(*  69 *) g_apasHARTUnitCode[69, 0] := ADR(asHARTUnitCodeText[69]); (* 'NM' *)
	(*  70 *) g_apasHARTUnitCode[70, 0] := ADR(asHARTUnitCodeText[70]); (* 'g/s' *)
	(*  71 *) g_apasHARTUnitCode[71, 0] := ADR(asHARTUnitCodeText[71]); (* 'g/min' *)
	(*  72 *) g_apasHARTUnitCode[72, 0] := ADR(asHARTUnitCodeText[72]); (* 'g/hr' *)
	(*  73 *) g_apasHARTUnitCode[73, 0] := ADR(asHARTUnitCodeText[73]); (* 'kg/s' *)
	(*  74 *) g_apasHARTUnitCode[74, 0] := ADR(asHARTUnitCodeText[74]); (* 'kg/min' *)
	(*  75 *) g_apasHARTUnitCode[75, 0] := ADR(asHARTUnitCodeText[75]); (* 'kg/hr' *)
	(*  76 *) g_apasHARTUnitCode[76, 0] := ADR(asHARTUnitCodeText[76]); (* 'kg/day' *)
	(*  77 *) g_apasHARTUnitCode[77, 0] := ADR(asHARTUnitCodeText[77]); (* 'MetTon/min' *)
	(*  78 *) g_apasHARTUnitCode[78, 0] := ADR(asHARTUnitCodeText[78]); (* 'MetTon/hr' *)
	(*  79 *) g_apasHARTUnitCode[79, 0] := ADR(asHARTUnitCodeText[79]); (* 'MetTon/day' *)
	(*  80 *) g_apasHARTUnitCode[80, 0] := ADR(asHARTUnitCodeText[80]); (* 'lb/s' *)
	(*  81 *) g_apasHARTUnitCode[81, 0] := ADR(asHARTUnitCodeText[81]); (* 'lb/min' *)
	(*  82 *) g_apasHARTUnitCode[82, 0] := ADR(asHARTUnitCodeText[82]); (* 'lb/hr' *)
	(*  83 *) g_apasHARTUnitCode[83, 0] := ADR(asHARTUnitCodeText[83]); (* 'lb/day' *)
	(*  84 *) g_apasHARTUnitCode[84, 0] := ADR(asHARTUnitCodeText[84]); (* 'ShTon/min' *)
	(*  85 *) g_apasHARTUnitCode[85, 0] := ADR(asHARTUnitCodeText[85]); (* 'ShTon/hr' *)
	(*  86 *) g_apasHARTUnitCode[86, 0] := ADR(asHARTUnitCodeText[86]); (* 'ShTon/day' *)
	(*  87 *) g_apasHARTUnitCode[87, 0] := ADR(asHARTUnitCodeText[87]); (* 'LTon/hr' *)
	(*  88 *) g_apasHARTUnitCode[88, 0] := ADR(asHARTUnitCodeText[88]); (* 'LTon/day' *)
	(*  89 *) g_apasHARTUnitCode[89, 0] := ADR(asHARTUnitCodeText[89]); (* 'DekaTherm' *)
	(*  90 *) g_apasHARTUnitCode[90, 0] := ADR(asHARTUnitCodeText[90]); (* 'SGU' *)
	(*  91 *) g_apasHARTUnitCode[91, 0] := ADR(asHARTUnitCodeText[91]); (* 'g/cm3' *)
	(*  92 *) g_apasHARTUnitCode[92, 0] := ADR(asHARTUnitCodeText[92]); (* 'kg/m3' *)
	(*  93 *) g_apasHARTUnitCode[93, 0] := ADR(asHARTUnitCodeText[93]); (* 'lb/gal' *)
	(*  94 *) g_apasHARTUnitCode[94, 0] := ADR(asHARTUnitCodeText[94]); (* 'lb/ft3' *)
	(*  95 *) g_apasHARTUnitCode[95, 0] := ADR(asHARTUnitCodeText[95]); (* 'g/ml' *)
	(*  96 *) g_apasHARTUnitCode[96, 0] := ADR(asHARTUnitCodeText[96]); (* 'kg/l' *)
	(*  97 *) g_apasHARTUnitCode[97, 0] := ADR(asHARTUnitCodeText[97]); (* 'g/l' *)
	(*  98 *) g_apasHARTUnitCode[98, 0] := ADR(asHARTUnitCodeText[98]); (* 'lb/CuIn' *)
	(*  99 *) g_apasHARTUnitCode[99, 0] := ADR(asHARTUnitCodeText[99]); (* 'ShTon/CuYd' *)
	(* 100 *) g_apasHARTUnitCode[100, 0] := ADR(asHARTUnitCodeText[100]); (* '�Twad' *)
	(* 101 *) g_apasHARTUnitCode[101, 0] := ADR(asHARTUnitCodeText[101]); (* '�Brix' *)
	(* 102 *) g_apasHARTUnitCode[102, 0] := ADR(asHARTUnitCodeText[102]); (* '�BaumHv' *)
	(* 103 *) g_apasHARTUnitCode[103, 0] := ADR(asHARTUnitCodeText[103]); (* '�BaumLt' *)
	(* 104 *) g_apasHARTUnitCode[104, 0] := ADR(asHARTUnitCodeText[104]); (* '�API' *)
	(* 105 *) g_apasHARTUnitCode[105, 0] := ADR(asHARTUnitCodeText[105]); (* '%Sol/wt' *)
	(* 106 *) g_apasHARTUnitCode[106, 0] := ADR(asHARTUnitCodeText[106]); (* '%Sol/vol' *)
	(* 107 *) g_apasHARTUnitCode[107, 0] := ADR(asHARTUnitCodeText[107]); (* '�Ball' *)
	(* 108 *) g_apasHARTUnitCode[108, 0] := ADR(asHARTUnitCodeText[108]); (* 'proof/vol' *)
	(* 109 *) g_apasHARTUnitCode[109, 0] := ADR(asHARTUnitCodeText[109]); (* 'proof/mass' *)
	(* 110 *) g_apasHARTUnitCode[110, 0] := ADR(asHARTUnitCodeText[110]); (* 'bush' *)
	(* 111 *) g_apasHARTUnitCode[111, 0] := ADR(asHARTUnitCodeText[111]); (* 'yd3' *)
	(* 112 *) g_apasHARTUnitCode[112, 0] := ADR(asHARTUnitCodeText[112]); (* 'ft3' *)
	(* 113 *) g_apasHARTUnitCode[113, 0] := ADR(asHARTUnitCodeText[113]); (* 'in3' *)
	(* 114 *) g_apasHARTUnitCode[114, 0] := ADR(asHARTUnitCodeText[114]); (* 'in/s' *)
	(* 115 *) g_apasHARTUnitCode[115, 0] := ADR(asHARTUnitCodeText[115]); (* 'in/min' *)
	(* 116 *) g_apasHARTUnitCode[116, 0] := ADR(asHARTUnitCodeText[116]); (* 'ft/min' *)
	(* 117 *) g_apasHARTUnitCode[117, 0] := ADR(asHARTUnitCodeText[117]); (* 'deg/s' *)
	(* 118 *) g_apasHARTUnitCode[118, 0] := ADR(asHARTUnitCodeText[118]); (* 'rev/s' *)
	(* 119 *) g_apasHARTUnitCode[119, 0] := ADR(asHARTUnitCodeText[119]); (* 'rpm' *)
	(* 120 *) g_apasHARTUnitCode[120, 0] := ADR(asHARTUnitCodeText[120]); (* 'mtr/hr' *)
	(* 121 *) g_apasHARTUnitCode[121, 0] := ADR(asHARTUnitCodeText[121]); (* 'm3/hr' *)
	(* 122 *) g_apasHARTUnitCode[122, 0] := ADR(asHARTUnitCodeText[122]); (* 'l/hr' *)
	(* 123 *) g_apasHARTUnitCode[123, 0] := ADR(asHARTUnitCodeText[123]); (* 'ft3/min' *)
	(* 124 *) g_apasHARTUnitCode[124, 0] := ADR(asHARTUnitCodeText[124]); (* 'bblLiq' *)
	(* 125 *) g_apasHARTUnitCode[125, 0] := ADR(asHARTUnitCodeText[125]); (* 'ounce' *)
	(* 126 *) g_apasHARTUnitCode[126, 0] := ADR(asHARTUnitCodeText[126]); (* 'ftpf' *)
	(* 127 *) g_apasHARTUnitCode[127, 0] := ADR(asHARTUnitCodeText[127]); (* 'kW' *)
	(* 128 *) g_apasHARTUnitCode[128, 0] := ADR(asHARTUnitCodeText[128]); (* 'kWh' *)
	(* 129 *) g_apasHARTUnitCode[129, 0] := ADR(asHARTUnitCodeText[129]); (* 'HP' *)
	(* 130 *) g_apasHARTUnitCode[130, 0] := ADR(asHARTUnitCodeText[130]); (* 'ft3/hr' *)
	(* 131 *) g_apasHARTUnitCode[131, 0] := ADR(asHARTUnitCodeText[131]); (* 'm3/min' *)
	(* 132 *) g_apasHARTUnitCode[132, 0] := ADR(asHARTUnitCodeText[132]); (* 'bbl/s' *)
	(* 133 *) g_apasHARTUnitCode[133, 0] := ADR(asHARTUnitCodeText[133]); (* 'bbl/min' *)
	(* 134 *) g_apasHARTUnitCode[134, 0] := ADR(asHARTUnitCodeText[134]); (* 'bbl/hr' *)
	(* 135 *) g_apasHARTUnitCode[135, 0] := ADR(asHARTUnitCodeText[135]); (* 'bbl/day' *)
	(* 136 *) g_apasHARTUnitCode[136, 0] := ADR(asHARTUnitCodeText[136]); (* 'gal/hr' *)
	(* 137 *) g_apasHARTUnitCode[137, 0] := ADR(asHARTUnitCodeText[137]); (* 'ImpGal/s' *)
	(* 138 *) g_apasHARTUnitCode[138, 0] := ADR(asHARTUnitCodeText[138]); (* 'l/hr' *)
	(* 139 *) g_apasHARTUnitCode[139, 0] := ADR(asHARTUnitCodeText[139]); (* 'ppm' *)
	(* 140 *) g_apasHARTUnitCode[140, 0] := ADR(asHARTUnitCodeText[140]); (* 'MCal/hr' *)
	(* 141 *) g_apasHARTUnitCode[141, 0] := ADR(asHARTUnitCodeText[141]); (* 'MJ/hr' *)
	(* 142 *) g_apasHARTUnitCode[142, 0] := ADR(asHARTUnitCodeText[142]); (* 'BTU/hr' *)
	(* 143 *) g_apasHARTUnitCode[143, 0] := ADR(asHARTUnitCodeText[143]); (* '�' *)
	(* 144 *) g_apasHARTUnitCode[144, 0] := ADR(asHARTUnitCodeText[144]); (* 'Rads' *)
	(* 145 *) g_apasHARTUnitCode[145, 0] := ADR(asHARTUnitCodeText[145]); (* 'in' *)
	(* 146 *) g_apasHARTUnitCode[146, 0] := ADR(asHARTUnitCodeText[146]); (* 'ug/lt' *)
	(* 147 *) g_apasHARTUnitCode[147, 0] := ADR(asHARTUnitCodeText[147]); (* 'ug/lt3' *)
	(* 148 *) g_apasHARTUnitCode[148, 0] := ADR(asHARTUnitCodeText[148]); (* '%' *)
	(* 149 *) g_apasHARTUnitCode[149, 0] := ADR(asHARTUnitCodeText[149]); (* '%' *)
	(* 150 *) g_apasHARTUnitCode[150, 0] := ADR(asHARTUnitCodeText[150]); (* '%StmQual' *) 
	(* 151 *) g_apasHARTUnitCode[151, 0] := ADR(asHARTUnitCodeText[151]); (* 'Ftin16' *)
	(* 152 *) g_apasHARTUnitCode[152, 0] := ADR(asHARTUnitCodeText[152]); (* 'ft3/lb' *)   
	(* 153 *) g_apasHARTUnitCode[153, 0] := ADR(asHARTUnitCodeText[153]); (* 'pF' *)
	(* 154 *) g_apasHARTUnitCode[154, 0] := ADR(asHARTUnitCodeText[154]); (* 'mlt/lt' *)
	(* 155 *) g_apasHARTUnitCode[155, 0] := ADR(asHARTUnitCodeText[155]); (* 'ult/lt' *)
	(* 160 *) g_apasHARTUnitCode[160, 0] := ADR(asHARTUnitCodeText[160]); (* '%Plato' *)
	(* 161 *) g_apasHARTUnitCode[161, 0] := ADR(asHARTUnitCodeText[161]); (* '%StmQual' *)
	(* 162 *) g_apasHARTUnitCode[162, 0] := ADR(asHARTUnitCodeText[162]); (* 'MCal' *)
	(* 163 *) g_apasHARTUnitCode[163, 0] := ADR(asHARTUnitCodeText[163]); (* 'kOhm' *)
	(* 164 *) g_apasHARTUnitCode[164, 0] := ADR(asHARTUnitCodeText[164]); (* 'MJ' *)
	(* 165 *) g_apasHARTUnitCode[165, 0] := ADR(asHARTUnitCodeText[165]); (* 'BTU' *)
	(* 166 *) g_apasHARTUnitCode[166, 0] := ADR(asHARTUnitCodeText[166]); (* 'm3' *)
	(* 167 *) g_apasHARTUnitCode[167, 0] := ADR(asHARTUnitCodeText[167]); (* 'lt' *)
	(* 168 *) g_apasHARTUnitCode[168, 0] := ADR(asHARTUnitCodeText[168]); (* 'ft3' *)
	(* 169 *) g_apasHARTUnitCode[169, 0] := ADR(asHARTUnitCodeText[169]); (* 'parts/bilion' *)
	(* 170-219 - HART spec. expansion table *)
	(* 235 *) g_apasHARTUnitCode[235, 0] := ADR(asHARTUnitCodeText[170]); (* 'Gal/day' *)
	(* 236 *) g_apasHARTUnitCode[236, 0] := ADR(asHARTUnitCodeText[171]); (* 'hlt' *)
	(* 237 *) g_apasHARTUnitCode[237, 0] := ADR(asHARTUnitCodeText[172]); (* 'MPa' *)
	(* 238 *) g_apasHARTUnitCode[238, 0] := ADR(asHARTUnitCodeText[173]); (* 'in' *)
	(* 239 *) g_apasHARTUnitCode[239, 0] := ADR(asHARTUnitCodeText[174]); (* 'mm' *)
	(* 240-249 - manufacturer specific defs. *)
	(* 250 *) g_apasHARTUnitCode[250, 0] := ADR(asHARTUnitCodeText[175]); (* '' *)
	(* 251 *) g_apasHARTUnitCode[251, 0] := ADR(asHARTUnitCodeText[176]); (* '-' *)
	(* 252 *) g_apasHARTUnitCode[252, 0] := ADR(asHARTUnitCodeText[177]); (* '?' *)
	(* 253 *) g_apasHARTUnitCode[253, 0] := ADR(asHARTUnitCodeText[178]); (* 'spec' *)

	(* Assign abbreviations *)
	(*   1 *) g_apasHARTUnitCode[1, 1] := ADR(asHARTUnitCodeAbbr[1]); (* 'InH2O' *)
	(*   2 *) g_apasHARTUnitCode[2, 1] := ADR(asHARTUnitCodeAbbr[2]); (* 'InHg' *)
	(*   3 *) g_apasHARTUnitCode[3, 1] := ADR(asHARTUnitCodeAbbr[3]); (* 'FtH2O' *)
	(*   4 *) g_apasHARTUnitCode[4, 1] := ADR(asHARTUnitCodeAbbr[4]); (* 'mmH2O' *)
	(*   5 *) g_apasHARTUnitCode[5, 1] := ADR(asHARTUnitCodeAbbr[5]); (* 'mmHg' *)
	(*   6 *) g_apasHARTUnitCode[6, 1] := ADR(asHARTUnitCodeAbbr[6]); (* 'PSI' *)
	(*   7 *) g_apasHARTUnitCode[7, 1] := ADR(asHARTUnitCodeAbbr[7]); (* 'bar' *)
	(*   8 *) g_apasHARTUnitCode[8, 1] := ADR(asHARTUnitCodeAbbr[8]); (* 'mbar' *)
	(*   9 *) g_apasHARTUnitCode[9, 1] := ADR(asHARTUnitCodeAbbr[9]); (* 'g/cm2' *)
	(*  10 *) g_apasHARTUnitCode[10, 1] := ADR(asHARTUnitCodeAbbr[10]); (* 'kg/cm2' *)
	(*  11 *) g_apasHARTUnitCode[11, 1] := ADR(asHARTUnitCodeAbbr[11]); (* 'PA' *)
	(*  12 *) g_apasHARTUnitCode[12, 1] := ADR(asHARTUnitCodeAbbr[12]); (* 'kPA' *)
	(*  13 *) g_apasHARTUnitCode[13, 1] := ADR(asHARTUnitCodeAbbr[13]); (* 'torr' *)
	(*  14 *) g_apasHARTUnitCode[14, 1] := ADR(asHARTUnitCodeAbbr[14]); (* 'ATM' *)
	(*  15 *) g_apasHARTUnitCode[15, 1] := ADR(asHARTUnitCodeAbbr[15]); (* 'ft3/min' *)
	(*  16 *) g_apasHARTUnitCode[16, 1] := ADR(asHARTUnitCodeAbbr[16]); (* 'gal/min' *)
	(*  17 *) g_apasHARTUnitCode[17, 1] := ADR(asHARTUnitCodeAbbr[17]); (* 'l/min' *)
	(*  18 *) g_apasHARTUnitCode[18, 1] := ADR(asHARTUnitCodeAbbr[18]); (* 'ImpGal/min' *)
	(*  19 *) g_apasHARTUnitCode[19, 1] := ADR(asHARTUnitCodeAbbr[19]); (* 'm3/hr' *)
	(*  20 *) g_apasHARTUnitCode[20, 1] := ADR(asHARTUnitCodeAbbr[20]); (* 'ft/s' *)
	(*  21 *) g_apasHARTUnitCode[21, 1] := ADR(asHARTUnitCodeAbbr[21]); (* 'mtr/s' *)
	(*  22 *) g_apasHARTUnitCode[22, 1] := ADR(asHARTUnitCodeAbbr[22]); (* 'gal/sec' *)
	(*  23 *) g_apasHARTUnitCode[23, 1] := ADR(asHARTUnitCodeAbbr[23]); (* 'MilGal/day' *)
	(*  24 *) g_apasHARTUnitCode[24, 1] := ADR(asHARTUnitCodeAbbr[24]); (* 'lt/sec' *)
	(*  25 *) g_apasHARTUnitCode[25, 1] := ADR(asHARTUnitCodeAbbr[25]); (* 'MilL/day' *)
	(*  26 *) g_apasHARTUnitCode[26, 1] := ADR(asHARTUnitCodeAbbr[26]); (* 'ft3/sec' *)
	(*  27 *) g_apasHARTUnitCode[27, 1] := ADR(asHARTUnitCodeAbbr[27]); (* 'ft3/day' *)
	(*  28 *) g_apasHARTUnitCode[28, 1] := ADR(asHARTUnitCodeAbbr[28]); (* 'm3/sec' *)
	(*  29 *) g_apasHARTUnitCode[29, 1] := ADR(asHARTUnitCodeAbbr[29]); (* 'm3/day' *)
	(*  30 *) g_apasHARTUnitCode[30, 1] := ADR(asHARTUnitCodeAbbr[30]); (* 'ImpGal/hr' *)
	(*  31 *) g_apasHARTUnitCode[31, 1] := ADR(asHARTUnitCodeAbbr[31]); (* 'ImpGal/day' *)
	(*  32 *) g_apasHARTUnitCode[32, 1] := ADR(asHARTUnitCodeAbbr[32]); (* '�C' *)
	(*  33 *) g_apasHARTUnitCode[33, 1] := ADR(asHARTUnitCodeAbbr[33]); (* '�F' *)
	(*  34 *) g_apasHARTUnitCode[34, 1] := ADR(asHARTUnitCodeAbbr[34]); (* '�R' *)
	(*  35 *) g_apasHARTUnitCode[35, 1] := ADR(asHARTUnitCodeAbbr[35]); (* 'Kelvin' *)
	(*  36 *) g_apasHARTUnitCode[36, 1] := ADR(asHARTUnitCodeAbbr[36]); (* 'mV' *)
	(*  37 *) g_apasHARTUnitCode[37, 1] := ADR(asHARTUnitCodeAbbr[37]); (* 'Ohm' *)
	(*  38 *) g_apasHARTUnitCode[38, 1] := ADR(asHARTUnitCodeAbbr[38]); (* 'Hz' *)
	(*  39 *) g_apasHARTUnitCode[39, 1] := ADR(asHARTUnitCodeAbbr[39]); (* 'mA' *)
	(*  40 *) g_apasHARTUnitCode[40, 1] := ADR(asHARTUnitCodeAbbr[40]); (* 'gal' *)
	(*  41 *) g_apasHARTUnitCode[41, 1] := ADR(asHARTUnitCodeAbbr[41]); (* 'lt' *)
	(*  42 *) g_apasHARTUnitCode[42, 1] := ADR(asHARTUnitCodeAbbr[42]); (* 'ImpGal' *)
	(*  43 *) g_apasHARTUnitCode[43, 1] := ADR(asHARTUnitCodeAbbr[43]); (* 'm3' *)
	(*  44 *) g_apasHARTUnitCode[44, 1] := ADR(asHARTUnitCodeAbbr[44]); (* 'ft' *)
	(*  45 *) g_apasHARTUnitCode[45, 1] := ADR(asHARTUnitCodeAbbr[45]); (* 'm' *)
	(*  46 *) g_apasHARTUnitCode[46, 1] := ADR(asHARTUnitCodeAbbr[46]); (* 'bbl' *)
	(*  47 *) g_apasHARTUnitCode[47, 1] := ADR(asHARTUnitCodeAbbr[47]); (* 'in' *)
	(*  48 *) g_apasHARTUnitCode[48, 1] := ADR(asHARTUnitCodeAbbr[48]); (* 'cm' *)
	(*  49 *) g_apasHARTUnitCode[49, 1] := ADR(asHARTUnitCodeAbbr[49]); (* 'mm' *)
	(*  50 *) g_apasHARTUnitCode[50, 1] := ADR(asHARTUnitCodeAbbr[50]); (* 'min' *)
	(*  51 *) g_apasHARTUnitCode[51, 1] := ADR(asHARTUnitCodeAbbr[51]); (* 'sec' *)
	(*  52 *) g_apasHARTUnitCode[52, 1] := ADR(asHARTUnitCodeAbbr[52]); (* 'hr' *)
	(*  53 *) g_apasHARTUnitCode[53, 1] := ADR(asHARTUnitCodeAbbr[53]); (* 'day' *)
	(*  54 *) g_apasHARTUnitCode[54, 1] := ADR(asHARTUnitCodeAbbr[54]); (* 'stokes' *)
	(*  55 *) g_apasHARTUnitCode[55, 1] := ADR(asHARTUnitCodeAbbr[55]); (* 'cpoise' *)
	(*  56 *) g_apasHARTUnitCode[56, 1] := ADR(asHARTUnitCodeAbbr[56]); (* 'uMho' *)
	(*  57 *) g_apasHARTUnitCode[57, 1] := ADR(asHARTUnitCodeAbbr[57]); (* '%' *)
	(*  58 *) g_apasHARTUnitCode[58, 1] := ADR(asHARTUnitCodeAbbr[58]); (* 'V' *)
	(*  59 *) g_apasHARTUnitCode[59, 1] := ADR(asHARTUnitCodeAbbr[59]); (* 'pH' *)
	(*  60 *) g_apasHARTUnitCode[60, 1] := ADR(asHARTUnitCodeAbbr[60]); (* 'g' *)
	(*  61 *) g_apasHARTUnitCode[61, 1] := ADR(asHARTUnitCodeAbbr[61]); (* 'kg' *)
	(*  62 *) g_apasHARTUnitCode[62, 1] := ADR(asHARTUnitCodeAbbr[62]); (* 'MetTon' *)
	(*  63 *) g_apasHARTUnitCode[63, 1] := ADR(asHARTUnitCodeAbbr[63]); (* 'lb' *)
	(*  64 *) g_apasHARTUnitCode[64, 1] := ADR(asHARTUnitCodeAbbr[64]); (* 'ShTon' *)
	(*  65 *) g_apasHARTUnitCode[65, 1] := ADR(asHARTUnitCodeAbbr[65]); (* 'LTon' *)
	(*  66 *) g_apasHARTUnitCode[66, 1] := ADR(asHARTUnitCodeAbbr[66]); (* 'mSiemen/cm' *)
	(*  67 *) g_apasHARTUnitCode[67, 1] := ADR(asHARTUnitCodeAbbr[67]); (* 'uSiemen/cm' *)
	(*  68 *) g_apasHARTUnitCode[68, 1] := ADR(asHARTUnitCodeAbbr[68]); (* 'N' *)
	(*  69 *) g_apasHARTUnitCode[69, 1] := ADR(asHARTUnitCodeAbbr[69]); (* 'NM' *)
	(*  70 *) g_apasHARTUnitCode[70, 1] := ADR(asHARTUnitCodeAbbr[70]); (* 'g/s' *)
	(*  71 *) g_apasHARTUnitCode[71, 1] := ADR(asHARTUnitCodeAbbr[71]); (* 'g/min' *)
	(*  72 *) g_apasHARTUnitCode[72, 1] := ADR(asHARTUnitCodeAbbr[72]); (* 'g/hr' *)
	(*  73 *) g_apasHARTUnitCode[73, 1] := ADR(asHARTUnitCodeAbbr[73]); (* 'kg/s' *)
	(*  74 *) g_apasHARTUnitCode[74, 1] := ADR(asHARTUnitCodeAbbr[74]); (* 'kg/min' *)
	(*  75 *) g_apasHARTUnitCode[75, 1] := ADR(asHARTUnitCodeAbbr[75]); (* 'kg/hr' *)
	(*  76 *) g_apasHARTUnitCode[76, 1] := ADR(asHARTUnitCodeAbbr[76]); (* 'kg/day' *)
	(*  77 *) g_apasHARTUnitCode[77, 1] := ADR(asHARTUnitCodeAbbr[77]); (* 'MetTon/min' *)
	(*  78 *) g_apasHARTUnitCode[78, 1] := ADR(asHARTUnitCodeAbbr[78]); (* 'MetTon/hr' *)
	(*  79 *) g_apasHARTUnitCode[79, 1] := ADR(asHARTUnitCodeAbbr[79]); (* 'MetTon/day' *)
	(*  80 *) g_apasHARTUnitCode[80, 1] := ADR(asHARTUnitCodeAbbr[80]); (* 'lb/s' *)
	(*  81 *) g_apasHARTUnitCode[81, 1] := ADR(asHARTUnitCodeAbbr[81]); (* 'lb/min' *)
	(*  82 *) g_apasHARTUnitCode[82, 1] := ADR(asHARTUnitCodeAbbr[82]); (* 'lb/hr' *)
	(*  83 *) g_apasHARTUnitCode[83, 1] := ADR(asHARTUnitCodeAbbr[83]); (* 'lb/day' *)
	(*  84 *) g_apasHARTUnitCode[84, 1] := ADR(asHARTUnitCodeAbbr[84]); (* 'ShTon/min' *)
	(*  85 *) g_apasHARTUnitCode[85, 1] := ADR(asHARTUnitCodeAbbr[85]); (* 'ShTon/hr' *)
	(*  86 *) g_apasHARTUnitCode[86, 1] := ADR(asHARTUnitCodeAbbr[86]); (* 'ShTon/day' *)
	(*  87 *) g_apasHARTUnitCode[87, 1] := ADR(asHARTUnitCodeAbbr[87]); (* 'LTon/hr' *)
	(*  88 *) g_apasHARTUnitCode[88, 1] := ADR(asHARTUnitCodeAbbr[88]); (* 'LTon/day' *)
	(*  89 *) g_apasHARTUnitCode[89, 1] := ADR(asHARTUnitCodeAbbr[89]); (* 'DekaTherm' *)
	(*  90 *) g_apasHARTUnitCode[90, 1] := ADR(asHARTUnitCodeAbbr[90]); (* 'SGU' *)
	(*  91 *) g_apasHARTUnitCode[91, 1] := ADR(asHARTUnitCodeAbbr[91]); (* 'g/cm3' *)
	(*  92 *) g_apasHARTUnitCode[92, 1] := ADR(asHARTUnitCodeAbbr[92]); (* 'kg/m3' *)
	(*  93 *) g_apasHARTUnitCode[93, 1] := ADR(asHARTUnitCodeAbbr[93]); (* 'lb/gal' *)
	(*  94 *) g_apasHARTUnitCode[94, 1] := ADR(asHARTUnitCodeAbbr[94]); (* 'lb/ft3' *)
	(*  95 *) g_apasHARTUnitCode[95, 1] := ADR(asHARTUnitCodeAbbr[95]); (* 'g/ml' *)
	(*  96 *) g_apasHARTUnitCode[96, 1] := ADR(asHARTUnitCodeAbbr[96]); (* 'kg/l' *)
	(*  97 *) g_apasHARTUnitCode[97, 1] := ADR(asHARTUnitCodeAbbr[97]); (* 'g/l' *)
	(*  98 *) g_apasHARTUnitCode[98, 1] := ADR(asHARTUnitCodeAbbr[98]); (* 'lb/CuIn' *)
	(*  99 *) g_apasHARTUnitCode[99, 1] := ADR(asHARTUnitCodeAbbr[99]); (* 'ShTon/CuYd' *)
	(* 100 *) g_apasHARTUnitCode[100, 1] := ADR(asHARTUnitCodeAbbr[100]); (* '�Twad' *)
	(* 101 *) g_apasHARTUnitCode[101, 1] := ADR(asHARTUnitCodeAbbr[101]); (* '�Brix' *)
	(* 102 *) g_apasHARTUnitCode[102, 1] := ADR(asHARTUnitCodeAbbr[102]); (* '�BaumHv' *)
	(* 103 *) g_apasHARTUnitCode[103, 1] := ADR(asHARTUnitCodeAbbr[103]); (* '�BaumLt' *)
	(* 104 *) g_apasHARTUnitCode[104, 1] := ADR(asHARTUnitCodeAbbr[104]); (* '�API' *)
	(* 105 *) g_apasHARTUnitCode[105, 1] := ADR(asHARTUnitCodeAbbr[105]); (* '%Sol/wt' *)
	(* 106 *) g_apasHARTUnitCode[106, 1] := ADR(asHARTUnitCodeAbbr[106]); (* '%Sol/vol' *)
	(* 107 *) g_apasHARTUnitCode[107, 1] := ADR(asHARTUnitCodeAbbr[107]); (* '�Ball' *)
	(* 108 *) g_apasHARTUnitCode[108, 1] := ADR(asHARTUnitCodeAbbr[108]); (* 'proof/vol' *)
	(* 109 *) g_apasHARTUnitCode[109, 1] := ADR(asHARTUnitCodeAbbr[109]); (* 'proof/mass' *)
	(* 110 *) g_apasHARTUnitCode[110, 1] := ADR(asHARTUnitCodeAbbr[110]); (* 'bush' *)
	(* 111 *) g_apasHARTUnitCode[111, 1] := ADR(asHARTUnitCodeAbbr[111]); (* 'yd3' *)
	(* 112 *) g_apasHARTUnitCode[112, 1] := ADR(asHARTUnitCodeAbbr[112]); (* 'ft3' *)
	(* 113 *) g_apasHARTUnitCode[113, 1] := ADR(asHARTUnitCodeAbbr[113]); (* 'in3' *)
	(* 114 *) g_apasHARTUnitCode[114, 1] := ADR(asHARTUnitCodeAbbr[114]); (* 'in/s' *)
	(* 115 *) g_apasHARTUnitCode[115, 1] := ADR(asHARTUnitCodeAbbr[115]); (* 'in/min' *)
	(* 116 *) g_apasHARTUnitCode[116, 1] := ADR(asHARTUnitCodeAbbr[116]); (* 'ft/min' *)
	(* 117 *) g_apasHARTUnitCode[117, 1] := ADR(asHARTUnitCodeAbbr[117]); (* 'deg/s' *)
	(* 118 *) g_apasHARTUnitCode[118, 1] := ADR(asHARTUnitCodeAbbr[118]); (* 'rev/s' *)
	(* 119 *) g_apasHARTUnitCode[119, 1] := ADR(asHARTUnitCodeAbbr[119]); (* 'rpm' *)
	(* 120 *) g_apasHARTUnitCode[120, 1] := ADR(asHARTUnitCodeAbbr[120]); (* 'mtr/hr' *)
	(* 121 *) g_apasHARTUnitCode[121, 1] := ADR(asHARTUnitCodeAbbr[121]); (* 'm3/hr' *)
	(* 122 *) g_apasHARTUnitCode[122, 1] := ADR(asHARTUnitCodeAbbr[122]); (* 'l/hr' *)
	(* 123 *) g_apasHARTUnitCode[123, 1] := ADR(asHARTUnitCodeAbbr[123]); (* 'ft3/min' *)
	(* 124 *) g_apasHARTUnitCode[124, 1] := ADR(asHARTUnitCodeAbbr[124]); (* 'bblLiq' *)
	(* 125 *) g_apasHARTUnitCode[125, 1] := ADR(asHARTUnitCodeAbbr[125]); (* 'ounce' *)
	(* 126 *) g_apasHARTUnitCode[126, 1] := ADR(asHARTUnitCodeAbbr[126]); (* 'ftpf' *)
	(* 127 *) g_apasHARTUnitCode[127, 1] := ADR(asHARTUnitCodeAbbr[127]); (* 'kW' *)
	(* 128 *) g_apasHARTUnitCode[128, 1] := ADR(asHARTUnitCodeAbbr[128]); (* 'kWh' *)
	(* 129 *) g_apasHARTUnitCode[129, 1] := ADR(asHARTUnitCodeAbbr[129]); (* 'HP' *)
	(* 130 *) g_apasHARTUnitCode[130, 1] := ADR(asHARTUnitCodeAbbr[130]); (* 'ft3/hr' *)
	(* 131 *) g_apasHARTUnitCode[131, 1] := ADR(asHARTUnitCodeAbbr[131]); (* 'm3/min' *)
	(* 132 *) g_apasHARTUnitCode[132, 1] := ADR(asHARTUnitCodeAbbr[132]); (* 'bbl/s' *)
	(* 133 *) g_apasHARTUnitCode[133, 1] := ADR(asHARTUnitCodeAbbr[133]); (* 'bbl/min' *)
	(* 134 *) g_apasHARTUnitCode[134, 1] := ADR(asHARTUnitCodeAbbr[134]); (* 'bbl/hr' *)
	(* 135 *) g_apasHARTUnitCode[135, 1] := ADR(asHARTUnitCodeAbbr[135]); (* 'bbl/day' *)
	(* 136 *) g_apasHARTUnitCode[136, 1] := ADR(asHARTUnitCodeAbbr[136]); (* 'gal/hr' *)
	(* 137 *) g_apasHARTUnitCode[137, 1] := ADR(asHARTUnitCodeAbbr[137]); (* 'ImpGal/s' *)
	(* 138 *) g_apasHARTUnitCode[138, 1] := ADR(asHARTUnitCodeAbbr[138]); (* 'l/hr' *)
	(* 139 *) g_apasHARTUnitCode[139, 1] := ADR(asHARTUnitCodeAbbr[139]); (* 'ppm' *)
	(* 140 *) g_apasHARTUnitCode[140, 1] := ADR(asHARTUnitCodeAbbr[140]); (* 'MCal/hr' *)
	(* 141 *) g_apasHARTUnitCode[141, 1] := ADR(asHARTUnitCodeAbbr[141]); (* 'MJ/hr' *)
	(* 142 *) g_apasHARTUnitCode[142, 1] := ADR(asHARTUnitCodeAbbr[142]); (* 'BTU/hr' *)
	(* 143 *) g_apasHARTUnitCode[143, 1] := ADR(asHARTUnitCodeAbbr[143]); (* '�' *)		
	(* 144 *) g_apasHARTUnitCode[144, 1] := ADR(asHARTUnitCodeAbbr[144]); (* 'Rads' *)
	(* 145 *) g_apasHARTUnitCode[145, 1] := ADR(asHARTUnitCodeAbbr[145]); (* 'in' *)
	(* 146 *) g_apasHARTUnitCode[146, 1] := ADR(asHARTUnitCodeAbbr[146]); (* 'ug/lt' *)
	(* 147 *) g_apasHARTUnitCode[147, 1] := ADR(asHARTUnitCodeAbbr[147]); (* 'ug/lt3' *)
	(* 148 *) g_apasHARTUnitCode[148, 1] := ADR(asHARTUnitCodeAbbr[148]); (* '%' *)
	(* 149 *) g_apasHARTUnitCode[149, 1] := ADR(asHARTUnitCodeAbbr[149]); (* '%' *)
	(* 150 *) g_apasHARTUnitCode[150, 1] := ADR(asHARTUnitCodeAbbr[150]); (* '%StmQual' *) 
	(* 151 *) g_apasHARTUnitCode[151, 1] := ADR(asHARTUnitCodeAbbr[151]); (* 'Ftin16' *)   
	(* 152 *) g_apasHARTUnitCode[152, 1] := ADR(asHARTUnitCodeAbbr[152]); (* 'ft3/lb' *)   
	(* 153 *) g_apasHARTUnitCode[153, 1] := ADR(asHARTUnitCodeAbbr[153]); (* 'pF' *)       
	(* 154 *) g_apasHARTUnitCode[154, 1] := ADR(asHARTUnitCodeAbbr[154]); (* 'mlt/lt' *)
	(* 155 *) g_apasHARTUnitCode[155, 1] := ADR(asHARTUnitCodeAbbr[155]); (* 'ult/lt' *)
	(* 160 *) g_apasHARTUnitCode[160, 1] := ADR(asHARTUnitCodeAbbr[160]); (* '%Plato' *)  
	(* 161 *) g_apasHARTUnitCode[161, 1] := ADR(asHARTUnitCodeAbbr[161]); (* '%StmQual' *)
	(* 162 *) g_apasHARTUnitCode[162, 1] := ADR(asHARTUnitCodeAbbr[162]); (* 'MCal' *) 
	(* 163 *) g_apasHARTUnitCode[163, 1] := ADR(asHARTUnitCodeAbbr[163]); (* 'kOhm' *)
	(* 164 *) g_apasHARTUnitCode[164, 1] := ADR(asHARTUnitCodeAbbr[164]); (* 'MJ' *)   
	(* 165 *) g_apasHARTUnitCode[165, 1] := ADR(asHARTUnitCodeAbbr[165]); (* 'BTU' *)  
	(* 166 *) g_apasHARTUnitCode[166, 1] := ADR(asHARTUnitCodeAbbr[166]); (* 'm3' *)   
	(* 167 *) g_apasHARTUnitCode[167, 1] := ADR(asHARTUnitCodeAbbr[167]); (* 'lt' *)
	(* 168 *) g_apasHARTUnitCode[168, 1] := ADR(asHARTUnitCodeAbbr[168]); (* 'ft3' *)
	(* 169 *) g_apasHARTUnitCode[169, 1] := ADR(asHARTUnitCodeAbbr[169]); (* 'parts/bilion' *)
	(* 170-219 - HART spec. expansion table *)
	(* 235 *) g_apasHARTUnitCode[235, 1] := ADR(asHARTUnitCodeAbbr[170]); (* 'Gal/day' *)
	(* 236 *) g_apasHARTUnitCode[236, 1] := ADR(asHARTUnitCodeAbbr[171]); (* 'hlt' *)
	(* 237 *) g_apasHARTUnitCode[237, 1] := ADR(asHARTUnitCodeAbbr[172]); (* 'MPa' *)
	(* 238 *) g_apasHARTUnitCode[238, 1] := ADR(asHARTUnitCodeAbbr[173]); (* 'in' *)
	(* 239 *) g_apasHARTUnitCode[239, 1] := ADR(asHARTUnitCodeAbbr[174]); (* 'mm' *)
	(* 240-249 - manufacturer specific defs. *)    
	(* 250 *) g_apasHARTUnitCode[250, 1] := ADR(asHARTUnitCodeAbbr[175]); (* '' *)
	(* 251 *) g_apasHARTUnitCode[251, 1] := ADR(asHARTUnitCodeAbbr[176]); (* '-' *)      
	(* 252 *) g_apasHARTUnitCode[252, 1] := ADR(asHARTUnitCodeAbbr[177]); (* '?' *)
	(* 253 *) g_apasHARTUnitCode[253, 1] := ADR(asHARTUnitCodeAbbr[178]); (* 'spec' *)

END_IF
               `   , � � ��           HART_VERSION ��ST	��ST      ��������        m  FUNCTION HART_VERSION : WORD
(*
 date     | release	| author  | Desc
----------+---------+------------------------------------------------------------
 15.11.07 |  0.8	| KD      | Init     
 04.12.07 |  0.9	| MP      | Redesign    
 07.01.08 |  1.0	| CM      | Implementation finished  
 14.01.08 |  1.1	| CM      | BugFix - HART_MBX 
 17.01.08 |  1.2	| CM 	  | Add 'UNIVERSAL COMMANDS IN HART REVISION 5' 
 28.03.08 |  1.3	| CM 	  | Put 'ADDR_LONG' into each request
 28.03.08 |  1.4	| CM 	  | Add HART_CMD15
 29.04.08 |  2.0	| JK 	  | Couplers 750-841, 750-842 and 750-833 compatible
          |         |         | BugFix - DateFormat
          |         |         | Add HART_CMD6,HART_CMD11,HART_CMD14;
          |         |         | Module/sensor Response code analysis
 26.06.08 |  2.1    | CM      | BugFix - "Undefined response code error"
 28.07.08 |  3.0    | CM      | Drop Input "xReset" for a better handling
 30.07.08 |  3.1    | CM      | Add 'COMMON PRACTICE COMMANDS'
 10.10.08 |  3.2    | JK      | Module/sensor error and response codes are ignored in HART_INFO
 25.02.09 |  3.3    | JK      | Modify MODE-DETECTION in "HART_INFO" to support 750-484
 25.03.09 |  3.4    | CM      | Add "gc_bRetries" for retransmission on communication errors
 04.05.09 |  3.5    | CM      | Extend 'COMMON PRACTICE COMMANDS'
 14.06.10 |  3.6    | CM      | Reset "dwError" in case of retransmission
 10.04.14 |  3.7    | CM      | Add "gc_xAccept_CTRL_PositiveWithoutData" for Fuji-HART-Sensors
 *)
VAR_INPUT
END_VAR
VAR
	(* Current library: version *)
	bMajor : BYTE := 16#03;
	bMinor : BYTE := 16#07;
END_VARE   HART_VERSION := SHL(BYTE_TO_WORD(bMajor), 8) OR BYTE_TO_WORD(bMinor);               �   , x  �           PLC_PRG ��ST	��ST      ��������        
  PROGRAM PLC_PRG
(* Complex program for 750-841 *)

VAR
	wCurrentAI1 AT %IW4 : WORD; (* raw 4..20mA Signal *)
	rCurrentAI1 : REAL;

	dwCountSuccessful : DWORD;
	dwCountError : DWORD;

	(* Operate with module *)
	bModule : BYTE := 3;
	bChannel: BYTE := 1;

	(* Identication of HART-modules and access synchronisation *)
	xInfoReset : BOOL;
	dwInfoError : DWORD;
	sInfoStatus: STRING;

	(* FDT-DTM-Interface *)
	xFdtReset : BOOL;
	bFdtMsgId : BYTE;
	dwFdtError : DWORD;
	sFdtStatus: STRING;

	(* HART lib version *)
	wHartLibVersion : WORD;



	(* HART CMD0 *)
	oCmd0 	   : HART_CMD0;
	stCmd0Data : tHART_CMD0;
	xCmd0Start : BOOL ;
	dwCmd0Error: DWORD;
	sCmd0Status: STRING;

	(* HART CMD1 *)
	oCmd1 	   : HART_CMD1;
	stCmd1Data : tHART_CMD1;
	xCmd1Start : BOOL ;
	dwCmd1Error: DWORD;
	sCmd1Status: STRING;

	(* HART CMD2 *)
	oCmd2 	   : HART_CMD2;
	stCmd2Data : tHART_CMD2;
	xCmd2Start : BOOL ;
	dwCmd2Error: DWORD;
	sCmd2Status: STRING;

	(* HART CMD3 *)
	oCmd3 	   : HART_CMD3;
	stCmd3Data : tHART_CMD3;
	xCmd3Start : BOOL ;
	dwCmd3Error: DWORD;
	sCmd3Status: STRING;
	oFtrigCmd3 : F_TRIG; (* Detects falling edge  cycled execution of CMD3 *)
	oTonCmd3   : TON; (* Timer for cycled execution of CMD3 *)

	(* HART CMD6 *)
	oCmd6		: HART_CMD6;
	bCmd6PollingAdr: BYTE := 10;
	xCmd6Start	: BOOL ;
	sCmd6Status	: STRING;
	dwCmd6Error	: DWORD;

	(* HART CMD11 *)
	oCmd11		: HART_CMD11;
	stCmd11Data : tHART_CMD0;
	sCmd11Tag 	: STRING(8) := 'TI XXX  ';
	xCmd11Start	: BOOL := TRUE;
	sCmd11Status: STRING;
	dwCmd11Error: DWORD;

	(* HART CMD12 *)
	oCmd12		: HART_CMD12;
	xCmd12Start	: BOOL := TRUE;
	dwCmd12Error: DWORD;
	sCmd12Status: STRING;
	sCmd12Msg 	: STRING;

	(* HART CMD13 *)
	oCmd13 	  	: HART_CMD13;
	stCmd13Data : tHART_CMD13;
	xCmd13Start : BOOL := TRUE;
	dwCmd13Error: DWORD;
	sCmd13Status: STRING;

	(* HART CMD14 *)
	oCmd14		: HART_CMD14;
	stCmd14Data : tHART_CMD14;
	xCmd14Start	: BOOL := TRUE;
	sCmd14Status: STRING;
	dwCmd14Error: DWORD;

	(* HART CMD15 *)
	oCmd15 	  	: HART_CMD15;
	stCmd15Data : tHART_CMD15;
	xCmd15Start : BOOL := TRUE;
	dwCmd15Error: DWORD;
	sCmd15Status: STRING;

	(* HART CMD16 *)
	oCmd16 	  	: HART_CMD16;
	dwCmd16FAN 	: DWORD;
	xCmd16Start : BOOL := TRUE;
	dwCmd16Error: DWORD;
	sCmd16Status: STRING;

	(* HART CMD17 *)
	oCmd17 	  	: HART_CMD17;
	dwCmd17Msg 	: STRING(32) := 'This is Wago PLC message';
	xCmd17Start : BOOL := TRUE;
	dwCmd17Error: DWORD;
	sCmd17Status: STRING;

	(* HART CMD18 *)
	oCmd18 	  	: HART_CMD18;
	dwCmd18Data : tHART_CMD13 := (sTag := 'TI XXX 1',
								  sDescriptor := 'description IJK ',
								  dDate := d#2008-07-30);
	xCmd18Start : BOOL := TRUE;
	dwCmd18Error: DWORD;
	sCmd18Status: STRING;
	oFtrigCmd18 : F_TRIG;
	oTonCmd18 : TON;

	(* HART CMD19 *)
	oCmd19 	  	: HART_CMD19;
	dwCmd19FAN 	: DWORD := 13;
	xCmd19Start : BOOL := TRUE;
	dwCmd19Error: DWORD;
	sCmd19Status: STRING;

	(* HART CMD33 *)
	oCmd33 	   : HART_CMD33;
	xCmd33Start : BOOL ;
	dwCmd33Error: DWORD;
	sCmd33Status: STRING;
	stCmd33DataSlot0 : tHART_CMD1;
	stCmd33DataSlot1 : tHART_CMD1;
	stCmd33DataSlot2 : tHART_CMD1;
	stCmd33DataSlot3 : tHART_CMD1;

	(* HART CMD44 *)
	oCmd44 	   : HART_CMD44;
	xCmd44Start : BOOL ;
	dwCmd44Error: DWORD;
	sCmd44Status: STRING;

	(* HART CMD48 *)
	oCmd48 	   : HART_CMD48;
	stCmd48Data : tHART_CMD48;
	xCmd48Start : BOOL ;
	dwCmd48Error: DWORD;
	sCmd48Status: STRING;

	(* HART CMD50 *)
	oCmd50 	   : HART_CMD50;
	xCmd50Start : BOOL ;
	dwCmd50Error: DWORD;
	sCmd50Status: STRING;
	bCmd50VarCodePrimary : BYTE;
	bCmd50VarCodeSecondary : BYTE;
	bCmd50VarCodeTertiary : BYTE;
	bCmd50VarCode4th : BYTE;

	(* HART CMD51 *)
	oCmd51 	   : HART_CMD51;
	xCmd51Start : BOOL ;
	dwCmd51Error: DWORD;
	sCmd51Status: STRING;
	bCmd51VarCodePrimary : BYTE;
	bCmd51VarCodeSecondary : BYTE;
	bCmd51VarCodeTertiary : BYTE;
	bCmd51VarCode4th : BYTE;

	(* HART CMD53 *)
	oCmd53 	   : HART_CMD53;
	xCmd53Start : BOOL ;
	dwCmd53Error: DWORD;
	sCmd53Status: STRING;
END_VAR'      ???�CalcCurrent          c(* This program  identifies all connected HART-modules and coordinate the MailBox communication. *)???TRUEA
xInfoReset	HART_INFO  sInfoStatus      dwInfoError    (* Read all variables *)oCmd3bModulebChannelA
xCmd3Start	HART_CMD3  sCmd3Status 
stCmd3Data      dwCmd3Error     oCmd44bModulebChannel15AxCmd44Start
HART_CMD44  sCmd44Status      dwCmd44Error     oCmd50bModulebChannelAxCmd50Start
HART_CMD50  sCmd50Status bCmd50VarCodePrimary bCmd50VarCodeSecondary bCmd50VarCodeTertiary bCmd50VarCode4th      dwCmd50Error     oCmd51bModulebChannel1032AxCmd51Start
HART_CMD51  sCmd51Status      dwCmd51Error     oCmd53bModulebChannel126AxCmd53Start
HART_CMD53  sCmd53Status      dwCmd53Error     oCmd33bModulebChannel0123AxCmd33Start
HART_CMD33  sCmd33Status stCmd33DataSlot0 stCmd33DataSlot1 stCmd33DataSlot2 stCmd33DataSlot3      dwCmd33Error     TRUE     oCmd48bModule1AxCmd48Start
HART_CMD48  sCmd48Status stCmd48Data      dwCmd48Error     oCmd0bModule2A
xCmd0Start	HART_CMD0  sCmd0Status 
stCmd0Data      dwCmd0Error    ;(* This program work as gateway for wago841-HART-FDT-DTM *)???At#40sHART_FDT  
dwFdtError 
sFdtStatus      	bFdtMsgId    (* HART library version *)�HART_VERSION  wHartLibVersion    (* Read primary variable *)oCMD1bModulebChannelA
xCmd1Start	HART_CMD1  sCmd1Status 
stCmd1Data      dwCmd1Error    '(* Read current and percent of range *)oCMD2bModulebChannelA
xCmd2Start	HART_CMD2  sCmd2Status 
stCmd2Data      dwCmd2Error    (* Read all variables *)oCmd3bModulebChannelA
xCmd3Start	HART_CMD3  sCmd3Status 
stCmd3Data      dwCmd3Error     	CMD3_BUSY�
oFtrigCmd3A
xCmd3StartF_TRIG           
ON_ERROR_3dwCmd3ErrorA16#0000NE     dwCountSuccessfulA1ADD  dwCountSuccessful     	CMD3_BUSYTRUE    
ON_ERROR_3dwCountErrorA1ADD  dwCountError    
CMD3_BUSY oTonCmd3�
xCmd3StartAt#1sTON        
xCmd3Start     TRUE    (* Write polling address *)oCmd6bModulebChannelbCmd6PollingAdrA
xCmd6Start	HART_CMD6  sCmd6Status      dwCmd6Error    6(* Read unique identifier associated with input tag *)oCmd11bModulebChannel	sCmd11TagAxCmd11Start
HART_CMD11  sCmd11Status stCmd11Data      dwCmd11Error    (* Read message *)oCmd12bModulebChannelAxCmd12Start
HART_CMD12  sCmd12Status 	sCmd12Msg      dwCmd12Error    #(* Read tag, descriptor and date *)oCmd13bModulebChannelAxCmd13Start
HART_CMD13  sCmd13Status stCmd13Data      dwCmd13Error    �(* Read sensor serial number,Units code for sensor limits and minimum span, Upper sensor limit, Lower sensor limit, Minimum span *)oCmd14bModulebChannelAxCmd14Start
HART_CMD14  sCmd14Status stCmd14Data      dwCmd14Error    (* Read output information *)oCmd15bModulebChannelAxCmd15Start
HART_CMD15  sCmd15Status stCmd15Data      dwCmd15Error     (* Read final assembly number *)oCmd16bModulebChannelAxCmd16Start
HART_CMD16  sCmd16Status 
dwCmd16FAN      dwCmd16Error    (* Write message *)oCmd17bModulebChannel
dwCmd17MsgAxCmd17Start
HART_CMD17  sCmd17Status      dwCmd17Error    $(* Write tag, descriptor and date *)oCmd18bModulebChanneldwCmd18DataAxCmd18Start
HART_CMD18  sCmd18Status      dwCmd18Error     
CMD18_BUSY�oFtrigCmd18AxCmd18StartF_TRIG           ON_ERROR_18dwCmd18ErrorA16#0000NE     dwCountSuccessfulA1ADD  dwCountSuccessful     
CMD18_BUSYTRUE    ON_ERROR_18dwCountErrorA1ADD  dwCountError    
CMD18_BUSY	oTonCmd18�xCmd18StartAt#30sTON        xCmd18Start    !(* Write final assembly number *)oCmd19bModulebChannel
dwCmd19FANAxCmd19Start
HART_CMD19  sCmd19Status      dwCmd19Errord    A   , , , f�           CalcCurrent ��ST�   (* Berechnung des 4..20mA Signal aus Prozesswert:
		0 	  ==>  4mA  
		32765 ==> 20mA
*)
rCurrentAI1 := 4 + (((20-4)/32765.0)*WORD_TO_REAL(wCurrentAI1));
               ����, _ >h         "   mod_com.lib 2.12.10 13:48:32 @���L#   Standard.lib 2.12.10 13:48:34 @���L)   SYSLIBCALLBACK.LIB 2.12.10 13:48:32 @���L   ]   ADD_PI_INFORMATION @      ADD_DESC       MODULE_INFO       MODULE_INFO_ACCESS                   CRC16 @           FBUS_ERROR_INFORMATION @           GET_DIGITAL_INPUT_OFFSET @           GET_DIGITAL_OUTPUT_OFFSET @           KBUS_ERROR_INFORMATION @           MOD_COM_VERSION @           PI_INFORMATION @           READ_INPUT_BIT @           READ_INPUT_WORD @           READ_OUTPUT_BIT @           READ_OUTPUT_WORD @           SET_DIGITAL_INPUT_OFFSET @           SET_DIGITAL_OUTPUT_OFFSET @           SLAVE_ADDRESS @           WRITE_OUTPUT_BIT @           WRITE_OUTPUT_WORD @              Globale_Variablen @           !   ASCIIBYTE_TO_STRING @                  CONCAT @        	   CTD @        	   CTU @        
   CTUD @           DELETE @           F_TRIG @        
   FIND @           INSERT @        
   LEFT @        	   LEN @        	   MID @           R_TRIG @           REAL_STATE @          REPLACE @           RIGHT @           RS @        	   RTC @        
   SEMA @           SR @           STANDARD_VERSION @          STRING_COMPARE @          STRING_TO_ASCIIBYTE @       	   TOF @        	   TON @           TP @              Global Variables 0 @           b   SysCallbackRegister @   	   RTS_EVENT       RTS_EVENT_FILTER       RTS_EVENT_SOURCE                   SysCallbackUnregister @              Globale_Variablen @           Version @                          ��������         ��2                ����������������  
             ����  ��������        ����  ��������                      POUs	            
   CMD_Custom                 HART_CMDCustom  Y   ����              CMDs_CommonPractice              
   HART_CMD33  o                
   HART_CMD34  B                
   HART_CMD35  K                
   HART_CMD38  f                
   HART_CMD40  g                
   HART_CMD44  r                
   HART_CMD45  i                
   HART_CMD46  j                
   HART_CMD48  m                
   HART_CMD50  p                
   HART_CMD51  q                
   HART_CMD53  s   ����              CMDs_Universal              	   HART_CMD0  H                	   HART_CMD1  S                
   HART_CMD11  M                
   HART_CMD12  _                
   HART_CMD13  R                
   HART_CMD14  D                
   HART_CMD15  X                
   HART_CMD16  N                
   HART_CMD17  a                
   HART_CMD18  ]                
   HART_CMD19  b                	   HART_CMD2  T                	   HART_CMD3  ^                	   HART_CMD6  �   ����            
   Convert_To                 HART_b2UnitSymbol  V                   HART_b2UnitText  U                   HART_DATE2pab  �                   HART_pab2DATE  Q                   HART_pab2DWORD  E                   HART_pab2dwSerialNumber  �                   HART_pab2REAL  J                   HART_pab2sDesc  h                   HART_pab2sMsg  k                   HART_pab2sTag  l                   HART_REAL2pab  C                   HART_STRING2pab  |   ����              Private                 HART_CheckModuleResponseCode  �                   HART_CheckSensorResponseCode  �                   HART_MBX  G                   HART_UnitCodeStrings  �   ����                HART_FDT  W               	   HART_INFO  /                   HART_VERSION  `                  PLC_PRG                CalcCurrent  A   �   ����           
   Data types              	   tHART_2AI  P                   tHART_2AI_MODE8  O                
   tHART_CMD0  F                
   tHART_CMD1  Z                   tHART_CMD13  [                  tHART_CMD14  L                   tHART_CMD15  d                
   tHART_CMD2  \                
   tHART_CMD3  I                   tHART_CMD35  e                   tHART_CMD48  n                	   tHART_FDT  c   ����             Visualizations  ����             Global Variables                 Globale_Variablen     ����                                         ��������             T�ST�.             �.                	   localhost            P      	   localhost            P      	   localhost            P     a�ST   �cqo