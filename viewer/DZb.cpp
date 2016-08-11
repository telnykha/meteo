//---------------------------------------------------------------------------


#pragma hdrstop
#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include "DZb.h"
 const double ct=8.85;
//---------------------------------------------------------------------------

#pragma package(smart_init)
  void DZb=(double ref,double dist, double x)
  {
  x=ct-(ref+log10(dist));
  }
