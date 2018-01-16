//---------------------------------------------------------------------------

#ifndef LFlashH
#define LFlashH
#include <vcl.h>

  typedef struct
{
    TDateTime time;
    double lat;
    double lon;
    int    num;
}TFlash;
int LFlash (char* Filename, TList* list);
TFlash* FindNL(TList*l, TTime T0);
void FindFlashes(TList* in, TList* out, TTime t, double dt);



//---------------------------------------------------------------------------
#endif
