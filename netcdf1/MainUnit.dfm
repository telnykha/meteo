object Form1: TForm1
  Left = 461
  Top = 135
  Width = 500
  Height = 503
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
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 151
    Height = 13
    Caption = #1043#1083#1086#1073#1072#1083#1100#1085#1099#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1099#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 64
    Width = 132
    Height = 13
    Caption = #1043#1083#1086#1073#1072#1083#1100#1085#1099#1077' '#1072#1090#1088#1080#1073#1091#1090#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 120
    Width = 80
    Height = 13
    Caption = #1056#1072#1079#1084#1077#1088#1085#1086#1089#1090#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Button1: TButton
    Left = 8
    Top = 184
    Width = 105
    Height = 25
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083'...'
    TabOrder = 0
    OnClick = Button1Click
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 32
    Width = 209
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
  end
  object ComboBox2: TComboBox
    Left = 8
    Top = 88
    Width = 209
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 2
  end
  object ComboBox3: TComboBox
    Left = 8
    Top = 144
    Width = 209
    Height = 21
    ItemHeight = 13
    TabOrder = 3
    Text = 'ComboBox3'
  end
  object Button2: TButton
    Left = 224
    Top = 30
    Width = 75
    Height = 25
    Caption = #1057#1074#1086#1081#1089#1090#1074#1072'...'
    TabOrder = 4
    OnClick = Button2Click
  end
  object OpenDialog1: TOpenDialog
    Filter = 'netcdf files|*.nc'
    Left = 104
  end
end
