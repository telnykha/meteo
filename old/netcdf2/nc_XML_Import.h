//---------------------------------------------------------------------------

#ifndef nc_XML_ImportH
#define nc_XML_ImportH
#include <VCL.h>
typedef struct{
AnsiString FileName;
TDateTime FDate;
TDateTime FTime;
TList* ListFlash;
}MREvent;

typedef struct
{
    TDateTime time;
    double lat;
    double lon;
    int    num;
}TFlash;

void ReadXML( AnsiString XFile, TList* MyList, AnsiString &RadarName, AnsiString & RadarType, double &Lat, double &Lon);

//---------------------------------------------------------------------------
#endif
