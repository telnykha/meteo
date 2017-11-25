//----------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OptionsForm.h"
//----------------------------------------------------------------------------
#pragma link "CSPIN"
#pragma resource "*.dfm"
TOptionsDlg *OptionsDlg;
//----------------------------------------------------------------------------
__fastcall TOptionsDlg::TOptionsDlg(TComponent *Owner)
	: TForm(Owner)
{
}
//----------------------------------------------------------------------------


void __fastcall TOptionsDlg::RadioGroup1Click(TObject *Sender)
{
if (RadioGroup1->ItemIndex==1)
    {  CheckBox4->Enabled=true;
       CheckBox5->Enabled=true;
       CheckBox6->Enabled=true;
    }
    else
    {
      CheckBox4->Enabled=false;
      CheckBox5->Enabled=false;
      CheckBox6->Enabled=false;
    }

}
//---------------------------------------------------------------------------

