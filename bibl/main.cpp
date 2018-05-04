//---------------------------------------------------------------------------
#include <vcl.h>
#include <TinyXML.h>
#include "LFlash.h"
#pragma link "tinyxml.lib"

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
///////
 void ListFiles(AnsiString& Path, AnsiString& FilterExt, TStrings* List, bool NeedFullNames)
{
  TSearchRec SearchRec;
  //FilterExt.Length();

  FilterExt = FilterExt.UpperCase();
  if (FindFirst(Path + "*.*", faAnyFile, SearchRec) == 0)
   {
    do {
      if (SearchRec.Attr & faDirectory)
       {

                }
      else
         {
        String Ext = ExtractFileExt(SearchRec.Name).UpperCase();
        if  (Ext == FilterExt) {
          if (NeedFullNames) {
            List->Add(Path+SearchRec.Name);
          } else {
            List->Add(SearchRec.Name);
          }
        }
      }
    } while (FindNext(SearchRec) ==  0);
    FindClose(SearchRec);
  }
}
 //////
void subListFile(AnsiString& fName, AnsiString& RName, AnsiString& dData, AnsiString& tTime)
//void subListFile(AnsiString& fName, AnsiString& RName)
{
 int l=fName.Length();// длина строки
 RName=fName.SubString(1,4);
 dData=fName.SubString(l-17,8);
 tTime=fName.SubString(l-8,6);
}
 //// разбор по строчкам времени  и запись в формате времени
 TDateTime SubTime(AnsiString Time)
 {
       AnsiString subString ;
       subString = Time.SubString(0,2);
       unsigned short h = StrToInt(subString);
       subString = Time.SubString(3,2);
       unsigned short m = StrToInt(subString);
       subString = Time.SubString(5,2);
       unsigned short s = StrToInt(subString);
       unsigned short ms =0;
       TDateTime t(h,m,s,ms);
       return t;
 }
    ///// //// разбор по строчкам даты  и запись в формате даты
   TDate SubData(AnsiString Data)
   {
       double yr=StrToInt(Data.SubString(0,4));
       double mm = StrToInt(Data.SubString(5,2));
       double ss = StrToInt(Data.SubString(7,2));
       TDate  d(yr,mm,ss);
       return d;
   }
   int DecodTim( AnsiString Time)
   {
       AnsiString subString ;
       subString = Time.SubString(0,2);
       unsigned short h = StrToInt(subString);
       subString = Time.SubString(3,2);
       unsigned short m = StrToInt(subString);
       subString = Time.SubString(5,2);
       unsigned short s = StrToInt(subString);
       int tt=60*h+m;
        return tt;
   }
/////
void StructListFile(TStrings* List, TList* flash_list, AnsiString& FileXml)
{

      TiXmlDocument m_doc;// объ€вление объекта  типа TiXml
      TiXmlElement* m_element; //объ€вление объекта  типа элемент дл€ TiXml
      TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
      m_doc.LinkEndChild(decl);
      m_element = new TiXmlElement("radar");
      m_element->SetAttribute("name_radar",List->Strings[0].SubString(0,4).c_str());
      m_element->SetAttribute("type_radar","wsd-88");
      m_element->SetDoubleAttribute("lat",100.5);
      m_element->SetDoubleAttribute("lon",-50);


     AnsiString Name,Data,Time;
     AnsiString Name1,Data1,Time1;
     int k=List->Count;// общее кол-во файлов в директории
      int delta;
    for (int i=0; i<k; i++)
    {
        if (i==k-1)
        {
          delta=5;
        }
        else
        {
            subListFile(List->Strings[i],Name,Data,Time);
            subListFile(List->Strings[i+1],Name1,Data1,Time1);
            delta = DecodTim(Time1) - DecodTim(Time);
        }
       TiXmlElement* elem = new TiXmlElement("event");

        // разобрали по сторочкам дату   и записали в формате времени
       TDateTime t=SubTime(Time);
       int tt=DecodTim(Time);
        // разобрали по сторочкам дату   и записали в формате даты
       TDate d=SubData(Data);
       AnsiString timeString = t.TimeString();
       elem->SetAttribute("NAME",List->Strings[i].c_str());
       elem->SetAttribute("DATE", d.DateString().c_str());
       elem->SetAttribute("TIME", t.TimeString().c_str());

       if (flash_list != NULL)
       {
            for (int j = 0; j < flash_list->Count; j++)
            {
               //
               TFlash* Flash = (TFlash*)flash_list->Items[j];
                TDateTime t_flash;
                t_flash=Flash->time;
                 unsigned short fh;
                 unsigned short fm;
                 unsigned short fs;
                 unsigned short fms=0;
                t_flash.DecodeTime(&fh,&fm,&fs,&fms);
                int ft=60*fh+fm;
                if (ft-tt> 0 && ft-tt<=delta)
                 {
                  TiXmlElement* elem1 = new TiXmlElement("flash");
                     elem1->SetDoubleAttribute("Lat", Flash->lat);
                     elem1->SetDoubleAttribute("Lon", Flash->lon);
                  //elem1->SetAttribute("Lat", Flash->lat);
                 // elem1->SetAttribute("Lon", Flash->lon);
                  elem1->SetAttribute("Num",Flash->num);
                  elem1->SetAttribute("Time",Flash->time.TimeString().c_str());
                  elem->LinkEndChild(elem1);

               }
            }
         }
       m_element->LinkEndChild(elem);
    }
     m_doc.LinkEndChild(m_element);
    m_doc.SaveFile(FileXml.c_str());
}

int main(int argc, char* argv[])
{
 AnsiString A=ExtractFilePath(argv[0]);// work directori

  TStringList* Memo1 =  new TStringList();
  TList* flash_list = new TList();
  ListFiles(A,".nc",Memo1, false);

  AnsiString FileName=A+"flashes.txt";
  if (FileExists(A+"flashes.txt"))
  LFlash (FileName.c_str(), flash_list);

  StructListFile(Memo1, flash_list, A+"out.xml");

}
//---------------------------------------------------------------------------
//LFlash ("c:\\Program Files (x86)\\Borland\\CBuilder6\\Projects\\meteo\\база\\HAS010734797\\KBIS\\flashes.txt", flash_list);
//ListFiles("c:\\Program Files (x86)\\Borland\\CBuilder6\\Projects\\meteo\\база\\HAS010734797\\KBIS\\", ".nc", Memo1, false);
 