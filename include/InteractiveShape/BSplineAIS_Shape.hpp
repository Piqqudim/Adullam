#pragma once
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<CurveAIS_Shape.hpp>
#include<Geom_BSplineCurve.hxx>
#include<BoxAIS_Shape.hpp>
#include<MyCustomAIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx>
#include<gp_Dir.hxx>
#include<gp_Pnt.hxx>
#include<vector>
using namespace std;
class BSplineAIS_Shape:public CurveAIS_Shape{
private:
Handle(Geom_BSplineCurve) Curve;
std::vector<Handle(EditCircleShape)> handles;
Handle(AIS_InteractiveContext) context;
Handle(CustomAIS_Shape) wireShape;
Handle(EditCircleShape) handle;
gp_Dir dir;
bool isFound=false;
bool isRational=false;


public:
BSplineAIS_Shape(const TopoDS_Shape& sh=TopoDS_Shape()):CurveAIS_Shape(sh){
return;
}
void SetCurve(Handle(Geom_BSplineCurve) curve){
  Curve=curve;
  isRational=curve->IsRational();
  return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
}
Handle(AIS_InteractiveContext) Context() const{
    return context;
}
void SetDir(const gp_Dir& d){
    dir=d;
    return;
}
gp_Dir Dir() const{
    return dir;
}
Handle(Geom_BSplineCurve) GetCurve() const{
    return Curve;
}
void UpdateShape(){
    BRepBuilderAPI_MakeEdge edgemaker;
    edgemaker.Init(GetCurve());
    if(!edgemaker.IsDone()){
        return;
    }
    SetShape(edgemaker.Edge());
    return;
}
void RedrawConvex(){
    BRepBuilderAPI_MakeWire wiremaker;
  
  for(int i=1;i<GetCurve()->NbPoles();i++){
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
    return;
 }
 else{
    wireShape->SetShape(wiremaker.Wire());
    CheckDisplayStatus(wireShape,context->DisplayStatus(wireShape));
    context->UpdateCurrentViewer();
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
bool IsFound() const{
    return isFound;
}
bool IsRational() const{
    return isRational;
}
void GetHandle(const size_t& ind){
    for(int i=0;i<handles.size();++i){
    if(handles.at(i)->Index()==ind){
        handle=handles.at(i);
        isFound=true;
        break;
    }
    }
    isFound=false;
    return;
}
void UpdateShape(const size_t& ind,const gp_Pnt& pnt){
    GetCurve()->SetPole(ind,pnt);
  if(handle){
    handle->SetPosition(GetCurve()->Pole(ind));
    context->SetLocation(handle,TopLoc_Location(gp_Trsf()));
    CheckDisplayStatus(handle,context->DisplayStatus(handle));
    RedrawConvex();
    UpdateShape();
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
    
  if(handles.empty()){
   for(int i=0;i<GetCurve()->NbPoles();i++){
     handles.emplace_back(new EditCircleShape(ET_BSPLINE,GetCurve()->Pole(i),dir,obj,i));
     context->Display(handles.at(i),false);
   }
   
   }
   else{
     for(auto i=0;i<handles.size();i++){
      CheckDisplayStatus(handles.at(i),context->DisplayStatus(handles.at(i)));
     }
   }
   RedrawConvex();

   context->UpdateCurrentViewer();
   return;
}
void RemoveEdit(){
  if(!handles.empty()){
    for(int i=0;i<handles.size();i++){
        context->Erase(handles.at(i),false);
    }
  }
  if(context->IsDisplayed(wireShape)){
    context->Erase(wireShape,false);
  }
  context->UpdateCurrentViewer();
    return;
}
void AlignMarkerWithDir(const gp_Dir& dir_1){
  if(handles.empty()){
    dir=dir_1;
    return;
  }
  for(int i=0;i<handles.size();i++){
    handles.at(i)->UpdateDir(dir_1);
    context->Redisplay(handles.at(i),false);
  }
  context->UpdateCurrentViewer();
  return;
}
};