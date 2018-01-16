//---------------------------------------------------------------------------


#pragma hdrstop
#include <stdio.h>
#include "math.h"
#include "LFlash.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
static double GetMinFromTime(TTime t)
{
   unsigned short h,m,s,ms;
   t.DecodeTime(&h,&m,&s,&ms);
    return 60*h+m;
}

   int LFlash (char* FileName, TList* list)

   {
    float log;
    float lon;
    int KK;
    char stime[15];

            FILE* f = fopen(FileName,"r+t");
        if (f == NULL)
                return 1;


    list->Clear();
    while (fscanf(f,"%s\t%f\t%f\t%d\n",&stime, &log,&lon,&KK)!= EOF )
    {
       AnsiString str = stime;
        unsigned short hour, min, sec;
       hour = StrToInt(str.SubString(0,2));
       min = StrToInt(str.SubString(4,2));
       sec = StrToInt(str.SubString(7,2));
        TTime t(hour,min, sec,0);
        TFlash* Flash=new TFlash;
        Flash->lat=log;
        Flash->lon=lon;
        Flash->time=t;
        Flash->num=KK;
        list->Add(Flash);
       }
   }

  TFlash* FindNL(TList*l, TTime T0)
  {
   TFlash* result=NULL;
   int m1 = 0;
   int m2 = 0;
   unsigned short ht;
   unsigned short mt;
   unsigned short st;
   unsigned short mst;


   T0.DecodeTime(&ht, &mt, &st, &mst);
   m1=ht*60 + mt;
   int min = 60;
   for (int i = 0; i < l->Count; i++)
   {
        TFlash* f = (TFlash*)l->Items[i];
        f->time.DecodeTime(&ht, &mt, &st, &mst);
        m2 = ht*60+mt;
        if (fabs(m2-m1) < min)
        {
            min = fabs(m2-m1);
            result = f;
        }
   }
  return result;
  }

void FindFlashes(TList* in, TList* out, TTime t, double dt)
{
  double m1 = 0;
  double m2 = 0;

   out->Clear();
   m1= GetMinFromTime(t);
   for (int i = 0; i < in->Count; i++)
   {
        TFlash* f = (TFlash*)in->Items[i];

        m2 = GetMinFromTime(f->time);
        if (m2-m1 > 0 && m2 - m1 < dt )
        {
                TFlash* f1 = new TFlash();
                f1->time = f->time;
                f1->lat=f->lat;
                f1->lon=f->lon;
                f1->num=f->num;

                out->Add(f1);
        }
   }
 

}








