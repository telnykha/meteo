object VarForm: TVarForm
  Left = 703
  Top = 124
  Width = 383
  Height = 521
  Caption = 'VarForm'
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
    Width = 11
    Height = 13
    Caption = 'ID'
  end
  object Label2: TLabel
    Left = 8
    Top = 24
    Width = 22
    Height = 13
    Caption = #1048#1084#1103
  end
  object Label3: TLabel
    Left = 8
    Top = 40
    Width = 19
    Height = 13
    Caption = #1058#1080#1087
  end
  object Label4: TLabel
    Left = 8
    Top = 56
    Width = 93
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1048#1079#1084#1077#1088#1077#1085#1080#1081
  end
  object Label5: TLabel
    Left = 8
    Top = 72
    Width = 88
    Height = 13
    Caption = #1063#1084#1089#1083#1086' '#1072#1090#1088#1080#1073#1091#1090#1086#1074
  end
  object Label8: TLabel
    Left = 128
    Top = 72
    Width = 225
    Height = 13
    Caption = 'Label5'
  end
  object Label9: TLabel
    Left = 128
    Top = 56
    Width = 225
    Height = 13
    Caption = 'Label4'
  end
  object Label10: TLabel
    Left = 128
    Top = 40
    Width = 233
    Height = 13
    Caption = 'Label3'
  end
  object Label11: TLabel
    Left = 128
    Top = 24
    Width = 225
    Height = 13
    Caption = 'Label2'
  end
  object Label12: TLabel
    Left = 128
    Top = 8
    Width = 225
    Height = 13
    Caption = 'Label1'
  end
  object Label6: TLabel
    Left = 10
    Top = 102
    Width = 58
    Height = 13
    Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1103
  end
  object Label13: TLabel
    Left = 142
    Top = 99
    Width = 19
    Height = 13
    Caption = 'Y = '
  end
  object ListBox1: TListBox
    Left = 8
    Top = 120
    Width = 121
    Height = 169
    ItemHeight = 13
    TabOrder = 0
  end
  object Chart1: TChart
    Left = 136
    Top = 120
    Width = 225
    Height = 169
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'TChart')
    Legend.Visible = False
    View3D = False
    TabOrder = 1
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
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
  object ComboBox2: TComboBox
    Left = 168
    Top = 96
    Width = 193
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 2
    OnChange = ComboBox2Change
  end
  object FImage1: TFImage
    Left = 24
    Top = 304
    Width = 313
    Height = 169
    Cursor = 1
    BorderStyle = bsFSingle
    ParentColor = False
  end
end
