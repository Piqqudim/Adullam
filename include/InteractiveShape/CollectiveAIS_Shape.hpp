#pragma once
#include<MyCustomAIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx>
#include<TopoDS_Edge.hxx>
#include<TopoDS_Face.hxx>
#include<TopoDS_Wire.hxx>
using namespace std;
/*
we need to create selector class for individual part of a model,
we have the edge selector,face selector,wire selector,


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

class ShapeSelector{
 private:


 public:
};