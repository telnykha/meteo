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
   X=(r0 /1)*cos(fi0*PI_VALUE/180);
   Y=(r0 /1)*sin(fi0*PI_VALUE/180);
}

void ConLL(double Lot1, double Lon1, double Lot2, double Lon2, double NormX, double NormY, double RR, double &xx, double &yy)
//
{
  // double NormX, double NormY -picture size
  //double RR -расстояние максимальное
 /* double gama1;
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

  double x=(gama*EARTH_DIAM); //метрическое расстояние
  double y= (gama*EARTH_DIAM);
 //double y=(asin(g1/g))*180/PI_VALUE;
 */
   //	double R=6372795;
	//double pi=3.14159265358979;
	 Lot1=Lot1*PI_VALUE/180;
	 Lon1=Lon1*PI_VALUE/180;
	 Lot2=Lot2*PI_VALUE/180;
	 Lon2=Lon2*PI_VALUE/180;
	double Lot=(Lot2-Lot1)/2;
	double Lon=(Lon2-Lon1)/2;
	double sigma=2*asin(sqrt((sin(Lot)*sin(Lot))+(cos(Lot1)*cos(Lot2)*sin(Lon)*sin(Lon))));
	double dist=sigma*EARTH_DIAM;
	double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*EARTH_DIAM;
	double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*EARTH_DIAM;
	double Angel;
     if (Lon1==Lon2 && Lot2<Lot1)
    {
	  Angel=90;
    }
    else if (Lon1==Lon2 && Lot2>Lot1)
    {
     Angel=-90;
    }

      if (Lot2<Lot1 && Lon2<Lon1)
      {
		 double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*EARTH_DIAM;
		 double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*EARTH_DIAM;
		 Angel=((atan(dy/dx)))*180/PI_VALUE;
      }
       else if (Lot2<Lot1 && Lon2>Lon1)
       {
		  double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*EARTH_DIAM;
		  double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*EARTH_DIAM;

		  Angel=((atan(dy/dx))*180/PI_VALUE)+90;
       }
       else if (Lot2>Lot1 && Lon2>Lon1)
       {
		  double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*EARTH_DIAM;
		  double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*EARTH_DIAM;
		  Angel=((atan(dy/dx))*180/PI_VALUE)+180;
       }
       else if (Lot2>Lot1 && Lon2<Lon1)
       {
		double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*EARTH_DIAM;
		double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*EARTH_DIAM;

		  Angel=((atan(dy/dx))*180/PI_VALUE)+270;
	   }
		Angel=Angel+180;
		//double A=(Angel+180);
	 //xx=(cos(A*PI_VALUE/180))*dist;
	 //yy=(sin(A*PI_VALUE/180))*dist;
	 double Kx=NormX/(2*RR);
	 double Ky=NormY/(2*RR);
 // RCircel(dist,A, xx,yy);
   //	xx=(0.5*NormX-dist/450)*cos(Angel);
   //	yy=(0.5*NormY-dist/450)*sin(Angel);
	xx=0.5*NormX+Kx*dist*cos(Angel*PI_VALUE/180);
	yy=0.5*NormY+Ky*dist*sin(Angel*PI_VALUE/180);
  //xx = 0.5*NormX*(xx + 1);
  //yy = 0.5*NormY*(yy + 1);
}



