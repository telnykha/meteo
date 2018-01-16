//---------------------------------------------------------------------------

#ifndef FGPSH
#define FGPSH
 void GPSToDist(double Lot1, double Lon1, double Lot2, double Lon2, double& dist, double& Angel);
 void DistToGPS (double Lot1, double Lon1, double dist, double Angel, bool North, bool West, double& Lot2, double& Lon2);
//---------------------------------------------------------------------------
#endif
