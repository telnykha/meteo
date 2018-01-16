//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VarUnit.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage"
#pragma resource "*.dfm"
TVarForm *VarForm;
//---------------------------------------------------------------------------
__fastcall TVarForm::TVarForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVarForm::ComboBox2Change(TObject *Sender)
{
  //
  Chart1->Series[0]->Clear();
    
}
//---------------------------------------------------------------------------
