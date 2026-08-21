#pragma once
#include<QUndoCommand>
#include<AIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx>
class TransformCommand:public QUndoCommand{
private:
Handle(AIS_Shape) prevShape;
Handle(AIS_Shape) currShape;
Handle(AIS_InteractiveContext) context;
public:
TransformCommand(Handle(AIS_Shape) pshape,Handle(AIS_Shape) cshape,Handle(AIS_InteractiveContext) con){
    context=con;
    prevShape=pshape;
    currShape=cshape;
    
}
void undo() override{
    if(context->IsDisplayed(currShape)){
        context->Remove(currShape,false);
    }
        context->Display(prevShape,false);
        context->UpdateCurrentViewer();
        return;
    
}
void redo() override{
    if(context->IsDisplayed(prevShape)){
        context->Remove(prevShape,false);
    }
    context->Display(currShape,false);
    context->UpdateCurrentViewer();
    return;
}
};