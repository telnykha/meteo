//---------------------------------------------------------------------------


#pragma hdrstop

#include "ImageData.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


TImageData::TImageData()  : TLFObjectList()
{

}

void __fastcall TImageData::AddImage(awpImage* image)
{
    TLFImage* img = new TLFImage();
    img->SetImage(image);
    Add(img);
}
awpImage* TImageData::GetImage (int index)
{
    TLFImage* img = (TLFImage*)Get(index);
    if (img != NULL)
        return img->GetImage();
    else
        return NULL;
}
