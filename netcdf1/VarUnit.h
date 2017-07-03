//---------------------------------------------------------------------------

#ifndef VarUnitH
#define VarUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include "FImage.h"
//---------------------------------------------------------------------------
class TVarForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TListBox *ListBox1;
    TLabel *Label6;
    TChart *Chart1;
    TLineSeries *Series1;
    TLabel *Label13;
    TComboBox *ComboBox2;
    TFImage *FImage1;
    void __fastcall ComboBox2Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TVarForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVarForm *VarForm;
//---------------------------------------------------------------------------
#endif
