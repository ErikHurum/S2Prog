//---------------------------------------------------------------------------
#ifdef BORLAND
	#include <vcl.h>
	#pragma hdrstop
	#pragma package(smart_init)
#endif
#include "TSNIncludes.h"
//---------------------------------------------------------------------------
NewLanguageWord FrenchDictionary[]=
{
//	{ Keyword	,Language}, // English (comment)
	{ L_WORD0   ,L""},			// FEIL-FEIL- Please lev empty
	{ L_WORD1   ,L"Valider"},			// 	Enable
	{ L_WORD2   ,L"Invalider"},			// 	Disable
	{ L_WORD3   ,L"Connecter"},			// 	On
	{ L_WORD4   ,L"Déconnecter"},			//	Off
	{ L_WORD5   ,L"Imprimante"},			//	Printer
	{ L_WORD6   ,L"Langue"},			//	Language:
	{ L_WORD7   ,L"Alarmes"},			// 	Alarms
	{ L_WORD8   ,L"Echange de ballast"},			//	Ballast exchange
	{ L_WORD9   ,L"Cargaison"},			//	Cargo
	{ L_WORD10  ,L"service"},			//	Service
	{ L_WORD11  ,L"Température"},			//	Temperature
	{ L_WORD12  ,L"Pression de la citerne"},			//	Tank pressure
	{ L_WORD13  ,L"Sélection de connexion"},			//	Select logging:
	{ L_WORD14  ,L"Temps de connexion"},			//	Logging time
	{ L_WORD15  ,L"Heures"},			//	Hours
	{ L_WORD16  ,L"Configuration de l'imprimante"},			//	Printer setup
	{ L_WORD17  ,L"Ouvrir"},			//	Open
	{ L_WORD18  ,L"Fermer"},			//	Close
	{ L_WORD19  ,L"Période de connexion"},			//	Log period
	{ L_WORD20  ,L"Système page 1"},			//	System page 1
	{ L_WORD21  ,L"Manuel d'utilisation"},			//	User manual
	{ L_WORD22  ,L"Configuration"},			//	Setup
	{ L_WORD23  ,L"Imprimante"},			//	Printer
	{ L_WORD24  ,L"Version du programme"},			//	Program version
	{ L_WORD25  ,L"Version des données"},			//	Data version:
	{ L_WORD26  ,L"Système d'identification"},			//	System ID:
	{ L_WORD27  ,L"Système d'élément"},			//	Unit System:
	{ L_WORD28  ,L"Langue"},			//	Language
	{ L_WORD29  ,L"GMT"},			//	GMT
	{ L_WORD30  ,L"Système page 2"},			//	System page 2
	{ L_WORD31  ,L"Référence atmosphérique"},			//	Atmospheric ref.
	{ L_WORD32  ,L"Mètre"},			//	meter
	{ L_WORD33  ,L"Compensation de tangage"},			//	Trim source
	{ L_WORD34  ,L"Degré"},			//	degree
	{ L_WORD35  ,L"Projet"},			//	Draft:
	{ L_WORD36  ,L"Unité"},			//	Unit
	{ L_WORD37  ,L"Eau de mer"},			//	Seawater
	{ L_WORD38  ,L"Liste source"},			//	List source:
	{ L_WORD39  ,L"Système page 3: IO unités"},			//	System page 3: IO units
	{ L_WORD40  ,L"Sélection"},			//	Select:
	{ L_WORD41  ,L"Système page 4: éléments hardware"},			//	System page 4: Hardware units
	{ L_WORD42  ,L"Système page 5"},			//	System page 5
	{ L_WORD43  ,L"Somme de toutes les citernes"},			//	Total for all tanks
	{ L_WORD44  ,L"Volume"},			//	Volume
	{ L_WORD45  ,L"Poids"},			//	Weight
	{ L_WORD46  ,L"Cargaison"},			//	Cargo
	{ L_WORD47  ,L"Ballast"},			//	Ballast
	{ L_WORD48  ,L"Fioul lourd"},			//	Heavy fuel oil
	{ L_WORD49  ,L"Gasoil"},			//	Diesel oil
	{ L_WORD50  ,L"Lubrifiants"},			//	Lubricants
	{ L_WORD51  ,L"Eau fraîche"},			//	Fresh water
	{ L_WORD52  ,L"Divers"},			//	Miscellaneous
	{ L_WORD53  ,L"Total général"},			//	Grand total
	{ L_WORD54  ,L"Page de configuration du système"},			//	System setup page
	{ L_WORD55  ,L"Economiseur d'écran"},			//	Screen saver:
 	{ L_WORD56  ,L"Minutes"},			//	minutes
	{ L_WORD57  ,L"Retardement du débranchement d'alarme"},			//	Alarm off delay:
	{ L_WORD58  ,L"Secondes"},			//	seconds
	{ L_WORD59  ,L"Unité SI"},			//	SI unit
	{ L_WORD60  ,L"Unité US "},			//	US unit
	{ L_WORD61  ,L"Réglage de colori "},			//	Set color:
	{ L_WORD62  ,L"Arrière-plan"},			//	Background
	{ L_WORD63  ,L"Premier-plan"},			//	Foreground
	{ L_WORD64  ,L"Luminosité"},			//	Brightness:
	{ L_WORD65  ,L"Sonnette /n témoin lumineux"},			//	Buzzer /\n Light test
	{ L_WORD66  ,L"Changement de code de sécurité"},			//	Change PIN code
	{ L_WORD67  ,L"Ecran de calibrage"},			//	Calibrate screen
	{ L_WORD68  ,L"EEPROM"},			//	EEPROM
	{ L_WORD69  ,L"Configuration d'application"},			//	Application setup
	{ L_WORD70  ,L"Colonne 1"},			//	Col. 1
	{ L_WORD71  ,L"Colonne 2"},			//	Col. 2
	{ L_WORD72  ,L"Colonne 3"},			//	Col. 3
	{ L_WORD73  ,L"Colonne 4"},			//	Col. 4
	{ L_WORD74  ,L"Nom"},			//	Name 
	{ L_WORD75  ,L"Mise à zéro de la sonde\n de pression du réservoir sur\n toutes les citernes de ballast"},			//	Zero adjust tank\n pressure sensor for\n all ballast tanks.
	{ L_WORD76  ,L"Mise à zéro du(des) capteur(s)\n de niveau\n sur toutes les citernes de ballast"},			//	Zero adjust level\n sensor(s) for\n all ballast tanks.
	{ L_WORD77  ,L"Densité de l'eau de ballast"},			//	Ballast water density
	{ L_WORD78  ,L"Mise à zéro de la sonde\n de pression du réservoir sur\n toutes les citernes de cargaison"},			//	Zero adjust tank\n pressure sensor for\n all cargo tanks.
	{ L_WORD79  ,L"Mise à zéro du(des) capteur(s)\n de niveau\n sur toutes les citernes de cargaison"},			//	Zero adjust level\n sensor(s) for\n all cargo tanks.
	{ L_WORD80  ,L"Densité pour:"},			//	Density for:
	{ L_WORD81  ,L"Mise à zero de la sonde\n de pression du reservoir sur\n tous les points de pression des citernes"},			//	Zero adjust tank\n pressure sensor for\n all tank pressure points.
	{ L_WORD82  ,L"Accès commun pour toutes les citernes de ballast"},			//	Common input for all Ballast tanks
	{ L_WORD83  ,L"Densité"},			//	Density
	{ L_WORD84  ,L"Erreur de configuration"},			//	Configuration Error
	{ L_WORD85  ,L"Texte"},			//	Text
	{ L_WORD86  ,L"Continuation"},			//	Continue
	{ L_WORD87  ,L"Haut de page"},			//	PageUp
	{ L_WORD88  ,L"Bas de page"},			//	PageDn
	{ L_WORD89  ,L"Configuration d'application"},			//	App.Setup
	{ L_WORD90  ,L"Détail"},			//	Detail
	{ L_WORD91  ,L"\nErreur inconnue de configuration"},			//	\nUnknown error in Configuration.
	{ L_WORD92  ,L"Tuyau de pression de cargaison"},			//	Cargo line pressure
	{ L_WORD93  ,L"Tuyau de retour de vapeur"},			//	Vapour return line
	{ L_WORD94  ,L"Détection d'arrivée d'eau"},			//	Water Ingress Detection
	{ L_WORD95  ,L"Commutateur de niveau"},			//	Level switch
	{ L_WORD96  ,L"Système"},			//	System
	{ L_WORD97  ,L"Alarme"},			//	Alarm
	{ L_WORD98  ,L"Application\n au groupe"},			//	Apply\n group
	{ L_WORD99  ,L"Non-configuré"},			//	Not Configured
	{ L_WORD100 ,L"Hors-service "},			//	Not in use
	{ L_WORD101 ,L"Linéaire"},			//	Linear
	{ L_WORD102 ,L"API / ASTM-IP"},			//	API / ASTM-IP
	{ L_WORD103 ,L"Emploi de la densité mesurée"},			//	Use measured density
	{ L_WORD104 ,L"Température de référence"},			//	Reference temperature
	{ L_WORD105 ,L"Emploi de la densité de référence"},			//	Use reference density
	{ L_WORD106 ,L"Référence 1"},			//	Reference 1
	{ L_WORD107 ,L"Référence 2"},			//	Reference 2
	{ L_WORD108 ,L"Coefficient"},			//	Coefficient
	{ L_WORD109 ,L"Trop-plein"},			//	Overfill
	{ L_WORD110 ,L"Haut niveau"},			//	High Level
	{ L_WORD111 ,L"Faible niveau"},			//	Low Level
	{ L_WORD112 ,L"Haute température"},			//	High Temp
	{ L_WORD113 ,L"Faible temperature"},			//	Low Temp
	{ L_WORD114 ,L"Haute pression du réservoir"},			//	High Tank Press
	{ L_WORD115 ,L"Faible pression du reservoir"},			//	Low Tank Press
	{ L_WORD116 ,L"Mise à zero de la sonde \n de pression du réservoir "},			//	Zero adjust tank \n pressure sensor
	{ L_WORD117 ,L"Mise à zéro du(des) capteur(s)\n de niveau"},			//	Zero adjust level \n sensor(s).
	{ L_WORD118 ,L"Ajustement du niveau"},			//	Adjust Level
	{ L_WORD119 ,L"Ajustement sonore"},			//	Adjust Sounding
	{ L_WORD120 ,L"Ajustement du vide"},			//	Adjust Ullage
	{ L_WORD121 ,L"Ajustement de la contenance"},			//	Adjust Volume
	{ L_WORD122 ,L"Ajustement du poids"},			//	Adjust Weight
	{ L_WORD123 ,L"Déverrouiller"},			//	Unlock
	{ L_WORD124 ,L"Emplacement"},			//	Location
	{ L_WORD125 ,L"Validation"},			//	Ena
	{ L_WORD126 ,L"Gain"},			//	Gain
	{ L_WORD127 ,L"Déport"},			//	Offset
	{ L_WORD128 ,L"Valeur"},			//	Value
	{ L_WORD129 ,L"Nouvelle valeur"},			//	New Value
	{ L_WORD130 ,L"Confirmation d'opération"},			//	Confirm operation
	{ L_WORD131 ,L"Appliquer les réglages actuels de densité à tous les réservoirs de cargaison"},			//	Apply current density settings to all cargo tanks.
	{ L_WORD132 ,L"Appliquer les réglages actuels de densité à tous les réservoirs de ballast"},			//	Apply current density settings to all ballast tanks.
	{ L_WORD133 ,L"Appliquer les réglages actuels de densité à tous les réservoirs de service"},			//	Apply current density settings to all service tanks.
	{ L_WORD134 ,L"Nouvelle limitation d'alarme"},			//	New Alarm limit
	{ L_WORD135 ,L"Appliquer les réglages actuels d'alarme à tous les réservoirs de cargaison"},			//	Apply current alarm settings to all cargo tanks.
	{ L_WORD136 ,L"Appliquer les réglages actuels d'alarme à tous les réservoirs de ballast"},			//	Apply current alarm settings to all ballast tanks
	{ L_WORD137 ,L"Appliquer les réglages actuels d'alarme à tous les réservoirs de service"},			//	Apply current alarm settings to all Service tanks
	{ L_WORD138 ,L"Appliquer les réglages actuels d'alarme à tous les réservoirs de pression"},			//	Apply current alarm settings to all Tank pressure
	{ L_WORD139 ,L"Appliquer les réglages actuels d'alarme à tous les points de température"},			//	Apply current alarm settings to all Temperature points
	{ L_WORD140 ,L"Mise à zéro de la sonde"},			//	Zero adjust sensor
	{ L_WORD141 ,L"La sonde doit être positionnée à l'air libre"},			//	The sensor must be vented to atmosphere
	{ L_WORD142 ,L"Mise à zero du niveau de la(des) sonde(s)!"},			//	Zero adjust level sensor(s)!
	{ L_WORD143 ,L"Le réservoir doit être vide et aucun nettoyage de réservoir n'a été effectué durant les 30 dernières min."},			//	The tank must be empty and no tank cleaning has been carried out the last 30 min.
	{ L_WORD144 ,L"Le niveau sera ajusté au niveau introduit; une insertion incorrecte provoquera le disfonctionnement du système"},			//	The level will be adjusted to the inserted level. Incorrect entry will cause malfunction of the system.
	{ L_WORD145 ,L"Niveau constaté"},			//	Observed Level
	{ L_WORD146 ,L"Sonorité constatée"},			//	Observed Sounding
	{ L_WORD147 ,L"Vide constaté"},			//	Observed Ullage
	{ L_WORD148 ,L"Contenance constatée"},			//	Observed Volume
	{ L_WORD149 ,L"Poids constaté"},			//	Observed Weight
	{ L_WORD150 ,L"Insérer le code de sécurité"},			//	Enter PIN code:
	{ L_WORD151 ,L"Réglage de la sonde gain"},			//	Set sensor gain
	{ L_WORD152 ,L"Réglage de la sonde valeur"},			//	Set sensor value
	{ L_WORD153 ,L"Alarte"},			//	Warning
	{ L_WORD154 ,L"Vous êtes sur le point d'ajuster la sonde gain; ceci peut en affecter l'exactitude!"},			//	You are about to adjust the sensor gain. This may affect the accuracy!
	{ L_WORD155 ,L"Vous êtes sur le point d'ajuster la sonde; ceci peut en affecter l'exactitude!"},			//	You are about to adjust the sensor. This may affect the accuracy!
	{ L_WORD156 ,L"Mise à zéro"},			//	Zero adjust
	{ L_WORD157 ,L"Valeurs de sonde"},			//	Sensor values
	{ L_WORD158 ,L"Haute ligne de pression"},			//	High Line Press
	{ L_WORD159 ,L"Faible ligne de pression"},			//	Low Line Press
	{ L_WORD160 ,L"Mise à zero de la ligne \n de la sonde de pression"},			//	Zero adjust line \n pressure sensor
	{ L_WORD161 ,L"OK"},			//	OK
	{ L_WORD162 ,L"Oui"},			//	Yes
	{ L_WORD163 ,L"Non"},			//	No
	{ L_WORD164 ,L"Poursuivre?"},			//	Continue?
	{ L_WORD165 ,L"Vue détaillée de l'alerte"},			//	Detail view warning:
	{ L_WORD166 ,L"Sélectionner un réservoir en pressant le bouton Détail dans la rangée"},			//	Select a tank by pressing on the row and push Detail button.
	{ L_WORD167 ,L"Précédent"},			//	< Prev
	{ L_WORD168 ,L"Prochain"},			//	Next >
	{ L_WORD169 ,L"Admission"},			//	Ackn.
	{ L_WORD170 ,L"Description"},			//	Description
	{ L_WORD171 ,L"Augmentation"},			//	Rised
	{ L_WORD172 ,L"Réinitialiser"},			//	Reset
	{ L_WORD173 ,L"Sans alarme"},			//	No Alarm
	{ L_WORD174 ,L"Réglage de la date (jj.mm.aa)"},			//	Set date (dd.mm.yy)
	{ L_WORD175 ,L"Réglage de l'heure (hh.mm.ss)"},			//	Set time (hh.mm.ss)
	{ L_WORD176 ,L"Erreur d'insertion d'heure!"},			//	Fault in insert of Time!
	{ L_WORD177 ,L"Format de l'heure (h.m.s.)"},			//	Time format (h.m.s)
	{ L_WORD178 ,L"Erreur d'insertion de la date"},			//	Fault in insert of Date
	{ L_WORD179 ,L"Format de la date (j.m.a.)"},			//	Date format (d.m.y)
	{ L_WORD180 ,L"Insertion de nouvelle valeur"},			//	Enter new value:
	{ L_WORD181 ,L"Sans valeur"},			//	No value
	{ L_WORD182 ,L"Sans sonde(s)"},			//	No sensor(s)
	{ L_WORD183 ,L"Insérer compensation (…..)"},			//	Enter trim. (Aft is -)
	{ L_WORD184 ,L"Insérer liste (…..)"},			//	Enter list. (Port is -)
	{ L_WORD185 ,L"Entrer nouvelle densité"},			//	Enter new density:
	{ L_WORD186 ,L"0"},			//	0
	{ L_WORD187 ,L"1"},			//	1
	{ L_WORD188 ,L"Erreur"},			//	Error
	{ L_WORD189 ,L"Automatique"},			//	Auto
	{ L_WORD190 ,L"Mannuel"},			//	Manual
	{ L_WORD191 ,L"Sans erreur"},			//	No Error
	{ L_WORD192 ,L"Entrée erronée"},			//	Input error
	{ L_WORD193 ,L"Densité erronée"},			//	Density error
	{ L_WORD194 ,L"Réf. Tmp1=Réf. Tmp2"},			//	RefTmp1=RefTmp2
	{ L_WORD195 ,L"Réf. Tmp1 fixe"},			//	RefTmp1 fixed
	{ L_WORD196 ,L"Coefficient erroné"},			//	Wrong coeff
	{ L_WORD197 ,L"Valeur trop élevée"},			//	Value is too high
	{ L_WORD198 ,L"Valeur trop faible"},			//	Value is too low
	{ L_WORD199 ,L"Utiliser API"},			//	Use API
	{ L_WORD200 ,L"Utiliser réf. densité 1"},			//	Use ref.density 1
	{ L_WORD201 ,L"Sélectionner tableau API"},			//	Select API table
	{ L_WORD202 ,L"Indicateur illégal"},			//	Illegal pointer
	{ L_WORD203 ,L"Valeur illégale"},			//	Illegal value
	{ L_WORD204 ,L"Réservoir inconnu"},			//	Unknown tank
	{ L_WORD205 ,L"AD non trouvé"},			//	AD not found
	{ L_WORD206 ,L"Sans sonde de température"},			//	No tmp sensor
	{ L_WORD207 ,L"Valeur hors série"},			//	Value out of range
	{ L_WORD208 ,L"Utiliser le système d'eau de mer"},			//	Use system seawater
	{ L_WORD209 ,L"Utiliser le système de ballast"},			//	Use system ballast
	{ L_WORD210 ,L"Température haute=température faible"},			//	Lo temp=Hi temp
	{ L_WORD211 ,L"Insertion non autorisée"},			//	Input not allowed
	{ L_WORD212 ,L"Cargaison non définie"},			//	Undefined Cargo
	{ L_WORD213 ,L"Réinsertion de donnée"},			//	Retry input
	{ L_WORD214 ,L"Réf. Dns1 trop bas"},			//	Ref Dns1 too low
	{ L_WORD215 ,L"Réf. Dns1 trop haut"},			//	Ref Dns1 too high
	{ L_WORD216 ,L"Réf. Dns2 trop bas"},			//	Ref Dns2 too low
	{ L_WORD217 ,L"Réf. Dns2 trop haut"},			//	Ref Dns2 too high
	{ L_WORD218 ,L"API hors de la gamme"},			//	API out of range
	{ L_WORD219 ,L"Erreur de sonde"},			//	Sensor Error
	{ L_WORD220 ,L"Gain hors de gamme"},			//	Gain out of range
	{ L_WORD221 ,L"Employer le système eau fraîche"},			//	Use sys fresh water
	{ L_WORD222 ,L"Employer le système carburant lourd"},			//	Use sys heavy fuel
	{ L_WORD223 ,L"Employer le système diesel"},			//	Use system diesel
	{ L_WORD224 ,L"Employer le système lubrifiants"},			//	Use sys lubricants
	{ L_WORD225 ,L"Limite basse > élevée"},			//	Low > High limit
	{ L_WORD226 ,L"Limite élevée < basse"},			//	High < Low limit
	{ L_WORD227 ,L"Limite élevée = basse"},			//	High = Low limit
	{ L_WORD228 ,L"Non-adjustable"},			//	Not adjustable
	{ L_WORD229 ,L"Insertion de donnée non autorisée"},			//	No input permission
	{ L_WORD230 ,L"Sonde endommagée"},			//	Sensor is disabled
	{ L_WORD231 ,L"Employer le tableau API53"},			//	Use API53 table
	{ L_WORD232 ,L"Employer le tableau API54"},			//	Use API54 table
	{ L_WORD233 ,L"Employer la réf. de densité 2"},			//	Use ref.density 2
	{ L_WORD234 ,L"Insertion commune non-utilisable"},			//	Can't use common input
	{ L_WORD235 ,L"Dépassement possible seulement en cas d'alerte au ………………….NOT SURE…………………… ou principal"},			//	Override only possible when there are alarm on either Pre or Main
	{ L_WORD236 ,L"Sans unité"},			//	No Unit
	{ L_WORD237 ,L""/*Blank*/}, // Do not touch this string !!
	{ L_WORD238 ,L"Longueur"},			//	Length
	{ L_WORD239 ,L"Pression atmosphérique/de la vapeur"},			//	Atm/Vapour pressure
	{ L_WORD240 ,L"Pression de la cargaison/ballast"},			//	Cargo/Ballast press
	{ L_WORD241 ,L"Ligne de pression"},			//	Line pressure
	{ L_WORD242 ,L"Coefficient de densité"},			//	Density coef.
	{ L_WORD243 ,L"Angle"},			//	Angle
	{ L_WORD244 ,L"Surface disponible"},			//	Free surface
	{ L_WORD245 ,L"Moment"},			//	Moment
	{ L_WORD246 ,L"Immersion"},			//	Immersion
	{ L_WORD247 ,L"Taux de charge"},			//	Loadrate
	{ L_WORD248 ,L"Pourcent"},			//	Percent
	{ L_WORD249 ,L"Zone centre de gravité dynamique"},			//	GZ area
	{ L_WORD250 ,L"Courant"},			//	Current
	{ L_WORD251 ,L"Voltage"},			//	Voltage
	{ L_WORD252 ,L"Heure"},			//	Time
	{ L_WORD253 ,L"m. secondes"},			//	mSeconds
	{ L_WORD254 ,L"Jours"},			//	Days
	{ L_WORD255 ,L"Pieds"},			//	feet
	{ L_WORD256 ,L"d. pieds"},			//	d.feet
	{ L_WORD257 ,L"m³"},			//	m³
	{ L_WORD258 ,L"litre"},			//	litre
	{ L_WORD259 ,L"US g."},			//	US g.
	{ L_WORD260 ,L"US bls"},			//	US bls
	{ L_WORD261 ,L"tonne"},			//	ton
	{ L_WORD262 ,L"l. tonne"},			//	l.ton
	{ L_WORD263 ,L"kN"},			//	kN
	{ L_WORD264 ,L"m³/h"},			//	m³/h
	{ L_WORD265 ,L"US b/h"},			//	USb/h
	{ L_WORD266 ,L"°C"},			//	°C
	{ L_WORD267 ,L"°F"},			//	°F
	{ L_WORD268 ,L"mH2O"},			//	mH2O
	{ L_WORD269 ,L"mmH2O"},			//	mmH2O
	{ L_WORD270 ,L"mBar"},			//	mBar
	{ L_WORD271 ,L"Bar"},			//	Bar
	{ L_WORD272 ,L"Psi"},			//	Psi
	{ L_WORD273 ,L"kPa"},			//	kPa
	{ L_WORD274 ,L"InH2O"},			//	InH2O
	{ L_WORD275 ,L"InHg"},			//	InHg
	{ L_WORD276 ,L"t/m³ vac"},			//	t/m³ vac
	{ L_WORD277 ,L"t/m³ air"},			//	t/m³ air
	{ L_WORD278 ,L"lb/usg"},			//	lb/usg
	{ L_WORD279 ,L"Deg"},			//	Deg
	{ L_WORD280 ,L"Rad"},			//	Rad
	{ L_WORD281 ,L"t/m³°C"},			//	t/m³°C
	{ L_WORD282 ,L"t/m³°F"},			//	t/m³°F
	{ L_WORD283 ,L"l/g/°C"},			//	l/g/°C
	{ L_WORD284 ,L"l/g/°F"},			//	l/g/°F
	{ L_WORD285 ,L"m^4"},			//	m^4
	{ L_WORD286 ,L"Feet^4"},			//	Feet^4
	{ L_WORD287 ,L"t*m"},			//	t*m
	{ L_WORD288 ,L"lton*Ft"},			//	lton*Ft
	{ L_WORD289 ,L"kNm"},			//	kNm
	{ L_WORD290 ,L"t/cm"},			//	t/cm
	{ L_WORD291 ,L"lton/in"},			//	lton/in
	{ L_WORD292 ,L"m*Rad"},			//	m*Rad
	{ L_WORD293 ,L"%"},			//	%
	{ L_WORD294 ,L"‰"},			//	‰
	{ L_WORD295 ,L"mAmp"},			//	mAmp
	{ L_WORD296 ,L"Amp"},			//	Amp
	{ L_WORD297 ,L"Volt"},			//	Volt
	{ L_WORD298 ,L"mVolt"},			//	mVolt
	{ L_WORD299 ,L"mSec"},			//	mSec
	{ L_WORD300 ,L"Sec"},			//	Sec
	{ L_WORD301 ,L"Min"},			//	Min
	{ L_WORD302 ,L"Heures"},			//	Hours
	{ L_WORD303 ,L"Jours"},			//	Days
	{ L_WORD304 ,L"inutilisé"},			//	Unused
	{ L_WORD305 ,L"Niveau Sns"},			//	LevelSns
	{ L_WORD306 ,L"Niveau Ref"},			//	LevelRef
	{ L_WORD307 ,L"Niveau IFC"},			//	LevelFC
	{ L_WORD308 ,L"Sonorité"},			//	Sounding
	{ L_WORD309 ,L"Vide"},			//	Ullage
	{ L_WORD310 ,L"Volume %"},			//	Volume%
	{ L_WORD311 ,L"Pression"},			//	Pressure
	{ L_WORD312 ,L"Haute pression"},			//	High Press
	{ L_WORD313 ,L"Basse pression"},			//	Low Press
	{ L_WORD314 ,L"Temps de fin"},			//	FinishTime
	{ L_WORD315 ,L"Temps restant"},			//	RemTime
	{ L_WORD316 ,L"Type de cargaison"},			//	CargoType
	{ L_WORD317 ,L"Pression inférieure"},			//	Bot Press
	{ L_WORD318 ,L"Pression médiane"},			//	Mid Press
	{ L_WORD319 ,L"Pression supérieure"},			//	Upp Press
	{ L_WORD320 ,L"Pression culminante"},			//	Top Press
	{ L_WORD321 ,L"Gain de pression inférieure"},			//	BP Gain
	{ L_WORD322 ,L"Gain de pression médiane"},			//	MP Gain
	{ L_WORD323 ,L"Gain de pression supérieure"},			//	UP Gain
	{ L_WORD324 ,L"Gain de pression culminante"},			//	TP Gain
	{ L_WORD325 ,L"Déport de pression inférieure"},			//	BP Offset
	{ L_WORD326 ,L"Déport de pression médiane"},			//	MP Offset
	{ L_WORD327 ,L"Déport de pression supérieure"},			//	UP Offset
	{ L_WORD328 ,L"Déport de pression culminante"},			//	TP Offset
	{ L_WORD329 ,L"Niveau de sonde"},			//	LevS
	{ L_WORD330 ,L"Niveau de réf."},			//	LevR
	{ L_WORD331 ,L"Niveau de flottaison"},			//	LevF
	{ L_WORD332 ,L"Sonde"},			//	Snd
	{ L_WORD333 ,L"Vide"},			//	Ull
	{ L_WORD334 ,L"Volume"},			//	Vol
	{ L_WORD335 ,L"Volume %"},			//	Vol%
	{ L_WORD336 ,L"Poids"},			//	Wgt
	{ L_WORD337 ,L"Densité"},			//	Dens
	{ L_WORD338 ,L"Température"},			//	Temp
	{ L_WORD339 ,L"Pression"},			//	Pres
	{ L_WORD340 ,L"Haute température"},			//	HTmp
	{ L_WORD341 ,L"Basse température"},			//	LTmp
	{ L_WORD342 ,L"Haute pression"},			//	HiPr
	{ L_WORD343 ,L"Basse pression"},			//	LoPr
	{ L_WORD344 ,L"………NOT SURE………"},			//	LRate
	{ L_WORD345 ,L"………NOT SURE………"},			//	FTim
	{ L_WORD346 ,L"………NOT SURE………"},			//	RTim
	{ L_WORD347 ,L"………NOT SURE………"},			//	Ctyp
	{ L_WORD348 ,L"Pression inférieure"},			//	BP
	{ L_WORD349 ,L"Pression médiane"},			//	MP
	{ L_WORD350 ,L"Pression supérieure"},			//	UP
	{ L_WORD351 ,L"Pression culminante"},			//	TP
	{ L_WORD352 ,L"Gain de pression inférieure"},			//	BPGn
	{ L_WORD353 ,L"Gain de pression médiane"},			//	MPGn
	{ L_WORD354 ,L"Gain de pression supérieure"},			//	UPGn
	{ L_WORD355 ,L"Gain de pression culminante"},			//	TPGn
	{ L_WORD356 ,L"………NOT SURE………"},			//	BPOf
	{ L_WORD357 ,L"………NOT SURE………"},			//	MPOf
	{ L_WORD358 ,L"………NOT SURE………"},			//	UPOf
	{ L_WORD359 ,L"………NOT SURE………"},			//	TPOf
	{ L_WORD360 ,L"Température inférieure"},			//	Bot Temp
	{ L_WORD361 ,L"Température médiane"},			//	Mid Temp
	{ L_WORD362 ,L"Température supérieure"},			//	Upp Temp
	{ L_WORD363 ,L"Température culminante"},			//	Top Temp
	{ L_WORD364 ,L"Température inférieure"},			//	BT
	{ L_WORD365 ,L"Température médiane"},			//	MT
	{ L_WORD366 ,L"Température supérieure"},			//	UT
	{ L_WORD367 ,L"Température culminante"},			//	TT
	{ L_WORD368 ,L"Sonde atmosphérique"},			//	Atm sensor
	{ L_WORD369 ,L"Puissance 24V(1)"},			//	Power 24V(1)
	{ L_WORD370 ,L"Puissance 24V(2)"},			//	Power 24V(2)
	{ L_WORD371 ,L"Puissance 3.3V"},			//	Power 3.3V
	{ L_WORD372 ,L"Puissance 1.8V"},			//	Power 1.8V
	{ L_WORD373 ,L"Etat ……………..NOT SURE………………"},			//	OS Status
	{ L_WORD374 ,L"Etat du flash"},			//	Flash Status
	{ L_WORD375 ,L"Dénomination de fonction"},			//	Task Name
	{ L_WORD376 ,L"Durée de fonctionnement"},			//	Running time
	{ L_WORD377 ,L"Puissance 5.0V"},			//	Power 5.0V
	{ L_WORD378 ,L"Puissance 12V"},			//	Power 12V
	{ L_WORD379 ,L"Canal de ……………NOT SURE………………."},			//	Com Channel
	{ L_WORD380 ,L"Version de……………NOT SURE………………."},			//	Com Version
	{ L_WORD381 ,L""},			//	Store Ver.
	{ L_WORD382 ,L""},			//	Rx Buf Size
	{ L_WORD383 ,L""},			//	Tx Buf Size
	{ L_WORD384 ,L"Etat de la réinitialisation"},			//	Reset Status
	{ L_WORD385 ,L"Redémarrage complet"},			//	Total Restart
	{ L_WORD386 ,L"Echec du décompte"},			//	Fail count
	{ L_WORD387 ,L"Echec complet du décompte"},			//	Tot. fail cnt
	{ L_WORD388 ,L"Programme"},			//	Program
	{ L_WORD389 ,L"Puissance 24V"},			//	Power 24V
	{ L_WORD390 ,L"Numéro de série"},			//	Serial Number
	{ L_WORD391 ,L"Etat de l'unité"},			//	Unit status
	{ L_WORD392 ,L"Etat de la carte"},			//	Card status
	{ L_WORD393 ,L"Nom du cargo"},			//	Cargo Name
	{ L_WORD394 ,L""},			//	VolCorrFactor
	{ L_WORD395 ,L""},			//	VCF@Temp
	{ L_WORD396 ,L"API mesuré"},			//	Measured API
	{ L_WORD397 ,L"…. densité"},			//	Comp. Density
	{ L_WORD398 ,L"…. densité1"},			//	Op. Density1
	{ L_WORD399 ,L"… densité2"},			//	Op. Density2
	{ L_WORD400 ,L"Référence température1"},			//	Ref. Temp1
	{ L_WORD401 ,L"Référence température2"},			//	Ref. Temp2
	{ L_WORD402 ,L"Non défini"},			//	Not defined
	{ L_WORD403 ,L"Simple"},			//	Simple
	{ L_WORD404 ,L"Pression atmosphérique"},			//	AtmPress
	{ L_WORD405 ,L"Ballaste"},			//	Ballast
	{ L_WORD406 ,L"Combustible lourd"},			//	Heavy fuel
	{ L_WORD407 ,L"Diesel"},			//	Diesel
	{ L_WORD408 ,L"Lubrifiants"},			//	Lubricants
	{ L_WORD409 ,L"Eau fraîche"},			//	Fresh water
	{ L_WORD410 ,L"Eau de mer"},			//	Sea water
	{ L_WORD411 ,L"API 6A"},			//	API 6A
	{ L_WORD412 ,L"API 6B"},			//	API 6B
	{ L_WORD413 ,L"API 6D"},			//	API 6D
	{ L_WORD414 ,L"API 53A"},			//	API 53A
	{ L_WORD415 ,L"API 53B"},			//	API 53B
	{ L_WORD416 ,L"API 53D"},			//	API 53D
	{ L_WORD417 ,L"API 54A"},			//	API 54A
	{ L_WORD418 ,L"API 54B"},			//	API 54B
	{ L_WORD419 ,L"API 54D"},			//	API 54D
	{ L_WORD420 ,L"DF"},			//	DF
	{ L_WORD421 ,L"DP"},			//	DP
	{ L_WORD422 ,L"DS"},			//	DS
	{ L_WORD423 ,L"DA"},			//	DA
	{ L_WORD424 ,L"Niveau"},			//	Level
	{ L_WORD425 ,L"Compensation en degrés"},			//	Trim in deg
	{ L_WORD426 ,L"Compensation en mètres"},			//	Trim in meter
	{ L_WORD427 ,L"Liste en degrés"},			//	List in deg
	{ L_WORD428 ,L"DF (selection d'utilisateur)"},			//	DF (User select)
	{ L_WORD429 ,L"DA (selection d'utilisateur)"},			//	DA (User select)
	{ L_WORD430 ,L"DF@........"},			//	DF@Mark
	{ L_WORD431 ,L"DA@........"},			//	DA@Mark
	{ L_WORD432 ,L"DF@PP"},			//	DF@PP
	{ L_WORD433 ,L"DA@PP"},			//	DA@PP
	{ L_WORD434 ,L"Connecter/Déconnecter"},			//	On/Off
	{ L_WORD435 ,L"Données du système"},			//	System data
	{ L_WORD436 ,L"Projets"},			//	Drafts
	{ L_WORD437 ,L"Citerne de cargaison"},			//	Cargo tank
	{ L_WORD438 ,L"Autres citernes"},			//	Other tanks
	{ L_WORD439 ,L"FRO"},			//	FRO
	{ L_WORD440 ,L"G1"},			//	G1
	{ L_WORD441 ,L"G2"},			//	G2
	{ L_WORD442 ,L"G3"},			//	G3
	{ L_WORD443 ,L"NL1"},			//	NL1
	{ L_WORD444 ,L"NL2"},			//	NL2
	{ L_WORD445 ,L"Niv"},			//	Lev
	{ L_WORD446 ,L"Densité mesur."},			//	Meas. Density
	{ L_WORD447 ,L"Liste en mètres"},			//	List in meter
	{ L_WORD448 ,L"Latitude"},			//	Latitude
	{ L_WORD449 ,L"Genre"},			//	Type
	{ L_WORD450 ,L"SnsDB"},			//	SnsDB
	{ L_WORD451 ,L"Placement"},			//	Placing
	{ L_WORD452 ,L"Gamme min"},			//	MinRange
	{ L_WORD453 ,L"Gamme max"},			//	MaxRange
	{ L_WORD454 ,L"Longueur du câble"},			//	CableLength
	{ L_WORD455 ,L"Adresse TCU"},			//	TCUAddress
	{ L_WORD456 ,L"Port"},			//	Port
	{ L_WORD457 ,L"Adresse IO"},			//	IOAddress
	{ L_WORD458 ,L"Canal"},			//	Channel
	{ L_WORD459 ,L"Carte de canal AD"},			//	ADCardChn
	{ L_WORD460 ,L"Compensation"},			//	Trim
	{ L_WORD461 ,L"Liste"},			//	List
	{ L_WORD462 ,L"Noir"},			//	Black
	{ L_WORD463 ,L"Gris foncé"},			//	Dark Gray
	{ L_WORD464 ,L"Gris clair"},			//	Light Gray
	{ L_WORD465 ,L"Blanc"},			//	White
	{ L_WORD466 ,L"Bleu"},			//	Blue
	{ L_WORD467 ,L"Impression"},			//	Print
	{ L_WORD468 ,L" S" /*Etat*/},			//	S" Status
	{ L_WORD469 ,L"Utiliser bls"},			//	Use bls
	{ L_WORD470 ,L"Utiliser m³"},			//	Use m³
	{ L_WORD471 ,L"Sec"},			//	Dry
	{ L_WORD472 ,L"--.-"},			//	--.-
	{ L_WORD473 ,L"Vide"},			//	Empty
	{ L_WORD474 ,L"*****" /*fixed length!*/}, // Do not touch this string !!
	{ L_WORD475 ,L"Principal"},			//	Main
	{ L_WORD476 ,L"Pre"},			//	Pre
	{ L_WORD477 ,L""},			//	Over
	{ L_WORD478 ,L""},			//	Prot
	{ L_WORD479 ,L""},			//	Com
	{ L_WORD480 ,L""},			//	(Rx/Tx)
	{ L_WORD481 ,L"sur TCU"},			//	on TCU:
	{ L_WORD482 ,L"sur ZB485"},			//	on ZB485:
	{ L_WORD483 ,L"Chargeur de ……."},			//	BootLoader
	{ L_WORD484 ,L"Application"},			//	Application
	{ L_WORD485 ,L"Inconnu"},			//	Unknown
	{ L_WORD486 ,L"Nul"},			//	None
	{ L_WORD487 ,L"Erreur"},			//	Err
	{ L_WORD488 ,L"Non Usité"},			//	NoUs
	{ L_WORD489 ,L"Autre"},			//	Other
	{ L_WORD490 ,L"Pression"},			//	Press
	{ L_WORD491 ,L"@PP"},			//	@PP
	{ L_WORD492 ,L"@Mark"},			//	@Mark
	{ L_WORD493 ,L""},			//	Deact.
	{ L_WORD494 ,L"Actif"},			//	Active
	{ L_WORD495 ,L""},			//	Ackn.
	{ L_WORD496 ,L"Limite"},			//	Lim:
	{ L_WORD497 ,L"Valeur"},			//	Val:
	{ L_WORD498 ,L"Erreur de curseur"},			//	Pointer Error
	{ L_WORD499 ,L"Inconnu"},			//	Unk.
	{ L_WORD500 ,L"Hors Série"},			//	OutOfRange
	{ L_WORD501 ,L"….. Faute"},			//	ComFault
	{ L_WORD502 ,L"Hniv"},			//	HLev
	{ L_WORD503 ,L"Haut niveau"},			//	HighLevel
	{ L_WORD504 ,L"Haute ligne de pression"},			//	HighLinePress
	{ L_WORD505 ,L"Hlpress"},			//	HLPr
	{ L_WORD506 ,L"Haute pression"},			//	HighPressure
	{ L_WORD507 ,L"Hpress"},			//	HPre
	{ L_WORD508 ,L"Haute température"},			//	HighTemp
	{ L_WORD509 ,L"Htemp"},			//	HTmp
	{ L_WORD510 ,L"Haut voltage"},			//	High Voltage
	{ L_WORD511 ,L"Hvolt"},			//	HVolt
	{ L_WORD512 ,L"Haute pression1"},			//	HighPressure1
	{ L_WORD513 ,L"Hpress1"},			//	HPr1
	{ L_WORD514 ,L"Basse pression1"},			//	LowPressure1
	{ L_WORD515 ,L"Bpress1"},			//	LPr1
	{ L_WORD516 , L"….. Faute"},			//	ComFault
	{ L_WORD517 ,L""},			//	IOErr
	{ L_WORD518 ,L"Bas niveau"},			//	LowLevel
	{ L_WORD519 ,L"Bniv"},			//	LLev
	{ L_WORD520 ,L"Basse ligne de pression"},			//	LowLinePress
	{ L_WORD521 ,L"Blpress"},			//	LLPr
	{ L_WORD522 ,L"Basse pression"},			//	LowPressure
	{ L_WORD523 ,L"Bpress"},			//	LPre
	{ L_WORD524 ,L"Basse température"},			//	Low Temp
	{ L_WORD525 ,L"Btemp"},			//	LTmp
	{ L_WORD526 ,L"Bas voltage"},			//	Low Voltage
	{ L_WORD527 ,L"Bvolt"},			//	LVolt
	{ L_WORD528 ,L"Echec"},			//	Failure
	{ L_WORD529 ,L"Eau principale"},			//	MainWater
	{ L_WORD530 ,L"Eprin"},			//	MWat
	{ L_WORD531 ,L""},			//	OpenLoop
	{ L_WORD532 ,L""},			//	oloop
	{ L_WORD533 ,L"Trop-plein"},			//	Overfill
	{ L_WORD534 ,L"T-plein"},			//	OFill
	{ L_WORD535 ,L"Pression de l'eau"},			//	PreWater
	{ L_WORD536 ,L"Peau"},			//	PWat
	{ L_WORD537 ,L"Erreur de gamme"},			//	RangeError
	{ L_WORD538 ,L"Err AD"},			//	ADErr
	{ L_WORD539 ,L""},			//	Cnv&Cal Error
	{ L_WORD540 ,L""},			//	HWErr
	{ L_WORD541 ,L""},			//	Conv Error
	{ L_WORD542 ,L""},			//	RaErr
	{ L_WORD543 ,L"Court circuit"},			//	ShortCircuit
	{ L_WORD544 ,L""},			//	Scirc
	{ L_WORD545 ,L"Détails"},			//	Details
	{ L_WORD546 ,L"Données de calibrage"},			//	Calibration Data
	{ L_WORD547 ,L"Numéro de série"},			//	SerNum
	{ L_WORD548 ,L"Gamme"},			//	Range
	{ L_WORD549 ,L"Source de données de calibrage"},			//	CalData Source
	{ L_WORD550 ,L"Compensation de niveau"},			//	Level offset
	{ L_WORD551 ,L"Inclinomètre"},			//	Inclinometer
	{ L_WORD552 ,L"Projet"},			//	Draft
	{ L_WORD553 ,L"Mesuré"},			//	Measured
	{ L_WORD554 ,L""},			//	ch
	{ L_WORD555 ,L""},			//	Loc
	{ L_WORD556 ,L""},			//	RawVal
	{ L_WORD557 ,L""},			//	CalVal
	{ L_WORD558 ,L""},			//	CnvCalE
	{ L_WORD559 ,L""},			//	PROM
	{ L_WORD560 ,L""},			//	PC
	{ L_WORD561 ,L""},			//	TCUCal
	{ L_WORD562 ,L""},			//	AD Sns
	{ L_WORD563 ,L""},			//	TCU Sns
	{ L_WORD564 ,L""},			//	From TCU
	{ L_WORD565 ,L"Vert"},			//	Green
	{ L_WORD566 ,L"FLASH d'effacement"},			//	Erasing FLASH
	{ L_WORD567 ,L"Info"},			//	Info
	{ L_WORD568 ,L"Echec d'effacement"},			//	Erasing Failure
	{ L_WORD569 ,L"Mise à jour de programme, svp attendre"},			//	Updating program,please wait...
	{ L_WORD570 ,L"Calibration de routine,\n svp appuyer sur l'écran\n au centre de l'anneau"},			//	Runtime calibration,\n please touch the screen\n at the center of the ring
	{ L_WORD571 ,L"Abandonner"},			//	Abort
	{ L_WORD572 ,L"Appuyer ici"},			//	Press here
	{ L_WORD573 ,L"(position supérieure gauche)"},			//	(upper left position)
	{ L_WORD574 ,L"(position basse droite"},			//	(lower right position)
	{ L_WORD575 ,L"Page"},			//	Page
	{ L_WORD576 ,L"Version de données"},			//	Data version
	{ L_WORD577 ,L"Cargaison de réservoirs"},			//	Cargo tanks
	{ L_WORD578 ,L"Ballastes de réservoirs"},			//	Ballast tanks
	{ L_WORD579 ,L"Service de réservoirs"},			//	Service tanks
	{ L_WORD580 ,L"Réservoirs de combustible lourd"},			//	Heavy Fuel Oil tanks
	{ L_WORD581 ,L"Réservoirs de diesel"},			//	Diesel Oil tanks
	{ L_WORD582 ,L"Réservoirs de lubrifiant"},			//	Lubricant tanks
	{ L_WORD583 ,L"Réservoirs divers"},			//	Miscellaneous tanks
	{ L_WORD584 ,L"Réservoirs d'eau fraîche"},			//	Freshwater tanks
	{ L_WORD585 ,L"Non défini"},			//	NotDef
	{ L_WORD586 ,L"Atmosphère"},			//	Atm
	{ L_WORD587 ,L"Bas"},			//	Bottom
	{ L_WORD588 ,L"Milieu"},			//	Middle
	{ L_WORD589 ,L"Haut"},			//	Upper
	{ L_WORD590 ,L"Pression du réservoir"},			//	TankPres
	{ L_WORD591 ,L""},			//	PumpRm
	{ L_WORD592 ,L""},			//	EngRm
	{ L_WORD593 ,L"Pont"},			//	Deck
	{ L_WORD594 ,L"Pont"},			//	Deck
	{ L_WORD595 ,L"Voie"},			//	Line
	{ L_WORD596 ,L""},			//	WIMain
	{ L_WORD597 ,L""},			//	WIPre
	{ L_WORD598 ,L""},			//	Inc
	{ L_WORD599 ,L""},			//	LSw
	{ L_WORD600 ,L""},			//	Rad
	{ L_WORD601 ,L""},			//	WIng
	{ L_WORD602 ,L"Mise à zero de la pression du réservoir"},			//	Zero adjust tank pressure!
	{ L_WORD603 ,L"Les reservoirs doivent être ventilés à l'air libre"},			//	The tanks must be vented to the atmosphere. This operation affects all tanks in group.
	{ L_WORD604 ,L"Mise à zero de la/s sonde/s!"},			//	Zero adjust sensor(s)!
	{ L_WORD605 ,L"Les reservoirs doivent être vidés et pas de nettoyage durant les 30 dernières minutes. Cette opération affecte tous les réservoirs du groupe."},			//	The tanks must be empty and no tank cleaning the last 30 minutes. This operation affects all tanks in group.
	{ L_WORD606 ,L"Alerte de mise à zéro"},			//	Zeroset warning:
	{ L_WORD607 ,L"Les reservoirs doivent être ventilés à l'air libre. Cette operation affecte tous les points de pression du reservoir."},			//	The tanks must be vented to the atmosphere. This operation affects all tank pressure points.
	{ L_WORD608 ,L"Les reservoirs doivent être vidés et pas de nettoyage durant les 30 dernières minutes. Cette opération affecte tous les points de pression du réservoir."},			// 	The tanks must be empty and no tank cleaning the last 30 minutes. This operation affects all tank pressure points.
	{ L_WORD609 ,L"Densité de combustible lourd"},			//	Heavy fuel density
	{ L_WORD610 ,L"Densité de diesel"},			//	Diesel oil density
	{ L_WORD611 ,L"Densité de lubrifiants"},			//	Lubricants density
	{ L_WORD612 ,L"Densité d'eau fraîche"},			//	Fresh water density
	{ L_WORD613 ,L"Dossier tronqué"},			//	 File truncated
	{ L_WORD614 ,L"Erreur dans la fixation UNICODE"},			//	Error in UNICODE string!
	{ L_WORD615 ,L"F"},			//	F 
	{ L_WORD616 ,L"A"},			//	A 
	{ L_WORD617 ,L"P"},			//	P 
	{ L_WORD618 ,L"S"},			//	S 
	{ L_WORD619 ,L"eGAL"},			//	Even
	{ L_WORD620 ,L"Imprimante sur ce TDU"},			//	Printer on this TDU
	{ L_WORD621 ,L"Températures"},			//	Temperatures
	{ L_WORD622 ,L"Pressions de voie"},			//	Line pressures
	{ L_WORD623 ,L"Pressions de réservoir"},			//	Tank pressures
	{ L_WORD624 ,L""},			//	CnvCal
	{ L_WORD625 ,L""},			//	CnvErr
	{ L_WORD626 ,L""},			//	CalErr
	{ L_WORD627 ,L""},
	{ L_WORD628 ,L""},
	{ L_WORD629 ,L""},
	{ L_WORD630 ,L""},
	{ L_WORD631 ,L""},
	{ L_WORD632 ,L""},
	{ L_WORD633 ,L""},
	{ L_WORD634 ,L""},
	{ L_WORD635 ,L""},
	{ L_WORD636 ,L""},
	{ L_WORD637 ,L""},
	{ L_WORD638 ,L""},
	{ L_WORD639 ,L""},
	{ L_WORD640 ,L""},
	{ L_WORD641 ,L""},
	{ L_WORD642 ,L""},
	{ L_WORD643 ,L""},
	{ L_WORD644 ,L""},
	{ L_WORD645 ,L""},
	{ L_WORD646 ,L""},
	{ L_WORD647 ,L""},
	{ L_WORD648 ,L""},
	{ L_WORD649 ,L""},
	{ L_WORD650 ,L""},
};

unsigned WordsInFrenchDictionary = NELEMENTS(FrenchDictionary);

wchar_t FrenchUserManual[] = {L"           User manual for TDU\n\
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

int SizeOfFrenchUserManual= sizeof(FrenchUserManual);

