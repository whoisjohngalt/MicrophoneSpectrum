// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "perfgrap.h"
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
 #include "math.h"
#include <Vcl.ComCtrls.hpp>
// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components

	TTimer *Timer1;
	TButton *Button1;
	TButton *Button2;
	TPaintBox *PaintBox1;
	TEdit *EditAmp;
	TEdit *EditPos;
	TEdit *EditFreq;
	TListBox *ListBox1;
	TButton *Button3;
	TButton *Button4;
	TEdit *Edit4;
	TEdit *EditTone;
	TEdit *EditDif;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TTrackBar *TrackBarAmpli;

	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);

private: // User declarations
		public : // User declarations
	__fastcall TForm1(TComponent* Owner);
	BOOL TForm1::InitDevice(int device);
	void TForm1::StopRecording();
	void TForm1::StartRecording();

public:
	UnicodeString gettone(float tone);
	float octav_mass[120];
	UnicodeString tone_mass[120];
	int run;
	float dif_without_abs;
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
