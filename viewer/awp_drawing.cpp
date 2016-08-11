//---------------------------------------------------------------------------


#pragma hdrstop

#include "awp_drawing.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int _awpDrawLine(awpImage* pImage, awpPoint p1, awpPoint p2, AWPBYTE bChan, AWPDOUBLE dValue, double v1,double v2)
{
	AWPRESULT res;
	AWPWORD t, distance;
	AWPSHORT incx, incy;

	AWPWORD startx=p1.X;
	AWPWORD starty=p1.Y;
	AWPWORD endx=p2.X;
	AWPWORD endy=p2.Y;
	AWPINT xerr = 0, yerr = 0, delta_x, delta_y;
    double r1,r;

	res = AWP_OK;
	_CHECK_RESULT_(( res = awpCheckImage(pImage)))
 	/*check the position*/
	if (p1.X >= pImage->sSizeX || p1.Y >= pImage->sSizeY || p1.X < 0 || p1.Y < 0)
   		_ERROR_EXIT_RES_(AWP_BADARG)
	/*check the position*/
	if (p2.X >= pImage->sSizeX || p2.Y >= pImage->sSizeY || p2.X < 0 || p2.Y < 0)
   		_ERROR_EXIT_RES_(AWP_BADARG)
	/*check the channel*/
	if (bChan >= pImage->bChannels)
		_ERROR_EXIT_RES_(AWP_BADARG)


	delta_x = endx - startx;
	delta_y = endy - starty;

	if (delta_x > 0) incx = 1;
	else if (delta_x == 0) incx = 0;
	else incx = -1;

	if (delta_y > 0) incy = 1;
	else if (delta_y == 0) incy = 0;
	else incy = -1;

	delta_x = abs(delta_x);
	delta_y = abs(delta_y);
	if (delta_x > delta_y) distance = delta_x;
	else distance = delta_y;

    r = sqrt((p2.X - p1.X)*(p2.X - p1.X) + (p2.Y - p1.Y)*(p2.Y - p1.Y));

	for (t = 0; t <= distance + 1; t ++)
	{
      if (startx < pImage->sSizeX && starty < pImage->sSizeY )
      {
        r1 = sqrt((startx - p1.X)*(startx - p1.X) + (starty - p1.Y)*(starty - p1.Y));

        double v = r1*(v2-v1) / (r) + v1;

        if (r == 0)
            v =  dValue;
		switch (pImage->dwType)
		{
			case AWP_BYTE:
					_PIXEL(pImage, startx, starty, bChan, AWPBYTE) = (AWPBYTE)dValue;
				break;
			case AWP_SHORT:
					_PIXEL(pImage, startx, starty, bChan, AWPSHORT) = (AWPSHORT)dValue;
				break;
			case AWP_FLOAT:
					_PIXEL(pImage, startx, starty, bChan, AWPFLOAT) = (AWPFLOAT)dValue;
 				break;
			case AWP_DOUBLE:
					_PIXEL(pImage, startx, starty, bChan, AWPDOUBLE) = v;
				break;
			default:
				_ERROR_EXIT_RES_(AWP_BADARG)
		}
      }

		xerr += delta_x;
		yerr += delta_y;
		if (xerr > (AWPINT)distance){xerr -= (AWPINT)distance; startx += (DWORD)incx;}
		if (yerr > (AWPINT)distance){yerr -= (AWPINT)distance; starty += (DWORD)incy;}
	}

CLEANUP:
    return res;
}
AWPRESULT _awpDrawPoint(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue)
{
	AWPRESULT res;
	AWPBYTE*	b;
	SHORT*	s;
	AWPFLOAT*  f;
	AWPDOUBLE* d;
	WORD  width; /*width of image line in elements*/
	DWORD pos;
	res = AWP_OK;
	_CHECK_RESULT_(( res = awpCheckImage(pImage)))
	/*check the position*/
	if (p.X >= pImage->sSizeX || p.Y >= pImage->sSizeY)
		_ERROR_EXIT_RES_(AWP_BADARG)
	/*check the channel*/
	if (bChan >= pImage->bChannels)
		_ERROR_EXIT_RES_(AWP_BADARG)
	/*pointer to the channel*/
	width = pImage->bChannels*pImage->sSizeX;
	pos = p.Y*width + p.X*pImage->bChannels + bChan;
	switch (pImage->dwType)
	{
	case AWP_BYTE:
			b = (AWPBYTE*)pImage->pPixels;
			b[pos] = (AWPBYTE)dValue;
		break;
	case AWP_SHORT:
			s = (SHORT*)pImage->pPixels;
			s[pos] = (SHORT)dValue;
		break;
	case AWP_FLOAT:
			f = (AWPFLOAT*)pImage->pPixels;
			f[pos] = (AWPFLOAT)dValue;
 		break;
	case AWP_DOUBLE:
			d = (AWPDOUBLE*)pImage->pPixels;
			d[pos] = dValue;
		break;
	default:
		_ERROR_EXIT_RES_(AWP_BADARG)
	}
CLEANUP:
    return res;
}
/*awpDrawThickPointByte
закрашивает окрестность точки p на изобажении, содержащем данные типа AWPBYTE*/
AWPRESULT _awpDrawThickPointByte(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
{
	AWPBYTE* b = (AWPBYTE*)pImage->pPixels;
	AWPBYTE  v = (AWPBYTE)dValue;
	AWPWORD  x, y;
	for (y = p.Y - radius; y < p.Y + radius; y++)
	{
		for (x = p.X - radius; x < p.X + radius; x++)
		{
			b[(x + y*pImage->sSizeX)*pImage->bChannels + bChan] = v;
		}
	}
	return AWP_OK;
}
/*awpDrawThickPointShort
закрашивает окрестность точки p на изобажении, содержащем данные типа AWPSHORT*/
AWPRESULT _awpDrawThickPointShort(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
{
	AWPSHORT* b = (AWPSHORT*)pImage->pPixels;
	AWPSHORT  v = (AWPSHORT)dValue;
	AWPWORD  x, y;
	for (y = p.Y - radius; y < p.Y + radius; y++)
	{
		for (x = p.X - radius; x < p.X + radius; x++)
		{
			b[x + y*pImage->sSizeX + bChan] = v;
		}
	}
	return AWP_OK;
}
/*awpDrawThickPointFloat
закрашивает окрестность точки p на изобажении, содержащем данные типа AWPSHORT*/
AWPRESULT _awpDrawThickPointFloat(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
{
	AWPFLOAT* b = (AWPFLOAT*)pImage->pPixels;
	AWPFLOAT  v = (AWPFLOAT)dValue;
	AWPWORD  x, y;
	for (y = p.Y - radius; y < p.Y + radius; y++)
	{
		for (x = p.X - radius; x < p.X + radius; x++)
		{
			b[x + y*pImage->sSizeX + bChan] = v;
		}
	}
	return AWP_OK;
}
/*awpDrawThickPointDouble
закрашивает окрестность точки p на изобажении, содержащем данные типа AWPSHORT*/
AWPRESULT _awpDrawThickPointDouble(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
{
	AWPDOUBLE* b = (AWPDOUBLE*)pImage->pPixels;
	AWPDOUBLE  v = (AWPDOUBLE)dValue;
	AWPWORD  x, y;
	for (y = p.Y - radius; y < p.Y + radius; y++)
	{
		for (x = p.X - radius; x < p.X + radius; x++)
		{
			b[x + y*pImage->sSizeX + bChan] = v;
		}
	}
	return AWP_OK;
}
// awpDrawThickPoint
// закрашивает окрестность точки p радиусом r
AWPRESULT _awpDrawThickPoint(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
{
    AWPRESULT res = AWP_OK;
	AWPINT maxx = p.X + radius;
	AWPINT minx = p.X - radius;
	AWPINT maxy = p.Y + radius;
	AWPINT miny = p.Y - radius;

	// проверка входных данных
	_CHECK_RESULT_(( res = awpCheckImage(pImage)))
	/*координата точки p с учетом радиуса точки не может выходить
	за пределы изображения*/
	if (maxx >= pImage->sSizeX || minx < 0 || maxy >= pImage->sSizeY || miny < 0)
		_ERROR_EXIT_RES_(AWP_BADARG)
	/* номер канала, на котором должна быть отрисована точка не может быть 
	   больше числа каналов входного изображения */
	if (bChan > pImage->bChannels)
		_ERROR_EXIT_RES_(AWP_BADARG)
	/*todo: значение якорсти рисуемой точки dValue не может выходить за допустимый диапазон, определяемый 
	выбранным типом изображения*/
	switch (pImage->dwType)
	{
	case AWP_BYTE:
		_CHECK_RESULT_(( res = _awpDrawThickPointByte(pImage, p, bChan, dValue, radius)))
		break;
	case AWP_SHORT:
		_CHECK_RESULT_(( res = _awpDrawThickPointShort(pImage, p, bChan, dValue, radius)))
		break;
	case AWP_FLOAT:
		_CHECK_RESULT_(( res = _awpDrawThickPointFloat(pImage, p, bChan, dValue, radius)))
		break;
	case AWP_DOUBLE:
		_CHECK_RESULT_(( res = _awpDrawThickPointDouble(pImage, p, bChan, dValue, radius)))
		break;
	}
CLEANUP:
	return res;
}



AWPRESULT _awpDrawThickLine(awpImage* pImage, awpPoint p1, awpPoint p2, AWPBYTE bChan, AWPDOUBLE dValue, double v1, double v2)
{
	AWPRESULT res;
	AWPWORD t, distance;
	AWPSHORT incx, incy;

	AWPWORD startx=p1.X;
	AWPWORD starty=p1.Y;
	AWPWORD endx=p2.X;
	AWPWORD endy=p2.Y;
	AWPINT xerr = 0, yerr = 0, delta_x, delta_y;
	awpPoint p;
    double r,r1,v;

	res = AWP_OK;
	_CHECK_RESULT_(( res = awpCheckImage(pImage)))
 	/*check the position*/
	if (p1.X >= pImage->sSizeX || p1.Y >= pImage->sSizeY || p1.X < 0 || p1.Y < 0)
   		_ERROR_EXIT_RES_(AWP_BADARG)
	/*check the position*/
	if (p2.X >= pImage->sSizeX || p2.Y >= pImage->sSizeY || p2.X < 0 || p2.Y < 0)
   		_ERROR_EXIT_RES_(AWP_BADARG)
	/*check the channel*/
	if (bChan >= pImage->bChannels)
		_ERROR_EXIT_RES_(AWP_BADARG)
	//width = pImage->bChannels*pImage->sSizeX;
/*	pos = p1.Y*width + p.X*bChan + bChan;*/

	delta_x = endx - startx;
	delta_y = endy - starty;

	if (delta_x > 0) incx = 1;
	else if (delta_x == 0) incx = 0;
	else incx = -1;

	if (delta_y > 0) incy = 1;
	else if (delta_y == 0) incy = 0;
	else incy = -1;

	delta_x = abs(delta_x);
	delta_y = abs(delta_y);
	if (delta_x > delta_y) distance = delta_x;
	else distance = delta_y;

     r = sqrt((p2.X - p1.X)*(p2.X - p1.X) + (p2.Y - p1.Y)*(p2.Y - p1.Y));


	for (t = 0; t <= distance + 1; t ++)
	{
      if (startx < pImage->sSizeX && starty < pImage->sSizeY )
      {
		p.X = startx;p.Y = starty;
         r1 = sqrt((startx - p1.X)*(startx - p1.X) + (starty - p1.Y)*(starty - p1.Y));

         v = r1*(v2-v1) / (r) + v1;

        if (r == 0)
            v =  dValue;


		_awpDrawThickPoint(pImage,p,bChan, v,1);
	  }

		xerr += delta_x;
		yerr += delta_y;
		if (xerr > (AWPINT)distance){xerr -= (AWPINT)distance; startx += (DWORD)incx;}
		if (yerr > (AWPINT)distance){yerr -= (AWPINT)distance; starty += (DWORD)incy;}
	}

CLEANUP:
    return res;
}

#pragma package(smart_init)
