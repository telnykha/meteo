//---------------------------------------------------------------------------


#pragma hdrstop

#include "nc_XML_Import.h"
#include <TinyXML.h>
#pragma link "tinyxml.lib"
//---------------------------------------------------------------------------

#pragma package(smart_init)

 void ReadXML( AnsiString XFile, TList* MyList, AnsiString &RadarName, AnsiString &RadarType, double &Lat, double &Lon)
{
 if (MyList==Null)
    return;
 if (!FileExists(XFile))
 {
    ShowMessage("������ ����");
    return;
 }
  //ShowMessage (XFile);
  TiXmlDocument m_doc;// ���������� �������  ���� TiXml
  TiXmlElement* m_element; //���������� �������  ���� ������� ��� TiXml

  if (!m_doc.LoadFile(XFile.c_str()))
  {
      ShowMessage("�� ���� ��������� .XML ����");
      return;
  }
  m_element=m_doc.FirstChildElement();
  if (m_element==NULL||strcmp(m_element->Value(),"radar")!=0)
  {
      ShowMessage("�� ���� ��������� .XML ����");
      return;
  }
   m_element->QueryDoubleAttribute("lat", &Lat);
   m_element->QueryDoubleAttribute("lon", &Lon);
   RadarName=m_element->Attribute("name_radar");
   RadarType=m_element->Attribute("type_radar");
   AnsiString S=RadarName+"  "+ RadarType+ " "+FloatToStr(Lat)+":"+FloatToStr(Lon);
   ShowMessage (S);
   TiXmlElement* element=m_element->FirstChildElement();// ���������  EVENT

   if (element==NULL||strcmp(element->Value(),"event")!=0)
  {
      ShowMessage("��t ������ � .XML �����");
      return;
  }
   for (TiXmlNode* child =m_element->FirstChild(); child; child = child->NextSibling())
   {
      MREvent* e = new MREvent;
      TiXmlElement* ee = child->ToElement();
      e->FileName = ee->Attribute("NAME");
      e->FDate = StrToDate(ee->Attribute("DATE"));
      e->FTime = StrToTime(ee->Attribute("TIME"));
      // ��������� �������
      TiXmlElement* f = ee->FirstChildElement();
      if (f != NULL)
      {

         e->ListFlash = new TList();
         for (TiXmlNode* child1 =ee->FirstChild(); child1; child1 = child1->NextSibling())
         {
            TFlash* fl = new TFlash;
            TiXmlElement* q =  child1->ToElement();
            q->QueryDoubleAttribute("Lat", &fl->lat);
            q->QueryDoubleAttribute("Lon", &fl->lon);
            q->Attribute("Num", &fl->num);
            e->ListFlash->Add(fl);
         }
      }
      else
        e->ListFlash = NULL;

      //��������� ��� � ������
      MyList->Add(e);


   }


}
