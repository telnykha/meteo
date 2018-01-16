object Form1: TForm1
  Left = 184
  Top = 139
  Width = 928
  Height = 574
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 8
    Width = 561
    Height = 457
  end
  object Button1: TButton
    Left = 664
    Top = 24
    Width = 209
    Height = 57
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 584
    Top = 120
    Width = 313
    Height = 129
    ScrollBars = ssBoth
    TabOrder = 1
    OnMouseDown = Memo1MouseDown
  end
  object Edit1: TEdit
    Left = 576
    Top = 336
    Width = 209
    Height = 21
    Enabled = False
    TabOrder = 2
    Text = 'Edit1'
    OnChange = Edit1Change
  end
  object OpenDialog1: TOpenDialog
    Filter = 'txt'
    Left = 176
    Top = 32
  end
end
