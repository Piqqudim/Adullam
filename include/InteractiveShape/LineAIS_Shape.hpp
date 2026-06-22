#pragma once 
#include<CurveAIS_Shape.hpp>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BoxAIS_Shape.hpp>
#include<Geom_Line.hxx>
#include<gp_Pnt.hxx>
#include<gp_Vec.hxx>
#include<PrsMgr_DisplayStatus.hxx>
#include<gp_Dir.hxx>
class LineAIS_Shape:public CurveAIS_Shape{
private:

 Handle(Geom_Line) lineCurve;
gp_Pnt start; //start point
gp_Pnt end; //end point

gp_Dir dir; //the direction of draw
 bool isConverted=false;
 Handle(EditCircleShape) ed;
 Handle(EditCircleShape) ed_1;
 Handle(EditCircleShape) ed_2;
public:
Handle(AIS_InteractiveContext) context;
LineAIS_Shape(const TopoDS_Shape& shape):CurveAIS_Shape(shape){
  SetDraftType(DT_LINE);
  return;
}
void SetStartPoint(const gp_Pnt& pnt){
  start=pnt;
  return;
}

gp_Pnt UpdateMidpoint(){
  gp_Vec midpointVec(Start(),End());
  return start.Translated(midpointVec*0.5);
}
void SetEndPoint(const gp_Pnt& pnt){
  end=pnt;
  return;
}
gp_Pnt Start() const{
  return start;
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
gp_Pnt End() const{
  return end;
}
void SetDir(const gp_Dir& d){
  dir=d;
  return;
}
gp_Dir GetDir() const{
  return dir;
}
TopoDS_Edge Edge() const{
  return TopoDS::Edge(Shape());
}
void UpdateShape(){
  BRepBuilderAPI_MakeEdge edgeMaker(Start(),End());
  if(!edgeMaker.IsDone()){
    return;
  }
  SetShape(edgeMaker.Edge());
  return;
}
void SetCurve(const Handle(Geom_Curve)& curve){
   lineCurve=Handle(Geom_Line)::DownCast(curve);
   if(!lineCurve){
    LoadMessage(QString(""),QString("Failed To Convert To Line"));
    return;
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
void UpdatePresentation(){

  CheckDisplayStatus(ed,context->DisplayStatus(ed));
  CheckDisplayStatus(ed_1,context->DisplayStatus(ed_1));
  CheckDisplayStatus(ed_2,context->DisplayStatus(ed_2));
  context->UpdateCurrentViewer();
  return;
}

void UpdateShape(const PARTEDIT& edittype,const gp_Pnt& pnt){
  switch(edittype){
    case PE_LINESTART:{
      SetStartPoint(pnt);
      
      ed_1->UpdateShape(dir,UpdateMidpoint());
     
      CheckDisplayStatus(ed_1,context->DisplayStatus(ed_1));
      UpdateShape();
      break;
    }
    case  PE_LINEEND:{
     SetEndPoint(pnt);
      
      ed_1->UpdateShape(dir,UpdateMidpoint());
     
      CheckDisplayStatus(ed_1,context->DisplayStatus(ed_1));
     UpdateShape();
     break;
    }
    
  }
  
  return;
}
void OnDisplayEditComp(Handle(AIS_InteractiveObject) obj){
  if(!ed){
  ed=new EditCircleShape(dir,Start());
  
  ed->SetMyContext(context);
  ed->SetAttachedObject(obj);
  ed->SetEditType(ET_LINE);
  ed->SetPartType(PE_LINESTART);
  context->Display(ed,1,4,false);
  }
  else{
  ed->SetPosition(Start());
  }
  if(!ed_1){
  ed_1=new EditCircleShape(dir,UpdateMidpoint());
  ed_1->SetMyContext(context);
  ed_1->SetEditType(ET_LINE);
  ed_1->SetAttachedObject(obj);
  ed_1->SetPartType(PE_LINEMIDPOINT);
  context->Display(ed_1,1,4,false);
} 
  else{
  ed_1->SetPosition(UpdateMidpoint());
  }
  
  if(!ed_2){
  ed_2=new EditCircleShape(dir,End());
  
  ed_2->SetMyContext(context);
  ed_2->SetAttachedObject(obj);
  ed_2->SetEditType(ET_LINE);
  ed_2->SetPartType(PE_LINEEND);
  context->Display(ed_2,1,4,false);
  
  }
  else{
  ed_2->SetPosition(End());
  }
  UpdatePresentation();
  return;
}
void RemoveEdit(){
  if(ed){
    context->Erase(ed,false);
  }
  if(ed_1){
    context->Erase(ed_1,false);
  }
  if(ed_2){
    context->Erase(ed_2,false);
  }
  context->UpdateCurrentViewer();
  return;
}
void UpdateWithTransform(const gp_Trsf& trans){
  
  return;
}
~LineAIS_Shape(){

}
};
