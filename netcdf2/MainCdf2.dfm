object Form2: TForm2
  Left = 926
  Top = 182
  Caption = 'Form2'
  ClientHeight = 583
  ClientWidth = 918
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 560
    Top = 160
    Width = 105
    Height = 105
  end
  object Splitter1: TSplitter
    Left = 461
    Top = 41
    Height = 435
    ExplicitLeft = 344
    ExplicitTop = 200
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 918
    Height = 41
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alTop
    TabOrder = 0
    OnResize = Panel1Resize
    object SpeedButton1: TSpeedButton
      Left = 0
      Top = 5
      Width = 32
      Height = 32
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
        5555555555555555555555555555555555555555555555555555555555555555
        555555555555555555555555555555555555555FFFFFFFFFF555550000000000
        55555577777777775F55500B8B8B8B8B05555775F555555575F550F0B8B8B8B8
        B05557F75F555555575F50BF0B8B8B8B8B0557F575FFFFFFFF7F50FBF0000000
        000557F557777777777550BFBFBFBFB0555557F555555557F55550FBFBFBFBF0
        555557F555555FF7555550BFBFBF00055555575F555577755555550BFBF05555
        55555575FFF75555555555700007555555555557777555555555555555555555
        5555555555555555555555555555555555555555555555555555}
      NumGlyphs = 2
      OnClick = SpeedButton1Click
    end
    object SpeedButton3: TSpeedButton
      Left = 36
      Top = 4
      Width = 32
      Height = 32
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      AllowAllUp = True
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333FFFFFFFFFFFFF33000077777770033377777777777773F000007888888
        00037F3337F3FF37F37F00000780088800037F3337F77F37F37F000007800888
        00037F3337F77FF7F37F00000788888800037F3337777777337F000000000000
        00037F3FFFFFFFFFFF7F00000000000000037F77777777777F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF00037F7F333333337F7F000FFFFFFFFF
        00037F7F333333337F7F000FFFFFFFFF07037F7F33333333777F000FFFFFFFFF
        0003737FFFFFFFFF7F7330099999999900333777777777777733}
      NumGlyphs = 2
      OnClick = SpeedButton3Click
    end
    object SpeedButton2: TSpeedButton
      Left = 68
      Top = 4
      Width = 32
      Height = 32
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333333333333333FF3333333333333744333333333333F773333333333337
        44473333333333F777F3333333333744444333333333F7733733333333374444
        4433333333F77333733333333744444447333333F7733337F333333744444444
        433333F77333333733333744444444443333377FFFFFFF7FFFFF999999999999
        9999733777777777777333CCCCCCCCCC33333773FF333373F3333333CCCCCCCC
        C333333773FF3337F333333333CCCCCCC33333333773FF373F3333333333CCCC
        CC333333333773FF73F33333333333CCCCC3333333333773F7F3333333333333
        CCC333333333333777FF33333333333333CC3333333333333773}
      NumGlyphs = 2
      OnClick = SpeedButton2Click
    end
    object SpeedButton4: TSpeedButton
      Left = 100
      Top = 4
      Width = 32
      Height = 32
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33333FF3333333333333447333333333333377FFF33333333333744473333333
        333337773FF3333333333444447333333333373F773FF3333333334444447333
        33333373F3773FF3333333744444447333333337F333773FF333333444444444
        733333373F3333773FF333334444444444733FFF7FFFFFFF77FF999999999999
        999977777777777733773333CCCCCCCCCC3333337333333F7733333CCCCCCCCC
        33333337F3333F773333333CCCCCCC3333333337333F7733333333CCCCCC3333
        333333733F77333333333CCCCC333333333337FF7733333333333CCC33333333
        33333777333333333333CC333333333333337733333333333333}
      NumGlyphs = 2
      OnClick = SpeedButton4Click
    end
    object SpeedButton5: TSpeedButton
      Left = 134
      Top = 4
      Width = 32
      Height = 32
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33333333333333333333EEEEEEEEEEEEEEE333FFFFFFFFFFFFF3E00000000000
        00E337777777777777F3E0F77777777770E337F33333333337F3E0F333333333
        70E337F3333F333337F3E0F33303333370E337F3337FF33337F3E0F333003333
        70E337F33377FF3337F3E0F33300033370E337F333777FF337F3E0F333000033
        70E337F33377773337F3E0F33300033370E337F33377733337F3E0F333003333
        70E337F33377333337F3E0F33303333370E337F33373333337F3E0F333333333
        70E337F33333333337F3E0FFFFFFFFFFF0E337FFFFFFFFFFF7F3E00000000000
        00E33777777777777733EEEEEEEEEEEEEEE33333333333333333}
      NumGlyphs = 2
      OnClick = SpeedButton5Click
    end
    object ComboBox3: TComboBox
      Left = 182
      Top = 7
      Width = 209
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Style = csDropDownList
      TabOrder = 0
      OnChange = ComboBox3Change
    end
    object CheckBox1: TCheckBox
      Left = 400
      Top = 13
      Width = 169
      Height = 17
      Caption = #1069#1082#1089#1087#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1076#1072#1085#1085#1099#1077
      TabOrder = 1
      OnClick = CheckBox1Click
    end
  end
  object FImage1: TFImage
    Left = 0
    Top = 41
    Width = 461
    Height = 435
    Cursor = 1
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    BorderStyle = bsFSingle
    Align = alLeft
    ParentColor = False
    OnMouseMove = FImage1MouseMove
    OnMouseUp = FImage1MouseUp
  end
  object Panel2: TPanel
    Left = 0
    Top = 476
    Width = 918
    Height = 88
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alBottom
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 2
    object Label3: TLabel
      Left = 456
      Top = 44
      Width = 42
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Azmuth'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      WordWrap = True
    end
    object Label1: TLabel
      Left = 452
      Top = 8
      Width = 54
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Elevation'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      WordWrap = True
    end
    object Chart1: TChart
      Left = 1
      Top = 1
      Width = 224
      Height = 86
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      BackWall.Brush.Style = bsClear
      Legend.Visible = False
      Title.Text.Strings = (
        'Azmuth')
      View3D = False
      Align = alLeft
      TabOrder = 0
      DefaultCanvas = 'TGDIPlusCanvas'
      ColorPaletteIndex = 13
      object Series1: TFastLineSeries
        SeriesColor = clRed
        LinePen.Color = clRed
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
    object Chart2: TChart
      Left = 225
      Top = 1
      Width = 224
      Height = 86
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      BackWall.Brush.Style = bsClear
      Legend.Visible = False
      Title.Text.Strings = (
        'Elevation')
      View3D = False
      Align = alLeft
      TabOrder = 1
      DefaultCanvas = 'TGDIPlusCanvas'
      ColorPaletteIndex = 13
      object FastLineSeries1: TFastLineSeries
        SeriesColor = clRed
        LinePen.Color = clRed
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
    object ComboBox1: TComboBox
      Left = 512
      Top = 8
      Width = 73
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Style = csDropDownList
      TabOrder = 2
      OnChange = ComboBox1Change
    end
    object ComboBox2: TComboBox
      Left = 512
      Top = 40
      Width = 73
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Style = csDropDownList
      TabOrder = 3
      OnChange = ComboBox2Change
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 564
    Width = 918
    Height = 19
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Panels = <
      item
        Text = 'x = y = r = psi = '
        Width = 50
      end>
  end
  object Panel3: TPanel
    Left = 464
    Top = 41
    Width = 454
    Height = 435
    Align = alClient
    Caption = 'Panel3'
    TabOrder = 4
    object Splitter2: TSplitter
      Left = 1
      Top = 301
      Width = 452
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      ExplicitTop = 1
      ExplicitWidth = 255
    end
    object ListView1: TListView
      Left = 1
      Top = 304
      Width = 452
      Height = 130
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alBottom
      Columns = <
        item
          Caption = #8470
        end
        item
          Caption = #1055#1083#1086#1097#1072#1076#1100
        end
        item
          Caption = #1055#1077#1088#1080#1084#1077#1090#1088
        end
        item
          Caption = 'X - '#1062'.'#1084
        end
        item
          Caption = 'Y - '#1094'.'#1084'.'
        end
        item
          Caption = #1041#1086#1083#1100#1096#1072#1103' '#1087#1086#1083#1091#1086#1089#1100
        end
        item
          Caption = #1052#1072#1083#1072#1103' '#1087#1086#1083#1091#1086#1089#1100
        end
        item
          Caption = #1059#1075#1086#1083' '#1085#1072#1082#1083#1086#1085#1072
        end
        item
          Caption = #1050#1086#1101#1092'. '#1092#1086#1088#1084#1099
        end
        item
          Caption = 'TETA'
        end
        item
          Caption = 'MI'
        end
        item
          Caption = 'MA'
        end
        item
          Caption = 'S'
        end>
      TabOrder = 0
      ViewStyle = vsReport
    end
    object FImage2: TFImage
      Left = 1
      Top = 1
      Width = 452
      Height = 300
      BorderStyle = bsFSingle
      Align = alClient
      ParentColor = False
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'groza|*.XML'
    Options = [ofHideReadOnly, ofNoChangeDir, ofAllowMultiSelect, ofEnableSizing]
    Left = 8
    Top = 48
  end
  object SaveDialog1: TSaveDialog
    Filter = 'png images|*.png|jpeg images|*.jpg|awp images|*.awp'
    Left = 40
    Top = 48
  end
  object MainMenu1: TMainMenu
    Left = 72
    Top = 48
    object File1: TMenuItem
      Caption = #1060#1072#1081#1083#1099
      object Open1: TMenuItem
        Caption = #1054#1090#1082#1099#1090#1100' '#1092#1072#1081#1083'...'
        OnClick = SpeedButton1Click
      end
      object N4: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077'...'
        OnClick = N4Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = #1042#1099#1093#1086#1076' '#1080#1079' '#1087#1088#1086#1075#1088#1072#1084#1084#1099
        OnClick = Exit1Click
      end
    end
    object View1: TMenuItem
      Caption = #1044#1074#1091#1084#1077#1088#1085#1099#1081' '#1074#1080#1076
      object Source1: TMenuItem
        Action = SourceViewAction
      end
      object SourceCone: TMenuItem
        Action = SourceConeViewAction
      end
      object SourceConeInter: TMenuItem
        Action = InterConeAction
      end
      object SourceVertical1: TMenuItem
        Action = SourceVerticalAction
      end
      object SourceVerticalInter1: TMenuItem
        Action = InterVerticalAction
      end
      object N2: TMenuItem
        Action = InterHorizontalAction
      end
      object N3: TMenuItem
        Action = ResultCellsAction
      end
    end
    object N3DView1: TMenuItem
      Caption = #1058#1088#1077#1093#1084#1077#1088#1085#1099#1081' '#1074#1080#1076
      Visible = False
      object Source3DData1: TMenuItem
        Action = Source3dViewAction
      end
      object Contours3DData1: TMenuItem
        Action = HContours3dViewAction
      end
    end
    object Tools1: TMenuItem
      Caption = #1048#1085#1089#1090#1088#1091#1084#1077#1085#1090#1099
      object Options1: TMenuItem
        Action = OptionsAction
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072'...'
      end
    end
  end
  object ActionList1: TActionList
    Left = 104
    Top = 48
    object SourceViewAction: TAction
      Category = 'View2D'
      Caption = #1048#1089#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077
      OnExecute = SourceViewActionExecute
      OnUpdate = SourceViewActionUpdate
    end
    object SourceConeViewAction: TAction
      Category = 'View2D'
      Caption = #1048#1089#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077' '#1085#1072' '#1082#1086#1085#1091#1089#1077
      OnExecute = SourceConeViewActionExecute
      OnUpdate = SourceConeViewActionUpdate
    end
    object InterConeAction: TAction
      Category = 'View2D'
      Caption = #1048#1085#1090#1077#1088#1087#1086#1083#1103#1094#1080#1103' '#1085#1072' '#1082#1086#1085#1091#1089#1077
      OnExecute = InterConeActionExecute
      OnUpdate = InterConeActionUpdate
    end
    object SourceVerticalAction: TAction
      Category = 'View2D'
      Caption = #1042#1077#1088#1090#1080#1082#1072#1083#1100#1085#1099#1081' '#1089#1088#1077#1079
      OnExecute = SourceVerticalActionExecute
      OnUpdate = SourceVerticalActionUpdate
    end
    object InterVerticalAction: TAction
      Category = 'View2D'
      Caption = #1048#1085#1090#1077#1088#1087#1086#1083#1103#1094#1080#1103' '#1074#1077#1088#1090#1080#1082#1072#1083#1100#1085#1086#1075#1086' '#1089#1088#1077#1079#1072
      OnExecute = InterVerticalActionExecute
      OnUpdate = InterVerticalActionUpdate
    end
    object OptionsAction: TAction
      Category = 'Tools'
      Caption = 'Options...'
      OnExecute = OptionsActionExecute
    end
    object Source3dViewAction: TAction
      Category = 'View23D'
      Caption = #1048#1089#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077
      OnExecute = Source3dViewActionExecute
      OnUpdate = Source3dViewActionUpdate
    end
    object HContours3dViewAction: TAction
      Category = 'View23D'
      Caption = #1058#1088#1077#1093#1084#1077#1088#1085#1099#1077' '#1082#1086#1085#1090#1091#1088#1099
      OnExecute = HContours3dViewActionExecute
      OnUpdate = HContours3dViewActionUpdate
    end
    object InterHorizontalAction: TAction
      Category = 'View2D'
      Caption = #1048#1085#1090#1077#1088#1087#1086#1083#1103#1094#1080#1103' '#1075#1086#1088#1080#1079#1086#1085#1090#1072#1083#1100#1085#1086#1075#1086' '#1089#1088#1077#1079#1072
      OnExecute = InterHorizontalActionExecute
      OnUpdate = InterHorizontalActionUpdate
    end
    object ResultCellsAction: TAction
      Category = 'View2D'
      Caption = #1050#1086#1085#1074#1077#1082#1090#1080#1074#1085#1099#1077' '#1103#1095#1077#1081#1082#1080
      OnExecute = ResultCellsActionExecute
      OnUpdate = ResultCellsActionUpdate
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 136
    Top = 48
  end
end
