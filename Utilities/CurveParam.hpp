#pragma once 
#include<TopoDS_Edge.hxx>
#include<Geom_Curve.hxx>
#include<gp_Pnt.hxx>
#include<gp_Dir.hxx>
#include<EdgeUtility.hpp>
using namespace EDGE;
enum CURVE_TYPE{
    CT_LINE,
    CT_CIRCLE,
    CT_ARC,
    CT_SPLINE,
    CT_BEZIER,
    CT_NULL
};
class CurveParam{
    private:
    CURVE_TYPE curvetype;
     
    public:
 CurveParam(){
    return;
}
void SetCurveType(const CURVE_TYPE& ctype){
    curvetype=ctype;
    return;
}
CURVE_TYPE curveType() const{
    return curvetype;
}
virtual void ConstructParameter(const TopoDS_Edge& edge){
    return;
}
};

class LineParam:public CurveParam{
 private:
 gp_Pnt startPoint;
 gp_Dir dir;
 double length=0.0;
 public:
 LineParam():CurveParam(){
    SetCurveType(CT_LINE);
    return;

 }
 LineParam(const TopoDS_Edge& edge){
    ConstructParameter(edge);  //for inplace construction;
    SetCurveType(CT_LINE);
   return;
 }
 gp_Dir LineDir()const{
    return dir;
 }
 double Length() const{
    return length;
 }
 gp_Pnt StartPoint() const {
    return startPoint;
 }
 void ConstructParameter(const TopoDS_Edge& edge) override{
   BRepAdaptor_Curve curve(edge);
   if(curve.GetType()!=GeomAbs_Line){
    return;
   }
   double first,last=0.0;
   Handle(Geom_Curve) geom_curve=BRep_Tool::Curve(edge,first,last);
   if(!geom_curve){
    return;
   }
   Handle(Geom_Line) geom_line=Handle(Geom_Line)::DownCast(geom_curve);
   if(!geom_line){
    return;
   }
   length=last;
   startPoint=geom_line->Position().Location();
   dir=geom_line->Position().Direction();
   return; 
 }

};
class ArcParam:public CurveParam{
private:
gp_Pnt StartPoint;
gp_Pnt EndPoint;
gp_Dir Dir;
gp_Pnt circleCenter;
double Radius=1.0;


public:
ArcParam():CurveParam(){
    SetCurveType(CT_ARC);
    return;
}
ArcParam(const TopoDS_Edge& edge){
  ConstructParameter(edge);
  SetCurveType(CT_ARC);
  return;
}
gp_Pnt startPoint() const{
    return StartPoint;
}
gp_Pnt endPoint() const{
    return EndPoint;
}
double radius() const{
    return Radius;
}
gp_Dir CircleDir() const{
    return Dir;
}
gp_Pnt Center() const{
    return circleCenter;
}
void ConstructParameter(const TopoDS_Edge& edge) override{
  BRepAdaptor_Curve curve(edge);
   if(curve.GetType()!=GeomAbs_Circle){
    return;
   }
   double first,last=0.0;
   Handle(Geom_Curve) geom_curve=BRep_Tool::Curve(edge,first,last);
   if(!geom_curve){
     return;
   }
   Handle(Geom_Circle) geom_circle=Handle(Geom_Circle)::DownCast(geom_curve);
   if(!geom_circle){
     return;
   }
   circleCenter=geom_circle->Circ().Location();
   Dir=geom_circle->Circ().Axis().Direction();
   Radius=geom_circle->Radius();
   geom_circle->D0(first,StartPoint);
   geom_circle->D0(last,EndPoint);
   
  return;
}
};