//---------------------------------------------------------------------------
#pragma hdrstop
#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include "Convert_Log_Lon.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


 // a,b -picture size
static void RCircel(double r0, double fi0, double& X, double& Y)
{
   X=(r0 / 450)*cos(fi0*PI_VALUE/180);
   Y=(r0 / 450)*sin(fi0*PI_VALUE/180);
}

void ConLL(double log, double lon, double log_R, double lon_R, double NormX, double NormY, double &xx, double &yy)
{
  // a,b -picture size
  double gama1;
  double gama;
  double l_LOG=log_R*PI_VALUE/180;// center of radar
  double l_LON=lon_R*PI_VALUE/180;   // center of radar
  double Log=log*PI_VALUE/180;  // current Log
  double Lon=lon*PI_VALUE/180;  // current Lon

    if (l_LOG==Log && l_LON==Lon)
    {
        xx=NormX;
        yy=NormY;
        return;
	}

  gama=2*asin(sqrt(sin((l_LOG-Log)/2)*sin((l_LOG-Log)/2)+cos(Log)*cos(l_LOG)*sin((l_LON-Lon)/2)*sin((l_LON-Lon)/2)));  //gaversinusov  formula
  //double gama=acos(sin(l_LOG)*sin(Log)+cos(l_LOG)*cos(Log)*cos(l_LON-Lon));  // simple formula
  gama1=2*asin((sqrt(cos(l_LOG)*cos(l_LOG)*sin((l_LON-Lon)/2)*sin((l_LON-Lon)/2))));
   double g1=sin(gama1);
   double g=sin(gama);
   if ((abs(g1-g))<0.001)
	  return;

  double x=(gama*EARTH_DIAM);
  double y=(asin(g1/g))*180/PI_VALUE;

  RCircel(x,y, xx,yy);
  xx = 0.5*NormX*(xx + 1);
  yy = 0.5*NormY*(yy + 1);
}


