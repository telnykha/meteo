//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include"CallDist.h"
#include <system.hpp>
#include "awpipl.h"
#include "math.h"
#include "draw.h"
#include "LFlash.h"
#include "map.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

  mTime=Now();

  m_list=new TList();

  mTime.DecodeTime(&h,&m,&s,&ms);
  min_count = m +h*60;
  d = NULL;
  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{


 awp2DPoint base;
 awp2DPoint P, p1;
 awpPoint p0;
 PaintBox1->Refresh();
 base.Y=StrToFloat(Edit1->Text);
 base.X=StrToFloat(Edit2->Text);

 ShiftMap(base); 

 if (d != NULL)
    delete d;
 d = new TGeoCoordConverter(base);
 double v = StrToFloat(Edit3->Text);
 d->Setarea_lat(v);
 v = StrToFloat(Edit4->Text);
 d->Setarea_lon(v);
 N_Lat=StrToFloat(Edit5->Text);
 N_Lon=StrToFloat(Edit6->Text);
 Label5->Caption= FormatFloat("000.000", base.Y) +":" + FormatFloat("000.000", base.X);
 Label6->Caption= FormatFloat("000.000", base.Y+d->Getarea_lat()) +":" + FormatFloat("000.000", base.X);
 Label7->Caption= FormatFloat("000.000", base.Y + d->Getarea_lat()) +":" + FormatFloat("000.000", base.X+d->Getarea_lon());
 Label8->Caption= FormatFloat("000.000", base.Y ) +":" + FormatFloat("000.000", base.X+ d->Getarea_lon());


 PaintBox1->Canvas->Rectangle(0,0,PaintBox1->Width, PaintBox1->Height);
 //
 TDateTime t;
 t=StrToTime(Edit8->Text);
 int dt=StrToFloat(Edit7->Text);
  TList* out = new TList();
  FindFlashes(m_list, out, t, dt);
  this->addflash(l_elements, out);
  delete out;

for (int i = 0; i < l_elements->Count; i++)
{
  TMapElement* f = (TMapElement*)l_elements->Items[i];
  P.X = f->S_lon;
  P.Y = f->S_lat;
  p0=d->ConvertKmToPix(P);
  P.X = f->S_lon + f->Size_lon;
  P.Y = f->S_lat + f->Size_lat;
  awpPoint p1=d->ConvertKmToPix(P);
  //PaintBox1->Canvas->Ellipse(p0.X,p0.Y,p0.X+5,p0.Y+5);
  if(f->N > 0)
    PaintBox1->Canvas->Brush->Color = RGB(0,255*f->N/300,0);
  else
    PaintBox1->Canvas->Brush->Color = RGB(255,255,255);

  PaintBox1->Canvas->Rectangle(p0.X, p0.Y, p1.X, p1.Y);
}

  

}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
    awp2DPoint base;

    bool T=Timer1->Enabled;
    Timer1->Enabled=false;
    if (!OpenDialog1->Execute())
         return;
    LFlash(OpenDialog1->FileName.c_str(),m_list);

   // addflash(l_elements,m_list);
    Label11->Caption = "Число вспышек = " + IntToStr(m_list->Count);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawFlash(TFlash* f0)
{
 awpPoint p0;
 awp2DPoint p;
 p.Y = f0->lat;
 p.X  = f0->lon;
 p0=d->ConvertKmToPix(p);
 PaintBox1->Canvas->Ellipse(p0.X,p0.Y,p0.X+15,p0.Y+15);
}
 void __fastcall TForm1::Button2Click(TObject *Sender)
{

      Timer1->Enabled=!Timer1->Enabled;
        if ( Timer1->Enabled)
       Button2->Caption="off";
          else
         Button2->Caption="play";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
 Timer1->Interval=ScrollBar1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
//   Button1Click(NULL);
 awp2DPoint P, p1;
   TTime t = StrToTime(Edit8->Text);
   min_count+=5;
  if (min_count>=24*60)
  min_count=0;
  mTime.DecodeTime(&h,&m,&s,&ms);
  h = (min_count)/60;
  m=min_count%60;
  t=TDateTime(h,m,s,ms);
  TList* out = new TList();
  int dt=StrToFloat(Edit7->Text);
  FindFlashes(m_list, out, t, dt);
  this->addflash(l_elements, out);
for (int i = 0; i < l_elements->Count; i++)
{
  TMapElement* f = (TMapElement*)l_elements->Items[i];
  P.X = f->S_lon;
  P.Y = f->S_lat;
  awpPoint p0=d->ConvertKmToPix(P);
  P.X = f->S_lon + f->Size_lon;
  P.Y = f->S_lat + f->Size_lat;
  awpPoint p1=d->ConvertKmToPix(P);
  //PaintBox1->Canvas->Ellipse(p0.X,p0.Y,p0.X+5,p0.Y+5);
  if(f->N > 0)
    PaintBox1->Canvas->Brush->Color = RGB(0,255,0);
  else
    PaintBox1->Canvas->Brush->Color = RGB(255,255,255);

  PaintBox1->Canvas->Rectangle(p0.X, p0.Y, p1.X, p1.Y);
}


  for (int i = 0; i < out->Count; i++)
  {
      TFlash* f = (TFlash*)out->Items[i];
      if (f != NULL)
      {
        AnsiString s = TimeToStr(f->time);
        DrawFlash(f);
      }
  }


  delete out;


}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{
//
 l_elements=new TList();
  CreateMap();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateMap()
{
 l_elements->Clear();

 awp2DPoint base;
 base.Y=StrToFloat(Edit1->Text);
 base.X=StrToFloat(Edit2->Text);

 double v_lat = StrToFloat(Edit3->Text);
 double v_lon = StrToFloat(Edit4->Text);
 double N_Lat=StrToFloat(Edit5->Text);
 double N_Lon=StrToFloat(Edit6->Text);
 double K=v_lat/N_Lat;
 double L=v_lon/N_Lon;

 double l1,l2;
 for (l1=0;l1<K;l1++)
 {
 for (l2=0;l2<L;l2++)
 {

         TMapElement*f = new TMapElement();
        // shirota;
        double Y=base.Y+l2*N_Lat;
        // dolgota;
        double X=base.X+l1*N_Lat;

        f->S_lat = Y;
        f->S_lon = X;
        f->Size_lat =  N_Lat;
        f->Size_lon = N_Lon;
        f->N = 0;
        memset(f->Vector, 0, sizeof(f->Vector));

        l_elements->Add(f);
    }
 }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::DdflashMap()
{
 ///

  /*TList* out = new TList();
  FindFlashes(m_list, out, t, dt);
  for (int i = 0; i < out->Count; i++)
  {
      TFlash* f = (TFlash*)out->Items[i];
      if (f != NULL)
      {
        AnsiString s = TimeToStr(f->time);
        DrawFlash(f);
      }
  }

  delete out;*/
}

void __fastcall TForm1::addflash(TList* l_e, TList*Out)
{
double i,j;
    for (i=0;i<l_e->Count;i++)
    {
      TMapElement* f = (TMapElement*)l_e->Items[i];
      f->N = 0;
      for (j=0;j<Out->Count;j++)
      {
           TFlash* o = (TFlash*)Out->Items[j];
           double x,dx,x0;
           x0 = f->S_lon;
           x  = o->lon;
           dx = f->S_lon + f->Size_lon;
           if ((f->S_lat <= o->lat && o->lat <= f->S_lat+f->Size_lat) &&
           (x >= x0) && (x <= dx) )
                  f->N = o->num;
           }

      }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{

 awp2DPoint base;
 awp2DPoint P, p1;
 awpPoint p0;
 base.Y=StrToFloat(Edit1->Text);
 base.X=StrToFloat(Edit2->Text);

    TDateTime t;
    t=StrToTime(Edit8->Text);
    int dt=StrToFloat(Edit7->Text);
    TList* out = new TList();
  FindFlashes(m_list, out, t, dt);
  for (int i = 0; i < out->Count; i++)
  {
      TFlash* f = (TFlash*)out->Items[i];
      if (f != NULL)
      {
        AnsiString s = TimeToStr(f->time);
        DrawFlash(f);
  //      PaintBox1->Canvas->Ellipse(p0.X,p0.Y,p0.X+15,p0.Y+15);
      }
  }

  delete out;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShiftMap(awp2DPoint base)
{
 double v_lat = StrToFloat(Edit3->Text);
 double v_lon = StrToFloat(Edit4->Text);
 double N_Lat=StrToFloat(Edit5->Text);
 double N_Lon=StrToFloat(Edit6->Text);
 double K=v_lat / N_Lat;
 double L= v_lon/ N_Lon;

 int l1,l2;
 int i = 0;
 for (l1=0;l1<K;l1++)
 {
 for (l2=0;l2<L;l2++)
 {
       TMapElement* f = (TMapElement*)l_elements->Items[i];
        // shirota;
        double Y=base.Y+l2*N_Lat;
        // dolgota;
        double X=base.X+l1*N_Lat;

        f->S_lat = Y;
        f->S_lon = X;
        i++;
    }
 }
}


void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
    if (SaveDialog1->Execute())
    {
        FILE* file = fopen(SaveDialog1->FileName.c_str(), "w+t");
        for (int i = 0; i < this->l_elements->Count; i++)
        {
           TMapElement* f = (TMapElement*)l_elements->Items[i];
           fprintf(file, "%d\t", f->N > 0 ? 1:0);
           for (int j = 0; j < 23; j++)
           {
              fprintf(file, "%f", f->Vector[j]);
           }
           fprintf(file, "\n");
        }
        fclose(file);
    }
}
//---------------------------------------------------------------------------



