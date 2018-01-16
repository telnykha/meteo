//---------------------------------------------------------------------------

#ifndef mapH
#define mapH
#include "awpipl.h"

//---------------------------------------------------------------------------
#endif

class TMapElement
{
public:
 TMapElement();
 ~TMapElement();

  double S_lat,S_lon,Size_lat, Size_lon;    //rectangle size
  int N;									// ligthing summa;
  double Vector[23];

  double GetS_lat();
  void SetS_lat(double L);
  double GetS_lon();
  void SetS_lon(double L);
  double GetSize_lat();
  void SetSize_lat(double w);
  double GetSize_lon();
  void SetSize_lon(double w);
};
