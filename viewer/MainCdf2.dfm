object Form2: TForm2
  Left = 78
  Top = 241
  Width = 801
  Height = 595
  Caption = 'Form2'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 41
    Width = 3
    Height = 388
    Cursor = crHSplit
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 785
    Height = 41
    Align = alTop
    TabOrder = 0
    OnResize = Panel1Resize
    object SpeedButton1: TSpeedButton
      Left = 4
      Top = 8
      Width = 23
      Height = 22
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
      Left = 26
      Top = 8
      Width = 23
      Height = 22
      AllowAllUp = True
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
      Left = 48
      Top = 8
      Width = 23
      Height = 22
      Caption = '<<'
      OnClick = SpeedButton2Click
    end
    object SpeedButton4: TSpeedButton
      Left = 72
      Top = 8
      Width = 23
      Height = 22
      Caption = '>>'
      OnClick = SpeedButton4Click
    end
    object SpeedButton5: TSpeedButton
      Left = 96
      Top = 8
      Width = 49
      Height = 22
      Caption = 'Play'
      OnClick = SpeedButton5Click
    end
  end
  object FImage1: TFImage
    Left = 3
    Top = 41
    Width = 782
    Height = 388
    Cursor = 1
    BorderStyle = bsFSingle
    Align = alClient
    ParentColor = False
    OnMouseMove = FImage1MouseMove
  end
  object Panel2: TPanel
    Left = 0
    Top = 429
    Width = 785
    Height = 88
    Align = alBottom
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 2
    object Label3: TLabel
      Left = 456
      Top = 44
      Width = 42
      Height = 13
      Caption = 'Azmuth'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
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
      Caption = 'Elevation'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
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
      BackWall.Brush.Color = clWhite
      BackWall.Brush.Style = bsClear
      Title.Text.Strings = (
        'Azmuth')
      Legend.Visible = False
      View3D = False
      Align = alLeft
      TabOrder = 0
      object Series1: TFastLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clRed
        LinePen.Color = clRed
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
    end
    object Chart2: TChart
      Left = 225
      Top = 1
      Width = 224
      Height = 86
      BackWall.Brush.Color = clWhite
      BackWall.Brush.Style = bsClear
      Title.Text.Strings = (
        'Elevation')
      Legend.Visible = False
      View3D = False
      Align = alLeft
      TabOrder = 1
      object FastLineSeries1: TFastLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clRed
        LinePen.Color = clRed
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
    end
    object ComboBox1: TComboBox
      Left = 512
      Top = 8
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      OnChange = ComboBox1Change
    end
    object ComboBox2: TComboBox
      Left = 512
      Top = 40
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      OnChange = ComboBox2Change
    end
    object Panel4: TPanel
      Left = 599
      Top = 1
      Width = 185
      Height = 86
      Align = alRight
      TabOrder = 4
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 517
    Width = 785
    Height = 19
    Panels = <
      item
        Text = 'x = y = r = psi = '
        Width = 50
      end>
    SimplePanel = False
  end
  object Panel3: TPanel
    Left = 3
    Top = 41
    Width = 782
    Height = 388
    Align = alClient
    TabOrder = 4
    Visible = False
    OnResize = Panel3Resize
    object PaintBox1: TPaintBox
      Left = 1
      Top = 1
      Width = 780
      Height = 386
      Align = alClient
      OnMouseDown = PaintBox1MouseDown
      OnMouseMove = PaintBox1MouseMove
      OnMouseUp = PaintBox1MouseUp
      OnPaint = PaintBox1Paint
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'netcdf files|*.nc'
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 8
    Top = 48
  end
  object SaveDialog1: TSaveDialog
    Filter = 'png images|*.png'
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
    end
    object N3DView1: TMenuItem
      Caption = #1058#1088#1077#1093#1084#1077#1088#1085#1099#1081' '#1074#1080#1076
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
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer1Timer
    Left = 136
    Top = 48
  end
end
