#include "TSNIncludes.h"
#pragma hdrstop
//---------------------------------------------------------------------------
NewLanguageWord EnglishDictionary[]=
{
//	{ Keyword	,English (0)
	{ L_WORD0   ,""},//"FEIL-FEIL-"},
	{ L_WORD1   ,""},//"Enable"},
	{ L_WORD2   ,""},//"Disable"},
	{ L_WORD3   ,""},//"On"},
	{ L_WORD4   ,""},//"Off"},
	{ L_WORD5   ,""},//"Printer"},
	{ L_WORD6   ,""},//"Language:"},
	{ L_WORD7   ,""},//"Alarms"},
	{ L_WORD8   ,""},//"Ballast exchange"},
	{ L_WORD9   ,""},//"Cargo"},
	{ L_WORD10  ,""},//"Service"},
	{ L_WORD11  ,""},//"Temperature"},
	{ L_WORD12  ,""},//"Tank pressure"},
	{ L_WORD13  ,""},//"Select logging:"},
	{ L_WORD14  ,""},//"Logging time"},
	{ L_WORD15  ,""},//"Hours"},
	{ L_WORD16  ,""},//"Printer setup"},
	{ L_WORD17  ,""},//"Open"},
	{ L_WORD18  ,""},//"Close"},
	{ L_WORD19  ,""},//"Log period"},
	{ L_WORD20  ,""},//"System page 1"},
	{ L_WORD21  ,""},//"User manual"},
	{ L_WORD22  ,""},//"Setup"},
	{ L_WORD23  ,""},//"Printer"},
	{ L_WORD24  ,""},//"Program version"},
	{ L_WORD25  ,""},//"Data version:"},
	{ L_WORD26  ,""},//"System ID:"},
	{ L_WORD27  ,""},//"Unit System:"},
	{ L_WORD28  ,""},//"Language"},
	{ L_WORD29  ,""},//"GMT"},
	{ L_WORD30  ,""},//"System page 2"},
	{ L_WORD31  ,""},//"Atmospheric ref."},
	{ L_WORD32  ,""},//"meter"},
	{ L_WORD33  ,""},//"Trim source:"},
	{ L_WORD34  ,""},//"degree"},
	{ L_WORD35  ,""},//"Draft:"},
	{ L_WORD36  ,""},//"Unit"},
	{ L_WORD37  ,""},//"Seawater"},
	{ L_WORD38  ,""},//"List source:"},
	{ L_WORD39  ,""},//"System page 3: IO units"},
	{ L_WORD40  ,""},//"Select:"},
	{ L_WORD41  ,""},//"System page 4: Hardware units"},
	{ L_WORD42  ,""},//"System page 5"},
	{ L_WORD43  ,""},//"Total for all tanks"},
	{ L_WORD44  ,""},//"Volume"},
	{ L_WORD45  ,""},//"Weight"},
	{ L_WORD46  ,""},//"Cargo"},
	{ L_WORD47  ,""},//"Ballast"},
	{ L_WORD48  ,""},//"Heavy fuel oil"},
	{ L_WORD49  ,""},//"Diesel oil"},
	{ L_WORD50  ,""},//"Lubricants"},
	{ L_WORD51  ,""},//"Fresh water"},
	{ L_WORD52  ,""},//"Miscellaneous"},
	{ L_WORD53  ,""},//"Grand total"},
	{ L_WORD54  ,""},//"System setup page"},
	{ L_WORD55  ,""},//"Screen saver:"},
	{ L_WORD56  ,""},//"minutes"},
	{ L_WORD57  ,""},//"Alarm off delay:"},
	{ L_WORD58  ,""},//"seconds"},
	{ L_WORD59  ,""},//"SI unit"},
	{ L_WORD60  ,""},//"US unit"},
	{ L_WORD61  ,""},//"Set color:"},
	{ L_WORD62  ,""},//"Background"},
	{ L_WORD63  ,""},//"Foreground"},
	{ L_WORD64  ,""},//"Brightness:"},
	{ L_WORD65  ,""},//"Buzzer /\nLight test"},
	{ L_WORD66  ,""},//"Change PIN code"},
	{ L_WORD67  ,""},//"Calibrate screen"},
	{ L_WORD68  ,""},//"EEPROM"},
	{ L_WORD69  ,""},//"Application setup"},
	{ L_WORD70  ,""},//"Col. 1"},
	{ L_WORD71  ,""},//"Col. 2"},
	{ L_WORD72  ,""},//"Col. 3"},
	{ L_WORD73  ,""},//"Col. 4"},
	{ L_WORD74  ,""},//"Name "},
	{ L_WORD75  ,""},//"Zero adjust tank\n pressure sensor for\n all ballast tanks."},
	{ L_WORD76  ,""},//"Zero adjust level\n sensor(s) for\n all ballast tanks."},
	{ L_WORD77  ,""},//"Ballast water density"},
	{ L_WORD78  ,""},//"Zero adjust tank\n pressure sensor for\n all cargo tanks."},
	{ L_WORD79  ,""},//"Zero adjust level\n sensor(s) for\n all cargo tanks."},
	{ L_WORD80  ,""},//"Density for:"},
	{ L_WORD81  ,""},//"Zero adjust tank\n pressure sensor for\n all tank pressure points."},
	{ L_WORD82  ,""},//"Common input for all Ballast tanks"},
	{ L_WORD83  ,""},//"Density"},
	{ L_WORD84  ,""},//"Configuration Error"},
	{ L_WORD85  ,""},//"Text"},
	{ L_WORD86  ,""},//"Continue"},
	{ L_WORD87  ,""},//"PageUp"},
	{ L_WORD88  ,""},//"PageDn"},
	{ L_WORD89  ,""},//"App.Setup"},
	{ L_WORD90  ,""},//"Detail"},
	{ L_WORD91  ,""},//"\nUnknown error in Configuration."},
	{ L_WORD92  ,""},//"Cargo line pressure"},
	{ L_WORD93  ,""},//"Vapour return line"},
	{ L_WORD94  ,""},//"Water Ingress Detection"},
	{ L_WORD95  ,""},//"Level switch"},
	{ L_WORD96  ,""},//"System"},
	{ L_WORD97  ,""},//"Alarm"},
	{ L_WORD98  ,""},//"Apply\n group"},
	{ L_WORD99  ,""},//"Not Configured"},
	{ L_WORD100 ,""},//"Not in use"},
	{ L_WORD101 ,""},//"Linear"},
	{ L_WORD102 ,""},//"API / ASTM-IP"},
	{ L_WORD103 ,""},//"Use measured density"},
	{ L_WORD104 ,""},//"Reference temperature"},
	{ L_WORD105 ,""},//"Use reference density"},
	{ L_WORD106 ,""},//"Reference 1"},
	{ L_WORD107 ,""},//"Reference 2"},
	{ L_WORD108 ,""},//"Coefficient"},
	{ L_WORD109 ,""},//"Overfill"},
	{ L_WORD110 ,""},//"High Level"},
	{ L_WORD111 ,""},//"Low Level"},
	{ L_WORD112 ,""},//"High Temp"},
	{ L_WORD113 ,""},//"Low Temp"},
	{ L_WORD114 ,""},//"High Tank Press"},
	{ L_WORD115 ,""},//"Low Tank Press"},
	{ L_WORD116 ,""},//"Zero adjust tank \npressure sensor"},
	{ L_WORD117 ,""},//"Zero adjust level \nsensor(s)."},
	{ L_WORD118 ,""},//"Adjust Level"},
	{ L_WORD119 ,""},//"Adjust Sounding"},
	{ L_WORD120 ,""},//"Adjust Ullage"},
	{ L_WORD121 ,""},//"Adjust Volume"},
	{ L_WORD122 ,""},//"Adjust Weight"},
	{ L_WORD123 ,""},//"Unlock"},
	{ L_WORD124 ,""},//"Location"},
	{ L_WORD125 ,""},//"Ena"},
	{ L_WORD126 ,""},//"Gain"},
	{ L_WORD127 ,""},//"Offset"},
	{ L_WORD128 ,""},//"Value"},
	{ L_WORD129 ,""},//"New Value"},
	{ L_WORD130 ,""},//"Confirm operation"},
	{ L_WORD131 ,""},//"Apply current density settings to all cargo tanks."},
	{ L_WORD132 ,""},//"Apply current density settings to all ballast tanks."},
	{ L_WORD133 ,""},//"Apply current density settings to all service tanks."},
	{ L_WORD134 ,""},//"New Alarm limit"},
	{ L_WORD135 ,""},//"Apply current alarm settings to all cargo tanks."},
	{ L_WORD136 ,""},//"Apply current alarm settings to all ballast tanks"},
	{ L_WORD137 ,""},//"Apply current alarm settings to all Service tanks"},
	{ L_WORD138 ,""},//"Apply current alarm settings to all Tank pressure"},
	{ L_WORD139 ,""},//"Apply current alarm settings to all Temperature points"},
	{ L_WORD140 ,""},//"Zero adjust sensor"},
	{ L_WORD141 ,""},//"The sensor must be vented to atmosphere"},
	{ L_WORD142 ,""},//"Zero adjust level sensor(s)!"},
	{ L_WORD143 ,""},//"The tank must be empty and no tank cleaning has been carried out the last 30 min."},
	{ L_WORD144 ,""},//"Protection plate!"},
	{ L_WORD145 ,""},//"Observed Level"},
	{ L_WORD146 ,""},//"Observed Sounding"},
	{ L_WORD147 ,""},//"Observed Ullage"},
	{ L_WORD148 ,""},//"Observed Volume"},
	{ L_WORD149 ,""},//"Observed Weight"},
	{ L_WORD150 ,""},//"Enter PIN code:"},
	{ L_WORD151 ,""},//"Set sensor gain"},
	{ L_WORD152 ,""},//"Set sensor value"},
	{ L_WORD153 ,""},//"Warning"},
	{ L_WORD154 ,""},//"You are about to adjust the sensor gain. This may affect the accuracy!"},
	{ L_WORD155 ,""},//"You are about to adjust the sensor. This may affect the accuracy!"},
	{ L_WORD156 ,""},//"Zero adjust"},
	{ L_WORD157 ,""},//"Sensor values"},
	{ L_WORD158 ,""},//"High Line Press"},
	{ L_WORD159 ,""},//"Low Line Press"},
	{ L_WORD160 ,""},//"Zero adjust line \npressure sensor"},
	{ L_WORD161 ,""},//"OK"},
	{ L_WORD162 ,""},//"Yes"},
	{ L_WORD163 ,""},//"No"},
	{ L_WORD164 ,""},//"Continue?"},
	{ L_WORD165 ,""},//"Detail view warning:"},
	{ L_WORD166 ,""},//"Select a tank by pressing on the row and push Detail button."},
	{ L_WORD167 ,""},//"< Prev"},
	{ L_WORD168 ,""},//"Next >"},
	{ L_WORD169 ,""},//"Ackn."},
	{ L_WORD170 ,""},//"Description"},
	{ L_WORD171 ,""},//"Raised"},
	{ L_WORD172 ,""},//"Reset"},
	{ L_WORD173 ,""},//"No Alarm"},
	{ L_WORD174 ,""},//"Set date (dd.mm.yy)"},
	{ L_WORD175 ,""},//"Set time (hh.mm.ss)"},
	{ L_WORD176 ,""},//"Fault in insert of Time!"},
	{ L_WORD177 ,""},//"Time format (h.m.s)"},
	{ L_WORD178 ,""},//"Fault in insert of Date"},
	{ L_WORD179 ,""},//"Date format (d.m.y)"},
	{ L_WORD180 ,""},//"Enter new value:"},
	{ L_WORD181 ,""},//"No value"},
	{ L_WORD182 ,""},//"No sensor(s)"},
	{ L_WORD183 ,""},//"Enter trim. (Aft is -)"},
	{ L_WORD184 ,""},//"Enter list. (Port is -)"},
	{ L_WORD185 ,""},//"Enter new density:"},
	{ L_WORD186 ,""},//"0"},
	{ L_WORD187 ,""},//"1"},
	{ L_WORD188 ,""},//"Error"},
	{ L_WORD189 ,""},//"Auto"},
	{ L_WORD190 ,""},//"Manual"},
	{ L_WORD191 ,""},//"No Error"},
	{ L_WORD192 ,""},//"Input error"},
	{ L_WORD193 ,""},//"Density error"},
	{ L_WORD194 ,""},//"RefTmp1=RefTmp2"},
	{ L_WORD195 ,""},//"RefTmp1 fixed"},
	{ L_WORD196 ,""},//"Wrong coeff"},
	{ L_WORD197 ,""},//"Value is too high"},
	{ L_WORD198 ,""},//"Value is too low"},
	{ L_WORD199 ,""},//"Use API"},
	{ L_WORD200 ,""},//"Use ref.density 1"},
	{ L_WORD201 ,""},//"Select API table"},
	{ L_WORD202 ,""},//"Illegal pointer"},
	{ L_WORD203 ,""},//"Illegal value"},
	{ L_WORD204 ,""},//"Unknown tank"},
	{ L_WORD205 ,""},//"AD not found"},
	{ L_WORD206 ,""},//"No tmp sensor"},
	{ L_WORD207 ,""},//"Value out of range"},
	{ L_WORD208 ,""},//"Use system seawater"},
	{ L_WORD209 ,""},//"Use system ballast"},
	{ L_WORD210 ,""},//"Lo temp=Hi temp"},
	{ L_WORD211 ,""},//"Input not allowed"},
	{ L_WORD212 ,""},//"Undefined Cargo"},
	{ L_WORD213 ,""},//"Retry input"},
	{ L_WORD214 ,""},//"Ref Dns1 too low"},
	{ L_WORD215 ,""},//"Ref Dns1 too high"},
	{ L_WORD216 ,""},//"Ref Dns2 too low"},
	{ L_WORD217 ,""},//"Ref Dns2 too high"},
	{ L_WORD218 ,""},//"API out of range"},
	{ L_WORD219 ,""},//"Sensor Error"},
	{ L_WORD220 ,""},//"Gain out of range"},
	{ L_WORD221 ,""},//"Use sys fresh water"},
	{ L_WORD222 ,""},//"Use sys heavy fuel"},
	{ L_WORD223 ,""},//"Use system diesel"},
	{ L_WORD224 ,""},//"Use sys lubricants"},
	{ L_WORD225 ,""},//"Low > High limit"},
	{ L_WORD226 ,""},//"High < Low limit"},
	{ L_WORD227 ,""},//"High = Low limit"},
	{ L_WORD228 ,""},//"Not adjustable"},
	{ L_WORD229 ,""},//"No input permission"},
	{ L_WORD230 ,""},//"Sensor is disabled"},
	{ L_WORD231 ,""},//"Use API53 table"},
	{ L_WORD232 ,""},//"Use API54 table"},
	{ L_WORD233 ,""},//"Use ref.density 2"},
	{ L_WORD234 ,""},//"Can't use common input"},
	{ L_WORD235 ,""},//"Override only possible when there are alarm on either Pre or Main"},
	{ L_WORD236 ,""},//"No Unit"},
	{ L_WORD237 ,""},//""/*Blank*/},
	{ L_WORD238 ,""},//"Length"},
	{ L_WORD239 ,""},//"Atm/Vapour pressure"},
	{ L_WORD240 ,""},//"Cargo/Ballast press"},
	{ L_WORD241 ,""},//"Line pressure"},
	{ L_WORD242 ,""},//"Density coef."},
	{ L_WORD243 ,""},//"Angle"},
	{ L_WORD244 ,""},//"Free surface"},
	{ L_WORD245 ,""},//"Moment"},
	{ L_WORD246 ,""},//"Immersion"},
	{ L_WORD247 ,""},//"Loadrate"},
	{ L_WORD248 ,""},//"Percent"},
	{ L_WORD249 ,""},//"GZ area"},
	{ L_WORD250 ,""},//"Current"},
	{ L_WORD251 ,""},//"Voltage"},
	{ L_WORD252 ,""},//"Time"},
	{ L_WORD253 ,""},//"mSeconds"},
	{ L_WORD254 ,""},//"Days"},
	{ L_WORD255 ,""},//"feet"},
	{ L_WORD256 ,""},//"d.feet"},
	{ L_WORD257 ,""},//"m�"},
	{ L_WORD258 ,""},//"litre"},
	{ L_WORD259 ,""},//"US g."},
	{ L_WORD260 ,""},//"US bls"},
	{ L_WORD261 ,""},//"ton"},
	{ L_WORD262 ,""},//"l.ton"},
	{ L_WORD263 ,""},//"kN"},
	{ L_WORD264 ,""},//"m�/h"},
	{ L_WORD265 ,""},//"USb/h"},
	{ L_WORD266 ,""},//"�C"},
	{ L_WORD267 ,""},//"�F"},
	{ L_WORD268 ,""},//"mH2O"},
	{ L_WORD269 ,""},//"mmH2O"},
	{ L_WORD270 ,""},//"mBar"},
	{ L_WORD271 ,""},//"Bar"},
	{ L_WORD272 ,""},//"Psi"},
	{ L_WORD273 ,""},//"kPa"},
	{ L_WORD274 ,""},//"InH2O"},
	{ L_WORD275 ,""},//"InHg"},
	{ L_WORD276 ,""},//"t/m� vac"},
	{ L_WORD277 ,""},//"t/m� air"},
	{ L_WORD278 ,""},//"lb/usg"},
	{ L_WORD279 ,""},//"Deg"},
	{ L_WORD280 ,""},//"Rad"},
	{ L_WORD281 ,""},//"t/m��C"},
	{ L_WORD282 ,""},//"t/m��F"},
	{ L_WORD283 ,""},//"l/g/�C"},
	{ L_WORD284 ,""},//"l/g/�F"},
	{ L_WORD285 ,""},//"m^4"},
	{ L_WORD286 ,""},//"Feet^4"},
	{ L_WORD287 ,""},//"t*m"},
	{ L_WORD288 ,""},//"lton*Ft"},
	{ L_WORD289 ,""},//"kNm"},
	{ L_WORD290 ,""},//"t/cm"},
	{ L_WORD291 ,""},//"lton/in"},
	{ L_WORD292 ,""},//"m*Rad"},
	{ L_WORD293 ,""},//"%"},
	{ L_WORD294 ,""},//"�"},
	{ L_WORD295 ,""},//"mAmp"},
	{ L_WORD296 ,""},//"Amp"},
	{ L_WORD297 ,""},//"Volt"},
	{ L_WORD298 ,""},//"mVolt"},
	{ L_WORD299 ,""},//"mSec"},
	{ L_WORD300 ,""},//"Sec"},
	{ L_WORD301 ,""},//"Min"},
	{ L_WORD302 ,""},//"Hours"},
	{ L_WORD303 ,""},//"Days"},
	{ L_WORD304 ,""},//"Unused"},
	{ L_WORD305 ,""},//"LevelSns"},
	{ L_WORD306 ,""},//"LevelRef"},
	{ L_WORD307 ,""},//"LevelFC"},
	{ L_WORD308 ,""},//"Sounding"},
	{ L_WORD309 ,""},//"Ullage"},
	{ L_WORD310 ,""},//"Volume%"},
	{ L_WORD311 ,""},//"Pressure"},
	{ L_WORD312 ,""},//"High Press"},
	{ L_WORD313 ,""},//"Low Press"},
	{ L_WORD314 ,""},//"FinishTime"},
	{ L_WORD315 ,""},//"RemTime"},
	{ L_WORD316 ,""},//"CargoType"},
	{ L_WORD317 ,""},//"Bot Press"},
	{ L_WORD318 ,""},//"Mid Press"},
	{ L_WORD319 ,""},//"Upp Press"},
	{ L_WORD320 ,""},//"Top Press"},
	{ L_WORD321 ,""},//"BP Gain"},
	{ L_WORD322 ,""},//"MP Gain"},
	{ L_WORD323 ,""},//"UP Gain"},
	{ L_WORD324 ,""},//"TP Gain"},
	{ L_WORD325 ,""},//"BP Offset"},
	{ L_WORD326 ,""},//"MP Offset"},
	{ L_WORD327 ,""},//"UP Offset"},
	{ L_WORD328 ,""},//"TP Offset"},
	{ L_WORD329 ,""},//"LevS"},
	{ L_WORD330 ,""},//"LevR"},
	{ L_WORD331 ,""},//"LevF"},
	{ L_WORD332 ,""},//"Snd"},
	{ L_WORD333 ,""},//"Ull"},
	{ L_WORD334 ,""},//"Vol"},
	{ L_WORD335 ,""},//"Vol%"},
	{ L_WORD336 ,""},//"Wgt"},
	{ L_WORD337 ,""},//"Dens"},
	{ L_WORD338 ,""},//"Temp"},
	{ L_WORD339 ,""},//"Pres"},
	{ L_WORD340 ,""},//"HTmp"},
	{ L_WORD341 ,""},//"LTmp"},
	{ L_WORD342 ,""},//"HiPr"},
	{ L_WORD343 ,""},//"LoPr"},
	{ L_WORD344 ,""},//"LRate"},
	{ L_WORD345 ,""},//"FTim"},
	{ L_WORD346 ,""},//"RTim"},
	{ L_WORD347 ,""},//"Ctyp"},
	{ L_WORD348 ,""},//"BP"},
	{ L_WORD349 ,""},//"MP"},
	{ L_WORD350 ,""},//"UP"},
	{ L_WORD351 ,""},//"TP"},
	{ L_WORD352 ,""},//"BPGn"},
	{ L_WORD353 ,""},//"MPGn"},
	{ L_WORD354 ,""},//"UPGn"},
	{ L_WORD355 ,""},//"TPGn"},
	{ L_WORD356 ,""},//"BPOf"},
	{ L_WORD357 ,""},//"MPOf"},
	{ L_WORD358 ,""},//"UPOf"},
	{ L_WORD359 ,""},//"TPOf"},
	{ L_WORD360 ,""},//"Bot Temp"},
	{ L_WORD361 ,""},//"Mid Temp"},
	{ L_WORD362 ,""},//"Upp Temp"},
	{ L_WORD363 ,""},//"Top Temp"},
	{ L_WORD364 ,""},//"BT"},
	{ L_WORD365 ,""},//"MT"},
	{ L_WORD366 ,""},//"UT"},
	{ L_WORD367 ,""},//"TT"},
	{ L_WORD368 ,""},//"Atm sensor"},
	{ L_WORD369 ,""},//"Power 24V(1)"},
	{ L_WORD370 ,""},//"Power 24V(2)"},
	{ L_WORD371 ,""},//"Power 3.3V"},
	{ L_WORD372 ,""},//"Power 1.8V"},
	{ L_WORD373 ,""},//"OS Status"},
	{ L_WORD374 ,""},//"Flash Status"},
	{ L_WORD375 ,""},//"Task Name"},
	{ L_WORD376 ,""},//"Running time"},
	{ L_WORD377 ,""},//"Power 5.0V"},
	{ L_WORD378 ,""},//"Power 12V"},
	{ L_WORD379 ,""},//"Com Channel"},
	{ L_WORD380 ,""},//"Com Version"},
	{ L_WORD381 ,""},//"Store Ver."},
	{ L_WORD382 ,""},//"Rx Buf Size"},
	{ L_WORD383 ,""},//"Tx Buf Size"},
	{ L_WORD384 ,""},//"Reset Status"},
	{ L_WORD385 ,""},//"Total Restart"},
	{ L_WORD386 ,""},//"Fail count"},
	{ L_WORD387 ,""},//"Tot. fail cnt"},
	{ L_WORD388 ,""},//"Program"},
	{ L_WORD389 ,""},//"Power 24V"},
	{ L_WORD390 ,""},//"Serial Number"},
	{ L_WORD391 ,""},//"Unit status"},
	{ L_WORD392 ,""},//"Card status"},
	{ L_WORD393 ,""},//"Cargo Name"},
	{ L_WORD394 ,""},//"VolCorrFactor"},
	{ L_WORD395 ,""},//"VCF@Temp"},
	{ L_WORD396 ,""},//"Measured API"},
	{ L_WORD397 ,""},//"Comp. Density"},
	{ L_WORD398 ,""},//"Ref.Density1"},
	{ L_WORD399 ,""},//"Ref.Density2"},
	{ L_WORD400 ,""},//"Ref. Temp1"},
	{ L_WORD401 ,""},//"Ref. Temp2"},
	{ L_WORD402 ,""},//"Not defined"},
	{ L_WORD403 ,""},//"Simple"},
	{ L_WORD404 ,""},//"AtmPress"},
	{ L_WORD405 ,""},//"Ballast"},
	{ L_WORD406 ,""},//"Heavy fuel"},
	{ L_WORD407 ,""},//"Diesel"},
	{ L_WORD408 ,""},//"Lubricants"},
	{ L_WORD409 ,""},//"Fresh water"},
	{ L_WORD410 ,""},//"Sea water"},
	{ L_WORD411 ,""},//"API 6A"},
	{ L_WORD412 ,""},//"API 6B"},
	{ L_WORD413 ,""},//"API 6D"},
	{ L_WORD414 ,""},//"API 53A"},
	{ L_WORD415 ,""},//"API 53B"},
	{ L_WORD416 ,""},//"API 53D"},
	{ L_WORD417 ,""},//"API 54A"},
	{ L_WORD418 ,""},//"API 54B"},
	{ L_WORD419 ,""},//"API 54D"},
	{ L_WORD420 ,""},//"DF"},
	{ L_WORD421 ,""},//"DP"},
	{ L_WORD422 ,""},//"DS"},
	{ L_WORD423 ,""},//"DA"},
	{ L_WORD424 ,""},//"Level"},// was level
	{ L_WORD425 ,""},//"Trim in deg"},
	{ L_WORD426 ,""},//"Trim in meter"},
	{ L_WORD427 ,""},//"List in deg"},
	{ L_WORD428 ,""},//"DF (User select)"},
	{ L_WORD429 ,""},//"DA (User select)"},
	{ L_WORD430 ,""},//"DF@Mark"},
	{ L_WORD431 ,""},//"DA@Mark"},
	{ L_WORD432 ,""},//"DF@PP"},
	{ L_WORD433 ,""},//"DA@PP"},
	{ L_WORD434 ,""},//"On/Off"},
	{ L_WORD435 ,""},//"System data"},
	{ L_WORD436 ,""},//"Drafts"},
	{ L_WORD437 ,""},//"Cargo tank"},
	{ L_WORD438 ,""},//"Other tanks"},
	{ L_WORD439 ,""},//"FRO"},
	{ L_WORD440 ,""},//"G1"},
	{ L_WORD441 ,""},//"G2"},
	{ L_WORD442 ,""},//"G3"},
	{ L_WORD443 ,""},//"NL1"},
	{ L_WORD444 ,""},//"NL2"},
	{ L_WORD445 ,""},//"Lev"},
	{ L_WORD446 ,""},//"Meas. Density"},
	{ L_WORD447 ,""},//"List in meter"},
	{ L_WORD448 ,""},//"Latitude"},
	{ L_WORD449 ,""},//"Type"},
	{ L_WORD450 ,""},//"SnsDB"},
	{ L_WORD451 ,""},//"Placing"},
	{ L_WORD452 ,""},//"MinRange"},
	{ L_WORD453 ,""},//"MaxRange"},
	{ L_WORD454 ,""},//"CableLength"},
	{ L_WORD455 ,""},//"TCUAddress"},
	{ L_WORD456 ,""},//"Port"},
	{ L_WORD457 ,""},//"IOAddress"},
	{ L_WORD458 ,""},//"Channel"},
	{ L_WORD459 ,""},//"ADCardChn"},
	{ L_WORD460 ,""},//"Trim"},
	{ L_WORD461 ,""},//"List"},
	{ L_WORD462 ,""},//"Black"},
	{ L_WORD463 ,""},//"Dark Gray"},
	{ L_WORD464 ,""},//"Light Gray"},
	{ L_WORD465 ,""},//"White"},
	{ L_WORD466 ,""},//"Blue"},
	{ L_WORD467 ,""},//"Print"},
	{ L_WORD468 ,""},//"S"	/*Status*/},
	{ L_WORD469 ,""},//"Use bls"},
	{ L_WORD470 ,""},//"Use m�"},
	{ L_WORD471 ,""},//"Dry"},
	{ L_WORD472 ,""},//"--.-"},
	{ L_WORD473 ,""},//"Empty"},
	{ L_WORD474 ,""},//"*****"	/*fixed length!*/},
	{ L_WORD475 ,""},//"Main"},
	{ L_WORD476 ,""},//"Pre"},
	{ L_WORD477 ,""},//"Over"},
	{ L_WORD478 ,""},//"Prot"},
	{ L_WORD479 ,""},//"Com"},
	{ L_WORD480 ,""},//"(Rx/Tx)"},
	{ L_WORD481 ,""},//"on TCU:"},
	{ L_WORD482 ,""},//"on ZB485:"},
	{ L_WORD483 ,""},//"BootLoader"},
	{ L_WORD484 ,""},//"Application"},
	{ L_WORD485 ,""},//"Unknown"},
	{ L_WORD486 ,""},//"None"},
	{ L_WORD487 ,""},//"Err"},
	{ L_WORD488 ,""},//"NoUs"},
	{ L_WORD489 ,""},//"Other"},
	{ L_WORD490 ,""},//"Press"},
	{ L_WORD491 ,""},//"@PP"},
	{ L_WORD492 ,""},//"@Mark"},
	{ L_WORD493 ,""},//"Deact."},
	{ L_WORD494 ,""},//"Active"},
	{ L_WORD495 ,""},//"Ackn."},
	{ L_WORD496 ,""},//"Lim:"},
	{ L_WORD497 ,""},//"Val:"},
	{ L_WORD498 ,""},//"Pointer Error"},
	{ L_WORD499 ,""},//"Unk."},
	{ L_WORD500 ,""},//"OutOfRange"},
	{ L_WORD501 ,""},//"ComFault"},
	{ L_WORD502 ,""},//"HLev"},
	{ L_WORD503 ,""},//"HighLevel"},
	{ L_WORD504 ,""},//"HighLinePress"},
	{ L_WORD505 ,""},//"HLPr"},
	{ L_WORD506 ,""},//"HighPressure"},
	{ L_WORD507 ,""},//"HPre"},
	{ L_WORD508 ,""},//"HighTemp"},
	{ L_WORD509 ,""},//"HTmp"},
	{ L_WORD510 ,""},//"High Voltage"},
	{ L_WORD511 ,""},//"HVolt"},
	{ L_WORD512 ,""},//"HighPressure1"},
	{ L_WORD513 ,""},//"HPr1"},
	{ L_WORD514 ,""},//"LowPressure1"},
	{ L_WORD515 ,""},//"LPr1"},
	{ L_WORD516 ,""},//"ComFault"},
	{ L_WORD517 ,""},//"IOErr"},
	{ L_WORD518 ,""},//"LowLevel"},
	{ L_WORD519 ,""},//"LLev"},
	{ L_WORD520 ,""},//"LowLinePress"},
	{ L_WORD521 ,""},//"LLPr"},
	{ L_WORD522 ,""},//"LowPressure"},
	{ L_WORD523 ,""},//"LPre"},
	{ L_WORD524 ,""},//"Low Temp"},
	{ L_WORD525 ,""},//"LTmp"},
	{ L_WORD526 ,""},//"Low Voltage"},
	{ L_WORD527 ,""},//"LVolt"},
	{ L_WORD528 ,""},//"Failure"},
	{ L_WORD529 ,""},//"MainWater"},
	{ L_WORD530 ,""},//"MWat"},
	{ L_WORD531 ,""},//"OpenLoop"},
	{ L_WORD532 ,""},//"oloop"},
	{ L_WORD109 ,""},//"Overfill"},
	{ L_WORD534 ,""},//"OFill"},
	{ L_WORD535 ,""},//"PreWater"},
	{ L_WORD536 ,""},//"PWat"},
	{ L_WORD537 ,""},//"RangeError"},
	{ L_WORD538 ,""},//"ADErr"},
	{ L_WORD539 ,""},//"Cnv&Cal Error"},
	{ L_WORD540 ,""},//"HWErr"},
	{ L_WORD541 ,""},//"Conv Error"},
	{ L_WORD542 ,""},//"RaErr"},
	{ L_WORD543 ,""},//"ShortCircuit"},
	{ L_WORD544 ,""},//"Scirc"},
	{ L_WORD545 ,""},//"Details"},
	{ L_WORD546 ,""},//"Calibration Data"},
	{ L_WORD547 ,""},//"SerNum"},
	{ L_WORD548 ,""},//"Range"},
	{ L_WORD549 ,""},//"CalData Source"},
	{ L_WORD550 ,""},//"Level offset"},
	{ L_WORD551 ,""},//"Inclinometer"},
	{ L_WORD552 ,""},//"Draft"},
	{ L_WORD553 ,""},//"Measured"},
	{ L_WORD554 ,""},//"ch"},
	{ L_WORD555 ,""},//"Loc"},
	{ L_WORD556 ,""},//"RawVal"},
	{ L_WORD557 ,""},//"CalVal"},
	{ L_WORD558 ,""},//"CnvCalE"},
	{ L_WORD559 ,""},//"PROM"},
	{ L_WORD560 ,""},//"PC"},
	{ L_WORD561 ,""},//"TCUCal"},
	{ L_WORD562 ,""},//"AD Sns"},
	{ L_WORD563 ,""},//"TCU Sns"},
	{ L_WORD564 ,""},//"From TCU"},
	{ L_WORD565 ,""},//"Green"},
	{ L_WORD566 ,""},//"Erasing FLASH"},
	{ L_WORD567 ,""},//"Info"},
	{ L_WORD568 ,""},//"Erasing Failure"},
	{ L_WORD569 ,""},//"Updating program,please wait..."},
	{ L_WORD570 ,""},//"Runtime calibration,\n please touch the screen\n at the center of the ring"},
	{ L_WORD571 ,""},//"Abort"},
	{ L_WORD572 ,""},//"Press here"},
	{ L_WORD573 ,""},//"(upper left position)"},
	{ L_WORD574 ,""},//"(lower right position)"},
	{ L_WORD575 ,""},//"Page"},
	{ L_WORD576 ,""},//"Data version"},
	{ L_WORD577 ,""},//"Cargo tanks"},
	{ L_WORD578 ,""},//"Ballast tanks"},
	{ L_WORD579 ,""},//"Service tanks"},
	{ L_WORD580 ,""},//"Heavy Fuel Oil tanks"},
	{ L_WORD581 ,""},//"Diesel Oil tanks"},
	{ L_WORD582 ,""},//"Lubricant tanks"},
	{ L_WORD583 ,""},//"Miscellaneous tanks"},
	{ L_WORD584 ,""},//"Freshwater tanks"},
	{ L_WORD585 ,""},//"NotDef"},
	{ L_WORD586 ,""},//"Atm"},
	{ L_WORD587 ,""},//"Bottom"},
	{ L_WORD588 ,""},//"Middle"},
	{ L_WORD589 ,""},//"Upper"},
	{ L_WORD590 ,""},//"TankPres"},
	{ L_WORD591 ,""},//"PumpRm"},
	{ L_WORD592 ,""},//"EngRm"},
	{ L_WORD593 ,""},//"Deck"},
	{ L_WORD594 ,""},//"Deck"},
	{ L_WORD595 ,""},//"Line"},
	{ L_WORD596 ,""},//"WIMain"},
	{ L_WORD597 ,""},//"WIPre"},
	{ L_WORD598 ,""},//"Inc"},
	{ L_WORD599 ,""},//"LSw"},
	{ L_WORD600 ,""},//"Rad"},
	{ L_WORD601 ,""},//"WIng"},
	{ L_WORD602 ,""},//"Zero adjust tank pressure!"},
	{ L_WORD603 ,""},//"The tanks must be vented to the atmosphere. This operation affects all tanks in group."},
	{ L_WORD604 ,""},//"Zero adjust sensor(s)!"},
	{ L_WORD605 ,""},//"The tanks must be empty and no tank cleaning the last 30 minutes. This operation affects all tanks in group."},
	{ L_WORD606 ,""},//"Zeroset warning:"},
	{ L_WORD607 ,""},//"The tanks must be vented to the atmosphere. This operation affects all tank pressure points."},
	{ L_WORD608 ,""},//"The tanks must be empty and no tank cleaning the last 30 minutes. This operation affects all tank pressure points."},
	{ L_WORD609 ,""},//"Heavy fuel density"},
	{ L_WORD610 ,""},//"Diesel oil density"},
	{ L_WORD611 ,""},//"Lubricants density"},
	{ L_WORD612 ,""},//"Fresh water density"},
	{ L_WORD613 ,""},//" File truncated"},
	{ L_WORD614 ,""},//"Error in UNICODE string!"},
	{ L_WORD615 ,""},//"F "},
	{ L_WORD616 ,""},//"A "},
	{ L_WORD617 ,""},//"P "},
	{ L_WORD618 ,""},//"S "},
	{ L_WORD619 ,""},//"Even"},
	{ L_WORD620 ,""},//"Printer on this TDU"},
	{ L_WORD621 ,""},//"Temperatures"},
	{ L_WORD622 ,""},//"Line pressures"},
	{ L_WORD623 ,""},//"Tank pressures"},
	{ L_WORD624 ,""},//"CnvCal"},
	{ L_WORD625 ,""},//"CnvErr"},
	{ L_WORD626 ,""},//"CalErr"},
	{ L_WORD627 ,""},//"TDU"},
	{ L_WORD628 ,""},//"PC"},
	{ L_WORD629 ,""},//"TCU"},
	{ L_WORD630 ,""},//"ANPro3"},
	{ L_WORD631 ,""},//"ANPro10"},
	{ L_WORD632 ,""},//"IOsystem"},
	{ L_WORD633 ,""},//"ZB_Red"},
	{ L_WORD634 ,""},//"Wago"},
	{ L_WORD635 ,""},//"TPCx"},
	{ L_WORD636 ,""},//"Printer"},
	{ L_WORD637 ,""},//"ANPro1"},
	{ L_WORD638 ,""},//"ANPro3"},
	{ L_WORD639 ,""},//"ANPro10"},
	{ L_WORD640 ,""},//"Modbus"},
	{ L_WORD641 ,""},//"Printer"},
	{ L_WORD642 ,""},//"Void space"},
	{ L_WORD643 ,""},//"Zero adjust void space\n pressure sensor for\n all void spaces."},
	{ L_WORD644 ,""},//"Zero adjust level\n sensor(s) for\n all void spaces."},
	{ L_WORD646 ,""},//"Apply current density settings to all void spaces."},
	{ L_WORD647 ,""},//"Apply current alarm settings to all void spaces"},
	{ L_WORD648 ,""},//"Leakage"},
	{ L_WORD649 ,""},//"Leak"},
	{ L_WORD650 ,""},//"Please wait"},
	{ L_WORD651 ,""},//"Wait"},
	{ L_WORD652 ,""},//"DST"},
	{ L_WORD653 ,""},//"24V"},
	{ L_WORD654 ,""},//"In#1"},
	{ L_WORD655 ,""},//"In#2"},
	{ L_WORD656 ,""},//"The system will be adjusted to the inserted value. Incorrect entry will cause malfunction of the system."},
	{ L_WORD657 ,""},//"Warning! Adjust Level"},
	{ L_WORD658 ,""},//"Warning! Adjust Sounding"},
	{ L_WORD659 ,""},//"Warning! Adjust Ullage"},
	{ L_WORD660 ,""},//"Warning! Adjust Volume"},
	{ L_WORD661 ,""},//"Warning! Adjust Weight"},
	{ L_WORD662 ,""},//"The protection plate must be installed on the sensor."},
	{ L_WORD663 ,""},//"The protection plate must be removed from the sensor."},
	{ L_WORD664 ,""},//"Enter Pin code:"},
	{ L_WORD665 ,""},//"Enter new pin code:"},
	{ L_WORD666 ,""},//"Screen saver time, min."},
	{ L_WORD667 ,""},//"Alarm delay time, sec."},
	{ L_WORD668 ,""},//"Enter old pin code:"},
	{ L_WORD669 ,""},//"Re-enter new pin code:"},
	{ L_WORD670 ,""},//"ComErr Id"		},
	{ L_WORD671 ,""},//"ComErr Cmd"	},
	{ L_WORD672 ,""},//"ComErr Msg"	},
	{ L_WORD673 ,""},//"ComErr Cnt"	},
	{ L_WORD674 ,""},//"ComErr Time"	},
	{ L_WORD675 ,""},//"Command"},
	{ L_WORD676 ,""},//"Object"},
	{ L_WORD677 ,""},//"Level"},
	{ L_WORD678 ,""},//"Lvl"},
	{ L_WORD679 ,""},//"Displacement"},
	{ L_WORD680 ,""},//"LCG"},
	{ L_WORD681 ,""},//"TCG"},
	{ L_WORD682 ,""},//"VCG"},
	{ L_WORD683 ,""},//"List in meter"},
	{ L_WORD684 ,""},//"Draft Mid"},
	{ L_WORD685 ,""},//"Liquid weight"},
	{ L_WORD686 ,""},//"Solid weight"},
	{ L_WORD687 ,""},//"Draft P"},
	{ L_WORD688 ,""},//"TFS Moment"},
	{ L_WORD689 ,""},//"L moment"},
	{ L_WORD690 ,""},//"T moment"},
	{ L_WORD691 ,""},//"V moment"},
	{ L_WORD692 ,""},//"VCG Solids"},
	{ L_WORD693 ,""},//"VCG adjusted"},
	{ L_WORD694 ,""},//"Max VCG"},
	{ L_WORD695 ,""},//"VCG margin"},
	{ L_WORD696 ,""},//"Dam.max VCG"},
	{ L_WORD697 ,""},//"Dam. VCG marg."},
	{ L_WORD698 ,""},//"Immersion"},
	{ L_WORD699 ,""},//"KM"},
	{ L_WORD700 ,""},//"GM solid"},
	{ L_WORD701 ,""},//"GM liquid"},
	{ L_WORD702 ,""},//"TCF"},
	{ L_WORD703 ,""},//"LCF"},
	{ L_WORD704 ,""},//"TCG"},
	{ L_WORD705 ,""},//"LCG"},
	{ L_WORD706 ,""},//"GZ"},
	{ L_WORD707 ,""},//"GZ30"},
	{ L_WORD708 ,""},//"GZ max"},
	{ L_WORD709 ,""},//"GZ angle"},
	{ L_WORD710 ,""},//"GZ a0-30"},
	{ L_WORD711 ,""},//"GZ a30-40"},
	{ L_WORD712 ,""},//"Flooding angle"},
	{ L_WORD713 ,""},//"Deadweight"},
	{ L_WORD714 ,""},//"LCB"},
	{ L_WORD715 ,""},//"MaxBM@"},
	{ L_WORD716 ,""},//"MaxSF@"},
	{ L_WORD717 ,""},//"Frame"},
	{ L_WORD718 ,""},//"Bend.Mom."},
	{ L_WORD719 ,""},//"Shr.Forc."},
	{ L_WORD720 ,""},//"Cor.BMom"},
	{ L_WORD721 ,""},//"APP dist."},
	{ L_WORD722 ,""},//"PrevFrame"},
	{ L_WORD723 ,""},//"BMomHrb"},
	{ L_WORD724 ,""},//"BMomSea"},
	{ L_WORD725 ,""},//"SForceHrb"},
	{ L_WORD726 ,""},//"SForceSea"},
	{ L_WORD727 ,""},//"SteelWgt"},
	{ L_WORD728 ,""},//"Buoyancy"},
	{ L_WORD729 ,""},//"Load"},
	{ L_WORD730 ,""},//"Mom.Change"},
	{ L_WORD731 ,""},//"Avg BMom"},
	{ L_WORD732 ,""},//"Avg SForce"},
	{ L_WORD733 ,""},//"Solids"},
	{ L_WORD734 ,""},//"Draft fore"},
	{ L_WORD735 ,""},//"Draft port"},
	{ L_WORD736 ,""},//"Draft stbd"},
	{ L_WORD737 ,""},//"Draft aft"},
	{ L_WORD738 ,""},//"TFree Surf."},
	{ L_WORD739 ,""},//"FreeSMom."},
	{ L_WORD740 ,""},//"GZ a0-40"},
	{ L_WORD741 ,""},//"Constant solids"},
	{ L_WORD742 ,""},//"Variable Solids"},
	{ L_WORD743 ,L""},
	{ L_WORD744 ,L""},
	{ L_WORD745 ,L""},
	{ L_WORD746 ,L""},
	{ L_WORD747 ,L""},
	{ L_WORD748 ,L""},
	{ L_WORD749 ,L""},
	{ L_WORD750 ,L""},
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
