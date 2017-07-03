//---------------------------------------------------------------------------

#ifndef cukculH
#define cukculH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TLabel *LOT1;
    TLabel *LON1;
    TLabel *LOT2;
    TLabel *LON2;
    TButton *CULCULATE;
    TEdit *Edit5;
    TEdit *Edit6;
    TLabel *DIST;
    TLabel *ANGEL;
    TEdit *Edit7;
    TEdit *Edit8;
    TLabel *Label2;
    TLabel *Label1;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *Edit9;
    TLabel *Label5;
    TButton *Button1;
    TLabel *Label7;
    TEdit *Edit11;
    TLabel *Label8;
    TEdit *Edit12;
    TLabel *Label9;
    TLabel *Label10;
    TEdit *Edit13;
    TEdit *Edit14;
    TEdit *Edit15;
    TLabel *Label12;
    TLabel *Label13;
    TEdit *Edit16;
    TLabel *Label14;
    TEdit *Edit17;
    TLabel *Label11;
    TLabel *Label6;
    TEdit *Edit10;
    TEdit *Edit18;
    TEdit *Edit19;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TEdit *Edit20;
    TLabel *Label18;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TEdit *Edit21;
    TEdit *Edit22;
    TLabel *Label19;
    TLabel *Label20;
    void __fastcall CULCULATEClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
