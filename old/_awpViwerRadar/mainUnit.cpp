//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainUnit.h"
#include "aboutUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage"


#pragma link "TrackBarEx"
#pragma resource "*.dfm"
TmainForm *mainForm;


//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
    : TForm(Owner)
{
    m_stColor = clBlack;
    m_eColor  = clWhite;
    this->m_objects = new TList;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::CloseActionExecute(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::OpneImageActionExecute(TObject *Sender)
{
    if (OpenDialog1->Execute())
    {
        FImage1->Init(OpenDialog1->FileName, NULL);

        //if (this->m_image != NULL)

         awpImage* img = NULL;
         //FImage1->Bitmap->GetAWPImage(&img);
           // awpReleaseImage(&this->m_image);
        FImage1->Bitmap->GetAWPImage(&m_image);
        int b=1024;
         awpResize(m_image,b,b);

         FImage1->Bitmap->SetAWPImage(m_image);
         //awpCopyImage(this->m_image, &img);
        // int n=10;
         //awpResize(m_image,m_image->sSizeX/n,m_image->sSizeY/n);
        UpdateImage();
    }
}
void __fastcall TmainForm::UpdateImage()
{
        // установка размеров изображения.
        // если размер изображения больше размеров окна -
        // выполняем операцию BestFit
        // иначе выполняем операцию ActualSize

        int w = FImage1->Width;
        int h = FImage1->Height;
        int w1 = FImage1->Bitmap->Width;
        int h1 = FImage1->Bitmap->Height;
/*
         awpColor c1, c2;
        awpImage* img = NULL;
        //FImage1->Bitmap->GetAWPImage(&img);
        awpCopyImage(m_image, &img);

        if (img)
        {

            //awpAutoLevels(img);

            c1.bRed = 0;
            c1.bGreen = 0;
            c1.bBlue = 255;

            c2.bRed = 255;
            c2.bGreen = 0;
            c2.bBlue = 0;

            awpColor* b = (awpColor*)img->pPixels;
            awpHistogramm h;
            awpGetHistogramm(img, &h);

            int maxv = 0;
            int maxi = 0;
            for (int i = 0; i < 255; i++)
            {
               if (h.Intensity[i] > maxv)
               {
                    maxv = h.Intensity[i];
                    maxi = i;
               }
            }
            for (int y = 0; y < img->sSizeY; y++)
            {
                for (int x = 0; x < img->sSizeX; x++)
                {

                   if (b[y*img->sSizeX + x].bBlue == maxi)
                    {
                      b[y*img->sSizeX + x].bBlue = 0;//c1.bRed + b[y*img->sSizeX + x].bBlue*(c2.bRed - c1.bRed) / 256.;
                      b[y*img->sSizeX + x].bGreen = 0;//c1.bGreen + b[y*img->sSizeX + x].bGreen*(c2.bGreen - c1.bGreen) / 256.;;
                      b[y*img->sSizeX + x].bRed = 0;//c1.bBlue +  b[y*img->sSizeX + x].bRed*(c2.bBlue - c1.bBlue) / 256.;
                    }
                    else
                    {
                      b[y*img->sSizeX + x].bBlue = c1.bRed + b[y*img->sSizeX + x].bBlue*(c2.bRed - c1.bRed) / 256.;
                      b[y*img->sSizeX + x].bGreen = c1.bGreen + b[y*img->sSizeX + x].bGreen*(c2.bGreen - c1.bGreen) / 256.;;
                      b[y*img->sSizeX + x].bRed = c1.bBlue +  b[y*img->sSizeX + x].bRed*(c2.bBlue - c1.bBlue) / 256.;
                    }
                }
            }


            FImage1->Bitmap->SetAWPImage(img);
            awpReleaseImage(&img);
        }  */

        if (w1 > w || h1 > h)
            FImage1->BestFit();
        else
            FImage1->ActualSize();

}
//---------------------------------------------------------------------------
void __fastcall TmainForm::FormResize(TObject *Sender)
{
    UpdateImage();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModePaneActionExecute(TObject *Sender)
{
    FImageToolkit1->CurrentTool = ftPane;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModePaneActionUpdate(TObject *Sender)
{
    ModePaneAction->Checked =  FImageToolkit1->CurrentTool == ftPane;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModeSelRectActionExecute(TObject *Sender)
{
    FImageToolkit1->CurrentTool = ftSelRect;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModeSelRectActionUpdate(TObject *Sender)
{
    ModeSelRectAction->Checked =  FImageToolkit1->CurrentTool == ftSelRect;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ActualSizeActionUpdate(TObject *Sender)
{
    ActualSizeAction->Enabled = !FImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::ActualSizeActionExecute(TObject *Sender)
{
    FImage1->ActualSize();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::BestFitActionExecute(TObject *Sender)
{
    FImage1->BestFit();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::BestFitActionUpdate(TObject *Sender)
{
     BestFitAction->Enabled = !FImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::AboutActionExecute(TObject *Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FormCreate(TObject *Sender)
{
    if(ParamCount() > 0)
    {
        FImage1->Init(ParamStr(1), NULL);
        FImage1->BestFit();
    }

    awpImage* img = NULL;
    awpCreateImage(&img, 256, 25, 3, AWP_BYTE);
    AWPBYTE* b = (AWPBYTE*)img->pPixels;
    awpColor c1,c2, c;
    c1.bRed = 0;
    c1.bGreen = 0;
    c1.bBlue = 255;

    c2.bRed = 255;
    c2.bGreen = 0;
    c2.bBlue = 0;

    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            c.bRed = c1.bRed + x*(c2.bRed - c1.bRed) / 256.;
            c.bGreen = c1.bGreen + x*(c2.bGreen - c1.bGreen) / 256.;
            c.bBlue = c1.bBlue + x*(c2.bBlue - c1.bBlue) / 256.;

            b[y*img->sSizeX*img->bChannels + 3*x]   = c.bBlue;
            b[y*img->sSizeX*img->bChannels + 3*x+1] = c.bGreen;
            b[y*img->sSizeX*img->bChannels + 3*x+2] = c.bRed;
        }
    }

    FImage2->Bitmap->SetAWPImage(img);
    awpReleaseImage(&img);

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TmainForm::Action1Execute(TObject *Sender)
{
    awpImage* img = NULL;
    FImage1->Bitmap->GetAWPImage(&img);

    if (img != NULL)
    {
        AWPBYTE* b = (AWPBYTE*)img->pPixels;
        for (int i = 0; i < img->sSizeX*img->sSizeY*img->bChannels; i++)
            b[i] = 255- b[i];
        FImage1->Bitmap->SetAWPImage(img);
        FImage1->Paint();
        awpReleaseImage(&img);
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::SpeedButton1Click(TObject *Sender)
{
    if (ColorDialog1->Execute())
    {
        m_stColor = ColorDialog1->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::SpeedButton2Click(TObject *Sender)
{
    if (ColorDialog1->Execute())
    {
        m_eColor = ColorDialog1->Color;
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::Action2Execute(TObject *Sender)
{
    this->UpdateImage();   
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::Action3Execute(TObject *Sender)
{
    awpImage* img = NULL;
    awpImage* bin = NULL;
    awpImage* out = NULL;

    FImage1->Bitmap->GetAWPImage(&img);
    awpConvert(img, AWP_CONVERT_3TO1_BYTE);

    awpCreateImage(&out, img->sSizeX, img->sSizeY, 3, AWP_BYTE);

    //invert
 //   AWPBYTE* pix = (AWPBYTE*)img->pPixels;
 //   for (int i = 0; i < img->sSizeX*img->sSizeY; i++)
 //       pix[i] = 255 - pix[i];


   // awpMakeBinary(img, &bin, TrackBarEx1->Position, AWP_BINARY, 0, 255, NULL);

    awpStrokeObj* s = NULL;
    int NumObj = 0;
    awpGetStrokes(img, &NumObj, &s, 15, NULL);
    this->m_objects->Clear();
    ListBox1->Clear();
    int cc = 0;
    for (int i = 0; i < NumObj; i++)
    {
        //
        int square;
        awpStrObjSquare(&s[i], &square);
        if (square > 10)
        {
              awpContour* c;
              awpCreateContour(&c, 100, true);

              awpGetObjCountour(&s[i], c);
             // awpDrawCPolygon(out, c, 0,255, 0, 1);
              awpRect r;
              awpCalcObjRect(&s[i], &r);

              TObjectProps* p = new TObjectProps;

              p->Square = square;
              p->r = r;
              awpGetContPerim(c, &p->Perim);
              awpGetObjCentroid(img, &s[i], &p->pm);

               this->m_objects->Add(p);
               this->ListBox1->Items->Add("Object " + IntToStr(cc));
               cc++;

              awpFreeContour(&c);

//            awpDrawRect(bin, &r, 0, 128, 1);
        }
    }


    FImage1->Bitmap->SetAWPImage(out);
    FImage1->BestFit();

    awpReleaseImage(&bin);
    awpReleaseImage(&img);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::ListBox1Click(TObject *Sender)
{
    	int index = ListBox1->ItemIndex;
        TObjectProps* p = (TObjectProps*)m_objects->Items[index];

        awpImage* img = NULL;

       // FImage1->Bitmap->GetAWPImage(&img);
       awpCopyImage(this->m_image, &img);
        if (img)
        {

            awpDrawCRect(img, &p->r, 255,0,0,1);
            awpRect r;
            r.left = p->pm.X - 2;
            r.right = p->pm.X + 2;
            r.top = p->pm.Y - 2;
            r.bottom = p->pm.Y + 2;
            awpDrawCCross(img, &r, 0, 255, 0, 1);
            FImage1->Bitmap->SetAWPImage(img);
            FImage1->Paint();
            awpReleaseImage(&img);
        }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::Button1Click(TObject *Sender)
{
    if (SaveDialog1->Execute())
    {
        FILE* f = fopen(SaveDialog1->FileName.c_str(), "w+t");
        if (f)
        {
           fprintf(f, "%d\n", TrackBarEx1->Position);
           for (int i = 0; i < this->m_objects->Count; i++)
           {
                TObjectProps* p = (TObjectProps*)m_objects->Items[i];

                fprintf(f, "%i\t%i\t%i\t%e\n", p->pm.X, p->pm.Y, p->Square, p->Perim);
           }

           fclose(f);
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::TrackBarEx1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

    Label1->Caption = IntToStr(TrackBarEx1->Position);

    awpImage* img = NULL;
    FImage1->Bitmap->GetAWPImage(&img);
   // awpCopyImage(m_image, &img);
    if (img != NULL)
    {
        AWPBYTE* b = (AWPBYTE*)img->pPixels;
        for (int i = 0; i < img->sSizeX*img->sSizeY; i++)
        {

            b[3*i] = 0;
            b[3*i+1] = 0;
            b[3*i+2] = b[3*i + 2] > TrackBarEx1->Position ? 255:0;

//            if (b[i] > TrackBarEx1->Position)
//                b[i] = 255;
//            else
//                b[i] = 0;
        }
        awpGaussianBlur(img, img, 1);
        FImage1->Bitmap->SetAWPImage(img);
        FImage1->Paint();

        awpReleaseImage(&img);
    }
}
//---------------------------------------------------------------------------




