#pragma once
#include<NodeDelegateModel>
#include<MyCustomAIS_Shape.hxx>
#include<ShapeNodeData.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
class OutputShapeNode:public NodeDelegateModel{
private:
Q_OBJECT
std::weak_ptr<ShapeNodeData> inputData;


public:
OutputShapeNode(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    if(portType==PortType::In){
        return 1;
    }
    return 0;
}
QString caption() const override{
    return tr("Output Shape Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    return ShapeNodeData(tr("Output Shape")).type();
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data){
        return;
    }
    inputData=dynamic_pointer_cast<ShapeNodeData>(data);
    if(inputData.lock()){
        TopoDS_Shape shape=inputData.lock()->Data();
        Handle(CustomAIS_Shape) outputShape=new CustomAIS_Shape(shape);
        emit EmitDrawnShape(outputShape);
        return;
    }
    return;
}
std::shared_ptr<NodeData> outData(PortIndex const port) override{
    std::shared_ptr<NodeData> ptr;
    return ptr;
}
//No embedded widget
QWidget* embeddedWidget() override{ return nullptr;}

signals:
void EmitDrawnShape(const Handle(CustomAIS_Shape)& Shape);
};
