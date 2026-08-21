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
#include<gp_Vec.hxx>
#include<gp_Quaternion.hxx>
#include<QtCore/QJsonArray>
#include<gp_Ax2.hxx>
#include<EdgeUtility.hpp>
#include<TopoDS_Wire.hxx>
#include<TopoDS.hxx>
#include<BRepBuilderAPI_MakeWire.hxx>
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
inline QJsonObject ToAxisJsonFormat(const gp_Ax2& inputAxis){
   QJsonObject object;
   object["Pos_X"]=inputAxis.Location().X();
   object["Pos_Y"]=inputAxis.Location().Y();
   object["Pos_Z"]=inputAxis.Location().Z();
   object["Dir_X"]=inputAxis.Direction().X();
   object["Dir_Y"]=inputAxis.Direction().Y();
   object["Dir_Z"]=inputAxis.Direction().Z();
   return object;
}
inline gp_Ax2 ToAxisFormat(const QJsonObject& object){
   double pos_x=object["Pos_X"].toDouble();
   double pos_y=object["Pos_Y"].toDouble();
   double pos_z=object["Pos_Z"].toDouble();
   double dir_x=object["Dir_X"].toDouble();
   double dir_y=object["Dir_Y"].toDouble();
   double dir_z=object["Dir_Z"].toDouble();
   gp_Pnt loc(pos_x,pos_y,pos_z);
   gp_Dir dir(dir_x,dir_y,dir_z);
   gp_Ax2 axis(loc,dir);
   return axis;
}
inline QJsonObject ToJsonTranslate(const gp_Vec& transvector){
   QJsonObject object;
   object["X"]=transvector.X();
   object["Y"]=transvector.Y();
   object["Z"]=transvector.Z();
   
   return object;
}
inline gp_Vec ToVector(const QJsonObject& object){
   double x=object["X"].toDouble();
   double y=object["Y"].toDouble();
   double z=object["Z"].toDouble();
   gp_Vec vec(x,y,z);
   return vec;
}
inline QJsonObject ToJsonQuaternion(const gp_Quaternion& quat){
   QJsonObject object;
   object["X"]=quat.X();
   object["Y"]=quat.Y();
   object["Z"]=quat.Z();
   object["W"]=quat.W();
   return object;
} 
inline gp_Quaternion ToQuat(const QJsonObject& object){
   double x=object["X"].toDouble();
   double y=object["Y"].toDouble();
   double z=object["Z"].toDouble();
   double w=object["W"].toDouble();
   gp_Quaternion quat(x,y,z,w);
   return quat;
}
inline QJsonObject ToDirFormat(const gp_Dir& dir){
   QJsonObject object;
   object["X"]=dir.X();
   object["Y"]=dir.Y();
   object["Z"]=dir.Z();
   return object;
}
inline gp_Dir ToDir(const QJsonObject& object){
   double x=object["X"].toDouble();
   double y=object["Y"].toDouble();
   double z=object["Z"].toDouble();
   gp_Dir dir(x,y,z);
   return dir;
}
inline QJsonObject ToPntJson(const gp_Pnt& pnt){
   QJsonObject object;
   object["X"]=pnt.X();
   object["Y"]=pnt.Y();
   object["Z"]=pnt.Z();
   return object;
}
inline gp_Pnt ToPoint(const QJsonObject& object){
   double x=object["X"].toDouble();
   double y=object["Y"].toDouble();
   double z=object["Z"].toDouble();
   gp_Pnt pnt(x,y,z);
   return pnt;
}
inline QJsonObject ToLineParam(const Handle(Geom_Line)& geom_line,const double& length){
    gp_Dir dir=geom_line->Position().Direction();
    gp_Pnt pos=geom_line->Position().Location();
    QJsonObject object;
    object["Direction"]=ToDirFormat(dir);
    object["Position"]=ToPntJson(pos);
    object["Length"]=length;
    object["Type"]=QString("Line");
    return object;
    
}
inline TopoDS_Edge ToLineEdge(const QJsonObject& object){
    gp_Pnt pos=ToPoint(object["Position"].toObject());
    gp_Dir dir=ToDir(object["Direction"].toObject());
    double len=object["Length"].toDouble();
    Handle(Geom_Line) geom_line=new Geom_Line(pos,dir);
    if(!geom_line){
      return TopoDS_Edge();
    }
    BRepBuilderAPI_MakeEdge edgemaker;
    edgemaker.Init(geom_line,0,len);
    if(edgemaker.IsDone()){
      return edgemaker.Edge();
    }
    return TopoDS_Edge();
}

inline QJsonObject ToCircleJson(const Handle(Geom_Circle)& circle){
   QJsonObject object;
   object["Axis"]=ToAxisJsonFormat(gp_Ax2(circle->Circ().Position().Location(),circle->Circ().Position().Direction()));
   object["Radius"]=circle->Radius();
   object["Type"]=QString("Circle");
   return object;
}
inline TopoDS_Edge ToCircle(const QJsonObject& object){
   gp_Ax2 ax2=ToAxisFormat(QJsonValue(object["Axis"]).toObject());
   double radius=object["Radius"].toDouble();
   Handle(Geom_Circle) circle=new Geom_Circle(ax2,radius);
   if(!circle){
      return TopoDS_Edge();
   }
   BRepBuilderAPI_MakeEdge edgemaker;
   edgemaker.Init(circle);
   if(edgemaker.IsDone()){
      return edgemaker.Edge();
   }
   return TopoDS_Edge();
}
inline QJsonObject ToCircularArcJson(const Handle(Geom_Circle)& arccircle,const double& firstparam,const double& secondparam){
   QJsonObject object;
   object["Circle"]=ToCircleJson(arccircle);
   object["first_param"]=firstparam;
   object["second_param"]=secondparam;
   object["Type"]=QString("Arc");
   return object;
}
inline TopoDS_Edge ToArc(const QJsonObject& object){
   QJsonObject circleObj=QJsonValue(object["Circle"]).toObject();
   gp_Ax2 axis=ToAxisFormat(QJsonValue(circleObj["Axis"]).toObject());
   double radius=circleObj["Radius"].toDouble();
   double firstparam=circleObj["first_param"].toDouble();
   double secondparam=circleObj["second_param"].toDouble();

   Handle(Geom_Circle) geom_circle=new Geom_Circle(axis,radius);
   if(!geom_circle){
      return TopoDS_Edge();
   }
   gp_Pnt firstpoint,secondpoint;
   geom_circle->D0(firstparam,firstpoint);
   geom_circle->D0(secondparam,secondpoint);
   
   GC_MakeArcOfCircle arcmaker(geom_circle->Circ(),firstpoint,secondpoint,true);
   if(!arcmaker.Value()){
      return TopoDS_Edge();
   }
   BRepBuilderAPI_MakeEdge edgemaker;
   edgemaker.Init(arcmaker.Value());
   if(edgemaker.IsDone()){
      return edgemaker.Edge();
   }
   return TopoDS_Edge();

}
inline QJsonArray ConvertWireToJson(const TopoDS_Wire& wire){
   QJsonArray jsonarray;
   TopExp_Explorer explorer(wire,TopAbs_EDGE);
    for(;explorer.More();explorer.Next()){
        BRepAdaptor_Curve curveAdaptor(TopoDS::Edge(explorer.Current()));
        switch(curveAdaptor.GetType()){
         case GeomAbs_Line:{
         double first,last=0.0;
         Handle(Geom_Curve) curve=BRep_Tool::Curve(TopoDS::Edge(explorer.Current()),first,last);
         if(curve){
            Handle(Geom_Line) geom_line=Handle(Geom_Line)::DownCast(curve);
            if(geom_line){
             jsonarray.append(QJsonValue(ToLineParam(geom_line,last)));
            }
         }
          break;
         }
         case GeomAbs_Circle:{
            double first,second=0.0;
            Handle(Geom_Curve) curve=BRep_Tool::Curve(TopoDS::Edge(explorer.Current()),first,second);
            if(curve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve))){
             Handle(Geom_TrimmedCurve) trimmedcurve=Handle(Geom_TrimmedCurve)::DownCast(curve);
             if(trimmedcurve){
               if(trimmedcurve->BasisCurve()->IsKind(STANDARD_TYPE(Geom_Circle))){
                  Handle(Geom_Circle) circle=Handle(Geom_Circle)::DownCast(trimmedcurve->BasisCurve());
                  if(circle){
                       jsonarray.append(QJsonValue(ToCircularArcJson(circle,first,second)));
                  }
               }
             }
            }
            else if(curve->IsKind(STANDARD_TYPE(Geom_Circle))){
            if(curve){
               Handle(Geom_Circle) circle=Handle(Geom_Circle)::DownCast(curve);
               if(circle){
                  jsonarray.append(QJsonValue(ToCircularArcJson(circle,first,second)));

               }
            }

            }
            break;
         }
        }
    }
    return jsonarray;
}
inline TopoDS_Wire ToWire(QJsonArray objectarray){
   BRepBuilderAPI_MakeWire wiremaker;
   for(auto geomJson:objectarray){
       QJsonObject geomobject=geomJson.toObject();
       QString val=geomobject["Type"].toString();
       if(val==QString("Line")){
         TopoDS_Edge edge=ToLineEdge(geomobject);
         edge.Orientation(TopAbs_FORWARD);
         wiremaker.Add(edge);
       }
       else if(val==QString("Arc")){
         TopoDS_Edge edge=ToArc(geomobject);
         edge.Orientation(TopAbs_FORWARD);
          wiremaker.Add(edge);
       }
   }
   if(wiremaker.IsDone()){
      return wiremaker.Wire();
   }
   return TopoDS_Wire();
}
}
