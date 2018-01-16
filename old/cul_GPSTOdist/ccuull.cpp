//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
 
#include "FGPS.h"
#include "ccuull.h"
//#define R=6372795;
//#define pi=3.14159265358979;
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
void __fastcall TForm1::Button1Click(TObject *Sender)
{
{
double R=6372795;
double pi=3.14159265358979;
double Lot1=(StrToFloat(Edit1->Text));
double Lon1=(StrToFloat(Edit2->Text));
double Lot2=(StrToFloat(Edit3->Text));
double Lon2=(StrToFloat(Edit4->Text));
double dist;
double Angel;
GPSToDist( Lot1, Lon1, Lot2, Lon2, dist, Angel);
  /*
double Lot=(Lot2-Lot1)/2;
double Lon=(Lon2-Lon1)/2;
double sigma=2*asin(sqrt((sin(Lot)*sin(Lot))+(cos(Lot1)*cos(Lot2)*sin(Lon)*sin(Lon))));
double dist=sigma*R;
double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*R;
double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*R;
double alfa=(atan(dy/dx))*180/pi;
double dist_check=sqrt(dx*dx+dy*dy);
 */
Edit6->Text=Angel;
Edit5->Text=dist;


 /*
Edit14->Text=dx;
Edit15->Text=dy;
Edit18->Text=Lot*180/pi;
Edit19->Text=Lon*180/pi;
Edit17->Text=dist_check-dist;
Edit16->Text=dist_check;
  */
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
 {
;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    double pi=3.14159265358979;
double R=6372795;
double Lot1=(StrToFloat(Edit7->Text));
double Lon1=(StrToFloat(Edit8->Text));
double dist=StrToFloat(Edit9->Text);
double Angel=(StrToFloat(Edit10->Text));

double Lot2, Lon2;
bool North, West;
North =CheckBox1->Checked;
 West=CheckBox2->Checked;
 DistToGPS ( Lot1,  Lon1, dist, Angel,  North, West, Lot2,  Lon2);
  Edit11->Text=Lot2;
  Edit12->Text=Lon2;

}
//---------------------------------------------------------------------------

