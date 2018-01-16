//---------------------------------------------------------------------------

#ifndef mainUnitH
#define mainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "FImage.h"
#include <ActnList.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "TrackBarEx.h"
//---------------------------------------------------------------------------

typedef struct
{
    int Square;
    double Perim;
    awpPoint pm;
    awpRect r;
}TObjectProps;
class TmainForm : public TForm
{
__published:	// IDE-managed Components
    TFImage *FImage1;
    TFImageToolkit *FImageToolkit1;
    TActionList *ActionList1;
    TAction *OpneImageAction;
    TPopupMenu *PopupMenu1;
    TMenuItem *N1;
    TMenuItem *N2;
    TAction *CloseAction;
    TMenuItem *N3;
    TOpenDialog *OpenDialog1;
    TAction *ModePaneAction;
    TAction *ModeSelRectAction;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *N6;
    TMenuItem *N7;
    TAction *ActualSizeAction;
    TAction *BestFitAction;
    TMenuItem *N8;
    TMenuItem *N9;
    TAction *AboutAction;
    TMenuItem *N10;
    TPanel *Panel1;
    TAction *Action1;
    TMenuItem *N11;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TColorDialog *ColorDialog1;
    TFImage *FImage2;
    TAction *Action2;
    TMenuItem *N12;
    TAction *Action3;
    TMenuItem *N13;
    TListBox *ListBox1;
    TButton *Button1;
    TSaveDialog *SaveDialog1;
    TTrackBarEx *TrackBarEx1;
    TLabel *Label1;
    void __fastcall CloseActionExecute(TObject *Sender);
    void __fastcall OpneImageActionExecute(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall ModePaneActionExecute(TObject *Sender);
    void __fastcall ModePaneActionUpdate(TObject *Sender);
    void __fastcall ModeSelRectActionExecute(TObject *Sender);
    void __fastcall ModeSelRectActionUpdate(TObject *Sender);
    void __fastcall ActualSizeActionUpdate(TObject *Sender);
    void __fastcall ActualSizeActionExecute(TObject *Sender);
    void __fastcall BestFitActionExecute(TObject *Sender);
    void __fastcall BestFitActionUpdate(TObject *Sender);
    void __fastcall AboutActionExecute(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Action1Execute(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall Action2Execute(TObject *Sender);
    void __fastcall Action3Execute(TObject *Sender);
    void __fastcall ListBox1Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall TrackBarEx1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
    awpImage* m_image;
    TColor    m_stColor;
    TColor    m_eColor;

    TList*    m_objects;

public:		// User declarations
    __fastcall TmainForm(TComponent* Owner);
    void __fastcall UpdateImage();
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
