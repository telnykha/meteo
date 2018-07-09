object Form1: TForm1
  Left = -8
  Top = -8
  Width = 1382
  Height = 754
  Caption = '7'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LOT1: TLabel
    Left = 40
    Top = 72
    Width = 27
    Height = 13
    Caption = 'LOT1'
  end
  object LON1: TLabel
    Left = 248
    Top = 72
    Width = 28
    Height = 13
    Caption = 'LON1'
  end
  object LOT2: TLabel
    Left = 40
    Top = 144
    Width = 27
    Height = 13
    Caption = 'LOT2'
  end
  object LON2: TLabel
    Left = 256
    Top = 144
    Width = 28
    Height = 13
    Caption = 'LON2'
  end
  object DIST: TLabel
    Left = 56
    Top = 304
    Width = 42
    Height = 13
    Caption = 'DIST (m)'
  end
  object ANGEL: TLabel
    Left = 288
    Top = 304
    Width = 63
    Height = 13
    Caption = 'ANGEL(grad)'
  end
  object Label2: TLabel
    Left = 544
    Top = 32
    Width = 155
    Height = 24
    Caption = #1086#1073#1088#1072#1090#1085#1099#1081' '#1088#1072#1089#1095#1077#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label1: TLabel
    Left = 144
    Top = 32
    Width = 134
    Height = 24
    Caption = #1087#1088#1103#1084#1086#1081' '#1088#1072#1089#1095#1077#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 544
    Top = 72
    Width = 15
    Height = 13
    Caption = 'Lot'
  end
  object Label4: TLabel
    Left = 680
    Top = 64
    Width = 18
    Height = 13
    Caption = 'Lon'
  end
  object Label5: TLabel
    Left = 696
    Top = 400
    Width = 16
    Height = 13
    Caption = 'dtX'
  end
  object Label7: TLabel
    Left = 168
    Top = 216
    Width = 45
    Height = 24
    Caption = 'result'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 608
    Top = 224
    Width = 45
    Height = 24
    Caption = 'result'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label9: TLabel
    Left = 496
    Top = 320
    Width = 19
    Height = 24
    Caption = 'lot'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label10: TLabel
    Left = 672
    Top = 320
    Width = 26
    Height = 24
    Caption = 'lon'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label12: TLabel
    Left = 264
    Top = 360
    Width = 11
    Height = 13
    Caption = 'dx'
  end
  object Label13: TLabel
    Left = 72
    Top = 360
    Width = 11
    Height = 13
    Caption = 'dy'
  end
  object Label14: TLabel
    Left = 200
    Top = 424
    Width = 52
    Height = 13
    Caption = 'dist check '
  end
  object Label11: TLabel
    Left = 223
    Top = 471
    Width = 21
    Height = 13
    Caption = 'error'
  end
  object Label6: TLabel
    Left = 508
    Top = 404
    Width = 15
    Height = 13
    Caption = 'diY'
  end
  object Label15: TLabel
    Left = 64
    Top = 512
    Width = 41
    Height = 13
    Caption = 'delta Lot'
  end
  object Label16: TLabel
    Left = 264
    Top = 512
    Width = 48
    Height = 13
    Caption = 'delta LON'
  end
  object Label17: TLabel
    Left = 480
    Top = 168
    Width = 42
    Height = 13
    Caption = 'DIST (m)'
  end
  object Label18: TLabel
    Left = 672
    Top = 160
    Width = 56
    Height = 13
    Caption = 'angel (grad)'
  end
  object Label19: TLabel
    Left = 488
    Top = 456
    Width = 37
    Height = 13
    Caption = 'error dX'
  end
  object Label20: TLabel
    Left = 688
    Top = 456
    Width = 35
    Height = 13
    Caption = 'error dy'
  end
  object Edit1: TEdit
    Left = 42
    Top = 98
    Width = 177
    Height = 21
    TabOrder = 0
    Text = '50'
  end
  object Edit2: TEdit
    Left = 248
    Top = 96
    Width = 177
    Height = 21
    TabOrder = 1
    Text = '-100'
  end
  object Edit3: TEdit
    Left = 40
    Top = 171
    Width = 168
    Height = 21
    TabOrder = 2
    Text = '55'
  end
  object Edit4: TEdit
    Left = 249
    Top = 175
    Width = 177
    Height = 21
    TabOrder = 3
    Text = '-101'
  end
  object CULCULATE: TButton
    Left = 128
    Top = 256
    Width = 129
    Height = 33
    Caption = 'CULCULATE'
    TabOrder = 4
    OnClick = CULCULATEClick
  end
  object Edit5: TEdit
    Left = 32
    Top = 328
    Width = 129
    Height = 21
    TabOrder = 5
    Text = 'Edit5'
  end
  object Edit6: TEdit
    Left = 216
    Top = 328
    Width = 137
    Height = 21
    TabOrder = 6
    Text = 'Edit6'
  end
  object Edit7: TEdit
    Left = 480
    Top = 96
    Width = 145
    Height = 21
    TabOrder = 7
    Text = '50'
  end
  object Edit8: TEdit
    Left = 656
    Top = 96
    Width = 137
    Height = 21
    TabOrder = 8
    Text = '-100'
  end
  object Edit9: TEdit
    Left = 648
    Top = 424
    Width = 129
    Height = 21
    TabOrder = 9
    Text = '100'
  end
  object Button1: TButton
    Left = 528
    Top = 256
    Width = 225
    Height = 33
    Caption = 'culculate'
    TabOrder = 10
    OnClick = Button1Click
  end
  object Edit11: TEdit
    Left = 472
    Top = 344
    Width = 137
    Height = 21
    TabOrder = 11
    Text = 'Edit11'
  end
  object Edit12: TEdit
    Left = 664
    Top = 344
    Width = 137
    Height = 21
    TabOrder = 12
    Text = 'Edit12'
  end
  object Edit13: TEdit
    Left = 484
    Top = 427
    Width = 129
    Height = 21
    TabOrder = 13
    Text = '100'
  end
  object Edit14: TEdit
    Left = 232
    Top = 384
    Width = 129
    Height = 21
    TabOrder = 14
    Text = 'Edit14'
  end
  object Edit15: TEdit
    Left = 48
    Top = 384
    Width = 113
    Height = 21
    TabOrder = 15
    Text = 'Edit15'
  end
  object Edit16: TEdit
    Left = 56
    Top = 424
    Width = 129
    Height = 21
    TabOrder = 16
    Text = 'Edit16'
  end
  object Edit17: TEdit
    Left = 54
    Top = 471
    Width = 130
    Height = 21
    TabOrder = 17
    Text = 'Edit17'
  end
  object Edit10: TEdit
    Left = 640
    Top = 189
    Width = 121
    Height = 21
    TabOrder = 18
    Text = '45'
  end
  object Edit18: TEdit
    Left = 56
    Top = 544
    Width = 113
    Height = 21
    TabOrder = 19
    Text = 'Edit18'
  end
  object Edit19: TEdit
    Left = 264
    Top = 544
    Width = 97
    Height = 21
    TabOrder = 20
    Text = 'Edit19'
  end
  object Edit20: TEdit
    Left = 480
    Top = 192
    Width = 129
    Height = 21
    TabOrder = 21
    Text = '10000'
  end
  object CheckBox1: TCheckBox
    Left = 504
    Top = 128
    Width = 65
    Height = 17
    Caption = 'north'
    Checked = True
    State = cbChecked
    TabOrder = 22
  end
  object CheckBox2: TCheckBox
    Left = 664
    Top = 128
    Width = 57
    Height = 17
    Caption = 'west'
    Checked = True
    State = cbChecked
    TabOrder = 23
  end
  object Edit21: TEdit
    Left = 480
    Top = 480
    Width = 137
    Height = 21
    TabOrder = 24
    Text = 'Edit21'
  end
  object Edit22: TEdit
    Left = 680
    Top = 480
    Width = 129
    Height = 21
    TabOrder = 25
    Text = 'Edit22'
  end
end
