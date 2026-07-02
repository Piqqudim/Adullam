#pragma once
//this holds information about the object that it is manpulating
//let's make the editable item to be a circular surface
#include<AIS_Shape.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<TopoDS_Edge.hxx>
#include<TopoDS_Shape.hxx>
#include<BRepBuilderAPI_MakeFace.hxx>
#include<gp_Pnt.hxx>
#include<gp_Trsf.hxx>
#include<InfoUtility.hpp>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<AIS_InteractiveContext.hxx>
#include<Geom_Circle.hxx>
#include<iostream>
using namespace std;
using namespace INFO;
enum EDIT_TYPE{
 ET_CIRCLE,
 ET_LINE,
 ET_BEZIER,
 ET_BSPLINE,
 ET_ARC,
 ET_HYPERBOLA,
 ET_ELLIPSE,
 ET_NULL
};
enum PARTEDIT{
PE_LINESTART,
PE_LINEEND,
PE_LINEMIDPOINT,
PE_CIRCLEMIDPOINT,
PE_CIRCLESTARTPOINT,
PE_NULL
};
class EditCircleShape:public AIS_Shape{
 
 private:
 Handle(AIS_InteractiveObject) attachedObject;
 Handle(AIS_InteractiveContext) context;
 gp_Dir faceDir;
 gp_Pnt position; //position in space
 Quantity_Color faceColor;
 size_t index=0; //very useful for indexing in Bezier and BSplines
 EDIT_TYPE etype=ET_NULL;
 PARTEDIT pedit=PE_NULL;
 public:

 EditCircleShape(const TopoDS_Shape& Shape=TopoDS_Shape()):AIS_Shape(Shape){
    return;
 }
 EditCircleShape(const EDIT_TYPE& et,const gp_Pnt& pnt,const gp_Dir& d,Handle(AIS_InteractiveObject) obj,const size_t& ind):AIS_Shape(TopoDS_Shape()){
   etype=et;
   faceDir=d;
   attachedObject=obj;
   index=ind;
   position=pnt;
   UpdateShape(faceDir,position);
   return;
}
 void SetEditType(const EDIT_TYPE& et){
   etype=et;
   return;
 }
 void SetPartType(const PARTEDIT& pt){
   pedit=pt;
   return;
 }
 void SetIndex(const size_t& i){
   index=i;
   return;
 }
 size_t Index() const{
   return index;
 }
 void SetMyContext(Handle(AIS_InteractiveContext) con){
   context=con;
   return;
 }
 EDIT_TYPE EditType() const{
   return etype;
 }
 PARTEDIT PartEdit() const{
   return pedit;
 }
 EditCircleShape(const gp_Dir& orientation,const gp_Pnt& pos):AIS_Shape(TopoDS_Shape()){
   UpdateShape(orientation,pos);
    SetFaceTransparency(0.6);
    SetColor(faceColor);
    return;
 }
 void UpdateDir(const gp_Dir& dir){
  UpdateShape(dir,GetPosition());
  return;
 }
 void UpdateShape(const gp_Dir& dir,const gp_Pnt& pnt){
    Handle(Geom_Circle) geomCircle=new Geom_Circle(gp_Ax2(pnt,dir),10.0);
    position=pnt;
    faceDir=dir;
    if(!geomCircle){
   cout<<"Failed To Create Circle"<<"\n";
        return;
    }
    BRepBuilderAPI_MakeEdge edgeMaker;
    edgeMaker.Init(geomCircle);
    if(!edgeMaker.IsDone()){
   cout<<"Failed to initialize edge from circle"<<"\n";
     return;
    }
    BRepBuilderAPI_MakeWire wiremaker(edgeMaker.Edge());
    if(!wiremaker.IsDone()){
  cout<<"Failed to initialize wire from edge"<<"\n";
        return;
    }
    BRepBuilderAPI_MakeFace facemaker(wiremaker.Wire());
    if(!facemaker.IsDone()){
    cout<<"Failed to initialize face from wire"<<"\n";     
   return;
    }
    SetShape(facemaker.Face());
    
    return;
 }
 
 void SetFaceTransparency(const float& val){
    SetTransparency(val);
     return;
 }
 void SetPosition(const gp_Pnt& pos){
    UpdateShape(FaceDir(),pos);
    return;
 }
 gp_Pnt GetPosition() const{
   return position;
 }

 gp_Dir FaceDir() const{
    return faceDir;
 }
void SetAttachedObject(Handle(AIS_InteractiveObject) object){
   attachedObject=object;
   return;
} 
Handle(AIS_InteractiveObject) AttachedObject() const{
   return attachedObject;
}
bool AcceptDisplayMode(const Standard_Integer theMode) const override{
  return theMode==1; 
}
 void Compute(const Handle(PrsMgr_PresentationManager)& prsmgr,
                        const Handle(Prs3d_Presentation)& thePrs,
                        const Standard_Integer            theMode) override{
 
  if(theMode==1){
  AIS_Shape::Compute(prsmgr,thePrs,theMode);
  cout<<"Presentation Computed"<<"\n";
  }
    thePrs->ReCompute();
 return;
}
void ComputeSelection(const Handle(SelectMgr_Selection)& aSelection,const Standard_Integer aMode) override{
   if(aMode==4){
   AIS_Shape::ComputeSelection(aSelection,4);
   return;
   }
   if(aMode==0){
      AIS_Shape::ComputeSelection(aSelection,0);
   }
   return;
}

};
