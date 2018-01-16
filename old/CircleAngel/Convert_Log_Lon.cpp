//---------------------------------------------------------------------------


#pragma hdrstop
    #include <vcl.h>
    #include <stdio.h>
    #include <math.h>

#include "Convert_Log_Lon.h"
 // a,b -picture size
 static void RCircel(double r0, double fi0, double& X, double& Y)
        {
           X=(r0/450)*cos(fi0*3.14/180);
           Y=(r0/450)*sin(fi0*3.14/180);
          }

void ConLL(double &log, double &lon, double &log_R, double &lon_R, double& NormX, double& NormY, double &xx, double &yy)
{
// a,b -picture size
double gama1;
double gama;
double l_LOG=log_R*3.14159265358979/180;// center of radar
double l_LON=lon_R*3.14159265358979/180;   // center of radar
double Log=log*3.14159265358979/180;  // current Log
double Lon=lon*3.14159265358979/180;  // current Lon

    if (l_LOG==Log && l_LON==Lon)
    {
        xx=NormX;
        yy=NormY;
        return;
    }

 gama=2*asin(sqrt(sin((l_LOG-Log)/2)*sin((l_LOG-Log)/2)+cos(Log)*cos(l_LOG)*sin((l_LON-Lon)/2)*sin((l_LON-Lon)/2)));  //gaversinusov  formula  
//double gama=acos(sin(l_LOG)*sin(Log)+cos(l_LOG)*cos(Log)*cos(l_LON-Lon));  // simple formula
 gama1=2*asin((sqrt(cos(l_LOG)*cos(l_LOG)*sin((l_LON-Lon)/2)*sin((l_LON-Lon)/2))));
                   double x=(gama*6372);
                   double y=(asin(sin(gama1)/sin(gama)))*180/3.14;

                RCircel(x,y,xx,yy);
                  xx= NormX*xx + 0.5*NormX;
                  yy=NormY*yy + 0.5*NormY;



}

//---------------------------------------------------------------------------

#pragma package(smart_init)






//---------------------------------------------------------------------------


