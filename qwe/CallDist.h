//---------------------------------------------------------------------------

#ifndef CallDistH
#define CallDistH
#include "awpipl.h"
#define EARTH_DIAM 6372
#define PI_V   3.14159265358979
const int image_width=512;
const int  image_hight=512;
const double area_lat=30;
const double area_lon=30;
const double  dlina_ikvatora=40075.7;

void GavS(double Lat,  double Lon, double Lat2,  double Lon2, double& dist);
void bgrad_shirota (double Lat, double& distSh);
awp2DPoint ConvertLatLonToKm(awp2DPoint base,awp2DPoint coord);
awpPoint  ConvertKmToPix (awp2DPoint P);


class TGeoCoordConverter
{
protected:
  int image_width;
  int  image_hight;
  double area_lat;
  double area_lon;

  awp2DPoint m_base;
public:
  TGeoCoordConverter(awp2DPoint base);
 ~TGeoCoordConverter();
  awp2DPoint ConvertLatLonToKm(awp2DPoint coord);
  awpPoint ConvertKmToPix (awp2DPoint P);
  awp2DPoint Getbase();
  double Getarea_lat();
  void Setarea_lat(double v);
  double Getarea_lon();
  void Setarea_lon(double v);

};

//---------------------------------------------------------------------------
#endif
