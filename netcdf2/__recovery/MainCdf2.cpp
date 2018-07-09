//---------------------------------------------------------------------------

#include <vcl.h>
#include "netcdf.h"
#include <math.h>
#pragma hdrstop

#include "MainCdf2.h"
#include "OptionsForm.h"
#include "Convert_Log_Lon.h"
#include "map.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage"
#pragma link "netcdfb.lib"
#pragma resource "*.dfm"


#define _ERR_EXIT_	goto CLEANUP;
#define _CHECK_RESULT_(r) if ((r) != AWP_OK) goto CLEANUP;
#define _ERROR_EXIT_RES_(v) {res = v; goto CLEANUP;}
#define _PIXEL(img, x, y, ch, type)\
	((type*)img->pPixels)[y*img->sSizeX*img->bChannels + x*img->bChannels + ch]

TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
	FList=new TList ();
	VecList=new TList ();
	MapList=new TList ();
	m_azmuth = NULL;
    m_dist   = NULL;
    m_elev   = NULL;

    m_mdown = false;
    m_max_lenght = 250*1800 / 1000;//максимальная длина луча

	m_2DViewOptions = eIntepolatedCone;
    m_3DViewOptions = e3dConeContours;

	m_2DOptions.dist_x = 150;
    m_2DOptions.step_ro = 2;
	m_2DOptions.step_fi = 2;
    m_2DOptions.smooth = false;
    m_2DOptions.contours = false;

    m_3DPoints = NULL;
    m_num3DPoints = 0;

    m_3DContours = 0;
    m_num3DContours = NULL;

	m_planeOptions.imageWidth = 512;
    m_planeOptions.Height = 3000;
	m_planeOptions.Distance = 150;
	m_strDataPath = L"";

    m_outFile = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SpeedButton1Click(TObject *Sender)
{
    if (OpenDialog1->Execute())
    {

       AnsiString RadarName, RadarType;
       this->m_strDataPath = ExtractFilePath(OpenDialog1->FileName);
       m_strDataPath += L"\\";
       FList->Clear();
       ReadXML (OpenDialog1->FileName,  FList,RadarName, RadarType,RLat,RLon);
       ComboBox3->Items->Clear();
       for(int i = 0; i < FList->Count; i++)
       {
           MREvent* e = ( MREvent*)FList->Items[i];
           ComboBox3->Items->Add(e->FileName);
       }
	   ComboBox3->ItemIndex = 0;
       ComboBox3Change(NULL);
       return;
    }

   ComboBox1->ItemIndex = 0;
   this->Draw2DScene();
}



static void _bSaveAWPAsDAT(const char* lpFileName, awpImage* pImage)
{
   FILE* F = fopen(lpFileName, "w+t");
   if (F != NULL)
   {
        //
        AWPDOUBLE* pix = (AWPDOUBLE*)pImage->pPixels;
        for (int y = 0; y < pImage->sSizeY; y++)
        {
            for (int x = 0; x < pImage->sSizeX; x++)
            {
               fprintf(F, "%f\n", pix[y*pImage->sSizeX + x]);
            }

        }
        fclose(F);
   }
}


void __fastcall TForm2::OpenNCFile(const char* lpFileName)
{
	if (m_ncid != 0)
    {
        nc_close(m_ncid);
        m_ncid = 0;
    }
    _AWP_SAFE_RELEASE_(m_source);
    _AWP_SAFE_RELEASE_(m_azmuth);
    _AWP_SAFE_RELEASE_(m_elev);
    if (m_dist != NULL)
    {
        free(m_dist);
        m_dist = NULL;
    }

    int status = NC_NOERR;
    int ncid   = 0;
    AnsiString FileName = lpFileName;
    status = nc_open(lpFileName, 0, &m_ncid);
    if (status != NC_NOERR)
        ShowMessage("не могу открыть файл " + FileName);

    int  ndims, nvars, ngatts, unlimdimid;
    status = nc_inq(m_ncid, &ndims, &nvars, &ngatts, &unlimdimid);
    if (status != NC_NOERR)
        ShowMessage("не могу открыть файл " + FileName);
    int varID;
    nc_inq_varid(this->m_ncid, "Reflectivity", &varID);


    nc_type xtypep;
    int ndimsp;
    int dimidsp[128];
    int nattsp;
	nc_inq_var(this->m_ncid,  varID, NULL, &xtypep, &ndimsp, dimidsp, &nattsp);

    char buf[NC_MAX_NAME+1];
    int w, h, c;
    for (int i = 0; i < ndimsp; i++)
    {
       size_t len;
       nc_inq_dim(this->m_ncid,dimidsp[i], buf, &len);
       AnsiString str = buf;

         if (str == "scanR")
         {
            c = len;
         }
         else if (str == "radialR")
         {
            h = len;
         }
         else if (str == "gateR")
         {
            w = len;
            m_max_lenght = 250*w / 1000;

         }

   }


	awpCreateImage(&m_source, w,h,c, AWP_DOUBLE);
    double* p = (double*)m_source->pPixels;


    size_t start[3] = {0,0,0};
	size_t count[3]  = {c,h,w};
    double* data = (double*)malloc(c*h*w*sizeof(double));
    status = nc_get_vara_double(this->m_ncid, varID, start, count, data);
    if (status != NC_NOERR)
        ShowMessage("ошибка!");


    nc_inq_varid(this->m_ncid, "azimuthR", &varID);

    awpCreateImage(&m_azmuth, h, c, 1, AWP_DOUBLE);
    double* dd = (double*)m_azmuth->pPixels;
    status = nc_get_var_double(this->m_ncid, varID, dd);
    if (status != NC_NOERR)
        ShowMessage("ошибка!");

    _bSaveAWPAsDAT("azmuth.txt", m_azmuth);

    nc_inq_varid(this->m_ncid, "distanceR", &varID);
    m_dist = (double*)malloc(w*sizeof(double));
    status = nc_get_var_double(this->m_ncid, varID, m_dist);
    if (status != NC_NOERR)
        ShowMessage("ошибка!");


    nc_inq_varid(this->m_ncid, "elevationR", &varID);
    awpCreateImage(&m_elev, h, c, 1, AWP_DOUBLE);
    dd = (double*)m_elev->pPixels;
    status = nc_get_var_double(this->m_ncid, varID, dd);
    if (status != NC_NOERR)
        ShowMessage("ошибка!");

    ComboBox1->Clear();
    for (int i = 0; i < c; i++)
		ComboBox1->AddItem(FormatFloat("00.00", dd[i*m_elev->sSizeX]), NULL);

    for (int r = 0;r < w; r++)
    {
        for (int a = 0; a < h; a++)
        {
           for (int cc = 0;cc < c; cc++)
            {
                p[r*c + cc+ c*w*a] = data[cc*w*h + (r + w*a)];
            }
        }
    }

    free(data);
   
}

//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{
    ComboBox2->Clear();
    double* a = (double*)this->m_azmuth->pPixels;
    this->Series1->Clear();
    for (int i = 0; i < this->m_azmuth->sSizeX; i++)
    {
        ComboBox2->Items->Add(FormatFloat("000.00", a[ComboBox1->ItemIndex*m_azmuth->sSizeX+i]));
        this->Series1->Add(a[ComboBox1->ItemIndex*m_azmuth->sSizeX+i]);
    }
	Draw2DScene();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton3Click(TObject *Sender)
{
	 if(SaveDialog1->Execute())
     {
        AnsiString FileName = SaveDialog1->FileName;
        AnsiString strExt = ExtractFileExt(FileName);
        if (strExt == "")
        {
            switch(SaveDialog1->FilterIndex)
            {
                case 1:
                	FileName += ".png";
                break;
                case 2:
                	FileName += ".jpg";
                break;
                case 3:
                	FileName += ".awp";
                break;
            }
        }
        FImage1->SaveToFile(FileName);
     }
}
/*awpDrawThickPointByte
закрашивает окрестность точки p на изобажении, содержащем данные типа AWPBYTE*/
static AWPRESULT _awpDrawThickPointByte(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
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
static AWPRESULT _awpDrawThickPointShort(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
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
static AWPRESULT _awpDrawThickPointFloat(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
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
static AWPRESULT _awpDrawThickPointDouble(awpImage* pImage, awpPoint p, AWPBYTE bChan, AWPDOUBLE dValue, AWPBYTE radius)
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

	 r = sqrt(double((p2.X - p1.X)*(p2.X - p1.X) + (p2.Y - p1.Y)*(p2.Y - p1.Y)));


	for (t = 0; t <= distance + 1; t ++)
	{
      if (startx < pImage->sSizeX && starty < pImage->sSizeY )
      {
		p.X = startx;p.Y = starty;
		 r1 = sqrt(double((startx - p1.X)*(startx - p1.X) + (starty - p1.Y)*(starty - p1.Y)));

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

 AWPRESULT awpGetCentroid(const awpImage* pImg, awpPoint* p)
{
    AWPRESULT res;
	AWPDOUBLE sum,x0,y0;
    AWPBYTE* pix;
    AWPINT  x, y;
    AWPDWORD i;

    res = AWP_OK;
    _CHECK_RESULT_((res = awpCheckImage(pImg)))

    if(pImg->dwType!=AWP_BYTE)
    {
        res = AWP_NOTSUPPORT;
        _ERR_EXIT_
    }

    if(pImg->bChannels!=1)
    {
        res = AWP_NOTSUPPORT;
        _ERR_EXIT_
    }
	x0=0;
    y0=0;
    pix = (AWPBYTE*)pImg->pPixels;
    for ( i = 0; i < pImg->sSizeY; i++)
    {
       y = i;
       for (x = 0; x <= pImg->sSizeX; x++)
	   {
          sum += pix[y*pImg->sSizeX + x];
          x0  += x*pix[y*pImg->sSizeX + x];
          y0  += y*pix[y*pImg->sSizeX + x];
       }
    }

	p->X = (AWPSHORT)floor(x0 / (double)sum + 0.5);
	p->Y = (AWPSHORT)floor(y0 / (double)sum + 0.5);
CLEANUP:
    return res;
}

 AWPRESULT awpGetOrientation(const awpImage* pImg, AWPDOUBLE* teta, AWPDOUBLE* mi, AWPDOUBLE* ma)
{
    /*local variables*/
    AWPRESULT res;
	AWPINT  x, y, j;
    AWPDOUBLE mxx, myy, mxy, intes,s; /*cental moments*/
	AWPBYTE* pixels;
	awpPoint center;
	AWPDWORD i;
    /*init out arguments */
    *teta = 0;
    *mi   = 0;
    *ma   = 0;
    res = AWP_OK;
    /*check the arguments*/
    _CHECK_RESULT_((res = awpCheckImage(pImg)))
	if (teta == NULL || mi == NULL || ma == NULL)
    {
        res = AWP_BADARG;
        _ERR_EXIT_
	}
    /*check the capabilities*/
    if (pImg->bChannels > 1 || pImg->dwType != AWP_BYTE)
    {
        res = AWP_BADARG;
        _ERR_EXIT_
    }
	/*init local variables*/
    mxx = 0; myy = 0; mxy = 0;
	if (awpGetCentroid(pImg, &center) != AWP_OK)
	{
		res = AWP_BADARG;
		_ERR_EXIT_
	}

	/*find the moment*/
	intes = 0;
    s = 0;
	pixels = (AWPBYTE*)pImg->pPixels;
	for (i = 0; i < pImg->sSizeY; i++)
	{
		for (j = 0; j <pImg->sSizeX; j++)
		{
			x = j;
			y = i;
			intes += pixels[y*pImg->sSizeX + x];
			s++;
			mxx += (x - center.X)*(x - center.X);
			myy += (y - center.Y)*(y - center.Y);
			mxy += (x - center.X)*(y - center.Y);
		}
	}
	//intes /=s;
	mxx /= intes;
	myy /= intes;
	mxy /= intes;

	if (mxy == 0 && myy <= mxx)
	{
		*teta = -AWP_PI / 2;
		*ma = 4 * sqrt(mxx);
		*mi = 4 * sqrt(myy);
	}
	else if (mxy == 0 && myy > mxx)
	{
		*teta = 0;
		*ma = 4 * sqrt(myy);
		*mi = 4 * sqrt(mxx);
	}
	else if (myy <= mxx)
	{
		*teta = atan(-2 * mxy*myy - mxx + sqrt((myy - mxx)*(myy - mxx) + 4 * mxy*mxy));
		*ma = sqrt(8 * (myy + mxx + sqrt((myy - mxx)*(myy - mxx) + 4 * mxy*mxy)));
		*mi = sqrt(8 * (myy + mxx - sqrt((myy - mxx)*(myy - mxx) + 4 * mxy*mxy)));

	}
	else if (myy > mxx)
	{
		*teta = atan(sqrt(mxx + myy + sqrt((mxx - myy)*(mxx - myy) + 4 * mxy*mxy)) / (-2 * mxy + 0.000001));
		*ma = sqrt(8 * (myy + mxx + sqrt((myy - mxx)*(myy - mxx) + 4 * mxy*mxy)));
		*mi = sqrt(8 * (myy + mxx - sqrt((myy - mxx)*(myy - mxx) + 4 * mxy*mxy)));
	}

	*teta = 180.0*(*teta) / AWP_PI;

CLEANUP:
	return res;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::Exit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::DrawVerticalArea()
{
    //
    int step = 1;

    double* a = (double*)this->m_elev->pPixels;
    double fi = a[(m_elev->sSizeY - 1)*m_elev->sSizeX + ComboBox2->ItemIndex];
    fi *= 3.14;
    fi /= 180;

    awpImage* img = NULL;
	int l = m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght;

    int width   = l;
    int height  = l*sin(fi);

	awpCreateImage(&img, width, height, 3, AWP_BYTE);
    AWPBYTE* b = (AWPBYTE*)img->pPixels;

    double min_psi, max_psi;
    double min_r,   max_r;
    min_psi = 90;
	int idx = ComboBox2->ItemIndex >= 0 ? ComboBox2->ItemIndex : 0;
    max_psi = a[idx];
    for (int i = 0; i < m_elev->sSizeY; i++)
    {
        if (a[i*m_elev->sSizeX + idx] > max_psi)
        {
            max_psi = a[i*m_elev->sSizeX + idx];
		}
        if (a[i*m_elev->sSizeX + idx] < min_psi)
        {
            min_psi = a[i*m_elev->sSizeX + idx];
        }
    }
    int h = img->sSizeY;

    for (int y = 0; y < img->sSizeY; y++)
    {
        for (int x = 0; x < l; x++)
        {
			double r = sqrt(double(x*x + (h-y)*(h-y)));
            double psi  = 0;
            if (x == 0)
                psi = 90;
            else
            {
                psi = 180*atan((double)(h-y)/(double)x)/ 3.14;
            }

            if (psi <= min_psi || psi >= max_psi || r >= m_source->sSizeX)
            {
                b[3*y*img->sSizeX + 3*x] = 64;
                b[3*y*img->sSizeX + 3*x+1] = 64;
                b[3*y*img->sSizeX + 3*x+2] = 64;
			}
            else
            {
                b[3*y*img->sSizeX + 3*x] = 0;
            }
        }
    }

    for (int i = 0; i < l - step; i+=step)
    {
        for (int j = 1; j < m_elev->sSizeY; j++)
        {
            double fi = a[(j-1)*m_elev->sSizeX + idx];
            double fi1 = a[j*m_elev->sSizeX + idx];
            bool green = false;
            if (mpsi > fi && mpsi < fi1 && mr > i && mr < i + step)
                green = true;

            fi *= 3.14;
            fi /= 180;
            fi1 *= 3.14;
            fi1 /= 180;
            awpPoint p,p1, p2, p3;

/*
            double norm = m_dist[i]/m_dist[m_source->sSizeX-1];
            p.X = m_source->sSizeX*norm*cos(fi);
            p.Y = img->sSizeY - img->sSizeX*norm*sin(fi);

            p1.X = m_source->sSizeX*norm*cos(fi1);
            p1.Y = img->sSizeY - img->sSizeX*norm*sin(fi1);
*/

			double norm = m_dist[i]/m_dist[m_source->sSizeX-1];
            double norm1 = m_dist[i+step]/m_dist[m_source->sSizeX-1];

            p.X = m_source->sSizeX*norm*cos(fi);
            p.Y = img->sSizeY - m_source->sSizeX*norm*sin(fi);

            p1.X = m_source->sSizeX*norm*cos(fi1);
			p1.Y = img->sSizeY - m_source->sSizeX*norm*sin(fi1);

            p2.X = m_source->sSizeX*norm1*cos(fi);
            p2.Y = img->sSizeY - m_source->sSizeX*norm1*sin(fi);

            p3.X = m_source->sSizeX*norm1*cos(fi1);
            p3.Y = img->sSizeY - m_source->sSizeX*norm1*sin(fi1);



            int r_idx = i;//m_dist[i];
            int fi_idx = idx;
            int psi_idx = j;


            double* data = (double*)this->m_source->pPixels;
            double  value = data[m_source->bChannels*(fi_idx*m_source->sSizeX + r_idx) + psi_idx];

            double  value1 = data[m_source->bChannels*(fi_idx*m_source->sSizeX + r_idx) + psi_idx -1];

            if (!green)
            {
//                awpDrawCEllipse(img, p, 1, 1, 0, 128, 128, 128, 2);
//                awpDrawCEllipse(img, p1, 1, 1, 0, 128, 128, 128, 2);
//                awpDrawCEllipse(img, p2, 1, 1, 0, 128, 128, 128, 2);
//                awpDrawCEllipse(img, p3, 1, 1, 0, 128, 128, 128, 2);
			}
            else
            {
                awpDrawCEllipse(img, p,  4, 4, 0, 0, 255, 0, 2);
                awpDrawCEllipse(img, p1, 4, 4, 0, 0, 255, 0, 2);
                awpDrawCEllipse(img, p2, 4, 4, 0, 0, 255, 0, 2);
                awpDrawCEllipse(img, p3, 4, 4, 0, 0, 255, 0, 2);
			}

            if (value < -32)
                  value = -32;
              //if (value > 97)
              //    value = 97;

              value += 32;
              value *=1.9;

            if (value1 < -32)
                  value1 = -32;
              //if (value > 97)
              //    value = 97;

              value1 += 32;
              value1 *=1.9;

            if (value < 32)
            {
                  _awpDrawThickLine(img, p,p1, 2, 0, 200,200);
            }
            else if (value > 63)
            {
                  _awpDrawThickLine(img, p,p1, 1, 0, value,value1);
            }
			else
               _awpDrawThickLine(img, p,p1, 0, 0, 64,64);

            //b[p.Y*3*img->sSizeX + 3*p.X + 2] = value;

        }
    }

    if (this->m_2DOptions.smooth)
        awpGaussianBlur(img, img, 1.5);

	FImage1->Bitmap->SetAWPImage(img);
    FImage1->BestFit();
    awpReleaseImage(&img);
}


// перевод из полярных координат в декартовы исходной матрицы

void __fastcall TForm2::DrawSource(int channel)
{
    awpImage* tmp = NULL;
    awpGetChannel(m_source,  &tmp, channel);
    awpConvert(tmp, AWP_CONVERT_TO_BYTE_WITH_NORM);
    FImage1->Bitmap->SetAWPImage(tmp);
    FImage1->BestFit();
    awpReleaseImage(&tmp);
}
void __fastcall TForm2::DrawSourceCone(int channel)
{

      awpImage* tmp = NULL;

	  awpGetChannel(m_source,  &tmp, channel);
      awpConvert(tmp, AWP_CONVERT_TO_BYTE_WITH_NORM);
      AWPBYTE* bb = (AWPBYTE*)tmp->pPixels;
      //
	  int width = 2*m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght ;
      int height = width;
      awpImage* polar = NULL;

	  awpCreateImage(&polar, width, width, 1, AWP_BYTE);
      AWPBYTE* b = (AWPBYTE*)polar->pPixels;

      double* a = (double*)m_azmuth->pPixels;
      a +=  ComboBox1->ItemIndex*m_azmuth->sSizeX;

      for (int i = 0; i < tmp->sSizeY; i+= this->m_2DOptions.step_fi)
      {
		for (int j = 0; j < tmp->sSizeX*this->m_2DOptions.dist_x / m_max_lenght; j+= this->m_2DOptions.step_ro)
        {
            int x =  width / 2 + j*cos(3.14*a[i]/180);
            int y =  width / 2 + j*sin(3.14*a[i]/180);
            b[y*width + x] = bb[i*tmp->sSizeX + j];
        }
      }

        FImage1->Bitmap->SetAWPImage(polar);
        FImage1->BestFit();

      _AWP_SAFE_RELEASE_(polar);
      _AWP_SAFE_RELEASE_(tmp);
}

void __fastcall TForm2::MakeSourceCone3D()
{
	  if (m_source == NULL)
        return;
      if (this->m_3DPoints != NULL)
      {
        free(m_3DPoints);
        m_3DPoints = NULL;
      }

      int num = 0;

      double* aa = (double*)this->m_elev->pPixels;
      double*s = (double*)m_source->pPixels;

      //
      int width = 2*m_source->sSizeX;
      int height = width;

      double* a = (double*)m_azmuth->pPixels;
      a +=  ComboBox1->ItemIndex*m_azmuth->sSizeX;
      T3DPoint p;
      for (int k = 0; k <  m_source->bChannels; k++)
      {
        for (int i = 0; i < m_source->sSizeY; i+=this->m_2DOptions.step_fi)
        {
		  for (int j = 0; j < m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght; j+= this->m_2DOptions.step_ro)
          {

              double fi = aa[k*m_elev->sSizeX + i];
              fi *= 3.14;
              fi /= 180;

              int x =   j*cos(3.14*a[i + m_azmuth->sSizeX*k]/180);
              int y =   j*sin(3.14*a[i + m_azmuth->sSizeX*k]/180);

			  p.x = (double)x / (this->m_2DOptions.dist_x / m_max_lenght*width/2);
			  p.y = (double)y / (this->m_2DOptions.dist_x / m_max_lenght*width/2);
              double d =  sqrt(p.x*p.x + p.y*p.y);
              p.z = (-1 + 10*d*sin(fi));
              double value = s[i*m_source->sSizeX*m_source->bChannels + j*m_source->bChannels + k];

			if (value < -32)
                  value = -32;

              value += 32;
              value *=1.9;


              if (value < 32)
                num++;
          }
        }
      }

    if (num == 0)
        return;

    m_3DPoints = (T3DPoint*)malloc(num*sizeof(T3DPoint));

    num = 0;
    for (int k = 0; k <  m_source->bChannels; k++)
    {
      for (int i = 0; i < m_source->sSizeY; i+=this->m_2DOptions.step_fi)
      {
        for (int j = 0; j < m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght; j+=this->m_2DOptions.step_ro)
        {

			double fi = aa[k*m_elev->sSizeX + i];
            fi *= 3.14;
            fi /= 180;

            int x =   j*cos(3.14*a[i + m_azmuth->sSizeX*k]/180);
            int y =   j*sin(3.14*a[i + m_azmuth->sSizeX*k]/180);

			p.x = (double)x / (this->m_2DOptions.dist_x / m_max_lenght*width/2);
            p.y = (double)y / (this->m_2DOptions.dist_x / m_max_lenght*width/2);
            double d =  sqrt(p.x*p.x + p.y*p.y);
            p.z = (-1 + 10*d*sin(fi));
            double value = s[i*m_source->sSizeX*m_source->bChannels + j*m_source->bChannels + k];

          if (value < -32)
                value = -32;

            value += 32;
            value *=1.9;


            if (value < 32)
            {
              m_3DPoints[num] = p;
              num++;
            }
        }
      }
    }

     m_num3DPoints = num;
}
void __fastcall TForm2::DrawInterCone3D(TCanvas* cnv)
{
	  if (m_source == NULL)
        return;
        MakeSourceCone3D();
      if (this->m_3DContours == NULL || this->m_num3DContours == 0)
        return;

            TColor c =  Canvas->Brush->Color;
			cnv->Brush->Color = (TColor)RGB(255, 0, 0);
            cnv->Pen->Color = cnv->Brush->Color;

      for (int i = 0; i < m_num3DContours; i++)
      {
           TPoint p1 = t.GetProjection(m_3DContours[i].pts[1]);
           cnv->MoveTo(p1.x, p1.y);
           for (int j = 2; j < m_3DContours[i].num-2; j++)
           {
            TPoint p2;
            p2 = t.GetProjection(m_3DContours[i].pts[j]);
            cnv->LineTo(p2.x, p2.y);
           }
      }
      Canvas->Brush->Color;

}

void __fastcall TForm2::DrawSourceCone3D(TCanvas* cnv)
{
      if (m_source == NULL)
        return;
      if (m_3DPoints == NULL || m_num3DPoints == 0)
        return;
      for (int i = 0; i < m_num3DPoints; i++)
      {
		 Draw3DPoint(cnv, m_3DPoints[i]);
      }

      return;


      double* aa = (double*)this->m_elev->pPixels;
	  double*s = (double*)m_source->pPixels;

      //
      int width = 2*m_source->sSizeX;
      int height = width;

      double* a = (double*)m_azmuth->pPixels;
      a +=  ComboBox1->ItemIndex*m_azmuth->sSizeX;
      T3DPoint p;
      for (int k = 0; k <  m_source->bChannels; k++)
      {
        for (int i = 0; i < m_source->sSizeY; i+=1)
        {
          for (int j = 0; j < m_source->sSizeX / 4; j+=2)
          {

              double fi = aa[k*m_elev->sSizeX + i];
              fi *= 3.14;
              fi /= 180;

              int x =   j*cos(3.14*a[i + m_azmuth->sSizeX*k]/180);
              int y =   j*sin(3.14*a[i + m_azmuth->sSizeX*k]/180);

              p.x = (double)x / (0.1*width);
              p.y = (double)y / (0.1*width);
              double d =  sqrt(p.x*p.x + p.y*p.y);
			  p.z = (-1 + 5*d*sin(fi));
              double value = s[i*m_source->sSizeX*m_source->bChannels + j*m_source->bChannels + k];

            if (value < -32)
                  value = -32;
              //if (value > 97)
              //    value = 97;

              value += 32;
              value *=1.9;


              if (value < 32)
                  Draw3DPoint(cnv, p);

          }
        }

      }

}
awpImage* TForm2::GetInterCone(int index)
{

    if (m_source == NULL)
		return NULL;

    awpImage* tmp = NULL;
    if (awpGetChannel(m_source,  &tmp, index) != AWP_OK)
        return NULL;
    double* a = (double*)m_azmuth->pPixels;
    double* t = (double*)tmp->pPixels;
    awpImage* res = NULL;
	int idx  = index;
    double len = m_source->sSizeX;
    int len1   = m_source->sSizeX-1;
	awpCreateImage(&res, 2*m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght, 2*m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght, 1, AWP_DOUBLE);
    double* r  = (double*)res->pPixels;

    awpPoint p1,p2,p3,p4, c[5];
	awpRect rect;

    awpContour contour;
    contour.NumPoints = 5;
    contour.Direction = true;
    contour.Points = c;
	int l = m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght;
    len1 = l;
    for (int i = 0; i < m_azmuth->sSizeX-1; i++ )
    {
        for (int j = 0; j < l; j++)
        {
            c[0].X = floor(len1 + len1*(m_dist[j] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);
            c[0].Y = floor(len1 + len1*(m_dist[j] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);

            c[1].X = floor(len1 + len1*(m_dist[j] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX + 1]/180) + 0.5);
            c[1].Y = floor(len1 + len1*(m_dist[j] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX +1]/180) + 0.5);

            c[2].X = floor(len1 + len1*(m_dist[j+1] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX+1]/180) + 0.5);
            c[2].Y = floor(len1 + len1*(m_dist[j+1] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX+1]/180) + 0.5);

            c[3].X = floor(len1 + len1*(m_dist[j+1] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX ]/180) + 0.5);
            c[3].Y = floor(len1 + len1*(m_dist[j+1] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);
            c[4] = c[0];

            awpGetContourRect(&contour, &rect);
			double v1, v2, v3, v4, v5, v6, v;

            v1 = t[j+ i*tmp->sSizeX];
            r[2*c[0].Y*(l) + c[0].X] = v1;
            v2 = t[j+ (i+1)*tmp->sSizeX];
            v3 = t[(j+1)+ (i+1)*tmp->sSizeX];
            v4 = t[(j+1)+ i*tmp->sSizeX];

            if (v1 == v2 && v1 == v3 && v1 == v4)
                continue;

            ///awpDrawPolygon(res, &contour, 0, 100, 0);

            double l1,l2;
			l1 = 1+sqrt(double((c[1].X - c[0].X)*(c[1].X - c[0].X) + (c[1].Y - c[0].Y)*(c[1].Y - c[0].Y)));
			l2 = 1+sqrt(double((c[3].X - c[2].X)*(c[3].X - c[2].X) + (c[3].Y - c[2].Y)*(c[3].Y - c[2].Y)));


            // нахождение minx и maxx
            awpPoint pp;
			for (int yy = rect.top; yy <= rect.bottom; yy++)
			{
                pp.Y = yy;
                for (int xx = rect.left; xx <= rect.right; xx++)
                {
                  pp.X = xx;
                  AWPBOOL result = false;
				  awpIsPointInContour(&contour, &pp, &result);
                  if (result == true)
                  {
                     double r1,r2, r3 , r4 , r5;
					 r1 = sqrt(double((xx - c[0].X)*(xx - c[0].X)+(yy - c[0].Y)*(yy - c[0].Y)));
					 r2 = sqrt(double((xx - c[1].X)*(xx - c[1].X)+(yy - c[1].Y)*(yy - c[1].Y)));

                     r3 = (l1*l1 + r1*r1 - r2*r2) / (2*l1);

					 r1 = sqrt(double((xx - c[2].X)*(xx - c[2].X)+(yy - c[2].Y)*(yy - c[2].Y)));
					 r2 = sqrt(double((xx - c[3].X)*(xx - c[3].X)+(yy - c[3].Y)*(yy - c[3].Y)));

                     r4 = (l2*l2+r1*r1 - r2*r2) / (2*l2);

					 r1 = sqrt(double((xx - c[0].X)*(xx - c[0].X)+(yy - c[0].Y)*(yy - c[0].Y)));
					 if (r1*r1 - r3*r3 >= 0 )
						 r5 = sqrt(double(r1*r1 - r3*r3 ));
                     else
                         r5 = 0;
                     // интерполяция.
                     v5 = r3*(v2 - v1) / l1 + v1;
                     v6 = r4*(v4 - v3) / l2 + v3;
                     v  =  v5 + r5*(v6 - v5) / l1;
                     r[2*yy*l + xx] = v;
                  }
                }
            }
        }
    }

    for (int i = 0; i < res->sSizeX*res->sSizeY; i++)
    {
        if (r[i] < -32)
            r[i] = -32;
        if (r[i] > 97)
            r[i] = 97;

        r[i] += 32;
        r[i] *=1.9;
	}
   _AWP_SAFE_RELEASE_(tmp);
    return res;
}

void __fastcall TForm2::DrawSourceConeInter(int channel)
{
	if (m_source == NULL || channel < 0)
        return;

    awpImage* tmp = NULL;//GetInterCone(channel);

	awpGetChannel(m_source,  &tmp, channel);
    double* a = (double*)m_azmuth->pPixels;
    double* t = (double*)tmp->pPixels;
    awpImage* res = NULL;
    int idx  = ComboBox1->ItemIndex;
    double len = m_source->sSizeX;
	int len1   = m_source->sSizeX-1;
	awpCreateImage(&res, 2*m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght, 2*m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght, 1, AWP_DOUBLE);
	double* r  = (double*)res->pPixels;

    awpPoint p1,p2,p3,p4, c[5];
    awpRect rect;

    awpContour contour;
    contour.NumPoints = 5;
    contour.Direction = true;
    contour.Points = c;
    int l = m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght;
    len1 = l;
    for (int i = 0; i < m_azmuth->sSizeX-1; i++ )
    {
		for (int j = 0; j < l; j++)
		{
			//int x,y,x1,y1,x3,y3,x4,y4;  //
			c[0].X = floor(len1 + len1*(m_dist[j] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);
            c[0].Y = floor(len1 + len1*(m_dist[j] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);

            c[1].X = floor(len1 + len1*(m_dist[j] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX + 1]/180) + 0.5);
			c[1].Y = floor(len1 + len1*(m_dist[j] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX +1]/180) + 0.5);

            c[2].X = floor(len1 + len1*(m_dist[j+1] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX+1]/180) + 0.5);
            c[2].Y = floor(len1 + len1*(m_dist[j+1] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX+1]/180) + 0.5);

            c[3].X = floor(len1 + len1*(m_dist[j+1] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX ]/180) + 0.5);
            c[3].Y = floor(len1 + len1*(m_dist[j+1] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);
			c[4] = c[0];
		   //	if (c[0].X<=256)
			 //	continue;

			awpGetContourRect(&contour, &rect);
			double v1, v2, v3, v4, v5, v6, v;

            v1 = t[j+ i*tmp->sSizeX];
            r[2*c[0].Y*(l) + c[0].X] = v1;
            v2 = t[j+ (i+1)*tmp->sSizeX];
            v3 = t[(j+1)+ (i+1)*tmp->sSizeX];
            v4 = t[(j+1)+ i*tmp->sSizeX];

            if (v1 == v2 && v1 == v3 && v1 == v4)
                continue;

               //    awpDrawPolygon(res, &contour, 0, 100, 0);

			double l1,l2;
			l1 = 1+sqrt(double((c[1].X - c[0].X)*(c[1].X - c[0].X) + (c[1].Y - c[0].Y)*(c[1].Y - c[0].Y)));
			l2 = 1+sqrt(double((c[3].X - c[2].X)*(c[3].X - c[2].X) + (c[3].Y - c[2].Y)*(c[3].Y - c[2].Y)));


            // нахождение minx и maxx
            awpPoint pp;
            for (int yy = rect.top; yy <= rect.bottom; yy++)
			{
                pp.Y = yy;
                for (int xx = rect.left; xx <= rect.right; xx++)
                {
                  pp.X = xx;
                  AWPBOOL result = false;
                  awpIsPointInContour(&contour, &pp, &result);
                  if (result == true)
                  {
                     double r1,r2, r3 , r4 , r5;
					 r1 = sqrt(double((xx - c[0].X)*(xx - c[0].X)+(yy - c[0].Y)*(yy - c[0].Y)));
					 r2 = sqrt(double((xx - c[1].X)*(xx - c[1].X)+(yy - c[1].Y)*(yy - c[1].Y)));

                     r3 = (l1*l1 + r1*r1 - r2*r2) / (2*l1);

					 r1 = sqrt(double((xx - c[2].X)*(xx - c[2].X)+(yy - c[2].Y)*(yy - c[2].Y)));
					 r2 = sqrt(double((xx - c[3].X)*(xx - c[3].X)+(yy - c[3].Y)*(yy - c[3].Y)));

                     r4 = (l2*l2+r1*r1 - r2*r2) / (2*l2);

					 r1 = sqrt(double((xx - c[0].X)*(xx - c[0].X)+(yy - c[0].Y)*(yy - c[0].Y)));
                     if (r1*r1 - r3*r3 >= 0 )
						 r5 = sqrt(double(r1*r1 - r3*r3 ));
                     else
                         r5 = 0;
                     // интерполяция.
					 v5 = r3*(v2 - v1) / l1 + v1;
                     v6 = r4*(v4 - v3) / l2 + v3;
                     v  =  v5 + r5*(v6 - v5) / l1;
                     r[2*yy*l + xx] = v;
                  }
                  else
                  {
					//r[2*yy*1832 + xx] = -32;
                  }
                }
            }


            awpPoint p1,p2;
            p1.X = c[0].X;
            p2.X = c[1].X;
            p1.Y = c[0].Y;
            p2.Y = c[1].Y;
        }
    }

    for (int i = 0; i < res->sSizeX*res->sSizeY; i++)
    {
        if (r[i] < -32)
            r[i] = -32;
        if (r[i] > 97)
            r[i] = 97;

        r[i] += 32;
        r[i] *=1.9;
    }

    awpImage* res1 = NULL;
	awpCreateImage(&res1, res->sSizeX, res->sSizeY, 3, AWP_BYTE);
    AWPBYTE* bres1 = (AWPBYTE*)res1->pPixels;
    for (int i = 0; i < res->sSizeX*res->sSizeY; i++)
    {
        if (r[i] < 60.8)
        {
            bres1[3*i] = 0;
			bres1[3*i+1] = 0;
            bres1[3*i+2] = 255;
        }
        else  if (r[i] > 60.8)
        {
            bres1[3*i] = 0;
            bres1[3*i+1] = r[i];
            bres1[3*i+2] = 0;
        }
        else
        {
            bres1[3*i] = 64;
            bres1[3*i+1] = 0;
            bres1[3*i+2] = 0;
        }

    }

    awpConvert(res, AWP_CONVERT_TO_BYTE);
    if (this->m_2DOptions.smooth)
    {
        awpGaussianBlur(res, res, 1.5);
        awpGaussianBlur(res1, res1, 1.5);
    }
    if (this->m_2DOptions.contours)
    {
		//
        AWPBYTE* pix = (AWPBYTE*)res->pPixels;
        for (int i = 0; i < res->sSizeX*res->sSizeY; i++)
		{
            pix[i] = 255- pix[i];
        }
        int num = 0;
		awpStrokeObj* obj = NULL;
        awpGetStrokes(res, &num, &obj, 250, NULL);//порог бинаризации (250)
        for (int i = 0; i < num; i++)
        {
            awpRect rect;
            awpCalcObjRect(&obj[i], &rect);
            int w = rect.right - rect.left;
            int h = rect.bottom - rect.top;
            if (w*h > 128)
            {
                awpContour* c = NULL;
                 awpCreateContour(&c, obj[i].Num*2, true);
                awpGetObjCountour(&obj[i], c);
                if (c == NULL)
                    continue;
                for (int k = 0; k < c->NumPoints-1; k++)
                {
                    awpPoint p1,p2;
                    p1.X = c->Points[k].X;
                    p2.X = c->Points[k+1].X;
                    p1.Y = c->Points[k].Y;
                    p2.Y = c->Points[k+1].Y;
                    awpDrawCLine(res1, p1, p2, 255, 255, 255, 1);
                }
                awpFreeContour(&c);
            }
		}
        awpFreeStrokes(num, &obj);


    }
    DrawFlashes1(res1);
	FImage1->Bitmap->SetAWPImage(res1);
	FImage1->BestFit();


   _AWP_SAFE_RELEASE_(tmp);
   _AWP_SAFE_RELEASE_(res);
   _AWP_SAFE_RELEASE_(res1);
}



void __fastcall TForm2::FormResize(TObject *Sender)
{
    FImage1->BestFit();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox2Change(TObject *Sender)
{
    this->FastLineSeries1->Clear();
    ComboBox1->Clear();
    double* a = (double*)this->m_elev->pPixels;
    for (int i = 0; i < this->m_azmuth->sSizeY; i++)
    {
        this->FastLineSeries1->Add(a[i*m_elev->sSizeX + ComboBox2->ItemIndex]);
        ComboBox1->Items->Add(FormatFloat("000.00", a[i*m_elev->sSizeX + ComboBox2->ItemIndex]));
    }
	ComboBox1->ItemIndex = 0;
    Draw2DScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FImage1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if (m_dist == NULL)
        return;
    int x,y, h, r;
	double dist, psi;

    x = FImage1->GetImageX(X);
    y = FImage1->GetImageY(Y);
    h = FImage1->Bitmap->Height;


	if (m_2DViewOptions == eSourceCone || m_2DViewOptions == eIntepolatedCone ||
     m_2DViewOptions == eInterpolatedHorizontal || m_2DViewOptions == eResultCell)
    {
		int r = (int)sqrt(double(x*x + (h-y)*(h-y)));
        dist = this->m_dist[r];
        psi  = 0;
		if (x == 0)
            psi = 90;
        else
            psi = 180*atan((double)(h-y)/(double)x)/ 3.14;
    }
	StatusBar1->Panels->Items[0]->Text = "x = " + IntToStr(x) + " y = " + IntToStr(y) + " r = " + FormatFloat(".000", dist/1000) + " psi = " + FormatFloat(".00", psi);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	this->m_mdown = true;
	m_dx = X;
	m_dy = Y;
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Draw3DPoint(TCanvas* cnv, T3DPoint& p)
{
		TPoint p1;
		p1 = t.GetProjection(p);
        TColor c =  Canvas->Brush->Color;
        cnv->Brush->Color = (TColor)RGB(255, 0, 0);
        cnv->Pen->Color = cnv->Brush->Color;
        int r = 1;
        cnv->Ellipse(p1.x - r, p1.y - r, p1.x + r, p1.y + r );
        Canvas->Brush->Color;
}

void __fastcall TForm2::Draw2DScene()
{
    switch (m_2DViewOptions)
    {
        case eSourceData:
			DrawSource(ComboBox1->ItemIndex);
        break;
        case eSourceCone:
            DrawSourceCone(ComboBox1->ItemIndex);
        break;
		case eIntepolatedCone:
            DrawSourceConeInter(ComboBox1->ItemIndex);
        break;
        case eSourceVirtical:
            //DrawVerticalArea();
        break;
        case eInterpolatedVertical:
			//DrawVerticalArea();
 //           MakeSourceCone3D();
 //           DrawSourceCone3D(FImage1->Canvas);

     MakeSourceCone3D();
    DrawScene();
        break;
        case eInterpolatedHorizontal:
           InterHorizontalActionExecute(NULL);
        break;
        case eResultCell:
            DrawResultCells();
            FImageResult(VecList, MapList);
            DrawResult(MapList);
        break;
    }
}
typedef struct palEntry
{
	double r;
	double g;
	double b;
}pe;

const palEntry HeatmapPal[128] =
{
	{0.0,	0.0,	74.0},
	{ 0.0,	0.0,	78.0 },
	{ 0.0,	0.0,	78.0 },
	{ 0.0,	0.0,	78.0 },
	{ 0.0,	0.0,	82.0 },
	{ 0.0,	0.0,	86.0 },
	{ 0.0,	0.0,	90.0 },
	{ 0.0,	0.0,	94.0 },
	{ 0.0,	0.0,	98.0 },
	{ 0.0,	0.0,	102.0 },
	{ 0.0,	0.0,	106.0 },
	{ 0.0,	0.0,	110.0 },
	{ 0.0,	0.0,	114.0 },
	{ 0.0,	0.0,	118.0 },
	{ 0.0,	0.0,	122.0 },
	{ 0.0,	0.0,	126.0 },
	{ 0.0,	2.0,	128.0 },
	{ 0.0,	6.0,	128.0 },
	{ 0.0,	10.0,	128.0 },
	{ 0.0,	14.0,	128.0 },
	{ 0.0,	18.0,	128.0 },
	{ 0.0,	22.0,	128.0 },
	{ 0.0,	26.0,	128.0 },
	{ 0.0,	30.0,	128.0 },
	{ 0.0,	34.0,	128.0 },
	{ 0.0,	38.0,	128.0 },
	{ 0.0,	42.0,	128.0 },
	{ 0.0,	46.0,	128.0 },
	{ 0.0,	50.0,	128.0 },
	{ 0.0,	54.0,	128.0 },
	{ 0.0,	58.0,	128.0 },
	{ 0.0,	62.0,	128.0 },
	{ 0.0,	66.0,	128.0 },
	{ 0.0,	70.0,	128.0 },
	{ 0.0,	74.0,	128.0 },
	{ 0.0,	78.0,	128.0 },
	{ 0.0,	82.0,	128.0 },
	{ 0.0,	86.0,	128.0 },
	{ 0.0,	90.0,	128.0 },
	{ 0.0,	94.0,	128.0 },
	{ 0.0,	98.0,	128.0 },
	{ 0.0,	102.0,	128.0 },
	{ 0.0,	106.0,	128.0 },
	{ 0.0,	110.0,	128.0 },
	{ 0.0,	114.0,	128.0 },
	{ 0.0,	118.0,	128.0 },
	{ 0.0,	122.0,	128.0 },
	{ 0.0,	126.0,	128.0 },
	{ 2.0,	128.0,	126.0 },
	{ 6.0,	128.0,	122.0 },
	{ 10.0,	128.0,	118.0 },
	{ 14.0,	128.0,	114.0 },
	{ 18.0,	128.0,	110.0 },
	{ 22.0,	128.0,	106.0 },
	{ 26.0,	128.0,	102.0 },
	{ 30.0,	128.0,	98.0 },
	{ 34.0,	128.0,	94.0 },
	{ 38.0,	128.0,	90.0 },
	{ 42.0,	128.0,	86.0 },
	{ 46.0,	128.0,	82.0 },
	{ 50.0,	128.0,	78.0 },
	{ 54.0,	128.0,	74.0 },
	{ 58.0,	128.0,	70.0 },
	{ 62.0,	128.0,	66.0 },
	{ 66.0,	128.0,	62.0 },
	{ 70.0,	128.0,	58.0 },
	{ 74.0,	128.0,	54.0 },
	{ 78.0,	128.0,	50.0 },
	{ 82.0,	128.0,	46.0 },
	{ 86.0,	128.0,	42.0 },
	{ 90.0,	128.0,	38.0 },
	{ 94.0,	128.0,	34.0 },
	{ 98.0,	128.0,	30.0 },
	{ 102.0,	128.0,	26.0 },
	{ 106.0,	128.0,	22.0 },
	{ 110.0,	128.0,	18.0 },
	{ 114.0,	128.0,	14.0 },
	{ 118.0,	128.0,	10.0 },
	{ 122.0,	128.0,	6.0 },
	{ 126.0,	128.0,	2.0 },
	{ 128.0,	126.0,	0.0 },
	{ 128.0,	122.0,	0.0 },
	{ 128.0,	118.0,	0.0 },
	{ 128.0,	114.0,	0.0 },
	{ 128.0,	110.0,	0.0 },
	{ 128.0,	106.0,	0.0 },
	{ 128.0,	102.0,	0.0 },
	{ 128.0,	98.0,	0.0 },
	{ 128.0,	94.0,	0.0 },
	{ 128.0,	90.0,	0.0 },
	{ 128.0,	86.0,	0.0 },
	{ 128.0,	82.0,	0.0 },
	{ 128.0,	78.0,	0.0 },
	{ 128.0,	74.0,	0.0 },
	{ 128.0,	70.0,	0.0 },
	{ 128.0,	66.0,	0.0 },
	{ 128.0,	62.0,	0.0 },
	{ 128.0,	58.0,	0.0 },
	{ 128.0,	54.0,	0.0 },
	{ 128.0,	50.0,	0.0 },
	{ 128.0,	46.0,	0.0 },
	{ 128.0,	42.0,	0.0 },
	{ 128.0,	38.0,	0.0 },
	{ 128.0,	34.0,	0.0 },
	{ 128.0,	30.0,	0.0 },
	{ 128.0,	26.0,	0.0 },
	{ 128.0,	22.0,	0.0 },
	{ 128.0,	18.0,	0.0 },
	{ 128.0,	14.0,	0.0 },
	{ 128.0,	10.0,	0.0 },
	{ 128.0,	6.0,	0.0 },
	{ 128.0,	2.0,	0.0 },
	{ 126.0,	0.0,	0.0 },
	{ 122.0,	0.0,	0.0 },
	{ 118.0,	0.0,	0.0 },
	{ 114.0,	0.0,	0.0 },
	{ 110.0,	0.0,	0.0 },
	{ 106.0,	0.0,	0.0 },
	{ 102.0,	0.0,	0.0 },
	{ 98.0,	0.0,	0.0 },
	{ 94.0,	0.0,	0.0 },
	{ 90.0,	0.0,	0.0 },
	{ 86.0,	0.0,	0.0 },
	{ 82.0,	0.0,	0.0 },
	{ 78.0,	0.0,	0.0 },
	{ 74.0,	0.0,	0.0 },
	{ 70.0,	0.0,	0.0 },
	{ 66.0,	0.0,	0.0 }
};


void __fastcall TForm2::DrawResultCells()
{
    awpImage* img = GetInterCone(0);
    AWPDOUBLE* pix = (AWPDOUBLE*)img->pPixels;

    for (int i = 0; i < img->sSizeX*img->sSizeY; i++)
    {
      if (pix[i] < 60.8)
          pix[i] = 1;
      else
		  pix[i] = 0;
    }
    for (int i = 1; i < 4; i++)
    {
        awpImage* cone = GetInterCone(i);
        if (cone == NULL)
            continue;

        AWPDOUBLE* pix1 = (AWPDOUBLE*)cone->pPixels;
        for (int j = 0; j < cone->sSizeX*cone->sSizeY; j++)
            pix[j] += pix1[j] < 60.8 ? 1 : 0;

        _AWP_SAFE_RELEASE_(cone);
    }
    awpConvert(img, AWP_CONVERT_TO_BYTE_WITH_NORM);
    awpImage* img1 = NULL;
    awpCopyImage(img, &img1);
    awpGaussianBlur(img, img1, 1.5);

    awpImage* img2 = NULL;
    awpCreateImage(&img2, img1->sSizeX, img1->sSizeY, 3, AWP_BYTE);
    AWPBYTE* bb1 = (AWPBYTE*)img1->pPixels;
    AWPBYTE* bb2 = (AWPBYTE*)img2->pPixels;

	if (OptionsDlg->RadioGroup1->ItemIndex==0)
    {
      for (int j = 0; j < img1->sSizeX*img1->sSizeY; j++)
      {
          bb2[3*j] = HeatmapPal[bb1[j]/2].b;
          bb2[3*j+1] = HeatmapPal[bb1[j]/2].g;
          bb2[3*j+2] = HeatmapPal[bb1[j]/2].r;
      }
    }
	else
    {
      for (int j = 0; j < img1->sSizeX*img1->sSizeY; j++)
        {
            bb2[3*j] = bb1[j];
            bb2[3*j+1] = bb1[j];
            bb2[3*j+2] = bb1[j];
        }
    }
    // поиск объектов.
    FindObjects(img1, img2);

    FImage1->Bitmap->SetAWPImage(img2);
    FImage1->BestFit();
    _AWP_SAFE_RELEASE_(img);
    _AWP_SAFE_RELEASE_(img1);
    _AWP_SAFE_RELEASE_(img2);

}


void __fastcall TForm2::SourceViewActionExecute(TObject *Sender)
{
    m_2DViewOptions = eSourceData;
	Draw2DScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SourceConeViewActionExecute(TObject *Sender)
{
    m_2DViewOptions = eSourceCone;
    Draw2DScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SourceConeViewActionUpdate(TObject *Sender)
{
//
    SourceConeViewAction->Checked = m_2DViewOptions == eSourceCone;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SourceViewActionUpdate(TObject *Sender)
{
    SourceViewAction->Checked = m_2DViewOptions == eSourceData;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::InterConeActionExecute(TObject *Sender)
{
	m_2DViewOptions = eIntepolatedCone;
	Draw2DScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::InterConeActionUpdate(TObject *Sender)
{
	InterConeAction->Checked = m_2DViewOptions == eIntepolatedCone;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SourceVerticalActionExecute(TObject *Sender)
{
    m_2DViewOptions = eSourceVirtical;
	Draw2DScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SourceVerticalActionUpdate(TObject *Sender)
{
//
    SourceVerticalAction->Checked = m_2DViewOptions == eSourceVirtical;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::InterVerticalActionExecute(TObject *Sender)
{
    m_2DViewOptions = eInterpolatedVertical;
	Draw2DScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::InterVerticalActionUpdate(TObject *Sender)
{
    InterVerticalAction->Checked =  m_2DViewOptions == eInterpolatedVertical;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Panel1Resize(TObject *Sender)
{
  //  Draw2DScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::OptionsActionExecute(TObject *Sender)
{
  // setup DLG
  OptionsDlg->CSpinEdit1->Value = m_2DOptions.dist_x;
  OptionsDlg->CSpinEdit4->Value = m_2DOptions.step_ro;
  OptionsDlg->CSpinEdit5->Value = m_2DOptions.step_fi;
  OptionsDlg->CheckBox1->Checked = m_2DOptions.smooth;
  OptionsDlg->CheckBox2->Checked = m_2DOptions.contours;

  OptionsDlg->CSpinEdit2->Value =  m_planeOptions.imageWidth;
  OptionsDlg->CSpinEdit6->Value =  m_planeOptions.Height;
  OptionsDlg->CSpinEdit7->Value =  m_planeOptions.Distance;
/*
	m_planeOptions.imageWidth = 512;
    m_planeOptions.Height = 3000;
	m_planeOptions.Distance = 150;
*/

  if (OptionsDlg->ShowModal() == mrOk)
  {
       m_2DOptions.dist_x = OptionsDlg->CSpinEdit1->Value;
       m_2DOptions.step_ro = OptionsDlg->CSpinEdit4->Value;
       m_2DOptions.step_fi = OptionsDlg->CSpinEdit5->Value;
       m_2DOptions.smooth = OptionsDlg->CheckBox1->Checked;
	   m_2DOptions.contours = OptionsDlg->CheckBox2->Checked;

	   m_planeOptions.imageWidth = OptionsDlg->CSpinEdit2->Value;
       m_planeOptions.Height = OptionsDlg->CSpinEdit6->Value;
	   m_planeOptions.Distance = OptionsDlg->CSpinEdit7->Value;

	   this->Draw2DScene();
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Source3dViewActionExecute(TObject *Sender)
{
//
    this->m_3DViewOptions = e3dSourceData;
   // MakeSourceCone3D();
   //DrawScene();
}

void __fastcall TForm2::DrawScene()
{
	Graphics::TBitmap* bmp = new Graphics::TBitmap();
	bmp->Width = ClientWidth;
	bmp->Height= ClientHeight;

	TCanvas* cnv = bmp->Canvas;
	TRect rect;  rect.left = 0; rect.top = 0;
    rect.Bottom = ClientHeight;
    rect.right =  ClientWidth;

	cnv->Brush->Color = clBlack;
	cnv->FillRect(rect);

	TCube cube(&t);
 	cube.Draw(cnv);
    switch(m_3DViewOptions)
    {
		case e3dSourceData:
            DrawSourceCone3D(cnv);
        break;

        case e3dConeContours:
            DrawInterCone3D(cnv);
        break;
    }


	FImage1->Canvas->Draw(0,0,bmp);
	delete bmp;

}


//---------------------------------------------------------------------------

void __fastcall TForm2::Source3dViewActionUpdate(TObject *Sender)
{
    Source3dViewAction->Checked =   this->m_3DViewOptions == e3dSourceData;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::HContours3dViewActionExecute(TObject *Sender)
{
    this->m_3DViewOptions = e3dConeContours;
  //  this->MakeInterCone3D();
  //  DrawScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::HContours3dViewActionUpdate(TObject *Sender)
{
    HContours3dViewAction->Checked = this->m_3DViewOptions == e3dConeContours;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::MakeInterCone3D()
{
    if (m_source == NULL)
        return;

      if (this->m_3DContours != NULL)
      {
          for (int i = 0; i < m_num3DContours; i++)
              free(m_3DContours[i].pts);

          free(this->m_3DContours);
          this->m_3DContours= NULL;
          this->m_num3DContours = 0;
      }

    for (int ee = 0; ee <  m_source->bChannels; ee++)
    {
      awpImage* tmp = NULL;
      awpGetChannel(m_source,  &tmp, ee);
      double* a = (double*)m_azmuth->pPixels;
      double* t = (double*)tmp->pPixels;

      awpImage* res = NULL;
      int idx  = ee;
	  double len = m_source->sSizeX;
	  int len1   = m_source->sSizeX-1;
	  awpCreateImage(&res, 2*m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght, 2*m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght, 1, AWP_DOUBLE);
      double* r  = (double*)res->pPixels;
	  double* aa = (double*)this->m_elev->pPixels;

      awpPoint p1,p2,p3,p4, c[5];
      awpRect rect;

      awpContour contour;
      contour.NumPoints = 5;
      contour.Direction = true;
      contour.Points = c;

      int l = m_source->sSizeX*this->m_2DOptions.dist_x / m_max_lenght;
      len1 = l;

      for (int i = 0; i < m_azmuth->sSizeX-1; i++ )
      {
          for (int j = 0; j < l; j++)
          {
              //int x,y,x1,y1,x3,y3,x4,y4;  //
              c[0].X = floor(len1 + len1*(m_dist[j] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);
              c[0].Y = floor(len1 + len1*(m_dist[j] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);

              c[1].X = floor(len1 + len1*(m_dist[j] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX + 1]/180) + 0.5);
              c[1].Y = floor(len1 + len1*(m_dist[j] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX +1]/180) + 0.5);

              c[2].X = floor(len1 + len1*(m_dist[j+1] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX+1]/180) + 0.5);
              c[2].Y = floor(len1 + len1*(m_dist[j+1] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX+1]/180) + 0.5);

              c[3].X = floor(len1 + len1*(m_dist[j+1] / m_dist[len1])*cos(3.14*a[i+ idx*m_azmuth->sSizeX ]/180) + 0.5);
              c[3].Y = floor(len1 + len1*(m_dist[j+1] / m_dist[len1] )*sin(3.14*a[i+ idx*m_azmuth->sSizeX]/180) + 0.5);
              c[4] = c[0];



			  awpGetContourRect(&contour, &rect);
              double v1, v2, v3, v4, v5, v6, v;

              v1 = t[j+ i*tmp->sSizeX];
              r[2*c[0].Y*(l) + c[0].X] = v1;
              v2 = t[j+ (i+1)*tmp->sSizeX];
              v3 = t[(j+1)+ (i+1)*tmp->sSizeX];
              v4 = t[(j+1)+ i*tmp->sSizeX];

			  if (v1 == v2 && v1 == v3 && v1 == v4)
                  continue;

                 //    awpDrawPolygon(res, &contour, 0, 100, 0);

              double l1,l2;
			  l1 = sqrt(double((c[1].X - c[0].X)*(c[1].X - c[0].X) + (c[1].Y - c[0].Y)*(c[1].Y - c[0].Y)));
			  l2 = sqrt(double((c[3].X - c[2].X)*(c[3].X - c[2].X) + (c[3].Y - c[2].Y)*(c[3].Y - c[2].Y)));


              // нахождение minx и maxx
              awpPoint pp;
              for (int yy = rect.top; yy <= rect.bottom; yy++)
              {
                  pp.Y = yy;
                  for (int xx = rect.left; xx <= rect.right; xx++)
                  {
                    pp.X = xx;
                    AWPBOOL result = false;
                    awpIsPointInContour(&contour, &pp, &result);
                    if (result == true)
                    {
                       double r1,r2, r3 , r4 , r5;
					   r1 = sqrt(double((xx - c[0].X)*(xx - c[0].X)+(yy - c[0].Y)*(yy - c[0].Y)));
					   r2 = sqrt(double((xx - c[1].X)*(xx - c[1].X)+(yy - c[1].Y)*(yy - c[1].Y)));

                       r3 = (l1*l1 + r1*r1 - r2*r2) / (2*l1);

					   r1 = sqrt(double((xx - c[2].X)*(xx - c[2].X)+(yy - c[2].Y)*(yy - c[2].Y)));
					   r2 = sqrt(double((xx - c[3].X)*(xx - c[3].X)+(yy - c[3].Y)*(yy - c[3].Y)));

                       r4 = (l2*l2+r1*r1 - r2*r2) / (2*l2);

					   r1 = sqrt(double(((xx - c[0].X)*(xx - c[0].X)+(yy - c[0].Y)*(yy - c[0].Y))));
                       if (r1*r1 - r3*r3 >= 0 )
						   r5 = sqrt(double(r1*r1 - r3*r3 ));
                       else
                           r5 = 0;
                       // интерполяция.
                       v5 = r3*(v2 - v1) / l1 + v1;
                       v6 = r4*(v4 - v3) / l2 + v3;
                       v  =  v5 + r5*(v6 - v5) / l1;
                       r[2*yy*l + xx] = v;
                    }
                    else
                    {
                      //r[2*yy*1832 + xx] = -32;
                    }
                  }
              }


              awpPoint p1,p2;
              p1.X = c[0].X;
              p2.X = c[1].X;
              p1.Y = c[0].Y;
              p2.Y = c[1].Y;

            // _awpDrawThickLine(res, p1,p2, 0, (v1+v2)/2, v1,v2);
          }
      }

	  for (int i = 0; i < res->sSizeX*res->sSizeY; i++)
      {
          if (r[i] < -32)
              r[i] = -32;
		  if (r[i] > 97)
              r[i] = 97;

          r[i] += 32;
          r[i] *=1.9;
      }

      awpConvert(res, AWP_CONVERT_TO_BYTE);
      if (this->m_2DOptions.smooth)
        awpGaussianBlur(res, res, 1.5);
          //
          AWPBYTE* pix = (AWPBYTE*)res->pPixels;
          for (int i = 0; i < res->sSizeX*res->sSizeY; i++)
          {
              pix[i] = 255- pix[i];
          }
          double fi = aa[ee*this->m_elev->sSizeX];
          fi *= 3.14;
          fi /= 180;

          int num = 0;
          awpStrokeObj* obj = NULL;
          awpGetStrokes(res, &num, &obj, 200, NULL);
          for (int i = 0; i < num; i++)
		  {
              awpRect rect;
              awpCalcObjRect(&obj[i], &rect);
              int w = rect.right - rect.left;
              int h = rect.bottom - rect.top;
              if (w*h > 100)
              {
                  awpContour* c = NULL;
                  awpCreateContour(&c, obj[i].Num, true);
				  awpGetObjCountour(&obj[i], c);
                  if (c == NULL)
                      continue;
                  this->m_num3DContours++;
                  int nc = m_num3DContours;
                  this->m_3DContours = (T3DContour*)realloc(this->m_3DContours, nc*sizeof(T3DContour));
                  this->m_3DContours[nc-1].num = c->NumPoints;
                  this->m_3DContours[nc-1].pts = (T3DPoint*)malloc(c->NumPoints*sizeof(T3DPoint));
                  for (int k = 1; k < c->NumPoints; k++)
                  {
                      awpPoint p1;

                      p1.X = c->Points[k-1].X;
                      p1.Y = c->Points[k-1].Y;

                      T3DPoint p;
                      p.x = -1 + (double)p1.X / ((double)res->sSizeX/2);
                      p.y = -1 + (double)p1.Y / ((double)res->sSizeY/2);
                      double d =  sqrt(p.x*p.x + p.y*p.y);
                      p.z = (-1 + 10*d*sin(fi));

                      this->m_3DContours[nc-1].pts[k] = p;
                  }
                  awpFreeContour(&c);
			  }
          }
          awpFreeStrokes(num, &obj);
     _AWP_SAFE_RELEASE_(res);
     _AWP_SAFE_RELEASE_(tmp);
   }
}


void __fastcall TForm2::SpeedButton4Click(TObject *Sender)
{
    m_currentFrame++;
    if (m_currentFrame >= FList->Count)
        m_currentFrame = 0;
    MREvent* e = ( MREvent*)FList->Items[m_currentFrame];
    if (e != NULL)
    {
      UnicodeString str = m_strDataPath;
      str += e->FileName.c_str();
      AnsiString _ansi = str;
      this->OpenNCFile(_ansi.c_str());
      ComboBox1->ItemIndex = 0;
      ComboBox3->ItemIndex = m_currentFrame;
	  Draw2DScene();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton2Click(TObject *Sender)
{
    m_currentFrame--;
    if (m_currentFrame < 0)
		m_currentFrame = FList->Count - 1;
	MREvent* e = ( MREvent*)FList->Items[m_currentFrame];
	if (e != NULL)
    {
      UnicodeString str = m_strDataPath;
      str += e->FileName.c_str();
      AnsiString _ansi = str;
      this->OpenNCFile(_ansi.c_str());
      ComboBox1->ItemIndex = 0;
	  Draw2DScene();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
 if (FList->Count == 0)
    return;
  SpeedButton4Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton5Click(TObject *Sender)
{
    Timer1->Enabled = !Timer1->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FindAlfaMaxMin(double& amin, double& amax)
{
    double* data = (double*)this->m_elev->pPixels;
    amin = data[0];
    amax = data[0];
    for (int i = 1; i < m_elev->sSizeX*m_elev->sSizeY; i++)
    {
        if (amin > data[i])
            amin = data[i];
        if (amax < data[i])
			amax = data[i];
    }

    amin = AWP_PI*amin/180.;
    amax = AWP_PI*amax/180.;

}
static double GetFi(double x, double y)
{
	double base = 0;
    double fi = 0;
    if (x == 0)
        fi = 90;
    else
        fi = 180* atan(fabs(y) / fabs(x)) / AWP_PI;
    if (x >= 0 && y >= 0)
        base = 0;
    else if (x <0 && y >= 0)
        base = 90;
    else if (x <= 0 && y < 0)
        base = 180;
    else if (x>= 0 && y < 0)
        base = 270;
    return base + fi;
}
double L2(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
awpPoint __fastcall  TForm2::FindFiTheta(double fi, double theta)
{
    double* f = (double*)this->m_azmuth->pPixels;
    double* t = (double*)this->m_elev->pPixels;
	awpPoint p;
    p.X = 0;
    p.Y = 0;
    double min = L2(f[0],fi, t[0], theta);
    int c = 0;
    for (int y = 0; y < m_elev->sSizeY; y++)
    {
        for (int x = 0; x < m_elev->sSizeX; x++)
        {
		   double v = L2(f[c], t[c], fi, theta);
           c++;
           if (min > v)
           {
            min = v;
            p.X = x;
            p.Y = y;
           }
        }
    }
    return p;
}

//---------------------------------------------------------------------------
void __fastcall TForm2::MakeInterPic(double H, double R, awpImage* img)
{
//
    if (img == NULL)
        return;
    if (H < 100 || R < 10000)
        return;

    double beta = 2*R / img->sSizeX;
    double R0 = 0;
	double R1 = 0;
    double alfa_max = 0;
    double alfa_min = 0;
    int scan_width = img->bChannels*img->sSizeX;

    FindAlfaMaxMin(alfa_min, alfa_max);

    R0 = H / tan(alfa_max);
    R1 = H / tan(alfa_min);

    if (R1 > R)
        R1 = R;

    awpPoint c;
    c.X = img->sSizeX / 2;
    c.Y = img->sSizeY / 2;
    AWPBYTE* bb = (AWPBYTE*)img->pPixels;
    for (int y = 0; y < img->sSizeY; y++)
    {
        for (int x = 0; x < img->sSizeX; x++)
        {
            double X, Y, ro;
            X = (x - c.X)*beta;
            Y = (y - c.Y)*beta;
            ro = sqrt(X*X + Y*Y);

            if (ro < R0 || ro > R1)
                continue;

            double fi = GetFi(X,Y);
            double theta = 180*atan(H / ro) / AWP_PI;
            awpPoint p = FindFiTheta(fi, theta);

			bb[y*scan_width + img->bChannels*x] = 0;
            bb[y*scan_width + img->bChannels*x + 1] = 255;
            bb[y*scan_width + img->bChannels*x + 2] = 0;
        }
    }
}

void __fastcall TForm2::InterHorizontalActionExecute(TObject *Sender)
{
	m_2DViewOptions = eInterpolatedHorizontal;
    awpImage* img = GetInterCone(0);
    AWPDOUBLE* pix = (AWPDOUBLE*)img->pPixels;
    for (int i = 1; i < 4; i++)
    {
        awpImage* cone = GetInterCone(i);
        if (cone == NULL)
            continue;

        AWPDOUBLE* pix1 = (AWPDOUBLE*)cone->pPixels;
        for (int j = 0; j < cone->sSizeX*cone->sSizeY; j++)
            pix[j] += pix1[j];

        _AWP_SAFE_RELEASE_(cone);
    }
    awpConvert(img, AWP_CONVERT_TO_BYTE_WITH_NORM);
    FImage1->Bitmap->SetAWPImage(img);
    FImage1->BestFit();
    _AWP_SAFE_RELEASE_(img);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::InterHorizontalActionUpdate(TObject *Sender)
{
	InterHorizontalAction->Checked = m_2DViewOptions == eInterpolatedHorizontal;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DrawFlashes1(awpImage* image)
{
	if (ComboBox3->ItemIndex < 0 || image == NULL)
		return;

	awpImage* img = image;
	int w = img->sSizeX;
	int h = img->sSizeY;
	double x = 0;
	double y = 0;

	MREvent* e = ( MREvent*)FList->Items[ComboBox3->ItemIndex];
	if (e != NULL && e->ListFlash != NULL)
	{
		for (int i = 0; i < e->ListFlash->Count; i++)
		{
			TFlash* f = (TFlash*)e->ListFlash->Items[i];
			ConLL(f->lat, f->lon, RLat, RLon, w,h, m_2DOptions.dist_x , x, y);

			awpRect rect;

			double r = (double)f->num / 100. < 1 ? 10 : f->num / 10;
			rect.left = x - r;
            rect.top  = y - r;
			rect.right = x + r;
			rect.bottom = y + r;

			awpDrawCRect(img, &rect,  255,0, 0,  3);

        }
	}
}

void __fastcall TForm2::ResultCellsActionExecute(TObject *Sender)
{
	m_2DViewOptions = eResultCell;
	Draw2DScene();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ResultCellsActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TForm2::N4Click(TObject *Sender)
{
    SpeedButton3Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FindObjects(awpImage*  img1, awpImage*  img2)
{
	ListView1->Clear();
	VecList->Clear();

	int SumS=0;  //сумма площадей всех ячеек
	double SumP=0;  // сумма периметров всех ячеек
	int num = 0;
	double MI,MA,TETA; // полуоси всех ячеек
	awpPoint P; //цент масс всех ячеек

	awpStrokeObj* obj = NULL;
	awpGetStrokes(img1, &num, &obj, 64, NULL);

	 awpGetOrientation(img1, &TETA, &MI, &MA);
	 awpGetCentroid(img1, &P);
	VecList->Add(new VectorP);

	VectorP* v = (VectorP*)VecList->Items[0];
	v->teta=TETA;
	v->mi=MI;
	v->ma=MA;
	v->cX=P.X;
	v->cY=P.Y;

	for (int i = 0; i < num; i++)
	{
		awpRect rect;

		awpCalcObjRect(&obj[i], &rect);
		int w = rect.right - rect.left;
		int h = rect.bottom - rect.top;

		if (w*h > 128)
		{
			VectorP *VP=new VectorP;
			// awpDrawCRect(img2,&rect, 0,255,255, 1);
			// площадь
			int s;
			awpStrObjSquare(&obj[i], &s);
			VP->s=s;
			TListItem* item = ListView1->Items->Add();
			item->Caption = IntToStr(i);
			item->SubItems->Add(s);
						//периметр
            awpContour* c = NULL;
			awpCreateContour(&c, obj[i].Num*2, true);
            awpGetObjCountour(&obj[i], c);
            if (c == NULL)
				continue;
            double d;
            awpDrawCPolygon(img2,c, 0,255,0,1);
			awpGetContPerim(c, &d);
			VP->p = d;   //добавили периметр
            awpFreeContour(&c);
			item->SubItems->Add(d);
			// цм
			awpPoint p;
			awpGetObjCentroid(img1, &obj[i], &p);
			VP->cX=p.X;
			VP->cY=p.Y;

			if(OptionsDlg->CheckBox4->Checked)
			{
				awpDrawCPoint(img2, p, 0,0,255, 3);
			}

			item->SubItems->Add(p.X);
			item->SubItems->Add(p.Y);
			// эллипс
			double teta;
			double mi;
			double ma;
			awpGetObjOrientation(img1, &obj[i],&teta, &mi, &ma); ///нодо смотреть и исправить и посмотреть как рисуются элипсы
            VP->teta=teta;
			VP->mi=mi;
			VP->ma=ma;
			awpDrawCEllipse(img2, p, mi,ma, teta, 0,0,255, 1);
            	item->SubItems->Add(ma);
				item->SubItems->Add(mi);
				item->SubItems->Add(teta);


		   //	awpGetOrientation(img1, &TETA, &MI, &MA);
		   //	VP->TETA=TETA;
		   //	VP->MI=MI;
		   //	VP->MA=MA;

		   //центр всех ячеек
			  /*
			awpGetCentroid(img1, &P);
			awpRect r;
		   r.left = P.X-10;
		   r.right = P.X+10;
		   r.top = P.Y-10;
		   r.bottom = P.Y+10;
		  awpDrawCross(img2, &r, 2, 255, 1);
		  */
		   VecList->Add(VP);

		SumS+=VP->s;
		SumP+=VP->p;
		VecList->Add(VP);
		}

	}
   v = (VectorP*)VecList->Items[0];
   //отрисока центра масс всех ячеек
		   awpRect r;
		   r.left = P.X-10;
		   r.right = P.X+10;
		   r.top = P.Y-10;
		   r.bottom = P.Y+10;
		  awpDrawCross(img2, &r, 2, 255, 1);


		TListItem* item = ListView1->Items->Add();
		item->Caption = "итого:";
		v->s=SumS;
		v->p=SumP;

	VecList->Add(v);
	item->SubItems->Add(v->s);
	item->SubItems->Add(v->p);
	item->SubItems->Add(v->teta);
	item->SubItems->Add(v->mi);
	item->SubItems->Add(v->ma);



	awpFreeStrokes(num, &obj);
	DrawFlashes1(img2);
}


void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (this->m_outFile != NULL)
		fclose(this->m_outFile);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox3Change(TObject *Sender)
{
    if (ComboBox3->ItemIndex >= 0)
	{
		AnsiString _ansi = m_strDataPath + ComboBox3->Items->Strings[ComboBox3->ItemIndex];
//        const char* name = "D:\\kabr\\KABR_V06_20150813_100016.nc";
        OpenNCFile(_ansi.c_str());
//        OpenNCFile(name);
        ComboBox1->ItemIndex = 0;
		Draw2DScene();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::PaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	 if (m_mdown)
	 {
		m_dx -= X;
		m_dy -= Y;
		t.ay = t.ay + m_dy;
		t.az = t.az + m_dx;
		this->DrawScene();
		m_dx = X;
		m_dy = Y;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FImage1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
//
	int XX=FImage1->GetImageX(X);
	int YY=FImage1->GetImageY(Y);

   //	for (int i)
}
//---------------------------------------------------------------------------

   void __fastcall TForm2::FImageResult(TList* VecList, TList* MapList)
   {
	  MapList->Clear();
	  double R,R0,r;
	  awpImage* img = NULL;
	  FImage1->Bitmap->GetAWPImage(&img);
	  R0=sqrt(2.)*img->sSizeX;
	  VectorP* VP =(VectorP*)VecList->Items[0];
	   double x1=VP->cX;
	   double y1=VP->cY;
	 //cоздаем карту
	 for(int y = 0; y < img->sSizeX; y+= 32)
	 {
		for (int x = 0; x < img->sSizeX; x+= 32)
		{
		  R=sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));


		   TMapElement* e = new TMapElement();
		   e->S_lat = y+16;
		   e->S_lon = x+16;
		   e->Size_lat = 34;
		   e->Size_lon = 34;
		   double S=VP->s;
		   double P=VP->p;
		   double MI=VP->mi;
		   double MA=VP->ma;
		   e->Vector[0]=(1.-  R/R0);
		   e->Vector[1]=S/(R*R);
		   e->Vector[2]=4*AWP_PI*S/(P*P);//4*sqrt(S*AWP_PI)/P; //обратный коэф малинковского
		   e->Vector[3]=MI/MA;
		   e->Vector[4]=MA/(R0);

		   //memset(e->Vector, 0, sizeof(e->Vector));

		   VectorP*  vp = GetNearCell(e->S_lon, e->S_lat);
		   if (vp != NULL)
		   {
			  r=sqrt(double((vp->cX -x)*(vp->cX-x)+(vp->cY-y)*(vp->cY-y)));
			  double s=vp->s;
			  double p=vp->p;
			  double mi=vp->mi;
			  double ma=vp->ma;


		   e->Vector[5]=(1.-  r/R0);
		   e->Vector[6]=sqrt(s*AWP_PI)/p;  //обратный коэф малинковского
		   e->Vector[7]=mi/ma;
		   e->Vector[8]= ma/(r+1);
		   e->Vector[9]=4*AWP_PI*s/(p*p);  //коэф формы
		   e->Vector[10]=p/(2*AWP_PI*(r+1));
		   e->Vector[11]=s/(2*AWP_PI*(r+1));

		   }


		   MapList->Add(e);

		}

	 }

   }

   void __fastcall TForm2::DrawResult(TList * MapList)
   {
	   awpImage* img = NULL;
	   awpCreateImage(&img, 1200, 1200, 1, AWP_BYTE);
	   for (int i = 0; i < MapList->Count; i++)
	   {
		   TMapElement* e = (TMapElement*)MapList->Items[i];

		   awpRect r;
		   r.left = e->S_lon - e->Size_lon/2;
		   r.right = e->S_lon + e->Size_lon/2;
		   r.top = e->S_lat - e->Size_lon/2;
		   r.bottom = e->S_lat + e->Size_lon/2;
		   double v = 0;
		   double num_flash = this->IsFlashInRect(r,600,600);
		   if (this->m_outFile != NULL)
				fprintf(m_outFile, "%f:", num_flash );
		   for (int j = 0; j < 11; j++)
		   {
			  v+= 0.125*e->Vector[j];
			  if (this->m_outFile != NULL)
				fprintf(m_outFile, "%f:", e->Vector[j] );
		   }
		   if (this->m_outFile != NULL)
			 fprintf(m_outFile, "\n");
		   v*=255;
		   awpFillRect (img, &r, 0, v);
	   }
	   FImage2->Bitmap->SetAWPImage(img);
	   FImage2->BestFit();
	   awpReleaseImage(&img);
   }

VectorP* TForm2::GetNearCell(double x, double y)
{
	if (VecList == NULL)
		return NULL;
    if (VecList->Count < 2)
        return NULL;
    double mind = 1e10;
    int    minidx;
    for (int i = 1; i < VecList->Count; i++)
    {
	   VectorP* v = (VectorP*)VecList->Items[i];
       double d = sqrt((x - v->cX)*(x - v->cX) + (y-v->cY)*(y-v->cY));
       if (d < mind)
       {
         mind = d;
         minidx = i;
	   }
    }
    return (VectorP*)VecList->Items[minidx];

}
void __fastcall TForm2::CheckBox1Click(TObject *Sender)
{
	if (CheckBox1->Checked)
	{
		this->m_outFile = fopen("svm_out.txt", "w+t");
	}
	else
	{
		if (m_outFile != NULL)
			fclose(this->m_outFile);
	}
}
//---------------------------------------------------------------------------
bool __fastcall TForm2::IsFlashInRect(awpRect r, int w, int h)
{
	if (ComboBox3->ItemIndex < 0)
		return false;
	double x = 0;
	double y = 0;

	MREvent* e = ( MREvent*)FList->Items[ComboBox3->ItemIndex];
	if (e != NULL && e->ListFlash != NULL)
	{
		for (int i = 0; i < e->ListFlash->Count; i++)
		{
			TFlash* f = (TFlash*)e->ListFlash->Items[i];
			ConLL(f->lat, f->lon, RLat,RLon, w,h, m_source->sSizeX*this->m_2DOptions.dist_x, x, y);
			if (x > r.left && x < r.right && y > r.top && y < r.bottom)
				return true;
		}
	}
	return false;
}

