object Form3: TForm3
  Left = 0
  Top = 0
  Caption = #1046#1077#1083#1072#1077#1090#1077' '#1080#1084#1077#1085#1080#1090#1100' '#1072#1076#1088#1077#1089' '#1076#1072#1085#1085#1099#1093'?'
  ClientHeight = 216
  ClientWidth = 413
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object RadioButton1: TRadioButton
    Left = 24
    Top = 57
    Width = 353
    Height = 17
    Caption = 'RadioButton1'
    TabOrder = 0
    Visible = False
    OnClick = RadioButton1Click
  end
  object RadioButton2: TRadioButton
    Left = 24
    Top = 80
    Width = 353
    Height = 17
    Caption = 'RadioButton2'
    TabOrder = 1
    Visible = False
    OnClick = RadioButton2Click
  end
  object RadioButton3: TRadioButton
    Left = 24
    Top = 103
    Width = 353
    Height = 17
    Caption = 'RadioButton3'
    TabOrder = 2
    Visible = False
    OnClick = RadioButton3Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 247
    Height = 21
    TabOrder = 3
  end
  object GroupBox1: TGroupBox
    Left = 112
    Top = 134
    Width = 177
    Height = 38
    TabOrder = 4
    object Button2: TButton
      Left = 97
      Top = 6
      Width = 75
      Height = 25
      Caption = #1053#1077#1090
      TabOrder = 0
      OnClick = Button2Click
    end
    object Button1: TButton
      Left = 5
      Top = 6
      Width = 75
      Height = 25
      Caption = #1044#1072
      DoubleBuffered = False
      Enabled = False
      ParentDoubleBuffered = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 1
      OnClick = Button1Click
    end
  end
end
