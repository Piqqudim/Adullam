#pragma once
#include<NodeDelegateModel>
#include<Geom_Circle.hxx>
#include<gp_Ax2.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<memory>
#include<ShapeNodeData.hpp>
using namespace std;
class PrimitiveCircleNode:public NodeDelegateModel{
private:
shared_ptr<ShapeNodeData> outputData;
TopoDS_Shape outputShape;
gp_Ax2 axis;
float Radius=1.0f;
public:
PrimitiveCircleNode(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 0;
        }
        case PortType::Out:{
            return 1;
        }
    }
    return 0;
}
void SetCircle(const gp_Ax2& ax,const float& val){
    axis=ax;
    Radius=val;
    if(Radius<=0.0f){
        Radius=1.0f;
    }
    if(outputData){
     Handle(Geom_Circle) circle=new Geom_Circle(axis,Radius);
     if(!circle){
        return;
     }
     BRepBuilderAPI_MakeEdge edgemaker;
     edgemaker.Init(circle);
     if(edgemaker.IsDone()){
        outputData->SetData(edgemaker.Edge());
     }
    }
    else{
      outputData=std::make_shared<ShapeNodeData>(tr(""));
     Handle(Geom_Circle) circle=new Geom_Circle(axis,Radius);
     if(!circle){
        return;
     }
     BRepBuilderAPI_MakeEdge edgemaker;
     edgemaker.Init(circle);
     if(edgemaker.IsDone()){
        outputData->SetData(edgemaker.Edge());
     }
    }
    return;
}
QString caption() const override{
    return tr("Primitive Circle");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Output Shape")).type();

            }
        }
    }
    return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        return std::static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};