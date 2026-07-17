#pragma once 
#include<NodeDelegateModel>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<memory>
#include<EdgeNodeData.hpp>
#include<ShapeNodeData.hpp>

using namespace std;
using namespace QtNodes;

class ConvertToWire:public NodeDelegateModel{
private:
std::shared_ptr<ShapeNodeData> outputShape;
std::weak_ptr<EdgeNodeData> edgeData;
TopoDS_Edge edge_1;
TopoDS_Wire outputWire;
public:
ConvertToWire(){
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
    }
}
QString caption() const override{
    return tr("Convert To Wire");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:{
                    return EdgeNodeData(tr("Input")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:{
                    return ShapeNodeData(tr("Output")).type();
                }
            }
        }
    default:
    break;
    }
    return {tr(""),tr("")};
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data){
        return;
    }
    switch(portIndex){
        case 0:{
          edgeData=dynamic_pointer_cast<EdgeNodeData>(data);
          if(edgeData.lock()){
           edge_1=edgeData.lock()->edge();
           break;
          }  
        }
    }
    if(outputShape){
     if(edge_1.IsNull()){
        return;
     }
     BRepBuilderAPI_MakeWire wiremaker(edge_1);
     if(wiremaker.IsDone()){
        outputShape->SetData(wiremaker.Wire());
     }
     else{
        return;
     }
    }
    else{
       outputShape=std::make_shared<ShapeNodeData>(tr(""));
       if(edge_1.IsNull()){
        return;
     }
     BRepBuilderAPI_MakeWire wiremaker(edge_1);
     if(wiremaker.IsDone()){
        outputShape->SetData(wiremaker.Wire());
     }
     else{
        return;
     }
    }
    emit dataUpdated(0);

}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(outputShape){
    return static_pointer_cast<NodeData>(outputShape);
  } 

    std::shared_ptr<NodeData> mptr;
    return static_pointer_cast<NodeData>(mptr);
}
QWidget* embeddedWidget() override{
    return nullptr;
}

};