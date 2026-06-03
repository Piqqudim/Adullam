#pragma once 
#include<AIS_Shape.hxx>
#include<TopoDS_Shape.hxx>
#include<Geom_Curve.hpp>
#include<InfoUtility.hpp>
using namespace INFO;
enum DRAFT_TYPE{
DT_OTHER,
DT_BEZIER,
DT_LINE,
DT_CIRCLE,
DT_ARC,
DT_BSPLINE,
DT_NULL
};
class CurveAIS_Shape:public AIS_Shape{
private:
 DEFINE_STANDARD_RTTIEXT(CurveAIS_Shape, AIS_Shape)
DRAFT_TYPE dtype=DT_NULL;
Handle(Geom_Curve) theCurve;

public:

CurveAIS_Shape(const TopoDS_Shape& shape):AIS_Shape(shape){
  if(shape.ShapeType()!=6){
    LoadMessage(tr(""),tr("Shape's Type is not an edge"));
    SetShape(TopoDS_Edge());
    return;
  }
  SetShape(TopoDS::Edge(shape));
  return;
}
virtual Standard_Boolean AcceptDisplayMode(const Standard_Integer theMode) const Standard_OVERRIDE
  {
    return true;
  }
  Standard_EXPORT virtual void Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
                                       const Handle(Prs3d_Presentation)&         thePrs,
                                       const Standard_Integer theMode) Standard_OVERRIDE{
     StdPrs_ToolTriangulatedShape::ClearOnOwnDeflectionChange(myshape, myDrawer, Standard_True);
      try
      {
        OCC_CATCH_SIGNALS
        StdPrs_WFShape::Add(thePrs, myshape, myDrawer);
      }
      //it throws an exception of type Standard_Failure
      catch (Standard_Failure const& anException)
      {
        LoadMessage(tr(""),tr("The WireFrame builder failed To build the presentation"));
        return;
      }
      
      return;
    }

virtual void SetCurve(const Handle(Geom_Curve)& curve) override{
  theCurve=curve;
  return;
}
Handle(Geom_Curve) TheCurve() const{
  return theCurve;
}                                     
void SetDraftType(const DRAFT_TYPE& dt){
  dtype=dt;
  return;
}
DRAFT_TYPE GetDraftType() const{
  return dtype;
}
};