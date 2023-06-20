#ifndef __DXFNAMESPACES_H__
#define __DXFNAMESPACES_H__
#pragma once

namespace DxfErrorCodes{
	enum DxfError{
        NoError = 0,
		CannotOpenFile,
		UnsupportedVersion,
		LayerNotFound
	};
};

#define _BEGCODE(name)	namespace Dxf##name##GroupCodes{ enum {
#define _ENDCODE		}; };

_BEGCODE(Layer)
	LayerName = 2,
	ColorNumber = 62,
	PlottingFlag = 290
_ENDCODE

_BEGCODE(ExtLimit)
	XCoord = 10,
	YCoord = 20,
	ZCoord = 30,
_ENDCODE


_BEGCODE(Text)
	XCoord      = 10,
	YCoord      = 20,
	ZCoord      = 30,
	Layer       = 8,
    TextStyle   = 7,
	Height      = 40,
	Width       = 41,
	Value       = 1,
    XAngle      = 11,
    YAngle      = 21,
    ZAngle      = 31,
    AttachPnt   = 71,
    DrawDir     = 72,
	LineSpace   = 73
_ENDCODE

_BEGCODE(Polyline)
	NumVertex   = 90,
	Layer       = 8,
	XCoord      = 10,
	YCoord      = 20,
	PenSize     = 39,
    PolyLineFlag= 70,
	Bulge       = 42
_ENDCODE

_BEGCODE(Line)
	NumVertex = 90,
	Layer    = 8,
    EntityHandle    = 5,
    SoftPtrHandle   = 330,
    SubClassmarker  = 100,
	XCoord1  = 10,
	XCoord2  = 11,
	YCoord1  = 20,
	YCoord2  = 21,
	PenSize  = 39,
_ENDCODE

_BEGCODE(Hatch)
    BoundryPath = 92,
    NumEdges    = 93,
    EdgeType    = 72,
    ExtusionX   = 210,
    ExtusionY   = 220,
    ExtusionZ   = 230,
    Name        = 2,
	NumVertex = 90,
	Layer    = 8,
    EntityHandle    = 5,
    SoftPtrHandle   = 330,
    SubClassmarker  = 100,
	XCoord1  = 10,
	XCoord2  = 11,
	YCoord1  = 20,
	YCoord2  = 21,
	ZCoord1  = 30,
	ZCoord2  = 31,
	Bulge = 42,
	PenSize  = 39,
_ENDCODE


#include ".\dxfvalue.h"

#define _BEGNSEC(name) namespace Dxf##name##SectionCodes{ const CDxfValue
#define _ENDNSEC(name) name##SectionEnd( 0, "ENDSEC" );};

_BEGNSEC(Common)
	SectionBegin( 0, "SECTION" ),
	SectionHeaderBegin( 2, "HEADER" ),
	SectionTablesBegin( 2, "TABLES" ),
	SectionEntitiesBegin( 2, "ENTITIES" ),
_ENDNSEC(Common)

_BEGNSEC(Header)
	VersionVariable( 9, "$ACADVER" ),
	SupportedVersion( 1, "AC101" ),        // Was "AC1015"
	SupportedVersion2( 1, "AC102" ),
    ExtMinBegin( 9, "$EXTMIN" ),
    ExtMaxBegin( 9, "$EXTMAX" ),
_ENDNSEC(Header)

_BEGNSEC(Table)
	TableBegin( 0, "TABLE" ),
		TableLayer( 2, "LAYER" ),
		LayerBegin( 0, "LAYER" ),
	TableEnd( 0, "ENDTAB" ),
_ENDNSEC(Table)

_BEGNSEC(Entities)
		PolylineBegin( 0, "LWPOLYLINE" ),
        LineBegin( 0, "LINE" ),
        HatchBegin( 0, "HATCH" ),
		TextBegin( 0, "TEXT" ),
		MTextBegin( 0, "MTEXT" ),
_ENDNSEC(Entities)
#endif //__DXFNAMESPACES_H__