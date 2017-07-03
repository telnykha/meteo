//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
 #include <math.h>
 #include "Convert_Log_Lon.h"
#pragma hdrstop

#include "CircleAngel.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
 /*static double Convert(double l)
 {
  double k=(l-floor(l))*60;
  return (floor (l)+k)*3.14/180;

 }
 */

/* static void RCircel(double r0, double fi0, double& X, double& Y, double& NormX,double& NormY)
        {
           X=NormX*(r0/450+1)*cos(fi0*3.14/180);
            Y=NormY*(r0/450+1)*sin(fi0*3.14/180);
          }
          */
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
                    randomize();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
float log;
float lon;
float log_R=46;
float lon_R=-100;
double NormX=Image1->Width/2;
double NormY=Image1->Height/2;
int KK;

// try
 //{
 //l_LOG=StrToFloat(Form1->Edit1->Text);
 //}
 //catch (Exception &exception)
  // {
   // Edit1->Text="1" ;
    // l_LOG=1;
    //}
 //l_LOG=(45+(0.5)*60)*3.14/180;

// l_LON=-(100+0.5*60)*3.14/180;

double r=1;
//double xx=(Image1->Width/2-r)*cos(l_LOG)*sin(l_LON);
//double yy=(Image1->Height /2-r)*sin(l_LOG)*sin(l_LON);
    FILE* f;
       if (OpenDialog1->Execute())
        {
         (f=fopen(OpenDialog1->FileName.c_str(),"r+t"));
         count=0;
                while (fscanf(f,"%f\t%f\t%d\n",&log,&lon,&KK)!= EOF)
                 { double X, Y;
                 ConLL(log_R, lon_R, log, lon, NormX,NormY, X,Y);
                      //(Memo1->Lines->Add(FloatToStr(X[count-1])+"  "+FloatToStr(gama)+"  "+FloatToStr(gama1)));

                       (Memo1->Lines->Add(FloatToStr(X)+"  "+FloatToStr(Y)+"  "+FloatToStr(KK)));

                        DIST[count]=X*1;
                        FI[count]=Y*1;
                        K[count]=KK*1;
                        count++;

                  }
        }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
 void __fastcall TForm1::Memo1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
      {
             int i;
            for (i=0;i<Memo1->Lines->Count; i++)
            {
               
               double R=(K[i]/100.*20);
               if (R<1)
               {
                R=5;
               }

               int a=Image1->Width;
               int b=Image1->Height;
               // x+= Image1->Width/2;
              // y+= Image1->Height/2;
               Image1->Canvas->Brush->Style = bsClear;
               Image1->Canvas->Ellipse(DIST[i], FI[i],DIST[i]+R, FI[i]+R);


            }

}
//---------------------------------------------------------------------------









