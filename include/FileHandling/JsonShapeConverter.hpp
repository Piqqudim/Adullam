#pragma once 
#include<TopoDS_Shape.hxx>
#include<string>
#include<sstream>
#include<BRep_Builder.hxx>
#include<BinTools.hxx>
#include<QtCore/QByteArray>
#include<BRepTools.hxx>
#include<InfoUtility.hpp>
#include<Quantity_Color.hxx>
using namespace std;
using namespace INFO;
//we will working with objects of QByte Array
namespace JsonConverter{
inline QByteArray ToBase64(const TopoDS_Shape& shape){
  stringstream Stream;
  BinTools::Write(shape,Stream); 

  auto content=Stream.str();
  return QByteArray(content.c_str(),static_cast<qsizetype>(content.size())).toBase64();
  
}    
inline QString ConvertToString(const TopoDS_Shape& shape){
     QByteArray inputValue=JsonConverter::ToBase64(shape);
     return QString::fromUtf8(inputValue);
    }
 inline TopoDS_Shape ToShape(const QString& value){
    if(value.isEmpty()){
        return TopoDS_Shape(); //return an empty TopoDS_Shape();
    }
    QByteArray binaryData=QByteArray::fromBase64(value.toUtf8()); //convert
    string string1(binaryData.constData(),static_cast<size_t>(binaryData.size()));
    if(string1.empty()){
      LoadMessage(QString("String Reading Error"),QString("Empty String"));
    }
    stringstream stream1(string1);

   
    TopoDS_Shape sh;
    BinTools::Read(sh,stream1); //read the binary data and convert it to an object of TopoDS_Shape
   if(sh.IsSame(TopoDS_Shape())){
      LoadMessage(QString("Shape Reading Error"),QString("Empty Shape"));

   }
    return sh;
 }

inline QString ToString(const TopoDS_Shape& Shape){
   stringstream Stream;

   BRepTools::Write(Shape,Stream);
   if(Stream.str().empty()){
       LoadMessage(QString("String Reading Error"),QString("Empty String"));

   }
   return QString::fromStdString(Stream.str());
 }
inline TopoDS_Shape ToMainShape(const QString& str){
   if(str.isEmpty()){
      LoadMessage(QString("String Error"),QString("Empty"));
      return TopoDS_Shape();
   }
   stringstream stream(str.toStdString());
   TopoDS_Shape shape;
   BRep_Builder builder; 
   BRepTools::Read(shape,stream,builder);
   if(!shape.IsSame(TopoDS_Shape())){
       LoadMessage(QString("Shape Reading"),QString("Successful Reading Of Shape"));
   }
   return shape;
 }
inline QJsonObject ToJsonColorFormat(const Quantity_Color& col){
   QJsonObject object;
   object["R"]=col.Red();
   object["G"]=col.Green();
   object["B"]=col.Blue();
   return object;
}
inline Quantity_Color ToColor(const QJsonObject& object){
   double r=object["R"].toDouble();
   double g=object["G"].toDouble();
   double b=object["B"].toDouble();
   Quantity_Color color(r,g,b,Quantity_TOC_RGB);
  return color;
}
}
