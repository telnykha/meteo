//---------------------------------------------------------------------------


#pragma hdrstop
#include "math.h"
#include "map.h"
//#include "system.h"
#include <vcl.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
TMapElement::TMapElement()

{
	N=0;
	double R,MI, MA, Theta, r, mi, ma, theta;
	int S,P,X, Y, s,p,x,y;
	bool N;
	Vector[0]=X/(R+1);
	Vector[1]=Y/(R+1);
	Vector[2]=S/(R*R+1);
	Vector[3]=P/(R+1);
	Vector[4]=MI/(R+1);
	Vector[5]=MA/(R+1);
	Vector[6]=Theta;
	Vector[7]=x/(r+1);
	Vector[8]=y/(r+1);
	Vector[9]=s/(r*r+1);
	Vector[10]=p/(r+1);
	Vector[11]=mi/(r+1);
	Vector[12]=ma/(r+1);
	Vector[13]=theta;
	Vector[14]=N;
}
// class destructor
TMapElement::~TMapElement()
{
}
double  TMapElement::GetS_lat()
{
    return S_lat;
}

void TMapElement::SetS_lat(double L)
{
   S_lat = L;
}
   double  TMapElement::GetS_lon()
{
    return S_lon;
}
  void TMapElement::SetS_lon(double L)
{
   S_lon = L;
}
    double  TMapElement::GetSize_lat()
{
    return Size_lat;
}
   void TMapElement::SetSize_lat(double w)
{
   Size_lat = w;
}
double  TMapElement::GetSize_lon()
{
	return Size_lon;
}
void TMapElement::SetSize_lon(double w)
{
   Size_lon = w;
}
  double CalcDist(int x1, int x2, int y1,int y2, double &R)
  {

  R=sqrt(double(abs(x1*x1-x2*x2)+(abs(y1*y1-y2*y2))));
  }
