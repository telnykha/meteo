//---------------------------------------------------------------------------


#pragma hdrstop
#include "math.h"


#include "CallDist.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//function gaversinusov formula in km
void GavS(double Lat,  double Lon, double Lat2,  double Lon2, double& dist)
{
  // translate to radian

  //lat-shirota(0X)
 //lon-dolgota (0Y)
  Lat=Lat*PI_V/180;
  Lon=Lon*PI_V/180;
  Lat2=Lat2*PI_V/180;
  Lon2=Lon2*PI_V/180;
  double delta_lat2=(Lat2-Lat)/2;
  double delta_lon2=(Lon2-Lon)/2;
  double delta_R2=2*asin(sqrt(sin(delta_lat2)*sin(delta_lat2)+cos(Lat)*cos(Lat2)*sin(delta_lon2)*sin(delta_lon2)));
         dist=delta_R2*EARTH_DIAM;// distance in km
  }


//  class constructor
TGeoCoordConverter::TGeoCoordConverter(awp2DPoint base)
{
    image_width = 512;
    image_hight = 512;
    area_lat =30;
    area_lon = 30;
    m_base=base;
}
// class destructor
TGeoCoordConverter::~TGeoCoordConverter()
{
}

awp2DPoint TGeoCoordConverter::ConvertLatLonToKm(awp2DPoint coord)
{
  double lat,lon,lat2, lon2, dist_X, dist_Y;
  awp2DPoint r;
  // for north and western hemisphere

  lat=m_base.Y;
  lon=m_base.X;
  lat2= coord.Y;
  lon2=coord.X;
 /* if (lat2<lat||lat2>lat+area_lat && abs(lon2)>abs(lon)||abs(lon2)>abs(lon+area_lon))
  {
   r.X=0;
   r.Y=0;
   return r;
  }
  */
  GavS(lat,lon,  lat2, lon, dist_Y);
  GavS(lat,lon,  lat, lon2, dist_X);
  r.X=dist_X;//*cos(lat2*PI_V/180);
  r.Y=dist_Y;
  return r;
}

awp2DPoint TGeoCoordConverter::Getbase()
{
    return m_base;
}
double TGeoCoordConverter::Getarea_lat()
{
    return  area_lat;
}
double TGeoCoordConverter::Getarea_lon()
{
    return  area_lon;
}
void TGeoCoordConverter::Setarea_lat(double v)
{
   area_lat = v;
}

void TGeoCoordConverter::Setarea_lon(double v)
{
 area_lon = v;
}




awpPoint TGeoCoordConverter::ConvertKmToPix (awp2DPoint P)
{

    awpPoint result;
    awp2DPoint pp = ConvertLatLonToKm(P);
    double dist_X1, dist_Y, dist_X2;
    double lat1=m_base.Y;
    double lon1=m_base.X;
    double L=P.Y;
    double G=P.X;
    double GG=G+area_lon;
    double lat2=lat1+area_lat;
    double lon2=lon1+area_lon;
             //find max dist in KM
    GavS(lat1,lon1,  lat2, lon1, dist_Y);
    GavS(lat1,lon1,  lat1, lon2, dist_X1);

    GavS(L, G,  L, GG, dist_X2);
      //GavS(lat1,lon2,  lat2, lon2, dist_X2);
    double dx;
    double Kf_X=image_width/dist_X1;
    double Kf_Y=image_hight/dist_Y;
    dx=(image_width-Kf_X*dist_X2)/2;
    double DX=abs(dist_X1-dist_X2);



    result.X =floor((Kf_X*pp.X-dx)+0.5);
    result.Y = image_hight - floor(Kf_Y*pp.Y+0.5);
    return result;
}

