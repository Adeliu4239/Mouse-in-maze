object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'HW3_Mouse in Maze by Adeliu'
  ClientHeight = 561
  ClientWidth = 701
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 160
    Height = 561
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 0
    object Label1: TLabel
      Left = 9
      Top = 9
      Width = 37
      Height = 25
      Caption = 'Size'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 9
      Top = 660
      Width = 40
      Height = 25
      Caption = 'Way'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object Label6: TLabel
      Left = 15
      Top = 353
      Width = 31
      Height = 13
      Caption = 'fast...'
    end
    object Label7: TLabel
      Left = 121
      Top = 353
      Width = 33
      Height = 13
      Caption = '...slow'
    end
    object Panel2: TPanel
      Left = 9
      Top = 32
      Width = 145
      Height = 121
      BevelInner = bvLowered
      BevelOuter = bvNone
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 0
      object Label3: TLabel
        Left = 8
        Top = 18
        Width = 42
        Height = 15
        Caption = 'Height :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 8
        Top = 52
        Width = 39
        Height = 15
        Caption = 'Width :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 8
        Top = 90
        Width = 27
        Height = 15
        Caption = 'Size :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
      end
      object Edit1: TEdit
        Left = 60
        Top = 16
        Width = 75
        Height = 21
        TabOrder = 0
      end
      object Edit2: TEdit
        Left = 60
        Top = 52
        Width = 75
        Height = 21
        TabOrder = 1
      end
      object Edit3: TEdit
        Left = 60
        Top = 90
        Width = 75
        Height = 21
        TabOrder = 2
      end
    end
    object Panel3: TPanel
      Left = 9
      Top = 660
      Width = 145
      Height = 89
      BevelInner = bvLowered
      BevelOuter = bvNone
      TabOrder = 1
      Visible = False
      object RadioButton1: TRadioButton
        Left = 8
        Top = 660
        Width = 64
        Height = 17
        Caption = '4-Way'
        Checked = True
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        TabStop = True
        Visible = False
      end
      object RadioButton2: TRadioButton
        Left = 8
        Top = 660
        Width = 64
        Height = 17
        Caption = '8-Way'
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        Visible = False
      end
    end
    object Button1: TButton
      Left = 9
      Top = 175
      Width = 145
      Height = 42
      Cursor = crHandPoint
      Caption = 'Generate Maze'
      Default = True
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 9
      Top = 223
      Width = 72
      Height = 42
      Cursor = crHandPoint
      Caption = 'Load Maze'
      TabOrder = 3
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 80
      Top = 223
      Width = 74
      Height = 42
      Cursor = crHandPoint
      Caption = 'Save Maze'
      Enabled = False
      TabOrder = 4
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 9
      Top = 423
      Width = 145
      Height = 42
      Cursor = crHandPoint
      Caption = 'Find a tour'
      Enabled = False
      TabOrder = 5
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 9
      Top = 487
      Width = 145
      Height = 42
      Cursor = crHandPoint
      Caption = 'Play game'
      Enabled = False
      TabOrder = 6
      OnClick = Button5Click
    end
    object CheckBox1: TCheckBox
      Left = 9
      Top = 327
      Width = 72
      Height = 17
      Caption = 'Refresh'
      TabOrder = 7
    end
    object TrackBar1: TTrackBar
      Left = 9
      Top = 372
      Width = 145
      Height = 45
      Cursor = crHandPoint
      Enabled = False
      TabOrder = 8
      TickMarks = tmBoth
    end
    object CheckBox2: TCheckBox
      Left = 69
      Top = 327
      Width = 85
      Height = 17
      Caption = 'Doubblebuffer'
      TabOrder = 9
      Visible = False
    end
    object CheckBox3: TCheckBox
      Left = 69
      Top = 327
      Width = 85
      Height = 17
      Caption = 'RandomColor'
      TabOrder = 10
    end
  end
  object PageControl1: TPageControl
    Left = 160
    Top = 0
    Width = 541
    Height = 561
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Memo'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 533
        Height = 533
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Grid-Num'
      ImageIndex = 1
      object StringGrid1: TStringGrid
        Left = 0
        Top = 0
        Width = 533
        Height = 533
        Align = alClient
        DefaultColWidth = 40
        DefaultRowHeight = 40
        FixedCols = 0
        FixedRows = 0
        GridLineWidth = 2
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Maze'
      ImageIndex = 2
      object StringGrid2: TStringGrid
        Left = 0
        Top = 0
        Width = 533
        Height = 533
        Align = alClient
        DefaultColWidth = 40
        DefaultRowHeight = 40
        FixedCols = 0
        FixedRows = 0
        TabOrder = 0
        OnDrawCell = StringGrid2DrawCell
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Play'
      ImageIndex = 3
      object StringGrid3: TStringGrid
        Left = 0
        Top = 0
        Width = 533
        Height = 533
        Align = alClient
        DefaultColWidth = 40
        DefaultRowHeight = 40
        DoubleBuffered = True
        FixedCols = 0
        FixedRows = 0
        ParentDoubleBuffered = False
        TabOrder = 0
        OnDrawCell = StringGrid3DrawCell
        OnKeyPress = StringGrid3KeyPress
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 8
    Top = 264
  end
  object SaveDialog1: TSaveDialog
    Left = 88
    Top = 264
  end
end
