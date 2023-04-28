//---------------------------------------------------------------------------

#ifndef HW3H
#define HW3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPanel *Panel2;
	TLabel *Label1;
	TPanel *Panel3;
	TLabel *Label2;
	TEdit *Edit1;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit2;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TButton *Button4;
	TButton *Button5;
	TMemo *Memo1;
	TOpenDialog *OpenDialog1;
	TStringGrid *StringGrid1;
	TSaveDialog *SaveDialog1;
	TLabel *Label5;
	TEdit *Edit3;
	TTabSheet *TabSheet3;
	TStringGrid *StringGrid2;
	TCheckBox *CheckBox1;
	TTrackBar *TrackBar1;
	TLabel *Label6;
	TLabel *Label7;
	TCheckBox *CheckBox2;
	TTabSheet *TabSheet4;
	TStringGrid *StringGrid3;
	TCheckBox *CheckBox3;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall StringGrid3DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall StringGrid3KeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
