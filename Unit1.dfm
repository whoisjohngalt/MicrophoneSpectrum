object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1040#1085#1072#1083#1080#1079#1072#1090#1086#1088' '#1089#1087#1077#1082#1090#1088#1072
  ClientHeight = 675
  ClientWidth = 1133
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 3
    Top = 0
    Width = 1024
    Height = 512
    Color = clBackground
    ParentColor = False
  end
  object Label1: TLabel
    Left = 376
    Top = 544
    Width = 154
    Height = 13
    Caption = #1063#1072#1089#1090#1086#1090#1072' '#1089#1080#1089#1090#1077#1084#1085#1086#1075#1086' '#1076#1080#1085#1072#1084#1080#1082#1072
  end
  object Label2: TLabel
    Left = 712
    Top = 518
    Width = 18
    Height = 13
    Caption = #1058#1086#1085
  end
  object Label3: TLabel
    Left = 888
    Top = 518
    Width = 65
    Height = 13
    Caption = #1054#1090#1082#1083#1086#1085#1077#1085#1080#1077' '
  end
  object Label4: TLabel
    Left = 712
    Top = 568
    Width = 131
    Height = 13
    Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1072#1084#1087#1083#1080#1090#1091#1076#1072
  end
  object Label5: TLabel
    Left = 888
    Top = 565
    Width = 94
    Height = 13
    Caption = #1055#1086#1079#1080#1094#1080#1103' '#1074' '#1084#1072#1089#1089#1080#1074#1077
  end
  object Label6: TLabel
    Left = 712
    Top = 611
    Width = 98
    Height = 13
    Caption = #1063#1072#1089#1090#1086#1090#1072' '#1084#1072#1082#1089#1080#1084#1091#1084#1072
  end
  object Button1: TButton
    Left = 35
    Top = 563
    Width = 75
    Height = 25
    Caption = #1057#1090#1072#1088#1090
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 152
    Top = 563
    Width = 75
    Height = 25
    Caption = #1057#1090#1086#1087
    TabOrder = 1
    OnClick = Button2Click
  end
  object EditAmp: TEdit
    Left = 712
    Top = 584
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'EditAmp'
  end
  object EditPos: TEdit
    Left = 888
    Top = 584
    Width = 121
    Height = 21
    TabOrder = 3
    Text = 'EditPos'
  end
  object EditFreq: TEdit
    Left = 712
    Top = 624
    Width = 121
    Height = 21
    TabOrder = 4
    Text = 'EditFreq'
  end
  object ListBox1: TListBox
    Left = 1033
    Top = 0
    Width = 24
    Height = 512
    ItemHeight = 13
    TabOrder = 5
    Visible = False
  end
  object Button3: TButton
    Left = 1033
    Top = 534
    Width = 75
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 6
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 256
    Top = 563
    Width = 114
    Height = 25
    Caption = #1057#1080#1089#1090#1077#1084#1085#1099#1081' '#1076#1080#1085#1072#1084#1080#1082
    TabOrder = 7
    OnClick = Button4Click
  end
  object Edit4: TEdit
    Left = 376
    Top = 565
    Width = 154
    Height = 21
    TabOrder = 8
    Text = '440'
  end
  object EditTone: TEdit
    Left = 712
    Top = 536
    Width = 121
    Height = 21
    TabOrder = 9
    Text = 'EditTone'
  end
  object EditDif: TEdit
    Left = 888
    Top = 537
    Width = 121
    Height = 21
    TabOrder = 10
    Text = 'EditDif'
  end
  object TrackBarAmpli: TTrackBar
    Left = 1063
    Top = 8
    Width = 45
    Height = 504
    Max = 70000
    Min = 12000
    Orientation = trVertical
    Position = 25000
    TabOrder = 11
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 600
    Top = 592
  end
end
