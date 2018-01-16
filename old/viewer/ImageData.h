//---------------------------------------------------------------------------

#ifndef ImageDataH
#define ImageDataH
//---------------------------------------------------------------------------
#include "_LF.h"

class TImageData  : public  TLFObjectList
{
public:
    TImageData();
    void __fastcall AddImage(awpImage* image);
    awpImage* GetImage (int index);
};

#endif
