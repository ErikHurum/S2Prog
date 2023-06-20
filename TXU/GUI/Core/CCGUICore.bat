@ECHO OFF
ECHO CCGUICore.BAT:       Compiling GUI\Core
CALL CC GUI2DLib
CALL CC GUI__AddSpaceHex
CALL CC GUI__Arabic
CALL CC GUI__BiDi
CALL CC GUI__CalcTextRect
CALL CC GUI__DivideRound
CALL CC GUI__DivideRound32
CALL CC GUI__DrawBitmap16bpp
CALL CC GUI__GetCursorPos
CALL CC GUI__GetFontSizeY
CALL CC GUI__GetNumChars
CALL CC GUI__HandleEOLine
CALL CC GUI__IntersectRect
CALL CC GUI__IntersectRects
CALL CC GUI__memcpy
CALL CC GUI__memset
CALL CC GUI__memset16
CALL CC GUI__Read
CALL CC GUI__ReduceRect
CALL CC GUI__SetPixelAlpha
CALL CC GUI__SetText
CALL CC GUI__strcmp
CALL CC GUI__strlen
CALL CC GUI__Wrap
CALL CC GUI_AddBin
CALL CC GUI_AddDec
CALL CC GUI_AddDecMin
CALL CC GUI_AddDecShift
CALL CC GUI_AddHex
CALL CC GUI_ALLOC_AllocInit
CALL CC GUI_ALLOC_AllocZero
CALL CC GUI_BMP
CALL CC GUI_BMP_DrawScaled
CALL CC GUI_BMP_Serialize
CALL CC GUI_CalcColorDist
CALL CC GUI_ClearRectEx
CALL CC GUI_Color2VisColor
CALL CC GUI_CursorArrowL
CALL CC GUI_CursorArrowLI
CALL CC GUI_CursorArrowLPx
CALL CC GUI_CursorArrowM
CALL CC GUI_CursorArrowMI
CALL CC GUI_CursorArrowMPx
CALL CC GUI_CursorArrowS
CALL CC GUI_CursorArrowSI
CALL CC GUI_CursorArrowSPx
CALL CC GUI_CursorCrossL
CALL CC GUI_CursorCrossLI
CALL CC GUI_CursorCrossLPx
CALL CC GUI_CursorCrossM
CALL CC GUI_CursorCrossMI
CALL CC GUI_CursorCrossMPx
CALL CC GUI_CursorCrossS
CALL CC GUI_CursorCrossSI
CALL CC GUI_CursorCrossSPx
CALL CC GUI_CursorHeaderM
CALL CC GUI_CursorHeaderMI
CALL CC GUI_CursorHeaderMPx
CALL CC GUI_CursorPal
CALL CC GUI_CursorPalI
CALL CC GUI_DispBin
CALL CC GUI_DispCEOL
CALL CC GUI_DispChar
CALL CC GUI_DispChars
CALL CC GUI_DispHex
CALL CC GUI_DispString
CALL CC GUI_DispStringAt
CALL CC GUI_DispStringAtCEOL
CALL CC GUI_DispStringHCenter
CALL CC GUI_DispStringInRect
CALL CC GUI_DispStringInRectEx
CALL CC GUI_DispStringInRectWrap
CALL CC GUI_DispStringLen
CALL CC GUI_DrawBitmap_24
CALL CC GUI_DrawBitmap_555
CALL CC GUI_DrawBitmap_565
CALL CC GUI_DrawBitmap_888
CALL CC GUI_DrawBitmap_8888
CALL CC GUI_DrawBitmap
CALL CC GUI_DrawBitmapEx
CALL CC GUI_DrawBitmapExp
CALL CC GUI_DrawBitmapHWAlpha
CALL CC GUI_DrawBitmapMag
CALL CC GUI_DrawFocusRect
CALL CC GUI_DrawGradient
CALL CC GUI_DrawGraph
CALL CC GUI_DrawGraphEx
CALL CC GUI_DrawHLine
CALL CC GUI_DrawLine
CALL CC GUI_DrawPie
CALL CC GUI_DrawPixel
CALL CC GUI_DrawPoint
CALL CC GUI_DrawPolygon
CALL CC GUI_DrawPolyline
CALL CC GUI_DrawRectEx
CALL CC GUI_DrawVLine
CALL CC GUI_ErrorOut
CALL CC GUI_Exec
CALL CC GUI_FillPolygon
CALL CC GUI_FillRect
CALL CC GUI_FillRectEx
CALL CC GUI_GetBitmapPixelColor
CALL CC GUI_GetBitmapPixelIndex
CALL CC GUI_GetBlankCols
CALL CC GUI_GetClientRect
CALL CC GUI_GetColor
CALL CC GUI_GetDispPos
CALL CC GUI_GetDrawMode
CALL CC GUI_GetFont
CALL CC GUI_GetFontInfo
CALL CC GUI_GetFontSizeY
CALL CC GUI_GetLineStyle
CALL CC GUI_GetOrg
CALL CC GUI_GetStringDistX
CALL CC GUI_GetTextAlign
CALL CC GUI_GetTextExtend
CALL CC GUI_GetTextMode
CALL CC GUI_GetVersionString
CALL CC GUI_GetYSizeOfFont
CALL CC GUI_GIF
CALL CC GUI_GIF_DrawScaled
CALL CC GUI_Goto
CALL CC GUI_InvertRect
CALL CC GUI_IsInFont
CALL CC GUI_Log
CALL CC GUI_MergeRect
CALL CC GUI_MOUSE
CALL CC GUI_MOUSE_DriverPS2
CALL CC GUI_MoveRect
CALL CC GUI_OnKey
CALL CC GUI_Pen
CALL CC GUI_PID
CALL CC GUI_RectsIntersect
CALL CC GUI_SaveContext
CALL CC GUI_ScreenSize
CALL CC GUI_SelectLayer
CALL CC GUI_SelectLCD
CALL CC GUI_SetAlpha
CALL CC GUI_SetClipRect
CALL CC GUI_SetColor
CALL CC GUI_SetColorIndex
CALL CC GUI_SetDecChar
CALL CC GUI_SetDefault
CALL CC GUI_SetDrawMode
CALL CC GUI_SetFont
CALL CC GUI_SetLBorder
CALL CC GUI_SetLineStyle
CALL CC GUI_SetLUTColor
CALL CC GUI_SetLUTColorEx
CALL CC GUI_SetLUTEntry
CALL CC GUI_SetOrg
CALL CC GUI_SetPixelIndex
CALL CC GUI_SetTextAlign
CALL CC GUI_SetTextMode
CALL CC GUI_SetTextStyle
CALL CC GUI_SIF
CALL CC GUI_SIF_Prop
CALL CC GUI_SIF_PropExt
CALL CC GUI_SIF_PropExtFrmInfo
CALL CC GUI_SIF_PropFrm
CALL CC GUI_SPRITE
CALL CC GUI_TOUCH
CALL CC GUI_TOUCH_DriverAnalog
CALL CC GUI_TOUCH_StoreState
CALL CC GUI_TOUCH_StoreUnstable
CALL CC GUI_UC
CALL CC GUI_UC_ConvertUC2UTF8
CALL CC GUI_UC_ConvertUTF82UC
CALL CC GUI_UC_DispString
CALL CC GUI_UC_EncodeNone
CALL CC GUI_UC_EncodeUTF8
CALL CC GUI_WaitKey
CALL CC GUI_WaitEvent
CALL CC GUI_Warn
CALL CC GUI_XBF
CALL CC GUI_XBF_Prop
CALL CC GUI_XBF_PropExt
CALL CC GUI_XBF_PropFrm
CALL CC GUIAlloc
CALL CC GUIAlloc1
CALL CC GUIArc
CALL CC GUIChar
CALL CC GUICharLine
CALL CC GUICharM
CALL CC GUICharP
CALL CC GUICharPExt
CALL CC GUICharPFrm
CALL CC GUICirc
CALL CC GUIColor2Index
CALL CC GUICore
CALL CC GUICurs
CALL CC GUICurs1
CALL CC GUIEncExt
CALL CC GUIEncJS
CALL CC GUIIndex2Color
CALL CC GUIPolyE
CALL CC GUIPolyM
CALL CC GUIPolyR
CALL CC GUIRealloc
CALL CC GUIStream
CALL CC GUITask
CALL CC GUITime
CALL CC GUITimer
CALL CC GUIUC0
CALL CC GUIVal
CALL CC GUIValf
CALL CC LCD
CALL CC LCD_API
CALL CC LCD_Curs
CALL CC LCD_GetColorIndex
CALL CC LCD_GetEx
CALL CC LCD_GetNumDisplays
CALL CC LCD_GetPixelColor
CALL CC LCD_Index2ColorEx
CALL CC LCD_L0_Generic
CALL CC LCD_MixColors256
CALL CC LCD_Mirror
CALL CC LCD_NextPixelAPI
CALL CC LCD_ReadRect
CALL CC LCD_Rotate180
CALL CC LCD_RotateCW
CALL CC LCD_RotateCCW
CALL CC LCD_SelectLCD
CALL CC LCD_SetAlphaEx
CALL CC LCD_SetAPI
CALL CC LCD_SetClipRectEx
CALL CC LCD_UpdateColorIndices
CALL CC LCDAA
CALL CC LCDColor
CALL CC LCDGetP
CALL CC LCDInfo
CALL CC LCDInfo0
CALL CC LCDInfo1
CALL CC LCDL0Delta
CALL CC LCDL0Mag
CALL CC LCDP1
CALL CC LCDP555_Index2Color
CALL CC LCDP565_Index2Color
CALL CC LCDP888_Index2Color
CALL CC LCDP8888_Index2Color
CALL CC LCDPM555_Index2Color
CALL CC LCDPM565_Index2Color
CALL CC LCDPM888_Index2Color
CALL CC LCDRLE16
CALL CC LCDRLE4
CALL CC LCDRLE8
