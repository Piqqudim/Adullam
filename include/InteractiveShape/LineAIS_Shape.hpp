#pragma once 
#include<CurveAIS_Shape.hxx>
#include<Geom_Line.hxx>
class LineAIS_Shape:public CurveAIS_Shape{
private:
 DEFINE_STANDARD_RTTIEXT(LineAIS_Shape,CurveAIS_Shape)
 Handle(Geom_Line) lineCurve;
 bool isConverted=false;
public:
LineAIS_Shape(const TopoDS_Shape& shape):CurveAIS_Shape(shape){
  return;
}
void SetCurve(const Handle(Geom_Curve)& curve) override{
   SetCurve(curve);
   lineCurve=Handle(Geom_Line)::DownCast(curve);
   if(!lineCurve){
    LoadMessage(tr(""),tr("Failed To Convert To Line"));
   }
   isConverted=true;
   return;
}
Handle(Geom_Line) LineCurve() const{
    return lineCurve;
}
bool IsConverted() const{
    return isConverted;
}
};
