#pragma once
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<memory>
#include<BRepBuilderAPI_MakeSolid.hxx>
#include<TopoDS.hxx>
#include<InfoUtility.hpp>
using namespace QtNodes;
using namespace std;
using namespace INFO;
class ConvertToMakeSolid:public NodeDelegateModel{
private:
std::weak_ptr<ShapeNodeData> inputShape;
std::shared_ptr<ShapeNodeData> outputShape;
TopoDS_Shape Shape;

public:
ConvertToMakeSolid(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 1;
        }
        case PortType::Out:{
            return 1;
        }
        default:
         break;
    }
    return 0;
}
QString caption() const override{
    return tr("Convert To Make Solid");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            if(portIndex==0){
                return ShapeNodeData(tr("Input Shell")).type();
            }
        }
        case PortType::Out:{
            if(portIndex==0){
                return ShapeNodeData(tr("Output Solid")).type();
            }
        }
    }
    return {tr(""),tr("")};
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data){
        return;
    }
    switch(portIndex){
        case 0:{
            inputShape=dynamic_pointer_cast<ShapeNodeData>(data);
            if(inputShape.lock()){
                Shape=inputShape.lock()->Data();
                break;
            }
        }
    
    }
    if(outputShape){
        if(Shape.ShapeType()!=TopAbs_SHELL){
           LoadMessage(tr(""),tr("The Input Shape is not a shell"));
           return;
        }
        BRepBuilderAPI_MakeSolid solidmaker(TopoDS::Shell(Shape));
        if(solidmaker.IsDone()){
            outputShape->SetData(Shape);
        }
        else{
            LoadMessage(tr(""),tr("Failed to convert to solid"));
            return;
        }

    }
    else{
        outputShape=std::make_shared<ShapeNodeData>(tr(""));
        if(Shape.ShapeType()!=TopAbs_SHELL){
           LoadMessage(tr(""),tr("The Input Shape is not a shell"));
           return;
        }
        BRepBuilderAPI_MakeSolid solidmaker(TopoDS::Shell(Shape));
        if(solidmaker.IsDone()){
            outputShape->SetData(Shape);
        }
        else{
            LoadMessage(tr(""),tr("Failed to convert to solid"));
            return;
        }

    }
    emit dataUpdated(0);
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputShape.get()){
        return static_pointer_cast<NodeData>(outputShape);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};