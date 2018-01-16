//---------------------------------------------------------------------------

#ifndef LatLonCalcUnitH
#define LatLonCalcUnitH
//---------------------------------------------------------------------------

typedef struct tagGPSPoint
{
    double lat;
    double lon;
}GPSPoint;

void GPSPointsToDist(GPSPoint p1, GPSPoint p2, double& dist, double& angle);
void DistToGPSPoint(GPSPoint p0, double dist, double angle, bool north, bool west,  GPSPoint& result);

#endif
