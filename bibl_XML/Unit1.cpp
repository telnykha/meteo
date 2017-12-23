//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#pragma hdrstop
#pragma link "TinyXML.lib"
#include <TinyXML.h>
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{

    TiXmlDocument m_doc;// объявление объекта  типа TiXml
    TiXmlElement* m_element; //объявление объекта  типа элемент для TiXml


    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
    m_doc.LinkEndChild(decl);
    m_element = new TiXmlElement("radar");
    m_element->SetAttribute("name_radar","KBIS");
    m_element->SetAttribute("type_radar","wsd-88");
    m_element->SetDoubleAttribute("lat",100);
    m_element->SetDoubleAttribute("lon",-50);
    int File=1;
    double Ttime=10;

    //создание event
    // структура заполняется информацией о найденном файле
     TSearchRec sr;
     int iAttributes = 0;
     //StringGrid1->
     //->RowCount = 1;


    TiXmlElement* elem = new TiXmlElement("event");
    TiXmlElement* elem1 = new TiXmlElement("flash");
    elem->SetAttribute("File", File);
    elem->SetAttribute("Ttime", Ttime);
    elem1->SetDoubleAttribute("lat",110);
    elem1->SetDoubleAttribute("lon",-55);
     elem1->SetDoubleAttribute("count",100);
    elem->LinkEndChild(elem1);
    m_element->LinkEndChild(elem);
    m_doc.LinkEndChild(m_element);
    m_doc.SaveFile("qwe.xml");
    ///
   // TSearchRec- как пробежаться по катологу

}

//---------------------------------------------------------------------------




