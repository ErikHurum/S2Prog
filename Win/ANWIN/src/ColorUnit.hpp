// CodeGear C++Builder
// Copyright (c) 1995, 2013 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ColorUnit.pas' rev: 26.00 (Windows)

#ifndef ColorunitHPP
#define ColorunitHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <Vcl.Themes.hpp>	// Pascal unit
#include <Vcl.Mask.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Colorunit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TEdit;
class PASCALIMPLEMENTATION TEdit : public Vcl::Stdctrls::TEdit
{
	typedef Vcl::Stdctrls::TEdit inherited;
	
public:
	/* TCustomEdit.Create */ inline __fastcall virtual TEdit(System::Classes::TComponent* AOwner) : Vcl::Stdctrls::TEdit(AOwner) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TEdit(HWND ParentWindow) : Vcl::Stdctrls::TEdit(ParentWindow) { }
	/* TWinControl.Destroy */ inline __fastcall virtual ~TEdit(void) { }
	
};


class DELPHICLASS TLabel;
class PASCALIMPLEMENTATION TLabel : public Vcl::Stdctrls::TLabel
{
	typedef Vcl::Stdctrls::TLabel inherited;
	
public:
	/* TCustomLabel.Create */ inline __fastcall virtual TLabel(System::Classes::TComponent* AOwner) : Vcl::Stdctrls::TLabel(AOwner) { }
	
public:
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TLabel(void) { }
	
};


class DELPHICLASS TMemo;
class PASCALIMPLEMENTATION TMemo : public Vcl::Stdctrls::TMemo
{
	typedef Vcl::Stdctrls::TMemo inherited;
	
public:
	/* TCustomMemo.Create */ inline __fastcall virtual TMemo(System::Classes::TComponent* AOwner) : Vcl::Stdctrls::TMemo(AOwner) { }
	/* TCustomMemo.Destroy */ inline __fastcall virtual ~TMemo(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TMemo(HWND ParentWindow) : Vcl::Stdctrls::TMemo(ParentWindow) { }
	
};


class DELPHICLASS TButtonedEdit;
class PASCALIMPLEMENTATION TButtonedEdit : public Vcl::Extctrls::TButtonedEdit
{
	typedef Vcl::Extctrls::TButtonedEdit inherited;
	
public:
	/* TCustomButtonedEdit.Create */ inline __fastcall virtual TButtonedEdit(System::Classes::TComponent* AOwner) : Vcl::Extctrls::TButtonedEdit(AOwner) { }
	/* TCustomButtonedEdit.Destroy */ inline __fastcall virtual ~TButtonedEdit(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TButtonedEdit(HWND ParentWindow) : Vcl::Extctrls::TButtonedEdit(ParentWindow) { }
	
};


class DELPHICLASS TLabeledEdit;
class PASCALIMPLEMENTATION TLabeledEdit : public Vcl::Extctrls::TLabeledEdit
{
	typedef Vcl::Extctrls::TLabeledEdit inherited;
	
public:
	/* TCustomLabeledEdit.Create */ inline __fastcall virtual TLabeledEdit(System::Classes::TComponent* AOwner) : Vcl::Extctrls::TLabeledEdit(AOwner) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TLabeledEdit(HWND ParentWindow) : Vcl::Extctrls::TLabeledEdit(ParentWindow) { }
	/* TWinControl.Destroy */ inline __fastcall virtual ~TLabeledEdit(void) { }
	
};


class DELPHICLASS TPanel;
class PASCALIMPLEMENTATION TPanel : public Vcl::Extctrls::TPanel
{
	typedef Vcl::Extctrls::TPanel inherited;
	
public:
	/* TCustomPanel.Create */ inline __fastcall virtual TPanel(System::Classes::TComponent* AOwner) : Vcl::Extctrls::TPanel(AOwner) { }
	
public:
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TPanel(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TPanel(HWND ParentWindow) : Vcl::Extctrls::TPanel(ParentWindow) { }
	
};


class DELPHICLASS TEditStyleHookColor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TEditStyleHookColor : public Vcl::Stdctrls::TEditStyleHook
{
	typedef Vcl::Stdctrls::TEditStyleHook inherited;
	
private:
	HIDESBASE void __fastcall UpdateColors(void);
	
protected:
	virtual void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	
public:
	__fastcall virtual TEditStyleHookColor(Vcl::Controls::TWinControl* AControl);
public:
	/* TMouseTrackControlStyleHook.Destroy */ inline __fastcall virtual ~TEditStyleHookColor(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Colorunit */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_COLORUNIT)
using namespace Colorunit;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ColorunitHPP
