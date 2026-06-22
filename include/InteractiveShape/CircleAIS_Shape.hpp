#pragma once
#include<CurveAIS_Shape.hpp>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BoxAIS_Shape.hpp>
#include<Geom_Circle.hxx>

#include<gp_Pnt.hxx>
#include<PrsMgr_DisplayStatus.hxx>
#include<gp_Vec.hxx>
class CircleAIS_Shape:public CurveAIS_Shape{
private:
Handle(Geom_Circle) circleCurve;
gp_Pnt center;
gp_Pnt radiusPos;
double radius=1.0f;
gp_Dir dir;
Handle(EditCircleShape) ed; //for circle's centre
Handle(EditCircleShape) ed_1; //for circle's start point;

public:
Handle(AIS_InteractiveContext) context;
CircleAIS_Shape(const TopoDS_Shape& shape):CurveAIS_Shape(shape){
    return;
}
void SetRadius(const double& r){
    radius=r;
    return;
}
void SetCenter(const gp_Pnt& val){
    center=val;
    return;
}
void SetDir(const gp_Dir& d){
    dir=d;
    return;
}
gp_Dir Dir() const{
    return dir;
}
gp_Pnt Center() const{
    return center;
}
double Radius() const{
    return radius;
}
void SetCurve(Handle(Geom_Circle) c){
    circleCurve=c;
    return;
}
Handle(Geom_Circle) GetCircle() const{
    return circleCurve;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
void UpdateShape(){
    Handle(Geom_Circle) circle=new Geom_Circle(gp_Ax2(Center(),Dir()),Radius());
    if(!circle){
        return;
    }
    BRepBuilderAPI_MakeEdge edgeMaker;
    edgeMaker.Init(circle);
    if(!edgeMaker.IsDone()){
     cout<<"Failed To Create Circle"<<"\n";
    }
    SetShape(edgeMaker.Edge());
    return;
}
void SetRadiusPosition(const gp_Pnt& pnt){
    radiusPos=pnt;
    return;
}
gp_Pnt RadiusPos() const{
    return radiusPos;
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
void OnDisplayComponent(Handle(AIS_InteractiveObject) obj){
    if(!ed){
       ed=new EditCircleShape(Dir(),Center());
       ed->SetAttachedObject(obj);
       ed->SetEditType(ET_CIRCLE);
       ed->SetPartType(PE_CIRCLEMIDPOINT);
        context->Display(ed,1,4,false);
    }
    else{
    ed->SetPosition(Center());
    }
    if(!ed_1){
        Handle(Geom_Circle) circ=new Geom_Circle(gp_Ax2(Center(),Dir()),Radius());
        gp_Pnt pnt;
        circ->D0((double)0.0,pnt);
        SetRadiusPosition(pnt);
        ed_1=new EditCircleShape(Dir(),pnt);
        ed_1->SetAttachedObject(obj);
        ed_1->SetEditType(ET_CIRCLE);
        ed_1->SetPartType(PE_CIRCLESTARTPOINT);
        context->Display(ed_1,1,4,false);
    }
    else{
        ed_1->SetPosition(RadiusPos());
    }

    UpdatePresentation();
 return;   
}
void UpdatePresentation(){
    CheckDisplayStatus(ed,context->DisplayStatus(ed));
    CheckDisplayStatus(ed_1,context->DisplayStatus(ed_1));
    context->UpdateCurrentViewer();
    return;
}
void UpdateShape(const PARTEDIT& edittype,const gp_Pnt& pnt){
  switch(edittype){
    case PE_CIRCLEMIDPOINT:{ //moving the center of the circle also moves the end point
        SetCenter(pnt);
        UpdateShape();
        ed->UpdateShape(Dir(),Center());
        Handle(Geom_Circle) circl=new Geom_Circle(gp_Ax2(Center(),Dir()),Radius());
        gp_Pnt pnt_1;
        circl->D0((double)0.0,pnt_1);
        ed_1->SetPosition(pnt_1);
        SetRadiusPosition(pnt_1);
        CheckDisplayStatus(ed,context->DisplayStatus(ed));
        CheckDisplayStatus(ed_1,context->DisplayStatus(ed_1));
        break;
    }
  case PE_CIRCLESTARTPOINT:{
       gp_Vec delta(Center(),pnt);
       SetRadius(delta.Magnitude());
       SetRadiusPosition(Center().Translated(delta));
       UpdateShape();
       ed_1->UpdateShape(Dir(),RadiusPos());
       CheckDisplayStatus(ed_1,context->DisplayStatus(ed_1));
       
       
     break;
  }
  }
  return;
}
void RemovePrs(){
    if(ed){
        context->Erase(ed,false);
    }
    if(ed_1){
        context->Erase(ed_1,false);
    }
    context->UpdateCurrentViewer();
    return;
}
void UpdateWithTransform(const gp_Trsf& trans){
    return;
}


};