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
	Vector[12];


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
  double CalcDist(int x1, int x2, int y1, int y2, double &R)
  {

  R=sqrt(double(abs(x1*x1-x2*x2)+(abs(y1*y1-y2*y2))));
  }
