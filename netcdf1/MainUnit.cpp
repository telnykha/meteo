//---------------------------------------------------------------------------

#include <vcl.h>
#include "netcdf.h"
#pragma hdrstop

#include "MainUnit.h"
#include "VarUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "netcdfb.lib"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        m_ncid = 0;
        this->m_source = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if (m_ncid != 0)
        {
            nc_close(m_ncid);
            m_ncid = 0;
        }

        if (OpenDialog1->Execute())
        {
            int status = NC_NOERR;
            int ncid   = 0;
            status = nc_open(OpenDialog1->FileName.c_str(), 0, &m_ncid);
            if (status != NC_NOERR)
                ShowMessage("не могу открыть файл " + OpenDialog1->FileName);
            int  ndims, nvars, ngatts, unlimdimid;
            status = nc_inq(m_ncid, &ndims, &nvars, &ngatts, &unlimdimid);
            if (status != NC_NOERR)
                ShowMessage("не могу открыть файл " + OpenDialog1->FileName);
            ComboBox1->Clear();
            char buf[NC_MAX_NAME+1];
            for (int i = 0; i < nvars; i++)
            {
                int nd;
                int ndimsp;
                int ndimdsp;
                int nattsp;
                status = nc_inq_var(m_ncid, i, buf, NULL, &ndimsp, &ndimdsp, &nattsp);
                ComboBox1->Items->Add(buf);
            }
            ComboBox1->ItemIndex = 0;
            ComboBox2->Clear();
            for (int i = 0; i < ngatts; i++)
            {
                size_t len;
                status = nc_inq_att(m_ncid, i, buf, NULL, &len);
                ComboBox2->Items->Add(buf);

            }
            ComboBox2->ItemIndex = 0;
            ComboBox3->Clear();
            for (int i = 0; i < ndims; i++)
            {
                int nd;
                size_t len;
                status = nc_inq_dim(m_ncid, i, buf, &len);
                ComboBox3->Items->Add(buf);
            }
            ComboBox3->ItemIndex = 0;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    VarForm->Caption = this->ComboBox1->Text;
    bool process = false;
       if ( VarForm->Caption == "Reflectivity")
       {
            ShowMessage("Hi");
            process = true;
       }

    int varID;
    nc_inq_varid(this->m_ncid, VarForm->Caption.c_str(), &varID);
    nc_type xtypep;
    int ndimsp;
    int dimidsp[128];
    int nattsp;
    nc_inq_var(this->m_ncid,  varID, NULL, &xtypep, &ndimsp, dimidsp, &nattsp);
    VarForm->Label8->Caption = IntToStr(nattsp);
    VarForm->Label9->Caption = IntToStr(ndimsp);
    VarForm->Label10->Caption = "неизвестный";
    VarForm->Label11->Caption = VarForm->Caption.c_str();
    VarForm->Label12->Caption = IntToStr(varID);
    VarForm->ListBox1->Clear();
    VarForm->ComboBox2->Clear();
    char buf[NC_MAX_NAME+1];
    int w, h, c;
    for (int i = 0; i < ndimsp; i++)
    {
       size_t len;
       nc_inq_dim(this->m_ncid,dimidsp[i], buf, &len);
       AnsiString str = buf;
       if (process)
       {
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
         }

       }

       VarForm->ComboBox2->AddItem(str, NULL);
       str += " len = ";
       str += IntToStr(len);
       VarForm->ListBox1->AddItem(str, NULL);
    }
    if (process)
    {
        _AWP_SAFE_RELEASE_(m_source);
        awpCreateImage(&m_source, w,h,c, AWP_DOUBLE);
        double* p = (double*)m_source->pPixels;
        size_t start[3] = {0,0,0};
        size_t count[3]  = {c,h,w};
        double* data = (double*)malloc(c*h*w*sizeof(double));
        int status = nc_get_vara_double(this->m_ncid, varID, start, count, data);
        if (status != NC_NOERR)
            ShowMessage("ошибка!");


        int k = 0;
        for (int r = 0;r < w; r++)
        {
            for (int a = 0; a < h; a++)
            {
               for (int cc = 0;cc < c; cc++)
                {
                    p[r*c + cc+ c*w*a] = data[cc*w*h + (r + w*a)];
                    k++;
                }
            }
        }

        awpImage* tmp = NULL;
        awpGetChannel(m_source,  &tmp, 0);
        awpConvert(tmp, AWP_CONVERT_TO_BYTE_WITH_NORM);
        double* m1;
        double* m2;
        awpMinMax(tmp, &m1, &m2);

        awpSaveImage("tmp.awp", tmp);
        VarForm->FImage1->Bitmap->SetAWPImage(tmp);
        awpReleaseImage(&tmp);
        free(data);
    }

    VarForm->Show();
}
//---------------------------------------------------------------------------

