#pragma once
#include<CurveAIS_Shape.hpp>
#include<BoxAIS_Shape.hpp>
#include<Geom_BezierCurve.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx> 
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<NCollection_Array1.hxx>
#include<gp_Dir.hxx>
#include<InfoUtility.hpp>
#include<iostream>
using namespace INFO;
using namespace std;
//we have to make sure that the number of poles must be less than max degree+1 and must be greater than 2
class BezierAIS_Shape:public CurveAIS_Shape{
  private:
Handle(Geom_BezierCurve) beziercurve; 
std::vector<Handle(EditCircleShape)>edshapes;
Handle(CustomAIS_Shape) wireShape; //this represents the surrounding convex hull
gp_Dir dir=gp_Dir(1.0,0.0,0.0);
 NCollection_Array1<gp_Pnt> pnts;
bool isRational=false;
Handle(AIS_InteractiveContext) context;
bool isFound=false;
Handle(EditCircleShape) editShape;
public:
BezierAIS_Shape(const TopoDS_Shape& shape):CurveAIS_Shape(shape){
    return;
}

void SetDir(const gp_Dir& dir_1){
  dir=dir_1;
  return;
}
gp_Dir GetDir() const{
  return dir;
}
void SetCurve(Handle(Geom_BezierCurve) c){
  beziercurve=c;
  return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
   context=con;
   return;
}
Handle(Geom_BezierCurve) GetCurve() const{
  return beziercurve;
}
//before updating shape,we have the properties of the curve e.g Poles(control points)
void UpdateShape(){
  Handle(Geom_BezierCurve) geom_curve=GetCurve();
  BRepBuilderAPI_MakeEdge edgemaker;
  edgemaker.Init(geom_curve);
  if(!edgemaker.IsDone()){
     return;
  }
  SetShape(edgemaker.Edge());
  return;
}
void DrawConvex(){
  BRepBuilderAPI_MakeWire wiremaker;
  
  for(int i=1;i<GetCurve()->NbPoles();i++){
    cout<<"Current Index  "<<(i-1)<<"\n";
    BRepBuilderAPI_MakeEdge edgemaker(GetCurve()->Pole(i-1),GetCurve()->Pole(i));
    if(edgemaker.IsDone()){
        wiremaker.Add(edgemaker.Edge());
    }
   
  }
  if(!wiremaker.IsDone()){
     return;
  }
  if(!wireShape){
     wireShape=new CustomAIS_Shape(wiremaker.Wire());
     context->Display(wireShape,true);
  }
  else{
    wireShape->SetShape(wiremaker.Wire());
   CheckDisplayStatus(wireShape,context->DisplayStatus(wireShape));

  }
  return;
}
void CheckDisplayStatus(Handle(AIS_InteractiveObject) object,const PrsMgr_DisplayStatus& status){
  switch(status){
    case PrsMgr_DisplayStatus_Displayed:{
      context->Redisplay(object,false);
      break;
    }
   case PrsMgr_DisplayStatus_Erased:{
     context->Display(object,1,4,false);
     break;
   }
 
  }
 return;  
}
void GetEditShapeHandle(const size_t& ind){
  for(int i=0;i<edshapes.size();++i){
    if(edshapes.at(i)->Index()==ind){
       editShape=edshapes.at(i);
       isFound=true;
       break;
    }
  }
  isFound=false;
  return;
}
bool IsFound() const{
  return isFound;
}
//before updateShape, we send the collection of points to an external variable

void UpdateShape(const size_t& ind,const gp_Pnt& pnt){
   GetCurve()->SetPole(ind,pnt);
  if(!editShape.IsNull()){
    editShape->SetPosition(GetCurve()->Pole(ind));
    context->SetLocation(editShape,TopLoc_Location(gp_Trsf()));
    CheckDisplayStatus(editShape,context->DisplayStatus(editShape));
    DrawConvex();
    UpdateShape();
  }
  
  return;
}
void DrawConvex(const NCollection_Array1<gp_Pnt> points){
  BRepBuilderAPI_MakeWire wiremaker;
  
  for(int i=1;i<points.Size();i++){
  BRepBuilderAPI_MakeEdge edgemaker(GetCurve()->Pole(i-1),GetCurve()->Pole(i));
  if(edgemaker.IsDone()){
     wiremaker.Add(edgemaker.Edge());
  }
 
  }
  if(!wiremaker.IsDone()){
     return;
  }
  if(!wireShape){
     wireShape=new CustomAIS_Shape(wiremaker.Wire());
     context->Display(wireShape,true);
  }
  else{
    wireShape->SetShape(wiremaker.Wire());
   CheckDisplayStatus(wireShape,context->DisplayStatus(wireShape));

  }
  return;
}
gp_Pnt GetPointAtIndex(const size_t& index){
 
  if(index>=GetCurve()->NbPoles()){
    return gp_Pnt();
  }
  
  return GetCurve()->Pole(index);
}
void ComputeEditShape(Handle(AIS_InteractiveObject) obj){
  
   if(GetCurve()->NbPoles()==0){
    return;
   }
   
  if(edshapes.empty()){
   for(int i=0;i<GetCurve()->NbPoles();i++){
     edshapes.emplace_back(new EditCircleShape(ET_BEZIER,GetCurve()->Pole(i),dir,obj,i));
     context->Display(edshapes.at(i),false);
   }
   
   }
   else{
     for(auto i=0;i<edshapes.size();i++){
      CheckDisplayStatus(edshapes.at(i),context->DisplayStatus(edshapes.at(i)));
     }
   }
   DrawConvex();
   context->UpdateCurrentViewer();
   return;
}
void RemoveEdit(){
  if(!edshapes.empty()){
    for(int i=0;i<edshapes.size();i++){
      context->Erase(edshapes.at(i),false);
    }
  }
  if(context->DisplayStatus(wireShape)==PrsMgr_DisplayStatus_Displayed){
     context->Erase(wireShape,false);
  }
  context->UpdateCurrentViewer();
  return;
}
void AlignMarkerWithDir(const gp_Dir& dir_1){
  if(edshapes.empty()){
    dir=dir_1;
    return;
  }
  for(int i=0;i<edshapes.size();i++){
    edshapes.at(i)->UpdateDir(dir);
    context->Redisplay(edshapes.at(i),false);
  }
  context->UpdateCurrentViewer();
  return;
}
};