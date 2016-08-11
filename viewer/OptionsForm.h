//----------------------------------------------------------------------------
#ifndef OptionsFormH
#define OptionsFormH
//----------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <Messages.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
//----------------------------------------------------------------------------
class TOptionsDlg : public TForm
{
__published:
	TButton *Button1;
	TButton *Button2;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
    TCSpinEdit *CSpinEdit1;
    TCSpinEdit *CSpinEdit4;
    TCSpinEdit *CSpinEdit5;
    TLabel *Label1;
    TLabel *Label4;
    TLabel *Label5;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TTabSheet *TabSheet3;
    TLabel *Label2;
    TCSpinEdit *CSpinEdit2;
    TLabel *Label6;
    TCSpinEdit *CSpinEdit6;
    TLabel *Label7;
    TCSpinEdit *CSpinEdit7;
private:
public:
	virtual __fastcall TOptionsDlg(TComponent *Owner);
};
//----------------------------------------------------------------------------
extern TOptionsDlg *OptionsDlg;
//----------------------------------------------------------------------------
#endif
