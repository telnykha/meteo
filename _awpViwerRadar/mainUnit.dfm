object mainForm: TmainForm
  Left = 303
  Top = 144
  Width = 959
  Height = 500
  Caption = 'awpViewer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object FImage1: TFImage
    Left = 121
    Top = 0
    Width = 822
    Height = 409
    Cursor = 1
    BorderStyle = bsFSingle
    Align = alClient
    ParentColor = False
    PopupMenu = PopupMenu1
    OnMouseUp = TrackBarEx1MouseUp
  end
  object Panel1: TPanel
    Left = 0
    Top = 409
    Width = 943
    Height = 53
    Align = alBottom
    TabOrder = 1
    object SpeedButton1: TSpeedButton
      Left = 328
      Top = 16
      Width = 23
      Height = 22
      Visible = False
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 560
      Top = 16
      Width = 23
      Height = 22
      Visible = False
      OnClick = SpeedButton2Click
    end
    object Label1: TLabel
      Left = 264
      Top = 16
      Width = 32
      Height = 13
      Caption = 'Label1'
    end
    object FImage2: TFImage
      Left = 360
      Top = 16
      Width = 256
      Height = 25
      Cursor = 1
      BorderStyle = bsFSingle
      ParentColor = False
      Visible = False
    end
    object Button1: TButton
      Left = 8
      Top = 16
      Width = 75
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100'...'
      TabOrder = 1
      OnClick = Button1Click
    end
    object TrackBarEx1: TTrackBarEx
      Left = 104
      Top = 8
      Width = 150
      Height = 45
      Max = 255
      Orientation = trHorizontal
      Frequency = 20
      Position = 128
      SelEnd = 0
      SelStart = 0
      TabOrder = 2
      ThumbLength = 8
      TickMarks = tmBoth
      TickStyle = tsAuto
      OnMouseUp = TrackBarEx1MouseUp
    end
  end
  object ListBox1: TListBox
    Left = 0
    Top = 0
    Width = 121
    Height = 409
    Align = alLeft
    ItemHeight = 13
    TabOrder = 2
    OnClick = ListBox1Click
  end
  object FImageToolkit1: TFImageToolkit
    CurrentTool = ftPane
    Image = FImage1
    Left = 16
    Top = 24
  end
  object ActionList1: TActionList
    Left = 56
    Top = 24
    object OpneImageAction: TAction
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077'...'
      OnExecute = OpneImageActionExecute
    end
    object CloseAction: TAction
      Caption = #1042#1099#1093#1086#1076
      OnExecute = CloseActionExecute
    end
    object ModePaneAction: TAction
      Caption = #1056#1077#1078#1080#1084' '#1087#1088#1086#1089#1084#1086#1090#1088#1072
      OnExecute = ModePaneActionExecute
      OnUpdate = ModePaneActionUpdate
    end
    object ModeSelRectAction: TAction
      Caption = #1042#1099#1073#1088#1072#1090#1100' '#1087#1088#1103#1084#1086#1091#1075#1086#1083#1100#1085#1080#1082
      OnExecute = ModeSelRectActionExecute
      OnUpdate = ModeSelRectActionUpdate
    end
    object ActualSizeAction: TAction
      Caption = #1048#1089#1093#1086#1076#1085#1099#1081' '#1088#1072#1079#1084#1077#1088
      OnExecute = ActualSizeActionExecute
      OnUpdate = ActualSizeActionUpdate
    end
    object BestFitAction: TAction
      Caption = #1042#1087#1080#1089#1072#1090#1100' '#1074' '#1086#1082#1085#1086
      OnExecute = BestFitActionExecute
      OnUpdate = BestFitActionUpdate
    end
    object AboutAction: TAction
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
      OnExecute = AboutActionExecute
    end
    object Action1: TAction
      Caption = #1048#1085#1074#1077#1088#1090#1080#1088#1086#1074#1072#1090#1100
      OnExecute = Action1Execute
    end
    object Action2: TAction
      Caption = #1042#1077#1088#1085#1091#1090#1100#1089#1103' '#1082' '#1080#1089#1093#1086#1076#1085#1086#1084#1091
      OnExecute = Action2Execute
    end
    object Action3: TAction
      Caption = #1055#1086#1080#1089#1082' '#1086#1073#1098#1077#1082#1090#1086#1074
      OnExecute = Action3Execute
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 96
    Top = 24
    object N1: TMenuItem
      Action = OpneImageAction
    end
    object N12: TMenuItem
      Action = Action2
    end
    object N11: TMenuItem
      Action = Action1
    end
    object N13: TMenuItem
      Action = Action3
    end
    object N4: TMenuItem
      Caption = '-'
    end
    object N5: TMenuItem
      Action = ModePaneAction
    end
    object N6: TMenuItem
      Action = ModeSelRectAction
    end
    object N7: TMenuItem
      Caption = '-'
    end
    object N8: TMenuItem
      Action = ActualSizeAction
    end
    object N9: TMenuItem
      Action = BestFitAction
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object N10: TMenuItem
      Action = AboutAction
    end
    object N3: TMenuItem
      Action = CloseAction
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'Jpeg images|*.jpeg;*.jpg|AWP images|*.awp|PNG images|*.png|TIFF ' +
      'images|*.tif;*.tiff|BMP images|*.bmp'
    Left = 144
    Top = 24
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 184
    Top = 24
  end
  object SaveDialog1: TSaveDialog
    Filter = 'Text files|*.txt'
    Left = 224
    Top = 24
  end
end
