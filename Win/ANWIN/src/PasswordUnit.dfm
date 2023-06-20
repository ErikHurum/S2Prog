object PasswordDlg: TPasswordDlg
  Left = 519
  Top = 244
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BiDiMode = bdLeftToRight
  BorderStyle = bsDialog
  Caption = 'Unlock'
  ClientHeight = 120
  ClientWidth = 248
  Color = clBtnFace
  ParentFont = True
  FormStyle = fsMDIForm
  ParentBiDiMode = False
  Position = poOwnerFormCenter
  Scaled = False
  OnActivate = FormActivate
  TextHeight = 15
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 83
    Height = 15
    Caption = 'Enter PIN-code:'
  end
  object Label2: TLabel
    Left = 93
    Top = 6
    Width = 4
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object OKBtn: TButton
    Left = 6
    Top = 59
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
    OnClick = OKBtnClick
  end
  object CancelBtn: TButton
    Left = 87
    Top = 59
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object PasswordEdit: TEdit
    Left = 8
    Top = 32
    Width = 154
    Height = 23
    Hint = 'PIN code'
    PasswordChar = '*'
    TabOrder = 0
    OnKeyDown = PasswordEditKeyDown
  end
end
