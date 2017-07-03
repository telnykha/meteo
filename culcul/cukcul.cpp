//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "cukcul.h"
#include "LatLonCalcUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CULCULATEClick(TObject *Sender)
{
double R=6372795;
double pi=3.14159265358979;
double Lot1=(StrToFloat(Edit1->Text))*pi/180;
double Lon1=(StrToFloat(Edit2->Text))*pi/180;
double Lot2=(StrToFloat(Edit3->Text))*pi/180;
double Lon2=(StrToFloat(Edit4->Text))*pi/180;
double Lot=(Lot2-Lot1)/2;
double Lon=(Lon2-Lon1)/2;
double sigma=2*asin(sqrt((sin(Lot)*sin(Lot))+(cos(Lot1)*cos(Lot2)*sin(Lon)*sin(Lon))));
double dist=sigma*R;
double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*R;
double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*R;
double alfa=(atan(dy/dx))*180/pi;
double dist_check=sqrt(dx*dx+dy*dy);
Edit6->Text=alfa;
Edit5->Text=dist;

  GPSPoint p1;
  GPSPoint p2;

  p1.lat= Lot1;
  p1.lon = Lon1;

  p2.lat= Lot2;
  p2.lon = Lon2;
  double angle = alfa;

 GPSPointsToDist(p1, p2, dist, angle);


Edit14->Text=dx;
Edit15->Text=dy;
Edit18->Text=Lot*180/pi;
Edit19->Text=Lon*180/pi;
Edit17->Text=dist_check-dist;
Edit16->Text=dist_check;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
double pi=3.14159265358979;
double R=6372795;
double Lot1=(StrToFloat(Edit7->Text))*pi/180;
double Lon1=(StrToFloat(Edit8->Text))*pi/180;
double dist=StrToFloat(Edit20->Text);
double alfa=(StrToFloat(Edit10->Text));
alfa=alfa*pi/180;
double distX=dist*cos(alfa);//StrToFloat(Edit9->Text);
double distY=dist*sin(alfa); //StrToFloat(Edit13->Text);

double X=((dist*cos(alfa))/2)/R;
double Y=((dist*sin(alfa))/2)/R;


double Lot2=(asin(sqrt(sin(Y)*sin(Y))))*180/pi;
double Lon2=((asin(sqrt((sin(X)*sin(X))/(cos(Lot1)*cos(Lot1))))))*180/pi;

    GPSPoint p0;
    GPSPoint result;

    p0.lat = Lot1;
    p0.lon = Lon1;
    double angle = alfa;

   DistToGPSPoint(p0, dist, angle, CheckBox1->Checked, CheckBox2->Checked, result);

   if (CheckBox1->Checked)
  {
         if (Lot1<0)
         {
           Edit11->Text=-(2*Lot2*pi/180+(-Lot1))*180/pi;
            }
            else
             {
                Edit11->Text=(2*Lot2*pi/180+Lot1)*180/pi;
             }

        }

        else
        {
        if (Lot1<0)
         {
           Edit11->Text=-((-Lot1)-2*Lot2*pi/180)*180/pi;
            }
        else
            {
            Edit11->Text=(Lot1-2*Lot2*pi/180)*180/pi;
            }
           }


           if (CheckBox2->Checked)
           {
                    if (Lon1<0)
                {

                        Edit12->Text=-(2*Lon2*pi/180+(-Lon1))*180/pi;
                 }
                             else
                 {
                                    Edit12->Text=(2*Lon2*pi/180+Lon1)*180/pi;
            }
        }
         else
         {
              if (Lon1<0)
                {

                        Edit12->Text=-((-Lon1)-2*Lon2*pi/180)*180/pi;
                 }
                             else
                 {
                                    Edit12->Text=(Lon1-2*Lon2*pi/180)*180/pi;
            }
         }

Edit9->Text=distX;
 Edit13->Text=distY;
double DDy=StrToFloat(Edit15->Text);
double DDx=StrToFloat(Edit14->Text);
double errorDx=DDx-distX;
double errorDy=DDy-distY;

 Edit22->Text=errorDx;
 Edit21->Text=errorDy;
}
//---------------------------------------------------------------------------




