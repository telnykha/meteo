//---------------------------------------------------------------------------


#pragma hdrstop

#include "fGPS.h"
#include <math.h>
//#define R=6372795;
//#define pi=3.14159265358979;
 void GPSToDist(double Lot1, double Lon1, double Lot2, double Lon2, double& dist, double& Angel)
 {
    double R=6372795;
    double pi=3.14159265358979;
    Lot1=Lot1*pi/180;
     Lon1=Lon1*pi/180;
     Lot2=Lot2*pi/180;
     Lon2=Lon2*pi/180;
    double Lot=(Lot2-Lot1)/2;
    double Lon=(Lon2-Lon1)/2;
    double sigma=2*asin(sqrt((sin(Lot)*sin(Lot))+(cos(Lot1)*cos(Lot2)*sin(Lon)*sin(Lon))));
    dist=sigma*R;

   // double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*R;
   // double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*R;


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
         double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*R;
         double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*R;
         Angel=((atan(dy/dx)))*180/pi;
      }
       else if (Lot2<Lot1 && Lon2>Lon1)
       {
          double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*R;
          double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*R;

          Angel=((atan(dy/dx))*180/pi)+90;
       }
       else if (Lot2>Lot1 && Lon2>Lon1)
       {
          double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*R;
          double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*R;
          Angel=((atan(dy/dx))*180/pi)+180;
       }
       else if (Lot2>Lot1 && Lon2<Lon1)
       {
        double dx=(2*asin(sqrt(cos(Lot1)*cos(Lot1)*sin(Lon)*sin(Lon))))*R;
        double dy=(2*asin(sqrt(sin(Lot)*sin(Lot))))*R;

          Angel=((atan(dy/dx))*180/pi)+270;
       }
         /*
     Angel=(atan(dy/dx))*180/pi; */



         }
 void DistToGPS (double Lot1, double Lon1, double dist, double Angel, bool North, bool West, double& Lot2, double& Lon2)
 {
      double R=6372795;
      double pi=3.14159265358979;
      Angel=Angel*pi/180;
      Lot1=Lot1*pi/180;
      Lon1=Lon1*pi/180;
      double X=((dist*cos(Angel))/2)/R;
      double Y=((dist*sin(Angel))/2)/R;
      Lot2=(asin(sqrt(sin(Y)*sin(Y))))*180/pi;  //schitaet raznizy Lot1 lot2
      Lon2=((asin(sqrt((sin(X)*sin(X))/(cos(Lot1)*cos(Lot1))))))*180/pi; //schitaet raznizy Lot1 lot2
      ///////
      if (North==false)
  {
         if (Lot1<0)
         {
           Lot2=-(2*Lot2*pi/180+(-Lot1))*180/pi;
            }
            else
             {
                Lot2=(2*Lot2*pi/180+Lot1)*180/pi;
             }

        }

        else
        {
        if (Lot1<0)
         {
           Lot2=-((-Lot1)-2*Lot2*pi/180)*180/pi;
            }
        else
            {
            Lot2=(Lot1-2*Lot2*pi/180)*180/pi;
            }
           }


           if (West==false)
           {
                    if (Lon1<0)
                {

                        Lon2=-(2*Lon2*pi/180+(-Lon1))*180/pi;
                 }
                             else
                 {
                                    Lon2=(2*Lon2*pi/180+Lon1)*180/pi;
            }
        }
         else
         {
              if (Lon1<0)
                {

                        Lon2=-((-Lon1)-2*Lon2*pi/180)*180/pi;
                 }
                             else
                 {
                                    Lon2=(Lon1-2*Lon2*pi/180)*180/pi;
            }
         }


        }
//---------------------------------------------------------------------------

#pragma package(smart_init)
 