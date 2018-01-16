//---------------------------------------------------------------------------

#ifndef CircleAngelH
#define CircleAngelH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TOpenDialog *OpenDialog1;
    TButton *Button1;
    TMemo *Memo1;
    TEdit *Edit1;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Edit1Change(TObject *Sender);
    void __fastcall Memo1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
              double l_LOG;
              double l_LON;
              double FI[10000];
              double DIST[10000];
              int K[10000];
              int count;
               void Draww();
               double gama;
                double gama1;
               double xx,yy;
               
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
