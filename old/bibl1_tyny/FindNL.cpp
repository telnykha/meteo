//---------------------------------------------------------------------------


#pragma hdrstop

#include "FindNL.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

double GetMinFromTime(TTime t)
{
   unsigned int h,m,s,ms;
   t.DecodeTime(&h,&m,&s,&ms);
    return 60*h+m;
}


        TFlash* FindNL(TList*l, TTime t)
        {
        TFlash* result=NULL;
        mTime.DecodeTime(&h,&m,&s,&ms);
        int t=60&h+m;
        int MinT=1440;  // min time in minut

        for (int i=0; i<l->Count;i++)
        {
        TFlash*a=(TFlash)*l->Items[i];

       int delta=abs(a->time-t);
        if(delta<MinT)
        {
          MinT=delta;
          result=a;
        }
         return;
        }
       }


