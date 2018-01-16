//---------------------------------------------------------------------------

#ifndef drawH
#define drawH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include "LFlash.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPaintBox *PaintBox1;
        TEdit *Edit1;
        TEdit *Edit2;
        TButton *Button1;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *Edit3;
    TEdit *Edit4;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TEdit *Edit5;
    TEdit *Edit6;
    TLabel *Label9;
    TLabel *Label10;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TTimer *Timer1;
    TLabel *Label11;
    TButton *Button2;
    TScrollBar *ScrollBar1;
    TEdit *Edit7;
    TLabel *Label13;
    TEdit *Edit8;
    TLabel *Label12;
    TButton *Button3;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall ScrollBar1Change(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations
TDateTime mTime;
  unsigned short h;
  unsigned short m;
  unsigned short s;
  unsigned short ms;
double N_Lat;
double N_Lon;
TList* m_list;
TList* l_elements;
int min_count;
TGeoCoordConverter* d;
    void __fastcall DrawFlash(TFlash* f);
    void __fastcall CreateMap();
    void __fastcall ShiftMap(awp2DPoint base);
    void __fastcall DdflashMap();
    void __fastcall addflash(TList*El,TList*Out);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 