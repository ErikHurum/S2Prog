#include "TSNIncludes.h"
#pragma hdrstop
//---------------------------------------------------------------------------
NewLanguageWord EnglishDictionary[]=
{
//  { Keyword   ,English (0)
    { L_WORD0   ,L"FEIL-FEIL-"},
    { L_WORD1   ,L"Enable"},
    { L_WORD2   ,L"Disable"},
    { L_WORD3   ,L"On"},
    { L_WORD4   ,L"Off"},
    { L_WORD5   ,L"Printer"},
    { L_WORD6   ,L"Language:"},
    { L_WORD7   ,L"Alarms"},
    { L_WORD8   ,L"Ballast exchange"},
    { L_WORD9   ,L"Cargo"},
    { L_WORD10  ,L"Service"},
    { L_WORD11  ,L"Temperature"},
    { L_WORD12  ,L"Tank pressure"},
    { L_WORD13  ,L"Select logging:"},
    { L_WORD14  ,L"Logging time"},
    { L_WORD15  ,L"Hours"},
    { L_WORD16  ,L"Printer setup"},
    { L_WORD17  ,L"Open"},
    { L_WORD18  ,L"Close"},
    { L_WORD19  ,L"Log period"},
    { L_WORD20  ,L"System page 1"},
    { L_WORD21  ,L"User manual"},
    { L_WORD22  ,L"Setup"},
    { L_WORD23  ,L"Printer"},
    { L_WORD24  ,L"Program version"},
    { L_WORD25  ,L"Data version:"},
    { L_WORD26  ,L"System ID:"},
    { L_WORD27  ,L"Unit System:"},
    { L_WORD28  ,L"Language"},
    { L_WORD29  ,L"GMT"},
    { L_WORD30  ,L"System page 2"},
    { L_WORD31  ,L"Atmospheric ref."},
    { L_WORD32  ,L"meter"},
    { L_WORD33  ,L"Trim source:"},
    { L_WORD34  ,L"degree"},
    { L_WORD35  ,L"Draft:"},
    { L_WORD36  ,L"Unit"},
    { L_WORD37  ,L"Seawater"},
    { L_WORD38  ,L"List source:"},
    { L_WORD39  ,L"System page 3: IO units"},
    { L_WORD40  ,L"Select:"},
    { L_WORD41  ,L"System page 4: Hardware units"},
    { L_WORD42  ,L"System page 5"},
    { L_WORD43  ,L"Total for all tanks"},
    { L_WORD44  ,L"Volume"},
    { L_WORD45  ,L"Weight"},
    { L_WORD46  ,L"Water"},
    { L_WORD47  ,L"Ballast"},
    { L_WORD48  ,L"Heavy fuel oil"},
    { L_WORD49  ,L"Diesel oil"},
    { L_WORD50  ,L"Lubricants"},
    { L_WORD51  ,L"Fresh water"},
    { L_WORD52  ,L"Miscellaneous"},
    { L_WORD53  ,L"Grand total"},
    { L_WORD54  ,L"System setup page"},
    { L_WORD55  ,L"Screen saver:"},
    { L_WORD56  ,L"minutes"},
    { L_WORD57  ,L"Alarm off delay:"},
    { L_WORD58  ,L"seconds"},
    { L_WORD59  ,L"SI unit"},
    { L_WORD60  ,L"US unit"},
    { L_WORD61  ,L"Set color:"},
    { L_WORD62  ,L"Background"},
    { L_WORD63  ,L"Foreground"},
    { L_WORD64  ,L"Brightness:"},
    { L_WORD65  ,L"Buzzer /\nLight test"},
    { L_WORD66  ,L"Change PIN code"},
    { L_WORD67  ,L"Calibrate screen"},
    { L_WORD68  ,L"EEPROM"},
    { L_WORD69  ,L"Application setup"},
    { L_WORD70  ,L"Col. 1"},
    { L_WORD71  ,L"Col. 2"},
    { L_WORD72  ,L"Col. 3"},
    { L_WORD73  ,L"Col. 4"},
    { L_WORD74  ,L"Name "},
    { L_WORD75  ,L"Zero adjust tank\n pressure sensor for\n all ballast tanks."},
    { L_WORD76  ,L"Zero adjust level\n sensor(s) for\n all ballast tanks."},
    { L_WORD77  ,L"Ballast water density"},
    { L_WORD78  ,L"Zero adjust tank\n pressure sensor for\n all cargo tanks."},
    { L_WORD79  ,L"Zero adjust level\n sensor(s) for\n all cargo tanks."},
    { L_WORD80  ,L"Density for:"},
    { L_WORD81  ,L"Zero adjust tank\n pressure sensor for\n all tank pressure points."},
    { L_WORD82  ,L"Common input for all Ballast tanks"},
    { L_WORD83  ,L"Density"},
    { L_WORD84  ,L"Configuration Error"},
    { L_WORD85  ,L"Text"},
    { L_WORD86  ,L"Continue"},
    { L_WORD87  ,L"PageUp"},
    { L_WORD88  ,L"PageDn"},
    { L_WORD89  ,L"App.Setup"},
    { L_WORD90  ,L"Detail"},
    { L_WORD91  ,L"\nUnknown error in Configuration."},
    { L_WORD92  ,L"Cargo line pressure"},
    { L_WORD93  ,L"Vapour return line"},
    { L_WORD94  ,L"Water Ingress Detection"},
    { L_WORD95  ,L"Level switch"},
    { L_WORD96  ,L"System"},
    { L_WORD97  ,L"Alarm"},
    { L_WORD98  ,L"Apply\n group"},
    { L_WORD99  ,L"Not Configured"},
    { L_WORD100 ,L"Not in use"},
    { L_WORD101 ,L"Linear"},
    { L_WORD102 ,L"API / ASTM-IP"},
    { L_WORD103 ,L"Use measured density"},
    { L_WORD104 ,L"Reference temperature"},
    { L_WORD105 ,L"Use reference density"},
    { L_WORD106 ,L"Reference 1"},
    { L_WORD107 ,L"Reference 2"},
    { L_WORD108 ,L"Coefficient"},
    { L_WORD109 ,L"Overfill"},
    { L_WORD110 ,L"High Level"},
    { L_WORD111 ,L"Low Level"},
    { L_WORD112 ,L"Hi Tmp Lim"},
    { L_WORD113 ,L"Lo Tmp Lim"},
    { L_WORD114 ,L"High Tank Press"},
    { L_WORD115 ,L"Low Tank Press"},
    { L_WORD116 ,L"Zero adjust tank \npressure sensor"},
    { L_WORD117 ,L"Zero adjust level \nsensor(s)."},
    { L_WORD118 ,L"Adjust Level"},
    { L_WORD119 ,L"Adjust Sounding"},
    { L_WORD120 ,L"Adjust Ullage"},
    { L_WORD121 ,L"Adjust Volume"},
    { L_WORD122 ,L"Adjust Weight"},
    { L_WORD123 ,L"Unlock"},
    { L_WORD124 ,L"Location"},
    { L_WORD125 ,L"Ena"},
    { L_WORD126 ,L"Gain"},
    { L_WORD127 ,L"Offset"},
    { L_WORD128 ,L"Value"},
    { L_WORD129 ,L"New Value"},
    { L_WORD130 ,L"Confirm operation"},
    { L_WORD131 ,L"Apply current density settings to all cargo tanks."},
    { L_WORD132 ,L"Apply current density settings to all ballast tanks."},
    { L_WORD133 ,L"Apply current density settings to all service tanks."},
    { L_WORD134 ,L"New Alarm limit"},
    { L_WORD135 ,L"Apply current alarm settings to all cargo tanks."},
    { L_WORD136 ,L"Apply current alarm settings to all ballast tanks"},
    { L_WORD137 ,L"Apply current alarm settings to all Service tanks"},
    { L_WORD138 ,L"Apply current alarm settings to all Tank pressure"},
    { L_WORD139 ,L"Apply current alarm settings to all Temperature points"},
    { L_WORD140 ,L"Zero adjust sensor"},
    { L_WORD141 ,L"The sensor must be vented to atmosphere"},
    { L_WORD142 ,L"Zero adjust level sensor(s)!"},
    { L_WORD143 ,L"The tank must be empty and no tank cleaning has been carried out the last 30 min."},
    { L_WORD144 ,L"Protection plate!"},
    { L_WORD145 ,L"Observed Level"},
    { L_WORD146 ,L"Observed Sounding"},
    { L_WORD147 ,L"Observed Ullage"},
    { L_WORD148 ,L"Observed Volume"},
    { L_WORD149 ,L"Observed Weight"},
    { L_WORD150 ,L"Enter PIN code:"},
    { L_WORD151 ,L"Set sensor gain"},
    { L_WORD152 ,L"Set sensor value"},
    { L_WORD153 ,L"Warning"},
    { L_WORD154 ,L"You are about to adjust the sensor gain. This may affect the accuracy!"},
    { L_WORD155 ,L"You are about to adjust the sensor. This may affect the accuracy!"},
    { L_WORD156 ,L"Zero adjust"},
    { L_WORD157 ,L"Sensor values"},
    { L_WORD158 ,L"High Line Press"},
    { L_WORD159 ,L"Low Line Press"},
    { L_WORD160 ,L"Zero adjust line \npressure sensor"},
    { L_WORD161 ,L"OK"},
    { L_WORD162 ,L"Yes"},
    { L_WORD163 ,L"No"},
    { L_WORD164 ,L"Continue?"},
    { L_WORD165 ,L"Detail view warning:"},
    { L_WORD166 ,L"Select a tank by pressing on the row and push Detail button."},
    { L_WORD167 ,L"< Prev"},
    { L_WORD168 ,L"Next >"},
    { L_WORD169 ,L"Ackn."},
    { L_WORD170 ,L"Description"},
    { L_WORD171 ,L"Raised"},
    { L_WORD172 ,L"Reset"},
    { L_WORD173 ,L"No Alarm"},
    { L_WORD174 ,L"Set date (dd.mm.yy)"},
    { L_WORD175 ,L"Set time (hh.mm.ss)"},
    { L_WORD176 ,L"Fault in insert of Time!"},
    { L_WORD177 ,L"Time format (h.m.s)"},
    { L_WORD178 ,L"Fault in insert of Date"},
    { L_WORD179 ,L"Date format (d.m.y)"},
    { L_WORD180 ,L"Enter new value:"},
    { L_WORD181 ,L"No value"},
    { L_WORD182 ,L"No sensor(s)"},
    { L_WORD183 ,L"Enter trim. (Aft is -)"},
    { L_WORD184 ,L"Enter list. (Port is -)"},
    { L_WORD185 ,L"Enter new density:"},
    { L_WORD186 ,L"0"},
    { L_WORD187 ,L"1"},
    { L_WORD188 ,L"Error"},
    { L_WORD189 ,L"Auto"},
    { L_WORD190 ,L"Manual"},
    { L_WORD191 ,L"No Error"},
    { L_WORD192 ,L"Input error"},
    { L_WORD193 ,L"Density error"},
    { L_WORD194 ,L"RefTmp1=RefTmp2"},
    { L_WORD195 ,L"RefTmp1 fixed"},
    { L_WORD196 ,L"Wrong coeff"},
    { L_WORD197 ,L"Value is too high"},
    { L_WORD198 ,L"Value is too low"},
    { L_WORD199 ,L"Use API"},
    { L_WORD200 ,L"Use ref.density 1"},
    { L_WORD201 ,L"Select API table"},
    { L_WORD202 ,L"Illegal pointer"},
    { L_WORD203 ,L"Illegal value"},
    { L_WORD204 ,L"Unknown tank"},
    { L_WORD205 ,L"AD not found"},
    { L_WORD206 ,L"No tmp sensor"},
    { L_WORD207 ,L"Value out of range"},
    { L_WORD208 ,L"Use system seawater"},
    { L_WORD209 ,L"Use system ballast"},
    { L_WORD210 ,L"Lo temp=Hi temp"},
    { L_WORD211 ,L"Input not allowed"},
    { L_WORD212 ,L"Undefined Cargo"},
    { L_WORD213 ,L"Retry input"},
    { L_WORD214 ,L"Ref Dns1 too low"},
    { L_WORD215 ,L"Ref Dns1 too high"},
    { L_WORD216 ,L"Ref Dns2 too low"},
    { L_WORD217 ,L"Ref Dns2 too high"},
    { L_WORD218 ,L"API out of range"},
    { L_WORD219 ,L"Sensor Error"},
    { L_WORD220 ,L"Gain out of range"},
    { L_WORD221 ,L"Use sys fresh water"},
    { L_WORD222 ,L"Use sys heavy fuel"},
    { L_WORD223 ,L"Use system diesel"},
    { L_WORD224 ,L"Use sys lubricants"},
    { L_WORD225 ,L"Low > High limit"},
    { L_WORD226 ,L"High < Low limit"},
    { L_WORD227 ,L"High = Low limit"},
    { L_WORD228 ,L"Not adjustable"},
    { L_WORD229 ,L"No input permission"},
    { L_WORD230 ,L"Sensor is disabled"},
    { L_WORD231 ,L"Use API53 table"},
    { L_WORD232 ,L"Use API54 table"},
    { L_WORD233 ,L"Use ref.density 2"},
    { L_WORD234 ,L"Can't use common input"},
    { L_WORD235 ,L"Override only possible when there are alarm on either Pre or Main"},
    { L_WORD236 ,L"No Unit"},
    { L_WORD237 ,L""/*Blank*/},
    { L_WORD238 ,L"Length"},
    { L_WORD239 ,L"Atm/Vapour pressure"},
    { L_WORD240 ,L"Cargo/Ballast press"},
    { L_WORD241 ,L"Line pressure"},
    { L_WORD242 ,L"Density coef."},
    { L_WORD243 ,L"Angle"},
    { L_WORD244 ,L"Free surface"},
    { L_WORD245 ,L"Moment"},
    { L_WORD246 ,L"Immersion"},
    { L_WORD247 ,L"Loadrate"},
    { L_WORD248 ,L"Percent"},
    { L_WORD249 ,L"GZ area"},
    { L_WORD250 ,L"Current"},
    { L_WORD251 ,L"Voltage"},
    { L_WORD252 ,L"Time"},
    { L_WORD253 ,L"mSeconds"},
    { L_WORD254 ,L"Days"},
    { L_WORD255 ,L"feet"},
    { L_WORD256 ,L"d.feet"},
    { L_WORD257 ,L"m�"},
    { L_WORD258 ,L"litre"},
    { L_WORD259 ,L"US g."},
    { L_WORD260 ,L"US bls"},
    { L_WORD261 ,L"ton"},
    { L_WORD262 ,L"l.ton"},
    { L_WORD263 ,L"kN"},
    { L_WORD264 ,L"m�/h"},
    { L_WORD265 ,L"USb/h"},
    { L_WORD266 ,L"�C"},
    { L_WORD267 ,L"�F"},
    { L_WORD268 ,L"mH2O"},
    { L_WORD269 ,L"mmH2O"},
    { L_WORD270 ,L"mBar"},
    { L_WORD271 ,L"Bar"},
    { L_WORD272 ,L"Psi"},
    { L_WORD273 ,L"kPa"},
    { L_WORD274 ,L"InH2O"},
    { L_WORD275 ,L"InHg"},
    { L_WORD276 ,L"t/m� vac"},
    { L_WORD277 ,L"t/m� air"},
    { L_WORD278 ,L"lb/usg"},
    { L_WORD279 ,L"Deg"},
    { L_WORD280 ,L"Rad"},
    { L_WORD281 ,L"t/m��C"},
    { L_WORD282 ,L"t/m��F"},
    { L_WORD283 ,L"l/g/�C"},
    { L_WORD284 ,L"l/g/�F"},
    { L_WORD285 ,L"m^4"},
    { L_WORD286 ,L"Feet^4"},
    { L_WORD287 ,L"t*m"},
    { L_WORD288 ,L"lton*Ft"},
    { L_WORD289 ,L"kNm"},
    { L_WORD290 ,L"t/cm"},
    { L_WORD291 ,L"lton/in"},
    { L_WORD292 ,L"m*Rad"},
    { L_WORD293 ,L"%"},
    { L_WORD294 ,L"�"},
    { L_WORD295 ,L"mAmp"},
    { L_WORD296 ,L"Amp"},
    { L_WORD297 ,L"Volt"},
    { L_WORD298 ,L"mVolt"},
    { L_WORD299 ,L"mSec"},
    { L_WORD300 ,L"Sec"},
    { L_WORD301 ,L"Min"},
    { L_WORD302 ,L"Hours"},
    { L_WORD303 ,L"Days"},
    { L_WORD304 ,L"Unused"},
    { L_WORD305 ,L"LevelSns"},
    { L_WORD306 ,L"LevelRef"},
    { L_WORD307 ,L"LevelFC"},
    { L_WORD308 ,L"Sounding"},
    { L_WORD309 ,L"Ullage"},
    { L_WORD310 ,L"Volume%"},
    { L_WORD311 ,L"Pressure"},
    { L_WORD312 ,L"High Press"},
    { L_WORD313 ,L"Low Press"},
    { L_WORD314 ,L"FinishTime"},
    { L_WORD315 ,L"RemTime"},
    { L_WORD316 ,L"CargoType"},
    { L_WORD317 ,L"Bot Press"},
    { L_WORD318 ,L"Mid Press"},
    { L_WORD319 ,L"Upp Press"},
    { L_WORD320 ,L"Top Press"},
    { L_WORD321 ,L"BP Gain"},
    { L_WORD322 ,L"MP Gain"},
    { L_WORD323 ,L"UP Gain"},
    { L_WORD324 ,L"TP Gain"},
    { L_WORD325 ,L"BP Offset"},
    { L_WORD326 ,L"MP Offset"},
    { L_WORD327 ,L"UP Offset"},
    { L_WORD328 ,L"TP Offset"},
    { L_WORD329 ,L"LevS"},
    { L_WORD330 ,L"LevR"},
    { L_WORD331 ,L"LevF"},
    { L_WORD332 ,L"Snd"},
    { L_WORD333 ,L"Ull"},
    { L_WORD334 ,L"Vol"},
    { L_WORD335 ,L"Vol%"},
    { L_WORD336 ,L"Wgt"},
    { L_WORD337 ,L"Dens"},
    { L_WORD338 ,L"Temp"},
    { L_WORD339 ,L"Pres"},
    { L_WORD340 ,L"HTmp"},
    { L_WORD341 ,L"LTmp"},
    { L_WORD342 ,L"HiPr"},
    { L_WORD343 ,L"LoPr"},
    { L_WORD344 ,L"LRate"},
    { L_WORD345 ,L"FTim"},
    { L_WORD346 ,L"RTim"},
    { L_WORD347 ,L"Ctyp"},
    { L_WORD348 ,L"BP"},
    { L_WORD349 ,L"MP"},
    { L_WORD350 ,L"UP"},
    { L_WORD351 ,L"TP"},
    { L_WORD352 ,L"BPGn"},
    { L_WORD353 ,L"MPGn"},
    { L_WORD354 ,L"UPGn"},
    { L_WORD355 ,L"TPGn"},
    { L_WORD356 ,L"BPOf"},
    { L_WORD357 ,L"MPOf"},
    { L_WORD358 ,L"UPOf"},
    { L_WORD359 ,L"TPOf"},
    { L_WORD360 ,L"Bot Tmp(T1)"},     // 0%
    { L_WORD361 ,L"Mid Tmp(T2)"},     //50%
    { L_WORD362 ,L"Upp Tmp(T3)"},     //85%
    { L_WORD363 ,L"Top Tmp"},
    { L_WORD364 ,L"T1"},
    { L_WORD365 ,L"T3"},
    { L_WORD366 ,L"T4"},
    { L_WORD367 ,L"TT"},
    { L_WORD368 ,L"Atm sensor"},
    { L_WORD369 ,L"Power 24V(1)"},
    { L_WORD370 ,L"Power 24V(2)"},
    { L_WORD371 ,L"Power 3.3V"},
    { L_WORD372 ,L"Power 1.8V"},
    { L_WORD373 ,L"OS Status"},
    { L_WORD374 ,L"Flash Status"},
    { L_WORD375 ,L"Task Name"},
    { L_WORD376 ,L"Running time"},
    { L_WORD377 ,L"Power 5.0V"},
    { L_WORD378 ,L"Power 12V"},
    { L_WORD379 ,L"Com Channel"},
    { L_WORD380 ,L"Com Version"},
    { L_WORD381 ,L"Store Ver."},
    { L_WORD382 ,L"Rx Buf Size"},
    { L_WORD383 ,L"Tx Buf Size"},
    { L_WORD384 ,L"Reset Status"},
    { L_WORD385 ,L"Total Restart"},
    { L_WORD386 ,L"Fail count"},
    { L_WORD387 ,L"Tot. fail cnt"},
    { L_WORD388 ,L"Program"},
    { L_WORD389 ,L"Power 24V"},
    { L_WORD390 ,L"Serial Number"},
    { L_WORD391 ,L"Unit status"},
    { L_WORD392 ,L"Card status"},
    { L_WORD393 ,L"Cargo Name"},
    { L_WORD394 ,L"VolCorrFactor"},
    { L_WORD395 ,L"VCF@Temp"},
    { L_WORD396 ,L"Measured API"},
    { L_WORD397 ,L"Comp. Density"},
    { L_WORD398 ,L"Ref.Density1"},
    { L_WORD399 ,L"Ref.Density2"},
    { L_WORD400 ,L"Ref. Temp1"},
    { L_WORD401 ,L"Ref. Temp2"},
    { L_WORD402 ,L"Not defined"},
    { L_WORD403 ,L"Simple"},
    { L_WORD404 ,L"AtmPress"},
    { L_WORD405 ,L"Ballast"},
    { L_WORD406 ,L"Heavy fuel"},
    { L_WORD407 ,L"Diesel"},
    { L_WORD408 ,L"Lubricants"},
    { L_WORD409 ,L"Fresh water"},
    { L_WORD410 ,L"Sea water"},
    { L_WORD411 ,L"API 6A"},
    { L_WORD412 ,L"API 6B"},
    { L_WORD413 ,L"API 6D"},
    { L_WORD414 ,L"API 53A"},
    { L_WORD415 ,L"API 53B"},
    { L_WORD416 ,L"API 53D"},
    { L_WORD417 ,L"API 54A"},
    { L_WORD418 ,L"API 54B"},
    { L_WORD419 ,L"API 54D"},
    { L_WORD420 ,L"DF"},
    { L_WORD421 ,L"DP"},
    { L_WORD422 ,L"DS"},
    { L_WORD423 ,L"DA"},
   // { L_WORD424 ,L"Level"},
    { L_WORD425 ,L"Trim in deg"},
    { L_WORD426 ,L"Trim in meter"},
    { L_WORD427 ,L"List in deg"},
    { L_WORD428 ,L"DF (User select)"},
    { L_WORD429 ,L"DA (User select)"},
    { L_WORD430 ,L"DF@Mark"},
    { L_WORD431 ,L"DA@Mark"},
    { L_WORD432 ,L"DF@PP"},
    { L_WORD433 ,L"DA@PP"},
    { L_WORD434 ,L"On/Off"},
    { L_WORD435 ,L"System data"},
    { L_WORD436 ,L"Drafts"},
    { L_WORD437 ,L"Cargo tank"},
    { L_WORD438 ,L"Other tanks"},
    { L_WORD439 ,L"FRO"},
    { L_WORD440 ,L"G1"},
    { L_WORD441 ,L"G2"},
    { L_WORD442 ,L"G3"},
    { L_WORD443 ,L"NL1"},
    { L_WORD444 ,L"NL2"},
    { L_WORD445 ,L"Lev"},
    { L_WORD446 ,L"Meas. Density"},
    { L_WORD447 ,L"List in meter"},
    { L_WORD448 ,L"Latitude"},
    { L_WORD449 ,L"Type"},
    { L_WORD450 ,L"SnsDB"},
    { L_WORD451 ,L"Placing"},
    { L_WORD452 ,L"MinRange"},
    { L_WORD453 ,L"MaxRange"},
    { L_WORD454 ,L"CableLength"},
    { L_WORD455 ,L"TCUAddress"},
    { L_WORD456 ,L"Port"},
    { L_WORD457 ,L"IOAddress"},
    { L_WORD458 ,L"Channel"},
    { L_WORD459 ,L"ADCardChn"},
    { L_WORD460 ,L"Trim"},
    { L_WORD461 ,L"List"},
    { L_WORD462 ,L"Black"},
    { L_WORD463 ,L"Dark Gray"},
    { L_WORD464 ,L"Light Gray"},
    { L_WORD465 ,L"White"},
    { L_WORD466 ,L"Blue"},
    { L_WORD467 ,L"Print"},
    { L_WORD468 ,L"S"   /*Status*/},
    { L_WORD469 ,L"Use bls"},
    { L_WORD470 ,L"Use m�"},
    { L_WORD471 ,L"Dry"},
    { L_WORD472 ,L"--.-"},
    { L_WORD473 ,L"Empty"},
    { L_WORD474 ,L"*****"   /*fixed length!*/},
    { L_WORD475 ,L"Main"},
    { L_WORD476 ,L"Pre"},
    { L_WORD477 ,L"Over"},
    { L_WORD478 ,L"Prot"},
    { L_WORD479 ,L"Com"},
    { L_WORD480 ,L"(Rx/Tx)"},
    { L_WORD481 ,L"on TCU:"},
    { L_WORD482 ,L"on ZB485:"},
    { L_WORD483 ,L"BootLoader"},
    { L_WORD484 ,L"Application"},
    { L_WORD485 ,L"Unknown"},
    { L_WORD486 ,L"None"},
    { L_WORD487 ,L"Err"},
    { L_WORD488 ,L"NoUs"},
    { L_WORD489 ,L"Other"},
    { L_WORD490 ,L"Press"},
    { L_WORD491 ,L"@PP"},
    { L_WORD492 ,L"@Mark"},
    { L_WORD493 ,L"Deact."},
    { L_WORD494 ,L"Active"},
    { L_WORD495 ,L"Ackn."},
    { L_WORD496 ,L"Lim:"},
    { L_WORD497 ,L"Val:"},
    { L_WORD498 ,L"Pointer Error"},
    { L_WORD499 ,L"Unk."},
    { L_WORD500 ,L"OutOfRange"},
    { L_WORD501 ,L"ComFault"},
    { L_WORD502 ,L"HLev"},
    { L_WORD503 ,L"HighLevel"},
    { L_WORD504 ,L"HighLinePress"},
    { L_WORD505 ,L"HLPr"},
    { L_WORD506 ,L"HighPressure"},
    { L_WORD507 ,L"HPre"},
    { L_WORD508 ,L"HighTemp"},
    { L_WORD509 ,L"HTmp"},
    { L_WORD510 ,L"High Voltage"},
    { L_WORD511 ,L"HVolt"},
    { L_WORD512 ,L"X Hi Press1"},
    { L_WORD513 ,L"XHiP1"},
    { L_WORD514 ,L"X Lo Press1"},
    { L_WORD515 ,L"XLoP1"},
    { L_WORD516 ,L"ComFault"},
    { L_WORD517 ,L"IOErr"},
    { L_WORD518 ,L"LowLevel"},
    { L_WORD519 ,L"LLev"},
    { L_WORD520 ,L"LowLinePress"},
    { L_WORD521 ,L"LLPr"},
    { L_WORD522 ,L"LowPressure"},
    { L_WORD523 ,L"LPre"},
    { L_WORD524 ,L"Low Temp"},
    { L_WORD525 ,L"LTmp"},
    { L_WORD526 ,L"Low Voltage"},
    { L_WORD527 ,L"LVolt"},
    { L_WORD528 ,L"Failure"},
    { L_WORD529 ,L"MainWater"},
    { L_WORD530 ,L"MWat"},
    { L_WORD531 ,L"OpenLoop"},
    { L_WORD532 ,L"oloop"},
  //  { L_WORD109 ,L"Overfill"},
    { L_WORD534 ,L"OFill"},
    { L_WORD535 ,L"PreWater"},
    { L_WORD536 ,L"PWat"},
    { L_WORD537 ,L"RangeError"},
    { L_WORD538 ,L"ADErr"},
    { L_WORD539 ,L"Cnv&Cal Error"},
    { L_WORD540 ,L"HWErr"},
    { L_WORD541 ,L"Conv Error"},
    { L_WORD542 ,L"RaErr"},
    { L_WORD543 ,L"ShortCircuit"},
    { L_WORD544 ,L"Scirc"},
    { L_WORD545 ,L"Details"},
    { L_WORD546 ,L"Calibration Data"},
    { L_WORD547 ,L"SerNum"},
    { L_WORD548 ,L"Range"},
    { L_WORD549 ,L"CalData Source"},
    { L_WORD550 ,L"Level offset"},
    { L_WORD551 ,L"Inclinometer"},
    { L_WORD552 ,L"Draft"},
    { L_WORD553 ,L"Measured"},
    { L_WORD554 ,L"ch"},
    { L_WORD555 ,L"Loc"},
    { L_WORD556 ,L"RawVal"},
    { L_WORD557 ,L"CalVal"},
    { L_WORD558 ,L"CnvCalE"},
    { L_WORD559 ,L"PROM"},
    { L_WORD560 ,L"PC"},
    { L_WORD561 ,L"TCUCal"},
    { L_WORD562 ,L"AD Sns"},
    { L_WORD563 ,L"TCU Sns"},
    { L_WORD564 ,L"From TCU"},
    { L_WORD565 ,L"Green"},
    { L_WORD566 ,L"Erasing FLASH"},
    { L_WORD567 ,L"Info"},
    { L_WORD568 ,L"Erasing Failure"},
    { L_WORD569 ,L"Updating program,please wait..."},
    { L_WORD570 ,L"Runtime calibration,\n please touch the screen\n at the center of the ring"},
    { L_WORD571 ,L"Abort"},
    { L_WORD572 ,L"Press here"},
    { L_WORD573 ,L"(upper left position)"},
    { L_WORD574 ,L"(lower right position)"},
    { L_WORD575 ,L"Page"},
    { L_WORD576 ,L"Data version"},
    { L_WORD577 ,L"Cargo tanks"},
    { L_WORD578 ,L"Ballast tanks"},
    { L_WORD579 ,L"Service tanks"},
    { L_WORD580 ,L"Heavy Fuel Oil tanks"},
    { L_WORD581 ,L"Diesel Oil tanks"},
    { L_WORD582 ,L"Lubricant tanks"},
    { L_WORD583 ,L"Miscellaneous tanks"},
    { L_WORD584 ,L"Freshwater tanks"},
    { L_WORD585 ,L"NotDef"},
    { L_WORD586 ,L"Atm"},
    { L_WORD587 ,L"Bottom"},
    { L_WORD588 ,L"Middle"},
    { L_WORD589 ,L"Upper"},
    { L_WORD590 ,L"TankPress"},
    { L_WORD591 ,L"PumpRm"},
    { L_WORD592 ,L"EngRm"},
    { L_WORD593 ,L"Deck"},
    { L_WORD594 ,L"Deck"},
    { L_WORD595 ,L"Line"},
    { L_WORD596 ,L"WIMain"},
    { L_WORD597 ,L"WIPre"},
    { L_WORD598 ,L"Inc"},
    { L_WORD599 ,L"LSw"},
    { L_WORD600 ,L"Rad"},
    { L_WORD601 ,L"WIng"},
    { L_WORD602 ,L"Zero adjust tank pressure!"},
    { L_WORD603 ,L"The tanks must be vented to the atmosphere. This operation affects all tanks in group."},
    { L_WORD604 ,L"Zero adjust sensor(s)!"},
    { L_WORD605 ,L"The tanks must be empty and no tank cleaning the last 30 minutes. This operation affects all tanks in group."},
    { L_WORD606 ,L"Zeroset warning:"},
    { L_WORD607 ,L"The tanks must be vented to the atmosphere. This operation affects all tank pressure points."},
    { L_WORD608 ,L"The tanks must be empty and no tank cleaning the last 30 minutes. This operation affects all tank pressure points."},
    { L_WORD609 ,L"Heavy fuel density"},
    { L_WORD610 ,L"Diesel oil density"},
    { L_WORD611 ,L"Lubricants density"},
    { L_WORD612 ,L"Fresh water density"},
    { L_WORD613 ,L" File truncated"},
    { L_WORD614 ,L"Error in UNICODE string!"},
    { L_WORD615 ,L"F "},
    { L_WORD616 ,L"A "},
    { L_WORD617 ,L"P "},
    { L_WORD618 ,L"S "},
    { L_WORD619 ,L"Even"},
    { L_WORD620 ,L"Printer on this TDU"},
    { L_WORD621 ,L"Temperatures"},
    { L_WORD622 ,L"Line pressures"},
    { L_WORD623 ,L"Tank pressures"},
    { L_WORD624 ,L"CnvCal"},
    { L_WORD625 ,L"CnvErr"},
    { L_WORD626 ,L"CalErr"},
    { L_WORD627 ,L"TDU"},
    { L_WORD628 ,L"PC"},
    { L_WORD629 ,L"TCU"},
    { L_WORD630 ,L"ANPro3"},
    { L_WORD631 ,L"ANPro10"},
    { L_WORD632 ,L"IOsystem"},
    { L_WORD633 ,L"ZB_Red"},
    { L_WORD634 ,L"Wago"},
    { L_WORD635 ,L"TPCx"},
    { L_WORD636 ,L"Printer"},
    { L_WORD637 ,L"ANPro1"},
    { L_WORD638 ,L"ANPro3"},
    { L_WORD639 ,L"ANPro10"},
    { L_WORD640 ,L"Modbus"},
    { L_WORD641 ,L"Printer"},
    { L_WORD642 ,L"Void space"},
    { L_WORD643 ,L"Zero adjust void space\n pressure sensor for\n all void spaces."},
    { L_WORD644 ,L"Zero adjust level\n sensor(s) for\n all void spaces."},
    { L_WORD646 ,L"Apply current density settings to all void spaces."},
    { L_WORD647 ,L"Apply current alarm settings to all void spaces"},
    { L_WORD648 ,L"Leakage"},
    { L_WORD649 ,L"Leak"},
    { L_WORD650 ,L"Please wait"},
    { L_WORD651 ,L"Wait"},
    { L_WORD652 ,L"DST"},
    { L_WORD653 ,L"24V"},
    { L_WORD654 ,L"In#1"},
    { L_WORD655 ,L"In#2"},
    { L_WORD656 ,L"The system will be adjusted to the inserted value. Incorrect entry will cause malfunction of the system."},
    { L_WORD657 ,L"Warning! Adjust Level"},
    { L_WORD658 ,L"Warning! Adjust Sounding"},
    { L_WORD659 ,L"Warning! Adjust Ullage"},
    { L_WORD660 ,L"Warning! Adjust Volume"},
    { L_WORD661 ,L"Warning! Adjust Weight"},
    { L_WORD662 ,L"The protection plate must be installed on the sensor."},
    { L_WORD663 ,L"The protection plate must be removed from the sensor."},
    { L_WORD664 ,L"Enter Pin code:"},
    { L_WORD665 ,L"Enter new pin code:"},
    { L_WORD666 ,L"Screen saver time, min."},
    { L_WORD667 ,L"Alarm delay time, sec."},
    { L_WORD668 ,L"Enter old pin code:"},
    { L_WORD669 ,L"Re-enter new pin code:"},
    { L_WORD670 ,L"ComErr Id"       },
    { L_WORD671 ,L"ComErr Cmd"  },
    { L_WORD672 ,L"ComErr Msg"  },
    { L_WORD673 ,L"ComErr Cnt"  },
    { L_WORD674 ,L"ComErr Time" },
    { L_WORD675 ,L"Command"},
    { L_WORD676 ,L"Object"},
    { L_WORD677 ,L"Level"},
    { L_WORD678 ,L"Lvl"},
    { L_WORD679 ,L"Displacement"},
    { L_WORD680 ,L"LCG"},
    { L_WORD681 ,L"TCG"},
    { L_WORD682 ,L"VCG"},
    { L_WORD683 ,L"List in meter"},
    { L_WORD684 ,L"Draft Mid"},
    { L_WORD685 ,L"Liquid weight"},
    { L_WORD686 ,L"Solid weight"},
    { L_WORD687 ,L"Draft P"},
    { L_WORD688 ,L"TFS Moment"},
    { L_WORD689 ,L"L moment"},
    { L_WORD690 ,L"T moment"},
    { L_WORD691 ,L"V moment"},
    { L_WORD692 ,L"VCG Solids"},
    { L_WORD693 ,L"VCG adjust"},
    { L_WORD694 ,L"Max VCG"},
    { L_WORD695 ,L"VCG margin"},
    { L_WORD696 ,L"Dam.max VCG"},
    { L_WORD697 ,L"Dam. VCG marg."},
    { L_WORD698 ,L"Immersion"},
    { L_WORD699 ,L"KM"},
    { L_WORD700 ,L"GM solid"},
    { L_WORD701 ,L"GM liquid"},
    { L_WORD702 ,L"TCF"},
    { L_WORD703 ,L"LCF"},
    { L_WORD704 ,L"TCG"},
    { L_WORD705 ,L"LCG"},
    { L_WORD706 ,L"GZ"},
    { L_WORD707 ,L"GZ30"},
    { L_WORD708 ,L"GZ max"},
    { L_WORD709 ,L"GZ angle"},
    { L_WORD710 ,L"GZ a0-30"},
    { L_WORD711 ,L"GZ a30-40"},
    { L_WORD712 ,L"Flooding angle"},
    { L_WORD713 ,L"Deadweight"},
    { L_WORD714 ,L"LCB"},
    { L_WORD715 ,L"MaxBM@"},
    { L_WORD716 ,L"MaxSF@"},
    { L_WORD717 ,L"Frame"},
    { L_WORD718 ,L"Bend.Mom."},
    { L_WORD719 ,L"Shr.Forc."},
    { L_WORD720 ,L"Cor.BMom"},
    { L_WORD721 ,L"APP dist."},
    { L_WORD722 ,L"PrevFrame"},
    { L_WORD723 ,L"BMomHrb"},
    { L_WORD724 ,L"BMomSea"},
    { L_WORD725 ,L"SForceHrb"},
    { L_WORD726 ,L"SForceSea"},
    { L_WORD727 ,L"SteelWgt"},
    { L_WORD728 ,L"Buoyancy"},
    { L_WORD729 ,L"Load"},
    { L_WORD730 ,L"Mom.Change"},
    { L_WORD731 ,L"Avg BMom"},
    { L_WORD732 ,L"Avg SForce"},
    { L_WORD733 ,L"Solids"},
    { L_WORD734 ,L"Draft fore"},
    { L_WORD735 ,L"Draft port"},
    { L_WORD736 ,L"Draft stbd"},
    { L_WORD737 ,L"Draft aft"},
    { L_WORD738 ,L"TFree Surf."},
    { L_WORD739 ,L"FreeSMom."},
    { L_WORD740 ,L"GZ a0-40"},
    { L_WORD741 ,L"Constant solids"},
    { L_WORD742 ,L"Variable Solids"},
    { L_WORD743 ,L"VCF"},
    { L_WORD744 ,L"Vol@RefTmp"},
    { L_WORD745 ,L"V@RT"},
    { L_WORD746 ,L"Bytes:"},
    { L_WORD747 ,L"Level diff."},
    { L_WORD748 ,L"LDif"},
    { L_WORD749 ,L"Bottom1"},
    { L_WORD750 ,L"Bottom2"},
    { L_WORD751 ,L"Bottom3"},
    { L_WORD752 ,L"Bottom4"},
    { L_WORD753 ,L"Bottom5"},
    { L_WORD754 ,L"BP1"},
    { L_WORD755 ,L"BP2"},
    { L_WORD756 ,L"BP3"},
    { L_WORD757 ,L"BP Gain1"},
    { L_WORD758 ,L"BP Gain2"},
    { L_WORD759 ,L"BP Gain3"},
    { L_WORD760 ,L"BP Offset1"},
    { L_WORD761 ,L"BP Offset2"},
    { L_WORD762 ,L"BP Offset3"},
    { L_WORD763 ,L"Fail Address"},
    { L_WORD764 ,L"Online"},
    { L_WORD765 ,L"Offline"},
    { L_WORD766 ,L"Online Status"},
    { L_WORD767 ,L"Ship Upright"},
    { L_WORD768 ,L"Trim Angle"},
    { L_WORD769 ,L"List Angle"},
    { L_WORD770 ,L"Factory defaults"},
    { L_WORD771 ,L"TDUce"},
    { L_WORD772 ,L"Updating configuration,please wait..."},
    { L_WORD773 ,L"Progress"},
    { L_WORD774 ,L"High"},
    { L_WORD775 ,L"Low"},
    { L_WORD776 ,L"Capacity"},
    { L_WORD777 ,L"Cap"},
    { L_WORD778 ,L"Ovfill Lim"},
    { L_WORD779 ,L"HiLev Lim"},
    { L_WORD780 ,L"HiVol Lim"},
    { L_WORD781 ,L"HiVol%Lim"},
    { L_WORD782 ,L"HiWgt Lim"},
    { L_WORD783 ,L"HiUll Lim"},
    { L_WORD784 ,L"LoLev Lim"},
    { L_WORD785 ,L"LoVol Lim"},
    { L_WORD786 ,L"LoVol%Lim"},
    { L_WORD787 ,L"LoWgt Lim"},
    { L_WORD788 ,L"LoUll Lim"},
    { L_WORD789 ,L"HiTmp Lim"},
    { L_WORD790 ,L"LoTmp Lim"},
    { L_WORD791 ,L"HiPre Lim"},
    { L_WORD792 ,L"LoPre Lim"},
    { L_WORD793 ,L"DnsDifLim"},
    { L_WORD794 ,L"LevChgLim"},
    { L_WORD795 ,L"HiLRLim"},
    { L_WORD796 ,L"LoLRLim"},
    { L_WORD797 ,L"OvFill Ena"},
    { L_WORD798 ,L"HiLev Enable"},
    { L_WORD799 ,L"LoLev Enable"},
 //   { L_WORD800 ,L""},				// Free
    { L_WORD801 ,L"HiPre Enable"},
    { L_WORD802 ,L"LoPre Enable"},
    { L_WORD803 ,L"DnsDifEnable"},
    { L_WORD804 ,L"LevCh Enable"},
    { L_WORD805 ,L"Hi LR Enable"},
    { L_WORD806 ,L"Lo LR Enable"},
    { L_WORD807 ,L"Cargo info/settings"},
    { L_WORD808 ,L"Alarm limits"},
    { L_WORD809 ,L"Alarm on/off"},
    { L_WORD810 ,L"Sensor values"},
    { L_WORD811 ,L"Sensor status"},
    { L_WORD812 ,L"Separator"},
    { L_WORD813 ,L"Submenu End"},
    { L_WORD814 ,L"BP1 Enable"},
    { L_WORD815 ,L"BP2 Enable"},
    { L_WORD816 ,L"BP3 Enable"},
    { L_WORD817 ,L"BP Enable"},
    { L_WORD818 ,L"MP Enable"},
    { L_WORD819 ,L"UP Enable"},
    { L_WORD820 ,L"TP Enable"},
    { L_WORD821 ,L"Duplicate name"},
    { L_WORD822 ,L"T1 Gain"     },
    { L_WORD823 ,L"T3 Gain"     },
    { L_WORD824 ,L"T4 Gain"     },
    { L_WORD825 ,L"TT Gain"     },
    { L_WORD826 ,L"T1 Offset"   },
    { L_WORD827 ,L"T3 Offset"   },
    { L_WORD828 ,L"T4 Offset"   },
    { L_WORD829 ,L"TT Offset"   },
    { L_WORD830 ,L"T1"},
    { L_WORD831 ,L"T3"},
    { L_WORD832 ,L"T4"},
    { L_WORD833 ,L"TT"},
    { L_WORD834 ,L"T1Gn"},
    { L_WORD835 ,L"T3Gn"},
    { L_WORD836 ,L"T4Gn"},
    { L_WORD837 ,L"TTGn"},
    { L_WORD838 ,L"T1Of"},
    { L_WORD839 ,L"T3Of"},
    { L_WORD840 ,L"T4Of"},
    { L_WORD841 ,L"TTOf"},
    { L_WORD842 ,L"T1 Enable"},
    { L_WORD843 ,L"T3 Enable"},
    { L_WORD844 ,L"T4 Enable"},
    { L_WORD845 ,L"TT Enable"},
    { L_WORD846 ,L"IO sys Delay"},
    { L_WORD847 ,L"MetriTape"},
    { L_WORD848 ,L"Interface"},
    { L_WORD849 ,L"Intrf"},
    { L_WORD850 ,L"Watr"},
    { L_WORD851 ,L"NoSensor"},
    { L_WORD852 ,L"Disabled"},
    { L_WORD853 ,L"Normal LSw"},
    { L_WORD854 ,L"Seagoing"},
    { L_WORD855 ,L"Tank cleaning"},
    { L_WORD856 ,L"Opr. Mode"},
    { L_WORD857 ,L"Operation mode"},
    { L_WORD858 ,L"Undefined"},
    { L_WORD859 ,L"Cleaning"},
    { L_WORD860 ,L"Load"},
    { L_WORD861 ,L"Discharge"},
    { L_WORD862 ,L"WARNING: Selecting YES will deactivate all level switches!"},
    { L_WORD863 ,L"User"},
    { L_WORD864 ,L"MsrdDnsStat"},
    { L_WORD865 ,L"Duplicate name"},
    { L_WORD866 ,L"Level change"},
    { L_WORD867 ,L"LChng"},
    { L_WORD868 ,L"Adjust"},
    { L_WORD869 ,L"Saab"},
    { L_WORD870 ,L"Cargo tank"},
    { L_WORD871 ,L"Ballast tank"},
    { L_WORD872 ,L"Service tank"},
    { L_WORD873 ,L"Heavy Fuel Oil tank"},
    { L_WORD874 ,L"Diesel Oil tank"},
    { L_WORD875 ,L"Lubricant tank"},
    { L_WORD876 ,L"Freshwater tank"},
    { L_WORD877 ,L"Miscellaneous tank"},
    { L_WORD878 ,L"Set level offset"},
    { L_WORD879 ,L"Set sensor offset"},
    { L_WORD880 ,L"You are about to adjust the sensor offset. This may affect the accuracy!"},
    { L_WORD881 ,L"You are about to adjust the level offset. This will affect the accuracy!"},
    { L_WORD882 ,L"Redundancy"},
    { L_WORD883 ,L"Radar Threshold"},
    { L_WORD884 ,L"RTrH"},
    { L_WORD885 ,L"Cap 98%"},
    { L_WORD886 ,L"Cap 100%"},
    { L_WORD887 ,L"C98%"},
    { L_WORD888 ,L"C100%"},
    { L_WORD889 ,L"Fuse"},
    { L_WORD890 ,L"AC"},
    { L_WORD891 ,L"Batt"},
    { L_WORD892 ,L"broken"},
    { L_WORD893 ,L"Tanks"},
    { L_WORD894 ,L"Apply current density settings to all tanks."},
    { L_WORD895 ,L"Apply current alarm settings to all tanks."},
    { L_WORD896 ,L"Oil"},
    { L_WORD897 ,L"Power"},
    { L_WORD898 ,L"Low voltage"},
    { L_WORD899 ,L"X Hi Press1"},
    { L_WORD900 ,L"X Low Press1"},
    { L_WORD901 ,L"XHiP1"},
    { L_WORD902 ,L"XLoP1"},
    { L_WORD903 ,L"X HiPre1 Lim"},
    { L_WORD904 ,L"X LoPre1 Lim"},
    { L_WORD905 ,L"Roll periode"},
    { L_WORD906 ,L"Roll Frequency"},
    { L_WORD907 ,L"Max list P"},
    { L_WORD908 ,L"Max list S"},
    { L_WORD909 ,L"Frequency"},
    { L_WORD910 ,L"Hz"},
    { L_WORD911 ,L"Press AlState"},
    { L_WORD912 ,L"Adjustable"},
    { L_WORD913 ,L"PrVac/non-PO"},
    { L_WORD914 ,L"VapRet"},
    { L_WORD915 ,L"PAlStat"},
    { L_WORD916 ,L"Ullage UTI"},
    { L_WORD917 ,L"UTI"},
    { L_WORD918 ,L"Distance URef - UTI"},
    { L_WORD919 ,L"DUTI"},
    { L_WORD920 ,L"Write\nconfig file"},
    { L_WORD921 ,L"Use API59 table"},
    { L_WORD922 ,L"Use API60 table"},
    { L_WORD923 ,L"API 59A"},
    { L_WORD924 ,L"API 59B"},
    { L_WORD925 ,L"API 59D"},
    { L_WORD926 ,L"API 60A"},
    { L_WORD927 ,L"API 60B"},
    { L_WORD928 ,L"API 60D"},
    { L_WORD929 ,L"Test"},
    { L_WORD930 ,L"Tst"},
    { L_WORD931 ,L"Light"},
    { L_WORD932 ,L"Lgt"},
    { L_WORD933 ,L"Conv"},
    { L_WORD934 ,L"Cnv"},
    { L_WORD935 ,L"TSS"},
    { L_WORD936 ,L"TZS"},
    { L_WORD937 ,L"Entry"},
    { L_WORD938 ,L"Basic type"},
    { L_WORD939 ,L"API 53E"},
    { L_WORD940 ,L"API 54E"},
    { L_WORD941 ,L"API 59E"},
    { L_WORD942 ,L"API 60E"},
    { L_WORD943 ,L"VapWeight"},
    { L_WORD944 ,L"GasWeight"},
    { L_WORD945 ,L"VapWgt"},
    { L_WORD946 ,L"GasW"},
    { L_WORD947 ,L"Float"},
    { L_WORD948 ,L"Ammoniak"      },
    { L_WORD949 ,L"Butadien"      },
    { L_WORD950 ,L"Isobutylene"   },
    { L_WORD951 ,L"Propylene"     },
    { L_WORD952 ,L"Propenoxide"   },
    { L_WORD953 ,L"Vynilchloride" },
    { L_WORD954 ,L"Vol.Offset"},
    { L_WORD955 ,L"VOff"},
    { L_WORD956 ,L"NetVolume"},
    { L_WORD957 ,L"NVol"},
    { L_WORD958 ,L"NVol@Ref"},
    { L_WORD959 ,L"NVolR"},
    { L_WORD960 ,L"NetWeight"},
    { L_WORD961 ,L"NWgt"},
    { L_WORD962 ,L"Part Load"},
    { L_WORD963 ,L"Part Load"},
    { L_WORD964 ,L"Butane"          },
    { L_WORD965 ,L"Propane"         },
    { L_WORD966 ,L"N-Butane"        },
    { L_WORD967 ,L"ISO-Butane"      },
    { L_WORD968 ,L"1-Butene"        },
    { L_WORD969 ,L"Crude C4"        },
    { L_WORD970 ,L"Raffinate 1"     },
    { L_WORD971 ,L"Raffinate 2"     },
    { L_WORD972 ,L"Propylene Ref"   },
    { L_WORD973 ,L"Gasolie    "     },
    { L_WORD974 ,L"Flexicoker LPG"  },
    { L_WORD975 ,L"Sulphur-1"       },
    { L_WORD976 ,L"Sulphur-2"       },
    { L_WORD977 ,L"Sulphur-3"       },
    { L_WORD978 ,L"Sulphur-4"       },
    { L_WORD979 ,L"Sulphur-5"       },
    { L_WORD980 ,L"Sulphur-6"       },
    { L_WORD981 ,L"You are about to adjust the level offset. This will affect the accuracy!"},
    { L_WORD982 ,L"Set table offset"},
    { L_WORD983 ,L"Table offset"},
    { L_WORD984 ,L"Custom"},
    { L_WORD985 ,L"Temp1"},
    { L_WORD986 ,L"Temp2"},
    { L_WORD987 ,L"Temp3"},
    { L_WORD988 ,L"Temp4"},
    { L_WORD989 ,L"Temp5"},
    { L_WORD990 ,L"Temp6"},
    { L_WORD991 ,L"Temp7"},
    { L_WORD992 ,L"Temp8"},
    { L_WORD993 ,L"Temp9"},
    { L_WORD994 ,L"Temp10"},
    { L_WORD995 ,L"MolMass"},
    { L_WORD996 ,L"Air"},
    { L_WORD997 ,L"g/mol"},
    { L_WORD998 ,L"HartCom Error"},
    { L_WORD999 ,L"Sensor Adjust"},
    { L_WORD1000,L"Norm state"},
    { L_WORD1001,L"Threshold"},
    { L_WORD1002,L"Lock"},
    { L_WORD1003,L"Fail"},
    { L_WORD1004,L"Misc"},
    { L_WORD1005,L"You are about to adjust the experience factor. This will affect the accuracy!"},
    { L_WORD1006 ,L"Set experience factor"},
    { L_WORD1007 ,L"CPU Load Raw"},
    { L_WORD1008 ,L"CPU Load Avg"},
    { L_WORD1009 ,L"CPU Load Max"},
    { L_WORD1010, L"Meas.Dns(Raw)"},
    { L_WORD1011, L"WashTrack" },
    { L_WORD1012, L"Revolutions" },
    { L_WORD1013, L"RPM" },
    { L_WORD1014, L"RPS" },
    { L_WORD1015, L"Revolutions" },
    { L_WORD1016, L"PO-mode" },
    { L_WORD1017, L"" },        // Currently unused
    { L_WORD1018 ,L"X Hi Press2"},
    { L_WORD1019 ,L"X Lo Press2"},
    { L_WORD1020 ,L"XHiP2"},
    { L_WORD1021 ,L"XLoP2"},
    { L_WORD1022 ,L"X HiPre2 Lim"},
    { L_WORD1023 ,L"X LoPre2 Lim"},
    { L_WORD1024 ,L"Temp25%"}, // 25%
    { L_WORD1025 ,L"Temp100%"}, // 100%
    { L_WORD1026 ,L"Level1"  },
    { L_WORD1027 ,L"Level2"  },
    { L_WORD1028 ,L"Level3"  },
    { L_WORD1029 ,L"Level4"  },
    { L_WORD1030 ,L"Level5"  },
    { L_WORD1031 ,L"AvgLevel"},
    { L_WORD1032 ,L"Custody Transfer"},
    { L_WORD1033 ,L"Lower"      },
    { L_WORD1034 ,L"Higher"     },

    { L_WORD1035,L"T2 Gain"     },
    { L_WORD1036,L"T5 Gain"     },
    { L_WORD1037,L"T2 Offset"   },
    { L_WORD1038,L"T5 Offset"   },
    { L_WORD1039,L"T2"          },
    { L_WORD1040,L"T5"          },
    { L_WORD1041,L"T2Gn"        },
    { L_WORD1042,L"T5Gn"        },
    { L_WORD1043,L"T2Of"        },
    { L_WORD1044,L"T5Of"        },
    { L_WORD1045,L"T2 Enable"   },
    { L_WORD1046,L"T5 Enable"   },
    { L_WORD1047,L"TrimCorr"    },
    { L_WORD1048,L"ListCorr"    },
    { L_WORD1049,L"VaporTemp"   },
    { L_WORD1050, L"CorrLevel"  },
    { L_WORD1051, L"Hi PresVac" },
    { L_WORD1052, L"Lo PresVac" },
    { L_WORD1053, L"HPVac"      },
    { L_WORD1054, L"LPVac"      },
    { L_WORD1055, L"Hi VapRet"  },
    { L_WORD1056, L"Lo VapRet"  },
    { L_WORD1057, L"HVPRet"     },
    { L_WORD1058, L"LVPRet"     },
    { L_WORD1059, L"Non-PO mode" },
    { L_WORD1060, L"Hi BotTemp" },
    { L_WORD1061, L"Lo BotTemp" },
    { L_WORD1062, L"HBTmp"      },
    { L_WORD1063, L"LBTmp"      },
    { L_WORD1064 ,L"Ullage@Rad" },
    { L_WORD1065 ,L"URad" },
    { L_WORD1066 ,L"DFP" },
    { L_WORD1067 ,L"DFS" },
    { L_WORD1066 ,L"DAP" },
    { L_WORD1067 ,L"DAS" },
    { L_WORD1068 ,L"LvlOff" },
    { L_WORD1069 ,L"Ullage FC" },
    { L_WORD1070 ,L"UllFC" },
    { L_WORD1071 ,L"Set Online" },
    { L_WORD1072 ,L"Set Offline" },
    { L_WORD1073 ,L"Draft values" },
    { L_WORD1074 ,L"Tank values" },
    { L_WORD1075 ,L"LinePressure Values" },


    { L_WORD1076 ,L"BP Ser.no" },
    { L_WORD1077 ,L"BP1 Ser.no" },
    { L_WORD1078 ,L"BP2 Ser.no" },
    { L_WORD1079 ,L"BP3 Ser.no" },
    { L_WORD1080 ,L"MP Ser.no" },
    { L_WORD1081 ,L"UP Ser.no" },
    { L_WORD1082 ,L"TP Ser.no" },

    { L_WORD1083 ,L"Can't calc" },
    { L_WORD1084 ,L"Lev. offst" },
    { L_WORD1085 ,L"LVOff" },
    { L_WORD1086 ,L"Freeboard" },
    { L_WORD1087 ,L"Viscosity" },
    { L_WORD1088 ,L"Task Name" },
    { L_WORD1089 ,L"Task Stack"},
    { L_WORD1090 ,L"Task Number"},
    { L_WORD1091 ,L"Task Info"},
    { L_WORD1092 ,L"Task Load"},
    { L_WORD1093 ,L"Pa*s"},
    { L_WORD1094 ,L"P"},
    { L_WORD1095 ,L"cP"},
    { L_WORD1096 ,L"Cargo Color"},
    { L_WORD1097 ,L"Seawater temp"   },
    { L_WORD1098 ,L"Ambient temp"},
    { L_WORD1099, L"Hi InertGas"     },
    { L_WORD1100, L"Lo InertGas"     },
    { L_WORD1101, L"H IGP"      },
    { L_WORD1102, L"L IGP"      },
    { L_WORD1103, L"Inerted"      },
    { L_WORD1104, L"HiHiLinePress"},
    { L_WORD1105, L"HHLPr"},
    { L_WORD1106, L"LOLO Level"},
    { L_WORD1107, L"LLLev"},
    { L_WORD1108, L"LOLO Lev Lim"},
    { L_WORD1109, L"LOLO Vol Lim"},
    { L_WORD1110, L"LOLO Vol%Lim"},
    { L_WORD1111, L"LOLO Wgt Lim"},
    { L_WORD1112, L"LOLO Ull Lim"},

    { L_WORD1113, L"TempIn"},
    { L_WORD1114, L"TempOut"},
    { L_WORD1115, L"TankCleaning"},

    { L_WORD1116, L"Low speed"},
    { L_WORD1117, L"LoSpd"},
    { L_WORD1118, L"Preset time"},
    { L_WORD1119, L"PreTm"},
    { L_WORD1120, L"RPH"},
    { L_WORD1121, L"H:M:S"},
    { L_WORD1122, L"Tank No."},
    { L_WORD1123, L"TNo"},
    { L_WORD1124, L"Distance"},

};

unsigned WordsInEnglishDictionary = NELEMENTS(EnglishDictionary);

wchar_t EnglishUserManual[] = {L"           User manual for TDU\n\
\n\
For full information about the operation of the system, see the INSTALATION, INSTRUCTION AND OPERATION MANUAL.\n\
\n\
This touch screen shall be operated by a stylus pen or the finger tip. Other equipment/tools will damage the screen.\n\
\n\
NOTE:\n\
Before you start operating the system, the INSTRUCTION AND OPERATION MANUAL must be studied and understood.\n\
\n\
It is strongly recommended that you know the consequences of wrong use of the density system, alarm settings, alarm disabling and zero adjust of sensors.\n\
FAILURE to do this correct can cause overloading or damage.\n\
\n\
The manual and other spare parts can be ordered from:\n\
\n\
Scanjet Ariston AS\n\
Dokkvegen 10\n\
3920 Porsgrunn\n\
Norway \n\
\n\
Tel: +47 35 93 11 30\n\
Service: +47 958 78 644\n\
Fax: +47 35 93 11 31\n\
E-mail: service@ariston.no\n\
Web: www.ariston.no\n\
"};

int SizeOfEnglishUserManual= sizeof(EnglishUserManual);
