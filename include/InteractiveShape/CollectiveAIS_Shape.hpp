#pragma once
#include<MyCustomAIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx>
#include<TopoDS_Edge.hxx>
#include<TopoDS_Face.hxx>
#include<TopoDS_Wire.hxx>
#include<InfoUtility.hpp>
#include<TopoDS.hxx>
#include<vector>
#include<QtCore/QString>
using namespace std;
using namespace INFO;
/*
we need to create selector class for individual part of a model,
we have the edge selector,face selector,wire selector,a whole shape selector


*/
class EdgeSelector{
private:
Handle(AIS_Shape) myShape;
TopoDS_Edge selectedEdge;
Quantity_Color selectionColor; //color for selection
Quantity_Color edgeColor; //previous edge color
bool isSelected=false;
Handle(AIS_InteractiveContext) context;
public:
EdgeSelector(Handle(AIS_Shape) shape,const TopoDS_Edge& edge,const Quantity_Color& col,Handle(AIS_InteractiveContext) con){
    context=con;
    selectedEdge=edge;
    myShape=shape;
    selectionColor=col;
    return;
}
EdgeSelector(){
    return;
}
void SetSelectedColor(const Quantity_Color& col){
    selectionColor=col;
    return;
}
void SetSelectedShape(Handle(AIS_Shape) theShape){
    myShape=theShape;
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
Handle(AIS_Shape) GetSelectedShape() const{
    return myShape;
}
void SetSelectedEdge(const TopoDS_Edge& e){
    selectedEdge=e;
    return;
}
void SelectEdge(){
    if(!myShape){
   return;
    }
   TopAbs_ShapeEnum st=myShape->Shape().ShapeType();
   if(st==6){ //for edge
    myShape->Color(edgeColor);
    myShape->SetColor(selectionColor);
    isSelected=true;
    if(context->IsDisplayed(myShape)){
        context->Redisplay(myShape,true);
    }
   }
   else if(st<6){
  Handle(CustomAIS_Shape) cshape=Handle(CustomAIS_Shape)::DownCast(myShape);
  if(cshape){
    if(!selectedEdge.IsNull()){
        cshape->HighlightEdge(selectedEdge,selectionColor);
        cshape->isEdgeSelected=true;
        if(context->IsDisplayed(cshape)){
            context->Redisplay(cshape,true);
        }
    }

  }
   }
   else{
    return;
   }
    return;
}
void UnSelectEdge(){
    if(!myShape){
        return;
    }
     TopAbs_ShapeEnum st=myShape->Shape().ShapeType();
     if(st==6){
        if(isSelected){
            myShape->SetColor(edgeColor);
            
            isSelected=false;
            if(context->IsDisplayed(myShape)){
                context->Redisplay(myShape,true);
            }
        }
     }
     else if(st<6){
        Handle(CustomAIS_Shape) cshape=Handle(CustomAIS_Shape)::DownCast(myShape);
        if(cshape){
            if(cshape->isEdgeSelected){
             cshape->UnhighlightEdge();
             cshape->isEdgeSelected=false;
            }
            if(context->IsDisplayed(cshape)){
                context->Redisplay(cshape,true);
            }
        }
     }
    return;
}
void Nullify(){
    UnSelectEdge();
    if(myShape){
        myShape.Nullify();
    }
    if(!selectedEdge.IsNull()){
        selectedEdge=TopoDS_Edge();
    }
    return;
}
};

class FaceSelector{
private:
Handle(AIS_Shape) myShape;
TopoDS_Face selectedFace;
Quantity_Color selectedColor;
Quantity_Color faceColor;
Handle(AIS_InteractiveContext) context;
bool isSelected=false;

public:
FaceSelector(Handle(AIS_Shape) shape,const TopoDS_Face& face,const Quantity_Color& col,Handle(AIS_InteractiveContext) con){
    context=con;
    selectedFace=face;
    myShape=shape;
    selectedColor=col;
    return;
}
FaceSelector(){
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
void SetSelectedColor(const Quantity_Color& col){
    selectedColor=col;
    return;
}
void SetSelectedFace(const TopoDS_Face& f){
    selectedFace=f;
    return;
}
void SetSelectedShape(Handle(AIS_Shape) shape){
    myShape=shape;
    return;
}
void SelectFace(){
    if(!myShape){
       return;
    }
    TopAbs_ShapeEnum st=myShape->Shape().ShapeType();
    if(st==4){
        myShape->Color(faceColor);
        myShape->SetColor(selectedColor);
        isSelected=true;
        if(context->IsDisplayed(myShape)){
        context->Redisplay(myShape,true);
        }
        return;
    }
    else if(st<4){
        Handle(CustomAIS_Shape) cshape=Handle(CustomAIS_Shape)::DownCast(myShape);
        if(cshape){
            if(!selectedFace.IsNull()){
                cshape->HighlightFace(selectedFace,selectedColor);
                cshape->isFaceSelected=true;
            }
            if(context->IsDisplayed(cshape)){
                context->Redisplay(cshape,true);
            }
        }
    }
    else{
    return;
    }
    return;
}
void UnSelectFace(){
    if(!myShape){
        return;
    }
    TopAbs_ShapeEnum st=myShape->Shape().ShapeType();
    if(st==4){
        if(isSelected){
            myShape->SetColor(faceColor);
            isSelected=false;
        }
        if(context->IsDisplayed(myShape)){
            context->Redisplay(myShape,true);
        }
    }
    else if(st<4){
        Handle(CustomAIS_Shape) cshape=Handle(CustomAIS_Shape)::DownCast(myShape);
        if(cshape){
            if(cshape->isFaceSelected){
                cshape->UnhighlightFace();
                cshape->isFaceSelected=false;
            }
            if(context->IsDisplayed(cshape)){
                context->Redisplay(cshape,true);
            }
        }
    }
    else{
        return;
    }
    return;
}
void Nullify(){
    UnSelectFace();
    if(myShape){
        myShape.Nullify();
    }
    if(!selectedFace.IsNull()){
     selectedFace=TopoDS_Face();
    }
    return;
}
};
class WireSelector{
private:
Handle(AIS_Shape) myShape;
TopoDS_Wire selectedWire;
TopoDS_Wire chosenWire=TopoDS_Wire(); //this one contains value either when the selected object is wire or the subpart selected is a wire
Quantity_Color selectedColor;
Quantity_Color wireColor;
Handle(AIS_InteractiveContext) context;
bool isSelected=false;

public:
WireSelector(Handle(AIS_Shape) shape,const TopoDS_Wire& wire,const Quantity_Color& col,Handle(AIS_InteractiveContext) con){
    context=con;
    selectedWire=wire;
    myShape=shape;
    selectedColor=col;
    return;
}
WireSelector(){
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
void SetSelectedColor(const Quantity_Color& col){
    selectedColor=col;
    return;
}
void SetSelectedWire(const TopoDS_Wire& w){
    selectedWire=w;
    return;
}
void SetSelectedShape(Handle(AIS_Shape) shape){
    myShape=shape;
    return;
}
Handle(AIS_Shape) SelectedShape() const{
    return myShape;
}
void SelectWire(){
    if(!myShape){
       return;
    }
    TopAbs_ShapeEnum st=myShape->Shape().ShapeType();
    if(st==TopAbs_WIRE){
        myShape->Color(wireColor);
        myShape->SetColor(selectedColor);
        chosenWire=TopoDS::Wire(myShape->Shape());
        isSelected=true;
        if(context->IsDisplayed(myShape)){
        context->Redisplay(myShape,true);
        }
        return;
    }
    else if(st<TopAbs_WIRE){
        Handle(CustomAIS_Shape) cshape=Handle(CustomAIS_Shape)::DownCast(myShape);
        if(cshape){
            if(!selectedWire.IsNull()){
                cshape->HighlightWire(selectedWire,selectedColor);
                cshape->isWireSelected=true;
                chosenWire=selectedWire;
            }

            if(context->IsDisplayed(cshape)){
                context->Redisplay(cshape,true);
            }
        }
    }
    else{
    return;
    }
    return;
}
TopoDS_Wire ChosenWire() const{
    return chosenWire;
}
void UnSelectWire(){
    if(!myShape){
        return;
    }
    TopAbs_ShapeEnum st=myShape->Shape().ShapeType();
    if(st==TopAbs_WIRE){
        if(isSelected){
            myShape->SetColor(wireColor);
            isSelected=false;
        }
        if(context->IsDisplayed(myShape)){
            context->Redisplay(myShape,true);
        }
    }
    else if(st<TopAbs_WIRE){
        Handle(CustomAIS_Shape) cshape=Handle(CustomAIS_Shape)::DownCast(myShape);
        if(cshape){
            if(cshape->isWireSelected){
                cshape->UnhighlightWire();
                cshape->isWireSelected=false;
            }
            if(context->IsDisplayed(cshape)){
                context->Redisplay(cshape,true);
            }
        }
    }
    else{
        return;
    }
    return;
}
void Nullify(){
    UnSelectWire();
    if(myShape){
        myShape.Nullify();
    }
    if(!selectedWire.IsNull()){
     selectedWire=TopoDS_Wire();
    }
    if(!chosenWire.IsNull()){
     chosenWire=TopoDS_Wire();
    }
    return;
}




};
class ShapeSelector{
 private:
Handle(AIS_Shape) myShape;
Quantity_Color objectColor;
Quantity_Color selectedColor;
Handle(AIS_InteractiveContext) context;
bool isSelected=false;

public:
ShapeSelector(Handle(AIS_Shape) shape,const Quantity_Color& col,Handle(AIS_InteractiveContext) con){
    context=con;
    
    myShape=shape;
    selectedColor=col;
    return;
}
ShapeSelector(){
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}


void SetSelectedShape(Handle(AIS_Shape) shape){
    myShape=shape;
    return;
}
void SelectShape(){
    if(!myShape){
       return;
    }
    myShape->Color(objectColor);
    myShape->SetColor(selectedColor);
    isSelected=true;
    if(context->IsDisplayed(myShape)){
        context->Redisplay(myShape,true);
    }
    return;
}
void UnSelectShape(){
    if(!myShape){
        return;
    }
    if(isSelected){
        myShape->SetColor(objectColor);
        isSelected=false;
    }
    if(context->IsDisplayed(myShape)){
        context->Redisplay(myShape,true);
    }
    return;
}
void Nullify(){
    UnSelectShape();
    if(myShape){
        myShape.Nullify();
    }
    
    return;
}


};
class CollectiveWireSelector{
private:
std::vector<WireSelector> wireselectors;
Quantity_Color groupColor;
Handle(AIS_InteractiveContext) context;
std::vector<TopoDS_Wire> selectedwires; //either as a standalone or part of an object


public:
CollectiveWireSelector(){
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
void SetGroupColor(const Quantity_Color& color){
    groupColor=color;
    return;
}
std::vector<TopoDS_Wire> Wires() const{
    return selectedwires;
}
//this one adds myshape to sets of shapes to be displayed,and also stores the selected wire
void AddToSelection(Handle(AIS_Shape) myshape,const TopoDS_Wire& wire){
    if(!wireselectors.empty()){
      for(auto i=0;i<wireselectors.size();i++){
      if(wireselectors.at(i).SelectedShape()==myshape){
         LoadMessage(QString("Duplicate Error"),QString("This object is already selected"));
         return;
      }
      }
    }
    wireselectors.emplace_back(myshape,wire,groupColor,context);
    wireselectors.at(wireselectors.size()-1).SelectWire();  
    selectedwires.push_back(wireselectors.at(wireselectors.size()-1).ChosenWire());  
    return;
}
void UnSelectAll(){
    if(!wireselectors.empty()){
     for(int i=0;i<wireselectors.size();i++){
        wireselectors.at(i).UnSelectWire();
     }
    }

    return;
}
void Nullify(){
    UnSelectAll();
    if(!wireselectors.empty()){
    wireselectors.clear();
    }
    if(!selectedwires.empty()){
       selectedwires.clear();
    }
    return;
}

};