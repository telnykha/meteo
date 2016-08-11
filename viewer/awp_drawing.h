//---------------------------------------------------------------------------

#ifndef awp_drawingH
#define awp_drawingH
#include "awpipl.h"
//---------------------------------------------------------------------------
int _awpDrawLine(awpImage* pImage, awpPoint p1, awpPoint p2, AWPBYTE bChan, AWPDOUBLE dValue, double v1,double v2);
AWPRESULT _awpDrawPoint(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue);
AWPRESULT _awpDrawThickPointByte(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius);
AWPRESULT _awpDrawThickPointShort(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius);
AWPRESULT _awpDrawThickPointFloat(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius);
AWPRESULT _awpDrawThickPointDouble(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius);
AWPRESULT _awpDrawThickPoint(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius);
AWPRESULT _awpDrawThickLine(awpImage* pImage, awpPoint p1, awpPoint p2, AWPBYTE bChan, AWPDOUBLE dValue, double v1, double v2);


#endif
